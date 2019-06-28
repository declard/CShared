#include "Delegates.h"

void *Event::dobj,*Event::dmet;

#pragma warning(push)
#pragma warning(disable:4273)
#pragma warning(disable:4731)
void*__cdecl DlegateBase::Probe() {
	__asm mov ecx,esp
	__asm mov edx,ebp
	return 0;
}

void*__cdecl DlegateBase::Helper() {
	__asm {
		call DlegateBase::Probe
		sub ecx,esp
		lea ecx,[ecx*2+4]
		sub esp,ecx
		cmp ebp,edx
		je OK
		mov ebp,[esp-4]
OK:		lea eax,DlegateBase::operator()
		jmp dword ptr [eax]
		ret
	}
}
#pragma warning(pop)

void Event::destroy() {
	List*temp;
	while(list) {
		temp=list->next;
		delete list;
		list=temp;
	}
}
Event::List*__stdcall Event::del(List*tail) {
	if (!tail) return 0;
	if (tail->object==dobj&&tail->method==dmet) {
		List*temp=tail->next;
		delete tail;
		return del(temp);
	}
	tail->next=del(tail->next);
	return tail;
}
Event&__fastcall Event::append(void*object,void*method,void*ctype) {
	int type=(int)ctype;
	if ((!object&&!(type&4))||!method||type>6) return *this;
	List*temp=new List;
	temp->next=list;
	list=temp;
	list->object=object;
	list->method=method;
	list->ctype=ctype;
	return *this;
}
Event&__fastcall Event::append(const Event&e) {
	List*temp,*dl=e.list;
	while(dl) {
		temp=new List;
		temp->next=list;
		list=temp;
		list->object=dl->object;
		list->method=dl->method;
		list->ctype=dl->ctype;
		dl=dl->next;
	}
	return *this;
}