#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bf.h>
int main(int argc, char** argv){
  if(argc != 2){
    fprintf(stderr, "No input file\n");
    return EXIT_FAILURE;
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
  code[length] = '\0';
  fclose(file);
  exec(buffer);
  free(buffer);
  return EXIT_SUCCESS;
}
