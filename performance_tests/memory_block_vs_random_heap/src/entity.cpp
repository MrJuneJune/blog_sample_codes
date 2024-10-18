#include "entity.h"
#include <iostream>
#include <string>

Entity::Entity() {
  memory_block =
      new char[sizeof(Vector3) * 2 + sizeof(int) * 2 + sizeof(std::string)];

  position = new (memory_block) Vector3;
  velocity = new (static_cast<char*>(memory_block) + sizeof(Vector3)) Vector3;
  health =
      new (static_cast<char*>(memory_block) + sizeof(Vector3) * 2) int32_t(100);
  attackPower =
      new (static_cast<char*>(memory_block) + sizeof(Vector3) * 2 + sizeof(int))
          int32_t(10);
  state = new (static_cast<char*>(memory_block) + sizeof(Vector3) * 2 +
               sizeof(int) * 2) std::string("idle");
}

Entity::~Entity() {
  // Call destructors explicitly
  position->~Vector3();
  velocity->~Vector3();

  // Free the memory block
  delete[] memory_block;
}

void Entity::update() {
  this->position->x += this->velocity->x;
  this->position->y += this->velocity->y;
  this->position->z += this->velocity->z;
}

void Entity::printDetails() {
  std::cout << "Position: (" << position->x << ", " << position->y << ", "
            << position->z << ")\n";
  std::cout << "Velocity: (" << velocity->x << ", " << velocity->y << ", "
            << velocity->z << ")\n";
  std::cout << "Health: " << *health << "\n";
  std::cout << "Attack Power: " << *attackPower << "\n";
  std::cout << "State: " << *state << "\n";
}

SlowEntity::SlowEntity() {
  this->position = new Vector3();
  this->velocity = new Vector3();
  this->health = new int();
  this->attackPower = new int();
}

void SlowEntity::update() {
  this->position->x += this->velocity->x;
  this->position->y += this->velocity->y;
  this->position->z += this->velocity->z;
}

void SlowEntity::printDetails() {
  std::cout << "Position: (" << position->x << ", " << position->y << ", "
            << position->z << ")\n";
  std::cout << "Velocity: (" << velocity->x << ", " << velocity->y << ", "
            << velocity->z << ")\n";
  std::cout << "Health: " << *health << "\n";
  std::cout << "Attack Power: " << *attackPower << "\n";
  std::cout << "State: " << *state << "\n";
}
