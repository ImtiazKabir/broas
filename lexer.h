#ifndef LEXER_H_
#define LEXER_H_

#define MX_TOK_SZ 32

enum TokenType { LABEL, OPCODE, VARIABLE, IMMEDIATE };

struct LexToken {
  enum TokenType type;
  union {
    long int tokint;
    char tokstr[MX_TOK_SZ];
  } token;
};

int getTokens(int fd, struct LexToken *tokens);

#endif /* !LEXER_H_ */
