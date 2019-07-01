include=../source/include/
implementation=../source/implementation/
test=../source/test/

all: linklist hash

linklist: $(include)symtable.h $(implementation)symtable_link.c $(test)symtable_test.c
	gcc -I $(include) $(implementation)symtable_link.c $(test)symtable_test.c -w -Wall -o linklist.out
	./linklist.out

hash: $(include)hash.h $(implementation)hash.c $(include)symtable.h $(implementation)symtable_hash.c $(test)symtable_test.c
	gcc -I $(include) $(implementation)hash.c $(implementation)symtable_hash.c $(test)symtable_test.c -w -Wall -o hash.out
	./hash.out
	

clean:
	rm linklist.out
	rm hash.out
