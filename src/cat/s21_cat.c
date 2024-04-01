#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char *argv[]) {
  int err = 0;

  struct flags *flag = malloc(sizeof(struct flags));

  flag->b = 0;
  flag->n = 0;
  flag->s = 0;
  flag->e = 0;
  flag->t = 0;
  flag->v = 0;

  if (argc < 2) {
    printf("Верный формат ввода: cat [OPTIONS] [FILE]\n");
    err = 1;
  }

  if (argc == 2) {
    if (argv[1][0] == '-') {
      printf("Необходимо ввести имя файла.\n");
      err = 1;
    } else {
      print_file(argv[1]);
    }
  }

  if (argc >= 3)
    if (switch_case(argc, argv, flag) == 1) err = 1;

  free(flag);
  return err;
}

void print_file(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char c = fgetc(f);
    while (c != EOF) {
      printf("%c", c);
      c = fgetc(f);
    }
  }
}

int switch_case(int argc, char *argv[], struct flags *flag) {
  int err = 0;
  char *file_name = argv[argc - 1];
  int flag_go = 0;

  for (int i = 1; i < argc - 1; i++) {
    if (argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        flag_go = 1;
        flag->b++;
      }
    }
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-E") == 0) {
        flag_go = 1;
        flag->e++;
      }
    }
    if (argv[i][1] == '-') {
      if (strcmp(argv[i], "--number") == 0) {
        flag_go = 1;
        flag->n++;
      }
    }
    if (argv[i][1] == '-') {
      if (strcmp(argv[i], "--squeeze-blank") == 0) {
        flag_go = 1;
        flag->s++;
      }
    }
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-T") == 0) {
        flag_go = 1;
        flag->t++;
      }
    }

    int len_argv = strlen(argv[i]);
    for (int j = 1; j < len_argv && flag_go == 0; j++) {
      if (argv[i][j] == 'b') flag->b++;
      if (argv[i][j] == 'n') flag->n++;
      if (argv[i][j] == 's') flag->s++;
      if (argv[i][j] == 'e') flag->e++;
      if (argv[i][j] == 't') flag->t++;
      if (argv[i][j] == 'v') flag->v++;
    }

    if (flag->b == 0 && flag->e == 0 && flag->s == 0 && flag->n == 0 &&
        flag->t == 0 && flag->v == 0) {
      printf("Неверный флаг\n");
      err = 1;
    }
  }

  operate(file_name, flag);

  return err;
}

void operate(char *file_name, struct flags *flag) {
  if (flag->b != 0 && flag->n != 0) option_b(file_name);

  if (flag->b != 0 && flag->n == 0) option_b(file_name);
  if (flag->n != 0) option_n(file_name);
  if (flag->s != 0) option_s(file_name);
  if (flag->e != 0) option_e(file_name);
  if (flag->t != 0) option_t(file_name);
  if (flag->v != 0) option_t(file_name);
}

void option_b(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];
    int line_number = 0;

    while (fgets(line, sizeof(line), f)) {
      if (strlen(line) > 1) {
        line_number++;
        printf("%6d\t%s", line_number, line);
      } else {
        printf("%s", line);
      }
    }
  }
  fclose(f);
}

void option_n(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];
    int line_number = 0;

    while (fgets(line, sizeof(line), f)) {
      // if (strlen(line) > 1) {
      line_number++;
      printf("%6d\t%s", line_number, line);
      // }
    }
  }

  fclose(f);
}

void option_s(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];
    int count = 0;

    while (fgets(line, sizeof(line), f)) {
      if (strlen(line) == 1 && count == 0) {
        printf("%s", line);
        count++;
      }
      if (strlen(line) > 1) {
        printf("%s", line);
        count = 0;
      }
    }
  }

  fclose(f);
}

void option_e(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];

    while (fgets(line, sizeof(line), f)) {
      int len = strlen(line);
      for (int i = 0; i < len; i++) {
        if (i < len - 1) printf("%c", line[i]);
        if (i == len - 1 && line[i] == '\n') printf("$\n");
        if (i == len - 1 && line[i] != '\n') printf("%c", line[i]);
      }
    }
  }

  fclose(f);
}

void option_t(char *file_name) {
  FILE *f = fopen(file_name, "rt");

  if (f == NULL)
    perror("Ошибка открытия файла");
  else {
    char line[LENGTH_STRING];
    char new_line[LENGTH_STRING * 2];

    while (fgets(line, sizeof(line), f)) {
      int j = 0;
      int len = strlen(line);
      for (int i = 0; i < len; i++) {
        if (line[i] == '\t') {
          new_line[j] = '^';
          new_line[j + 1] = 'I';
          j += 2;
        } else {
          new_line[j] = line[i];
          j++;
        }
      }
      new_line[j] = '\0';
      printf("%s", new_line);
    }
  }

  fclose(f);
}
