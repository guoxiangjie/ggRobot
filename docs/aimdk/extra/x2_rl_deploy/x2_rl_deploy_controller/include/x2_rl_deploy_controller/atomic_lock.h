#pragma once

#include <atomic>

class RWLock
{
 public:
  RWLock()  = default;
  ~RWLock() = default;

  void Lock()
  {
    while (flag_.test_and_set(std::memory_order_acquire))
      ;
  }

  bool TryLock() { return flag_.test_and_set(std::memory_order_acquire) ? false : true; }

  void Unlock() { flag_.clear(std::memory_order_release); }

 private:
  std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

template <typename L>
class AtomicLock
{
 public:
  explicit AtomicLock(L &lock) : lock_(lock) { lock_.Lock(); }

  ~AtomicLock() { lock_.Unlock(); }

 private:
  L &lock_;
};
