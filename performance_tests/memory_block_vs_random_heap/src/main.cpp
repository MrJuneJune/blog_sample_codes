#include <chrono>
#include <iostream>
#include "entity.h"

int main() {
  const int iterations = 50000000;

  Entity* entity = new Entity();
  SlowEntity* slowEntity = new SlowEntity();

  auto startSlowEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    slowEntity->update();
  }
  auto endSlowEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationSlowEntity =
      endSlowEntity - startSlowEntity;
  std::cout << "Time taken by SlowEntity: " << durationSlowEntity.count()
            << " ms" << std::endl;
  delete slowEntity;

  auto startEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    entity->update();
  }
  auto endEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity =
      endEntity - startEntity;
  std::cout << "Time taken by Entity: " << durationEntity.count() << " ms"
            << std::endl;

  return 0;
}
