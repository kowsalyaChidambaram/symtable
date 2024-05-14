Description:

  The symbol table consists of bindings which holds the key and value.
The symbol table owns the key and duplicates are not entertained. 
Implemented in two ways : Linked List and Hashing.

Repos skeleton :
```bash
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
```

its hard to comment what every file has and does, suit yourself ;)



You'll need to do the following to get started:
Building from source

Get the repo if you dont have yet.
```bash
git clone https://github.com/kowsalyaChidambaram/symtable.git
```

move to build folder; trash out the left over execution files
```bash
cd build
make clean
```

creates and runs the execution file related to linkedlist
```bash
make linklist
```

creates and runs the execution file related to hash
```bash
make hash
```
