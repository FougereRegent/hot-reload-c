#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_PATH "./prj"

#define NB_CHAR_SYS 255
#define SUCCESS 0
#define ERROR -1

#define DIGEST_SIZE 32
#define TRUE 1
#define FALSE 0

#define CLOSE_DL(handle) dlclose(handle)

typedef unsigned char boolean;

void *(*plug_function)(void *d);

static void *load_module(char *name_module);
static void *load_function(void *lib, char *name_function);
static boolean file_change(const char *file_name);
static void compile();

static char old_digest[DIGEST_SIZE];

/*This project is used to make an personal hot reload*/
int main(int argc, char **argv) {
  printf("Hot Reloading\n");

  void *result = NULL;
  while (1) {
#define FILE_PATH "./prj/main.c"
    boolean result_modif = file_change(FILE_PATH);

    if (result_modif) {
      fprintf(stdout, "Changement fichier\n");
      compile();
    }

    void *handle = load_module("libmain.so");
    plug_function = load_function(handle, "main_module");

    result = plug_function(result);

    getchar();
    CLOSE_DL(handle);
  }
  free(result);
  return EXIT_SUCCESS;
}

static void *load_module(char *name_module) {
  void *handle = NULL;

  handle = dlopen(name_module, RTLD_NOW);

  if (handle == NULL) {
    perror("dlopen() :");
    exit(1);
  }
  return handle;
}

static void *load_function(void *lib, char *name_function) {
  void (*func_ptr)(void) = NULL;
  if (lib == NULL) {
    return NULL;
  }

  func_ptr = dlsym(lib, name_function);
  return func_ptr;
}

static boolean file_change(const char *file_name) {
  FILE *file;
  char command[1024];
  char digest_result[DIGEST_SIZE];

  sprintf(command, "md5sum %s | cut -d ' ' -f1", file_name);

  if ((file = popen(command, "r")) == NULL) {
    perror("popen() :");
    exit(1);
  }
  fscanf(file, "%s", digest_result);
  if (pclose(file)) {
    perror("pclose() :");
    exit(1);
  }

  if (strcmp(old_digest, digest_result) != 0) {
    strcpy(old_digest, digest_result);
    return TRUE;
  }
  return FALSE;
}

static void compile() {
#define COMPILE_COMAND "make -C ./prj"
#define ADD_ENV_LD "export LD_LIBRARY_PATH=$(pwd)/prj:$LD_LIBRARY_PATH"

  if (system(ADD_ENV_LD) < 0) {
    perror("system() :");
    exit(1);
  }

  if (system(COMPILE_COMAND) < 0) {
    fprintf(stderr, "Erreur de compilation");
  }
}
