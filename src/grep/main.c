#include "main.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int err = 0;

  struct flags *flag = malloc(sizeof(struct flags));

  flag->e = 0;
  flag->n = 0;
  flag->c = 0;
  flag->v = 0;
  flag->l = 0;
  flag->i = 0;

  if (argc < 3) {
    printf("Верный формат ввода: grep [OPTIONS] template [FILE_NAME]\n");
    err = 1;
  }

  if (argc == 3) {
    if (common_search(argc, argv) == 1) {
      err = 1;
    }
  }

  if (argc > 3) {
    if (switch_case(argc, argv, flag) == 1) {
      err = 1;
    }
  }
  free(flag);
  return err;
}

int common_search(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[1];
  char *file_name = argv[argc - 1];

  FILE *f = fopen(file_name, "rt");

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  if (pattern == file_name) {
    printf("Ошибка тут\n");
    err = 1;
  }

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];

    while (fgets(line, sizeof(line), f)) {
      if (!regexec(preg, line, 0, NULL, 0)) {
        printf("%s", line);
      }
    }
  }
  regfree(preg);
  fclose(f);
  return err;
}

int switch_case(int argc, char *argv[], struct flags *flag) {
  int err = 0;

  for (int i = 1; i < argc - 1; i++) {
    if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
      if (argv[i][1] == 'e') flag->e++;
      if (argv[i][1] == 'n') flag->n++;
      if (argv[i][1] == 'c') flag->c++;
      if (argv[i][1] == 'v') flag->v++;
      if (argv[i][1] == 'l') flag->l++;
      if (argv[i][1] == 'i') flag->i++;

      if (flag->e == 0 && flag->n == 0 && flag->c == 0 && flag->v == 0 &&
          flag->l == 0 && flag->i == 0) {
        printf("Неверный флаг\n");
        err = 1;
      }
    }
  }

  if (operate(argc, argv, flag) == 1) err = 1;

  return err;
}

int operate(int argc, char *argv[], struct flags *flag) {
  int err = 0;

  if (flag->e != 0) option_e(argc, argv);
  if (flag->n != 0)
    if (option_n(argc, argv) == 1) err = 1;
  if (flag->c != 0)
    if (option_c(argc, argv) == 1) err = 1;
  if (flag->v != 0)
    if (option_v(argc, argv) == 1) err = 1;
  if (flag->l != 0)
    if (option_l(argc, argv) == 1) err = 1;
  if (flag->i != 0)
    if (option_i(argc, argv) == 1) err = 1;

  return err;
}

int option_e(int argc, char *argv[]) {
  int err = 0;
  char *file_name = argv[argc - 1];

  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];

    while (fgets(line, sizeof(line), f)) {
      int i = 2;
      int stop = 0;

      while (i < argc && stop == 0) {
        char *pattern = argv[i];

        regex_t preg_storage;
        regex_t *preg = &preg_storage;

        regcomp(preg, pattern, 0);

        if (!regexec(preg, line, 0, NULL, 0)) {
          stop = 1;
          printf("%s", line);
        }
        // free(line);
        regfree(preg);
        i += 2;
      }
    }
  }
  // printf("%c", '\n');

  fclose(f);

  return err;
}

int option_n(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[2];
  char line[LENGTH_STRING];

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }
  for (int i = 3; i < argc; i++) {
    FILE *f = fopen(argv[i], "rt");

    if (f == NULL)
      perror("Ошибка открытия файла");
    else {
      int line_number = 1;

      while (fgets(line, sizeof(line), f)) {
        // int str_len = strlen(line);
        if (!regexec(preg, line, 0, NULL, 0)) {
          if (argc > 4)
            printf("%s:%d:%s", argv[i], line_number, line);
          else
            printf("%d:%s", line_number, line);
        }
        line_number++;
      }
    }
    fclose(f);
  }
  if (line[strlen(line) - 1] != '\n') printf("%c", '\n');
  regfree(preg);
  // fclose(f);

  return err;
}

int option_c(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[2];

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }

  for (int i = 3; i < argc; i++) {
    FILE *f = fopen(argv[i], "rt");

    if (f == NULL)
      perror("Ошибка открытия файла");
    else {
      char line[LENGTH_STRING];
      int count = 0;

      while (fgets(line, sizeof(line), f)) {
        if (!regexec(preg, line, 0, NULL, 0)) {
          count++;
        }
      }
      if (argc > 4)
        printf("%s:%d\n", argv[i], count);
      else
        printf("%d\n", count);
    }
    fclose(f);
  }
  regfree(preg);
  // fclose(f);

  return err;
}

int option_v(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[2];
  char line[LENGTH_STRING];

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }
  for (int i = 3; i < argc; i++) {
    FILE *f = fopen(argv[i], "rt");

    if (f == NULL)
      perror("Ошибка открытия файла");
    else {
      while (fgets(line, sizeof(line), f)) {
        if (regexec(preg, line, 0, NULL, 0)) {
          if (argc > 4)
            printf("%s:%s", argv[i], line);
          else
            printf("%s", line);
        }
      }
    }
    fclose(f);
  }
  if (line[strlen(line) - 1] != '\n') printf("%c", '\n');
  // printf("%s", line);

  regfree(preg);
  // fclose(f);
  return err;
}

int option_l(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[2];
  int stop = 0;

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }

  for (int i = 3; i < argc; i++) {
    FILE *f = fopen(argv[i], "rt");

    if (f == NULL)
      perror("Ошибка открытия файла");
    else {
      char line[LENGTH_STRING];

      while (fgets(line, sizeof(line), f) && stop == 0) {
        if (!regexec(preg, line, 0, NULL, 0)) {
          stop = 1;
        }
      }
      if (stop == 1) printf("%s\n", argv[i]);
    }
    stop = 0;
    fclose(f);
  }
  regfree(preg);

  return err;
}

int option_i(int argc, char *argv[]) {
  int err = 0;
  char *pattern = argv[2];
  char line[LENGTH_STRING];
  char line_tmp[LENGTH_STRING];

  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  toLowerCase(pattern);

  if (regcomp(preg, pattern, 0)) {
    printf("Ошибка с regex\n");
    err = 1;
  }
  for (int i = 3; i < argc; i++) {
    FILE *f = fopen(argv[i], "rt");

    if (f == NULL)
      perror("Ошибка открытия файла");
    else {
      while (fgets(line, sizeof(line), f)) {
        int sizeof_tmp = sizeof(line);
        for (int i = 0; i < sizeof_tmp; i++) {
          line_tmp[i] = line[i];
        }
        toLowerCase(line);
        if (!regexec(preg, line, 0, NULL, 0)) {
          if (argc > 4)
            printf("%s:%s", argv[i], line_tmp);
          else
            printf("%s", line_tmp);
        }
      }
    }
    fclose(f);
  }

  regfree(preg);

  return err;
}

void toLowerCase(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}
