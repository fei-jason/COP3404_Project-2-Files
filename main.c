#include "headers.h"

#define COMMENT 35
#define INPUT_BUF_SIZE 60
#define NEW_LINE 10
#define SPACE 32
#define SYMBOL_TABLE_SIZE 100

void performPass1(symbol* symbolTable[], char* filename, address* addresses);
struct segment* prepareSegments(char* line);
void trim(char string[]);

int main(int argc, char* argv[])
{
	// Do not modify this statement
	address addresses = { 0x00, 0x00, 0x00 };

	// Check whether at least one (1) input file was provided
	

	// Create the symbol table for storing the symbol data
	symbol* symbolTable[SYMBOL_TABLE_SIZE];
	initializeSymbolTable(symbolTable);

	// Perform Pass 1: read records from input file and load symbol data into the symbol table
	performPass1(symbolTable, argv[1], &addresses);

	// Display the symbol data contained in the symbol table
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
		if (symbolTable[i] != NULL) { 
			printf("Name: %s Address: %x\n", symbolTable[i]->name, symbolTable[i]->address);
		}
	}
	// Display the assembly summary data
	
}

void performPass1(symbol* symbolTable[], char* filename, address* addresses)
{
	FILE* ptr;
	char record[INPUT_BUF_SIZE];
	symbol symbol;
	address address;

	ptr = fopen(filename, "r");
	if (ptr == NULL){
		//perform error handling here
		
		exit(1);
	}

	printf("%-10s", "Symbol Table Log\n");
	for (int i = 0; i < 25; i++) {
		printf("-");
	}
	printf("\n");

	// //check PC address
	// fgets(record, INPUT_BUF_SIZE, ptr);
	// strtok(record, " ");
	// strtok(NULL, " ");
	// pcAddress = atof(strtok(NULL, " "));

	// printf("\n\n-----------------------%d", pcAddress);

	while (fgets(record, INPUT_BUF_SIZE, ptr) != NULL) {
		if (record[0] != '#') {

			if (record[0] < 32) {
				//display BLANK_RECORD 
			}

			segment* newSeg = prepareSegments(record);
			//printf("%s %s %s\n", newSeg->label, newSeg->operation, newSeg->operand);

			if (isDirective(newSeg->label) > 0 || isOpcode(newSeg->operation) > 0) {
				//display ILLEGAL_SYMBOL
			}

			int dirType = isDirective(newSeg->operation);
			if (isStartDirective(dirType)) {
				//address.start = atoi(newSeg->operand);
				address.start = strtol(newSeg->operand, NULL, 16);
				address.current = strtol(newSeg->operand, NULL, 16);
				address.increment = 0x0000;
				//address.current = atoi(newSeg->operand);
				printf("STARTING ---- %x and %x\n", address.start, address.current);
			} else if (dirType != 0) {
				address.increment = getMemoryAmount(dirType, newSeg->operand);
				printf("dirType %x, INCREMENT ---- %d\n", dirType, address.increment);
			} else {
				//display ILLEGAL_OPCODE_DIRECTIVE 
			}

			if (isOpcode(newSeg->operation)) {
				address.increment = getOpcodeFormat(newSeg->operation);
				printf("newSeg->operation %s, INCREMENT ---- %d\n", newSeg->operation, address.increment);
			} else {
				//display ILLEGAL_OPCODE_DIRECTIVE 
			}

			if (strlen(newSeg->label) > 0 && strcmp(newSeg->label, "FIRST") != 0) {
				insertSymbol(symbolTable, newSeg->label, address.current);
			}
			
			address.current += address.increment;
			printf("Current: %x increment: %d\n", address.current, address.increment);

		}
		memset(record, '\0', sizeof(record));
	}
	fclose(ptr);
}

// Do no modify any part of this function
segment* prepareSegments(char* statement)
{
	struct segment* temp = malloc(sizeof(segment));
	strncpy(temp->label, statement, SEGMENT_SIZE - 1);
	strncpy(temp->operation, statement + SEGMENT_SIZE - 1, SEGMENT_SIZE - 1);
	strncpy(temp->operand, statement + (SEGMENT_SIZE - 1) * 2, SEGMENT_SIZE - 1);

	trim(temp->label); // Label
	trim(temp->operation); // Operation
	trim(temp->operand); // Operand
	return temp;
}

// Do no modify any part of this function
void trim(char value[])
{
	for (int x = 0; x < SEGMENT_SIZE; x++)
	{
		if (value[x] == SPACE)
		{
			value[x] = '\0';
		}
	}
}