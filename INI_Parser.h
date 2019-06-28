#ifndef INI_ParserH
#define INI_ParserH
#include "XS.h"
#include <stdio.h>
#include "windows.h"
class INI {
	XS file; // Имя файла
	struct Group {
		XS name;
		struct Var {
			XS name,value;
			int hash;
			Var *next;
		} *root,*active; // Корень списка переменных, активная переменная
		int hash;
		Group *next;
	} *root,*active; // Корень списка групп, активная группа

	typedef Group::Var Var;

	Group* DelGroup(Group*,Group*); // Рекурсивный поиск и удаление группы
	Var* DelVar(Var*,Var*); // Рекурсивный поиск и удаление переменной
	int Hash(XS);
public:
	INI(); // ctor
	~INI(); // dtor

	bool Load(const XS&); // Загрузить файл
	bool Save(const XS&); // Сохранить файл
	// Удалить
	void DelGroup();
	void DelVar();
	// Перейти в
		// Начало писка
	bool FirstGroup();
	bool FirstVar();
		// Следующй элемент
	bool NextGroup();
	bool NextVar();
	// Получить имя
	bool GetGroup(XS&);
	bool GetVar(XS&);
	// Добавить
	bool AddGroup(const XS&);
	bool AddVar(const XS&);
	// Переименовать
	bool RenGroup(const XS&);
	bool RenVar(const XS&);
	// Установаить значение переменной
	bool SetBool(const bool&);
	bool SetInt(const long&);
	bool SetFloat(const double&);
	bool SetString(const XS&);
	// Получить значение переменной
	bool GetBool(bool&);
	bool GetInt(long&);
	bool GetFloat(double&);
	bool GetString(XS&);
	// Выбрать по имени
	bool SelectGroup(const XS&);
	bool SelectVar(const XS&);
};
#endif
