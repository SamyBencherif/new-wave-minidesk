#include "raylib.h"

struct circles {
  int x;
  int y;
  int r;
};

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "New Wave MiniDesk");

    SetTargetFPS(60);
    SetExitKey(0);

    struct circles circles[1000];
    int circles_index = 0;
    int circles_size = 0;

    while (!WindowShouldClose())
    {
      BeginDrawing();

      if (IsMouseButtonDown(0))
      {
        // mousedown: event
        circles[circles_index].x = GetMouseX();
        circles[circles_index].y = GetMouseY();
        circles[circles_index].r = 10;
        circles_index++;
        circles_size++;

        if (circles_index == 1000) 
          // circular limited array
          circles_index = 0;
      }

      // from loop:
      ClearBackground(BLUE);

      // from loop:
      for (int i=0; i<circles_size; i++)
      {
        DrawCircle(circles[i].x, circles[i].y, circles[i].r, RED);
      }

      EndDrawing();
    }

    CloseWindow();
    return 0;
}
