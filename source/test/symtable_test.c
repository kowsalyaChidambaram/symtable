#include"symtable.h"
//test the function "SymTable_new"
void test_SymTable_new()
{
	SymTable_t oSymTable = SymTable_new ();
	assert(SymTable_new !=NULL);
	printf(" test success: craetes a new Symtable\n");
}
//test the function "SymTable_free"
void test_SymTable_free(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	SymTable_free(oSymTable);
	printf(" test success: frees the memory occupied\n");
}
//test the function "SymTable_getLength"
void test_SymTable_getLength(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	if(SymTable_getLength(oSymTable) >= 0 )
		printf(" test success: finds the length of the symtable\n");
	else
		printf(" test fail: frees the memory occupied\n"); 
}
//lets map this function to "SymTable_map"
void function(const char* pcKey, const void* pvValue, void* pvExtra) 
{
	printf("\n %s\t%s", pcKey, pvValue);
}
//test mapping a function to "SymTable_map"
void test_SymTable_map(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	SymTable_map(oSymTable, function, "");
	if(SymTable_getLength(oSymTable) == 0 )
		printf(" test success: founds the length of the symtable to be zero\n");
	else	
		printf(" test success: maps the specified funtion to the map \n");
}

//test all the functions in one go
int main()
{
	test_SymTable_new();
	SymTable_t oSymTable = SymTable_new ();
	test_SymTable_getLength(oSymTable);
	test_SymTable_free(oSymTable);
	test_SymTable_map(oSymTable);
}
