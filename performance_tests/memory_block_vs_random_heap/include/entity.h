#pragma once
#include <string>

struct Vector3 {
  float x, y, z;
};

struct Entity {
  char* memory_block = NULL;

  Vector3* position = NULL;
  Vector3* velocity = NULL;
  int* health = NULL;
  int* attackPower = NULL;
  std::string* state = NULL;

  int num_attributes = 5;

  Entity();

  ~Entity();

  void update();
  void printDetails();
};

struct SlowEntity {
  Vector3* position;
  Vector3* velocity;
  int* health;
  int* attackPower;

  std::string* state = NULL;

  SlowEntity();

  void update();
  void printDetails();
};
