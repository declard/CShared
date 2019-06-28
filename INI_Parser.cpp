#include "INI_Parser.h"
#define activevar active->active
INI::Group* INI::DelGroup(INI::Group*cur,INI::Group*trgt) {
	if (!cur) return 0;
	if (cur==trgt) return cur->next;
	cur->next=DelGroup(cur->next,trgt);
	return cur;
}
INI::Var* INI::DelVar(INI::Var*cur,INI::Var*trgt) {
	if (!cur) return 0;
	if (cur==trgt) return cur->next;
	cur->next=DelVar(cur->next,trgt);
	return cur;
}
int INI::Hash(XS str) {
	str=str.ToLower();
	int h;
	for(int i=0;i<str.Length();i++) h=(h+str[i])%253;
	return h;
}
INI::INI() {
	root=active=0;
}
INI::~INI() {
	if (!root) return;
	active=root;
	Group*gt;
	Var*vt;
	do {
		gt=active->next;
		do {
			vt=activevar->next;
			delete activevar;
		} while (activevar=vt);
		delete active;
	} while(active=gt);

}
bool INI::Load(const XS&name) {
	static char automat[6][5]={
		/*
			0 - Имя переменной, 1 - Ожидание строки
			2 - Строка с ', 3 - Строка с "
			4 - Строка без " и ', (5 - конец строки
			6 - получена строка с ', 7 - получена строка с ")
		*/
		 1, 4, 2, 3, 4, // =
		-1, 6, 5, 3, 4, // '
		-1, 7, 2, 5, 4, // "
		-1, 5, 2, 3, 5, // ; или #
		 0, 4, 2, 3, 4, // Прочие символы
		-1, 5,-1,-1, 5  // Конец строки
	};
	FILE *file;
	int line=0;
	char buf[1025],ins,state=0;
	XS str;
	if (!(file=fopen(name.c_str(),"r"))) return false;
	while (fgets(buf,1024,file)) {
		str=XS(buf).Trim();
		XS vn,vs;
		if (str[0]=='['&&str.Last()==']') AddGroup(str.SubStr(1,-1));
		else for(int i=0;i<=str.Length();i++) {
			if (i==str.Length()) ins=5;
			else switch (str[i]) {
				case '=': ins=0; break;
				case '\'': ins=1; break;
				case '"': ins=2; break;
				case ';': case '#': ins=3; break;
				default: ins=4;
			}
			state=automat[ins][state];
			switch (state) {
				case -1: MessageBox(0,(XS("Incorrect sequense on line ")+line).c_str(),
					"INI Parser Warning",MB_ICONWARNING); i=str.Length(); state=0; break;
				case 0: vn+=str[i];
				case 1: break;
				case 2: case 3: case 4: vs+=str[i]; break;
				case 5: AddVar(vn.Trim()); if (!str.IsEmpty()) SetString(vs);
					i=str.Length(); state=0; break;
				case 6: case 7: state-=4; break;
			}
		}
		line++;
	}
	fclose(file);
	return true;
}
bool INI::Save(const XS&name) {
	FILE *file=fopen(name.c_str(),"w");
	Group *gt=root;
	Var *vt=root->root;
	if (!file) return false;
	do {
		fwrite(("["+gt->name+"]").c_str(),1,gt->name.Length(),file);
		do fwrite((vt->name+"="+vt->value+"\n").c_str(),1,
			vt->name.Length()+vt->value.Length()+2,file);
		while (vt=vt->next);
	} while(gt=gt->next);
	fclose(file);
	return true;
}
void INI::DelGroup() {
	root=DelGroup(root,active);
	active=root;
}
void INI::DelVar() {
	active->root=DelVar(active->root,active->active);
	activevar=active->root;
}
bool INI::FirstGroup() {
	if (!root) return false;
	active=root;
	return true;
}
bool INI::FirstVar() {
	if (!active||!activevar) return false;
	activevar=active->root;
	return true;
}
bool INI::NextGroup() {
	if (!active||!active->next) return false;
	active=active->next;
	return true;
}
bool INI::NextVar() {
	if (!active||!activevar||!activevar->next) return false;
	activevar=activevar->next;
	return true;
}
bool INI::GetGroup(XS&dest) {
	if (!active) return false;
	dest=active->name;
	return true;
}
bool INI::GetVar(XS&dest) {
	if (!active||!activevar) return false;
	dest=activevar->name;
	return true;
}
bool INI::AddGroup(const XS&name) {
	int hash=Hash(name);
	for(Group *gt=root;gt;gt=gt->next)
		if (gt->hash==hash&&gt->name.Cmpi(name)) return false;
	Group*group=new Group;
	group->name=name;
	group->hash=hash;
	group->active=group->root=0;
	if (active) {
		group->next=active->next;
		active->next=group;
		active=group;
		return true;
	}
	group->next=root;
	active=root=group;
	return true;
}
bool INI::AddVar(const XS&name) {
	if (!active) return false;
	int hash=Hash(name);
	for(Var *var=active->root;var;var=var->next)
		if (var->hash==hash&&var->name.Cmpi(name)) return false;
	var=new Var;
	var->name=name;
	var->hash=hash;
	if (active->active) {
		var->next=activevar->next;
		activevar->next=var;
		activevar=var;
		return true;
	}
	var->next=active->root;
	activevar=active->root=var;
	return true;
}
bool INI::RenGroup(const XS&name) {
	if (!active) return false;
	active->name=name;
	active->hash=Hash(name);
	return true;
}
bool INI::RenVar(const XS&name) {
	if (!active||!activevar) return false;
	activevar->name=name;
	activevar->hash=Hash(name);
	return true;
}
bool INI::SetBool(const bool&val) {
	if (!active||!activevar) return false;
	if (val) activevar->value="true";
	else activevar->value="false";
	return true;
}
bool INI::SetInt(const long&val) {
	if (!active||!activevar) return false;
	char buf[12];
	buf[sprintf(buf,"%ld",val)]=0;
	activevar->value=buf;
	return true;
}
bool INI::SetFloat(const double&val) {
	if (!active||!activevar) return false;
	char buf[15];
	buf[sprintf(buf,"%ld",val)]=0;
	activevar->value=buf;
	return true;
}
bool INI::SetString(const XS&str) {
	if (!active||!activevar) return false;
	activevar->value=str;
	return true;
}
bool INI::GetBool(bool&var) {
	if (!active||!activevar) return false;
	XS &str=activevar->value;
	if (!str.IsEmpty()) switch (str[0]) {
		case 'T': case 't': case 'Y': case 'y': case '1':
		var=true; break;
		case 'F': case 'f': case 'N': case 'n': case '0':
		var=false; break;
		default:
		return false;
	}
	else var=false;
	return true;
}
bool INI::GetInt(long&var) {
	if (!active||!activevar) return false;
	sscanf(activevar->value.c_str(),"%ld",&var);
	return true;
}
bool INI::GetFloat(double&var) {
	if (!active||!activevar) return false;
	sscanf(activevar->value.c_str(),"%Le",&var);
	return true;
}
bool INI::GetString(XS&str) {
	if (!active||!activevar) return false;
	str=activevar->value;
	return true;
}
bool INI::SelectGroup(const XS&name) {
	Group *gt=active;
	active=root;
	int hash=Hash(name);
	while(active) if (active->hash==hash&&active->name.Cmpi(name)) return true;
	active=gt;
	return false;
}
bool INI::SelectVar(const XS&name) {
	if (!active) return false;
	Var *vt=activevar;
	activevar=active->root;
	int hash=Hash(name);
	while(activevar) if (activevar->hash==hash&&activevar->name.Cmpi(name)) return true;
	activevar=vt;
	return false;
}
#undef activevar
