#pragma once

#include <memory>

#include "x2_rl_deploy_controller/atomic_lock.h"

template <typename T>
class DataBoard
{
 public:
  explicit DataBoard() = default;
  ~DataBoard()         = default;

  void SetData(const T &data)
  {
    AtomicLock<RWLock> lock(lock_);
    data_ptr_ = std::shared_ptr<T>(new T(data));
  }

  bool GetData(T &data, bool clear = false)
  {
    AtomicLock<RWLock> lock(lock_);
    if (data_ptr_ == nullptr) {
      return false;
    }

    data = *data_ptr_;
    if (clear) {
      data_ptr_.reset();
    }

    return true;
  }

 private:
  std::shared_ptr<T> data_ptr_;
  RWLock             lock_;
};