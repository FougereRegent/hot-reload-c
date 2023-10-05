#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int age;
  char *name;
} data;

void *main_module(void *d) {
  data *saved_data;

  if (d == NULL) {
    saved_data = malloc(sizeof(data));
    saved_data->name = malloc(sizeof(char));
    saved_data->age = 11;

    strcpy(saved_data->name, "Damien");
  } else {
    saved_data = (data *)d;
  }

  if (strcmp(saved_data->name, "Damien") == 0) {
    saved_data->age = 55;
    strcpy(saved_data->name, "John");
  } else {
    strcpy(saved_data->name, "Damien");
  }

  printf("Test 5\n");
  printf("Name : %s\tAge: %d\n", saved_data->name, saved_data->age);

  return saved_data;
}
