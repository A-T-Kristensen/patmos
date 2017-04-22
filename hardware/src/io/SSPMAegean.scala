/*
 * Copyright: 2017, Technical University of Denmark, DTU Compute
 * Author: Henrik Enggaard Hansen (henrik.enggaard@gmail.com)
 * License: Simplified BSD License
 *
 * The core of a shared scratch-pad memory
 *
 * Based upon Martin Schoeberl's ALU example
 *
 */

package io

import Chisel._
import Node._

import patmos.Constants._

import ocp._

import sspm._

// /**
//  * Connection between SSPMConnector and the SSPMAegean
//  */
// trait SSPMConnectorSignals {
//   val connectorSignals = new Bundle() {
//     val enable = Bits(INPUT, 1)

//     val M = new Bundle() {
//        val Data = Bits(OUTPUT, DATA_WIDTH)
//        val Addr = Bits(OUTPUT, ADDR_WIDTH)
//        val ByteEn = Bits(OUTPUT, 4)
//        val WE = Bits(OUTPUT, 1)
//     }

//     val S = new Bundle() {
//        val Data = UInt(INPUT, DATA_WIDTH)
//     }
//   }
// }


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

  scheduler.io.done := Bool(true)

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
  mem.io.M.We := connectors(scheduler.io.out).connectorSignals.M.WE
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
class SSPMAegeanTester(dut: SSPMAegean) extends Tester(dut) {
  def idle() = {
    poke(dut.io(1).M.Cmd, OcpCmd.IDLE.litValue())
    poke(dut.io(1).M.Addr, 0)
    poke(dut.io(1).M.Data, 0)
    poke(dut.io(1).M.ByteEn, Bits("b0000").litValue())
  }

  def wr(addr: BigInt, data: BigInt, byteEn: BigInt) = {
    poke(dut.io(1).M.Cmd, OcpCmd.WR.litValue())
    poke(dut.io(1).M.Addr, addr)
    poke(dut.io(1).M.Data, data)
    poke(dut.io(1).M.ByteEn, byteEn)
  }

  def rd(addr: BigInt, byteEn: BigInt) = {
    poke(dut.io(1).M.Cmd, OcpCmd.RD.litValue())
    poke(dut.io(1).M.Addr, addr)
    poke(dut.io(1).M.Data, 0)
    poke(dut.io(1).M.ByteEn, byteEn)
  }

  // Initial setup
  println("\nSetup initial state\n")

  idle()

  expect(dut.io(1).S.Resp, 0)

  // Write test
  println("\nTest write\n")
  step(1)

  wr(1, 42, Bits("b1111").litValue())

  step(1)

  idle()

  println("\nStall until data valid\n")
  // Stall until data valid
  while(peek(dut.io(1).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  step(1)
  expect(dut.io(1).S.Resp, 0)

  // Read  test
  println("\nRead test\n")
  step(1)

  rd(1, Bits("b1111").litValue())

  step(1)

  idle()

  println("\nStall until data valid\n")
  // Stall until data valid
  while(peek(dut.io(1).S.Resp) != OcpResp.DVA.litValue()) {
    step(1)
  }

  expect(dut.io(1).S.Data, 42)

  step(1)
  expect(dut.io(1).S.Resp, 0)

}

object SSPMAegeanTester {
  def main(args: Array[String]): Unit = {
    println("Testing the SSPMAegean")
    chiselMainTest(Array("--genHarness", "--test", "--backend", "c",
      "--compile", "--targetDir", "generated"),
      () => Module(new SSPMAegean(4))) {
        f => new SSPMAegeanTester(f)
      }
  }
}


