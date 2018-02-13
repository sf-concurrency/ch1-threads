/*:

 # Counter protected by a mutex
 ### "Threads and Locks"
 [@algal](github.com/algal)

 This illustrates using a POSIX mutex to protect a counter.

 */

import Darwin

var counter:Int  = 0

var mutex:pthread_mutex_t = pthread_mutex_t()
pthread_mutex_init(&mutex, nil)

func get_thread_id() -> UInt64
{
  var tid:UInt64 = 0
  pthread_threadid_np(pthread_self(), &tid)
  return tid
}

func perform_increment() {
  for _ in 0..<1000 {
    pthread_mutex_lock(&mutex)
    counter += 1
    pthread_mutex_unlock(&mutex)
  }
}

/// Wrapped the incrementer in nonsense to satisfy `pthread_create`
func perform_increment_wrapped(_ x:UnsafeMutableRawPointer) -> UnsafeMutableRawPointer?
{
  perform_increment()
  return nil
}

func main() {
  var t1:pthread_t? = nil
  pthread_create(&t1, nil, perform_increment_wrapped, nil)

  var t2:pthread_t? = nil
  pthread_create(&t2, nil, perform_increment_wrapped, nil)

  pthread_join(t1!, nil)
  pthread_join(t2!, nil)

  print("Counter value: \(counter)")
}

main()

