#include <chrono>
#include <cstdint>
#include <iostream>

constexpr float Pi32 = 3.1415f;

class shape_base {
 public:
  shape_base() {}

  virtual float Area() = 0;
};

class square : public shape_base {
 public:
  square(float SideInit) : Side(SideInit) {}

  virtual float Area() { return Side * Side; }

 private:
  float Side;
};

class rectangle : public shape_base {
 public:
  rectangle(float WidthInit, float HeightInit)
      : Width(WidthInit), Height(HeightInit) {}

  virtual float Area() { return Width * Height; }

 private:
  float Width, Height;
};

class triangle : public shape_base {
 public:
  triangle(float BaseInit, float HeightInit)
      : Base(BaseInit), Height(HeightInit) {}

  virtual float Area() { return 0.5f * Base * Height; }

 private:
  float Base, Height;
};

class circle : public shape_base {
 public:
  circle(float RadiusInit) : Radius(RadiusInit) {}

  virtual float Area() { return Pi32 * Radius * Radius; }

 private:
  float Radius;
};

float totalAreaVTML(int32_t shape_counts, shape_base** shapes) {
  float accum = 0.0f;
  for (int32_t shape_index = 0; shape_index < shape_counts; ++shape_index) {
    accum += shapes[shape_index]->Area();
  }

  return accum;
}

const int TOTAL_NUMBER_OF_SHAPES = 9999;

int main() {
  rectangle rect(10.0f, 10.0f);
  triangle tri(10.0f, 10.0f);
  circle cir(10.0f);

  shape_base* shapes[TOTAL_NUMBER_OF_SHAPES];

  double elapsed_time_ns;

  std::cout << "Using virtual function" << "\n";

  for (int j = 0; j < 10000; j++) {
    for (int i = 0; i < 3333; i++) {
      shapes[i * 3] = new rectangle(10.0f, 10.0f);
      shapes[i * 3 + 1] = new triangle(10.0f, 10.0f);
      shapes[i * 3 + 2] = new circle(10.0f);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    totalAreaVTML(TOTAL_NUMBER_OF_SHAPES, shapes);
    auto end_time = std::chrono::high_resolution_clock::now();
    elapsed_time_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(
                           end_time - start_time)
                           .count();

    for (int i = 0; i < TOTAL_NUMBER_OF_SHAPES; ++i) {
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
