#include "raylib.h"
#include <ncurses.h>
#include <unistd.h>

#define MAX_LINES 100
#define LINES_PER_SCREEN 20
#define LINE_SPACING 30

const char *initial_text[] = {
  "╔╗────╔╗─",
  "║╚╗╔╦╗║╚╗",
  "║╔╣╠║╣║╔╣",
  "╚═╝╚╩╝╚═╝",
  "╔═╗───────────",
  "║╬║╔═╗─╔══╗╔═╗",
  "╠╗║║╬╚╗║║║║║╩╣",
  "╚═╝╚══╝╚╩╩╝╚═╝",
  "",
  "Rise, brave knight. Your valor",
  // (Rest of your initial_text content)
};

const char *kingdom_info[] = {
  "The Kingdom of Aeloria has long", "been a beacon of hope and strength.",
  "Our lands are vast, filled with...",
  // (Rest of your kingdom_info content)
};

const char *special_armor[] = {
  "Within the armory of the castle...",
  // (Rest of your special_armor content)
};

int num_lines_initial = sizeof (initial_text) / sizeof (initial_text[0]);
int num_lines_kingdom = sizeof (kingdom_info) / sizeof (kingdom_info[0]);
int num_lines_armor = sizeof (special_armor) / sizeof (special_armor[0]);

int scroll_position = 0;
int current_menu = 0; // 0 for initial text, 1 for menu options

void
DisplayText (const char **text, int num_lines, int scroll_pos)
{
  BeginDrawing ();
  ClearBackground (BLACK);

  int max_lines = num_lines < LINES_PER_SCREEN ? num_lines : LINES_PER_SCREEN;
  for (int i = 0; i < max_lines; i++)
    {
      if (i + scroll_pos < num_lines)
        {
          DrawText (text[i + scroll_pos], 20, 20 + i * LINE_SPACING, 20,
                    RAYWHITE);
        }
    }
  EndDrawing ();
}

void
DisplayMenu ()
{
  BeginDrawing ();
  ClearBackground (DARKGRAY);
  DrawText ("What would you like to do?", 20, 20, 20, RAYWHITE);
  DrawText ("1. Ask about the kingdom", 20, 60, 20, LIGHTGRAY);
  DrawText ("2. Ask about special armor and equipment", 20, 100, 20,
            LIGHTGRAY);
  DrawText ("3. Proceed to the next part of the game", 20, 140, 20, LIGHTGRAY);
  EndDrawing ();
}

int
main (void)
{
  InitWindow (800, 600, "Text-Based Game");

  SetTargetFPS (60);

  int num_lines = num_lines_initial;
  const char **text = initial_text;

  while (!WindowShouldClose ())
    {
      if (current_menu == 0)
        {
          if (IsKeyPressed (KEY_DOWN)
              && scroll_position < num_lines - LINES_PER_SCREEN)
            {
              scroll_position++;
            }
          if (IsKeyPressed (KEY_UP) && scroll_position > 0)
            {
              scroll_position--;
            }
          if (IsKeyPressed (KEY_RIGHT))
            {
              current_menu = 1; // Open menu
            }

          DisplayText (text, num_lines, scroll_position);
        }
      else
        {
          DisplayMenu ();

          if (IsKeyPressed (KEY_ONE))
            {
              text = kingdom_info;
              num_lines = num_lines_kingdom;
              scroll_position = 0;
              current_menu = 0;
            }
          else if (IsKeyPressed (KEY_TWO))
            {
              text = special_armor;
              num_lines = num_lines_armor;
              scroll_position = 0;
              current_menu = 0;
            }
          else if (IsKeyPressed (KEY_THREE))
            {
              DrawText ("Proceeding to next part...", 20, 200, 20, RAYWHITE);
              EndDrawing ();
              sleep (2); // Pause for effect
              break;     // Exits the game here for demo
            }
        }
    }

  CloseWindow ();
  return 0;
}
