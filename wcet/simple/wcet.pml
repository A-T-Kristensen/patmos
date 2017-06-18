---
format: pml-0.1
triple: patmos-unknown-unknown-elf
machine-functions:
- name: 8
  level: machinecode
  mapsto: main
  arguments:
  - name: "%argc"
    index: 0
    registers:
    - r3
  hash: 0
  blocks:
  - name: 0
    mapsto: entry
    predecessors: []
    successors: []
    instructions:
    - index: 0
      opcode: SRESi
      size: 4
      stack-cache-argument: 8
      address: 133428
    - index: 1
      opcode: MFS
      size: 4
      address: 133432
    - index: 2
      opcode: SWS
      size: 4
      memmode: store
      memtype: stack
      address: 133436
    - index: 3
      opcode: LIl
      size: 8
      address: 133440
    - index: 4
      opcode: MFS
      size: 4
      address: 133448
    - index: 5
      opcode: SWS
      size: 4
      memmode: store
      memtype: stack
      address: 133452
    - index: 6
      opcode: LWC
      size: 4
      memmode: load
      memtype: cache
      address: 133456
    - index: 7
      opcode: LWC
      size: 4
      memmode: load
      memtype: cache
      address: 133460
    - index: 8
      opcode: LWC
      size: 4
      memmode: load
      memtype: cache
      address: 133464
    - index: 9
      opcode: LWC
      size: 4
      memmode: load
      memtype: cache
      address: 133468
    - index: 10
      opcode: ADDr
      size: 4
      address: 133472
    - index: 11
      opcode: SRAi
      size: 4
      address: 133476
    - index: 12
      opcode: CALL
      callees:
      - foo
      size: 4
      branch-type: call
      branch-delay-slots: 3
      address: 133480
    - index: 13
      opcode: SRi
      size: 4
      address: 133484
    - index: 14
      opcode: ADDr
      size: 4
      address: 133488
    - index: 15
      opcode: SRAi
      size: 4
      address: 133492
    - index: 16
      opcode: SENSi
      size: 4
      stack-cache-argument: 8
      address: 133496
    - index: 17
      opcode: LWS
      size: 4
      memmode: load
      memtype: stack
      address: 133500
    - index: 18
      opcode: NOP
      size: 4
      address: 133504
    - index: 19
      opcode: MTS
      size: 4
      address: 133508
    - index: 20
      opcode: LWS
      size: 4
      memmode: load
      memtype: stack
      address: 133512
    - index: 21
      opcode: NOP
      size: 4
      address: 133516
    - index: 22
      opcode: MTS
      size: 4
      address: 133520
    - index: 23
      opcode: NOP
      size: 4
      address: 133524
    - index: 24
      opcode: RET
      size: 4
      branch-type: return
      branch-delay-slots: 3
      address: 133528
    - index: 25
      opcode: NOP
      size: 4
      address: 133532
    - index: 26
      opcode: NOP
      size: 4
      address: 133536
    - index: 27
      opcode: SFREEi
      size: 4
      stack-cache-argument: 8
      address: 133540
    address: 133428
  subfunctions:
  - name: 0
    blocks:
    - 0
- name: 7
  level: machinecode
  mapsto: foo
  arguments:
  - name: "%b"
    index: 0
    registers:
    - r3
  - name: "%val"
    index: 1
    registers:
    - r4
  - name: "%val2"
    index: 2
    registers:
    - r5
  hash: 0
  blocks:
  - name: 0
    mapsto: entry
    predecessors: []
    successors:
    - 4
    - 1
    instructions:
    - index: 0
      opcode: MFS
      size: 4
      address: 133316
    - index: 1
      opcode: MOVrp
      size: 4
      address: 133320
    - index: 2
      opcode: BRND
      size: 4
      branch-type: conditional
      branch-targets:
      - 4
      address: 133324
    address: 133316
  - name: 1
    mapsto: "(null)"
    predecessors:
    - 0
    successors:
    - 2
    instructions:
    - index: 0
      opcode: LIi
      size: 4
      address: 133328
    - index: 1
      opcode: BRNDu
      size: 4
      branch-type: unconditional
      branch-targets:
      - 2
      address: 133332
    address: 133328
  - name: 3
    mapsto: for.inc
    predecessors:
    - 2
    successors:
    - 2
    loops:
    - 2
    instructions:
    - index: 0
      opcode: MUL
      size: 4
      address: 133336
    - index: 1
      opcode: NOP
      size: 4
      address: 133340
    - index: 2
      opcode: MFS
      size: 4
      address: 133344
    address: 133336
  - name: 2
    mapsto: for.cond
    predecessors:
    - 3
    - 1
    successors:
    - 7
    - 3
    loops:
    - 2
    instructions:
    - index: 0
      opcode: SUBi
      size: 4
      address: 133348
    - index: 1
      opcode: CMPIEQ
      size: 4
      address: 133352
    - index: 2
      opcode: BRND
      size: 4
      branch-type: conditional
      branch-targets:
      - 3
      address: 133356
    - index: 3
      opcode: BRNDu
      size: 4
      branch-type: unconditional
      branch-targets:
      - 7
      address: 133360
    address: 133348
  - name: 4
    mapsto: for.cond1.preheader
    predecessors:
    - 0
    successors:
    - 5
    instructions:
    - index: 0
      opcode: LIi
      size: 4
      address: 133364
    - index: 1
      opcode: MUL
      size: 4
      address: 133368
    - index: 2
      opcode: LIi
      size: 4
      address: 133372
    - index: 3
      opcode: MFS
      size: 4
      address: 133376
    address: 133364
  - name: 5
    mapsto: for.cond1
    predecessors:
    - 4
    - 5
    successors:
    - 6
    - 5
    loops:
    - 5
    instructions:
    - index: 0
      opcode: SUBi
      size: 4
      address: 133380
    - index: 1
      opcode: MOVrp
      size: 4
      address: 133384
    - index: 2
      opcode: BRND
      size: 4
      branch-type: conditional
      branch-targets:
      - 5
      address: 133388
    address: 133380
  - name: 6
    mapsto: if.end.loopexit
    predecessors:
    - 5
    successors:
    - 7
    instructions:
    - index: 0
      opcode: ADDr
      size: 4
      address: 133392
    address: 133392
  - name: 7
    mapsto: if.end
    predecessors:
    - 6
    - 2
    successors: []
    instructions:
    - index: 0
      opcode: RET
      size: 4
      branch-type: return
      branch-delay-slots: 3
      address: 133396
    - index: 1
      opcode: NOP
      size: 4
      address: 133400
    - index: 2
      opcode: MOV
      size: 4
      address: 133404
    - index: 3
      opcode: MTS
      size: 4
      address: 133408
    address: 133396
  subfunctions:
  - name: 0
    blocks:
    - 0
    - 1
    - 3
    - 2
    - 4
    - 5
    - 6
    - 7
bitcode-functions:
- name: main
  level: bitcode
  hash: 0
  blocks:
  - name: entry
    predecessors: []
    successors: []
    instructions:
    - index: 0
      opcode: load
      memmode: load
    - index: 1
      opcode: load
      memmode: load
    - index: 2
      opcode: load
      memmode: load
    - index: 3
      opcode: add
    - index: 4
      opcode: load
      memmode: load
    - index: 5
      opcode: sdiv
    - index: 6
      opcode: call
      callees:
      - foo
    - index: 7
      opcode: ret
- name: foo
  level: bitcode
  hash: 0
  blocks:
  - name: entry
    predecessors: []
    successors:
    - for.cond1.preheader
    - for.cond
    instructions:
    - index: 0
      opcode: icmp
    - index: 1
      opcode: br
  - name: for.cond1.preheader
    predecessors:
    - entry
    successors:
    - for.cond1
    instructions:
    - index: 0
      opcode: mul
    - index: 1
      opcode: br
  - name: for.cond
    predecessors:
    - entry
    - for.inc
    successors:
    - if.end
    - for.inc
    loops:
    - for.cond
    instructions:
    - index: 0
      opcode: phi
    - index: 1
      opcode: phi
    - index: 2
      opcode: call
    - index: 3
      opcode: add
    - index: 4
      opcode: icmp
    - index: 5
      opcode: br
  - name: for.inc
    predecessors:
    - for.cond
    successors:
    - for.cond
    loops:
    - for.cond
    instructions:
    - index: 0
      opcode: mul
    - index: 1
      opcode: br
  - name: for.cond1
    predecessors:
    - for.cond1
    - for.cond1.preheader
    successors:
    - if.end.loopexit
    - for.cond1
    loops:
    - for.cond1
    instructions:
    - index: 0
      opcode: phi
    - index: 1
      opcode: call
    - index: 2
      opcode: add
    - index: 3
      opcode: icmp
    - index: 4
      opcode: br
  - name: if.end.loopexit
    predecessors:
    - for.cond1
    successors:
    - if.end
    instructions:
    - index: 0
      opcode: add
    - index: 1
      opcode: br
  - name: if.end
    predecessors:
    - for.cond
    - if.end.loopexit
    successors: []
    instructions:
    - index: 0
      opcode: phi
    - index: 1
      opcode: ret
flowfacts:
- scope:
    function: foo
    loop: for.cond
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond
  op: less-equal
  rhs: 52
  level: bitcode
  origin: llvm.bc
  classification: loop-global
- scope:
    function: foo
    loop: for.cond
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond
  op: less-equal
  rhs: 52
  level: bitcode
  origin: llvm.bc
  classification: loop-global
- scope:
    function: foo
    loop: for.cond
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond
  op: less-equal
  rhs: 74
  level: bitcode
  origin: user.bc
  classification: loop-global
- scope:
    function: foo
    loop: for.cond1
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond1
  op: less-equal
  rhs: 74
  level: bitcode
  origin: llvm.bc
  classification: loop-global
- scope:
    function: foo
    loop: for.cond1
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond1
  op: less-equal
  rhs: 74
  level: bitcode
  origin: llvm.bc
  classification: loop-global
- scope:
    function: foo
    loop: for.cond1
  lhs:
  - factor: 1
    program-point:
      function: foo
      block: for.cond1
  op: less-equal
  rhs: 74
  level: bitcode
  origin: user.bc
  classification: loop-global
- scope:
    function: 7
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 3
  - factor: -51
    program-point:
      function: 7
      block: 7
  - factor: 51
    program-point:
      function: 7
      block: 6
  op: less-equal
  rhs: '0'
  origin: llvm
  level: machinecode
- scope:
    function: 7
  lhs:
  - factor: -74
    program-point:
      function: 7
      block: 6
  - factor: 1
    program-point:
      function: 7
      block: 5
  op: less-equal
  rhs: '0'
  origin: llvm
  level: machinecode
- scope:
    function: 7
    loop: 2
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 2
  op: less-equal
  rhs: '52'
  origin: llvm
  level: machinecode
- scope:
    function: 7
    loop: 2
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 2
  op: less-equal
  rhs: '52'
  origin: llvm
  level: machinecode
- scope:
    function: 7
    loop: 5
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 5
  op: less-equal
  rhs: '74'
  origin: llvm
  level: machinecode
- scope:
    function: 7
    loop: 5
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 5
  op: less-equal
  rhs: '74'
  origin: llvm
  level: machinecode
- scope:
    function: 7
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 3
  - factor: -73
    program-point:
      function: 7
      block: 7
  - factor: 73
    program-point:
      function: 7
      block: 6
  op: less-equal
  rhs: '0'
  origin: user
  level: machinecode
- scope:
    function: 7
  lhs:
  - factor: -74
    program-point:
      function: 7
      block: 6
  - factor: 1
    program-point:
      function: 7
      block: 5
  op: less-equal
  rhs: '0'
  origin: user
  level: machinecode
- scope:
    function: 7
    loop: 2
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 2
  op: less-equal
  rhs: '74'
  origin: user
  level: machinecode
- scope:
    function: 7
    loop: 5
  lhs:
  - factor: 1
    program-point:
      function: 7
      block: 5
  op: less-equal
  rhs: '74'
  origin: user
  level: machinecode
relation-graphs:
- src:
    function: main
    level: bitcode
  dst:
    function: 8
    level: machinecode
  nodes:
  - name: 0
    type: entry
    src-block: entry
    dst-block: 0
    src-successors:
    - 1
    dst-successors:
    - 1
  - name: 1
    type: exit
  status: valid
- src:
    function: foo
    level: bitcode
  dst:
    function: 7
    level: machinecode
  nodes:
  - name: 0
    type: entry
    src-block: entry
    dst-block: 0
    src-successors:
    - 3
    - 4
    dst-successors:
    - 2
    - 4
  - name: 1
    type: exit
  - name: 2
    type: dst
    dst-block: 1
    dst-successors:
    - 3
  - name: 3
    type: progress
    src-block: for.cond
    dst-block: 2
    src-successors:
    - 8
    - 7
    dst-successors:
    - 8
    - 7
  - name: 4
    type: progress
    src-block: for.cond1.preheader
    dst-block: 4
    src-successors:
    - 5
    dst-successors:
    - 5
  - name: 5
    type: progress
    src-block: for.cond1
    dst-block: 5
    src-successors:
    - 5
    - 6
    dst-successors:
    - 5
    - 6
  - name: 6
    type: progress
    src-block: if.end.loopexit
    dst-block: 6
    src-successors:
    - 7
    dst-successors:
    - 7
  - name: 7
    type: progress
    src-block: if.end
    dst-block: 7
    src-successors:
    - 1
    dst-successors:
    - 1
  - name: 8
    type: progress
    src-block: for.inc
    dst-block: 3
    src-successors:
    - 3
    dst-successors:
    - 3
  status: valid
timing:
- scope:
    function: 7
  cycles: 425
  level: machinecode
  origin: platin
  cache-max-cycles-instr: 0
  cache-min-hits-instr: 0
  cache-max-misses-instr: 0
  cache-max-cycles-stack: 0
  cache-max-misses-stack: 0
  cache-max-cycles-data: 0
  cache-min-hits-data: 0
  cache-max-misses-data: 0
  cache-max-cycles: 0
  profile:
  - reference:
      function: 7
      edgesource: 0
      edgetarget: 1
    cycles: 3
    wcet-frequency: 1
    wcet-contribution: 3
  - reference:
      function: 7
      edgesource: 1
      edgetarget: 2
    cycles: 4
    wcet-frequency: 1
    wcet-contribution: 4
  - reference:
      function: 7
      edgesource: 3
      edgetarget: 2
    cycles: 3
    wcet-frequency: 51
    wcet-contribution: 153
  - reference:
      function: 7
      edgesource: 2
      edgetarget: 7
    cycles: 6
    wcet-frequency: 1
    wcet-contribution: 6
  - reference:
      function: 7
      edgesource: 2
      edgetarget: 3
    cycles: 5
    wcet-frequency: 51
    wcet-contribution: 255
  - reference:
      function: 7
      edgesource: 7
    cycles: 4
    wcet-frequency: 1
    wcet-contribution: 4
