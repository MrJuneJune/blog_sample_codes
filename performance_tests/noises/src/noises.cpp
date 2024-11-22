#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <raylib.h>

namespace real {

/* randomly place */
void whiteNoiseRandom(const int& sides, const float& inner_radius, Vector2 positions[], int& i) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> random_float(0, 1);

  Vector2 start_point = { random_float(gen) * sides, random_float(gen) * sides };
  float x = start_point.x;
  float y = start_point.y;
  positions[i] = { x, y };
}

/* randomly places if it is not to close to each others */
void blueNoiseRandom(const int& sides, const float& inner_radius, Vector2 positions[], int& i) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> random_float(0, 1);
  int attempts = 0;
  const int max_attempts = sides * sides;

  while (attempts < max_attempts) {
    Vector2 start_point = { random_float(gen) * sides, random_float(gen) * sides };
    float x = start_point.x;
    float y = start_point.y;

    if (x >= 0 && x < sides && y >= 0 && y < sides) {
      bool added = true;
      for (int j = 0; j < i; j++) {
        Vector2 current_point = positions[j];
        float dx = x - current_point.x;
        float dy = y - current_point.y;
        if (std::sqrt(dx * dx + dy * dy) < inner_radius) {
          added = false;
          break;
        }
      }
      if (added) {
        positions[i] = { x, y };
        break;
      }
    }
    attempts++;
  }
}

/* randomly places within given radius if it is possible. If not, randomly find an suitable empty spot */
void blueNoiseCircle(const int& sides, const float& inner_radius, const float& outer_radius,
               Vector2& starting_point, Vector2 positions[], int& i){
  float center_x = starting_point.x;
  float center_y = starting_point.y;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> angle_dist(0, 2 * M_PI);
  std::uniform_real_distribution<float> radius_dist(0, 1);

  bool added = false;
  int attempts = 0;
  const int max_attempts = outer_radius*outer_radius*PI - inner_radius*inner_radius*PI;

  while (attempts <= max_attempts) {
    float theta = angle_dist(gen);
    float random_scale = radius_dist(gen);
    float radius = std::sqrt(random_scale * (outer_radius * outer_radius -
                                             inner_radius * inner_radius) +
                             inner_radius * inner_radius);
    float x = center_x + radius * std::cos(theta);
    float y = center_y + radius * std::sin(theta);

    added = true;
    if (x > 0 && x < sides && y > 0 && y < sides) {
      for (int j = 0; j < i; j++) {
        Vector2 current_point = positions[j];
        float dx = x - current_point.x;
        float dy = y - current_point.y;
        if (std::sqrt(dx * dx + dy * dy) < inner_radius) {
          added = false;
          break;
        }
      }
      if (added) { 
        positions[i] = { x, y };
        break;
      }
    }

    attempts++;
  }

  /* When we are out of the options within given circle so that it needs to find a empty spot randomly*/
  if (!added) {
    blueNoiseRandom(sides, inner_radius, positions, i);
  }
}
} // namespace real

int main() {
  const int WIDTH = 1000, HEIGHT = 800;
  const int MAX_POINT = 800;

  const float OUTER_RADIUS = 60.0f;
  const float INNER_RADIUS = 30.0f;

  Vector2 positions[MAX_POINT];
  positions[0] = {100, 100};
  int current_number_of_points = 0;

  InitWindow(WIDTH, HEIGHT, "Random Noise");
  Texture2D grass = LoadTexture("./assets/grass.png");

  int newWidth = (int)(INNER_RADIUS * 1.5f);
  int newHeight = (int)(INNER_RADIUS);

  RenderTexture2D renderTexture = LoadRenderTexture(newWidth, newHeight);

  BeginTextureMode(renderTexture);

  ClearBackground(BLANK);

  DrawTexturePro(
      grass,
      (Rectangle){ 0, 0, (float)grass.width, (float)grass.height  }, 
      (Rectangle){ 0, 0, INNER_RADIUS * 1.5f, INNER_RADIUS},                            
      (Vector2){ 0, 0},                                                       
      0.0f,
      WHITE 
  );

  EndTextureMode();

  Texture2D resizedTexture = renderTexture.texture;

  UnloadTexture(grass);

  while (current_number_of_points < MAX_POINT) {
      Vector2 starting_point = positions[current_number_of_points];
      current_number_of_points++; 
      std::cout << "point " << current_number_of_points << "\n";
      real::whiteNoiseRandom(WIDTH, INNER_RADIUS, positions, current_number_of_points);

      // Vector2 starting_point = positions[current_number_of_points];
      // current_number_of_points++; 
      // std::cout << "point " << current_number_of_points << "\n";
      // real::blueNoiseRandom(WIDTH, INNER_RADIUS, positions, current_number_of_points);

      // Vector2 starting_point = positions[current_number_of_points];
      // current_number_of_points++; 
      // std::cout << "point " << current_number_of_points << "\n";
      // real::blueNoiseCircle(WIDTH, INNER_RADIUS, OUTER_RADIUS, starting_point, positions, current_number_of_points);
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    for (int j=0; j<current_number_of_points; j++) {
      Vector2 point = positions[j];
      DrawTexture(resizedTexture, point.x, point.y, WHITE);
      // DrawPixel(point.x, point.y, WHITE);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
