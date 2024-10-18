#include <chrono>
#include <iostream>
#include "entity.h"

int main() {
  const int iterations = 5000000;

  Entity entity;
  SlowEntity slowEntity;

  auto startEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    entity.update();
  }
  auto endEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity =
      endEntity - startEntity;
  std::cout << "Time taken by Entity: " << durationEntity.count() << " ms"
            << std::endl;

  auto startSlowEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    slowEntity.update();
  }
  auto endSlowEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationSlowEntity =
      endSlowEntity - startSlowEntity;
  std::cout << "Time taken by SlowEntity: " << durationSlowEntity.count()
            << " ms" << std::endl;

  return 0;
}
