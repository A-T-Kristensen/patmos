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
  io.bRamCtrlPins.MCmd  := io.ocp.M.Cmd
  io.bRamCtrlPins.MAddr := io.ocp.M.Addr(extAddrWidth-1, 0)
  io.bRamCtrlPins.MData := io.ocp.M.Data
  io.bRamCtrlPins.MByteEn := io.ocp.M.ByteEn
  io.ocp.S.Data := io.bRamCtrlPins.SData

  val respReg = Reg(init = OcpResp.NULL)
  respReg := OcpResp.NULL

  io.ocp.S.Resp := respReg

  when(io.bRamCtrlPins.MCmd === OcpCmd.WR || io.bRamCtrlPins.MCmd === OcpCmd.RD) {
      respReg :=  OcpResp.DVA
  }
}
