#include "my_grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/my_common.h"
#include "../common/my_string.h"

int parse_flags(char* arg, info* flag) {
  int i = 1;
  int res = 0;
  while (arg[i] != '\0' && res == 0) {
    switch (arg[i]) {
      case 'e':
        flag->e = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        if (flag->l == 0) {
          flag->c = 1;
          flag->n = 0;
          flag->o = 0;
        }
        break;
      case 'l':
        flag->l = 1;
        flag->c = 0;
        flag->n = 0;
        flag->o = 0;
        break;
      case 'n':
        if (flag->l == 0 && flag->c == 0) flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        flag->e = -1;
        break;
      case 'o':
        if (flag->l == 0 && flag->c == 0) flag->o = 1;
        break;
      default:
        printf("my_grep: invalid option -- '%c'\n", arg[i]);
        res = -1;
        break;
    }
    ++i;
  }
  return res;
}

int open_file(char* name, FILE** fin, int flag) {
  int res = 0;
  if ((*fin = fopen(name, "r")) == NULL) {
    if (flag == 0) printf("my_grep: %s: No such file or directory\n", name);
    res = -1;
  }
  return res;
}

void process_h(info flag, char* fname) {
  if (flag.h != 1) {
    int bound = 2;
    if (flag.f_count >= bound) printf("%s:", fname);
  }
}

void process_n(info flag, int count_l) {
  if (flag.n == 1) printf("%d:", count_l);
}

void process_c(info flag, int match_count, char* fname) {
  if (flag.c == 1) {
    process_h(flag, fname);
    printf("%d\n", match_count);
  }
}

void mv_pointer(int bound, char** orig_str) {
  for (int i = 0; i < bound; i++) (*orig_str)++;
}

int alloc_arr(char** input, int symb, int* a_size) {
  int res = 0;
  if (*input == NULL || symb == -1) {
    *input = (char*)malloc((*a_size) * sizeof(char));
    if (*input == NULL)
      res = -1;
    else
      my_memset(*input, '\0', *a_size);
  } else {
    if (symb + 1 == *a_size) {
      *a_size *= 2;
      char* tmp = (char*)realloc(*input, (*a_size) * sizeof(char));
      if (tmp != NULL) {
        *input = tmp;
      } else {
        res = -1;
      }
    }
  }
  return res;
}

int process_f_add_template(FILE* fin, info* flag, char*** template) {
  int res = 0;
  char ch;
  int symb = 0;
  int a_size = 100;
  char* word = NULL;
  res = alloc_arr(&word, symb, &a_size);
  while ((ch = fgetc(fin)) != EOF && !feof(fin) && !ferror(fin) && res != -1) {
    if (ch != '\n') {
      word[symb] = ch;
      symb++;
      res = alloc_arr(&word, symb, &a_size);
    }
    if (res != -1 && ch == '\n') {
      word[symb] = '\0';
      res = save_name(&flag->t_count, template, word, &flag->t_size);
      my_memset(word, '\0', symb);
      symb = 0;
    }
  }
  if (my_strlen(word) > 0 && res != -1) {
    word[symb] = '\0';
    res = save_name(&flag->t_count, template, word, &flag->t_size);
  }
  if (word != NULL || res != -1) free(word);
  return res;
}

int process_f(char*** template, char* fname, info* flag) {
  int res = 0;
  FILE* fin = NULL;
  res = open_file(fname, &fin, 0);
  if (res != -1) res = process_f_add_template(fin, flag, template);
  if (fin != NULL) fclose(fin);
  return res;
}

int process_without_ef(info* flag, char*** template, char*** input) {
  int res = 0;
  if (flag->e == 0) {
    if (flag->f_count == 1) {
      printf("Usage: ./my_grep [OPTION]... PATTERNS [FILE]...\n");
      res = -1;
    }
    if (res != -1) {
      res = save_name(&flag->t_count, template, (*input)[0], &flag->t_size);
      if (res != -1) {
        free((*input)[0]);
        for (int i = 0; i < flag->f_count - 1; i++) {
          (*input)[i] = (*input)[i + 1];
        }
        flag->f_count--;
      }
    }
  }
  return res;
}

int parse_input(int argc, char* argv[], info* flag, char*** input,
                char*** tmplt) {
  int res = 0;
  for (int i = 1; i < argc; i++) {
    if (my_strlen(argv[i]) != 1 && argv[i][0] == '-' && flag->e != 1) {
      res = parse_flags(argv[i], flag);
    } else if (flag->f == 1) {
      res = process_f(tmplt, argv[i], flag);
      flag->f = 0;
    } else if (flag->e == 1) {
      flag->e = -1;
      res = save_name(&flag->t_count, tmplt, argv[i], &flag->t_size);
    } else {
      res = save_name(&flag->f_count, input, argv[i], &flag->f_size);
    }
    if (res == -1) break;
  }
  if (res != -1 && flag->f_count == 0) {
    printf("Usage: ./my_grep [OPTION]... PATTERNS [FILE]...\n");
    res = -1;
  }
  if (res != -1) res = process_without_ef(flag, tmplt, input);
  return res;
}

void process_l(info flag, int match_count, char* fname) {
  if (flag.l == 1 && match_count >= 1) {
    printf("%s\n", fname);
  }
}

char* process_look_up(char** str, char** tmplt, info flag, int* find_len,
                      int* ind) {
  char* lookup = NULL;
  char* lookup2 = NULL;
  *find_len = 0;
  int find_len2 = 0;

  for (int i = 0; i < flag.t_count; i++) {
    regex_t regex;
    int reti;
    int fl = REG_EXTENDED;
    if (flag.i == 1) fl |= REG_ICASE;
    reti = regcomp(&regex, tmplt[i], fl);
    if (reti) {
      fprintf(stderr, "Could not compile regex\n");
    }

    regmatch_t pmatch;
    const size_t nmatch = 1;
    reti = regexec(&regex, *str, nmatch, &pmatch, 0);
    if (reti == 0) {
      find_len2 = pmatch.rm_eo - pmatch.rm_so;
      lookup2 = *str + pmatch.rm_so;
      if (lookup == NULL || lookup2 < lookup) {
        lookup = lookup2;
        *find_len = find_len2;
        *ind = i;
      } else if (lookup == lookup2) {
        if (find_len2 > *find_len) {
          lookup = lookup2;
          *find_len = find_len2;
          *ind = i;
        }
      }
    }
    regfree(&regex);
  }
  return lookup;
}

void print_string_end(int matches, info fl, int enter, char** orig_str,
                      int end_enter) {
  if (fl.o == 0 && !(fl.l == 1 || fl.c == 1)) {
    if (matches >= 1 || (matches == 0 && enter == 1)) {
      if (end_enter == 1) {
        printf("%s", *orig_str);
      } else {
        printf("%s\n", *orig_str);
      }
    }
  }
  *orig_str = "\0";
}

int check_tmplt_enter(char* lookup, char** tmplt, info fl, int ind) {
  int enter = 0;
  if (lookup != NULL && fl.o == 1) {
    if (my_strcmp(tmplt[ind], ".") == 0) {
      enter = 1;
    }
  }
  return enter;
}

void process_fl_begin(info flag, int matches, char* fname, int count_l) {
  if (!(flag.v == 1 && flag.o == 1)) {
    if (matches == 1 || flag.o == 1) {
      process_h(flag, fname);
      process_n(flag, count_l);
    }
  }
}

void process_fl_end(info fl, int match, int* mcount, char** str) {
  if ((fl.c == 1 && match != 0) || (fl.l == 1 && match == 1)) {
    (*mcount)++;
    *str = "\0";
  }
}

void print_found(info fl, char* str, int offset, int len, char** orig_str,
                 int enter, int end_enter) {
  if (fl.v == 1) {
    if (fl.o == 0) {
      printf("%s", str);
    }
    *orig_str = "\0";
  } else {
    if (fl.o == 0 || (fl.o == 1 && enter == 1)) {
      printf("%.*s", offset, *orig_str);
    }
    mv_pointer(offset, orig_str);
    printf("%.*s", len, *orig_str);
    mv_pointer(len, orig_str);
    if (fl.o == 1 || (fl.o == 0 && **orig_str == '\0' && end_enter == 0))
      printf("\n");
  }
}

void nline(info fl, char** tmpl, int lines, char** my, int* mtch, char* name) {
  char* orig_str = *my;
  int end_enter = orig_str[my_strlen(orig_str) - 1] == '\n' ? 1 : 0;
  int matches = 0;

  while (*orig_str != '\0') {
    char* str = orig_str;
    int len = 0;
    int ind = 0;
    char* lookup = process_look_up(&str, tmpl, fl, &len, &ind);
    int enter = check_tmplt_enter(lookup, tmpl, fl, ind);

    if (((lookup != NULL && fl.v == 0) || (lookup == NULL && fl.v == 1)) &&
        (enter == 0)) {
      matches++;
      if (fl.l == 0 && fl.c == 0) {
        process_fl_begin(fl, matches, name, lines);
        print_found(fl, *my, (int)(lookup - str), len, &orig_str, enter,
                    end_enter);
      } else {
        process_fl_end(fl, matches, mtch, &orig_str);
      }
    } else {
      print_string_end(matches, fl, enter, &orig_str, end_enter);
    }
  }
}

void execution(FILE* in, info fl, char** tmplt, char* name) {
  int count_l = 0;
  int mtch = 0;

  char* line_ptr = NULL;
  size_t line_size_n = 0;

  while (getline(&line_ptr, &line_size_n, in) > 0) {
    count_l++;
    nline(fl, tmplt, count_l, &line_ptr, &mtch, name);
  }

  free(line_ptr);
  process_c(fl, mtch, name);
  process_l(fl, mtch, name);

  fclose(in);
}

int start(int argc, char* argv[]) {
  info flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 10};
  char** name_arr = NULL;
  char** template = NULL;

  int res = parse_input(argc, argv, &flag, &name_arr, &template);
  if (res != -1 && name_arr != NULL) {
    for (int i = 0; i < flag.f_count; i++) {
      FILE* fin = NULL;
      if (!open_file(name_arr[i], &fin, flag.s))
        execution(fin, flag, template, name_arr[i]);
    }
  }
  if (name_arr == NULL && res != -1)
    printf("Usage: ./my_grep [OPTION]... PATTERNS [FILE]...\n");
  free_in(&flag.f_count, &name_arr);
  free_in(&flag.t_count, &template);
  return res;
}

int main(int argc, char* argv[]) {
  int res = 0;
  if (argc >= 3) {
    res = start(argc, argv);
  } else {
    printf("Usage: ./my_grep [OPTION]... PATTERNS [FILE]...\n");
  }
  return res;
}
