#pragma once
#include <chrono>

class Benchmark
{
  std::chrono::high_resolution_clock::time_point Start_;
public:
  void Start()
  {
    Start_ = std::chrono::high_resolution_clock::now();
  }
  template<class duration = std::chrono::milliseconds>
  long long End()const
  {
    return std::chrono::duration_cast<duration>(std::chrono::high_resolution_clock::now() - Start_).count();
  }
public:
  Benchmark()
  {
    Start();
  }
};
