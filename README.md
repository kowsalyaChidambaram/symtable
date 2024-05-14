Description:

  The symbol table consists of bindings which holds the key and value.
The symbol table owns the key and duplicates are not entertained. 
Implemented in two ways : Linked List and Hashing.

Repos skeleton :
./README.md #that you have found here
./build
	./build/Makefile #makes the compilation and execution incredibly easy
./source
	./source/include/
		./source/include/hash.h 
		./source/include/symtable.h
	./source/implementation/
		./source/implementation/hash.c
		./source/implementation/symtable_link.c
		./source/implementation/symtable_hash.c
	./source/test/
		./source/test/symtable_test.c 

its hard to comment what every file has and does, suit yourself ;)

details to build
> cd build
> make clean
	trashes out the left over execution files left out
> make linklist
	creates and runs the execution file related to linkedlist
> make hash
	creates and runs the execution file related to hash
