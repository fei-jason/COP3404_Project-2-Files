/*********************************************
*        DO NOT REMOVE THIS MESSAGE
*
* This file is provided by Professor Littleton
* to assist students with completing Project 2.
*
*        DO NOT REMOVE THIS MESSAGE
**********************************************/

#include "headers.h"

void displayError(int errorType, char* errorInfo)
{
	switch (errorType) {
        case BLANK_RECORD:
            printf("ERROR: Source File Contains Blank Lines");
            break;
        case DUPLICATE:
            printf("ERROR: Duplicate Symbol Name (%s) Found in Source File", errorInfo);
            break; 
        case FILE_NOT_FOUND:
            printf("ERROR: The Program is Unable to Open the Provided Input (%s)", errorInfo);
            break; 
        case ILLEGAL_OPCODE_DIRECTIVE:
            printf("ERROR: Illegal Opcode or Directive (%s) Found in Source File", errorInfo);
            break;
        case ILLEGAL_SYMBOL:
            printf("ERROR: Symbol Name (%s) Cannot be a Command or Directive", errorInfo);
            break; 
	    case MISSING_COMMAND_LINE_ARGUMENTS:
            printf("ERROR: Missing Command Line Arguments. ");
            break;
        case OUT_OF_MEMORY:
            printf("ERROR: Program Address (%s) Exceeds Maximum Memory Address [0x100000]", errorInfo);
            break; 
        case OUT_OF_RANGE_BYTE:
            printf("ERROR: Byte Value (%s) Out of Range [00 to FF]", errorInfo);
            break;
        case OUT_OF_RANGE_WORD:
            printf("ERROR: Word Value (%s) Out of Range [-8,388,608 to 8,388,607]", errorInfo);
            break;
        default:
            break;
    }
}