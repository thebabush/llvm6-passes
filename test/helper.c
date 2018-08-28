#include <stdio.h>

void _printer(char *msg) {
  // Green text
  fputs("\e[32m", stdout);
  puts(msg);
  fputs("\e[39m", stdout);
}

