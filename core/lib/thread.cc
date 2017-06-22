#include "core/lib/thread.h"

namespace lib {

SimpleThread::SimpleThread(std::function<void()> f) {
  func = f;
  started = false;
}

void SimpleThread::start() {
  th=std::thread(func);
  started = true;
}

void SimpleThread::join() {
  if (started) {
    th.join();
    started = false;
  }
}

}
