#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bf.h"
void exec(char* cmd){
  signed char* arr = calloc(30000, 1);
  int i = 0;
  int stack[3000];
  int sp = 0;
  int index = 0;
  int count[2];
  while(i < strlen(cmd)){
    if(cmd[i] == '['){
      if(arr[index] == 0){
	int depth = 1;
	while(depth > 0 && ++i < strlen(cmd)){
	  if(cmd[i] == '['){
	    depth++;
	  }
	  else if(cmd[i] == ']'){
	    depth--;
	  }
	}
	i++;
      }
      else{
	stack[sp++] = i++;
      }
      count[0]++;
    }
    else if(cmd[i] == ']'){
      if(sp == 0){
	fprintf(stderr, "No matching [ for ]\n");
	exit(1);
      }
      if(arr[index] != 0){
	i = stack[sp - 1] + 1;
      }
      else{
	sp--;
	i++;
      }
      count[1]++;
    }
    else{
      switch(cmd[i]){
      case '+': arr[index]++;
	break;
      case '-': arr[index]--;
	break;
      case '>': if(++index >= 30000){
	  fprintf(stderr, "Out of bound\n");
	  exit(1);
	}
	break;
      case '<': if(--index < 0){
	  fprintf(stderr, "Out of bound\n");
	  exit(1);
	}
	break;
      case '.': if(arr[index] < 0){
	  fprintf(stderr, "Negative values are not allowed\n");
	  exit(1);
	}
	putchar(arr[index]);
	break;
      case ',': scanf(" %c", &arr[index]);
	break;
      }
      i++;
    }
  }
  if(count[0] != count[1]){
    fprintf(stderr, "No matching ] for [\n");
    exit(1);
  }
  free(arr);
}
