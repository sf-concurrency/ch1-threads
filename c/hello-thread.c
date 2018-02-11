/*
hello-thread - simple hello world with threads

Demonstrates how to create and join a thread.

by Greg Heo <greg@gregheo.com>
*/

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

/// Returns the current thread ID.
static uint64_t get_thread_id() {
  uint64_t tid = 0;
  pthread_threadid_np(pthread_self(), &tid);
  return tid;
}

/**
Function to be run from a new thread.

The pthread API expects a function that takes a single `void *` argument,
and returns a `void *`. We don't use either of these values.
*/
static void * hello(void *dummy) {
  printf("Hello from thread #%llu!\n", get_thread_id());

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t1;
  pthread_create(
    &t1,   // out parameter
    NULL,  // thread attributes
    hello, // function pointer
    NULL   // argument to send into the function
  );

  printf("Hello from the main thread (#%llu)!\n", get_thread_id());

  // Yield the processor. Not strictly required for this example since we're
  // waiting for the thread in the following line.
  pthread_yield_np();

  // Wait for thread t1 to finish.
  pthread_join(t1, NULL);

  return 0;
}
