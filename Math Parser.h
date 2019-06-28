#ifndef ParserH
#define ParserH
#include "XS.h"

class Parser {
	static char *mpe;
	char *error,state,type;
	XS last_error;
	int depth;

	enum { VAR, VAL, ADD, SUB, MUL,
		DIV, POW, NEG, FUNC, ROOT
	}; // Типы узлов

	enum { SIN, COS, TG, CTG, SEC, COSEC,
		ARCSIN, ARCCOS, ARCTG, ARCCTG,
		SH, CH, TGH, CTGH, LOG, EXP, ABS
	}; // Типы функций

	typedef struct PTS {
		int type;
		union {
			struct {
				PTS *r;
				union {
					PTS *l;
					int func;
				};
			};
			double val;
		};
	} *PT;// Узел

	PT pres;

	static int GetPriority(PT a) {
		if (!a) return 0;
		switch(a->type) {
			case ADD:
			case SUB: return 1;
			case MUL:
			case DIV: return 2;
			case POW: return 3;
			case NEG: return 4;
			case ROOT: return 5;
			default: return 6;
		}
	} // Определение приоритета оператора

	void Destroy(PT); // Деструктор дерева
	double Eval(PT,const double &); // Вычисление дерева
	double Eval(const double);
	XS LP(char *&); // Лексический парсер
	PT SP(char *&); // Синтаксический парсер
	void Error(const char*,const char*); // Отчёт об ошибке
	//PT Derivate(PT);
public:
	Parser(); // default ctor
	Parser(const XS&); // parsing ctor
	~Parser(); // dtor
	double operator ()(double); // Вычисление
	double operator ()(); // Вычисление без переменной
	bool operator ()(const XS&); // Парсинг
	XS GetLastError(); // Просмотр последней ошибки
};
#endif
