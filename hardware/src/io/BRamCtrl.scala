/*
 * BRam interface for Patmos
 *
 * Authors: Luca Pezzarossa (lpez@dtu.dk)
 *          Andreas T. Kristensen (s144026@student.dtu.dk)
 */

package io

import Chisel._
import Node._
import ocp._

object BRamCtrl extends DeviceObject {
	var extAddrWidth = 32
	var dataWidth = 32

	def init(params : Map[String, String]) = {
		extAddrWidth = getPosIntParam(params, "extAddrWidth")
		dataWidth = getPosIntParam(params, "dataWidth")
	}

	def create(params: Map[String, String]) : BRamCtrl = {
		Module(new BRamCtrl(extAddrWidth=extAddrWidth, dataWidth=dataWidth))
	}

	trait Pins {
		val bRamCtrlPins = new Bundle() {
			val MCmd    = UInt(OUTPUT,3)
			val MAddr   = UInt(OUTPUT,extAddrWidth)
			val MData   = UInt(OUTPUT,dataWidth)
			val MByteEn = UInt(OUTPUT,4)
			val SData   = UInt(INPUT,dataWidth)
		}
	}
}

class BRamCtrl(extAddrWidth : Int = 32,
										 dataWidth : Int = 32) extends CoreDevice() {

	override val io = new CoreDeviceIO() with BRamCtrl.Pins

	// Assigments of inputs and outputs
/*  io.bRamCtrlPins.MCmd  := io.ocp.M.Cmd
	io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth-1, 0)
	io.bRamCtrlPins.MData := io.ocp.M.Data
	io.bRamCtrlPins.MByteEn := io.ocp.M.ByteEn*/

	io.bRamCtrlPins.MCmd  := Bits(0)
	io.bRamCtrlPins.MAddr := Bits(0)
	io.bRamCtrlPins.MData := Bits(0)
	io.bRamCtrlPins.MByteEn := Bits(0)
	io.ocp.S.Data := io.bRamCtrlPins.SData

	val respReg = Reg(init = OcpResp.NULL)
	respReg := OcpResp.NULL

	io.ocp.S.Resp := respReg

	// |1b|1b|2b|10b|10b|4b|4b|
	// rst, array/vect (0/1), wr_dim (0, 1, 10), M, N, factor, startbank
	// M is also for vectors

	// rst

	// array/vect

	// wr_dim

	// M

	// N

	// factor = (settings(7, 4)


	// startbank
	val settings = Reg(init = Bits(0, width = 32))
	settings := settings

	// Registes for misc.

	val cols = Reg(init = Bits(0, width = 10))
	cols := cols

	val col_cnt = Reg(init = Bits(0, width = 10))
	col_cnt := col_cnt  

	val rows = Reg(init = Bits(0, width = 10))
	rows := rows

	val row_cnt = Reg(init = Bits(0, width = 10))
	row_cnt := row_cnt  

	val max_bank = Reg(init = Bits(0, width = 4))
	max_bank := max_bank

	val start_bank = Reg(init = Bits(0, width = 4))
	start_bank := start_bank

	val cur_bank = Reg(init = Bits(0, width = 4))
	cur_bank := cur_bank

	// Number of banks used in the application
	val bank_bits = Bits(4)

	// Used for the maximum of 16 counters to memory banks

	val memories = Vec.fill(16) {Reg(init = Bits(0, width = 10))}  

	for (j <- 0 until 16) {
		memories(j) := memories(j)
	}

	//States for the controller

	val s_idle :: s_settings :: s_array_wr1 :: s_array_wr2 :: s_vec :: Nil = Enum(UInt(), 5)
	val state = Reg(init = s_idle)  

	when (state === s_idle){

		when(io.ocp.M.Addr(2) === Bits(0) && io.ocp.M.Cmd === OcpCmd.WR) {

			// Update settings

			settings := io.ocp.M.Data
			state := s_settings

	 }.elsewhen(io.ocp.M.Cmd === OcpCmd.WR || io.ocp.M.Cmd === OcpCmd.RD){

		io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth - 1, 0)
		respReg := OcpResp.DVA
		}
	}

	when(state === s_settings){

		respReg := OcpResp.DVA

		cols := settings(17, 8) >> (settings(7, 4) - Bits(1)) 
		rows := settings(27, 18) >> (settings(7, 4) - Bits(1)) 

		max_bank := settings(7, 4) - Bits(1) // # banks - 1
		start_bank := settings(3, 0)
		cur_bank := Bits(0)  
		col_cnt := Bits(0)
		row_cnt := Bits(0)

		for (j <- 0 until 16) {
			memories(j) := Bits(0)
		}

		// Check if vector or array

		when(settings(30) === Bits(0)){ // array

			when(settings(29, 28) === Bits(1)){ // wr_dim = 1
				state := s_array_wr1

			}.elsewhen(settings(29, 28) === Bits(2)){ // wr_dim = 2
				state := s_array_wr2
				
			}        
		}.otherwise{ // vector
			state := s_vec
		}
	}

	when(state === s_array_wr1) {

		when(io.ocp.M.Cmd === OcpCmd.WR){

			when(io.ocp.M.Addr(2) === Bits(1)){ // Use offset for data

				// Write out

				io.bRamCtrlPins.MCmd  := OcpCmd.WR
				io.bRamCtrlPins.MAddr(11, 0) := memories(cur_bank)
				io.bRamCtrlPins.MAddr(15, 12) := cur_bank + start_bank // Upper most 4 bits select bank
				memories(cur_bank) := memories(cur_bank) + Bits(4)
				io.bRamCtrlPins.MData := io.ocp.M.Data
				io.bRamCtrlPins.MByteEn := Bits(15)

				respReg := OcpResp.DVA

				when(col_cnt === settings(17, 8) - Bits(1)){ // Check if end of row

					col_cnt := Bits(0)

					// check if time to change row
					// no need to check max bank, since this is always the last

					when(row_cnt === rows - Bits(1) || rows === Bits(0)){

						row_cnt := Bits(0)
						cur_bank := cur_bank + Bits(1)          

					}.otherwise{

						row_cnt := row_cnt + Bits(1)

					}     					

				}.otherwise{
					col_cnt := col_cnt + Bits(1)
				}   

			}.otherwise{

				// Update settings

				state := s_settings
				settings := io.ocp.M.Data
			}
		}.elsewhen(io.ocp.M.Cmd === OcpCmd.RD){
			io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth - 1, 0)
			respReg := OcpResp.DVA			
		}
	}

	when(state === s_array_wr2) {

		when(io.ocp.M.Cmd === OcpCmd.WR){

			when(io.ocp.M.Addr(2) === Bits(1)){ // Use offset for data

				// Write out

				io.bRamCtrlPins.MCmd  := OcpCmd.WR
				io.bRamCtrlPins.MAddr(11, 0) := memories(cur_bank)				
				io.bRamCtrlPins.MAddr(15, 12) := cur_bank + start_bank
				memories(cur_bank) := memories(cur_bank) + Bits(4)

				io.bRamCtrlPins.MData := io.ocp.M.Data
				io.bRamCtrlPins.MByteEn := Bits(15)

				respReg := OcpResp.DVA

				when(col_cnt === cols - Bits(1) || cols === Bits(0)){ // Check when we reach end of column

					col_cnt := Bits(0)

					when(cur_bank === max_bank){
						cur_bank := start_bank
					}.otherwise{
						cur_bank := cur_bank + Bits(1)
					}

				}.otherwise{
					col_cnt := col_cnt + Bits(1)
				}

			}.otherwise{

				// Update settings

				state := s_settings
				settings := io.ocp.M.Data
			}
		}.elsewhen(io.ocp.M.Cmd === OcpCmd.RD){
			io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth - 1, 0)
			respReg := OcpResp.DVA			
		}
	}  

	when(state === s_vec) {

		when(io.ocp.M.Cmd === OcpCmd.WR){

			when(io.ocp.M.Addr(2) === Bits(1)){ // Use offset for data

				// Write out

				io.bRamCtrlPins.MCmd  := OcpCmd.WR
				io.bRamCtrlPins.MAddr(11, 0) := memories(cur_bank)				
				io.bRamCtrlPins.MAddr(15, 12) := cur_bank + start_bank
				memories(cur_bank) := memories(cur_bank) + Bits(4)
				io.bRamCtrlPins.MData := io.ocp.M.Data
				io.bRamCtrlPins.MByteEn := Bits(15)

				respReg := OcpResp.DVA

				row_cnt := Bits(0)

				// check if time to change bank

				when(row_cnt === rows - Bits(1)){

					row_cnt := Bits(0)
					cur_bank := cur_bank + Bits(1)

				}.otherwise{

					row_cnt := row_cnt + Bits(1)
				}

			}.otherwise{

				// Update settings

				state := s_settings
				settings := io.ocp.M.Data
			}
		}.elsewhen(io.ocp.M.Cmd === OcpCmd.RD){
			io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth - 1, 0)
			respReg := OcpResp.DVA			
		}
	}
}

class BRamCtrlTester(dut: BRamCtrl) extends Tester(dut) {

	def currentState() = {
		peek(dut.state)
	} 

	def expectState(State: BigInt) = {
		expect(dut.state, State)
	} 

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

	def rd(addr: BigInt, byteEn: BigInt) = {
		poke(dut.io.ocp.M.Cmd, OcpCmd.RD.litValue())
		poke(dut.io.ocp.M.Addr, addr)
		poke(dut.io.ocp.M.Data, 0)
		poke(dut.io.ocp.M.ByteEn, byteEn)
	}  

	def expectOut(MCmd: BigInt, MAddr: BigInt, MData: BigInt, MByteEn: BigInt) = {
		expect(dut.io.bRamCtrlPins.MCmd, MCmd)
		expect(dut.io.bRamCtrlPins.MAddr, MAddr)
		expect(dut.io.bRamCtrlPins.MData, MData)
		expect(dut.io.bRamCtrlPins.MByteEn, MByteEn)
	}  

	def expectRd(data: BigInt, resp: BigInt) = {
		expect(dut.io.ocp.S.Data, data)
		expect(dut.io.ocp.S.Resp, resp)
	}    

	println("\n*************************")
	println("\nSet to initial state\n")
	println("*************************\n")	

	idle()
	expectOut(0, 0, 0, 0)
	expectState(0)

	step(1)

	expectOut(0, 0, 0, 0)
	expectState(0)

	step(1)

	/*
		Put into wr_dim 2 state

		1) Write settings
		2) Write array (4x4), banks = 2, start_bank = 0
	*/  

	println("\n*************************")
	println("\nWrite settings\n")  
	println("*************************\n")


	wr(0, Bits("b00100000000100000000010000100000").litValue() , Bits("b1111").litValue())
	expectState(0)
	expectOut(0, 0, 0, 0) // The bram should not see this

	step(1)

	idle()

	// settings are being set and we now go to state 1
	expect(dut.io.ocp.S.Resp, 0)
	expectState(1)

	step(1)

	println("\n*************************")
	println("\nTest wr_dim 2 state\n")  
	println("*************************\n")
	
	// Now into wr_dim_2 state, give slave response since settings are set.
	expect(dut.io.ocp.S.Resp, 1)  
	expectState(3)
	expectOut(0, 0, 0, 0)

	expect(dut.rows, 2) // Max rows per - 1
	expect(dut.cols, 2)
	expect(dut.col_cnt, 0)
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 0)
	expect(dut.cur_bank, 0)

	step(1)  

	expectState(3)
	expectOut(0, 0, 0, 0)

	step(1) 

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0000000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(3)

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(3)  

	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)	

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000000000").litValue(), 3, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.col_cnt, 0)  
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)  

	step(1)	

	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0001000000000100").litValue(), 1, Bits("b1111").litValue())
	expectState(3)


	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 1)  

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000001000").litValue(), 2, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)  

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000001100").litValue(), 3, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)	

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000001000").litValue(), 2, Bits("b1111").litValue())
	expectState(3)

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)		

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000001100").litValue(), 3, Bits("b1111").litValue())
	expectState(3)

	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 1)

	// We now stay idle for several clock cycles

	step(1)

	idle()
	expectOut(0, 0, 0, 0)
	expectState(3)

	step(5)
	expectOut(0, 0, 0, 0)
	expectState(3)

	step(1) 

	// And resume

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000010000").litValue(), 3, Bits("b1111").litValue())
	expectState(3)

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 0)	

	// We now write new settings

	step(1)

	println("\n*************************")
	println("\nWrite new settings while not finished\n")
	println("*************************\n")

	// Now start_bank is = 1


	wr(0, Bits("b00100000000100000000010000100001").litValue() , Bits("b1111").litValue())
	expectState(3)
	expectOut(0, 0, 0, 0) // The bram should not see this

	step(1)
	idle()

	// settings are being set

	expect(dut.io.ocp.S.Resp, 0)
	expectState(1)

	expect(dut.col_cnt, 1)
	expect(dut.row_cnt, 0)
	expect(dut.start_bank, 0) // Old settings
	expect(dut.cur_bank, 0)

	step(1)

	// settings are set

	expect(dut.io.ocp.S.Resp, 1)
	expectState(3)  

	expect(dut.rows, 2)
	expect(dut.cols, 2)  // Max rows per -1
	expect(dut.col_cnt, 0)
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 1) // Updated
	expect(dut.cur_bank, 0)    

	step(1)

	expectState(3)  

	step(2) // Still same settings

	expect(dut.io.ocp.S.Resp, 0)
	expectState(3)  

	expect(dut.rows, 2)
	expect(dut.cols, 2)  // Max rows per
	expect(dut.col_cnt, 0)  
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 1) // Updated
	expect(dut.cur_bank, 0)     

	step(1)

	/*
		Put into wr_dim 1 state

		1) Write settings
		2) Write array (2x2)
		3) Banks = 2

	*/   

	println("\n*************************")
	println("\nWr_dim_1 test\n")
	println("*************************\n")	

	wr(0, Bits("b00010000000010000000001000100010").litValue() , Bits("b1111").litValue())
	expectState(3)
	expectOut(0, 0, 0, 0) // The bram should not see this  

	step(1)

	idle()

	expect(dut.io.ocp.S.Resp, 0)
	expectState(1)  

	expect(dut.rows, 2)
	expect(dut.cols, 2)  // Max rows per from previous
	expect(dut.col_cnt, 0)  
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 1) // Old value
	expect(dut.cur_bank, 0)    

	step(1)

	expect(dut.io.ocp.S.Resp, 1)
	expectState(2)  

	expect(dut.rows, 1)
	expect(dut.cols, 1)  // Max rows per - 1
	expect(dut.col_cnt, 0)  
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 2) // Updated
	expect(dut.cur_bank, 0)      

	step(1)

	// We now write the 2x2 matrix

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0010000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(2)

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)
	expect(dut.start_bank, 2) // Updated	

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0010000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(2)  

	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)	

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)	

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0011000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(2)

	expect(dut.col_cnt, 0)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0011000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(2)  

	expect(dut.col_cnt, 1)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)	

	step(1)
	expectState(2)  
	idle()
	expect(dut.io.ocp.S.Resp, 1)

	/*
		Put into vector state

		1) Write settings
		2) Write vec (4)
		3) 2 banks

	*/   	
	println("\n*************************")
	println("\nVector test\n")
	println("*************************\n")

	wr(0, Bits("b01000000000100000000000000100000").litValue() , Bits("b1111").litValue())
	expectState(2)
	expectOut(0, 0, 0, 0) // The bram should not see this  

	step(1)

	idle()

	expect(dut.io.ocp.S.Resp, 0)
	expectState(1)  
// Old value
	expect(dut.col_cnt, 0)
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 2)

	step(1)

	expect(dut.io.ocp.S.Resp, 1)
	expectState(4)  
// Updated
	expect(dut.rows, 2)
	expect(dut.col_cnt, 0)
	expect(dut.row_cnt, 0)
	expect(dut.max_bank, 1)
	expect(dut.start_bank, 0)

	step(1)

	// we now write a vector of length 4

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0000000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(4)

	expect(dut.row_cnt, 0)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(4)  

	expect(dut.row_cnt, 1)
	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)	

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0001000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(4)

	expect(dut.row_cnt, 0)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(4)  

	expect(dut.row_cnt, 1)
	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	// Do a read, check that we do not change state.

	expectState(4)
	idle()
	expect(dut.io.ocp.S.Resp, 1)
	rd(0, Bits("b1111").litValue())

	step(1)
	expectOut(0, 0, 0, 0)
	expectState(4)
	expect(dut.io.ocp.S.Resp, 1)


	/*
		Put into wr_dim 2 state

		1) Write settings
		2) Write array (4x4), (4 banks), start_bank = 0
	*/  

	println("\n*************************")
	println("\nWrite settings\n")  
	println("*************************\n")


	wr(0, Bits("b00100000000100000000010001000000").litValue() , Bits("b1111").litValue())
	expectState(4)
	expectOut(0, 0, 0, 0) // The bram should not see this

	step(1)

	idle()

	// settings are being set and we now go to state 1
	expect(dut.io.ocp.S.Resp, 0)
	expectState(1)

	step(1)

	println("\n*************************")
	println("\nTest wr_dim 2 state with 4 banks\n")  
	println("*************************\n")
	
	// Now into wr_dim_2 state, give slave response since settings are set.
	expect(dut.io.ocp.S.Resp, 1)  
	expectState(3)
	expectOut(0, 0, 0, 0)

	expect(dut.rows, 0) // Max rows per
	expect(dut.cols, 0)
	expect(dut.col_cnt, 0)
	expect(dut.max_bank, 3)
	expect(dut.start_bank, 0)
	expect(dut.cur_bank, 0)

	step(1)  

	expectState(3)
	expectOut(0, 0, 0, 0)

	step(1) 

	// We now test a write
	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0000000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(3)

	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000000000").litValue(), 2, Bits("b1111").litValue())
	expectState(3)  

	expect(dut.cur_bank, 1)
	expect(dut.io.ocp.S.Resp, 0)	

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0010000000000000").litValue(), 3, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.cur_bank, 2)
	expect(dut.io.ocp.S.Resp, 0)  

	step(1)	

	wr(4, 1, Bits("b1111").litValue()) // We always write to addr 4 when just writing
	expectOut(1, Bits("b0011000000000000").litValue(), 1, Bits("b1111").litValue())
	expectState(3)

	expect(dut.cur_bank, 3)
	expect(dut.io.ocp.S.Resp, 1)  

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.cur_bank, 0)
	expect(dut.io.ocp.S.Resp, 0)  

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0001000000000100").litValue(), 3, Bits("b1111").litValue())
	expectState(3)	

	expect(dut.cur_bank, 1)

	step(1)

	idle()
	expect(dut.io.ocp.S.Resp, 1)	

	step(1)

	wr(4, 2, Bits("b1111").litValue())
	expectOut(1, Bits("b0010000000000100").litValue(), 2, Bits("b1111").litValue())
	expectState(3)

	expect(dut.cur_bank, 2)
	expect(dut.io.ocp.S.Resp, 0)		

	step(1)

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0011000000000100").litValue(), 3, Bits("b1111").litValue())
	expectState(3)

	expect(dut.cur_bank, 3)

	// We now stay idle for several clock cycles

	step(1)

	idle()
	expectOut(0, 0, 0, 0)
	expectState(3)

	step(5)
	expectOut(0, 0, 0, 0)
	expectState(3)

	step(1) 

	// And resume

	wr(4, 3, Bits("b1111").litValue())
	expectOut(1, Bits("b0000000000001000").litValue(), 3, Bits("b1111").litValue())
	expectState(3)

	expect(dut.cur_bank, 0)	

}


object BRamCtrlTester {
	def main(args: Array[String]): Unit = {
		println("Testing the BRamCtrl")
		chiselMainTest(Array("--genHarness", "--test", "--backend", "c",
			"--compile", "--targetDir", "generated"),
			() => Module(new BRamCtrl(32, 32))) {
				f => new BRamCtrlTester(f)
			}
	}
}