#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#define TRUE 1
#define FALSE 0
#define WINDOW_NAME "Hot Reload"

typedef unsigned char boolean;
/*Déclaration de tes données*/
typedef struct {
  boolean init_state;
} data;

/*Déclaration des constante*/

static const int screenWidth = 800;
static const int screenHeight = 800;

static void init() {
  InitWindow(screenWidth, screenHeight, WINDOW_NAME);
  SetTargetFPS(60);
}

void *main_module(void *d) {
  data *saved_data;

  /*Initialisation des données*/
  if (d == NULL) {
    saved_data = (data *)malloc(sizeof(data));
    saved_data->init_state = false;
  } else {
    saved_data = (data *)d;
  }

  if (!saved_data->init_state) {
    init();
    saved_data->init_state = TRUE;
  }

  while (!WindowShouldClose()) {
  }

  CloseWindow();
  return saved_data;
}
