#include "Math Parser.h"
#include <math.h>
#include <windows.h>

char *Parser::mpe="Mathematic Parser Error:";

void Parser::Destroy(PT tree) {
	if (!tree) return;
	switch (tree->type) {
		case VAR: case VAL: break;
		default: Destroy(tree->l);
		case NEG: case FUNC: Destroy(tree->r);
	}
	delete tree;
}

double Parser::Eval(PT ptr,const double &var) {
	if (!ptr) return 0;
	if (ptr->type==VAR) if (type) return var; else goto ewv;
	if (ptr->type==VAL) return ptr->val;
	double l,r;
	if (ptr->type!=NEG&&ptr->type!=FUNC) l=Eval(ptr->l,var); // Если унарные операции, то l не является указателем на дерево
	if (error) return l;
	r=Eval(ptr->r,var); // Вычисление правого операнда
	if (error) return r;

	switch (ptr->type) { // Действие для каждого типа вершин
		case ADD: l+=r; break;
		case SUB: l-=r; break;
		case MUL: l*=r; break;
		case DIV: if (!r) goto dbz; l/=r; break;
		case POW: if (!l&&r<=0) goto ue; l=pow(l,r); break;
		case NEG: l=-r; break;
		case FUNC:
		switch (ptr->func) { // Если вершина является функцией
			case SIN: l=sin(r); break;
			case COS: l=cos(r); break;
			case TG: l=tan(r); break;
			case CTG: l=tan(r); if (!l) goto dbz; l=1/l; break;
			case SEC: l=cos(r); if (!l) goto dbz; l=1/l; break;
			case COSEC: l=sin(r); if (!l) goto dbz; l=1/l; break;
			case ARCSIN: l=asin(r); break;
			case ARCCOS: l=acos(r); break;
			case ARCTG: l=atan(r); break;
			case ARCCTG: if (!r) goto dbz; l=atan(1/r); break;
			case SH: l=sinh(r); break;
			case CH: l=cosh(r); break;
			case TGH: l=tanh(r); break;
			case CTGH: l=tanh(r); if (!l) goto dbz; l=1/l; break;
			case LOG: if (r<=0) goto ue; l=log(r); break;
			case EXP: l=exp(r); break;
			case ABS: if (r<0) l=-r; else l=r; break;
		}
	}
	return l;
	// Ошибки
dbz:	throw "Division by zero";
ue:	throw "Unexpected error";
ewv:	throw "Evaluating non-constant expression with no variable given";
}

// Лексический анализатор
XS Parser::LP(char *&str) {
	XS delimeters("\x20\t\n\r"),terminals("-+*/^()"); // Разделители и терминальные символы
	int len=0;
	char automat[3][3]={
		{0,-1,-1},// Разделители
		{1,-1,-1},// Терминальные символы
		{2,-1, 2} // прочие последовательности
	}, // Талица переходов ДКА
	c,instate,state=0;
	while(c=*str) {
		if (delimeters.IsIn(c)) instate=0;
		else if (terminals.IsIn(c)) instate=1;
		else instate=2;
		state=automat[instate][state];
		switch(state) {
			case -1: return XS(str-len,len);
			case 1:
			case 2: len++;
			case 0: str++;
		}
	}
	return XS(str-len,len);
}

// Синтаксический анализатор
Parser::PT Parser::SP(char *&str) {
	static char automat[8][7]={
		{-1, 0,-1, 0,-1, 0,-1},// Оператор
		{ 1,-1, 1,-1,-1,-1, 1},// Число
		{ 2,-1, 2,-1, 2,-1, 2},// (
		{-1, 3,-1, 3,-1, 3,-1},// )
		{ 4,-1, 4,-1,-1,-1, 4},// Имя функции
		{ 5,-1, 5,-1,-1,-1, 5},// Переменная
		{ 6, 0, 6, 0,-1, 0, 6},// Унарный минус
		{-1, 7,-1, 7,-1, 7,-1},// Конец строки
	}; // Таблица переходов ДКА
	static XS operators("+-*/^"),
	functions("sin cos tg ctg sec cosec arcsin arccos arctg arcctg sh ch tgh ctgh log exp abs");
	char instate,priority;
	int func;
	XS atom;
	PT root /*Tree root*/,r /*Rightest node*/,v=0 /*Value node*/,node /*Proceeded node*/,temp;
	PTS troot;
	root=&troot;
	r=root;
	r->type=ROOT;
	r->r=0;

	while(1) {

		atom=LP(str); // Получение лексемы
		
		// Опознавание лексемы
		if (error) instate=state=0;
		else if (!atom.Length()) instate=7;
		else if (atom.Length()==1) switch(atom[0]) {
			case '-':	instate=6; break;
			case 'x':
			case 'X':
			case 'х':
			case 'Х':	instate=5; break;
			case ')':	instate=3; break;
			case '(':	instate=2; break;
			default:	if (operators.IsIn(atom[0])) instate=0;
				else goto check;
		}
		else goto check;
		goto through;
check:
		if (atom.IsNumber()) instate=1;
		else if ((func=functions.FindTok(atom,32))!=-1) instate=4;
		else {
			error="Parse error: wrong atom";
			instate=8;
		}
through:
		
		// Изменение состояния
		state=automat[instate][state];
		
		// Обработка состояния
		switch(state) {
			// Ошибка
			case -1:if (!error) error="Parse error: wrong atom sequence";
				last_error=error;
				depth=0;
				state=0;
				if (v) delete v;
				if (root->r) Destroy(root->r);
				return 0;
			// Оператор
			case 0:	node=new PTS;
				node->type=operators.Pos(atom[0])+ADD;
				node->r=0;
				priority=GetPriority(node);
				temp=root;
				do if (temp->r&&GetPriority(temp->r)>=priority||(temp->r&&temp->r->type>=NEG)) {
					r->r=v;
					node->l=temp->r;
					r=node;
					temp->r=node;
					break;
				}
				else if (temp==r) {
					node->l=v;
					r->r=node;
					r=node;
					break;
				} while (temp=temp->r);
				break;
			// Число
			case 1:	v=new PTS;
				v->type=VAL;
				v->val=atom.ToDouble();
				break;
			// (
			case 2:	depth++;
				v=SP(str);
				break;
			// )
			case 3:	if (!depth--) error="Unexpected ')'";
				r->r=v;
				return root->r;
			// Функция
			case 4:	node=new PTS;
				node->type=FUNC;
				node->r=0;
				node->func=func;
				r->r=node;
				r=node;
				break;
			// Переменная
			case 5:	v=new PTS;
				v->type=VAR;
				break;
			// Унарный минус
			case 6:	node=new PTS;
				node->type=NEG;
				node->l=0;
				r->r=node;
				r=node;
				break;
			// Конец строки
			case 7:	if (depth) {
					error="Unexpected end of line";
					break;
				}
				r->r=v;
				return root->r;
		};
	}
}

void Parser::Error(const char*str0,const char*str1) {
	MessageBoxA(0,str0,str1,MB_ICONWARNING);
}

Parser::Parser() {
	error=0;
	pres=0;
	state=2;
	depth=0;
}
Parser::Parser(const XS&in) {
	char *str=in.c_str();
	error=0;
	state=2;
	depth=0;
	pres=SP(str);
	if (error) {
		Error(error,mpe);
		pres=0;
	}
	error=0;
}
Parser::~Parser() {
	Destroy(pres);
}
double Parser::operator ()(double val) {
	type=1;
	return Eval(val);
}
double Parser::operator ()() {
	type=0;
	return Eval(0);
}
double Parser::Eval(const double val) {
	if (!pres) {
		Error("Tree Doesn't Exist!",mpe);
		return 0;
	}
	double res;
	try { res=Eval(pres,val); }
	catch (const char* str) {
		last_error=str;
		Error(str,mpe);
		error=0;
		return 0;
	}
	return res;
}
bool Parser::operator ()(const XS &in) {
	char *str=in.c_str();
	Destroy(pres);
	state=2;
	depth=0;
	pres=SP(str);
	if (error) {
		pres=0;
		error=0;
		return false;
	}
	return true;
}

XS Parser::GetLastError() {
	return last_error;
}