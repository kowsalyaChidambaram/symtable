#include "symtable.h"
//definition of the structure for a building
typedef struct bindings
{
	const char* pcKey;
	const void* pvValue;
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
	previous = oSymTable->head;
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
	return oSymTable->number_of_bind;
}
//maps the symtable to a function
void SymTable_map(SymTable_t oSymTable, void(*pfApply)(const char* pcKey, const void* pvValue, void* pvExtra), const void* pvExtra)
{
	assert(oSymTable != NULL);		
	bind temp = oSymTable->head;
	while(temp != NULL)
	{
		pfApply(temp->pcKey, temp->pvValue,"");
		temp = temp->next_bind;
	}
}
//tries hard to locate the key in the bindings; returns 0 if failed, else returns 1 
int SymTable_contains(SymTable_t oSymTable, const char* pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL); //can always check the length of the symtable and return 0 on the second line, beside the while condition do the same
//lesson learnt: just continue the coding ;) quit over thinking
	bind temp = oSymTable->head;
	while(temp != NULL)
	{
		if(strcmp(temp->pcKey, pcKey) == 0) //if equals then return positive
			return 1;
		temp = temp->next_bind;
	}
	return 0; //key not found
}
//this creates a new bind and returns 1 only if the key is not found in the table and memory can hold it back itself.
int SymTable_put(SymTable_t oSymTable, const char* pcKey, const void* pvValue)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(pvValue != NULL);
	if(SymTable_contains(oSymTable, pcKey) == 0)
	{
		bind new_bind = (bind) malloc(sizeof(struct bindings));
		if(new_bind == NULL)
			return 0;
		new_bind->pcKey = pcKey;
		new_bind->pvValue = pvValue;
		new_bind->next_bind = oSymTable->head;
		oSymTable->head = new_bind;
		oSymTable->number_of_bind += 1;	
		return 1;
	}
	return 0; //key not found
}
//tries to patch up the value associated with the key proposed if not found the respective matching key in the table, returns NULL, else value meets key ;)
void* SymTable_get(SymTable_t oSymTable, const char* pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	if(  SymTable_getLength(oSymTable)!=0) 
	{
		if( SymTable_contains(oSymTable, pcKey) !=0 ) //lets breakdown, first make sure the key is in the table then dig depper into to get the value;)
		{
			
			bind temp = oSymTable->head;
			for(int i = 0; i < oSymTable->number_of_bind; i++)
			{
				if(strcmp(temp->pcKey,pcKey ) == 0 )
					return temp->pvValue;
				temp = temp->next_bind;
			}
		}
	}
	return NULL; //key not found
}
//removes the key if found and returns the opaque pointer else returns NULL
void *SymTable_remove (SymTable_t oSymTable, const char *pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	bind temp = oSymTable->head;
	bind opaque_ptr; //the opaque pointer
	bind previous = oSymTable->head; //takes the head pointer of the table, if its the head and previous just change the sytable->head to next bind in queue
	
	while(temp != NULL )
	{
		if( strcmp(temp->pcKey, pcKey) ==0 ) //look for the key in the table
		{
			opaque_ptr = temp->pvValue; //this could be the head pointer
			if(previous == oSymTable->head)
			{
				oSymTable->head = previous->next_bind;
			}
			else
			{
				previous->next_bind = temp->next_bind;
			}
			oSymTable->number_of_bind -= 1 ;
			free(temp); 
			return opaque_ptr;
		}
		previous = temp;
		temp = temp->next_bind;
	}
	return NULL; //key not found
}
//replaces the key if found and returns the opaque pointer else returns NULL
void *SymTable_replace (SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(	pvValue!= NULL); //remind me about assert tradition
	bind temp = oSymTable->head;
	bind opaque_ptr;
	while( temp != NULL)
	{
		if(strcmp(temp->pcKey, pcKey) == 0)
		{
			opaque_ptr = temp->pvValue; //document states about an opaque pointer to the lost vale;)
			temp->pvValue = pvValue;
			return opaque_ptr;
		}
		temp = temp->next_bind;
	}
	return NULL; //returns NULL if key not found
}
