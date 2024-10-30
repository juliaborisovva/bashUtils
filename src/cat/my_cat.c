#include "my_cat.h"

#include <stdio.h>
#include <stdlib.h>

#include "../common/my_common.h"
#include "../common/my_string.h"

int parse_long_flags(char* arg, struct flags* flag) {
  int res = 0;
  if (my_strcmp(arg, "--number-nonblank") == 0) {
    flag->b = 1;
    if (flag->n == 1) flag->n = 0;
  } else if (my_strcmp(arg, "--number") == 0) {
    if (flag->b == 0) flag->n = 1;
  } else if (my_strcmp(arg, "--squeeze-blank") == 0) {
    flag->s = 1;
  } else if (my_strcmp(arg, "--show-ends") == 0) {
    flag->e = 1;
  } else if (my_strcmp(arg, "--show-tabs") == 0) {
    flag->t = 1;
  } else if (my_strcmp(arg, "--show-nonprinting") == 0) {
    flag->v = 1;
  } else {
    printf("my_cat: invalid option '%s'\n", arg);
    res = -1;
  }
  return res;
}

int parse_flags(char* arg, struct flags* flag) {
  int i = 1;
  int res = 0;
  while (arg[i] != '\0' && res == 0) {
    switch (arg[i]) {
      case '-':
        if ((res = parse_long_flags(arg, flag)) != -1) res = 1;
        break;
      case 'b':
        flag->b = 1;
        if (flag->n == 1) flag->n = 0;
        i++;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        i++;
        break;
      case 'E':
        flag->e = 1;
        i++;
        break;
      case 'v':
        flag->v = 1;
        i++;
        break;
      case 'n':
        if (flag->b == 0) flag->n = 1;
        i++;
        break;
      case 's':
        flag->s = 1;
        i++;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        i++;
        break;
      case 'T':
        flag->t = 1;
        i++;
        break;
      default:
        printf("my_cat: invalid option -- '%c'\n", arg[i]);
        res = -1;
        break;
    }
  }
  return res;
}

int parse_input(int argc, char* argv[], struct flags* flag, int* count,
                char*** input) {
  int res = 0;
  static int a_size = 1;
  for (int i = 1; i < argc; i++) {
    if (my_strlen(argv[i]) != 1 && argv[i][0] == '-')
      res = parse_flags(argv[i], flag);
    else
      res = save_name(count, input, argv[i], &a_size);
    if (res == -1) break;
  }
  return res;
}

int open_file(char* name, FILE** fin) {
  int res = 0;
  if ((*fin = fopen(name, "r")) == NULL) {
    printf("my_cat: %s: No such file or directory\n", name);
    res = -1;
  }
  return res;
}

void process_n_line(int* lines, int* dbl, int* symb, struct flags flag) {
  (*symb)++;
  if (*symb == 1)
    (*dbl)++;
  else
    *dbl = 0;
  if (flag.s != 1 || *dbl < 2) {
    if (flag.n == 1 && *symb == 1) printf("%6d\t", (*lines)++);
    if (*symb != 1) (*lines)++;
    if (flag.e == 1) putchar('$');
    putchar('\n');
  }
  *symb = 0;
}

void process_v(int ch) {
#if defined(__linux__)
  if (ch >= 0 && ch <= 8)
    printf("^%c", ch + 64);
  else if (ch >= 11 && ch <= 31 && ch != 13)
    printf("^%c", ch + 64);
  else if (ch == 127)
    printf("^%c", ch - 64);
  else if (ch >= 128 && ch <= 159)
    printf("M-^%c", ch - 64);
  else if (ch >= 160 && ch <= 255)
    printf("M-%c", ch - 128);
  else
    putchar(ch);
#elif defined(__APPLE__) || defined(__MACH__)
  if (ch >= 0 && ch <= 8)
    printf("^%c", ch + 64);
  else if (ch >= 11 && ch <= 31 && ch != 13)
    printf("^%c", ch + 64);
  else if (ch == 127)
    printf("^%c", ch - 64);
  else if (ch >= 128 && ch <= 159)
    printf("M-^%c", ch - 64);
  else
    putchar(ch);
#endif
}

void process_line(int ch, int* symb, struct flags flag, int count_l) {
  (*symb)++;
  if (*symb == 1 && (flag.b == 1 || flag.n == 1)) printf("%6d\t", count_l);
  if (ch == '\t' && flag.t == 1)
    printf("^I");
  else if (flag.v == 1)
    process_v(ch);
  else
    putchar(ch);
}

void process_data(struct flags flag, FILE** fin, int* count_l) {
  int ch;
  int symb = 0, doubles = 0;

  while ((ch = fgetc(*fin)) != EOF && !feof(*fin) && !ferror(*fin)) {
    if (ch == '\n')
      process_n_line(count_l, &doubles, &symb, flag);
    else
      process_line(ch, &symb, flag, *count_l);
  }

  fclose(*fin);
}

int start(int argc, char* argv[]) {
  struct flags flag = {0, 0, 0, 0, 0, 0};
  int file_count = 0;
  char** name_arr = NULL;

  int res = parse_input(argc, argv, &flag, &file_count, &name_arr);

  if (res != -1 && name_arr != NULL) {
    int count_l = 1;
    for (int i = 0; i < file_count; i++) {
      FILE* fin = NULL;
      if (!open_file(name_arr[i], &fin)) process_data(flag, &fin, &count_l);
#if defined(__APPLE__) || defined(__MACH__)
      count_l = 1;
#endif
    }
  }
  if (name_arr == NULL && res != -1)
    printf("my_cat: File or directory is not specified\n");
  free_in(&file_count, &name_arr);
  return res;
}

int main(int argc, char* argv[]) {
  int res = 0;
  if (argc >= 2) {
    res = start(argc, argv);
  } else {
    printf("my_cat: File or directory and options are not specified\n");
  }
  return res;
}
