#include "raylib.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct launcher {
  int x;
  int y;
  char title[30];
  Texture* ico;
  char shellexecute[100];
};

struct launcher launchers[20];
int launchers_size = 0;

struct ContextMenu {
  bool active;
  int x;
  int y;
};
struct ContextMenu contextMenu;

int DrawButton(int x, int y, int w, int h, Color c)
{
  int mx = GetMouseX();
  int my = GetMouseY();

  bool triggered = false;
  int mousebtn = -1;

  if (mx >= x && mx < x+w)
    if (my >= y && my < y+h)
    {
      c.a += 20;
      if (IsMouseButtonDown(0))
        c.a += 30;

      if (IsMouseButtonPressed(0))
        mousebtn = 0;
      if (IsMouseButtonPressed(1)) 
        mousebtn = 1;
    }

  DrawRectangle(x,y,w,h,c);

  return mousebtn;
}

void DrawLauncher(struct launcher* l)
{
  float scale = 2;
  Vector2 pos;

  pos.x = (int) (GetScreenWidth()/2. - scale * l->ico->width/2.); 
  pos.y = (int) (GetScreenHeight()/2. - scale * l->ico->height/2.);

  pos.x += l->x; pos.y += l->y;
  Color hint = {0,0,0,20};

  int mousebtn = -1;

  if (!contextMenu.active)
    mousebtn = DrawButton(pos.x-5, pos.y-5, 64+10, 64+20+10, hint);

  if (mousebtn == 0) // primary
  {
    system(l->shellexecute);
  }
  else if (mousebtn == 1) // secondary click
  {
    contextMenu.active = true;
    contextMenu.x = GetMouseX();
    contextMenu.y = GetMouseY();
  }

  DrawTextureEx(*l->ico, pos, 0, scale, WHITE);
  pos.y += 64;
  DrawText(l->title, pos.x, pos.y, 16, BLACK);
}

void DrawContextMenu()
{
  int textSize = 16;
  int w = 130;
  int h = (textSize+4)*3;

  DrawRectangle(contextMenu.x, contextMenu.y, w, h, WHITE);
  DrawRectangleLines(contextMenu.x, contextMenu.y, w, h, BLACK);

  if (IsMouseButtonPressed(0))
  {
    // if in bounds
    int mx = GetMouseX(); int my = GetMouseY();
    int x = contextMenu.x; int y = contextMenu.y;
    if (x <= mx && mx < x+w && y <= my && my < y+h)
    {
      // activate context menu item
    }
    else
    {
      // close context menu
      contextMenu.active = false;
    }
  }

  Color tint = {0,0,0,20};
  DrawButton(contextMenu.x, contextMenu.y,       w, h/3, tint);
  DrawButton(contextMenu.x, contextMenu.y+h/3,   w, h/3, tint);
  DrawButton(contextMenu.x, contextMenu.y+2*h/3, w, h/3, tint);

  DrawText("edit",      contextMenu.x+4, 2+contextMenu.y, textSize, BLACK);
  DrawText("rename",    contextMenu.x+4, 2+contextMenu.y+textSize+2, textSize, BLACK);
  DrawText("changeico", contextMenu.x+4, 2+contextMenu.y+2*(textSize+2), textSize, BLACK);
}

/*

Try using Aseprite, Firefox, and Thunar File Select

Create Icon Macro , with changeico, run, edit, rename

*/
int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "New Wave Minidesk");
    
    SetTargetFPS(10);
    SetExitKey(0);

    Texture t = LoadTexture("../logo.png");
    Texture t2 = LoadTexture("../pixely.png");

    Texture ico_aseprite = LoadTexture("../aseprite.png");
    Texture ico_terminal = LoadTexture("../terminal.png");
    Texture ico_firefox = LoadTexture("../firefox.png");
    Texture ico_chrome = LoadTexture("../chrome.png");

    contextMenu.active = false;

    // --- BEGIN LAUNCHERS DEFINITION --- //

    if (launchers_size < 20) 
    {
      launchers[launchers_size].x = -300;
      launchers[launchers_size].y = 50;
      strcpy(launchers[launchers_size].title, "aseprite");
      launchers[launchers_size].ico = &ico_aseprite;
      strcpy(launchers[launchers_size].shellexecute, "aseprite&");
      launchers_size++;
    }

    if (launchers_size < 20) 
    {
      launchers[launchers_size].x = 300;
      launchers[launchers_size].y = -200;
      strcpy(launchers[launchers_size].title, "terminal");
      launchers[launchers_size].ico = &ico_terminal;
      strcpy(launchers[launchers_size].shellexecute, "xfce4-terminal&");
      launchers_size++;
    }

    if (launchers_size < 20) 
    {
      launchers[launchers_size].x = -100;
      launchers[launchers_size].y = 200;
      strcpy(launchers[launchers_size].title, "firefox");
      launchers[launchers_size].ico = &ico_firefox;
      strcpy(launchers[launchers_size].shellexecute, "firefox-esr&");
      launchers_size++;
    }

    if (launchers_size < 20) 
    {
      launchers[launchers_size].x = 170;
      launchers[launchers_size].y = 200;
      strcpy(launchers[launchers_size].title, "chrome");
      launchers[launchers_size].ico = &ico_chrome;
      strcpy(launchers[launchers_size].shellexecute, "chromium&");
      launchers_size++;
    }

    // --- ENDOF LAUNCHERS DEFINITION --- //

    while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(WHITE);
      float scale = 3;
      Vector2 pos = {
        (int) (GetScreenWidth()/2. - scale*t.width/2.), 
        (int) (GetScreenHeight()/2. - scale*t.height/2.)
      };
      DrawTextureEx(t, pos, 0, scale, WHITE);

      for (int i=0; i<launchers_size; i++)
      {
        DrawLauncher(&launchers[i]);
      }

      if (contextMenu.active)
      {
        DrawContextMenu();
      }

      EndDrawing();
    }

    CloseWindow();
    return 0;
}
