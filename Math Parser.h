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
	}; // ���� �����

	enum { SIN, COS, TG, CTG, SEC, COSEC,
		ARCSIN, ARCCOS, ARCTG, ARCCTG,
		SH, CH, TGH, CTGH, LOG, EXP, ABS
	}; // ���� �������

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
	} *PT;// ����

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
	} // ����������� ���������� ���������

	void Destroy(PT); // ���������� ������
	double Eval(PT,const double &); // ���������� ������
	double Eval(const double);
	XS LP(char *&); // ����������� ������
	PT SP(char *&); // �������������� ������
	void Error(const char*,const char*); // ����� �� ������
	//PT Derivate(PT);
public:
	Parser(); // default ctor
	Parser(const XS&); // parsing ctor
	~Parser(); // dtor
	double operator ()(double); // ����������
	double operator ()(); // ���������� ��� ����������
	bool operator ()(const XS&); // �������
	XS GetLastError(); // �������� ��������� ������
};
#endif
