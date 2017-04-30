/*
 * Copyright: 2017, Technical University of Denmark, DTU Compute
 * Author: Henrik Enggaard Hansen (henrik.enggaard@gmail.com)
 *         Andreas Toftegaard Kristensen (s144026@student.dtu.dk)
 * License: Simplified BSD License
 *
 * The core fore a shared scratch-pad memory on Aegean
 *
 *
 */

package io

import Chisel._
import Node._

import patmos.Constants._

import ocp._

import sspm._

/**
 * A top level of SSPMAegean
 */
class SSPMAegean(val nConnectors: Int) extends Module {

  //override val io = new CoreDeviceIO()

  val io = Vec.fill(nConnectors) { new OcpCoreSlavePort(ADDR_WIDTH, DATA_WIDTH) }

  // Generate modules
  val mem = Module(new memSPM(1024))
  val connectors = Vec.fill(nConnectors) { Module(new SSPMConnector()).io }
  val scheduler = Module(new Scheduler(nConnectors))
  val decoder = UIntToOH(scheduler.io.out, nConnectors)

  scheduler.io.done := Bool(true) // Set scheduler to start

  // Connect the SSPMConnector with the SSPMAegean
  for (j <- 0 until nConnectors) {
      connectors(j).ocp.M <> io(j).M
      connectors(j).ocp.S <> io(j).S
      connectors(j).connectorSignals.S.Data := mem.io.S.Data

    // Enable connectors based upon one-hot coding of scheduler
    connectors(j).connectorSignals.enable := decoder(j)
  }

  mem.io.M.Data := connectors(scheduler.io.out).connectorSignals.M.Data
  mem.io.M.Addr := connectors(scheduler.io.out).connectorSignals.M.Addr
  mem.io.M.ByteEn := connectors(scheduler.io.out).connectorSignals.M.ByteEn
  mem.io.M.We := connectors(scheduler.io.out).connectorSignals.M.We
}

// Generate the Verilog code by invoking chiselMain() in our main()
object SSPMAegeanMain {
  def main(args: Array[String]): Unit = {
    println("Generating the SSPMAegean hardware")
    val chiselArgs = args.slice(0,args.length) // If we later add for number of connectors,
                                               // we shoud index in another fashion, see SRamCtrl
    chiselMain(chiselArgs, () => Module(new SSPMAegean(4)))
  }
}


/**
 * Test the SSPMAegean design
 */
class SSPMAegeanTester(dut: SSPMAegean, size: Int) extends Tester(dut) {

  // Set CPU core idle
  // It is important that this is done if
  // you want to work with the same address later on
  def idle(core: Int) = {
    poke(dut.io(core).M.Cmd, OcpCmd.IDLE.litValue())
    poke(dut.io(core).M.Addr, 0)
    poke(dut.io(core).M.Data, 0)
    poke(dut.io(core).M.ByteEn, Bits("b0000").litValue())
  }

  // Simulate a write instruction from Patmos
  def wr(addr: BigInt, data: BigInt, byteEn: BigInt, core: Int) = {
    poke(dut.io(core).M.Cmd, OcpCmd.WR.litValue())
    poke(dut.io(core).M.Addr, addr)
    poke(dut.io(core).M.Data, data)
    poke(dut.io(core).M.ByteEn, byteEn)
  }

  // Simulate a read instruction from Patmos
  def rd(addr: BigInt, byteEn: BigInt, core: Int) = {
    poke(dut.io(core).M.Cmd, OcpCmd.RD.litValue())
    poke(dut.io(core).M.Addr, addr)
    poke(dut.io(core).M.Data, 0)
    poke(dut.io(core).M.ByteEn, byteEn)
  }

  // Check wires to shared scratch-pad memory
  def mem() = {
    peek(dut.mem.io.M.Data)
    peek(dut.mem.io.M.Addr)
    peek(dut.mem.io.M.We)
    peek(dut.mem.io.S.Data)
  }

  // Initial setup, all cores set to idle

  println("\nSetup initial state\n")

  for(i <- 0 until size){
  	idle(i)
  }

  step(1)

  for(i <- 0 until size){
  	expect(dut.io(i).S.Resp, 0)
  }

  // Write test, write from core i to memory location,
  // each core only writes once the previous core has read
  // its value back

  println("\nTest write\n")

  for(i <- 0 until size){

    // Write

	  wr((i+1)*4, i+1, Bits("b1111").litValue(), i)

    step(1)

	  while(peek(dut.io(i).S.Resp) != OcpResp.DVA.litValue()) {
	    step(1)
	  }

    // Request to read back the data to determine if correct

    rd((i+1)*4, Bits("b1111").litValue(), i)

    step(1)

    while(peek(dut.io(i).S.Resp) != OcpResp.DVA.litValue()) {
      step(1)
    }

    expect(dut.io(i).S.Data, i+1)

    idle(i)
  }

  // Read test

  println("\nRead test\n")

  for(i <- 0 until size){

	  rd((i+1)*4, Bits("b1111").litValue(), i)

    step(1)

  	// Stall until data valid

	  while(peek(dut.io(i).S.Resp) != OcpResp.DVA.litValue()) {
	    step(1)
	  }

    expect(dut.io(i).S.Data, i+1)

    idle(i)
  }

  // Test for expected fails
  // byte writes uses byte enable and not address
  // so writing to address 5 should overwrite address 4 data

  println("\nTest for expected overwrite\n")

  wr(4, 1, Bits("b1111").litValue(), 0)

  step(1)

  idle(0)

  while(peek(dut.io(0).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  wr(5, 3, Bits("b1111").litValue(), 1)

  step(1)

  idle(1)

  while(peek(dut.io(1).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  rd(4, Bits("b1111").litValue(), 0)

  step(1)

  idle(0)

  // Stall until data valid
  while(peek(dut.io(0).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  expect(dut.io(0).S.Data, 3)

  step(1)

  expect(dut.io(0).S.Resp, 0)

  step(1)

  for(i <- 0 until size){
    idle(i)
  }

  // We just wait long enough such that core 1 gets its response

  step(1)

  // Have multiple cores write at the same time and then reading
  // They should then be allowed to read once they have a response

  println("\nTest with multiple cores\n")

  var rdResp = 0
  var currentCore = 0
  var prevCore = 0
  var wrRespCores: Array[Int] =  Array[Int](0, 0, 0, 0)

  wr(4, 2, Bits("b1111").litValue(), 0)
  wr(8, 3, Bits("b1111").litValue(), 1)
  wr(12, 4, Bits("b1111").litValue(), 2)
  wr(16, 5, Bits("b1111").litValue(), 3)

  currentCore = peek(dut.scheduler.io.out).toInt

  step(1)

  prevCore = currentCore

  for(i <- 0 until size){
    if(i != prevCore){
      idle(i)
    }
  }

  currentCore = peek(dut.scheduler.io.out).toInt

  while(rdResp != size) {

    if(peek(dut.io(prevCore).S.Resp) == OcpResp.DVA.litValue() && wrRespCores(prevCore) == 0){

      // Receive response for write, now read
      rd((prevCore+1)*4, Bits("b1111").litValue(), prevCore)
      wrRespCores(prevCore) = 1

    } else if (peek(dut.io(prevCore).S.Resp) == OcpResp.DVA.litValue() && wrRespCores(prevCore) == 1) {

      // check read
      rdResp = rdResp + 1
      expect(dut.io(prevCore).S.Data, prevCore + 2)
      idle(prevCore)
    }

    step(1)

    prevCore = currentCore
    currentCore = peek(dut.scheduler.io.out).toInt

    if(peek(dut.io(prevCore).S.Resp) == OcpResp.NULL.litValue()) {
      idle(prevCore)
    }


  }

  step(1)

  // Synchronization

  println("\nSynchronization\n")

  rd(0, Bits("b1111").litValue(), 0)

  step(1)

  while(peek(dut.io(0).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  expect(dut.scheduler.io.out, 0)

  rd(4, Bits("b1111").litValue(), 0)

  step(1)

  expect(dut.scheduler.io.out, 0)
  expect(dut.io(0).S.Resp, OcpResp.DVA.litValue())

  wr(4, 1, Bits("b1111").litValue(), 0)

  step(1)

  expect(dut.scheduler.io.out, 1)

  expect(dut.io(0).S.Resp, OcpResp.DVA.litValue())
}

object SSPMAegeanTester {
  def main(args: Array[String]): Unit = {
    println("Testing the SSPMAegean")
    chiselMainTest(Array("--genHarness", "--test", "--backend", "c",
      "--compile", "--targetDir", "generated"),
      () => Module(new SSPMAegean(4))) {
        f => new SSPMAegeanTester(f, 4)
      }
  }
}