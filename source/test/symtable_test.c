#include"symtable.h"
void test_SymTable_new()
{
	SymTable_t oSymTable = SymTable_new ();
	assert(SymTable_new !=NULL);
	printf(" test success: craetes a new Symtable\n");
}
void test_SymTable_free(SymTable_t oSymTable)
{
	SymTable_free(oSymTable);
	printf(" test success: frees the memory occupied\n");
}
void test_SymTable_getLength(SymTable_t oSymTable)
{
	if(SymTable_getLength(oSymTable) >= 0 )
		printf(" test success: finds the length of the symtable\n");
	else
		printf(" test fail: frees the memory occupied\n"); 
}
int main()
{
	test_SymTable_new();
	SymTable_t oSymTable = SymTable_new ();
	test_SymTable_getLength(oSymTable);
	test_SymTable_free(oSymTable);
}
