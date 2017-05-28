/*
 * Controller for HwA, extended with input parameters to HwA
 *
 * Authors: Andreas Toftegaard (s144026@student.dtu.dk)
 *
 */

package io

import Chisel._
import Node._
import ocp._

object HwACtrlExt extends DeviceObject {
	var extAddrWidth = 32
	var dataWidth = 32

	def init(params : Map[String, String]) = {
		extAddrWidth = getPosIntParam(params, "extAddrWidth")
		dataWidth = getPosIntParam(params, "dataWidth")
	}

	def create(params: Map[String, String]) : HwACtrlExt = {
		Module(new HwACtrlExt(extAddrWidth=extAddrWidth, dataWidth=dataWidth))
	}

	trait Pins {
		val hwACtrlExtPins = new Bundle() {
			val ap_start_out  = UInt(OUTPUT,1)
			val ap_reset_out  = UInt(OUTPUT,1)
			val ap_ready_in   = UInt(INPUT,1)
			val ap_idle_in    = UInt(INPUT,1)
			val ap_done_in    = UInt(INPUT,1)

			val par1  = UInt(OUTPUT,1)
			val par2  = UInt(OUTPUT,1)			
		}
	}
}

class HwACtrlExt(extAddrWidth : Int = 32,
										 dataWidth : Int = 32) extends CoreDevice() {
	override val io = new CoreDeviceIO() with HwACtrlExt.Pins

	// Default response and data
	val respReg = Reg(init = OcpResp.NULL)
	respReg := OcpResp.NULL

	val rdDataReg = Reg(init = Bits(0, width = 32))
	rdDataReg := Bits(0)

	val startReg = Reg(init = Bits(0))
	startReg := Bits(0)  

	// Connections to master
	io.ocp.S.Resp := respReg
	io.ocp.S.Data := rdDataReg

	// Default values out

	io.hwACtrlExtPins.ap_start_out := startReg
	io.hwACtrlExtPins.ap_reset_out := Bits(0)

	// Parameter registers and logic

	val parReg1 = Reg(init = Bits(0, width = 32))
	parReg1 := parReg1

	val parReg2 = Reg(init = Bits(0, width = 32))
	parReg2 := parReg2	

	when(io.ocp.M.Cmd === OcpCmd.WR && io.ocp.M.Addr === Bits(4)) {
		parReg1 := io.ocp.M.Data
	}

	when(io.ocp.M.Cmd === OcpCmd.WR && io.ocp.M.Addr === Bits(8)) {
		parReg2 := io.ocp.M.Data
	}	

	io.hwACtrlExtPins.par1 := parReg1
	io.hwACtrlExtPins.par2 := parReg2		

	//States for the controller

	val s_idle :: s_start :: s_wait_read :: Nil = Enum(UInt(), 3)

	val state = Reg(init = s_idle)

	//State control

	when(state === s_idle) {
		when(io.ocp.M.Cmd === OcpCmd.WR && io.ocp.M.Data === SInt(1) && io.ocp.M.Addr === Bits(0)) {
			// On next cycle, give data valid, for a single cycle
			respReg := OcpResp.DVA
			state := s_start
			startReg := Bits(1)

		}.elsewhen(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
			respReg := OcpResp.DVA
			rdDataReg := Bits(0)  
			state === s_idle

		}.otherwise {
			state === s_idle
		}
	}

	when(state === s_start) {
		startReg := Bits(0)

		when(io.hwACtrlExtPins.ap_done_in === UInt(1)) {
			state := s_wait_read

			when(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
				respReg := OcpResp.DVA
				rdDataReg := Bits(0)
			}

		}.otherwise {
			state := s_start

			when(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
			 respReg := OcpResp.DVA
			 rdDataReg := Bits(0)
			}
		}
	}

	when(state === s_wait_read) {
		when(io.ocp.M.Cmd === OcpCmd.RD) {
			// On next cycle, give data valid, for a single cycle
			respReg := OcpResp.DVA
			rdDataReg := Bits(1)
			state := s_idle

		}.elsewhen(io.ocp.M.Cmd === OcpCmd.WR) {
				respReg := OcpResp.DVA
				state := s_wait_read
				rdDataReg := Bits(1)
		}.otherwise{
			rdDataReg := Bits(1)      
			state := s_wait_read
		}
	}
}

class HwACtrlExtTester(dut: HwACtrlExt) extends Tester(dut) {

	def idle() = {
		poke(dut.io.ocp.M.Cmd, OcpCmd.IDLE.litValue())
		poke(dut.io.ocp.M.Addr, 0)
		poke(dut.io.ocp.M.Data, 0)
		poke(dut.io.ocp.M.ByteEn, Bits("b0000").litValue())
	}

	def wr(addr: BigInt, data: BigInt, byteEn: BigInt) = {
		poke(dut.io.ocp.M.Cmd, OcpCmd.WR.litValue())
		poke(dut.io.ocp.M.Addr, addr)
		poke(dut.io.ocp.M.Data, data)
		poke(dut.io.ocp.M.ByteEn, byteEn)
	}

	def expectOut(start: BigInt, reset: BigInt) = {
		expect(dut.io.hwACtrlExtPins.ap_start_out, start)
		expect(dut.io.hwACtrlExtPins.ap_reset_out, reset)
	}

	def HwASignals(ready: BigInt, idle: BigInt, done: BigInt) = {
		poke(dut.io.hwACtrlExtPins.ap_ready_in, ready)
		poke(dut.io.hwACtrlExtPins.ap_idle_in, idle)
		poke(dut.io.hwACtrlExtPins.ap_done_in, done)      
	}    

	def rd(addr: BigInt, byteEn: BigInt) = {
		poke(dut.io.ocp.M.Cmd, OcpCmd.RD.litValue())
		poke(dut.io.ocp.M.Addr, addr)
		poke(dut.io.ocp.M.Data, 0)
		poke(dut.io.ocp.M.ByteEn, byteEn)
	}

	def expectRd(data: BigInt, resp: BigInt) = {
		expect(dut.io.ocp.S.Data, data)
		expect(dut.io.ocp.S.Resp, resp)
	}  

	def expectPar(dataPar1: BigInt, dataPar2: BigInt) = {
		expect(dut.io.hwACtrlExtPins.par1 , dataPar1)
		expect(dut.io.hwACtrlExtPins.par2 , dataPar2)

	}  	

	// Set to initial state

	println("\nSet to initial state\n")  

	idle()

	step(1)

	// Start Accelerator

	println("\nStart Accelerator\n")  

	wr(0, 1, Bits("b1111").litValue())

	step(1)

	idle()

	expectOut(1, 0)

	step(10)

	expectOut(0, 0)

	step(1)

	println("\nAcelerator done\n")  

	// Return done = 1 from HwA

	HwASignals(0, 0, 1)

	step(10)

	rd(0, Bits("b1111").litValue())

	step(1)

	idle()
	expectRd(1, 1)

	step(10)

	expectRd(0, 0)
	expectOut(0, 0)  

	step(1)

	println("\nCheck that parameters can be updated\n")  

	wr(4, 1, Bits("b1111").litValue())

	step(1)

	idle()

	expectPar(1, 0)

	step(10)

	expectPar(1, 0)

	step(1)

	wr(8, 1, Bits("b1111").litValue())	

	step(1)
	idle()

	expectPar(1, 1)

	println("\nVerify that accelerator can run again\n")  

	wr(0, 1, Bits("b1111").litValue())

	step(1)

	idle()

	expectOut(1, 0)	


}


object HwACtrlExtTester {
	def main(args: Array[String]): Unit = {
		println("Testing the HwA Ctrl")
		chiselMainTest(Array("--genHarness", "--test", "--backend", "c",
			"--compile", "--targetDir", "generated"),
			() => Module(new HwACtrlExt(32, 32))) {
				f => new HwACtrlExtTester(f)
			}
	}
}