#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h> //testing needs
typedef struct SymTable* SymTable_t;
SymTable_t SymTable_new (void);
void SymTable_free (SymTable_t oSymTable);
int SymTable_getLength (SymTable_t oSymTable);
void SymTable_map(SymTable_t oSymTable, void(*pfApply)(const char* pcKey, const void* pvValue, void* pvExtra), const void* pvExtra);
