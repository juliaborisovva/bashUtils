#include <stdlib.h>

#include "my_string.h"

void free_in(int* count, char*** in) {
  if (*in != NULL) {
    for (int j = 0; j < *count; j++) free((*in)[j]);
    free(*in);
  }
  *count = 0;
}

int add_name(int* count, char*** input, char* arg) {
  int res = 0;
  // ! обработка пустой строки
  if (my_strcmp(arg, "\0") == 0) arg = ".";
  char* in = (char*)malloc((my_strlen(arg) + 1) * sizeof(char));
  if (in != NULL) {
    my_strcpy(in, arg);
    (*input)[*count] = in;
    (*count)++;
  } else {
    free_in(count, input);
    res = -1;
  }
  return res;
}

int save_name(int* count, char*** input, char* arg, int* a_size) {
  int res = 0;
  if (*input == NULL) {
    *input = (char**)malloc(*a_size * sizeof(char*));
    if (*input != NULL)
      res = add_name(count, input, arg);
    else
      res = -1;
  } else {
    if (*a_size <= *count) {
      *a_size *= 2;
      char** tmp = (char**)realloc(*input, *a_size * sizeof(char*));
      if (tmp != NULL) {
        *input = tmp;
      } else {
        free_in(count, input);
        res = -1;
      }
    }
    if (res != -1) res = add_name(count, input, arg);
  }
  return res;
}
