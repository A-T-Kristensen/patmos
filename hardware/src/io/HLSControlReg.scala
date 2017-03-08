/*
 * Control register for HLS
 *
 * Authors: Andreas Toftegaard (s144026@student.dtu.dk)
 *
 */

package io

import Chisel._
import Node._
import ocp._

object HLSControlReg extends DeviceObject {
  var extAddrWidth = 32
  var dataWidth = 32

  def init(params : Map[String, String]) = {
    extAddrWidth = getPosIntParam(params, "extAddrWidth")
    dataWidth = getPosIntParam(params, "dataWidth")
  }

  def create(params: Map[String, String]) : HLSControlReg = {
    Module(new HLSControlReg(extAddrWidth=extAddrWidth, dataWidth=dataWidth))
  }

  trait Pins {
    val hLSControlRegPins = new Bundle() {
      val ap_start_out  = UInt(OUTPUT,1)
      val ap_reset_out  = UInt(OUTPUT,1)
      val ap_ready_in   = UInt(INPUT,1)
      val ap_idle_in    = UInt(INPUT,1)
      val ap_done_in    = UInt(INPUT,1)
    }
  }
}

class HLSControlReg(extAddrWidth : Int = 32,
                     dataWidth : Int = 32) extends CoreDevice() {
  override val io = new CoreDeviceIO() with HLSControlReg.Pins

  // Default response and data
  val respReg = Reg(init = OcpResp.NULL)
  respReg := OcpResp.NULL

  val rdDataReg = Reg(init = Bits(0, width = 32))
  rdDataReg := rdDataReg

  //For count register

  val CNT_MAX = UInt(3); // The number of cycles that we reset

  val cntReg = Reg(init = UInt(0, 5))
  cntReg:= cntReg

  // Connections to master
  io.ocp.S.Resp := respReg
  io.ocp.S.Data := rdDataReg

  // Default values out

  io.hLSControlRegPins.ap_start_out := Bits(0)
  io.hLSControlRegPins.ap_reset_out := Bits(0)

  //States for the controller

  val s_idle :: s_reset :: s_stall :: s_start :: s_wait_read :: Nil = Enum(UInt(), 5)

  val state = Reg(init = s_idle)

  //State control

  when(state === s_idle) {
    when(io.ocp.M.Cmd === OcpCmd.WR && io.ocp.M.Data === SInt(1)) {
      // On next cycle, give data valid, for a single cycle
      respReg := OcpResp.DVA
      state := s_reset
      io.hLSControlRegPins.ap_reset_out := UInt(1)

    }.elsewhen(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
      respReg := OcpResp.DVA
      rdDataReg := Bits(0)  
      state === s_idle

    }.otherwise {
      state === s_idle
    }
  }

  when(state === s_reset) {

    io.hLSControlRegPins.ap_reset_out := UInt(1)

    when(cntReg === CNT_MAX) {
      cntReg := UInt(0)
      state := s_stall

      when(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
          respReg := OcpResp.DVA
          rdDataReg := Bits(0)
        }

    }.otherwise {
      cntReg := cntReg + UInt(1)
      
      state := s_reset

      when(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
        respReg := OcpResp.DVA
        rdDataReg := Bits(0)
      }
    }
  }

  when(state === s_stall) {

    state := s_start

    when(io.ocp.M.Cmd === OcpCmd.RD || io.ocp.M.Cmd === OcpCmd.WR) {
     respReg := OcpResp.DVA
     rdDataReg := Bits(0)
    }
  }

  when(state === s_start) {

    io.hLSControlRegPins.ap_start_out := UInt(1)

    when(io.hLSControlRegPins.ap_done_in === UInt(1)) {
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
      //state := s_idle
	  state := s_wait_read
    }.elsewhen(io.ocp.M.Cmd === OcpCmd.WR) {
        respReg := OcpResp.DVA
      	state := s_wait_read
    }.otherwise{
      state := s_wait_read
    }
  }
}