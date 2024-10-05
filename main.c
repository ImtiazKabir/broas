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

#define MAX_VARIABLES 100

#define MEMORY_SIZE 1024

struct Label {
	char *name;
	int instructionIndex;
};

struct Variable {
	char *name;
	int value;
};

int getValue(struct LexToken valueToken, struct Variable *variables, int numberOfVariables, struct Label *labels, int numberOfLabels);
void setValue(struct LexToken variableToken, int value, struct Variable *variables, int *pNumberOfVariables);

int main(void) {
	int fd;

	struct LexToken instructions[MAX_INSTRUCTIONS][MAX_TOKENS_IN_LINE];
	struct LexToken tokens[MAX_TOKENS_IN_FILE];
	int totalTokens;
	int nextInstruction = 0;
	int totalInstructions;

	struct Label labels[MAX_LABELS];
	int nextLabel = 0;

	struct Variable variables[MAX_VARIABLES];
	int nextVariable = 0;

	int memory[MEMORY_SIZE];

	int i;

	fd = open("test.broas", O_RDONLY);

	totalTokens = getTokens(fd, tokens);

	i = 0;
	while (i < totalTokens) {
		struct LexToken lexToken = tokens[i++];

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
				instructions[nextInstruction][1] = tokens[i++];
			}
			else {
				fprintf(stderr, "Unknown operation %s\n", lexToken.token.tokstr);
				exit(1);
			}

			++nextInstruction;
		}

		else if (lexToken.type == LABEL) {
			labels[nextLabel].name = tokens[i - 1].token.tokstr;
			labels[nextLabel].instructionIndex = nextInstruction;
			++nextLabel;
		}

		else {
			fprintf(stderr, "Unexpected token %s in place of opcode or label, (encountered at %dth token position)\n", lexToken.token.tokstr, i);
			exit(1);
		}
	}

	totalInstructions = nextInstruction;
	nextInstruction = 0;

	while (nextInstruction < totalInstructions) {
		struct LexToken *instruction = instructions[nextInstruction];
		char *opcode = instruction[0].token.tokstr;

		if (strcmp(opcode, "add") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand + rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "sub") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand - rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "lw") == 0) {
			int memoryOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);

			setValue(instruction[1], memory[memoryOperand], variables, &nextVariable);
		}

		else if (strcmp(opcode, "sw") == 0) {
			int variableOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int memoryOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);

			memory[memoryOperand] = variableOperand;
		}

		else if (strcmp(opcode, "mult") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand * rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "div") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand / rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "beq") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand == rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "bneq") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand != rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "mod") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand % rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "xor") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand ^ rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "or") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand | rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "and") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand & rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "not") == 0) {
			int operand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int result = ~operand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "sl") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand << rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "sr") == 0) {
			int leftOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			int result = leftOperand >> rightOperand;

			setValue(instruction[1], result, variables, &nextVariable);
		}

		else if (strcmp(opcode, "blt") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand < rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "bgt") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand > rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "ble") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand <= rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "bge") == 0) {
			int leftOperand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			int rightOperand = getValue(instruction[2], variables, nextVariable, labels, nextLabel);
			int branchAddress = getValue(instruction[3], variables, nextVariable, labels, nextLabel);
			
			if (leftOperand >= rightOperand) {
				nextInstruction = branchAddress;
				continue;
			}
		}

		else if (strcmp(opcode, "jmp") == 0) {
			int jumpAddress = getValue(instruction[1], variables, nextVariable, labels, nextLabel);

			nextInstruction = jumpAddress;
			continue;
		}

		else if (strcmp(opcode, "print") == 0) {
			int operand = getValue(instruction[1], variables, nextVariable, labels, nextLabel);

			printf("%c", operand);
		}

		else if (strcmp(opcode, "scan") == 0) {
			int c = getchar();

			setValue(instruction[1], c, variables, &nextVariable);
		}

		else if (strcmp(opcode, "exit") == 0) {
			int exitCode = getValue(instruction[1], variables, nextVariable, labels, nextLabel);
			exit(exitCode);
		}

		else {
			printf("Unknown operation %s\n", opcode);
		}
		
		++nextInstruction;
	}

	close(fd);
	return 0;
}

int getValue(struct LexToken valueToken, struct Variable *variables, int numberOfVariables, struct Label *labels, int numberOfLabels) {
	if (valueToken.type == IMMEDIATE) return valueToken.token.tokint;
	else if (valueToken.type == VARIABLE) {
		int i;
		for (i = 0; i < numberOfVariables; ++i) {
			if (strcmp(variables[i].name, valueToken.token.tokstr) == 0) {
				return variables[i].value;
			}
		}
	}
	else if (valueToken.type == LABEL) {
		int i;
		for (i = 0; i < numberOfLabels; ++i) {
			if (strcmp(labels[i].name, valueToken.token.tokstr) == 0) {
				return labels[i].instructionIndex;
			}
		}
	}
	else {
		fprintf(stderr, "Cannot get value of %s, (can only access value of a variable or immediate or label)\n", valueToken.token.tokstr);
	}
	exit(1);
}

void setValue(struct LexToken variableToken, int value, struct Variable *variables, int *pNumberOfVariables) {
	int i;
	
	if (variableToken.type != VARIABLE) {
		fprintf(stderr, "Can only set value of a variable\n");
		exit(1);
	}

	for (i = 0; i < *pNumberOfVariables; ++i) {
		if (strcmp(variables[i].name, variableToken.token.tokstr) == 0) {
			variables[i].value = value;
			return;
		}
	}

	variables[*pNumberOfVariables].name = variableToken.token.tokstr;
	variables[*pNumberOfVariables].value = value;
	++(*pNumberOfVariables);
}
