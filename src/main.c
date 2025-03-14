#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bf.h"
int main(int argc, char** argv){
  if(argc != 2){
    char* buffer = NULL;
    size_t len = 0;
    ssize_t read;
    signed char* arr = calloc(30000, 1);
    while(1){
      printf(">> ");
      read = getline(&buffer, &len, stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if(read != -1){
	if(strcasecmp(buffer, "exit") == 0){
	  break;
	}
	exec(buffer, arr);
      }
    }
    free(arr);
    free(buffer);
    return EXIT_SUCCESS;
  }
  FILE* file = fopen(argv[1], "r");
  if(!file){
    fprintf(stderr, "Can't open file\n");
    return EXIT_FAILURE;
  }
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  rewind(file);
  char* buffer = malloc(length + 1);
  if(!buffer){
    fprintf(stderr, "Can't allocate memory for buffer\n");
    return EXIT_FAILURE;
  }
  fread(buffer, 1, length, file);
  buffer[length] = '\0';
  fclose(file);
  signed char* arr = calloc(30000, 1);
  exec(buffer, arr);
  free(buffer);
  return EXIT_SUCCESS;
}
