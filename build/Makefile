include=../source/include/
implementation=../source/implementation/
test=../source/test/

all: linklist hash

linklist: $(include)symtable.h $(implementation)symtable_link.c $(test)symtable_test.c
	gcc -I $(include) $(implementation)symtable_link.c $(test)symtable_test.c -w -Wall -o test_linked

hash: $(include)hash.h $(implementation)hash.c $(include)symtable.h $(implementation)symtable_hash.c $(test)symtable_test.c
	gcc -I $(include) $(implementation)hash.c $(implementation)symtable_hash.c $(test)symtable_test.c -w -Wall -o test_hash 
	
test: all
	./test_linked
	./test_hash
	
clean:
	rm test_linked
	rm test_hash

