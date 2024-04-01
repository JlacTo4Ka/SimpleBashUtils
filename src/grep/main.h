#ifndef SRC_GREP_MAIN_H
#define SRC_GREP_MAIN_H

const int LENGTH_STRING = 4096;
const int FILE_NAME = 7;

struct flags {
  int e;
  int n;
  int c;
  int v;
  int l;
  int i;
};

// void common_search(char *template, char* file_name);
int common_search(int argc, char *argv[]);
int switch_case(int argc, char *argv[], struct flags *flag);
int operate(int argc, char *argv[], struct flags *flag);
int option_e(int argc, char *argv[]);
int option_n(int argc, char *argv[]);
int option_c(int argc, char *argv[]);
int option_v(int argc, char *argv[]);
int option_l(int argc, char *argv[]);
int option_i(int argc, char *argv[]);
void toLowerCase(char *str);

#endif  // SRC_GREP_MAIN_H