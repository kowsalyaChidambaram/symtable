#include"symtable.h"
#include<time.h>
//test the function "SymTable_new"
void test_SymTable_new()
{
	SymTable_t oSymTable = SymTable_new ();
	assert(SymTable_new !=NULL);
	printf("test success: craetes a new Symtable\n");
}
//test the function "SymTable_free"
void test_SymTable_free(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	SymTable_free(oSymTable);
	printf("test success: frees the memory occupied\n");
}
//test the function "SymTable_getLength"
void test_SymTable_getLength(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	if(SymTable_getLength(oSymTable) >= 0 )
		printf("test success: finds the length of the symtable\n");
	else
		printf("test fail: cant finds the length of the symtable\n"); 
}
//lets map this function to "SymTable_map"
void function(const char* pcKey, const void* pvValue, void* pvExtra) 
{
	printf("\n%s\t%s", pcKey, pvValue);
}
//test mapping a function to "SymTable_map"
void test_SymTable_map(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	SymTable_map(oSymTable, function, "");
	if(SymTable_getLength(oSymTable) == 0 )
		printf("\n\ntest success: founds the length of the symtable to be zero\n");
	else	
		printf("\n\ntest success: maps the specified funtion to the map \n");
}
//tests thefunction "test_SymTable_contains"
void test_SymTable_contains(SymTable_t oSymTable)
{
	
	//SymTable_contains();
}
//aux function t0 make keys here 
char* make_Key(int i)
{
	char* result = (char *) malloc(50);
	sprintf(result, "%d" ,i);
	return result;
}
//aux function to make value
char* make_value(int i)
{
	srand(time(0));
	char *type[9] = { "char", "short", "int" , "float", "double" , "string", "long", "long long", "unsigned_" };
	return type[i%9];
}
//tests thefunction "test_SymTable_put"
void test_SymTable_put(SymTable_t oSymTable)
{
	int put_returns;
	int count = 65521;
	if(SymTable_getLength(oSymTable) != 0 ) //so far the symtable is a skeleton of length 0
		printf("test fails: initial Symtable has 0 binds in it\n");
	put_returns = SymTable_put(oSymTable,"box", "int"); //new bind with int value
	put_returns = SymTable_put(oSymTable,"bottle", "float"); //new bind with float value
	put_returns = SymTable_put(oSymTable,"xyz", "double"); //new bind with double value
	put_returns = SymTable_put(oSymTable, make_Key(0), make_value(0)); // test aux functions for the loop ahead
	put_returns = SymTable_put(oSymTable,"test", "double"); //duplicate values alters symtable
	put_returns = SymTable_put(oSymTable, "test", "string"); //duplicate keys doesnt alter symtable
	if (put_returns != 0)
	{
		printf("test fails: duplcated keys\n");
		return;
	}
	if (SymTable_getLength(oSymTable) != 5 ) 
	{
		printf("test fails: length doesnt match\n");
		return;
	}
	test_SymTable_map(oSymTable);
	for( int i = 1; i <= count  ; i++) 
	{
		put_returns = SymTable_put(oSymTable, make_Key(i), make_value(i));
	}
	//test_SymTable_map(oSymTable);
	if(SymTable_getLength(oSymTable) != 5 + count )
	{
		printf("test fails: length doesnt match for long run\n");
		return;
	}
	printf("test success2: puts executed successfully \n");
	
}
//tests thefunction "test_SymTable_get"
void test_SymTable_get(SymTable_t oSymTable)
{
	//SymTable_get();
}
//test all the functions in one go
int main()
{
	test_SymTable_new();
	SymTable_t oSymTable = SymTable_new ();
	test_SymTable_getLength(oSymTable);
	//test_SymTable_free(oSymTable);
	test_SymTable_put(oSymTable);
	//test_SymTable_map(oSymTable);
	//test_SymTable_get();
	//test_SymTable_contains();
}
