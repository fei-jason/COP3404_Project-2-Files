/*********************************************
*        DO NOT REMOVE THIS MESSAGE
*
* This file is provided by Professor Littleton
* to assist students with completing Project 2.
*
*        DO NOT REMOVE THIS MESSAGE
**********************************************/

#include "headers.h"

#define SINGLE_QUOTE 39

enum directives {
	ERROR, BASE, BYTE, END, RESB, RESW, START, WORD
};

int getMemoryAmount(int directiveType, char* string)
{
	int bytes = 0;
	int decimal = 0;
	char hexString[8];
	switch(directiveType) {
		case BASE:
			return bytes;
		case END:
			return bytes;
		case START:
			return bytes;
		case BYTE:
			if (strstr(string, "X") != NULL) {
				char *token = strtok(string, "'");
				token = strtok(NULL, "'");
				if (token[0] < '0' || token[0] > 'F' ) {
					//ERROR 
				}
				if(token[1] < '0' || token[1] > 'F') {
					//ERROR
				}
				return bytes + 1;
			} else {
				//something is wrong when C'SIZE > 5'
				char *token = strtok(string, "'");
				token = strtok(NULL, "'");
				return strlen(token);
			}
		case RESW:
			return 3 * atoi(string);
		case RESB:
			//decimal = strtol(string, NULL, 10);
			//snprintf(hexString, 8, "%x", decimal);
			return atoi(hexString);
		case WORD:
			return bytes + 3;
	}
}

int isDirective(char* string) 
{
	if (strcmp(string, "BASE") == 0) { return BASE; }
	else if (strcmp(string, "BYTE") == 0) { return BYTE; }
	else if(strcmp(string, "END") == 0) { return END; }
	else if (strcmp(string, "RESB") == 0) { return RESB; }
	else if (strcmp(string, "RESW") == 0) { return RESW; }
	else if (strcmp(string, "START") == 0) { return START; }
	else if (strcmp(string, "WORD") == 0) { return WORD; }
	else { return ERROR; }
}

bool isStartDirective(int directiveType)
{
	return directiveType == START ? true : false;
}