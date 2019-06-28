#ifndef HcastH
#define HcastH
template<class T,class F>__inline T horrible_cast(F obj) {
	union {
		T t;
		F f;
	} u;
	u.f=obj;
	return u.t;
}
#endif