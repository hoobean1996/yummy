# cpu arch
`LLVM Machine Code Analyzer`

## how to make the best use of the CPU resource using a single thread.
  [Just Works]
    - Execution Units
    - Out-of-Order Scheduling, Retirement
    - Instruction Decode & Microcode
    - Infruction Fetch, L1 cache
  [Compiler Takes care of it]
    - Execution Unit
    - Instruction Decode & Microcode
    - Instruction Fetch
    - Memory Ordering & Execution
  [Needs Care]
    - L1 Data Cache
    - L2 Cache & Interrupt servicing
    - Memory Ordering & Execution
    - Instruction Fetch & L1 Cache
    - SSE 4.2 instructions



## l1/l2/l3

getconf -a | grep CACHE

