#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h> //testing needs
typedef struct SymTable* SymTable_t;
SymTable_t SymTable_new (void);
void SymTable_free (SymTable_t oSymTable);
int SymTable_getLength (SymTable_t oSymTable);
