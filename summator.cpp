#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <string.h>

#define MIN(a,b) a>b?b:a
#define MAX(a,b) a<b?b:a

void d(const char *str) { printf("%s\n",str);}
//void d(const char *str,int n) { printf("%s%d\n",str,n);}

class number {
	char *ptr;
public:
	unsigned long len;
	char sign;
	number() {
		sign=0;
		ptr=0;
		len=0;
	}
	number(unsigned long n) {
		sign=0;
		len=n;
		if (n) ptr=new char[len];
	}
	number(const number&temp) {
		sign=temp.sign;
		len=temp.len;
		if (temp.ptr) {
			ptr=new char[len];
			memcpy(ptr,temp.ptr,len);
		}
	}
	number(const char *str);
	~number() {
		if (ptr) delete []ptr;
	}
	/*
	void resize(unsigned int n) {
		if (!n) {
			if (ptr) delete []ptr;
			len=0;
			return;
		}
		char *temp=new char[n];
		memset(temp,0,n);
		if (ptr) {
			memcpy(temp,ptr,MIN(len,n));
			delete []ptr;
		}
		len=n;
		ptr=temp;
	}
	void operator++() {
		resize(len+1);
	}
	void operator--() {
		if (len) resize(len-1);
	}
	*/
	void trim();
	char &operator[](unsigned long pos) {
		if (pos<len) return ptr[len-pos-1];
		else {
			getch();
			exit(0);
		}
	}
	void clear() {
		memset(ptr,0,len);
	}
	void print();
};

number::number(const char *str) {
	if (str[0]=='-') {
		sign=1;
		str++;
	}
	else sign=0;
	len=strlen(str);
	for(int i=0;i<len;i++) if (str[i]>='0'&&str[i]<='9') ptr[i]=str[i]-0x30;
}

void number::trim() {
	long n=0;
	while(n<len&&!ptr[n++]);
	len-=n;
	char *temp=new char[++len];
	if (ptr) {
		memmove(temp,(void*)(ptr+n-1),len);
		delete []ptr;
	}
	ptr=temp;
}

void number::print() {
	for(long i=0;i<len;i++) printf("%u",(int)ptr[i]);
}

number sum(const number &x,const number &y) {
	long max=MAX(x.len,y.len),min=MIN(x.len,y.len);
	number r(max+1);
	char c,o=0;
	for(long i=0;i<max;i++) {
		c=o;
		if (i<x.len) c+=x[i];
		if (i<y.len) c+=y[i];
		if (c>9) {
			o=1;
			c-=10;
		}
		else o=0;
		r[i]=c;
	}
	r[i]=o;
	r.trim();
	return r;
}

number mul(const number &x,const number &y) {
	number r(x.len+y.len),t(x.len+1);
	char c,o=0;
	int temp;
	for(long yi=0;yi<y.len;yi++) {
		for(long xi=0;xi<x.len;xi++) {
			c=x[xi]*y[yi]+o;
			if (c>9) {
				o=div(c,10).quot;
				c%=10;
			}
			else o=0;
			t[xi]=c;
		}
		t[x.len]=o;
		o=0;
		for(long i=0;i<t.len;i++) {
			temp=i+yi;
			r[temp]+=t[i]+o;
			if (r[temp]>9) {
				o=1;
				r[temp]-=10;
			}
			else o=0;
		}
		if (++temp<r.len) r[temp]=o;
		o=0;
		t.clear();
	}
	r.trim();
	return r;
}

void main() {
	clrscr();
	number
	x("7654767593042431056890347250634205632056324053"),
	y("463497534075988787878878887320148023614872309156872196478321684796213956014826523648632184623189461284565467365378435625463");
	number r(mul(x,y));
	r.print();
	getch();
}
