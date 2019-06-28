#include <memory.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "XS.h"
const char* XS::Delimeters=" \t\n\r";

#ifdef XS_IS_MSVS
#pragma warning(disable:4996)
#endif

#ifdef XS_USE_LOCALE
char XS::toupper(unsigned char c) const {
	return _locale->_toupper[c];
}
char XS::tolower(unsigned char c) const {
	return _locale->_tolower[c];
}

XS::Locale CP1251={
	{
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
		0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
		0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
		0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
		0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x7b,0x7c,0x7d,0x7e,0x7f,
		0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf
	},{
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
		0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		0x40,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
		0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x5b,0x5c,0x5d,0x5e,0x5f,
		0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
		0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
		0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
	}
};
#endif

void XS::separate() {
	if (_ptr) {
		if (_ptr->_count==1) return;
		container*old=_ptr;
		_ptr=new container;
		_ptr->_len=old->_len;
		if (old->_data) {
			_ptr->_data=new char[_ptr->_len+1];
			memcpy(_ptr->_data,old->_data,_ptr->_len);
			_ptr->_data[_ptr->_len]=0;
		}
		else _ptr->_data=0;
		if (!--old->_count) {
			if (old->_data) delete []old->_data;
			delete old;
		}
	}
	else {
		_ptr=new container;
		_ptr->_data=0;
		_ptr->_len=0;
	}
	_ptr->_count=1;
}

void XS::separate(char) {
#ifdef XS_USE_LOCALE
	_locale=&CP1251;
#endif
	_ptr=0;
	separate();
}

void XS::fixzerodata() {
	if (_ptr->_data) return;
	_ptr->_data=new char[1];
	_ptr->_data[0]=0;
}

void XS::numeric_ctor(const char*format,...) {
	separate(0);
	char*&_data=_ptr->_data,buf[30];
	long&_len=_ptr->_len,*_ptr=(long*)((char*)&format+sizeof(format));
	_len=sprintf(buf,format,*_ptr,_ptr[1]);
	_data=new char[_len+1];
	memcpy(_data,buf,_len);
	_data[_len]=0;
}

void XS::clear() {
	if (_ptr&&!--_ptr->_count) {
		if (_ptr->_data) delete []_ptr->_data;
		delete _ptr;
	}
	_ptr=0;
}

bool __fastcall XS::match(char*mptr,char*mend,char*sptr,char*send) {
	while (mptr<mend) {
		switch(*mptr) {
		case '?':
			if (sptr++>=send) return false;
			mptr++;
			break;
		case '*':
			if (++mptr>=mend) return true;
			while (!match(mptr,mend,sptr,send)) if (sptr>=send) return false; else sptr++;
			return true;
		case '\\':
			switch (*++mptr) {
				case '*': case '?': case '\\': if (*mptr++!=*sptr++) return false; break;
				default: if (*sptr++!='\\') return false;
			}
			break;
		default:
			if (*mptr++!=*sptr||sptr++>=send) return false;
		}
	}
	if (sptr==send) return true;
	return false;
}



void XS::operator()(char*src,long len) {
	clear();
	separate();
	if (len&&src) {
		_ptr->_data=new char[len+1];
		memcpy(_ptr->_data,src,len);
		_ptr->_data[len]=0;
		_ptr->_len=len;
	}
	else fixzerodata();
}

XS::XS() {
	separate(0);
	fixzerodata();
}
XS::XS(const char* src) {
	separate(0);
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	if (!src||!src[0]) {
		fixzerodata();
		return;
	}
	while(src[_len]) _len++;
	_data=new char[_len+1];
	memcpy(_data,src,_len);
	_data[_len]=0;
}
XS::XS(const XS&src) {
#ifdef XS_USE_LOCALE
	_locale=src._locale;
#endif
	_ptr=src._ptr;
	if (!_ptr) separate(),fixzerodata();
	else _ptr->_count++;
}
XS::XS(const XS*src) {
#ifdef XS_USE_LOCALE
	_locale=src->_locale;
#endif
	_ptr=src->_ptr;
	if (!_ptr) separate(),fixzerodata();
	else _ptr->_count++;
}
XS::XS(const char* src,long len) {
	separate(0);
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	_len=len;
	if (len<=0) {
		fixzerodata();
		return;
	}
	_data=new char[len+1];
	memcpy(_data,src,len);
	_data[len]=0;
}
XS::XS(char src) {
	separate(0);
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	_len=1;
	_data=new char[2];
	_data[0]=src;
	_data[1]=0;
}

#ifdef __BORLANDC__
XS::XS(const AnsiString&str) {
	separate(0);
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	_len=str.Length();
	if (!_len) {
		fixzerodata();
		return;
	}
	_data=new char[_len+1];
	memcpy(_data,str.c_str(),_len);
	_data[_len]=0;
}

AnsiString __fastcall XS::ToAnsiString() {
	if (_ptr->_data) return AnsiString(_ptr->_data,_ptr->_len);
	return AnsiString();
}
XS::operator AnsiString() {
	if (_ptr->_data) return AnsiString(_ptr->_data,_ptr->_len);
	return AnsiString();
}
#endif

double XS::ToDouble() {
	double res;
	if (!sscanf(_ptr->_data,"%le",&res)) throw "Can't convert XS into double";
	return res;
}
long XS::ToLong() {
	int res;
	if (!sscanf(_ptr->_data,"%ld",&res)) throw "Can't convert XS into long";
	return res;
}

XS::~XS() {
	clear();
}


XS __fastcall operator+(const char* lhs, const XS rhs) {
	XS temp(lhs);
	temp+=rhs;
	return temp;
}
XS __fastcall XS::operator+(const char*rhs) const {
	XS temp(this);
	temp+=XS(rhs);
	return temp;
}
XS __fastcall XS::operator+(const XS rhs) const {
	XS temp(this);
	temp+=rhs;
	return temp;
}
XS __fastcall operator+(const char lhs,const XS rhs) {
	XS temp(lhs);
	temp+=rhs;
	return temp;
}
XS __fastcall XS::operator+(const char rhs) const {
	XS temp(this);
	temp+=rhs;
	return temp;
}


XS& __fastcall XS::operator=(const XS rhs) {
	if (this==&rhs) return *this;
	clear();
	_ptr=rhs._ptr;
	if (!_ptr) separate(),fixzerodata();
	else _ptr->_count++;
	return *this;
}
XS& __fastcall XS::operator+=(const XS  rhs) {
	if (!rhs) return *this;
	separate();
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data,*temp;
	temp=new char[_len+rhs._ptr->_len+1];
	memcpy(temp,_data,_len);
	delete [] _data;
	_data=temp;
	memcpy(temp+_len,rhs._ptr->_data,rhs._ptr->_len);
	_len+=rhs._ptr->_len;
	_data[_len]=0;
	return *this;
}
XS& __fastcall XS::operator+=(char c) {
	separate();
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data,*temp;
	temp=new char[_len+2];
	memcpy(temp,_data,_len);
	delete [] _data;
	_data=temp;
	_data[_len++]=c;
	_data[_len]=0;
	return *this;
}

bool __fastcall XS::operator==(const XS  rhs) const {
	if (this==&rhs||_ptr==rhs._ptr) return true;
	if (_ptr->_len!=rhs._ptr->_len||memcmp(_ptr->_data,rhs._ptr->_data,_ptr->_len)) return false;
	return true;
}
bool __fastcall XS::operator!=(const XS  rhs) const {
	return !operator==(rhs);
}
bool __fastcall XS::Cmp(const XS  rhs) const {
	return operator==(rhs);
}
bool __fastcall XS::Cmpi(const XS  rhs) const {
	if (this==&rhs||_ptr==rhs._ptr) return true;
	char*s0=_ptr->_data,*s1=rhs._ptr->_data;
	if (_ptr->_len!=rhs._ptr->_len) return false;
	for(long i=0;i<_ptr->_len;i++) if (tolower(*s0++)!=tolower(*s1++)) return false;
	return true;
}
bool __fastcall XS::StartsWith(const XS str) const {
	if (str._ptr->_len>_ptr->_len) return false;
	if (!str._ptr->_len) return true;
	char*data0=_ptr->_data,*data1=str._ptr->_data;
	long len=str._ptr->_len;
	while(len--) if (*data0++!=*data1++) return false;
	return true;
}
bool __fastcall XS::EndsWith(const XS str) const {
	if (str._ptr->_len>_ptr->_len) return false;
	if (!str._ptr->_len) return true;
	char*data0=_ptr->_data+_ptr->_len,*data1=str._ptr->_data+str._ptr->_len;
	long len=str._ptr->_len;
	while(len--) if (*--data0!=*--data1) return false;
	return true;
}
bool __fastcall XS::StartsWithi(const XS str) const {
	if (str._ptr->_len>_ptr->_len) return false;
	if (!str._ptr->_len) return true;
	char*data0=_ptr->_data,*data1=str._ptr->_data;
	long len=str._ptr->_len;
#ifdef XS_USE_LOCALE
	while(len--) if (tolower(*data0++)!=tolower(*data1++)) return false;
#else
	while(len--) if (tolower(*data0++,*_locale)!=tolower(*data1++,*str._locale)) return false;
#endif
	return true;
}
bool __fastcall XS::EndsWithi(const XS str) const {
	if (str._ptr->_len>_ptr->_len) return false;
	if (!str._ptr->_len) return true;
	char*data0=_ptr->_data+_ptr->_len,*data1=str._ptr->_data+str._ptr->_len;
	long len=str._ptr->_len;
#ifndef XS_USE_LOCALE
	while(len--) if (tolower(*--data0)!=tolower(*--data1)) return false;
#else
	while(len--) if (tolower(*--data0,*_locale)!=tolower(*--data1,*str._locale)) return false;
#endif
	return true;
}
bool __fastcall XS::IsIn(const char a) const {
	for(long i=0;i<_ptr->_len;i++) if (_ptr->_data[i]==a) return true;
	return false;
}
bool __fastcall XS::IsIn(const XS str) const {
	long tlen=_ptr->_len,slen=str._ptr->_len;
	char*tdata=_ptr->_data,*end,*sdata=str._ptr->_data;
	if (!slen) return true;
	if (!tlen) return false;
	if (slen>5) {
		long i,j,k,*next;
		next=new long[slen];
		j=0; k=next[0]=-1;
		while (j<slen-1) {
			while (k>=0&&sdata[j]!=sdata[k]) k=next[k];
			if (sdata[++j]==sdata[++k]) next[j]=next[k]; else next[j]=k;
		}
		for(i=j=k=0;j<slen&&i<tlen;i++,j++)
			while (j>=0&&tdata[i]!=sdata[j]) j=next[j];
		delete []next;
		if (j==slen) return true;
		return false;
	}
	end=tdata+tlen-slen;
	for(long i;tdata<end;tdata++) {
		for(i=0;i<slen;i++) if (tdata[i]!=sdata[i]) break;
		if (i==slen) return true;
	}
	return false;
}


bool __fastcall XS::Match(const XS mask) const {
	char*sptr=_ptr->_data,*mptr=mask._ptr->_data;
	return match(mptr,mptr+mask._ptr->_len,sptr,sptr+_ptr->_len);
}


char& __fastcall XS::operator [](long idx) {
	if (idx<0) idx+=_ptr->_len;
	if (idx<0||idx>=_ptr->_len) throw "XS: [] is out of bound";
	separate();
	return _ptr->_data[idx];
}
const char __fastcall XS::operator [](long idx) const {
	if (idx<0) idx+=_ptr->_len;
	if (idx<0||idx>=_ptr->_len) throw "XS: [] is out of bound";
	return _ptr->_data[idx];
}
char __fastcall XS::Last() const {
	if (!_ptr->_len) throw "XS: There is no Last char";
	return _ptr->_data[_ptr->_len-1];
}


XS&__fastcall XS::SetLen(long len) {
	if (len==_ptr->_len) return *this;
	separate();
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	if (len<0) len+=_len;
	if (!len) {
		clear();
		separate();
		fixzerodata();
		return *this;
	}
	char *temp=new char[len+1];
	memset(temp,0,len+1);
	memcpy(temp,_data,(len<_len?len:_len));
	_len=len;
	_data=temp;
	return *this;
}


XS __fastcall XS::Insert(const XS str,long index) const {
	if (index>_ptr->_len) index=_ptr->_len;
	if (index<0) index=_ptr->_len+index+1;
	if (index<0) index=0;
	if (!str) return *this;
	if (!_ptr->_len) return str;
	long len=_ptr->_len;
	char*data=_ptr->_data;
	char*temp=new char[len+str._ptr->_len+1];
	if (index) memcpy(temp,data,index);
	memcpy(temp+index,str._ptr->_data,str._ptr->_len);
	if (index<len) memcpy(temp+index+str._ptr->_len,data+index,len-index);
	XS res(temp,len+str._ptr->_len);
	delete []temp;
	return res;
}
XS __fastcall XS::Delete(long index,long count) const {
	if (!index&&count==_ptr->_len) return XS();
	long len=_ptr->_len;
	char*data=_ptr->_data;
	if (index<0) index+=len;
	if (index<0) index=0;
	if (count<0) count=len-index+count;
	if (count<=0) return *this;
	len-=count;
	char *temp=new char[len+1];
	if (index) memcpy(temp,data,index);
	if (len!=index) memcpy(temp+index,data+index+count,len-index);
	XS res(temp,len);
	delete []temp;
	return res;
}
XS __fastcall XS::ToLower() const {
	long _len=_ptr->_len;
	XS temp(*this);
	if (!_len) return temp;
	temp.separate();
	char*str=temp._ptr->_data;
	while(_len--) *str=tolower(*str),str++;
	return temp;
}
XS __fastcall XS::ToUpper() const {
	long _len=_ptr->_len;
	XS temp(*this);
	if (!_len) return temp;
	temp.separate();
	char*str=temp._ptr->_data;
	while(_len--) *str=toupper(*str),str++;
	return temp;
}

XS __fastcall XS::Trim(const XS dl) const {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	long s,e;
	for(s=0;s<_len;s++) if (!dl.IsIn(_data[s])) break;
	for(e=_len;e;e--) if (!dl.IsIn(_data[e-1])) break;
	return SubStr(s,e-s);
}
XS __fastcall XS::LTrim(const XS dl) const {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	long i;
	for(i=0;i<_len;i++) if (!dl.IsIn(_data[i])) break;
	return SubStr(i);
}
XS __fastcall XS::RTrim(const XS dl) const {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	long i;
	for(i=_len;i;i--) if (!dl.IsIn(_data[i-1])) break;
	return SubStr(0,i);
}

XS __fastcall XS::Trim() const {
	return Trim(Delimeters);
}
XS __fastcall XS::LTrim() const {
	return LTrim(Delimeters);
}
XS __fastcall XS::RTrim() const {
	return RTrim(Delimeters);
}

XS __fastcall XS::SubStr(long index,long count) const {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	if (!count) return XS();
	if (index<0) index+=_len;
	if (count<0) count+=_len-index;
	if (index+count>_len) count=_len-index;
	return XS(_data+index,count);
}
XS __fastcall XS::SubStr(long index) const {
	return SubStr(index,(index>=0?_ptr->_len:0)-index);
}

XS __fastcall XS::Replace(const XS from,const XS to) const {
	if (!*this&&!from) return to;
	if (!*this||!from||from._ptr->_len>_ptr->_len) return *this;
	if (from._ptr->_len==to._ptr->_len) {
		long rlen=from._ptr->_len;
		XS res(this);
		char*dptr=res._ptr->_data,*dend=dptr+_ptr->_len-rlen+1;
		while(dptr<dend)
			if (!memcmp(dptr,from._ptr->_data,rlen)) {
				memcpy(dptr,to._ptr->_data,rlen);
				dptr+=rlen;
			}
			else dptr++;
		return res;
	}
	else {
		long len=_ptr->_len,count=0,rlen;
		char*dptr=_ptr->_data,*dend=dptr+len-from._ptr->_len+1,**map=new char*[len],*temp,*tptr;
		while(dptr<dend)
			if(!memcmp(dptr,from._ptr->_data,from._ptr->_len)) {
				map[count++]=dptr;
				dptr+=from._ptr->_len;
			}
			else dptr++;
		if (!count) {
			delete []map;
			return XS(this);
		}
		dend+=from._ptr->_len-1;
		dptr=_ptr->_data;
		rlen=len+(to._ptr->_len-from._ptr->_len)*count;
		tptr=temp=new char[rlen];
		for(long i=0;i<count;i++) {
			memcpy(tptr,dptr,map[i]-dptr);
			tptr+=map[i]-dptr;
			memcpy(tptr,to._ptr->_data,to._ptr->_len);
			tptr+=to._ptr->_len;
			dptr=map[i]+from._ptr->_len;
		}
		memcpy(tptr,dptr,dend-dptr);
		delete []map;
		return XS(temp,rlen);
	}
}
XS __fastcall XS::Replace(char from,char to) const {
	XS res(this);
	for(long i=0;i<_ptr->_len;i++) if (_ptr->_data[i]==from) res._ptr->_data[i]=to;
	return res;
}
XS __fastcall XS::Remove(const XS mask) const {
	if (!*this||!mask) return *this;
	long len=_ptr->_len,count=0,rlen;
	char*dptr=_ptr->_data,*dend=dptr+len-mask._ptr->_len+1,**map=new char*[len],*temp,*tptr;
	while(dptr<dend)
		if(!memcmp(dptr,mask._ptr->_data,mask._ptr->_len)) {
			map[count++]=dptr;
			dptr+=mask._ptr->_len;
		}
		else dptr++;
	if (!count) {
		delete []map;
		return XS(this);
	}
	dend+=mask._ptr->_len-1;
	dptr=_ptr->_data;
	rlen=len-mask._ptr->_len*count;
	tptr=temp=new char[rlen];
	for(long i=0;i<count;i++) {
		memcpy(tptr,dptr,map[i]-dptr);
		tptr+=map[i]-dptr;
		dptr=map[i]+mask._ptr->_len;
	}
	memcpy(tptr,dptr,dend-dptr);
	delete []map;
	return XS(temp,rlen);
}

XS __fastcall XS::Remove(char c) const {
	char*dptr=_ptr->_data,*dend=dptr+_ptr->_len,*temp=new char[_ptr->_len],*tptr=temp;
	for(;dptr<dend;dptr++) if (*dptr!=c) *tptr++=*dptr;
	XS res(temp,long(tptr-temp));
	delete []temp;
	return res;
}

long __fastcall XS::Pos(char a,long start) const {
	if (start>=_ptr->_len) return -1;
	if (start<0) start+=_ptr->_len;
	if (start<0) start=0;
	for(long i=start;i<_ptr->_len;i++) if (_ptr->_data[i]==a) return i;
	return -1;
}
long __fastcall XS::Pos(const XS  str,long start) const {
	if (start>=_ptr->_len) return -1;
	if (start<0) start+=_ptr->_len;
	if (start<0) start=0;
	long tlen=_ptr->_len-start,slen=str._ptr->_len;
	char*tdata=_ptr->_data+start,*end,*sdata=str._ptr->_data;
	if (!slen) return 0;
	if (!tlen) return -1;
	if (slen>5) {
		long i,j,k,*next;
		next=new long[slen];
		j=0; k=next[0]=-1;
		while (j<slen-1) {
			while (k>=0&&sdata[j]!=sdata[k]) k=next[k];
			if (sdata[++j]==sdata[++k]) next[j]=next[k]; else next[j]=k;
		}
		for(i=j=k=0;j<slen&&i<tlen;i++,j++)
			while (j>=0&&tdata[i]!=sdata[j]) j=next[j];
		delete []next;
		if (j==slen) return i-slen;
		return -1;
	}
	end=tdata+tlen-slen;
	for(long i;tdata<end;tdata++) {
		for(i=0;i<slen;i++) if (tdata[i]!=sdata[i]) break;
		if (i==slen) return long(tdata-_ptr->_data);
	}
	return -1;
}

XS& XS::Explode(char d,long n,...) {
	separate();
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	XS **args=(XS**)(horrible_cast<long>(&n)+sizeof(n));
	int i,start=0,var=0;
	for(i=0;i<_len;i++) if (_data[i]==d) {
		(**args++)(_data+start,i++-start);
		if (++var==n) break;
		start=i;
	}
	if (_len&&++var<=n) (**args)(_data+start,i++-start);
	if (i+1>=_len) {
		clear();
		separate();
		fixzerodata();
	}
	else operator=(Delete(0,i));
	return *this;
}

bool XS::IsNumber() const  {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	if (!_len) return false;
	long i=0;
	if (_data[0]=='-') {
		if (_len==1) return false;
		i++;
	}
	bool flag=false;
	for(;i<_len;i++) if (_data[i]<'0'||_data[i]>'9') if (_data[i]=='.'&&!flag) flag=true; else return false;
	return true;
}

XS __fastcall XS::GetTok(long n,char d) const {
	long&_len=_ptr->_len;
	char*&_data=_ptr->_data;
	if (n<0) return XS();
	long start,end=-1,i=0,pos=0;
	while(_len>i++) if (_data[i]==d) {
		start=end;
		end=i;
		if (pos++==n) break;
	}
	if (end==-1&&!n) return *this;
	if (end!=-1&&pos>=n) {
		if (i>=_len) return SubStr(end+1);
		return SubStr(start+1,end-start-1);
	}
	return XS();
}

long __fastcall XS::FindTok(const XS mask,char d) const {
	long _len=_ptr->_len,ii,pos=0,len=_len-mask.Length();
	char*_data=_ptr->_data;
	for(long i=0;i<=len;i++) {
		if (_data[i]==d) pos++;
		for(ii=0;ii<mask.Length();ii++) if (mask[ii]!=_data[i+ii]) break;
		if (ii==mask.Length()&&(i==len||_data[i+ii]==d)) return pos;
	}
	return -1;
}


long __fastcall XS::TokPos(const XS mask,char d) const {
	long _len=_ptr->_len,ii,len=_len-mask.Length();
	char*_data=_ptr->_data;
	for(long i=0;i<=len;i++) {
		for(ii=0;ii<mask.Length();ii++) if (mask[ii]!=_data[i+ii]) break;
		if (ii==mask.Length()&&(i+ii==len||_data[i+ii]==d)) return i;
	}
	return -1;
}


long __fastcall XS::NumTok(char d) const {
	long num=0,len=_ptr->_len;
	if (!len) return 0;
	char*data=_ptr->_data;
	for(long i=0;i<=len;i++) if (data[i]==d) num++;
	return num+1;
}


XSBuilder::XSBuilder()	{
	_capacity=_initialCapacity;
	_data=new char[_initialCapacity];
	_len=0;
}
XSBuilder::XSBuilder(long capacity) {
	if (capacity<=0) _capacity=_initialCapacity;
	else _capacity=capacity;
	_data=new char[_capacity];
	_len=0;
}
XSBuilder::XSBuilder(XS str) {
	if (_initialCapacity>=str.Length()) _capacity=_initialCapacity;
	else _capacity=str.Length();
	_data=new char[_capacity];
	_len=0;
	Append(str);
}
XSBuilder::~XSBuilder() {
	delete []_data;
}
void XSBuilder::Realloc(long newCapacity) {
	if (_capacity==newCapacity||newCapacity<=0) return;
	char*data=new char[newCapacity];
	if (_capacity<newCapacity) _len=newCapacity;
	if (_len) memcpy(data,_data,_len);
	_capacity=newCapacity;
	_data=data;
}
void XSBuilder::Expand(long newLen) {
	long newCapacity=_capacity<<1;
	if (newCapacity<newLen) newCapacity=newLen+_initialCapacity;
	Realloc(newCapacity);
}
bool XSBuilder::Length(long value) {
	if (value<0) return false;
	if (value<=_len) {
		_len=value;
		_data[_len]=0;
	}
	else {
		Realloc(value);
		memset(_data+_len,0,value-_len);
		_len=value;
	}
	return true;
}
void XSBuilder::Append(char ch) {
	if (_len==_capacity) Realloc(_capacity<<1);
	_data[_len++]=ch;
}
void XSBuilder::Append(char ch,long count) {
	int newLen=_len+count;
	if (newLen>_capacity) Expand(newLen);
	for(int i=_len;i<newLen;i++) _data[i]=ch;
	_len = newLen;
}
void XSBuilder::Append(XS str) {
	int strLen=str.Length();
	int newLen=_len+strLen;
	if (newLen>_capacity) Expand(newLen);
	memcpy(_data+_len,str.c_str(),strLen);
	_len=newLen;
}
void XSBuilder::Append(long value) {
	sprintf(_data,"%ld",value);
}
char&__fastcall XSBuilder::operator[](long index) {
	if (index<0) index+=_len;
	if (index<0||index>=_len) throw "XSBuilder [] index is out of bound";
	return _data[index];
}

#ifdef XS_IS_MSVS
#pragma warning(default:4996)
#endif
