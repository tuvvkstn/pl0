#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

using namespace std;

#define MAX_CODE 1000
#define MAX_DATA 1000
Instruction code[MAX_CODE];
int code_length = 0;

int stack[MAX_DATA];
int pc = 0, t = -1, b = 0;

int usr_in_val;

void interpreter();
void display_code();
void display_stack();
int base(int L);
void load_code_from_file(char *filename);
int main(int argc, char* argv[]){
	if(argc != 2){
		printf("usage: ./pl0run filename\n");
		exit(-1);
	}
	load_code_from_file(argv[1]);
	display_code();
	interpreter();
	display_stack();
	return 0;
}

void interpreter(){
	printf("Interpreter...\n");
	pc = 0, t = -1, b = 0;
	int Exit = 0;
	do{
		switch (code[pc].op) {
		case OP_LA: //Load address
			t++;
			stack[t] = base(code[pc].p) + code[pc].q;
			break;
		case OP_LV: //Load value
			t++;
			stack[t] = stack[base(code[pc].p) + code[pc].q];
			break;
		case OP_LC: //Load constant
			t++;
			stack[t] = code[pc].q;
			break;
		case OP_LI: //Load indirect
			stack[t] = stack[stack[t]];
			break;
		case OP_INT: //Increment T
			t += code[pc].q;
			break;
		case OP_DCT: //Decrement T
			t -= code[pc].q;
			break;
		case OP_J: //Jump
			pc = code[pc].q - 1;
			break;
		case OP_FJ: //False jump
			if(stack[t] == 0){
				pc = code[pc].q - 1;
				t --;
			}
			break;
		case OP_HL: //Halt
			printf("Ket thuc chuong trinh.\n");
			Exit = 1;
			break;
		case OP_ST: //Store
			stack[stack[t-1]] = stack[t];
			t -= 2;
			break;
		case OP_CALL: //Call
			stack[t+2] = b;
			stack[t+3] = pc;
			stack[t+4] = base(code[pc].p);
			b = t + 1;
			pc = code[pc].q - 1;
			break;
		case OP_EP: //exit procedure
			t = b - 1;
			pc = stack[b-2] - 1;
			b = stack[b+1];
			break;
		case OP_EF: //exit function
			t = b;
			pc = stack[b+2] - 1;
			b = stack[b+1];
			break;
		case OP_RC: //read character
			printf("Enter a character: ");
			scanf("%d", &usr_in_val);
			stack[stack[t]] = usr_in_val;
			t--;
			break;
		case OP_RI: //read integer
			printf("Enter an integer: ");
			scanf("%d", &usr_in_val);
			stack[stack[t]] = usr_in_val;
			t--;
			break;
		case OP_WRC: //write character
			printf("Output a charater: ");
			printf("%d", stack[t]);
			t--;
			break;
		case OP_WRI: //write integer
			printf("Output an integer: ");
			printf("%d", stack[t]);
			t--;
			break;
		case OP_WLN: //write LN
			printf("\n");
			break;
		case OP_ADD: //add
			t--;
			stack[t] = stack[t] + stack[t+1];
			break;
		case OP_SUB: //subtract
			t--;
			stack[t] = stack[t] - stack[t+1];
			break;
		case OP_MUL: //mul
			t--;
			stack[t] = stack[t] * stack[t+1];
			break;
		case OP_DIV: //div
			t--;
			stack[t] = stack[t] / stack[t+1];
			break;
		case OP_NEG://negative
			stack[t] = - stack[t];
			break;
		case OP_CV: //copy top
			stack[t+1] = stack[t];
			t++;
			break;
		case OP_EQ: //equal
			t--;
			if(stack[t] == stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_NE: //not equal
			t--;
			if(stack[t] != stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_GT: //greater
			t--;
			if(stack[t] > stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_LT: //less
			t--;
			if(stack[t] < stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_GE: //greater or equal
			t--;
			if(stack[t] >= stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_LE: //less or equal
			t--;
			if(stack[t] <= stack[t+1]){
				stack[t] = 1;
			}
			else {
				stack[t] = 0;
			}
			break;
		case OP_BP: //break point
			printf("break point\n");
			break;
		default:
			printf("Error on input instruction opcode.\n");
		}
		pc ++;
	}
	while (Exit == 0);
	return ;
}
int base(int L){
	int c = b;
	while(L > 0){
		c = stack[c+3];
		L--;
	}
	return c;
}
void load_code_from_file(char *filename){
	printf("Loading code from file %s...\n", filename);
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		printf("File %s not found.\n", filename);
		exit(-1);
	}
	char line[30];
	int count = 0;
	while(fgets(line, sizeof(line), fp)){
//		printf("%s", line);
		char* op_code_str;
		char* p_str;
		char* q_str;
		op_code_str = strtok(line, " \n");
//		printf("op_code_str = %s\n",op_code_str);

		if(strcmp(op_code_str, "LA") == 0) {
			code[count].op = OP_LA;
			strcpy(code[count].op_str,"LA");
			p_str = strtok(NULL, " ");
			code[count].p = atoi(p_str);
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "LV") == 0) {
			code[count].op = OP_LV;
			strcpy(code[count].op_str, "LV");
			p_str = strtok(NULL, " ");
			code[count].p = atoi(p_str);
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "LC") == 0) {
			code[count].op = OP_LC;
			strcpy(code[count].op_str, "LC");
			code[count].p = -1;
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "LI") == 0) {
			code[count].op = OP_LI;
			strcpy(code[count].op_str,"LI");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "INT") == 0) {
			code[count].op = OP_INT;
			strcpy(code[count].op_str, "INT");
			code[count].p = -1;
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "DCT") == 0) {
			code[count].op = OP_DCT;
			strcpy(code[count].op_str,"DCT");
			code[count].p = -1;
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "J") == 0) {
			code[count].op = OP_J;
			strcpy(code[count].op_str, "J");
			code[count].p = -1;
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		if(strcmp(op_code_str, "FJ") == 0) {
			code[count].op = OP_FJ;
			strcpy(code[count].op_str , "FJ");
			code[count].p = -1;
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "HLT") == 0) {
			code[count].op = OP_HL;
			strcpy(code[count].op_str , "HL");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "ST") == 0) {
			code[count].op = OP_ST;
			strcpy(code[count].op_str , "ST");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "CALL") == 0) {
			code[count].op = OP_CALL;
			strcpy(code[count].op_str , "CALL");
			p_str = strtok(NULL, " ");
			code[count].p = atoi(p_str);
			q_str = strtok(NULL, " ");
			code[count].q = atoi(q_str);
		}
		else if(strcmp(op_code_str, "EP") == 0) {
			code[count].op = OP_EP;
			strcpy(code[count].op_str , "EP");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "EF") == 0) {
			code[count].op = OP_EF;
			strcpy(code[count].op_str , "EF");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "RC") == 0) {
			code[count].op = OP_RC;
			strcpy(code[count].op_str , "RC");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "RI") == 0) {
			code[count].op = OP_RI;
			strcpy(code[count].op_str , "RI");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "WRC") == 0) {
			code[count].op = OP_WRC;
			strcpy(code[count].op_str , "WRC");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "WRI") == 0) {
			code[count].op = OP_WRI;
			strcpy(code[count].op_str , "WRI");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "WLN") == 0) {
			code[count].op = OP_WLN;
			strcpy(code[count].op_str , "WLN");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "ADD") == 0) {
			code[count].op = OP_ADD;
			strcpy(code[count].op_str , "ADD");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "SUB") == 0) {
			code[count].op = OP_SUB;
			strcpy(code[count].op_str , "SUB");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "MUL") == 0) {
			code[count].op = OP_MUL;
			strcpy(code[count].op_str , "MUL");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "DIV") == 0) {
			code[count].op = OP_DIV;
			strcpy(code[count].op_str , "DIV");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "NEG") == 0) {
			code[count].op = OP_NEG;
			strcpy(code[count].op_str , "NEG");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "CV") == 0) {
			code[count].op = OP_CV;
			strcpy(code[count].op_str , "CV");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "EQ") == 0) {
			code[count].op = OP_EQ;
			strcpy(code[count].op_str , "EQ");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "NE") == 0) {
			code[count].op = OP_NE;
			strcpy(code[count].op_str ,"NE");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "GT") == 0) {
			code[count].op = OP_GT;
			strcpy(code[count].op_str , "GT");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "LT") == 0) {
			code[count].op = OP_LT;
			strcpy(code[count].op_str , "LT");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "GE") == 0) {
			code[count].op = OP_GE;
			strcpy(code[count].op_str , "GE");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "LE") == 0) {
			code[count].op = OP_LE;
			strcpy(code[count].op_str , "LE");
			code[count].p = -1;
			code[count].q = -1;
		}
		else if(strcmp(op_code_str, "BP") == 0) {
			code[count].op = OP_BP;
			strcpy(code[count].op_str , "BP");
			code[count].p = -1;
			code[count].q = -1;
		}
		else {
			printf("Error instruction in input file.\n");
			fclose(fp);
			return ;
		}
		count += 1;
	}
	code_length = count;
	fclose(fp);
	return ;
}
void display_code(){
	printf("Display code read:\n");
	for(int i = 0; i < code_length; i++){
		printf("%s %d %d\n", code[i].op_str, code[i].p, code[i].q);
	}
//	printf("pc = %d\n", pc);
	return ;
}
void display_stack(){
	printf("Display stack...\n");
	for(int i = t; i >= 0; i--){
		printf("%d...%d\n", i, stack[i]);
	}
	return ;
}
