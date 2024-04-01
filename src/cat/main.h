#ifndef SRC_CAT_MAIN_H
#define SRC_CAT_MAIN_H

const int LENGTH_STRING = 4096;
const int FILE_NAME = 7;

struct flags {
  int b;
  int n;
  int s;
  int e;
  int t;
  int v;
};

void print_file(char *file_name);
int switch_case(int argc, char *argv[], struct flags *flag);
void operate(char *file_name, struct flags *flag);

// void option_b(char *line, int line_number);
void option_b(char *file_name);

void option_n(char *file_name);
void option_s(char *file_name);
void option_e(char *file_name);
void option_t(char *file_name);
void gnustnay(char *argv[]);

#endif  // SRC_CAT_MAIN_H