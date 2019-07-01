#include"symtable.h"
//test the function "SymTable_new"
void test_SymTable_new()
{
	SymTable_t oSymTable = SymTable_new ();
	assert(SymTable_new !=NULL);
	printf("test success: SymTable_new craetes a new Symtable\n");
}
//test the function "SymTable_free"
void test_SymTable_free(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	SymTable_free(oSymTable);
	printf("test success: SymTable_free frees the memory occupied\n");
}
//test the function "SymTable_getLength"
void test_SymTable_getLength(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	if(SymTable_getLength(oSymTable) >= 0 )
		printf("test success: SymTable_getLength finds the length of the symtable\n");
	else
		printf("test fail:  SymTable_getLength cant finds the length of the symtable\n"); 
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
		printf("\n\ntest success:  SymTable_map founds the length of the symtable to be zero\n");
	else	
		printf("\n\ntest success: SymTable_map right flow\n");
}
//tests thefunction "test_SymTable_contains"
void test_SymTable_contains(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	int contains_returns;
	if ( (SymTable_contains(oSymTable, "key") == 0)   && (SymTable_contains(oSymTable, "xyz") == 1)) //"key" no such key is in symtable, key "xyz" is in symtable*
		printf("test success: SymTable_contain right flow\n");
	else
		printf("test fail: SymTable_contain doesn't flow good\n");
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
	assert(oSymTable != NULL);
	int put_returns;
	int count = 4; // 65521;
	if(SymTable_getLength(oSymTable) != 0 ) //so far the symtable is a skeleton of length 0
		printf("test fails: SymTable_put, initial Symtable has 0 binds in it\n");
	put_returns = SymTable_put(oSymTable,"box", "int"); //new bind with int value
	put_returns = SymTable_put(oSymTable,"bottle", "float"); //new bind with float value
	put_returns = SymTable_put(oSymTable,"xyz", "double"); //new bind with double value
	put_returns = SymTable_put(oSymTable, make_Key(0), make_value(0)); // test aux functions for the loop ahead
	put_returns = SymTable_put(oSymTable,"test", "double"); //duplicate values alters symtable
	put_returns = SymTable_put(oSymTable, "test", "string"); //duplicate keys doesnt alter symtable
	if (put_returns != 0)
	{
		printf("test fails: SymTable_put duplcated keys\n");
		return;
	}
	if (SymTable_getLength(oSymTable) != 5 ) 
	{
		printf("test fails: SymTable_put length doesnt match\n");
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
		printf("test fails: SymTable_put length doesnt match for long run\n");
		return;
	}
	printf("test success: SymTable_put right flow\n");
	
}
//tests thefunction "test_SymTable_get"
void test_SymTable_get(SymTable_t oSymTable)
{
	assert(oSymTable != NULL);
	void* temp;
	temp = SymTable_get(oSymTable, "xyz"); //looks for the key of an old key 
	if ( temp == NULL)
	{
		printf("test fails: SymTable_get wrong flow \n");
		return;
	}
	if( strcmp((char*) temp, "double"))
	{
		printf("test fails: SymTable_get wrong flow \n");
		return;
	}
	temp = SymTable_get(oSymTable,"symtable"); //sad the key symtable isnt in the symtable ;)
	if( temp != NULL )
	{
		printf("test fails: SymTable_get wrong flow \n");		
		return;
	}
	printf("test succeess : test_SymTable_get right flow \n");
}
//tests the functions "SymTable_remove" 
void test_SymTable_remove (SymTable_t oSymTable)
{
	
	void *temp;
	temp = SymTable_remove(oSymTable, "xyz"); // Available key "xyz" expected to return a opaque pointer
	if (temp == NULL )
	{
		printf("test fails:SymTable_remove wrong flow \n");		
		return;
	}
	temp = SymTable_remove(oSymTable, "abc"); // new key "abc" expected to return a null
	if (temp != NULL )
	{
		printf("test fails: SymTable_remove wrong flow \n");		
		return;
	}
	printf("test succeess : SymTable_remove right flow \n");
}
//tests the functions "SymTable_replace"
void test_SymTable_replace (SymTable_t oSymTable)
{
	void *temp;
	temp = SymTable_replace(oSymTable, "box", "unsigned_"); // Available key "xyz" expected to return a opaque pointer
	if (temp == NULL )
	{
		printf("test fails: SymTable_replace wrong flow \n");		
		return;
	}
	temp = SymTable_replace(oSymTable, "abc", "unsigned_"); // new key "abc" expected to return a null
	if (temp != NULL )
	{
		printf("test fails: SymTable_replace wrong flow \n");		
		return;
	}
	printf("test succeess : SymTable_replace right flow \n");
}
//test all the functions in one go
int main()
{
	test_SymTable_new();
	SymTable_t oSymTable = SymTable_new ();
	test_SymTable_getLength(oSymTable);
	test_SymTable_put(oSymTable);
	//test_SymTable_map(oSymTable); //this is included in the test_SymTable_put for easy view ;)
	test_SymTable_get(oSymTable);
	test_SymTable_contains(oSymTable);
	test_SymTable_remove(oSymTable);
	test_SymTable_replace(oSymTable);
	test_SymTable_free(oSymTable);
}
