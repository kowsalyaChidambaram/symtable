#include"symtable.h"
#include"hash.h"
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
	bind *bucket_start;
	int number_of_bucket; //to store total no of binds
};
//Creates a new Symtable object returns NULL if no enough memory or return the pointer to the Symtable.
SymTable_t SymTable_new (void)
{
	SymTable_t temp = (SymTable_t) malloc (sizeof(SymTable_t));
	assert(temp != NULL); //memory insufficient
	temp->number_of_bucket = 0; 	//set the length to 0 by default.
	temp->bucket_start = (bind *) calloc(509 , sizeof(bind));
	for(int i=0; i < 509 ; i++)
		temp->bucket_start[i] = NULL; //make all the buckets to null to avoid tension
	return temp; 
}
//Frees the memory occupied by each key and each bind.
void SymTable_free (SymTable_t oSymTable)
{
	assert(oSymTable != NULL );
	bind temp, previous;
	for(int i=0; i< 509; i++)
	{
		temp = oSymTable->bucket_start[i];
		while( temp!= NULL)
		{
			previous = temp;
			temp = temp->next_bind;
			free(previous->pcKey);
			free(previous);
		}
	}
	free(oSymTable->bucket_start);
	free(oSymTable);
	return;
}
//returns the length of the symtable
int SymTable_getLength (SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
    return oSymTable->number_of_bucket;
}
//maps the symtable to a function
void SymTable_map(SymTable_t oSymTable, void(*pfApply)(const char* pcKey, const void* pvValue, void* pvExtra), const void* pvExtra)
{
	assert(oSymTable != NULL);
    assert(pvExtra != NULL);
    assert(pfApply != NULL);
    bind temp;
    for (int i=0; i < 509 ; i++ )
    {
    	temp = oSymTable->bucket_start[i];
    	while(temp != NULL)
    	{
    		pfApply(temp->pcKey, temp->pvValue, (void*)pvExtra);
            temp = temp->next_bind;
    	}
    }
}
//tries hard to locate the key in the bindings; returns 0 if failed, else returns 1 
int SymTable_contains(SymTable_t oSymTable, const char* pcKey)
{
	 //can always check the length of the symtable and return 0 on the second line, beside the while condition do the same
//lesson learnt: just continue the coding ;) quit over thinking
 //if equals then return positive
 return 0; //key not found
}
//this creates a new bind and returns 1 only if the key is not found in the table and memory can hold it back itself.
int SymTable_put(SymTable_t oSymTable, const char* pcKey, const void* pvValue)
{
	return 0; //key not found
}
//tries to patch up the value associated with the key proposed if not found the respective matching key in the table, returns NULL, else value meets key ;)
void* SymTable_get(SymTable_t oSymTable, const char* pcKey)
{
	//lets breakdown, first make sure the key is in the table then dig depper into to get the value;)
	return NULL; //key not found
}
//removes the key if found and returns the opaque pointer else returns NULL
void *SymTable_remove (SymTable_t oSymTable, const char *pcKey)
{
	//the opaque pointer
	//takes the head pointer of the table, if its the head and previous just change the sytable->head to next bind in queue
	//look for the key in the table
	//this could be the head pointer
	return NULL;//key not found
}
//replaces the key if found and returns the opaque pointer else returns NULL
void *SymTable_replace (SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
	 //remind me about assert tradition
	  //document states about an opaque pointer to the lost vale;)
	  return NULL; //returns NULL if key not found
}
