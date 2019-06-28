#ifndef INI_ParserH
#define INI_ParserH
#include "XS.h"
#include <stdio.h>
#include "windows.h"
class INI {
	XS file; // ��� �����
	struct Group {
		XS name;
		struct Var {
			XS name,value;
			int hash;
			Var *next;
		} *root,*active; // ������ ������ ����������, �������� ����������
		int hash;
		Group *next;
	} *root,*active; // ������ ������ �����, �������� ������

	typedef Group::Var Var;

	Group* DelGroup(Group*,Group*); // ����������� ����� � �������� ������
	Var* DelVar(Var*,Var*); // ����������� ����� � �������� ����������
	int Hash(XS);
public:
	INI(); // ctor
	~INI(); // dtor

	bool Load(const XS&); // ��������� ����
	bool Save(const XS&); // ��������� ����
	// �������
	void DelGroup();
	void DelVar();
	// ������� �
		// ������ �����
	bool FirstGroup();
	bool FirstVar();
		// �������� �������
	bool NextGroup();
	bool NextVar();
	// �������� ���
	bool GetGroup(XS&);
	bool GetVar(XS&);
	// ��������
	bool AddGroup(const XS&);
	bool AddVar(const XS&);
	// �������������
	bool RenGroup(const XS&);
	bool RenVar(const XS&);
	// ����������� �������� ����������
	bool SetBool(const bool&);
	bool SetInt(const long&);
	bool SetFloat(const double&);
	bool SetString(const XS&);
	// �������� �������� ����������
	bool GetBool(bool&);
	bool GetInt(long&);
	bool GetFloat(double&);
	bool GetString(XS&);
	// ������� �� �����
	bool SelectGroup(const XS&);
	bool SelectVar(const XS&);
};
#endif
