#pragma once

#include "observer.h"
#include <vector>

namespace nsweeper {
template <Observer T> class Subject {
  std::vector<T *> observers;

public:
  void attach(T &observer);
  void notifyObservers();
};

template <Observer T> void Subject<T>::attach(T &observer) {
  observers.emplace_back(observer);
}

template <Observer T> void Subject<T>::notifyObservers() {
  for (T *ob : observers) {
    ob->notify();
  }
}
} // namespace nsweeper
