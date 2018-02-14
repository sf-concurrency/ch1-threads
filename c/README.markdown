## Examples in C

[hello-thread](hello-thread.c): Simple "hello world" example with threads.

[counter-bad](counter-bad.c): Increments a global counter from two threads. Expected output is 20000 (10000 from two threads) but actual results will vary and be less than 20000.

[counter-mutex](counter-mutex.c): Adds mutex locks to the global counter example. See comments beginning with "Mutex:" for the additions.
