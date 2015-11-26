/*
 * parser.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: vuvantu
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


TokenType token;
int line_num = 0;
int num;
char ident[MAX_IDENT_LEN + 1];
char ch;
char filename[30] ;//=  "inputFile/prog1.PL0";
int i;
FILE* reader;
void open(char* filename){
	reader = fopen(filename, "r");
	return ;
}
void close(char* filename){
	fclose(reader);
	return ;
}
char getCHAR(){
	char c = fgetc(reader);
//	printf("%c ", c);
	return c;
}
TokenType getToken(){
	if(ch == ' ' || ch == '\t' || ch == '\n'){
		if(ch == '\n') line_num += 1;
		while(ch == ' ' || ch == '\t' || ch == '\n'){
			ch = getCHAR();
			if(ch == '\n') line_num += 1;
		}
	}
	if(isLetter(ch)){
		i = 0;
		ident[i] = ch;
		while(1) {
			ch = getCHAR();
			if(isLetter(ch) || isDigit(ch)){
				i += 1;
				ident[i] = ch;
			}
			else{
				break;
			}
		}
		ident[i+1] = '\0';
		if(i > MAX_IDENT_LEN){
			printf("Ident %s qua dai, khong hop le\n", ident);
			return NONE;
		}
		if(isKeyword(ident)){
			printf("%s - %s\n", ident, tokenTypeChar[getTokenType(ident)]);
			return getTokenType(ident);
		}
		else{
			printf("%s - %s\n", ident, tokenTypeChar[IDENT]);
			return IDENT;
		}
	}
	if(isDigit(ch)){
		i = 0;
		ident[i] = ch;
		while(1){
			ch = getCHAR();
			if(isDigit(ch)){
				i += 1;
				ident[i] = ch;
			}
			else{
				break;
			}
		}
		ident[i+1] = '\0';
		num = string2int(ident);
		printf("%s - %s\n", ident, tokenTypeChar[NUMBER]);
		return NUMBER;
	}
	if(ch == '+'){
		ch = getCHAR();
		ident[0] = '+';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PLUS]);
	return PLUS;
	}
	if(ch == '*'){
		ch = getCHAR();
		ident[0] = '*';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[TIMES]);
		return TIMES;
	}
	if(ch == '-'){
		ch = getCHAR();
		ident[0] = '-';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[MINUS]);
		return MINUS;
	}
	if(ch == '/'){
		ch = getCHAR();
		printf("%s - %s\n", ident, tokenTypeChar[SLASH]);
		return SLASH;
	}
	if(ch == '%'){
		ch = getCHAR();
		ident[0] = '%';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PERCENT]);
		return PERCENT;
	}
	if(ch == '='){
		ch = getCHAR();
		ident[0] = '=';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[EQU]);
		return EQU;
	}
	if(ch == '<'){
		ch = getCHAR();
		if(ch == '>'){
			ch = getCHAR();
			ident[0] = '<';
			ident[1] = '>';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[NEQ]);
			return NEQ;
		}
		else if (ch == '='){
			ch = getCHAR();
			ident[0] = '<';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[LEQ]);
			return LEQ;
		}
		else
			ident[0] = '<';
			ident[1] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[LSS]);
			return LSS;
	}
	if(ch == '>'){
		ch = getCHAR();
		if(ch == '='){
			ch = getCHAR();
			ident[0] = '>';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[GEQ]);
			return GEQ;
		}
		else
			ident[0] = '>';
			ident[1] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[GTR]);
			return GTR;
	}
	if(ch == '('){
		ch = getCHAR();
		ident[0] = '(';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[LPARENT]);
		return LPARENT;
	}
	if(ch == ')'){
		ch = getCHAR();
		ident[0] = ')';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[RPARENT]);
		return RPARENT;
	}
	if(ch == '['){
		ident[0] = '[';
		ident[1] = '\0';
		ch = getCHAR();
		printf("%s - %s\n", ident, tokenTypeChar[LBRACK]);
		return LBRACK;
	}
	if(ch == ']'){
		ch = getCHAR();
		ident[0] = ']';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[RBRACK]);
		return RBRACK;
	}
	if(ch == '.'){
		ch = getCHAR();
		ident[0] = '.';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PERIOD]);
		return PERIOD;
	}
	if(ch == ','){
		ch = getCHAR();
		ident[0] = ',';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[COMMA]);
		return COMMA;
	}
	if(ch == ';'){
		ch = getCHAR();
		ident[0] = ';';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[SEMICOLON]);
		return SEMICOLON;
	}
	if(ch == ':'){
		ch = getCHAR();
		if(ch == '='){
			ch = getCHAR();
			ident[0] = ':';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[ASSIGN]);
			return ASSIGN;
		}
		else {
			ident[0] = ':';
			ident[1] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[HAICHAM]);
			return HAICHAM;

		}
		printf("%s - %s\n", ident, tokenTypeChar[NONE]);
		return NONE;
	}
	if(ch == '?'){
		ch = getCHAR();
		ident[0] = '?';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[HOICHAM]);
		return HOICHAM;
	}
	printf("%s - %s\n", ident, tokenTypeChar[NONE]);
	return NONE;
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("USAGE: PL0_COMPILE filename\n");
		exit(1);
	}
	strcpy(filename, argv[1]);
	open(filename);
	ch = ' ';
	token = getToken();
	program();
	close(filename);
	return 0;
}
void program(){
	if(token == PROGRAM){
		token = getToken();
		if(token == IDENT){
			token = getToken();
			if(token == SEMICOLON){
				token = getToken();
				block();
				if(token == PERIOD){
					printf("Thanh cong!\n");
				}
				else{
					error_display("[In program] Thieu dau cham.\n");
				}
			}
			else{
				error_display("[In program] Thieu dau cham phay.\n");
			}
		}
		else {
			error_display("[In program] Thieu ten chuong trinh.\n");
		}
	}
	else {
		error_display("Thieu tu khoa PROGRAM.\n");
	}
	return ;
}
void block(){
	switch (token) {
	case CONST:
		do{
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token ==EQU){
					token = getToken();
					if(token == NUMBER){
						token = getToken();
					}
					else{
						error_display("[in block -> CONST] Thieu so sau trong bieu thuc.\n");
					}
				}
				else{
					error_display("[in block -> CONST] Thieu dau bang sau dinh danh.\n");
				}
			}
			else {
				error_display("[in block > CONST] Thieu ten.\n");
			}
		} while(token == COMMA);

		if(token == SEMICOLON){
			token = getToken();
			block();
		}
		else{
			error_display("[in block] Thieu dau cham phay ket thuc khai bao CONST.\n");
		}
		break;
	case VAR:
		do {
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == LBRACK){
					token = getToken();
					if(token == NUMBER){
						token = getToken();
						if(token == RBRACK){
							token = getToken();
						}
						else{
							error_display("[in block -> VAR] Thieu dong ngoac vuong sau khai bao mang.\n");
						}
					}
					else{
						error_display("[in block -> VAR] Thieu so trong khai bao mang.\n");
					}
				}

			}
			else{
				error_display("[in block -> VAR] Thieu dinh danh.\n");
			}
		}
		while(token == COMMA);

		if(token == SEMICOLON){
			token = getToken();
			block();
		}
		else{
			error_display("[in block -> VAR] Thieu dau cham phay sau khai bao bien.\n");
		}
		break;
	case PROCEDURE:
		token = getToken();
		if(token == IDENT){
			token = getToken();
			if(token == LPARENT){
				do {
					token = getToken();
					if(token == VAR){
						token = getToken();
					}
					if(token == IDENT){
						token = getToken();
					}
					else{
						error_display("[in block -> PROCEDURE] Thieu ten bien trong khai bao thu tuc.\n");
					}
				} while(token == SEMICOLON);
				if(token == RPARENT){
					token = getToken();
				}
				else{
					error_display("[in block -> PROCEDURE] Thieu dau dong ngoac.\n");
				}
			}

			if(token == SEMICOLON){
				token = getToken();
				block();
				if(token == SEMICOLON){
					token = getToken();
					block();
				}
				else{
					error_display("[in block -> PROCEDURE] Thieu dau cham phay sau khoi block.\n");
				}
			}
			else{
				error_display("[in block -> PROCEDURE] Khoi PROCEDURE sai.\n");
			}
		}
		else{
			error_display("[in block -> PROCEDURE] Thieu ten thu tuc.\n");
		}
		break;
	case BEGIN:
		token = getToken();
		statement();

		while(token == SEMICOLON){
			token = getToken();
			statement();
		}
		if(token == END){
			token = getToken();
		}
		else{
			error_display("[in block -> BEGIN] Thieu END.\n");
		}
		break;

	default:
		error_display("[in block] Block begin error.\n");
		break;
	}//end switch case

	return ;
}
void statement(){
	printf("call statement, token = %s.\n", ident);
	switch (token) {
		case IDENT:
			token = getToken();
			if(token == LBRACK){
				token = getToken();
				expression();
				if(token == RBRACK){
					token = getToken();
				}
				else{
					error_display("[in statement -> IDENT] Thieu dau dong ngoac vuong.\n");
				}
			}
			if(token == ASSIGN){
				token = getToken();
				expression();
				if(token == EQU || token == GTR || token == GEQ
						|| token == LSS || token == LEQ || token == NEQ){
					token = getToken();
					expression();
					if(token == HOICHAM){
						token = getToken();
						expression();
						if(token == HAICHAM){
							token = getToken();
							expression();
						}
						else{
							error_display("[in statement -> IDENT] Bieu thuc gan sai.\n");
						}
					}
					else{
						error_display("[in statement -> IDENT] Bieu thuc gan sai.\n");
					}
				}
			}
			else {
				error_display("[in statement -> IDENT] Thieu dau gan.\n");
			}
			break;
		case CALL:
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == LPARENT){
					do {
						token = getToken();
						expression();
					}
					while(token == COMMA);
					if(token == RPARENT){
						token = getToken();
					}
					else{
						error_display("[in statement -> CALL] Thieu dau dong ngoac.\n");
					}
				}
			}
			else {
				error_display("[in statement -> CALL] Thieu ten thu tuc khi goi.\n");
			}
			break;
		case BEGIN:
			token = getToken();
			statement();
			while(token == SEMICOLON){
				token = getToken();
				statement();
			}
			if(token == END){
				token = getToken();
			}
			else{
				error_display("[in statement -> BEGIN] Thieu END.\n");
			}
			break;
		case IF:
			token = getToken();
			condition();
			if(token == THEN){
				token = getToken();
				statement();
			}
			else{
				error_display("[in statement -> IF] Thieu Then sau if.\n");
			}
			break;
		case WHILE:
			token = getToken();
			condition();
			if(token == DO){
				token = getToken();
				statement();
			}
			else{
				error_display("[in statement -> WHILE] Thieu DO sau WHILE.\n");
			}
			break;
		case FOR:
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == ASSIGN){
					token = getToken();
					expression();
					if(token == TO){
						token = getToken();
						expression();
						if(token == DO){
							token = getToken();
							statement();
						}
						else{
							error_display("[in statement -> FOR] Thieu DO.\n");
						}
					}
					else {
						error_display("[in statement -> FOR] Thieu TO.\n");
					}
				}
				else {
					error_display("[in statement -> FOR] Thieu phep gan.\n");
				}
			}
			else if (token == LPARENT){
				token = getToken();
				if(token == IDENT){
					token = getToken();
					if(token == ASSIGN){
						token = getToken();
						expression();
						if(token == SEMICOLON){
							token = getToken();
							condition();
							if(token == SEMICOLON){
								token = getToken();
								if(token == IDENT){
									token = getToken();
									if(token == ASSIGN){
										token = getToken();
										expression();
										if(token == RPARENT){
											token = getToken();
											statement();
										}
										else{
											error_display("[in stament -> FOR 2] Bieu thuc sai.\n");
										}
									}
									else{
										error_display("[in stament -> FOR 2] Bieu thuc sai.\n");
									}
								}
								else{
									error_display("[in stament -> FOR 2] Bieu thuc sai.\n");
								}
							}
							else{
								error_display("[in stament -> FOR 2] Bieu thuc sai.\n");
							}
						}
						else {
							error_display("[in stament -> FOR 2] Bieu thuc sai.\n");
						}
					}
					else{
						error_display("[in statement -> FOR 2] Thieu phep gan.\n");
					}
				}
				else {
					error_display("[instatement -> FOR 2] Thieu ten bien.\n");
				}
			}
			else{
				error_display("[in statement -> FOR] Thieu ten bien.\n");
			}
			break;
			/*
			 * REPEAT [BEGIN] Stm, stm,..[END](neu co >= 2 cau lenh) hoac stm (neu co 1 cau lenh)
			 * UNTIL
			 */
		case REPEAT:
			if(token == BEGIN){
				token = getToken();
				statement();
				while(token == SEMICOLON){
					token = getToken();
					statement();
				}
				if(token == END){
					token = getToken();
				}
				else {
					error_display("[in statement -> REPEAT] Thieu END.\n");
				}
			}
			else {
				token = getToken();
				statement();
			}
			if(token == UNTIL){
				token = getToken();
				condition();
			}
			else {
				error_display("[in statement -> REPEAT] Thieu tu khoa UNTIL.\n");
			}
			break;
		default:
			//error_display("[in statement] Khoi statement sai.\n");
			break;
	}

	return ;
}
void condition(){
	printf("call condition.\n");
	if(token == ODD){
		token = getToken();
		expression();
		return ;
	}
	expression();
	if(token == EQU || token == GTR || token == GEQ
			|| token == LSS || token == LEQ || token == NEQ){
		token = getToken();
		expression();
	}
	else {
		error_display("[in condition -> expression] Bieu thuc dieu kien khong hop le.\n");
	}
	return;
}
void expression(){
	printf("call expression.\n");
	if(token == PLUS || token == MINUS){
		token = getToken();
	}
	term();
	while(token == PLUS || token == MINUS){
		token = getToken();
		term();
	}
	return ;
}
void term(){
	printf("call term.\n");
	factor();
	while(token == TIMES || token == PERCENT || token == SLASH){
		token = getToken();
		factor();
	}
//	token = getToken();
	return;
}
void factor(){
	printf("call factor.\n");
	switch (token) {
		case IDENT:
			token = getToken();
			if(token == LBRACK){
				token = getToken();
				expression();
				if(token == RBRACK){
					token = getToken();
				}
				else {
					error_display("[in factor -> IDENT] Thieu dong ngoac vuong.\n");
				}
			}
			break;
		case NUMBER:
			token = getToken();
			break;
		case LPARENT:
			token = getToken();
			expression();
			if(token == RPARENT){
				token = getToken();
			}
			else {
				error_display("[in factor] Thieu dau dong ngoac.\n");
			}
			break;
		default:
			error_display("[in factor] Khoi factor sai.\n");
			break;
	}
	return;
}
void error_display(const char* err_msg){
	printf("Line number %d, %s",line_num, err_msg);
	close(filename);
	exit(-1);
	return;
}
