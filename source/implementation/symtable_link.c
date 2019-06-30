#include "symtable.h"
//definition of the structure for a building
typedef struct bindings
{
	const char* pcKey;
	const void* pvVale;
	struct bindings* next_bind;
}*bind;
//definition of strructure for a Symtable
struct SymTable
{
	bind head;
	int number_of_bind; //to store total no of binds
};
//Creates a new Symtable object returns NULL if no enough memory or return the pointer to the Symtable.
SymTable_t SymTable_new (void)
{
	SymTable_t new_SymTable;
	new_SymTable = (SymTable_t) malloc(sizeof(struct SymTable));
	if (new_SymTable == NULL)
	{
		return new_SymTable;
	}
	else
	{
		new_SymTable->head = NULL;
		new_SymTable->number_of_bind = 0; //set the length to 0 by default.
		return new_SymTable; 
	}
}
//Frees the memory occupied by each key and each bind.
void SymTable_free (SymTable_t oSymTable)
{
	assert(oSymTable != NULL );
	bind temp, previous;
	previous = oSymTable -> head;
	while ( previous != NULL )
	{
		temp = previous;
		previous = previous->next_bind;
		free((char*) temp->pcKey);
		free(temp);
	}
	free ( oSymTable );
}
//returns the length of the symtable
int SymTable_getLength (SymTable_t oSymTable)
{
	assert(oSymTable !=	NULL);
	return oSymTable -> number_of_bind;
}
//maps the symtable to a function
void SymTable_map(SymTable_t oSymTable, void(*pfApply)(const char* pcKey, const void* pvValue, void* pvExtra), const void* pvExtra)
{
	assert(oSymTable != NULL);		
	bind temp = oSymTable->head;
	while(temp != NULL)
	{
		pfApply(temp->pcKey, temp->pvVale,pfApply );
		temp = temp->next_bind;
	}
}
