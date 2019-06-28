#pragma hdrstop
#include "BFParser.h"
#include "memory.h"
BFP::instruction *BFP::Parse(const XS&ctape) {
	instruction *cur=0,*tempi=0;
	struct instruction_stack {
		instruction_stack*ptr;
		instruction *data;
	} *temps=0,*stack=0;
	char c;
	XS codes("<>+-.,[]");
	for(int i=ctape.Length()-1;i>=0;i--) {
		tempi=new instruction;
		c=ctape[i];
		if (codes.IsIn(c)) tempi->opcode=c;
		/*else if (c>='0'&&c<='9') {
			tempi->opcode='a';
			tempi->add=(int)(c-'0');
		}*/
		else {
			while(stack) {
				temps=stack->ptr;
				delete stack;
				stack=temps;
			}
			delete tempi;
			while(cur) {
				tempi=cur->next;
				delete cur;
				cur=tempi;
			}
			throw "";
		}
		if (c=='[') {
			tempi->anext=stack->data->next;
			stack->data->next=tempi;
			temps=stack->ptr;
			delete stack;
			stack=temps;
		}
		else if (c==']') {
			temps=new instruction_stack;
			temps->data=tempi;
			temps->ptr=stack;
			stack=temps;
		}
		tempi->next=cur;
		cur=tempi;
	}
	return cur;
}
void BFP::CheckRange(int&pos) {
	if (pos>BLOCK_SIZE-1) {
		if (segment->next) segment=segment->next;
		else {
			tape_segment *temps=new tape_segment;
			memset(temps->tape,0,BLOCK_SIZE);
			temps->prev=segment;
			temps->next=0;
			segment->next=temps;
			segment=temps;
		}
		pos-=BLOCK_SIZE;
	}
	else if (pos<0) {
		if (segment->prev) segment=segment->prev;
		else {
			tape_segment *temps=new tape_segment;
			memset(temps->tape,0,BLOCK_SIZE);
			temps->next=segment;
			temps->prev=0;
			segment->prev=temps;
			segment=temps;
		}
		pos+=BLOCK_SIZE;
	}
}
BFP::BFP(char t,const XS&str) {
	ptr=0;
	type=t;
	ptr=Parse(str);
	segment=new tape_segment;
	segment->prev=segment->next=0;
	memset(segment->tape,0,BLOCK_SIZE);
}
void BFP::Destroy(instruction*p) {
	if (!p) return;
	if (p->opcode=='[') Destroy(p->anext);
	if (p->opcode!=']') Destroy(p->next);
	delete p;
}
BFP::~BFP() {
	Destroy(ptr);
	tape_segment *temps;
	while(segment&&segment->prev) segment=segment->prev;
	while(segment) {
		temps=segment->next;
		delete segment;
		segment=temps;
	}
}

XS BFP::operator()(unsigned int depth) {
	if (depth<50) depth=50;
	if (!ptr) return XS();
	int pos=0;
	unsigned int alc=0;
	XS out;
	instruction *p=ptr;
	while(p) {
		switch (p->opcode) {
			case '>': pos++; CheckRange(pos); break;
			case '<': pos--; CheckRange(pos); break;
			case '+': segment->tape[pos]++; break;
			case '-': segment->tape[pos]--; break;
			case '.': if (type) out+=" "+XS((int)segment->tape[pos]); else out+=segment->tape[pos]; break;
			case '[': if (segment->tape[pos]) break; p=p->anext; continue;
			case ']': if (alc++>depth) return out;
			//case 'a': segment->tape[pos]*=10; segment->tape[pos]+=(char)p->add; break;
		}
		p=p->next;
	}
	return out;
}