#include <chrono>
#include <iostream>
#include "entity.h"

void iterateThrough(const int iterations, Entity* entity) {
  auto startEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    entity->update();
  }
  auto endEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity =
      endEntity - startEntity;
  // std::cout << "Time taken: " << durationEntity.count() << " ms" << std::endl;
}

void iterateThrough(const int iterations, SlowEntity* entity) {
  auto startEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    entity->update();
  }
  auto endEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity =
      endEntity - startEntity;
  // std::cout << "Time taken: " << durationEntity.count() << " ms" << std::endl;
}

void updateTest(int iterations) {
  std::cout << "First run" << "\n";
  std::cout << "Heap allocated Entity" << "\n";
  SlowEntity* slowEntity = new SlowEntity();
  iterateThrough(iterations, slowEntity);
  delete slowEntity;
  std::cout << "Memory Block Entity" << "\n";
  Entity* entity = new Entity();
  iterateThrough(iterations, entity);
  delete entity;

  std::cout << "Second run reverse" << "\n";
  std::cout << "Memory Block Entity" << "\n";
  Entity* entity2 = new Entity();
  iterateThrough(iterations, entity2);
  delete entity2;
  std::cout << "Heap allocated Entity" << "\n";
  SlowEntity* slowEntity2 = new SlowEntity();
  iterateThrough(iterations, slowEntity2);
  delete slowEntity2;
}

void update(int x) {
  SlowEntity* slowEntity = new SlowEntity();
  iterateThrough(x, slowEntity);
  delete slowEntity;
}

void updateMB(int x) {
  Entity* entity = new Entity();
  iterateThrough(x, entity);
  delete entity;
}

void createHeap(int number) {
  std::cout << "Heap" << "\n";
  auto startEntity = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < number; i++) {
    update(10);
  }
  auto endEntity = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity =
      endEntity - startEntity;
  std::cout << "Time taken: " << durationEntity.count() << " ms" << std::endl;

  std::cout << "MD" << "\n";
  auto startEntity2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < number; i++) {
    updateMB(10);
  }
  auto endEntity2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationEntity2 =
      endEntity2 - startEntity2;
  std::cout << "Time taken: " << durationEntity2.count() << " ms" << std::endl;
}

int main() {
  // updateTest(50000000);
  createHeap(1000000);
  return 0;
}
