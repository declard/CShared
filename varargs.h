/**********************
*		WARNING!
*	Use this funcs ONLY
*	in __cdecl functions
*	...at your own risc ;)
************************/
#ifndef varargsH
#define varargsH
unsigned long varargs_num(); // Returns size used for args in stack (bytes)
void* varargs_first(); // Returns pointer to 0th argument
void varargs_prep(); // Checks if EBP needs to be set manually or not
void varargs_probe(char&);
#endif