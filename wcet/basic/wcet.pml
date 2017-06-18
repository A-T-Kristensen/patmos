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
      address: 133364
    - index: 1
      opcode: MFS
      size: 4
      address: 133368
    - index: 2
      opcode: SWS
      size: 4
      memmode: store
      memtype: stack
      address: 133372
    - index: 3
      opcode: MFS
      size: 4
      address: 133376
    - index: 4
      opcode: SWS
      size: 4
      memmode: store
      memtype: stack
      address: 133380
    - index: 5
      opcode: SUBi
      size: 4
      address: 133384
    - index: 6
      opcode: LIi
      size: 4
      address: 133388
    - index: 7
      opcode: SWC
      size: 4
      memmode: store
      memtype: cache
      address: 133392
    - index: 8
      opcode: LWC
      size: 4
      memmode: load
      memtype: cache
      address: 133396
    - index: 9
      opcode: NOP
      size: 4
      address: 133400
    - index: 10
      opcode: SRAi
      size: 4
      address: 133404
    - index: 11
      opcode: CALL
      callees:
      - foo
      size: 4
      branch-type: call
      branch-delay-slots: 3
      address: 133408
    - index: 12
      opcode: SRi
      size: 4
      address: 133412
    - index: 13
      opcode: ADDr
      size: 4
      address: 133416
    - index: 14
      opcode: SRAi
      size: 4
      address: 133420
    - index: 15
      opcode: SENSi
      size: 4
      stack-cache-argument: 8
      address: 133424
    - index: 16
      opcode: LWS
      size: 4
      memmode: load
      memtype: stack
      address: 133428
    - index: 17
      opcode: NOP
      size: 4
      address: 133432
    - index: 18
      opcode: MTS
      size: 4
      address: 133436
    - index: 19
      opcode: LWS
      size: 4
      memmode: load
      memtype: stack
      address: 133440
    - index: 20
      opcode: NOP
      size: 4
      address: 133444
    - index: 21
      opcode: MTS
      size: 4
      address: 133448
    - index: 22
      opcode: NOP
      size: 4
      address: 133452
    - index: 23
      opcode: RET
      size: 4
      branch-type: return
      branch-delay-slots: 3
      address: 133456
    - index: 24
      opcode: NOP
      size: 4
      address: 133460
    - index: 25
      opcode: ADDi
      size: 4
      address: 133464
    - index: 26
      opcode: SFREEi
      size: 4
      stack-cache-argument: 8
      address: 133468
    address: 133364
  subfunctions:
  - name: 0
    blocks:
    - 0
- name: 7
  level: machinecode
  mapsto: foo
  arguments:
  - name: "%bar"
    index: 0
    registers:
    - r3
  hash: 0
  blocks:
  - name: 0
    mapsto: entry
    predecessors: []
    successors:
    - 2
    - 1
    instructions:
    - index: 0
      opcode: MFS
      size: 4
      address: 133316
    - index: 1
      opcode: LIi
      size: 4
      address: 133320
    - index: 2
      opcode: CMPIEQ
      size: 4
      address: 133324
    - index: 3
      opcode: BRND
      size: 4
      branch-type: conditional
      branch-targets:
      - 2
      address: 133328
    address: 133316
  - name: 1
    mapsto: if.then
    predecessors:
    - 0
    successors:
    - 2
    instructions:
    - index: 0
      opcode: SHADD2r
      size: 4
      address: 133332
    - index: 1
      opcode: LIi
      size: 4
      address: 133336
    - index: 2
      opcode: SLi
      size: 4
      address: 133340
    - index: 3
      opcode: CMPLT
      size: 4
      address: 133344
    - index: 4
      opcode: CMOV
      size: 4
      address: 133348
    address: 133332
  - name: 2
    mapsto: if.end2
    predecessors:
    - 0
    - 1
    successors: []
    instructions:
    - index: 0
      opcode: MTS
      size: 4
      address: 133352
    - index: 1
      opcode: RETND
      size: 4
      branch-type: return
      address: 133356
    address: 133352
  subfunctions:
  - name: 0
    blocks:
    - 0
    - 1
    - 2
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
      opcode: alloca
    - index: 1
      opcode: store
      memmode: store
    - index: 2
      opcode: load
      memmode: load
    - index: 3
      opcode: sdiv
    - index: 4
      opcode: call
      callees:
      - foo
    - index: 5
      opcode: ret
- name: foo
  level: bitcode
  hash: 0
  blocks:
  - name: entry
    predecessors: []
    successors:
    - if.end2
    - if.then
    instructions:
    - index: 0
      opcode: icmp
    - index: 1
      opcode: br
  - name: if.then
    predecessors:
    - entry
    successors:
    - if.end2
    instructions:
    - index: 0
      opcode: mul
    - index: 1
      opcode: icmp
    - index: 2
      opcode: select
    - index: 3
      opcode: br
  - name: if.end2
    predecessors:
    - if.then
    - entry
    successors: []
    instructions:
    - index: 0
      opcode: phi
    - index: 1
      opcode: ret
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
    - 2
    - 3
    dst-successors:
    - 2
    - 3
  - name: 1
    type: exit
  - name: 2
    type: progress
    src-block: if.end2
    dst-block: 2
    src-successors:
    - 1
    dst-successors:
    - 1
  - name: 3
    type: progress
    src-block: if.then
    dst-block: 1
    src-successors:
    - 2
    dst-successors:
    - 2
  status: valid
timing:
- scope:
    function: 7
  cycles: 14
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
    cycles: 4
    wcet-frequency: 1
    wcet-contribution: 4
  - reference:
      function: 7
      edgesource: 1
      edgetarget: 2
    cycles: 5
    wcet-frequency: 1
    wcet-contribution: 5
  - reference:
      function: 7
      edgesource: 2
    cycles: 5
    wcet-frequency: 1
    wcet-contribution: 5
