/*********************************************
*        DO NOT REMOVE THIS MESSAGE
*
* This file is provided by Professor Littleton
* to assist students with completing Project 2.
*
*        DO NOT REMOVE THIS MESSAGE
**********************************************/

#include "headers.h"

#define MOD_SIZE 10
#define SYMBOL_TABLE_SEGMENTS 10
#define SYMBOL_TABLE_SIZE 100

int computeHash(char* input);

int computeHash(char* symbolName)
{
	int hash = 0;

	for (int i = 0; symbolName[i] != '\0'; i++) {
		hash += symbolName[i];
	}

	return hash % MOD_SIZE * SYMBOL_TABLE_SEGMENTS;
}

void displaySymbolTable(symbol* symbolTable[])
{
	printf("\n%-10s", "Symbol Table Contents\n");
	for (int i = 0; i < 25; i++) {
		printf("-");
	}
	printf("\n");
	printf("%-6s %-10s %s\n", "Index", "Name", "Address"); 
	printf("%-6s %-10s %s\n", "-----", "----", "-------"); 
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
		if (symbolTable[i] != NULL) { 
			printf("%-6d %-10s 0x%x\n", i, symbolTable[i]->name, symbolTable[i]->address);
		}
	}
}

void initializeSymbolTable(symbol* symbolTable[])
{
	for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
		symbolTable[i] = NULL;
	}
}

void insertSymbol(symbol* symbolTable[], char symbolName[], int symbolAddress)
{
	int hashValue = computeHash(symbolName);
	bool inserted = false;
	bool dupName = false;

	while (!inserted) {
		if(symbolTable[hashValue] == NULL) {
			symbolTable[hashValue] = malloc(sizeof(symbol));
			strcpy(symbolTable[hashValue]->name, symbolName);
			symbolTable[hashValue]->address = symbolAddress;
			inserted = true;
		}
		else {
			if (strcmp(symbolTable[hashValue]->name, symbolName) == 0) {
				inserted = true;
				dupName = true;
				displayError(DUPLICATE, symbolTable[hashValue]->name);
				exit(0);
			} 
			hashValue++;
		}
	}
	if (!dupName) {
		printf("Added %s to Symbol Table at Index %d \n", symbolName, hashValue);
	}

}