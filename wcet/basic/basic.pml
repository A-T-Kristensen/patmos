---
format:          pml-0.1
triple:          patmos-unknown-unknown-elf
machine-functions: 
  - name:            8
    level:           machinecode
    mapsto:          main
    arguments:       
      - name:            '%argc'
        index:           0
        registers:       [ r3 ]
    hash:            0
    blocks:          
      - name:            0
        mapsto:          entry
        predecessors:    [  ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          SRESi
            size:            4
            stack-cache-argument: 8
          - index:           1
            opcode:          MFS
            size:            4
          - index:           2
            opcode:          SWS
            size:            4
            memmode:         store
            memtype:         stack
          - index:           3
            opcode:          MFS
            size:            4
          - index:           4
            opcode:          SWS
            size:            4
            memmode:         store
            memtype:         stack
          - index:           5
            opcode:          SUBi
            size:            4
          - index:           6
            opcode:          LIi
            size:            4
          - index:           7
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           8
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           9
            opcode:          NOP
            size:            4
          - index:           10
            opcode:          SRAi
            size:            4
          - index:           11
            opcode:          CALL
            callees:         [ foo ]
            size:            4
            branch-type:     call
            branch-delay-slots: 3
          - index:           12
            opcode:          SRi
            size:            4
          - index:           13
            opcode:          ADDr
            size:            4
          - index:           14
            opcode:          SRAi
            size:            4
          - index:           15
            opcode:          SENSi
            size:            4
            stack-cache-argument: 8
          - index:           16
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           17
            opcode:          NOP
            size:            4
          - index:           18
            opcode:          MTS
            size:            4
          - index:           19
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           20
            opcode:          NOP
            size:            4
          - index:           21
            opcode:          MTS
            size:            4
          - index:           22
            opcode:          NOP
            size:            4
          - index:           23
            opcode:          RET
            size:            4
            branch-type:     return
            branch-delay-slots: 3
          - index:           24
            opcode:          NOP
            size:            4
          - index:           25
            opcode:          ADDi
            size:            4
          - index:           26
            opcode:          SFREEi
            size:            4
            stack-cache-argument: 8
    subfunctions:    
      - name:            0
        blocks:          [ 0 ]
  - name:            7
    level:           machinecode
    mapsto:          foo
    arguments:       
      - name:            '%bar'
        index:           0
        registers:       [ r3 ]
    hash:            0
    blocks:          
      - name:            0
        mapsto:          entry
        predecessors:    [  ]
        successors:      [ 2, 1 ]
        instructions:    
          - index:           0
            opcode:          MFS
            size:            4
          - index:           1
            opcode:          LIi
            size:            4
          - index:           2
            opcode:          CMPIEQ
            size:            4
          - index:           3
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 2 ]
      - name:            1
        mapsto:          if.then
        predecessors:    [ 0 ]
        successors:      [ 2 ]
        instructions:    
          - index:           0
            opcode:          SHADD2r
            size:            4
          - index:           1
            opcode:          LIi
            size:            4
          - index:           2
            opcode:          SLi
            size:            4
          - index:           3
            opcode:          CMPLT
            size:            4
          - index:           4
            opcode:          CMOV
            size:            4
      - name:            2
        mapsto:          if.end2
        predecessors:    [ 0, 1 ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          MTS
            size:            4
          - index:           1
            opcode:          RETND
            size:            4
            branch-type:     return
    subfunctions:    
      - name:            0
        blocks:          [ 0, 1, 2 ]
...
---
format:          pml-0.1
triple:          patmos-unknown-unknown-elf
bitcode-functions: 
  - name:            main
    level:           bitcode
    hash:            0
    blocks:          
      - name:            entry
        predecessors:    [  ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          alloca
          - index:           1
            opcode:          store
            memmode:         store
          - index:           2
            opcode:          load
            memmode:         load
          - index:           3
            opcode:          sdiv
          - index:           4
            opcode:          call
            callees:         [ foo ]
          - index:           5
            opcode:          ret
  - name:            foo
    level:           bitcode
    hash:            0
    blocks:          
      - name:            entry
        predecessors:    [  ]
        successors:      [ if.end2, if.then ]
        instructions:    
          - index:           0
            opcode:          icmp
          - index:           1
            opcode:          br
      - name:            if.then
        predecessors:    [ entry ]
        successors:      [ if.end2 ]
        instructions:    
          - index:           0
            opcode:          mul
          - index:           1
            opcode:          icmp
          - index:           2
            opcode:          select
          - index:           3
            opcode:          br
      - name:            if.end2
        predecessors:    [ if.then, entry ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          ret
...
---
format:          pml-0.1
triple:          patmos-unknown-unknown-elf
relation-graphs: 
  - src:             
      function:        main
      level:           bitcode
    dst:             
      function:        8
      level:           machinecode
    nodes:           
      - name:            0
        type:            entry
        src-block:       entry
        dst-block:       0
        src-successors:  [ 1 ]
        dst-successors:  [ 1 ]
      - name:            1
        type:            exit
    status:          valid
  - src:             
      function:        foo
      level:           bitcode
    dst:             
      function:        7
      level:           machinecode
    nodes:           
      - name:            0
        type:            entry
        src-block:       entry
        dst-block:       0
        src-successors:  [ 2, 3 ]
        dst-successors:  [ 2, 3 ]
      - name:            1
        type:            exit
      - name:            2
        type:            progress
        src-block:       if.end2
        dst-block:       2
        src-successors:  [ 1 ]
        dst-successors:  [ 1 ]
      - name:            3
        type:            progress
        src-block:       if.then
        dst-block:       1
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
    status:          valid
...
