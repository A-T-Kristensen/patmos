/*
   Copyright 2014 Technical University of Denmark, DTU Compute. 
   All rights reserved.
   
   This file is part of the time-predictable VLIW processor Patmos.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.

      2. Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in the
         documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
   NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   The views and conclusions contained in the software and documentation are
   those of the authors and should not be interpreted as representing official
   policies, either expressed or implied, of the copyright holder.
 */

/*
 * Boot loader (for uniprocessor).
 * 
 * Authors: Tórur Biskopstø Strøm (torur.strom@gmail.com)
 *          Wolfgang Puffitsch (wpuffitsch@gmail.com)
 *
 */

//We need this if we want to make it a bootapp
#include "boot.h"
#include "include/patio.h"
#include "include/bootable.h"

// #define DEBUG

// a variable to remember the (shadow) stack pointer
static volatile unsigned int r31;

int main(void) __attribute__((noreturn));

int main(void) {

  // save (shadow) stack pointer
  asm volatile ("mov %0 = $r31;" : "=r" (r31));

#ifdef DEBUG
  WRITE("DOWN\n", 5);
#endif

  // download application
  volatile int (*entrypoint)() = download();
#ifdef DEBUG
  // force some valid address for debugging
  if (entrypoint == NULL) {
    entrypoint = 0x20004;
  }
#endif

  // initialize the content of the I-SPM from the main memory
  // copy words not bytes
  for (int i = 0; i < get_ispm_size()/4; ++i) {
    // starting at 64 K (1 << 16) word address (/4)
    *(SPM+(1<<16)/4+i) = *(MEM+(1<<16)/4+i);
  }

  static unsigned char msg[10];

#ifdef DEBUG
  WRITE("START ", 6);
    
  msg[0] = XDIGIT(((int)entrypoint >> 28) & 0xf);
  msg[1] = XDIGIT(((int)entrypoint >> 24) & 0xf);
  msg[2] = XDIGIT(((int)entrypoint >> 20) & 0xf);
  msg[3] = XDIGIT(((int)entrypoint >> 16) & 0xf);
  msg[4] = XDIGIT(((int)entrypoint >> 12) & 0xf);
  msg[5] = XDIGIT(((int)entrypoint >>  8) & 0xf);
  msg[6] = XDIGIT(((int)entrypoint >>  4) & 0xf);
  msg[7] = XDIGIT(((int)entrypoint >>  0) & 0xf);
  msg[8] = '\n';
  WRITE(msg, 9);
#endif

  // call the application's _start()
  int retval = -1;
  if (entrypoint != 0) {
    // enable global mode
    global_mode();

    retval = (*entrypoint)();

    // Return may be "unclean" and leave registers clobbered.
    asm volatile ("" : :
                  : "$r2", "$r3", "$r4", "$r5",
                    "$r6", "$r7", "$r8", "$r9",
                    "$r10", "$r11", "$r12", "$r13",
                    "$r14", "$r15", "$r16", "$r17",
                    "$r18", "$r19", "$r20", "$r21",
                    "$r22", "$r23", "$r24", "$r25",
                    "$r26", "$r27", "$r28", "$r29",
                    "$r30", "$r31");

    // enable local mode again
    local_mode();
  }

  // restore (shadow) stack pointer
  asm volatile ("mov $r31 = %0;" : : "r" (r31));

#ifdef DEBUG
  WRITE("EXIT\n", 5);
#endif

  // Print exit magic and return code
#ifdef ETHMAC
  msg[0] = '\0';
  msg[1] = 'x';
  msg[2] = retval & 0xff;
  udp_send(TX_ADDR, ARP_ADDR, host_ip, TARGET_PORT, HOST_PORT, msg, 3, 10000);
#else
  uart_write('\0');
  uart_write('x');
  uart_write(retval & 0xff);
#endif

  // clear caches and loop back
  inval_dcache();
  inval_mcache();
  _start();

  for(;;);
}
