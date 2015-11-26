/*
 * util.h
 *
 *  Created on: Sep 18, 2015
 *      Author: vuvantu
 */
#ifndef UTILS_H_
#define UTILS_H_
#define MAX_IDENT_LEN 30
#define NUM_KEYWORD 17
#define NUM_TOKENTYPE 41

#include <string.h>
#include <stdio.h>
enum TokenType { NONE = 0, IDENT, NUMBER,
				BEGIN, CALL, CONST, DO, ELSE, END, FOR, IF,
				ODD, PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
				PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ,
				GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK,
				PERIOD, COMMA, SEMICOLON, ASSIGN, PERCENT, HOICHAM, HAICHAM, REPEAT, UNTIL  };

const char* tokenTypeChar [NUM_TOKENTYPE] = {"NONE", "IDENT", "NUMBER",
											"BEGIN", "CALL", "CONST", "DO", "ELSE", "END", "FOR", "IF",
											"ODD", "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE",
											"PLUS", "MINUS", "TIMES", "SLASH", "EQU", "NEQ", "LSS", "LEQ",
											"GTR", "GEQ", "LPARENT", "RPARENT", "LBRACK", "RBRACK",
											"PERIOD", "COMMA", "SEMICOLON", "ASSIGN", "PERCENT",
											"HOICHAM", "HAICHAM", "REPEAT", "UNTIL"};
const char* keywords[NUM_KEYWORD] = {"begin" , "end", "if", "then", "while", "do", "call", "odd",
									"to", "const", "var","procedure", "program", "else", "for", "repeat", "until"};

int isLetter(char ch){
	if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return 1;
	return 0;
}
int isDigit(char ch){
	if( ch >= '0' && ch <= '9')
		return 1;
	return 0;
}
int pow(int x, int n){
	if(n < 0) {
		printf("error in pow() function: n < 0\n");
		return -1;
	}
	if(n == 0 ) return 1;
	return x * pow(x, n-1);
}
int string2int(char *s){
	int i = 0;
	int value = 0;
	while(s[i] != '\0'){
		value += (s[i] - '0') * pow(10, i);
		i += 1;
	}
	return value;
}
/*
 * Neu ident la keyword tra ve so thu tu cua keyword
 */
int isKeyword(const char *string_1){
//	printf("In isKeyword, string = %s\n", string);
	char string[30];
	strcpy(string, string_1);
	for(unsigned int i = 0; i < strlen(string); i++){
		if(string[i] >= 'A' && string[i] <= 'Z'){
			string[i] += 'a' - 'A';
		}
	}
	int r = 0;
	for(int i = 0; i < NUM_KEYWORD; i++){
		if(strcmp(string, keywords[i]) == 0){
			r = 1;
			break;
		}
	}
	return r;
}
TokenType getTokenType(const char* string_1){
//	printf("In gettokentype, string = %s\n", string);
	char string[30];
	strcpy(string, string_1);
	for(unsigned int i = 0; i < strlen(string); i++){
		if(string[i] >= 'A' && string[i] <= 'Z'){
			string[i] += 'a' - 'A';
		}
	}
	if(strcmp(string, "begin") == 0)
		return BEGIN;
	if(strcmp(string, "end") == 0)
		return END;
	if(strcmp(string, "if") == 0)
		return IF;
	if(strcmp(string, "then") == 0)
		return THEN;
	if(strcmp(string, "while") == 0)
		return WHILE;
	if(strcmp(string, "do") == 0)
		return DO;
	if(strcmp(string, "call") == 0)
		return CALL;
	if(strcmp(string, "odd") == 0)
		return ODD;
	if(strcmp(string, "to") == 0)
		return TO;
	if(strcmp(string, "const") == 0)
		return CONST;
	if(strcmp(string, "var") == 0)
		return VAR;
	if(strcmp(string, "procedure") == 0)
		return PROCEDURE;
	if(strcmp(string, "program") == 0)
		return PROGRAM;
	if(strcmp(string, "for") == 0)
		return FOR;
	if(strcmp(string, "else") == 0)
		return ELSE;
	if(strcmp(string, "repeat") == 0)
		return REPEAT;
	if(strcmp(string, "until") == 0)
		return UNTIL;
	return NONE;
}
void error_display(const char *); //display an error message
void program();
void block();
void statement();
void expression();
void condition();
void term();
void factor();

typedef enum {
	OP_LA, //Load address
	OP_LV, //Load value
	OP_LC, //Load constant
	OP_LI, //Load indirect
	OP_INT, //Increment T
	OP_DCT, //Decrement T
	OP_J, //Jump
	OP_FJ, //False jump
	OP_HL, //Halt
	OP_ST, //Store
	OP_CALL, //Call
	OP_EP, //exit procedure
	OP_EF, //exit function
	OP_RC, //read character
	OP_RI, //read integer
	OP_WRC, //write character
	OP_WRI, //write integer
	OP_WLN, //write LN
	OP_ADD, //add
	OP_SUB, //subtract
	OP_MUL, //mul
	OP_DIV, //div
	OP_NEG, //negative
	OP_CV, //copy top
	OP_EQ, //equal
	OP_NE, //not equal
	OP_GT, //greater
	OP_LT, //less
	OP_GE, //greater or equal
	OP_LE, //less or equal
	OP_BP, //break point
} OpCode;
typedef struct {
	OpCode op;
	char op_str[4];
	int p;
	int q;
} Instruction;
#endif /* UTILS_H_ */
