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
        successors:      [ 2 ]
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
            opcode:          MOV
            size:            4
          - index:           4
            opcode:          MFS
            size:            4
          - index:           5
            opcode:          SWS
            size:            4
            memmode:         store
            memtype:         stack
          - index:           6
            opcode:          MFS
            size:            4
          - index:           7
            opcode:          SWS
            size:            4
            memmode:         store
            memtype:         stack
          - index:           8
            opcode:          LIi
            size:            4
          - index:           9
            opcode:          SUBi
            size:            4
          - index:           10
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 2 ]
          - index:           11
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           12
            opcode:          LIi
            size:            4
      - name:            1
        mapsto:          for.body.i.i
        predecessors:    [ 2 ]
        successors:      [ 2 ]
        loops:           [ 2 ]
        instructions:    
          - index:           0
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           1
            opcode:          SHADD2l
            size:            8
          - index:           2
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           3
            opcode:          ADDi
            size:            4
      - name:            2
        mapsto:          for.cond.i.i
        predecessors:    [ 0, 1 ]
        successors:      [ 3, 1 ]
        loops:           [ 2 ]
        instructions:    
          - index:           0
            opcode:          CMPEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 1 ]
      - name:            3
        mapsto:          '(null)'
        predecessors:    [ 2 ]
        successors:      [ 5 ]
        instructions:    
          - index:           0
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 5 ]
          - index:           1
            opcode:          LIi
            size:            4
          - index:           2
            opcode:          MOV
            size:            4
      - name:            4
        mapsto:          for.body2.i.i
        predecessors:    [ 5 ]
        successors:      [ 5 ]
        loops:           [ 5 ]
        instructions:    
          - index:           0
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           1
            opcode:          SHADD2l
            size:            8
          - index:           2
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           3
            opcode:          ADDi
            size:            4
      - name:            5
        mapsto:          for.cond1.i.i
        predecessors:    [ 4, 3 ]
        successors:      [ 6, 4 ]
        loops:           [ 5 ]
        instructions:    
          - index:           0
            opcode:          CMPEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 4 ]
      - name:            6
        mapsto:          '(null)'
        predecessors:    [ 5 ]
        successors:      [ 7 ]
        instructions:    
          - index:           0
            opcode:          BRCFu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 3
            branch-targets:  [ 7 ]
          - index:           1
            opcode:          LIi
            size:            4
          - index:           2
            opcode:          MOV
            size:            4
          - index:           3
            opcode:          NOP
            size:            4
      - name:            7
        mapsto:          for.cond5.i.i
        predecessors:    [ 8, 6 ]
        successors:      [ 9, 8 ]
        loops:           [ 7 ]
        instructions:    
          - index:           0
            opcode:          CMPEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 8 ]
          - index:           2
            opcode:          BRCFNDu
            size:            4
            branch-type:     unconditional
            branch-targets:  [ 9 ]
      - name:            8
        mapsto:          for.body6.i.i
        predecessors:    [ 7 ]
        successors:      [ 7 ]
        loops:           [ 7 ]
        instructions:    
          - index:           0
            opcode:          SHADD2l
            size:            8
          - index:           1
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 7 ]
          - index:           2
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           3
            opcode:          ADDi
            size:            4
      - name:            9
        mapsto:          matrix1_init.exit
        predecessors:    [ 7 ]
        successors:      [ 10 ]
        instructions:    
          - index:           0
            opcode:          CALLND
            callees:         [ matrix1_main ]
            size:            4
            branch-type:     call
          - index:           1
            opcode:          MOV
            size:            4
          - index:           2
            opcode:          BRCFu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 3
            branch-targets:  [ 10 ]
          - index:           3
            opcode:          LIi
            size:            4
          - index:           4
            opcode:          MOV
            size:            4
          - index:           5
            opcode:          SENSi
            size:            4
            stack-cache-argument: 8
      - name:            10
        mapsto:          for.cond.i
        predecessors:    [ 9, 11 ]
        successors:      [ 12, 11 ]
        loops:           [ 10 ]
        instructions:    
          - index:           0
            opcode:          CMPEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 11 ]
          - index:           2
            opcode:          BRNDu
            size:            4
            branch-type:     unconditional
            branch-targets:  [ 12 ]
      - name:            11
        mapsto:          for.inc.i
        predecessors:    [ 10 ]
        successors:      [ 10 ]
        loops:           [ 10 ]
        instructions:    
          - index:           0
            opcode:          SHADD2l
            size:            8
          - index:           1
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           2
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 10 ]
          - index:           3
            opcode:          ADDi
            size:            4
          - index:           4
            opcode:          ADDr
            size:            4
      - name:            12
        mapsto:          matrix1_return.exit
        predecessors:    [ 10 ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          LIi
            size:            4
          - index:           1
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           2
            opcode:          CMPNEQ
            size:            4
          - index:           3
            opcode:          MTS
            size:            4
          - index:           4
            opcode:          LIi
            size:            4
          - index:           5
            opcode:          LIin
            size:            4
          - index:           6
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           7
            opcode:          CMOV
            size:            4
          - index:           8
            opcode:          MTS
            size:            4
          - index:           9
            opcode:          LWS
            size:            4
            memmode:         load
            memtype:         stack
          - index:           10
            opcode:          RET
            size:            4
            branch-type:     return
            branch-delay-slots: 3
          - index:           11
            opcode:          ADDi
            size:            4
          - index:           12
            opcode:          MTS
            size:            4
          - index:           13
            opcode:          SFREEi
            size:            4
            stack-cache-argument: 8
    subfunctions:    
      - name:            0
        blocks:          [ 0, 1, 2, 3, 4, 5, 6 ]
      - name:            7
        blocks:          [ 7, 8 ]
      - name:            9
        blocks:          [ 9 ]
      - name:            10
        blocks:          [ 10, 11, 12 ]
  - name:            7
    level:           machinecode
    mapsto:          matrix1_main
    hash:            0
    blocks:          
      - name:            0
        mapsto:          entry
        predecessors:    [  ]
        successors:      [ 1 ]
        instructions:    
          - index:           0
            opcode:          LIin
            size:            4
          - index:           1
            opcode:          LIl
            size:            8
          - index:           2
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 1 ]
          - index:           3
            opcode:          MOV
            size:            4
          - index:           4
            opcode:          MFS
            size:            4
      - name:            8
        mapsto:          for.inc7
        predecessors:    [ 3 ]
        successors:      [ 1 ]
        loops:           [ 1 ]
        instructions:    
          - index:           0
            opcode:          ADDi
            size:            4
          - index:           1
            opcode:          ADDi
            size:            4
      - name:            1
        mapsto:          for.cond
        predecessors:    [ 0, 8 ]
        successors:      [ 9, 2 ]
        loops:           [ 1 ]
        instructions:    
          - index:           0
            opcode:          CMPIEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 9 ]
      - name:            2
        mapsto:          for.cond1.preheader
        predecessors:    [ 1 ]
        successors:      [ 3 ]
        loops:           [ 1 ]
        instructions:    
          - index:           0
            opcode:          SHADD2r
            size:            4
          - index:           1
            opcode:          SLi
            size:            4
          - index:           2
            opcode:          SHADD2l
            size:            8
          - index:           3
            opcode:          LIl
            size:            8
          - index:           4
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 3 ]
          - index:           5
            opcode:          MOV
            size:            4
          - index:           6
            opcode:          MOV
            size:            4
      - name:            7
        mapsto:          for.inc5
        predecessors:    [ 5 ]
        successors:      [ 3 ]
        loops:           [ 3, 1 ]
        instructions:    
          - index:           0
            opcode:          ADDi
            size:            4
          - index:           1
            opcode:          ADDi
            size:            4
          - index:           2
            opcode:          ADDi
            size:            4
      - name:            3
        mapsto:          for.cond1
        predecessors:    [ 2, 7 ]
        successors:      [ 8, 4 ]
        loops:           [ 3, 1 ]
        instructions:    
          - index:           0
            opcode:          CMPIEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 8 ]
      - name:            4
        mapsto:          for.body2
        predecessors:    [ 3 ]
        successors:      [ 5 ]
        loops:           [ 3, 1 ]
        instructions:    
          - index:           0
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           1
            opcode:          BRu
            size:            4
            branch-type:     unconditional
            branch-delay-slots: 2
            branch-targets:  [ 5 ]
          - index:           2
            opcode:          MOV
            size:            4
          - index:           3
            opcode:          MOV
            size:            4
      - name:            6
        mapsto:          for.body4
        predecessors:    [ 5 ]
        successors:      [ 5 ]
        loops:           [ 5, 3, 1 ]
        instructions:    
          - index:           0
            opcode:          NEG
            size:            4
          - index:           1
            opcode:          SHADD2r
            size:            4
          - index:           2
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           3
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           4
            opcode:          SUBi
            size:            4
          - index:           5
            opcode:          MUL
            size:            4
          - index:           6
            opcode:          LWC
            size:            4
            memmode:         load
            memtype:         cache
          - index:           7
            opcode:          MFS
            size:            4
          - index:           8
            opcode:          ADDr
            size:            4
          - index:           9
            opcode:          SWC
            size:            4
            memmode:         store
            memtype:         cache
          - index:           10
            opcode:          ADDi
            size:            4
      - name:            5
        mapsto:          for.cond3
        predecessors:    [ 4, 6 ]
        successors:      [ 7, 6 ]
        loops:           [ 5, 3, 1 ]
        instructions:    
          - index:           0
            opcode:          CMPEQ
            size:            4
          - index:           1
            opcode:          BRND
            size:            4
            branch-type:     conditional
            branch-targets:  [ 6 ]
          - index:           2
            opcode:          BRNDu
            size:            4
            branch-type:     unconditional
            branch-targets:  [ 7 ]
      - name:            9
        mapsto:          for.end8
        predecessors:    [ 1 ]
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
        blocks:          [ 0, 8, 1, 2, 7, 3, 4, 6, 5, 9 ]
valuefacts:      
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-write
    values:          
      - symbol:          matrix1_A
    program-point:   
      function:        8
      block:           1
      instruction:     2
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-write
    values:          
      - symbol:          matrix1_B
    program-point:   
      function:        8
      block:           4
      instruction:     2
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-write
    values:          
      - symbol:          matrix1_C
    program-point:   
      function:        8
      block:           8
      instruction:     2
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-read
    values:          
      - symbol:          matrix1_C
    program-point:   
      function:        8
      block:           11
      instruction:     1
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-write
    values:          
      - symbol:          matrix1_C
    program-point:   
      function:        7
      block:           4
      instruction:     0
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-read
    values:          
      - symbol:          matrix1_B
    program-point:   
      function:        7
      block:           6
      instruction:     2
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-read
    values:          
      - symbol:          matrix1_C
    program-point:   
      function:        7
      block:           6
      instruction:     6
  - level:           machinecode
    origin:          llvm.mc
    variable:        mem-address-write
    values:          
      - symbol:          matrix1_C
    program-point:   
      function:        7
      block:           6
      instruction:     9
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
        successors:      [ for.cond.i.i ]
        instructions:    
          - index:           0
            opcode:          alloca
          - index:           1
            opcode:          bitcast
          - index:           2
            opcode:          call
          - index:           3
            opcode:          store
            memmode:         store
          - index:           4
            opcode:          br
      - name:            for.cond.i.i
        predecessors:    [ for.body.i.i, entry ]
        successors:      [ for.cond1.i.i, for.body.i.i ]
        loops:           [ for.cond.i.i ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          call
          - index:           2
            opcode:          icmp
          - index:           3
            opcode:          br
      - name:            for.body.i.i
        predecessors:    [ for.cond.i.i ]
        successors:      [ for.cond.i.i ]
        loops:           [ for.cond.i.i ]
        instructions:    
          - index:           0
            opcode:          load
            memmode:         load
          - index:           1
            opcode:          getelementptr
          - index:           2
            opcode:          store
            memmode:         store
          - index:           3
            opcode:          add
          - index:           4
            opcode:          br
      - name:            for.cond1.i.i
        predecessors:    [ for.cond.i.i, for.body2.i.i ]
        successors:      [ for.cond5.i.i, for.body2.i.i ]
        loops:           [ for.cond1.i.i ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          call
          - index:           2
            opcode:          icmp
          - index:           3
            opcode:          br
      - name:            for.body2.i.i
        predecessors:    [ for.cond1.i.i ]
        successors:      [ for.cond1.i.i ]
        loops:           [ for.cond1.i.i ]
        instructions:    
          - index:           0
            opcode:          load
            memmode:         load
          - index:           1
            opcode:          getelementptr
          - index:           2
            opcode:          store
            memmode:         store
          - index:           3
            opcode:          add
          - index:           4
            opcode:          br
      - name:            for.cond5.i.i
        predecessors:    [ for.cond1.i.i, for.body6.i.i ]
        successors:      [ matrix1_init.exit, for.body6.i.i ]
        loops:           [ for.cond5.i.i ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          call
          - index:           2
            opcode:          icmp
          - index:           3
            opcode:          br
      - name:            for.body6.i.i
        predecessors:    [ for.cond5.i.i ]
        successors:      [ for.cond5.i.i ]
        loops:           [ for.cond5.i.i ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          store
            memmode:         store
          - index:           2
            opcode:          add
          - index:           3
            opcode:          br
      - name:            matrix1_init.exit
        predecessors:    [ for.cond5.i.i ]
        successors:      [ for.cond.i ]
        instructions:    
          - index:           0
            opcode:          bitcast
          - index:           1
            opcode:          call
          - index:           2
            opcode:          call
            callees:         [ matrix1_main ]
          - index:           3
            opcode:          br
      - name:            for.cond.i
        predecessors:    [ for.inc.i, matrix1_init.exit ]
        successors:      [ matrix1_return.exit, for.inc.i ]
        loops:           [ for.cond.i ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          phi
          - index:           2
            opcode:          call
          - index:           3
            opcode:          icmp
          - index:           4
            opcode:          br
      - name:            for.inc.i
        predecessors:    [ for.cond.i ]
        successors:      [ for.cond.i ]
        loops:           [ for.cond.i ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          load
            memmode:         load
          - index:           2
            opcode:          add
          - index:           3
            opcode:          add
          - index:           4
            opcode:          br
      - name:            matrix1_return.exit
        predecessors:    [ for.cond.i ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          icmp
          - index:           1
            opcode:          sext
          - index:           2
            opcode:          ret
  - name:            matrix1_main
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
        predecessors:    [ for.inc7, entry ]
        successors:      [ for.end8, for.cond1.preheader ]
        loops:           [ for.cond ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          phi
          - index:           2
            opcode:          call
          - index:           3
            opcode:          icmp
          - index:           4
            opcode:          br
      - name:            for.cond1.preheader
        predecessors:    [ for.cond ]
        successors:      [ for.cond1 ]
        loops:           [ for.cond ]
        instructions:    
          - index:           0
            opcode:          mul
          - index:           1
            opcode:          getelementptr
          - index:           2
            opcode:          br
      - name:            for.cond1
        predecessors:    [ for.inc5, for.cond1.preheader ]
        successors:      [ for.inc7, for.body2 ]
        loops:           [ for.cond1, for.cond ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          phi
          - index:           2
            opcode:          phi
          - index:           3
            opcode:          call
          - index:           4
            opcode:          icmp
          - index:           5
            opcode:          br
      - name:            for.body2
        predecessors:    [ for.cond1 ]
        successors:      [ for.cond3 ]
        loops:           [ for.cond1, for.cond ]
        instructions:    
          - index:           0
            opcode:          store
            memmode:         store
          - index:           1
            opcode:          br
      - name:            for.cond3
        predecessors:    [ for.body4, for.body2 ]
        successors:      [ for.inc5, for.body4 ]
        loops:           [ for.cond3, for.cond1, for.cond ]
        instructions:    
          - index:           0
            opcode:          phi
          - index:           1
            opcode:          phi
          - index:           2
            opcode:          mul
          - index:           3
            opcode:          call
          - index:           4
            opcode:          icmp
          - index:           5
            opcode:          br
      - name:            for.body4
        predecessors:    [ for.cond3 ]
        successors:      [ for.cond3 ]
        loops:           [ for.cond3, for.cond1, for.cond ]
        instructions:    
          - index:           0
            opcode:          ptrtoint
          - index:           1
            opcode:          mul
          - index:           2
            opcode:          add
          - index:           3
            opcode:          inttoptr
          - index:           4
            opcode:          load
            memmode:         load
          - index:           5
            opcode:          load
            memmode:         load
          - index:           6
            opcode:          mul
          - index:           7
            opcode:          load
            memmode:         load
          - index:           8
            opcode:          add
          - index:           9
            opcode:          store
            memmode:         store
          - index:           10
            opcode:          getelementptr
          - index:           11
            opcode:          add
          - index:           12
            opcode:          br
      - name:            for.inc5
        predecessors:    [ for.cond3 ]
        successors:      [ for.cond1 ]
        loops:           [ for.cond1, for.cond ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          getelementptr
          - index:           2
            opcode:          add
          - index:           3
            opcode:          br
      - name:            for.inc7
        predecessors:    [ for.cond1 ]
        successors:      [ for.cond ]
        loops:           [ for.cond ]
        instructions:    
          - index:           0
            opcode:          getelementptr
          - index:           1
            opcode:          add
          - index:           2
            opcode:          br
      - name:            for.end8
        predecessors:    [ for.cond ]
        successors:      [  ]
        instructions:    
          - index:           0
            opcode:          ret
flowfacts:       
  - scope:           
      function:        main
      loop:            for.cond.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond1.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond1.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond1.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond1.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond1.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond1.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond5.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond5.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond5.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond5.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond5.i.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond5.i.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i
    op:              less-equal
    rhs:             102
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i
    op:              less-equal
    rhs:             102
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        main
      loop:            for.cond.i
    lhs:             
      - factor:          1
        program-point:   
          function:        main
          block:           for.cond.i
    op:              less-equal
    rhs:             101
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond1
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond1
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          user.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond3
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond3
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond3
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond3
    op:              less-equal
    rhs:             11
    level:           bitcode
    origin:          llvm.bc
    classification:  loop-global
  - scope:           
      function:        matrix1_main
      loop:            for.cond3
    lhs:             
      - factor:          1
        program-point:   
          function:        matrix1_main
          block:           for.cond3
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
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
      - name:            1
        type:            exit
      - name:            2
        type:            progress
        src-block:       for.cond.i.i
        dst-block:       2
        src-successors:  [ 4, 5 ]
        dst-successors:  [ 3, 4 ]
      - name:            3
        type:            dst
        dst-block:       3
        dst-successors:  [ 5 ]
      - name:            4
        type:            progress
        src-block:       for.body.i.i
        dst-block:       1
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
      - name:            5
        type:            progress
        src-block:       for.cond1.i.i
        dst-block:       5
        src-successors:  [ 7, 8 ]
        dst-successors:  [ 6, 7 ]
      - name:            6
        type:            dst
        dst-block:       6
        dst-successors:  [ 8 ]
      - name:            7
        type:            progress
        src-block:       for.body2.i.i
        dst-block:       4
        src-successors:  [ 5 ]
        dst-successors:  [ 5 ]
      - name:            8
        type:            progress
        src-block:       for.cond5.i.i
        dst-block:       7
        src-successors:  [ 9, 10 ]
        dst-successors:  [ 9, 10 ]
      - name:            9
        type:            progress
        src-block:       for.body6.i.i
        dst-block:       8
        src-successors:  [ 8 ]
        dst-successors:  [ 8 ]
      - name:            10
        type:            progress
        src-block:       matrix1_init.exit
        dst-block:       9
        src-successors:  [ 11 ]
        dst-successors:  [ 11 ]
      - name:            11
        type:            progress
        src-block:       for.cond.i
        dst-block:       10
        src-successors:  [ 12, 13 ]
        dst-successors:  [ 12, 13 ]
      - name:            12
        type:            progress
        src-block:       for.inc.i
        dst-block:       11
        src-successors:  [ 11 ]
        dst-successors:  [ 11 ]
      - name:            13
        type:            progress
        src-block:       matrix1_return.exit
        dst-block:       12
        src-successors:  [ 1 ]
        dst-successors:  [ 1 ]
    status:          valid
  - src:             
      function:        matrix1_main
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
        src-successors:  [ 3, 4 ]
        dst-successors:  [ 3, 4 ]
      - name:            3
        type:            progress
        src-block:       for.cond1.preheader
        dst-block:       2
        src-successors:  [ 5 ]
        dst-successors:  [ 5 ]
      - name:            4
        type:            progress
        src-block:       for.end8
        dst-block:       9
        src-successors:  [ 1 ]
        dst-successors:  [ 1 ]
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
        src-successors:  [ 8 ]
        dst-successors:  [ 8 ]
      - name:            7
        type:            progress
        src-block:       for.inc7
        dst-block:       8
        src-successors:  [ 2 ]
        dst-successors:  [ 2 ]
      - name:            8
        type:            progress
        src-block:       for.cond3
        dst-block:       5
        src-successors:  [ 9, 10 ]
        dst-successors:  [ 9, 10 ]
      - name:            9
        type:            progress
        src-block:       for.body4
        dst-block:       6
        src-successors:  [ 8 ]
        dst-successors:  [ 8 ]
      - name:            10
        type:            progress
        src-block:       for.inc5
        dst-block:       7
        src-successors:  [ 5 ]
        dst-successors:  [ 5 ]
    status:          valid
...
