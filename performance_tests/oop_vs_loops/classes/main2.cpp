#include <chrono>
#include <cstdint>
#include <iostream>

constexpr float Pi32 = 3.1415f;

enum ShapeType : int32_t {
  RECTANGLE,
  TRIANGLE,
  CIRCLE,

  SHAPE_COUNT,
};

struct Shape {
  ShapeType type;
  float width;
  float height;
};

float const values[SHAPE_COUNT] = {1.0, 0.5f, Pi32};

float getAreaSwitch(const Shape& shape) {
  float sums = 0.0f;
  sums = values[shape.type] * shape.width * shape.height;
  return sums;
}

float totalAreaVTML(int32_t shape_counts, Shape* shapes[]) {
  float accum = 0.0f;
  for (int32_t shape_index = 0; shape_index < shape_counts; ++shape_index) {
    accum += getAreaSwitch(*shapes[shape_index]);
  }

  return accum;
}

const int TOTAL_NUMBER_OF_SHAPES = 9999;

int main() {
  Shape* shapes[TOTAL_NUMBER_OF_SHAPES];

  double elapsed_time_ns;

  std::cout << "Using Struct" << "\n";
  for (int j = 0; j < 10000; j++) {
    for (int i = 0; i < 3333; i++) {
      shapes[i * 3] = new Shape{RECTANGLE, 10.0f, 10.0f};
      shapes[i * 3 + 1] = new Shape{TRIANGLE, 10.0f, 10.0f};
      shapes[i * 3 + 2] = new Shape{CIRCLE, 10.0f, 0.0f};
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    totalAreaVTML(TOTAL_NUMBER_OF_SHAPES, shapes);
    auto end_time = std::chrono::high_resolution_clock::now();
    elapsed_time_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(
                           end_time - start_time)
                           .count();
    for (int i = 0; i < 9999; ++i) {
      delete shapes[i];
    }
  }

  double avg_time_per_shape_ns =
      static_cast<double>(elapsed_time_ns) / (10000 * TOTAL_NUMBER_OF_SHAPES);
  std::cout << "Took time: " << elapsed_time_ns / 1000.0f << "ms\n";
  double avg_cycles_per_shape = avg_time_per_shape_ns * 3;
  std::cout << "Average CPU cycles per shape (Struct): " << avg_cycles_per_shape
            << "\n";

  return 0;
}
