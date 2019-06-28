#ifndef BFParserH
#define BFParserH
#define BLOCK_SIZE 1024
#include "XS.h"
class BFP {
	struct instruction {
		char opcode;
		instruction *next;
		union {
			instruction *anext;
			int add;
		};
	} *ptr;
	struct tape_segment {
		signed char tape[BLOCK_SIZE];
		tape_segment *prev,*next;
	} *segment;
	void Destroy(instruction*);
	instruction *Parse(const XS&);
	void CheckRange(int&);
	char type;
public:
	BFP(char,const XS&);
	~BFP();
	XS operator()(unsigned int);
};
#endif
