#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"

#define MAX_TOKENS_IN_FILE 1024
#define MAX_TOKENS_IN_LINE 5
#define MAX_INSTRUCTIONS 100

#define MAX_LABELS 100

struct Label {
	char *name;
	int instructionIndex;
};

int main(void) {
	int fd;

	struct LexToken instructions[MAX_INSTRUCTIONS][MAX_TOKENS_IN_LINE];
	struct LexToken tokens[MAX_TOKENS_IN_FILE];
	int totalTokens;
	int nextInstruction = 0;
	
	struct Label labels[MAX_LABELS];
	int nextLabel = 0;

	int i;

	fd = open("test.broas", O_RDONLY);

	totalTokens = getTokens(fd, tokens);

	for (i = 0; i < totalTokens; ++i) {
		struct LexToken lexToken = tokens[i];

		if (lexToken.type == OPCODE) {
			instructions[nextInstruction][0] = lexToken;

			if (strcmp(lexToken.token.tokstr, "add") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "sub") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "lw") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "sw") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "mult") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "div") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "beq") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "bneq") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "mod") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "xor") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "or") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "and") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "not") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "sl") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "sr") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "blt") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "bgt") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "ble") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "bge") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
				instructions[nextInstruction][2] = tokens[i++];
				instructions[nextInstruction][3] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "jmp") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "print") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "scan") == 0) {
				instructions[nextInstruction][1] = tokens[i++];
			}
			else if (strcmp(lexToken.token.tokstr, "exit") == 0) {
			}
			else {
				fprintf(stderr, "Unknown operation %s\n", lexToken.token.tokstr);
				exit(1);
			}
		
			++nextInstruction;

		}

		else if (lexToken.type == LABEL) {
			labels[nextLabel].name = lexToken.token.tokstr;
			labels[nextLabel].instructionIndex = nextInstruction;
			++nextLabel;
		}

		else {
			fprintf(stderr, "Unexpected token %s in place of opcode or label\n", lexToken.token.tokstr);
			exit(1);
		}
	}

	close(fd);
	return 0;
}
