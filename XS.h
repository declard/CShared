#ifndef XSH
#define XSH
#include "hcast.h"
#define XS_USE_LOCALE

#if defined(_MSC_VER)&&!defined(__MWERKS__)&&!defined(__VECTOR_C)&&!defined(__ICL)&&!defined(__BORLANDC__)
#define XS_IS_MSVS
#endif

#ifdef __BORLANDC__
#include <system.hpp>
#endif

extern "C++" class XS {
#ifdef XS_USE_LOCALE
public:
	struct Locale {
		unsigned char _toupper[256],_tolower[256];
	};
#endif
protected:
	static const char*Delimeters;
	
	struct container {
		char *_data;
		long _len;
		unsigned int _count;
	} *_ptr;
#ifdef XS_USE_LOCALE
	Locale*_locale;
	char toupper(unsigned char c) const;
	char tolower(unsigned char c) const;
#endif

	// Container service functions
	void separate();
	void separate(char);
	void fixzerodata();
	void numeric_ctor(const char*,...);
	void clear();
public:
	// Useful functions
#ifndef XS_USE_LOCALE
	static char __inline toupper(char c) { if (c<='z'&&c>='a') return c+'A'-'a'; if (c<='ÿ'&&c>='à') return c+'À'-'à'; return c; }
	static char __inline tolower(char c) { if (c<='Z'&&c>='A') return c+'a'-'A'; if (c<='ß'&&c>='À') return c+'à'-'À'; return c; }
#else
	void __inline SetLocale(Locale&locale) { _locale=&locale; }
	static char __inline toupper(unsigned char c,Locale&locale) { return locale._toupper[c]; }
	static char __inline tolower(unsigned char c,Locale&locale) { return locale._tolower[c]; }
#endif
	static bool __fastcall match(char*,char*,char*,char*);
	
	void __inline ForceSeparate() { separate(); }
	
	void operator()(char*src,long len);
	// Ctors
	XS();
	XS(const char*src);
	XS(const XS&src);
	XS(const XS*src);
	XS(const char*src,long len);
	XS(char src);
	XS(int src) {
		numeric_ctor("%d",src);
	}
	XS(unsigned int src) {
		numeric_ctor("%u",src);
	}
	XS(long src) {
		numeric_ctor("%ld",src);
	}
	XS(unsigned long src) {
		numeric_ctor("%lu",src);
	}
	XS(double src) {
		numeric_ctor("%.12Lf",src);
	}
#ifdef __BORLANDC__
	XS(const AnsiString&str);

	AnsiString __fastcall ToAnsiString();
	operator AnsiString();
#endif
	double ToDouble();
	long ToLong();

	// Dtor
	~XS();

	// Concatenation
	XS __fastcall operator +(const XS) const;
	XS __fastcall operator +(const char*) const;
	friend XS __fastcall operator+(const char*,const XS);
	XS __fastcall operator +(const char) const;
	friend XS __fastcall operator+(const char,const XS);

	// Assignments
	XS& __fastcall operator =(const XS rhs);
	XS& __fastcall operator +=(const XS rhs);
	XS& __fastcall operator +=(char c);

	// Comparisons
	bool __fastcall operator ==(const XS rhs) const;
	bool __fastcall operator !=(const XS rhs) const;
	bool __fastcall Cmp(const XS rhs) const;
	bool __fastcall Cmpi(const XS rhs) const; //ignorecase

	// Relations
	bool __fastcall StartsWith(const XS str) const;
	bool __fastcall EndsWith(const XS str) const;
	bool __fastcall StartsWithi(const XS str) const;
	bool __fastcall EndsWithi(const XS str) const;
	bool __fastcall IsIn(const char a) const;
	bool __fastcall IsIn(const XS str) const;
	bool __fastcall Match(const XS mask) const;

	// Iterators
	char& __fastcall operator [](const long idx);
	const char  __fastcall operator [](const long idx) const;
	char __fastcall Last() const;

	// Query string attributes
	long __inline Length()const { return _ptr->_len; }
	__declspec(property(get=Length)) long Len;
	bool __inline IsEmpty() const { return !(_ptr->_len); }
	bool __inline operator!() const { return !(_ptr->_len); }
	__inline operator bool() const { return _ptr->_len!=0; }
	__inline const char* c_str() const { return _ptr->_data; }
	__declspec(property(get=c_str)) const char*Data;

	//
	XS&__fastcall SetLen(long newLength);

	// String modifiers
	XS __fastcall Insert(const XS str,long index) const;
	XS __fastcall Delete(long index,long count) const;
	XS __fastcall ToLower() const;
	XS __fastcall ToUpper() const;
	XS __fastcall Trim() const;
	XS __fastcall LTrim() const;
	XS __fastcall RTrim() const;
	XS __fastcall Trim(const XS dl) const;
	XS __fastcall LTrim(const XS dl) const;
	XS __fastcall RTrim(const XS dl) const;
	XS __fastcall SubStr(long index,long count) const;
	XS __fastcall SubStr(long index) const;
	XS __fastcall Replace(const XS from,const XS to) const;
	XS __fastcall Replace(char from,char to) const;
	XS __fastcall Remove(const XS mask) const;
	XS __fastcall Remove(char c) const;

	// Search
	long __fastcall Pos(char a,long start=0) const;
	long __fastcall Pos(const XS str,long start=0) const;

	// Special
	XS&Explode(char d,long n,...);
	bool IsNumber() const;

	// Token funcs
	XS __fastcall GetTok(long n,char d) const;
	long __fastcall FindTok(const XS mask,char d) const;
	long __fastcall TokPos(const XS mask,char d) const;
	long __fastcall NumTok(char d) const;
};


extern "C++" class XSBuilder {
protected:
	static const long _initialCapacity = 256;
	char*_data;
	long _len,_capacity;

	void Realloc(long newCapacity);
public:
	XSBuilder();
	XSBuilder(long capacity);
	XSBuilder(XS str);
	~XSBuilder();
	void Expand(long newLen);
	char& __fastcall operator [](long idx);
	long __inline Length() { return _len; }
	bool Length(long value);
	operator XS() { return XS(_data, _len); }
	void Append(char ch);
	XSBuilder&operator+=(char ch) { Append(ch); return *this; }
	void Append(char ch,long count);
	void Append(XS str);
	XSBuilder&operator+=(XS str) { Append(str); return *this; }
	void Append(long value);
	XSBuilder&operator+=(long value) { Append(value); return *this; }
};


#ifdef XS_USE_LOCALE
extern XS::Locale CP1251;
#endif
#endif
