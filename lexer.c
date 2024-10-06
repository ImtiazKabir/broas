#include "lexer.h"

#include <complex.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t readchar(int fd, char *pc) { return read(fd, pc, 1); }

int readline(int fd, char *line, size_t max) {
  char c;

  if (max == 0) {
    return -1;
  }

  if (readchar(fd, &c) == 0) {
    return 1;
  }

  if (c == '\n') {
    *line = '\0';
    return 0;
  }

  *line = c;
  return readline(fd, line + 1, max - 1);
}

char *getword(char *line, char *word, size_t max) {
  size_t i = 0;

  while ((i < max) && (*line != ' ') && (*line != '\0')) {
    *word = *line;
    word++;
    line++;
    i++;
  }

  while (*line == ' ') {
    line++;
  }

  *word = '\0';
  return line;
}

enum TokenType toktype(char const *word) {
  static char const opcodes[][8] = {
      "add", "sub", "lw",  "sw",  "mult",  "div",  "beq", "bneq",
      "mod", "xor", "or",  "and", "not",   "sl",   "sr",  "blt",
      "bgt", "ble", "bge", "jmp", "ref", "deref",
			"print", "scan", "exit"};
  static int const n = sizeof(opcodes) / sizeof(opcodes[0]);
  int i;

  for (i = 0; i < n; i++) {
    if (strcmp(word, opcodes[i]) == 0) {
      return OPCODE;
    }
  }

  if (*word == '@') {
    return LABEL;
  }

  if (('0' <= *word && *word <= '9') || *word == '-') {
    return IMMEDIATE;
  }

  return VARIABLE;
}

int getTokens(int fd, struct LexToken *tokens) {
  int n = 0;
  char line[128];
  while (!readline(fd, line, sizeof(line))) {
    char word[16];
    char *l = line;

    while (*l != '\0') {
      enum TokenType type;
      l = getword(l, word, sizeof(word));

      if (*word == ';') {
        break;
      }

      type = toktype(word);

      tokens[n].type = type;

      strcpy(tokens[n].token.tokstr, word);
      if (type == IMMEDIATE) {
        tokens[n].token.tokint = atoi(word);
      }
      n++;
    }
  }
  return n;
}

#ifdef LEXER_MAIN
int main(void) {
  int fd = open("test.broas", O_RDONLY);
  struct LexToken tokens[1024] = {0};
  int n = getTokens(fd, tokens);
  int i = 0;

  for (i = 0; i < n; i++) {
    if (tokens[i].type == IMMEDIATE) {
      printf("<IMMEDIATE, %d>\n", tokens[i].token.tokint);
    } else if (tokens[i].type == LABEL) {
      printf("<LABEL, %s>\n", tokens[i].token.tokstr);
    } else if (tokens[i].type == VARIABLE) {
      printf("<VARIABLE, %s>\n", tokens[i].token.tokstr);
    } else if (tokens[i].type == OPCODE) {
      printf("<OPCODE, %s>\n", tokens[i].token.tokstr);
    } else {
      puts("<UNKNOWN>");
    }
  }

  close(fd);
  return 0;
}
#endif
