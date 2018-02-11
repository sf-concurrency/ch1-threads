/*
counter-bad - simple counter with a race condition.

by Greg Heo <greg@gregheo.com>
*/

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

/// Global counter variable
int counter = 0;

/// Returns the current thread ID.
static uint64_t get_thread_id() {
  uint64_t tid = 0;
  pthread_threadid_np(pthread_self(), &tid);
  return tid;
}

/// Function that mutates the global counter.
static void * perform_increment(void *dummy) {
  for (int i = 0; i < 10000; ++i) {
    ++counter;
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t1;
  pthread_create(&t1, NULL, perform_increment, NULL);

  pthread_t t2;
  pthread_create(&t2, NULL, perform_increment, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Counter value: %d\n", counter);

  return 0;
}
