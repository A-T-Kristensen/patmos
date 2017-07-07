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

  val settings = Reg(init = Bits(0, width = 32))
  settings := settings

  // Registes for misc.

  val n = Reg(init = Bits(0, width = 10))
  n := n

  val col_cnt = Reg(init = Bits(0, width = 10))
  col_cnt := col_cnt  

  val m = Reg(init = Bits(0, width = 10))
  m := m

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

  //States for the controller

  val s_idle :: s_settings :: s_array_wr1 :: s_array_wr2 :: s_vec :: Nil = Enum(UInt(), 5)
  val state = Reg(init = s_idle)  

  when (state === s_idle){

    when(io.ocp.M.Addr(2) === Bits(0) && io.ocp.M.Cmd === OcpCmd.WR) {

      // Update settings

      settings := io.ocp.M.Data
      state := s_settings

   }.elsewhen(io.ocp.M.Cmd === OcpCmd.WR || io.ocp.M.Cmd === OcpCmd.RD){

    respReg := OcpResp.DVA

    }
  }

  when(state === s_settings){

    respReg := OcpResp.DVA

    n := (settings(16, 8) >> settings(7, 4)) - Bits(1)
    m := (settings(27, 20) >> settings(7, 4)) - Bits(1)
    max_bank := settings(7, 4) + settings(7, 4) - Bits(1)
    start_bank := settings(3, 0)
    cur_bank := settings(3, 0)     
    col_cnt := Bits(0)
    row_cnt := Bits(0)

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

  }

  when(state === s_array_wr2) {

    when(io.ocp.M.Cmd === OcpCmd.WR){

      when(io.ocp.M.Addr(2) === Bits(0)){

        // Write out

        io.bRamCtrlPins.MCmd  := OcpCmd.WR
        io.bRamCtrlPins.MAddr(15, 11) := cur_bank
        io.bRamCtrlPins.MAddr(10, 0) := io.ocp.M.Addr(10, 0)

        io.bRamCtrlPins.MData := io.ocp.M.Data
        io.bRamCtrlPins.MByteEn := Bits(15)

        respReg := OcpResp.DVA

        when(col_cnt === n){

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
    }
  }  

  when(state === s_vec) {
    
  }    

}
