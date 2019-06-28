#ifndef DelegateH
#define DelegateH
#pragma comment(lib,"Delegates.lib")
class Event;
class __declspec(dllimport) VoidCast {
	void *pointer;
public:
	VoidCast(...);
	operator void*();
};

namespace DelegateCall {
	enum {
		THISCALL,
		CDECL,
		STDCALL,
		FASTCALL,
		SCDECL,		// Static
		SSTDCALL,	// Static
		SFASTCALL,	// Static
	};
};

class __declspec(dllimport) DlegateBase {
public:
	void*object,*method,*ctype;		// Main delegate attributes
protected:
	void*esp,*ebp,*ret,*esp0,*esp1; // Temp variables
	static void*__cdecl Probe();	// Stack and stack frame probe
	static void*__cdecl Helper();	// Helper for templated Delegate implementation
public:
	DlegateBase(const DlegateBase&);
	DlegateBase(VoidCast object,VoidCast method,int type=DelegateCall::THISCALL);
	bool __inline operator==(const DlegateBase&d)
		{ return (object==d.object&&method==d.method&&ctype==d.ctype); }
	void*__fastcall operator()(...);
	DlegateBase&operator=(const DlegateBase&);
	operator bool();
};

template<class R=void>
class Delegate:public DlegateBase {
public:
	__inline Delegate(const DlegateBase&d):DlegateBase(d){}
	__inline Delegate(const Delegate&d):DlegateBase((DlegateBase&)d){}
	__inline Delegate(VoidCast object,VoidCast method,int type=DelegateCall::THISCALL)
		:DlegateBase(object,method,type){}
	R operator()(...) { DlegateBase::Helper(); return *(R*)0; }
	__inline operator Delegate&() { return *this; }
};

void Delegate<void>::operator()(...) { DlegateBase::Helper(); }

class Event {
	static void*dobj,*dmet;	// Little optimizing :)
protected:
	void*esp,*ebp,*ebx,*ret,*esp0,*esp1;// Temp variables
	struct List {
		void*object,*method,*ctype;		// Main 'delegate' attributes
		List*next;
	}*list;	// 'delegates' list
	void destroy();
	static List*__stdcall del(List*);
	static __inline List*del(List*l,void*o,void*m) { dobj=o; dmet=m; return del(l); }
	Event&__fastcall append(void*,void*,void*);
	__inline Event&append(void*o,void*m,int t) { return append(o,m,(void*)t); }
	Event&__fastcall append(const Event&);
public:
	__inline Event() { list=0; }
	__inline Event(const Event&e) { list=0; append(e); }
	__inline Event(const DlegateBase&d) { list=0; append(d.object,d.method,d.ctype); }
	__inline Event(VoidCast object,VoidCast method,int ctype=DelegateCall::THISCALL)
		{ list=0; append(object,method,ctype); }

	~Event() { destroy(); }

	__inline Event&Append(VoidCast object,VoidCast method,int ctype=DelegateCall::THISCALL)
		{ return append(object,method,ctype); }
	__inline Event&Delete(VoidCast object,VoidCast method)
		{ list=del(list,object,method); return *this; }

	__declspec(dllimport) void operator()(...);
	__inline Event&operator=(const Event&e)
		{ if (&e==this) return *this; destroy(); list=0; return append(e); }
	__inline operator bool() { return list!=0; }

	__inline Event&operator+=(const Event&e) { return append(e); }
	__inline Event&operator+=(const DlegateBase&d)
		{ return append(d.object,d.method,d.ctype); }
	__inline Event&operator-=(const DlegateBase&d)
		{ list=del(list,d.object,d.method); return *this; }
};
#endif