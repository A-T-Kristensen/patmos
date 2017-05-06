---
format:          pml-0.1
triple:          patmos-unknown-unknown-elf
machine-functions: 
  - name:            8
    level:           machinecode
    mapsto:          main
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
            opcode:          CALL
            callees:         [ bram_main ]
            size:            4
            branch-type:     call
            branch-delay-slots: 3
          - index:           5
            opcode:          NOP
            size:            4
          - index:           6
            opcode:          NOP
            size:            4
          - index:           7
            opcode:          SWS
            size:            4
            memmode:         store
            memtype:         stack
          - index:           8
            opcode:          SENSi
            size:            4
            stack-cache-argument: 8
          - index:           9
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           10
            opcode:          NOP
            size:            4
          - index:           11
            opcode:          MTS
            size:            4
          - index:           12
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           13
            opcode:          NOP
            size:            4
          - index:           14
            opcode:          MTS
            size:            4
          - index:           15
            opcode:          NOP
            size:            4
          - index:           16
            opcode:          RET
            size:            4
            branch-type:     return
            branch-delay-slots: 3
          - index:           17
            opcode:          NOP
            size:            4
          - index:           18
            opcode:          MOV
            size:            4
          - index:           19
            opcode:          SFREEi
            size:            4
            stack-cache-argument: 8
    subfunctions:    
      - name:            0
        blocks:          [ 0 ]
  - name:            7
    level:           machinecode
    mapsto:          bram_main
    hash:            0
    blocks:          
      - name:            0
        mapsto:          entry
        predecessors:    [  ]
        successors:      [ 1 ]
        instructions:    
          - index:           0
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 1 ]
          - index:           1
            opcode:          LIi
            size:            4
          - index:           2
            opcode:          MFS
            size:            4
      - name:            6
        mapsto:          for.body
        predecessors:    [ 1 ]
        successors:      [ 1 ]
        loops:           [ 1 ]
        instructions:    
          - index:           0
            opcode:          SHADD2l
            size:            8
          - index:           1
            opcode:          SWL
            size:            4
            memmode:         store
            memtype:         local
          - index:           2
            opcode:          ADDi
            size:            4
      - name:            1
        mapsto:          for.cond
        predecessors:    [ 0, 6 ]
        successors:      [ 2, 6 ]
        loops:           [ 1 ]
        instructions:    
          - index:           0
            opcode:          CMPIEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 6 ]
      - name:            2
        mapsto:          '(null)'
        predecessors:    [ 1 ]
        successors:      [ 3 ]
        instructions:    
          - index:           0
            opcode:          MOV
            size:            4
          - index:           1
            opcode:          BRNDu
            size:            4
            branch-type:     unconditional
            branch-targets:  [ 3 ]
      - name:            4
        mapsto:          for.body2
        predecessors:    [ 3 ]
        successors:      [ 3 ]
        loops:           [ 3 ]
        instructions:    
          - index:           0
            opcode:          SHADD2l
            size:            8
          - index:           1
            opcode:          LWL
            size:            4
            memmode:         load
            memtype:         local
          - index:           2
            opcode:          ADDi
            size:            4
      - name:            3
        mapsto:          for.cond1
        predecessors:    [ 4, 2 ]
        successors:      [ 5, 4 ]
        loops:           [ 3 ]
        instructions:    
          - index:           0
            opcode:          CMPIEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 4 ]
      - name:            5
        mapsto:          for.end4
        predecessors:    [ 3 ]
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
        blocks:          [ 0, 6, 1, 2, 4, 3, 5 ]
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
            opcode:          call
            callees:         [ bram_main ]
          - index:           1
            opcode:          ret
  - name:            bram_main
    level:           bitcode
    hash:            0
    blocks:          
      - name:            entry
        predecessors:    [  ]
        successors:      [ for.cond ]
        instructions:    
          - index:           0
            opcode:          br
      - name:            for.cond
        predecessors:    [ for.body, entry ]
        successors:      [ for.cond1, for.body ]
        loops:           [ for.cond ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          call
          - index:           2
            opcode:          icmp
          - index:           3
            opcode:          br
      - name:            for.body
        predecessors:    [ for.cond ]
        successors:      [ for.cond ]
        loops:           [ for.cond ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          getelementptr
          - index:           2
            opcode:          store
            memmode:         store
          - index:           3
            opcode:          add
          - index:           4
            opcode:          br
      - name:            for.cond1
        predecessors:    [ for.cond, for.body2 ]
        successors:      [ for.end4, for.body2 ]
        loops:           [ for.cond1 ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          call
          - index:           2
            opcode:          icmp
          - index:           3
            opcode:          br
      - name:            for.body2
        predecessors:    [ for.cond1 ]
        successors:      [ for.cond1 ]
        loops:           [ for.cond1 ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          load
            memmode:         load
          - index:           2
            opcode:          add
          - index:           3
            opcode:          br
      - name:            for.end4
        predecessors:    [ for.cond1 ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          ret
flowfacts:       
  - scope:           
      function:        bram_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        bram_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        bram_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        bram_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        bram_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        bram_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        bram_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
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
      function:        bram_main
      level:           bitcode
    dst:             
      function:        7
      level:           machinecode
    nodes:           
      - name:            0
        type:            entry
        src-block:       entry
        dst-block:       0
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
      - name:            1
        type:            exit
      - name:            2
        type:            progress
        src-block:       for.cond
        dst-block:       1
        src-successors:  [ 4, 5 ]
        dst-successors:  [ 3, 4 ]
      - name:            3
        type:            dst
        dst-block:       2
        dst-successors:  [ 5 ]
      - name:            4
        type:            progress
        src-block:       for.body
        dst-block:       6
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
      - name:            5
        type:            progress
        src-block:       for.cond1
        dst-block:       3
        src-successors:  [ 6, 7 ]
        dst-successors:  [ 6, 7 ]
      - name:            6
        type:            progress
        src-block:       for.body2
        dst-block:       4
        src-successors:  [ 5 ]
        dst-successors:  [ 5 ]
      - name:            7
        type:            progress
        src-block:       for.end4
        dst-block:       5
        src-successors:  [ 1 ]
        dst-successors:  [ 1 ]
    status:          valid
...
