#include"symtable.h"
#include"hash.h"
//definition of the structure for a building
typedef struct bindings
{
	const char* pcKey;
	const void* pvValue;
	struct bindings* next_bind;
}*bind;
int bucket_size[] = {509, 1021, 2039, 4093, 8191, 16381, 32749, 65521};
static int size = 0;
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
	temp->bucket_start = (bind *) calloc(bucket_size[size] , sizeof(bind));
	for(int i=0; i < bucket_size[size] ; i++)
		temp->bucket_start[i] = NULL; //make all the buckets to null to avoid tension
	return temp; 
}
//Frees the memory occupied by each key and each bind.
void SymTable_free (SymTable_t oSymTable)
{
	assert(oSymTable != NULL );
	bind temp, previous;
	for(int i=0; i< bucket_size[size]; i++)
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
    for (int i=0; i < bucket_size[size] ; i++ )
    {
    	temp = oSymTable->bucket_start[i];
    	while(temp != NULL)
    	{
    		pfApply(temp->pcKey, temp->pvValue,"");
            temp = temp->next_bind;
    	}
    }
}
//tries hard to locate the key in the bindings; returns 0 if failed, else returns 1 
int SymTable_contains(SymTable_t oSymTable, const char* pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	int i =SymTable_hash(pcKey, bucket_size[size]); //call SymTable_hash, this returns the bucket number
	bind temp = oSymTable->bucket_start[i]; //pointer to the firstt bind in the bucket
	while(temp !=NULL)
	{
		if( strcmp(temp->pcKey, pcKey) ==0) //if equals then return positive
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
	int i = SymTable_hash(pcKey, bucket_size[size]);
	bind temp;
	if(oSymTable->bucket_start[i] == NULL)
	{
		bind node = (bind) malloc (sizeof(struct bindings));
		if (node == NULL)
			return 0; //no enough memory
		node->pvValue = pvValue;
		node->pcKey = pcKey;
		node->next_bind= NULL;
		oSymTable->bucket_start[i] = node;
		oSymTable->number_of_bucket += 1;
		return 1;
	}
	else 
	{
		bind node = oSymTable->bucket_start[i]; //look in the hashed bucket, if found return 0
		bind prev = NULL; 
		while ( node != NULL)
		{
			if( strcmp(node->pcKey, pcKey) == 0)
				return 0;
			prev = node;
			node = node->next_bind;
		}
		//if not found create a new bind and point it to prev -> next
		bind new_bind = (bind) malloc(sizeof(struct bindings));
		if (new_bind ==NULL) //no enough space
			return 0;
		new_bind->pcKey = pcKey;
		new_bind->pvValue = pvValue;
		new_bind->next_bind = NULL;
		oSymTable->number_of_bucket += 1 ;
		prev->next_bind = new_bind;
		return 1;	
	}
	return 0; //key not found
}
//tries to patch up the value associated with the key proposed if not found the respective matching key in the table, returns NULL, else value meets key ;)
void* SymTable_get(SymTable_t oSymTable, const char* pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	int i = SymTable_hash(pcKey, bucket_size[size]);
	bind temp = oSymTable->bucket_start[i]; 
	while( temp !=NULL) //lets breakdown, first make sure the key is in the table then dig depper into to get the value;)
	{
		if (strcmp(temp->pcKey, pcKey) == 0)
			return temp->pvValue;
		temp = temp->next_bind;
	}
	return NULL; //key not found
}
//removes the key if found and returns the opaque pointer else returns NULL
void *SymTable_remove (SymTable_t oSymTable, const char *pcKey)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	int i = SymTable_hash(pcKey, bucket_size[size]); 
	bind temp = oSymTable->bucket_start[i];
	bind prev = NULL;	//takes the head pointer of the table, if its the head and previous just change the sytable->head to next bind in queue
	while(temp != NULL )
	{
		if (strcmp(temp->pcKey, pcKey) == 0 ) //look for the key in the table
		{
			void* opaque_pointer = temp->pvValue;//the opaque_pointer
			if(temp == oSymTable->bucket_start[i]) //this could be the head pointer
			{
				 oSymTable->bucket_start[i] = temp->next_bind;
				
			}
			else
			{
					prev->next_bind = temp->next_bind;
			}		
		 	oSymTable->number_of_bucket -= 1;
			free(temp);
			return opaque_pointer;
		}
		prev = temp;
		temp = temp->next_bind;
	}
	return NULL;//key not found
}
//replaces the key if found and returns the opaque pointer else returns NULL
void *SymTable_replace (SymTable_t oSymTable, const char *pcKey, const void *pvValue)
{
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(pvValue != NULL);
	int i = SymTable_hash(pcKey, bucket_size[size]); 
	bind temp = oSymTable->bucket_start[i];
	while(temp != NULL )
	{
		if (strcmp(temp->pcKey, pcKey) == 0 ) //look for the key in the table
		{
			void* opaque_pointer = temp->pvValue;  //document states about an opaque pointer to the lost vale;
			temp->pvValue = pvValue;		
			return opaque_pointer;
		}
		temp = temp->next_bind;
	}
	//remind me about assert tradition
	rehash(oSymTable);
	return NULL; //returns NULL if key not found
} //trial rehash
void rehash(SymTable_t oSymTable)
{
	size++;
	assert(oSymTable != NULL);
	SymTable_t new_oSymTable;
	new_oSymTable = SymTable_new(); //creates an individual symtable
	for(int i=0; i < bucket_size[size - 1] ; i++) 
	{
		bind temp = oSymTable->bucket_start[i]; //old table
		while(temp != NULL)
		{
			SymTable_put( new_oSymTable, temp->pcKey, temp->pvValue);
			temp = temp->next_bind; //increment bind in old table
		}
	}
	oSymTable->bucket_start = new_oSymTable->bucket_start;
	free(new_oSymTable);
}
