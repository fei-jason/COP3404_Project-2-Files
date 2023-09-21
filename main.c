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
	if (argv[1] == NULL) {
		displayError(MISSING_COMMAND_LINE_ARGUMENTS, NULL);
		return -1;
	}

	// Create the symbol table for storing the symbol data
	symbol* symbolTable[SYMBOL_TABLE_SIZE];
	initializeSymbolTable(symbolTable);

	// Perform Pass 1: read records from input file and load symbol data into the symbol table
	performPass1(symbolTable, argv[1], &addresses);

	// Display the symbol data contained in the symbol table
	displaySymbolTable(symbolTable);

	// Display the assembly summary data
	printf("\n%-10s\n", "Assembly Summary");
	printf("%-10s\n", "----------------");
	printf("Starting Address: 0x%-2x\n", addresses.start);
	printf("Ending Addresses: 0x%-2x\n", addresses.current);
	printf("Program Size (bytes): %-2d\n\n", addresses.current - addresses.start);
}

void performPass1(symbol* symbolTable[], char* filename, address* addresses)
{
	FILE* ptr;
	char record[INPUT_BUF_SIZE];
	symbol symbol;

	ptr = fopen(filename, "r");
	if (ptr == NULL){
		//perform error handling here
		displayError(FILE_NOT_FOUND, filename);
		exit(1);
	}

	printf("\n%-10s", "Symbol Table Logs\n");
	for (int i = 0; i < 25; i++) {
		printf("-");
	}
	printf("\n");

	while (fgets(record, INPUT_BUF_SIZE, ptr) != NULL) {
		if (record[0] != '#') {

			if (record[0] < 32) {
				//display BLANK_RECORD 
				displayError(BLANK_RECORD, NULL);
				exit(-1);
			}

			segment* newSeg = prepareSegments(record);
			//printf("%s %s %s\n", newSeg->label, newSeg->operation, newSeg->operand);

			if (isDirective(newSeg->label) > 0 || isOpcode(newSeg->label)) {
				//display ILLEGAL_SYMBOL
				displayError(ILLEGAL_SYMBOL, newSeg->label);
				exit(1);
			}

			int dirType = isDirective(newSeg->operation);
			if (isStartDirective(dirType)) {
				addresses->start = strtol(newSeg->operand, NULL, 16);
				addresses->current = strtol(newSeg->operand, NULL, 16);
				//printf("STARTING ---- %x and %x\n", address.start, address.current);
			} else if (dirType != 0) {
				addresses->increment = getMemoryAmount(dirType, newSeg->operand);
				//printf("dirType %x, INCREMENT ---- %d\n", dirType, address.increment);
			} else if (isOpcode(newSeg->operation)) {
				addresses->increment = getOpcodeFormat(newSeg->operation);
			} else {
				//display ILLEGAL_OPCODE_DIRECTIVE
				displayError(ILLEGAL_OPCODE_DIRECTIVE, newSeg->operation);
				exit(-1);
				//printf("Somehow went here\n");
			}

			// if (isOpcode(newSeg->operation)) {
			// 	address.increment = getOpcodeFormat(newSeg->operation);
			// 	//printf("newSeg->operation %s, INCREMENT ---- %d\n", newSeg->operation, address.increment);
			// } else {
			// 	//display ILLEGAL_OPCODE_DIRECTIVE
			// 	printf("Somehow went here v2\n");
			// }

			if (strlen(newSeg->label) > 0 && strcmp(newSeg->label, "COPY") != 0) {
				insertSymbol(symbolTable, newSeg->label, addresses->current);
			}
			
			addresses->current += addresses->increment;
			//printf("Current: %x increment: %d\n", address.current, address.increment);

			if(addresses->current > 0x100000) {
				//check PC address
				char err[12];
				sprintf(err, "%x", addresses->current);
				displayError(OUT_OF_MEMORY, err);
				//printf(" %s", newSeg->label);
				exit(-1);
			}
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