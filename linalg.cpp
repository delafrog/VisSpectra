#ifndef LINALG_CPP
#define LINALG_CPP


#include "linalg.h"

using namespace std;


// Implementation of the class vecT<>
//____________________________________
template <class T>
vecT<T>::vecT()
{
	x	= 0x00000000;
	mN	= 0;
	N	= 0;
}
//____________________________________
template <class T>
vecT<T>::vecT(int n){N=0;mN=n;x	= new T [n];}
//____________________________________
template <class T>
vecT<T>::vecT(const T *a,int n)
{
	mN	= N = n;
	x = new T [mN];
	for(int i=0;i<N;++i)x[i] = a[i];
}
//____________________________________
template <class T>
vecT<T>::vecT(const T *a,int n,int m)
{
	N	= n;
	mN	= m;
	x	= new T [mN];
	for(int i=0;i<N;++i)x[i] = a[i];
}
//____________________________________
template <class T>
vecT<T>::vecT(const vecT <T> &r)
{
	N	= r.N;mN	= r.mN;	
	x	= new T [mN];
	//for(int i=0;i<N;++i)x[i]=r.x[i];
	memcpy(x,r.x,N*sizeof(T));
}
//____________________________________
template <class T>
vecT<T>::vecT(const char *a)	// конструктор для строк
{
	int ii;
	ii	= ((int)strlen(a));
	/*ii	= -1;
	do
	{
		ii++;
	}while(a[ii]!='\0');

	ii++;*/
	N	= mN = ii;
	x	= new T [mN];
	memcpy(x,a,N*sizeof(T));
}
//____________________________________
template <class T>
void vecT<T>::addmem(int n)
{
	mN+=n;
	T *x_;
	x_	= new T [mN];
	memcpy(x_,x,N*sizeof(T));
	delete [] x;
	x	= x_;
}
//____________________________________
template <class T>
void vecT<T>::addmem()
{
	mN+=dN;
	T *x_;
	x_	= new T [mN];
	memcpy(x_,x,N*sizeof(T));
	delete [] x;
	x	= x_;
}
//____________________________________
template <class T>
void vecT<T>::setmem(int n)
{
	mN	= n;
	N	= 0;
	delete [] x;
	x	= new T [mN];
}
//____________________________________
template <class T>
void vecT<T>::setmem()
{
	mN	= dN;
	N	= 0;
	delete [] x;
	x	= new T [mN];
}
//____________________________________
template <class T>
void vecT<T>::setlen(int n)			// выделить память на 'n' элементов и установить длину равную N. Предыдущие данные забываются
{
	mN	= N =n;
	delete [] x;
	x	= new T [mN];
	memset(x,0,N*sizeof(T));
}
//____________________________________
template <class T>
void vecT<T>::fsetlen(int n)			// выделить память на 'n' элементов, если нужно, и установить длину равную n. 
{
	if (n > mN)	setmem(n);
	N = n;
}
//____________________________________
template<class T>
void vecT<T>::zero()
{
	memset(x, 0, sizeof(T)*N);
}
//____________________________________
template<class T>
void vecT<T>::setValue(const T &y, int pos)  // установить значение y на позицию pos
{
	if (pos >= mN)
	{
		vecT<T> loc;
		loc.setlen(pos);
		this->swp(loc);
	}
	if (pos == N) N = pos + 1;
	else if (pos > N) {
		memset(x + N, 0, (pos-N)*(sizeof(T)));
		N = pos + 1;
	}
	x[pos] = y;
}
//____________________________________
template <class T>
void vecT<T>::add(const T &y)
{
	if (N>=mN)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		//5memset(x,0,N*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	x[N]	= y;
	N++;
}
//____________________________________
template <class T>
void vecT<T>::add(const T &y,int pos)
{
	if (N>=mN)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		memcpy(x_,x,pos*sizeof(T));
		x_[pos]	= y;
		memcpy(x_+pos+1,x+pos,(N-pos)*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	else
	{
		if(pos<N)
			memmove(x+pos+1,x+pos,(N-pos)*sizeof(T));
		else
		{
			if(pos>mN) addmem(pos-mN);
			N = pos;
		}
		x[pos]	= y;
	}
	N++;
}
//____________________________________
template <class T>
void vecT<T>::add(const vecT<T> &y)
{
	if ((N+y.N)>mN)
	{
		T *x_;
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		memcpy(x_+N,y.x,y.N*sizeof(T));
		x	= x_;	
	}
	else
	{
		memcpy(x+N,y.x,y.N*sizeof(T));
	}
	N	+= y.N;
}
//____________________________________
template <class T>
void vecT<T>::add(const vecT<T> &y,int &pos)
{
	if (N+y.N>mN)
	{
		T *x_;
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,pos*sizeof(T));
		memcpy(x_+pos,y.x,y.N*sizeof(T));
		memcpy(x_+pos+y.N,x+pos,(N-pos)*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	else
	{
		if(pos<N)
			memmove(x+pos+y.N,x+pos,(N-pos)*sizeof(T));
		else
			N = pos;
		memcpy(x+pos,y.x,y.N*sizeof(T));
	}
	N	+= y.N;
}
//____________________________________
template <class T>
void vecT<T>::add(const T* y, const int n)	// вставить в конец массив из 'n' элементов по указателю 'y'.
{
	if ((N+n)>mN)
	{
		T *x_;
		mN	+= n;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		memcpy(x_+N,y,n*sizeof(T));
		x	= x_;	
	}
	else
	{
		memcpy(x+N,y,n*sizeof(T));
	}
	N	+= n;
}
//____________________________________
template <class T>
void vecT<T>::add(const char* y)	// вставить в конец массив из 'n' элементов по указателю 'y'.
{
	int n;
	n	= ((int)strlen(y));
	if ((N+n)>mN)
	{
		T *x_;
		mN	+= n;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		memcpy(x_+N,y,n*sizeof(T));
		x	= x_;	
	}
	else
	{
		memcpy(x+N,y,n*sizeof(T));
	}
	N	+= n;
}

//____________________________________
/*template <class T>
void vecT<T>::adt(T &a,T &b)	// добавить два элемента в конец
{
	if (N>=mN-1)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		delete [] x;
		x	= x_;	
	}
	x[N]	= a;
	N++;
	x[N]	= b;
	N++;
}*/
//____________________________________
template <class T>
void vecT<T>::pst(const vecT<T> &y)		// заменить текущий массив на массив 'y' (с проверкой размера)
{
	if (y.N>mN)
	{
		mN	= y.N;
		delete [] x;
		x	= new T [mN];
	}
	memcpy(x,y.x,y.N*sizeof(T));
	N	= y.N;
}
//____________________________________
template <class T>
void vecT<T>::swp(vecT<T> &y)	// поменять друг с другом текущий массив и массив 'y'
{
	T *z;
	int i;
	i	= y.N;y.N	= N;N	= i;
	i	= y.mN;y.mN	= mN;mN	= i;
	z	= y.x;y.x	= x;x	=z;
}
//____________________________________
template <class T>
void vecT<T>::pad(vecT<T> &y)		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
{
	T *x_;
	if ((N+y.N)>mN)
	{		
		mN	+= y.N;
		x_	= new T [mN];
		//memcpy(x_,x,N*sizeof(T));
		for(int i =0;i<N;i++)x_[i]	= x[i];
		delete [] x;		
		x	= x_;
		//x_	= x+N;
		//for(int i =0;i<y.N;i++)x_[i]	= y.x[i];
		//memcpy(x_+N,y.x,y.N*sizeof(T));
	}
	x_	= x+N;
	for(int i =0;i<y.N;i++)x_[i]	= y.x[i];
	N	+= y.N;
}
//____________________________________
template <class T>
void vecT<T>::pad(T &y)		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
{
	if ((N+1)>mN)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		//memcpy(x_,x,N*sizeof(T));
		for(int i =0;i<N;i++)x_[i]	= x[i];
		delete [] x;
		x	= x_;
	}
	x[N]	= y;
	N	++;
}
//____________________________________
template <class T>
void vecT<T>::adp(T &y)
{

}
//____________________________________
template <class T>
void vecT<T>::adz()
{
	if (N>=mN)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		//5memset(x,0,N*sizeof(T));
		delete [] x;
		x	= x_;	
	}
//	x[N]	= y;
	N++;

}
//____________________________________
/**/
/*template <class T>
//template <class W>
void vecT<T>::pad(vecT<T> &y)		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
{
	if ((N+y.N)>mN)
	{
		T *x_;
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		msT::dlt	= false;
		delete [] x;
		msT::dlt	= true;
		memcpy(x_+N,y.x,y.N*sizeof(T));
		x	= x_;
	}
	else
	{
		memcpy(x+N,y.x,y.N*sizeof(T));
	}
	N	+= y.N;
}/**/
//____________________________________
template <class T>
void vecT<T>::rem()
{
	N--;
	N	= N<0 ? 0 : N;
}
//____________________________________
template <class T>
void vecT<T>::rem(int y)
{
	N	-= y;
	N	= N<0 ? 0 : N;
}
//____________________________________
template <class T>
void vecT<T>::rem(int y,int pos)
{
	if (pos < N) 
	{
		if (pos >= N - y)
		{
			N = pos;
		}
		else
		{
			memmove(x + pos, x + pos + y, (N - pos - y) * sizeof(T));
			N -= y;
		}
		N = N < 0 ? 0 : N;
	}
}
//____________________________________
template <class T>
vecT<T>& vecT<T>::ind(vecT<int> &in, vecT<T> &a)	// запись в массив 'a' элементов массива с позициями из массива 'in';
{
	a.N	= in.N;
	for(int i=0;i<a.N;++i){a.x[i]	= x[in.x[i]];}
	return a;
}
//____________________________________
template <class T>
vecT<T> &	vecT<T>::its(vecT<T> & a,vecT<T> & b)		// возвращает в b пересечение текущего массива и массива 'a'.
{
	b.N	= 0;
	int i,j,k;
	for(i=0;i<N;++i)
	{
		k	= 0;
		for(j=0;j<b.N;j++){if (x[i]==b.x[j]) {k	= 1; break;}}
		if (k==0)
		{
			for(j=0;j<a.N;j++){if (x[i]==a.x[j]) {k	= 1; break;}}
			if (k==1) {b.x[b.N++] = x[i];}
		}
	}
	return b;
}
//____________________________________
template <class T>
inline vecT<T> &	vecT<T>::itss(vecT<T> & a,vecT<T> & b)		// возвращает пересечение текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
{
	T c;
	b.N	= 0;
	int i,j;
	j	= 0;
	if ((a.x[0]>x[N-1])||(x[0]>a.x[a.N-1])) return b;
	c	= x[0];
	for(i=0;(i<N)&&(j<a.N);++i)
	{
		if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];++j;}
		else
		{
			while((x[i]>a.x[j])&&(j<a.N-1)){++j;}
			if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];++j;}
		}
	}
	
	return b;
}
//____________________________________
template <class T>
void	vecT<T>::itssi(vecT<T> & a,vecT<vec2int> &id)	// возвращает индексы пересечения текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
{
	id.N	= 0;
	if ((a.x[0]>x[N-1])||(x[0]>a.x[a.N-1])) return;
	int i,j=0;
	for(i=0;(i<N)&&(j<a.N);++i)
	{
		if (x[i]==a.x[j])
		{
			id.x[id.N].x[0] = i;
			id.x[id.N].x[1] = j;
			++id.N;
			++j;
		}
		else
		{
			while((x[i]>a.x[j])&&(j<a.N-1)){++j;}
			if (x[i]==a.x[j]) 
			{
				id.x[id.N].x[0] = i;
				id.x[id.N].x[1] = j;
				++id.N;
				++j;
			}
		}
	}
	
	//return b;
}
//____________________________________
template <class T>
void	vecT<T>::itssi_(vecT<T> & a,vecT<vec2int> &id)	// аналогично itssi(), но дла случавев когда в тек. массиве имеются повторяющиеся элементы
{
	id.N	= 0;
	if ((a.x[0]>x[N-1])||(x[0]>a.x[a.N-1])) return;
	int i,j=0;
	for(i=0;(i<N)&&(j<a.N);++i)
	{
		if (x[i]==a.x[j])
		{
			id.x[id.N].x[0] = i;
			id.x[id.N].x[1] = j;
			++id.N;
			if(x[i+1]!=a.x[j]) ++j;
		}
		else
		{
			while((x[i]>a.x[j])&&(j<a.N-1)){++j;}
			if (x[i]==a.x[j]) 
			{
				id.x[id.N].x[0] = i;
				id.x[id.N].x[1] = j;
				++id.N;
				if(x[i+1]!=a.x[j]) ++j;
			}
		}
	}
	
	//return b;
}
//____________________________________
template <class T>
inline vecT<T> &	vecT<T>::uni(vecT<T> & a,vecT<T> & b)		// возвращает в b объеденение текущего массива и массива 'a'.
{
	T r;
	int i,j;
	if (b.mN<N+a.N) b.sm(N+a.N);
	memcpy(b.x,x,N*sizeof(T));b.N	= N;	// копируем текущий массив в начало массива b
	for(i=0;i<a.N;++i)	// перебор всех элементов второго массива - a
	{		
		r	= a.x[i];
		for(j=0;(j<b.N)&&(b.x[j]!=r);++j);	// проверка: есть- ли текущий элемент среди элементов массива b
		if (j==b.N) b.x[b.N++] = r;		// если нет, то добавить его в массив b
	}
	return b;
}
//____________________________________
template <class T>
inline vecT<T> &	vecT<T>::unis(vecT<T> & a,vecT<T> & b)		// я??я??я??я??я??я??b я??я??я??я??я?? я??я??я??я??я??я??я??я??я??я??я??я??я??'a'.
{
	T c;
	b.N	= 0;
	int i,j;
	j	= 0;
	if (N>0)
	{
		if (a.x[0]>x[N-1])
		{
			memcpy(b.x,x,N*sizeof(T));
			memcpy(b.x+N,a.x,a.N*sizeof(T));
			b.N=N+a.N;
			return b;
		}
		if (x[0]>a.x[a.N-1])
		{
			memcpy(b.x,a.x,a.N*sizeof(T));
			memcpy(b.x+a.N,x,N*sizeof(T));
			b.N=N+a.N;
			return b;
		}
		c	= x[0];
		for(i=0;i<N;i++)
		{
			if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))) {c = b.x[b.N++]=x[i];j++;}
			else
			{
				while((x[i]>=a.x[j])&&(j<a.N))
				{
					if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
				}
				if ((x[i]!=c)||(b.N==0)) {c = b.x[b.N++]=x[i];}
			}
		}
		while((x[N-1]<a.x[j])&&(j<a.N))
		{
			if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
		}
	}
	else
	{
		memcpy(b.x,a.x,a.N*sizeof(T));
		b.N	= a.N;
	}
	return b;
}
template <class T>
void	vecT<T>::unisi(vecT<T> & a,vecT<T> &b,vecT<int> &id)	// возвращает индексы объединения текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
{
	T c;
	b.N		= 0;
	id.N	= 0;
	int i,j;
	j	= 0;
	if (N>0)
	{
		if (a.x[0]>x[N-1])
		{
			memcpy(b.x,x,N*sizeof(T));
			memcpy(b.x+N,a.x,a.N*sizeof(T));
			b.N=N+a.N;
			memset(id.x,0,N*sizeof(T));
			memset(id.x+N,0x00000001,a.N*sizeof(int));
			id.N = b.N;
		}
		if (x[0]>a.x[a.N-1])
		{
			memcpy(b.x,a.x,a.N*sizeof(T));
			memcpy(b.x+a.N,x,N*sizeof(T));
			b.N=N+a.N;
			memset(id.x,1,a.N*sizeof(T));
			memset(id.x+N,0,N*sizeof(T));
			id.N = b.N;
		}
		c	= x[0];
		for(i=0;i<N;i++)
		{
			if ((x[i]==a.x[j])&&((x[i]!=c)||(b.N==0))){	c = b.x[b.N++]=x[i];j++;}
			else
			{
				while((x[i]>=a.x[j])&&(j<a.N))
				{
					if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
				}
				if ((x[i]!=c)||(b.N==0)) {c = b.x[b.N++]=x[i];}
			}
		}
		while((x[N-1]<a.x[j])&&(j<a.N))
		{
			if ((a.x[j]!=c)||(b.N==0)) c = b.x[b.N++]=a.x[j++];
		}
	}
	else
	{
		memcpy(b.x,a.x,a.N*sizeof(T));
		b.N	= a.N;
	}
//	return b;/**/
}
//____________________________________
template <class T>
vecT<int> &	vecT<T>::fnd(vecT<int> &in,T a)		// находит номера элементов массива равных 'a'.
{
	in.N	= 0;
	for(int i=0;i<N;++i){if (x[i]==a){in.x[in.N++]	= i;}}
	return in;
}
//____________________________________
template <class T>
vecT<int> &	vecT<T>::fnd(vecT<bool> &in,vecT<int> &a)	// находит номера истиных элементов массива 'in' и помещает их в 'a'.
{
	a.N	= 0;
	for(int i=0;i<in.N;++i){if (in.x[i]){a.x[a.N++]	=i;}}
	return a;
}
//____________________________________
template <class T>
void vecT<T>::fnd(vecT<bool> &in,vecT<int> &a,vecT<int> &b)	// находит номера истиных элементов массива 'in' и помещает их в 'a', а ложных - в 'b'.
{
	a.N	= 0;b.N	= 0;
	for(int i=0;i<in.N;++i){if (in.x[i]){a.x[a.N++]	=i;}else{b.x[b.N++]	=i;}}
}
//____________________________________
template <class T>
int	vecT<T>::fnd(const T &a)					// находит номер первого элемента в текущем массиве, который равен 'a'
{
	for(int i=0;i<N;++i){if (x[i]==a){return i;}}
	return -1;
}
//____________________________________
template <class T>
int	vecT<T>::fnd(const T &a,const T &b)// определяет первый номер массива который не равен 'a' и не равен 'b'.
{
	for(int i=0;i<N;i++){if ((x[i]!=a)&&(x[i]!=b)) return i;}
	return -1;
}
//____________________________________
template <class T>
int	vecT<T>::fmr(const T &a)	//находит первый элемента массива больше 'a'
{
	for(int i=0;i<N;i++){if ((x[i]>a)) return i;}
	return -1;
}
//____________________________________
template <class T>
int	vecT<T>::fmre(const T &a)	//находит первый элемента массива больше 'a'
{
	for(int i=0;i<N;i++){if ((x[i]>=a)) return i;}
	return -1;
}
template<class T>
int vecT<T>::fmr(const T & a, int beg)
{
	for (int i = beg; i<N; i++) { if ((x[i]>a)) return i; }
	return -1;
}
template<class T>
int vecT<T>::fmre(const T & a, int beg)
{
	for (int i = beg; i<N; i++) { if ((x[i] >= a)) return i; }
	return -1;
}
//____________________________________
template <class T>
int vecT<T>::idscheck()	// возвращает число совпадений элементов с их индексами для T=int
{
	int ii,jj;
	jj	= 0;
	for(ii=0;ii<N;ii++){if(x[ii]==ii) jj++;}
	return jj;
}
//____________________________________
template <class T>
void vecT<T>::sort()	//   сортировка массива. (метод пузырька)
{
	int i;
	T b;
	bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(x[i]>x[i+1])
			{
			b		= x[i];
			x[i]	= x[i+1];
			x[i+1]= b; 
			ch	= true;
		}
	}while(ch);
}
//____________________________________
template <class T>
void vecT<T>::sort(vecT<T> &a)	// я??я??я??я??я?? я??я??я??я??я?? я??я??я??я??я??. (я??я??я??:-) 
{							// я??я??я??я?? 'a' я??я??я??я?? я??я??я??я??я??я??я??я??я??я??я?? я??я??я??
	if (a.N<N) a.setmem(N);
	memcpy(a.x,x,sizeof(T)*N);
	a.N	= N;
	int i;
	T b;
	bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(a.x[i]>a.x[i+1])
			{
			b		= a.x[i];
			a.x[i]	= a.x[i+1];
			a.x[i+1]= b; 
			ch	= true;
		}
	}while(ch);
}
//____________________________________
template <class T>
void vecT<T>::sort(vecT<T> &a, vecT<int> &j)	// я??я??я??я??я?? я??я??я??я??я?? я??я??я??я??я??. (я??я??я??:-)
{					// я??я??я??я?? 'a' я??я??я??я?? я??я??я??я??я??я??я??я??я??я??я?? я??я??я??, я??я??'j' я??я??я?? я??я??я??я??я??я??
	if (a.N<N) a.setmem(N);
	memcpy(a.x,x,sizeof(T)*N);
	a.N	= N;
	int i,k;
	T b;
	bool ch;	
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(a.x[i]>a.x[i+1])
		{
			b		= a.x[i];
			a.x[i]	= a.x[i+1];
			a.x[i+1]= b; 
			k		= j.x[i];
			j.x[i]	= j.x[i+1];
			j.x[i+1]= k;
			ch	= true;
		}
	}while(ch);
}
//void sort_(vecT<int> &j);	// я??я??я??я??я?? я??я??я??;  я??'j' - я??я??я?? я??я??я??я??я?? 'a'.
//____________________________________
template <class T>
void vecT<T>::sort_(vecT<int> &j)	// сортировка массива. в 'j' - индексы перестановок
{
	int i,k;
	T b;
	bool ch;
	do
	{
		ch	= false;
		for (i=0;i<N-1;i++)
		if(x[i]>x[i+1])
		{
			b		= x[i];
			x[i]	= x[i+1];
			x[i+1]= b;
			k		= j.x[i];
			j.x[i]	= j.x[i+1];
			j.x[i+1]= k;
			ch	= true;
		}
	}while(ch);
}
//____________________________________
template <class T>
void vecT<T>::qsort() // быстрая сортировка (рекурсивный метод)
{
/*	if (N<20)
	{
		sort();
		/*if(N==2)
		{
			if (x[0]>x[1])
			{
				T z;
				z = x[0];
				x[0] = x[1];
				x[1] = z;
			}
		}* /
	}else
	{
		int N1,N2;
		N1 = N/2;
		N2 = N-N1;
		vecT<T> v1,v2;
		v1.x = x;
		v1.mN = N1;
		v1.N = N1;
		v2.x = x+N1;
		v2.mN = N2;
		v2.N = N2;
		v1.qsort();
		v2.qsort();
		if(v1.x[N1-1]>v2.x[0])
		{
			vecT<T> v3;
			v3.setlen(N);
			v1.unis(v2,v3);
			memcpy(x,v3.x,v3.N*sizeof(T));
		}
	}
*/
}
//____________________________________
template <class T>
T vecT<T>::scpr(vecT<T> &r) // скалярное произведение текущего вектора на вектор r
{
	T a = 0;
	for(int i =0;i<N;++i)a+=x[i]*r.x[i];
	return a;
}
//____________________________________
template<class T>
void vecT<T>::cycle_shift(vecT<T> &r, int dn)//  циклический сдвиг текущего массива на dn элементов вправо, результат в r; r(ii) = x(ii-dn)
{
	int ii, jj;
	jj = 0;
	dn = dn >= 0 ? dn : N + dn;
	for (ii = dn; ii < N; ii++)
	{
		r.x[ii] = x[jj++];
	}
	for (ii = 0; ii < dn; ii++)
	{
		r.x[ii] = x[jj++];
	}
	r.N = N;
}
//____________________________________
template<class T>
T vecT<T>::shft_crl(vecT<T>& r, int dn)
{
	T res;
	res = T(0);

	dn = dn >= 0 ? dn : N + dn;
	int ii, jj;
	jj = 0;
	for (ii = dn; ii < N; ii++)
	{
		res += x[ii] * r.x[jj++];
	}
	for (ii = 0; ii < dn; ii++)
	{
		res += x[ii] * r.x[jj++];
	}
	return res;
	/*if(dn>=0)
	{
		int ii, jj;
		jj = 0;
		for (ii = dn; ii < N; ii++)
		{
			res += x[jj++] * r.x[ii];
		}
		for (ii = 0; ii < dn; ii++)
		{
			res += x[jj++] * r.x[ii];
		}
	}
	else
	{
		int ii, jj;
		jj = 0;
		dn = -dn;
		for (ii = dn; ii < N; ii++)
		{
			res += x[ii] * r.x[jj++];
		}
		for (ii = 0; ii < dn; ii++)
		{
			res += x[ii] * r.x[jj++];
		}
	}*/
}
//____________________________________
template<class T>
int vecT<T>::max_crl_shft(vecT<T>& r, int gs)
{
	int idp, idm, id0, Npk, npk;
	/*T krl, krlp, krlm,krl2p,krl2m,krl3p, krl3m; //  максимум должен быть на протяжении от -3 до +3 соседних позиций

	idp = idm = id0 = gs;
	krl = shft_crl(r, id0);
	idp++;
	krlp = shft_crl(r, idp);
	idp++;
	krl2p = shft_crl(r, idp);
	idp++;
	krl3p = shft_crl(r, idp);
	idm--;
	krlm = shft_crl(r, idm);
	idm--;
	krl2m = shft_crl(r, idm);
	idm--;
	krl3m = shft_crl(r, idm);

	if ((krl > krlm)&(krl > krl1m)&(krl > krl2m)&(krl > krlp)&(krl > krl1p)&(krl > krl2p)) return gs;*/
	npk = 3;
	Npk = 2*npk +1;
	vecT<T> krlx(Npk);
	krlx.fsetlen(Npk);
	
	idp = gs - npk;
	for (int ii = 0; ii < krlx.N; ii++)
	{
		krlx.x[ii] = shft_crl(r, idp);
		idp++;
	}

	krlx.max(id0);

	if (id0 == npk) return gs;

	vecT<T> krlx_(krlx.N);
	krlx_.fsetlen(krlx.N);
	T *xx;
	
/*	idp = id0 + npk;
	idp = idp > Npk ? Npk : idp;
	idm = id0 - npk;
	idm = idm < ? 0 : idm;*/

	do {
		if (id0 > npk) // максимум справа от центра
		{
			idm = id0 - npk;
			idp = Npk;
			xx = krlx_.x;
			for (int ii = idm; ii < idp; ii++) { *xx = krlx.x[ii]; xx++; }
			idp += gs - npk;
			idm = Npk - idm;
			for (int ii = idm; ii < Npk; ii++) { krlx_.x[ii] = shft_crl(r, idp); idp++; }
		}
		else
		{
			idp = id0 + npk + 1;
			idm = Npk - idp;
			xx = krlx_.x + idm;//(Npk - idp - 1);
			for (int ii = 0; ii < idp; ii++) { *xx = krlx.x[ii]; xx++; }
			idp = gs - npk -idm;
			for (int ii = 0; ii < idm; ii++) { krlx_.x[ii] = shft_crl(r, idp); idp++; }

		}
		krlx.swp(krlx_);

		gs = gs - npk+id0;
		gs -= gs > N ? N : 0;// gs < 0 ? -N : 0;
	//	gs += gs < 0 ? N : 0;

		krlx.max(id0);

		if (id0 == npk) return gs;
	} while (true);

	/*

	do
	{
		if ((krlm < krl)&(krl < krlp)) // id0++ 
		{
			id0++;
			idp++;
			idm++;
			krlm = krl;
			krl = krlp;
			krlp = shft_crl(r, idp);
		}
		else if ((krlm > krl)&(krl > krlp)) // id0--
		{
			id0--;
			idp--;
			idm--;
			krlp = krl;
			krl = krlm;
			krlm = shft_crl(r, idm);
		}
		else if ((krl < krlm)&(krl < krlp)) 
		{
			if ((krlp > krlm)) // id0++
			{
				id0++;
				idp++;
				idm++;
				krlm = krl;
				krl = krlp;
				krlp = shft_crl(r, idp);
			}
			else //id0--;
			{
				id0--;
				idp--;
				idm--;
				krlp = krl;
				krl = krlm;
				krlm = shft_crl(r, idm);
			}
		}
	} while (!((krl > krlm)&(krl > krlp)));

	return id0;*/
}
//____________________________________
template <class T>
void vecT<T>::var1D(const T &xbeg,const T &dx,const T &xend)	// заполнить массивом от xbeg до  xend  с шагом dx
{
	int N1;
	N1	= (int)((xend - xbeg)/dx); // число элементов
	if(N1>0)
	{
		if((N1*dx)==(xend - xbeg)) N1++;
		if(N1>mN) setmem(N1);
		N	= N1;
		for(int ii=0;ii<N;ii++){x[ii]	= xbeg+dx*ii;}
	}
}
//____________________________________
template <class T>
void vecT<T>::var1D_(const T &xbeg, const T &dx, const int &N1) // заполнить массивом от xbeg с шагом dx на N1 элементов
{
	if (N1>0)
	{
		if (N1 > mN){setmem(N1);}
		N = N1;
		//x[0] = xbeg;
		//T *p = x;
		for (int ii = 0;ii<N;ii++) {x[ii] = xbeg + dx*ii;}
	}
}
//____________________________________
template<class T>
void vecT<T>::interp1(const vecT<T>& x_in, const vecT<T>& y_in, const vecT<T>& x_out)
{
	/*fsetlen(x_out.N);
	vecT<int> ids(N); // номера из x_in , такие что x_in.x[ids.x[jj]]<x_out.x[jj], но x_in.x[ids.x[jj]+1]>x_out.x[jj]

	

	
	int ii;
	ii = 0;
	if (x_out.x[0] < x_in.x[0])
	{
		do
		{
			ids.x[ii] = -1;
			ii++;
		} while (x_out.x[ii] < x_in.x[0]);
	}

	for (; ii < N; ii++)
	{
		if (x_out.x[ii] < x_in.x[0])
		{
			ids.x[ii] = -1;
		}
	}*/
}
//____________________________________
template<class T>
void vecT<T>::Lanczos_interp( const vecT<T>& y_in, int n_, int a_)
{
//	T dlt = (x_in.x[1] - x_in.x[0])/n;
//	x_out.var1D(x_in.x[0], dlt, x_in.last());
	int ii,ie,ib,ilb;
	vecT<T> x0;
	vecT<T> L0;
	x0.var1D(T(-a_), 1.0/T(n_), T(a_));
	L0.lncz(x0, a_);  // вычисление контура сплайн-функции соответсвующей фильтру Ланцоша
	ii = (y_in.N-1)*n_ + 1;
	if (mN < ii) setlen(ii); else { N = ii; zero(); }

	for (ii = 0; ii < a_; ii++)
	{
		ib = 0;
		ie = (ii + a_ )*n_ + 1;
		ilb = (a_ - ii)*n_;
		for (int jj = ib; jj < ie; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N - a_ ; ii++)
	{
		ib = (ii - a_)*n_ ;
		ie = (ii + a_)*n_ + 1;
		ilb = 0;
		for (int jj = ib; jj < ie; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N; ii++)
	{
		ib = (ii - a_)*n_;
		ilb = 0;
		for (int jj = ib; jj < N; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
}
//____________________________________
template<class T>
void vecT<T>::Lanczos_interp(const vecT<T>& y_in, int n_, int a_, const vecT<T> &x0, const vecT<T> &L0) // перегруженная версия для многократного использования с внешним контуром сплайн-фильтра
{
	//	T dlt = (x_in.x[1] - x_in.x[0])/n;
	//	x_out.var1D(x_in.x[0], dlt, x_in.last());
	int ii, ie, ib, ilb;
/*	vecT<T> x0;
	vecT<T> L0;
	x0.var1D(T(-a_), 1.0 / T(n_), T(a_));
	L0.lncz(x0, a_);  // вычисление контура сплайн-функции соответсвующей фильтру Ланцоша*/
	ii = (y_in.N - 1)*n_ + 1;
	if (mN < ii) setlen(ii); else { N = ii; zero(); }

	for (ii = 0; ii < a_; ii++)
	{
		ib = 0;
		ie = (ii + a_)*n_ + 1;
		ilb = (a_ - ii)*n_;
		for (int jj = ib; jj < ie; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N - a_; ii++)
	{
		ib = (ii - a_)*n_;
		ie = (ii + a_)*n_ + 1;
		ilb = 0;
		for (int jj = ib; jj < ie; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N; ii++)
	{
		ib = (ii - a_)*n_;
		ilb = 0;
		for (int jj = ib; jj < N; jj++)
		{
			x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
}
//____________________________________
template<class T>
T vecT<T>::ModeLevel(int Nres)
{
	T r,dr,rx,rn;
	
	rx = max();
	rn = min();
	dr = (rx - rn) / (Nres);
	vecT<int> Hst;
	Hst.setlen(Nres+1);
	int jj;
	for (int ii = 0; ii < N; ii++)
	{
		jj = (int)((x[ii] - rn) / dr);
		Hst.x[jj]++;
	}
	Hst.max(jj);
	r = rn + dr*jj + dr / 2;
	return r;
}
//____________________________________
template<class T>
void vecT<T>::StatDistr(int Nres, T & mode, T & sigma)
{
	T dr, rx, rn;

	rx = max();
	rn = min();
	dr = (rx - rn) / (Nres);
	vecT<int> Hst;
	Hst.setlen(Nres + 1);
	int jj;
	for (int ii = 0; ii < N; ii++)
	{
		jj = (int)((x[ii] - rn) / dr);
		Hst.x[jj]++;
	}
	int kk,sm,sl;
	kk = Hst.max(jj);
	mode = rn + dr*jj + dr / 2;
	//sm = Hst.sum();
	//sm /= 2;
	//sl = kk;
	sm = kk / 2;
	sl = kk;
	int ii;
	for (ii = 1; (ii < jj)&(sl>sm); ii++)
	{
		sl = Hst.x[jj + ii] !=0 ? Hst.x[jj + ii]: sl;
	}
	sigma = dr*ii*2;
}
//____________________________________
template <class W>
vecT<W> operator - (vecT<W> &a)
{
	vecT<W> r(a);
	for(int i = 0;i<r.N;++i) r.x[i]= -r.x[i];
	return r;
}
//____________________________________
template <class W>
vecT<W> operator +(const W &a,const vecT<W> &b)
{
	vecT<W> r;
	r.setlen(b.N);
	for(int i = 0;i<r.N;++i) r.x[i] = a+b.x[i];
	return r;
}
//____________________________________
template <class W>
vecT<W> operator -(const W &a,const vecT<W> &b)
{
	vecT<W> r;
	r.setlen(b.N);
	for(int i = 0;i<r.N;++i) r.x[i] = a-b.x[i];
	return r;
}
//____________________________________
template <class W>
vecT<W> operator *(const W &a,const vecT<W> &b)
{
	vecT<W> r;
	r.setlen(b.N);
	for(int i = 0;i<r.N;++i) r.x[i] = a*b.x[i];
	return r;
}
//____________________________________
template <class W>
vecT<W> operator /(const W &a,const vecT<W> &b)
{
	vecT<W> r;
	r.setlen(b.N);
	for(int i = 0;i<r.N;++i) r.x[i] = a/b.x[i];
	return r;
}
//____________________________________
template <class T>
void vecT<T>::plus(vecT<T> &a,vecT<T> &b) // x = a+b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a.x[i]+b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::minus(vecT<T> &a,vecT<T> &b) // x = a-b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a.x[i]-b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::prod(vecT<T> &a,vecT<T> &b) // x = a*b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a.x[i]*b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::divd(vecT<T> &a,vecT<T> &b) // x = a/b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a.x[i]/b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::plus(T &a,vecT<T> &b) // x = a+b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a+b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::minus(T &a,vecT<T> &b) // x = a-b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a-b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::prod(T &a,vecT<T> &b) // x = a*b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a*b.x[i];
}
//____________________________________
template <class T>
void vecT<T>::divd(T &a,vecT<T> &b) // x = a/b, где x - тек. вектор 
{
	for(int i =0; i<N;++i) x[i] = a/b.x[i];
}
//____________________________________
template<class T>
vecT<T>& vecT<T>::sinc( vecT<T>& x_in)
{
	T loc;
	fsetlen(x_in.N);
	int idz = x_in.fnd(T(0));
	if (idz == -1)
	{
		for (int ii = 0; ii < N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
		}
	}
	else
	{
		for (int ii = 0; ii < idz; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
		}
		x[idz] = 1;
		for (int ii = idz+1; ii < N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
		}
	}
	
	return *this;
}
template<class T>
vecT<T>& vecT<T>::lncz( vecT<T>& x_in, int a)
{
	T loc;
	fsetlen(x_in.N);
	int idz = x_in.fnd(T(0));
	if (idz == -1)
	{
		for (int ii = 0; ii < N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
			loc /= a;
			x[ii] *= sin(loc) / loc;
		}
	}
	else
	{
		for (int ii = 0; ii < idz; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
			loc /= a;
			x[ii] *= sin(loc) / loc;
		}
		x[idz] = 1;
		for (int ii = idz + 1; ii < N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			x[ii] = sin(loc) / loc;
			loc /= a;
			x[ii] *= sin(loc) / loc;
		}
	}

	return *this;
}
//____________________________________
template <class W>
void showfull ( vecT<W> &a)
{
	for(int i =0;i<a.N;i++) 
	{
		cout<<a.x[i]<<endl;
	}
}
//____________________________________
template <class T>
void vecT<T>::setbindec(int n)	// заполнить текущий массив числами 2^k сумма которых даёт входное число n
{
	setmem(32);	// установка на 32 элемента - число бит 4-ёх байт (sizeof(int)=4)
	int ii,jj,kk,ij;

	ii	= n;
	ij	= 0;
	do
	{
		jj	= ii>>1;
		kk	= jj<<1;
		ii	-= kk;
		if (ii==1) 
		{
			ii	= 1<<ij;
			add(ii);
		}else
		{
			add(0);
		}
		ii	= jj;
		ij++;
	}while(jj!=0);
}
//____________________________________
/*//____________________________________
template <class W>
friend ostream & operator << (ostream & stream,const vecT<W> &a)
{

}*/
//____________________________________
//____________________________________

//____________________________class	msT____________________________________________________________________________
//________________________________Реализация методов________________________________________________________________
//____________________________________
/*template <class T>
msT<T>::msT()
{
	x	= 0x00000000;
	mN	= 0;
	N	= 0;
	//dlt	= true;
}
//____________________________________
template <class T>
msT<T>::msT(int n){N=0;mN=n;x	= new T [n];/*dlt	= true;* /}
//____________________________________
template <class T>
msT<T>::msT(const T *a,int n)
{
	mN	= N = n;
	//dlt	= true;
	x = new T [mN];
	for(int i=0;i<N;++i)x[i] = a[i];
}
//____________________________________
template <class T>
msT<T>::msT(const T *a,int n,int m)
{
	N	= n;
	mN	= m;
	//dlt	= true;
	x	= new T [mN];
	for(int i=0;i<N;++i)x[i] = a[i];
}
//____________________________________
template <class T>
msT<T>::msT(const msT <T> &r)
{
	N	= r.N;mN	= r.mN;	
	x	= new T [mN];
	//for(int i=0;i<N;++i)x[i]=r.x[i];
	memcpy(x,r.x,N*sizeof(T));
	//dlt	= true;
}
//____________________________________
template <class T>
msT<T>::msT(const vecT <T> &r)
{
	N	= r.N;mN	= r.mN;	
	//dlt	= true;
	x	= new T [mN];
	//for(int i=0;i<N;++i)x[i]=r.x[i];
	memcpy(x,r.x,N*sizeof(T));
}
//____________________________________
template <class T>
void msT<T>::pad(msT<T> &y)		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
{
	T *x_;
	if ((N+y.N)>mN)
	{		
		mN	+= y.N;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		dlt	= false;
		delete [] x;
		dlt	= true;
		x	= x_;
		//x_	= x+N;
		//for(int i =0;i<y.N;i++)x_[i]	= y.x[i];
		//memcpy(x_+N,y.x,y.N*sizeof(T));
	}
	x_	= x+N;
	for(int i =0;i<y.N;i++)x_[i]	= y.x[i];
	N	+= y.N;
}
//____________________________________
template <class T>
void msT<T>::pad(T &y)		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
{
	if ((N+1)>mN)
	{
		T *x_;
		mN	+= dN;
		x_	= new T [mN];
		memcpy(x_,x,N*sizeof(T));
		dlt	= false;
		delete [] x;
		dlt	= true;
		x	= x_;
	}
	x[N]	= y;
	N	++;
}/**/
//____________________________________
//____________________________class	msT____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________





//____________________________class	sparse____________________________________________________________________________
//________________________________Реализация методов________________________________________________________________
//____________________________________
template <class T>
sparse<T>::sparse(sparse<T> & cpspr)	// конструктор копий
{
	S.setmem(cpspr.S.mN);
	S.pst(cpspr.S);

	I.setmem(cpspr.I.mN);
	I.pst(cpspr.I);

	J.setmem(cpspr.J.mN);
	J.pst(cpspr.J);
	nx	= cpspr.nx;
	ny	= cpspr.ny;
}
//____________________________________
template <class T>
void sparse<T>::init(int n, int nz) // инициалилация матрицы n_x_n  c nz ненулевыми элементами.
{
	S.setmem(nz);
	I.setmem(nz);
	J.setmem(n+1);
	J.N	= n;
	for(int j=0;j<J.N;J.x[j++]=-1);// все строки пусты 
	nx	= ny = n;
}
//____________________________________
template <class T>
T sparse<T>::get(const int my,const int mx) // доступ к элементу A(my,mx);
{
	int i,j,i_;
	if ((my>=ny)||(mx>=nx)) return 0;
	i	= J.x[my];	// номер первого элемента строки 'my'
	if (i==-1) return 0;
	if (mx<I.x[i]) return 0;
	for(j=my+1;(j<J.N)&&(J.x[j]==-1);j++);// поиск следующей ненулевой строки
	if(j<J.N)	// если есть следующая строка строка
	{
		i_	= J.x[j];// номер первого элемента следующей строки
		if (mx>I.x[i_-1]) return 0;
	}else i_ = S.N;
	for(j=i;(j<i_);j++)
	{
		if (mx==I.x[j]) return S.x[j];
	}
	return 0;
}
//____________________________________
template <class T>
T & sparse<T>::set(const int my,const int mx) // доступ к элементу A(my,mx);
{
	int i,j,i_;
	const T nl = 0;
	if ((my>=ny)||(mx>=nx))
	{
		j	= my-J.N+1;
		J.addmem(j);
		J.N	= my+1;
		for(i=ny;i<J.N;i++) J.x[i]	= -1;
		nx	= mx+1;
		ny	= my+1;
	}
	i	= J.x[my];	// номер первого элемента строки 'my'
	if (i==-1)// пустая строка
	{
		for(j=my+1;(j<J.N)&&(J.x[j]==-1);j++);// найти ближайшую непустую строку
		if( j==J.N)	// не найдено ни одной заполненной строки
		{
			i_	= S.N; // номер элемента из S на которое нужно вставить новый элемент
			J.x[my]	= i_;
			I.add(mx);
			S.add(nl);
			return S.x[i_];
		}
		//j	- номер ближайшей ненулевой строки с больши номером
		i_	= J.x[j];  // номер элемента из S перед которым нужно вставить новый элемент
		J.x[my]	= i_;
		return addpos(my,mx,i_);
	}
	if (mx<I.x[i]) // I.x[i]-первый ненулевой столбец в строке my; требуемый номер столбца меньше стобца первого ненулевого элемента в строке.
	{
		J.x[my]	= i;	// замена данных о первом столбце
		return addpos(my,mx,i);
	}
	for(j=my+1;(j<J.N)&&(J.x[j]==-1);j++);// поиск следующей ненулевой строки
	if(j<J.N)	// если есть следующая строка строка
	{
		i_	= J.x[j];// номер первого элемента следующей строки
		if (mx>I.x[i_-1]) return addpos(my,mx,i_); // I.x[i_-1]  - последний ненулевой столбец в строке my;требуемый номер столбца больше стобца последнего ненулевого элемента в строке.
	}else i_ = S.N;
	for(j=i;(j<i_)&&(mx>I.x[j]);j++); // проход по элементам строки
	if (mx==I.x[j]) return S.x[j];	// найдено совпадение позиций - запрашиваемый элемент уже есть в матрице
	// j - позиция элемента в S на место которого нужно вставить новый элемент
	return addpos(my,mx,j);

	/*for(j=i;(j<i_)&&(mx<I.x[j]);j++);
	{
		if (mx==I.x[j]) return S.x[j];
	}/**/
	//return 0;
}
template <class T>
T & sparse<T>::fst(const int my,const int mx) // доступ к элементу A(my,mx)
{
	int i,j;
	i	= J.x[my];	// номер первого элемента строки 'my'
	for(j=i;(mx>I.x[j]);j++); // проход по элементам строки
	return S.x[j];
}
template <class T>
T & sparse<T>::addpos(const int my,const int mx,const int i)	// инициализация нового элеметна со строкой mx, и номеров i в массиве S (используется в set())
{
	const T nl = 0;
	I.add(mx,i);	// добавить столбец в массив столбцов на позицию i
	S.add(nl,i);	// добавить новый нулевой элемент на позицию i
	for(int j=my+1;j<J.N;++j){if(J.x[j]!=-1) ++J.x[j];}	// коррекция вектора с позициями первых ненулевых элементов
	return S.x[i];
}
//____________________________________
template <class T>
void sparse<T>::tns()	// транспонирование матрицы
{
	vecT<vecT <T> > clms(nx);	// массив стоблцов значений;
	vecT<vecT <int> > inds(nx);	// массив индексов строк;
	clms.N	= nx;
	int i,i1,j1,j2,k;
	// заполнение буферной матрицы значений clms и матрицы номеров строк inds
	for (i=0;i<J.N;i++)	// проход по строкам
	{//для каждой строки
		j1	= J.x[i];// номер первого элемента в тек строке
		if(j1!=-1) //выбор ненулевых строк
		{
			for(i1=i+1;(i1<J.N)&&(J.x[i1]==-1);i1++);// след. ненулевая строка
			j2	= (i1<J.N) ? J.x[i1] : I.N; // номер первого элемента в след. строке
			for(k=j1;k<j2;k++)// проход по ненулевым элементам тек. строки
			{
				clms.x[I.x[k]].add(S.x[k]); // добавить в столбец I.x[k] элемент S.x[k]
				inds.x[I.x[k]].add(i);	// добавить в данные о строке для столбца I.x[k]; (строки будут отсортированы)
			}
		}
	}
	memset(S.x,0,S.N*S.sz);
	memset(I.x,0,I.N*I.sz);
	for (i=0;i<J.N;i++)J.x[i]=-1;
	nx	= ny;
	ny	= clms.N;
	i1	= 0;
	for(i=0;i<clms.N;i++)// цикл по столбцам исходной матрицы
	{
		if(clms.x[i].N!=0)// выбор непустых столбцов
		{
			J.x[i]	= i1;	//запоминание номера первого элемента в текущей	 строке транспонированной матрицы
			for(k=0;k<clms.x[i].N;k++)//проход вдоль столбца исходной матрицы
			{
				I.x[i1]	= inds.x[i].x[k];	// номер столбца транспонированной матрицы (строки исходной)
				S.x[i1]	= clms.x[i].x[k];	// запоминание элемента;
				++i1;
			}
		}
	}
}
//____________________________________
template <class T>
vecT<T> & sparse<T>::pmv_f(vecT<T> &a, vecT<T> &b) // умножение разреженной матрицы на вектор 'a' результат в 'b'
{
	int i_,j_,j,i;
	T	x,y;
	for(i=0;i<J.N-1;i++)
	{
		i_	= J.x[i];
		j_	= J.x[i+1];
		x	= 0;		
		for(j=i_;j<j_;j++) x+=S.x[j]*a.x[I.x[j]];
		b.x[i]	= x;
	}
	i	= J.N-1;
	i_	= J.x[i];
	j_	= I.N;
	x	= 0;		
	for(j=i_;j<j_;j++) x+=S.x[j]*a.x[I.x[j]];
	b.x[i]	= x;
	return b;
}
//____________________________________
template <class T>
vecT<T> & sparse<T>::pmv(vecT<T> &a, vecT<T> &b) // умножение разреженной матрицы на вектор 'a' результат в 'b'
{
	int i_,j_,j,i1;
	T	x;
	for(int i=0;i<J.N;i++)
	{
		i_	= J.x[i];
		if(i_!=-1)
		{
			for(i1=i+1;(i1<J.N)&&(J.x[i1]==-1);i1++);// след. ненулевая строка
			j_	= (i1<J.N) ? J.x[i1] : I.N; // номер первого элемента в след. строке
			x	= 0;		
			for(j=i_;j<j_;j++) x+=S.x[j]*a.x[I.x[j]];
			b.x[i]	= x;
		}
	}
	return b;
}
//____________________________________

//____________________________class	sparse____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________



//____________________________class	SparseMatr____________________________________________________________________________
//________________________________Реализация методов________________________________________________________________
//____________________________________
template <class T>
SparseMatr<T>::SparseMatr(SparseMatr<T> & r)	// конструктор копий
{
	S.setlen(r.S.N);
	I.setlen(r.I.N);
	for(int i=0;i<S.N;i++) {S.x[i].pst(r.S.x[i]);}
	for(int i=0;i<I.N;i++) {I.x[i].pst(r.I.x[i]);}
	nx	= r.nx;
	ny	= r.ny;
}
//____________________________________
template <class T>
void SparseMatr<T>::setCopy(SparseMatr<T> & r)
{
	S.setlen(r.S.N);
	I.setlen(r.I.N);
	for(int i=0;i<S.N;i++) {S.x[i].pst(r.S.x[i]);}
	for(int i=0;i<I.N;i++) {I.x[i].pst(r.I.x[i]);}
	nx	= r.nx;
	ny	= r.ny;
}
template <class T> 
template <class W>
void SparseMatr<T>::setCopyW(SparseMatr<W> & r)
{
	S.setlen(r.S.N);
	I.setlen(r.I.N);
	for(int i=0;i<I.N;i++) {I.x[i].pst(r.I.x[i]);}
	for(int i=0;i<S.N;i++)
	{
		S.x[i].setlen(r.S.x[i].N);
		for(int j =0;j<S.x[i].N;j++)
		{
			S.x[i].x[j] = r.S.x[i].x[j];
		}
	}
	nx	= r.nx;
	ny	= r.ny;
}
//____________________________________
template <class T>
void SparseMatr<T>::setCopy(FullMatrix<T> & r)
{
	setSize(r.ny,r,nx);
	for(int i = 0;i<ny;i++)
	{
		for(int j=0;j<nx;j++)
		{
			if(r.x.x[i][j]!=0)
			{
				set(i,j)=r.x.x[i][j];
			}
		}
	}

}
//____________________________________
template <class T>
void SparseMatr<T>::swp(SparseMatr<T> & r)
{
	S.swp(r.S);
	I.swp(r.I);
	int ii;
	ii		= nx;
	nx		= r.nx;
	r.nx	= ii;
	ii		=  ny;
	ny		= r.ny;
	r.ny	= ii;
}
//____________________________________
template<class T>
void SparseMatr<T>::setSignature(vecT<vecint>& id)
{
	ny = id.N;
	S.setlen(ny);
	I.setlen(ny);
	int kk = 0;
	int jj;
	for (int ii = 0;; ii < ny; ii++)
	{
		jj = id.x[ii].last();
		kk = kk > jj ? kk : jj;
		I.x[ii].pst(id.x[ii]);
		S.x[ii].setlen(id.x[ii].N);
	}
	nx = kk;
}
//____________________________________
template <class T>
T SparseMatr<T>::get(const int my,const int mx) // доступ к элементу A(my,mx);
{
	int i;
	if(I.x[my].N==0)return 0;
	i	= I.x[my].fnd(mx);
	if(i!=-1) return S.x[my].x[i];
	return 0;
}
//____________________________________
template <class T>
T & SparseMatr<T>::fst(const int my,const int mx) // быстрый доступ к элементу A(my,mx) при обращении к заведомо существующему элементу
{
	return S.x[my].x[I.x[my].fnd(mx)];
}
//____________________________________
template <class T>
void SparseMatr<T>::setSize(const int my,const int mx)	// транспонирование матрицы
{
	ny	= my;
	nx	= mx;
	S.setlen(my);
	I.setlen(my);
}
//____________________________________
template <class T>
void SparseMatr<T>::reSize(const int my,const int mx)	// установка новых размеров матрицы с сохранением данных.
{
	if ((my<I.mN)&&(my<S.mN))
	{
		I.N	= my;
		S.N	= my;
		nx	= mx;
		ny	= my;
		int ii,jj;
		for(ii=0;ii<I.N;ii++)
		{
			jj	= I.x[ii].fmre(my);
			if(jj!= -1)
			{
				S.x[ii].N	= I.x[ii].N	= jj;
			}
		}
	}else
	{
		SparseMatr<T> A;
		A.setSize(my,mx);
		A.S.swp(S);
		A.I.swp(I);
		int ii;
		for(ii=0;ii<ny;ii++)
		{
			S.x[ii].swp(A.S.x[ii]);
			I.x[ii].swp(A.I.x[ii]);
		}
		nx	= mx;
		ny	= my;
	}
}
//____________________________________
template <class T>
T & SparseMatr<T>::set(const int my,const int mx) // доступ к элементу A(my,mx);
{
	int i;
	const T nl = 0;
	nx	= mx>=nx ? mx+1 :nx;
	if (my>=ny)
	{
		vecT<vecT<T> > S1;
		vecT<vecT<int> > I1;
		ny	= my+1;
		S1.setmem(ny);
		I1.setmem(ny);
		I1.N	= S1.N = ny;
		for(i=0;i<S.N;i++)
		{
			S1.x[i].pst(S.x[i]);
			I1.x[i].pst(I.x[i]);
		}
		S.swp(S1);
		I.swp(I1);
		S.x[my].add(nl);
		I.x[my].add(mx);
		return S.x[my].x[0];
	}
	if(I.x[my].N==0)
	{
		S.x[my].add(nl);
		I.x[my].add(mx);
		return S.x[my].x[0];
	}
	i	= I.x[my].fnd(mx);
	if(i!=-1)return S.x[my].x[i];
	int j	= 0;
	for(;I.x[my].x[j]<mx&&j<I.x[my].N;++j);
	if(j==I.x[my].N)
	{
		S.x[my].add(nl);
		I.x[my].add(mx);
	}
	else
	{
		S.x[my].add(nl,j);
		I.x[my].add(mx,j);
	}
	return S.x[my].x[j];
}//____________________________________
template <class T>
void SparseMatr<T>::del(const int my,const int mx) // удалить (присвоить занчение 0) элемент A(my,mx)
{
	if (get(my,mx)!=0)
	{
		int ix;
		ix	= I.x[my].fnd(mx);
		S.x[my].rem(1,ix);
		I.x[my].rem(1,ix);
	}
}
//____________________________________
template <class T>
void SparseMatr<T>::delsym(const int my) // удалить строку и столбец my с перемещением последней строки на место 'my'
{
	int ii,jj,kk,ia,mm;
	ii	= ny-1;

	/*if(I.x[my].N!=0)
	{
		for(jj=0;jj<I.x[my].N;jj++)
		{
			kk	= I.x[my].x[jj];// номер столбца в строке my
			ia	= I.x[kk].fnd(my); // найти положение столбца my в строке kk
			I.x[kk].rem(1,ia); // удалить из строки kk элемент в столбце my
			S.x[kk].rem(1,ia);
			//I.x[kk].x[ia]	= -2;
		}
	}*/

	T xx;
	for(jj=0;jj<I.x[ii].N;jj++)
	{
		kk	= I.x[ii].x[jj];	// тек. номер столбца в последней строке
		ia	= I.x[kk].fnd(ii);	// найти в строке 'kk' указатели на элемент в последней строке
		for(mm=0;(mm<I.x[kk].N)&&(I.x[kk].x[mm]<my);mm++);
		if(I.x[kk].x[mm]==my)
		{
			S.x[kk].x[mm]	= S.x[kk].x[ia];
		}else
		{// в строке нет элемента с номером столбца  my
			I.x[kk].rem(1,ia);
			I.x[kk].add(my,mm);
			xx	= S.x[kk].x[ia];
			S.x[kk].rem(1,ia);
			S.x[kk].add(xx,mm);
			//I.x[kk].x[ia]	= my;	// заменить указание на столбец my
		}
	}

	//I.x[my].pst(I.x[ii]);
	//S.x[my].pst(S.x[ii]);
	I.x[my].swp(I.x[ii]);
	S.x[my].swp(S.x[ii]);
	I.x[ii].N	= 0;
	S.x[ii].N	= 0;
	I.N--;
	S.N--;
	ny--;
	nx--;
}
//____________________________________
template <class T>
void SparseMatr<T>::symswp(const int my)// поменять местами строку и столбец my с последней строкой и столбцом (алгоритм для симмертичной мартицы)
{
	if(my!=nx)
	{
		int ii,jj,kk,mm,ia;
		ii	= nx-1;

		// смена номеров строк
		S.x[my].swp(S.x[ii]);
		I.x[my].swp(I.x[ii]);

		T xx;

		// замена последнего столбца на столбец my
		for(jj=0;jj<I.N;jj++)
		{
			mm	= I.x[jj].fnd(ii);	// положение последнего столбца в тек. строке
			kk	= I.x[jj].fnd(my);	// положение столбца my в тек. строке
			if((kk!=-1)&&(mm!=-1))
			{
				xx	= S.x[jj].x[kk];
				S.x[jj].x[kk]	= S.x[jj].x[mm];
				S.x[jj].x[mm]	= xx;
			}else
			{
				if((kk==-1)&&(mm!=-1)) // столбца my  нет
				{
					for(ia=0;(ia<I.x[jj].N)&&(I.x[jj].x[ia]<my);ia++);
					if(ia<mm)
					{
						I.x[jj].rem(1,mm);
						I.x[jj].add(my,ia);
						xx	= S.x[jj].x[mm];
						S.x[jj].rem(1,mm);
						S.x[jj].add(xx,ia);
					}else
					{
						I.x[jj].x[mm]	= my;
					}
				}
				else // последнего столбца нет
				{
					if ((kk!=-1)&&(mm==-1))
					{
						I.x[jj].rem(1,kk);
						I.x[jj].add(ii);
						xx	= S.x[jj].x[kk];
						S.x[jj].rem(1,kk);
						S.x[jj].add(xx);
					}
				}
			}
		}
	}
}
//____________________________________
template <class T>
void SparseMatr<T>::ColumnSwap(const int &id1,const int &id2) // поменять местами 2 столбца
{
	if((id1>=0)&&(id2>=0)&&(id1<nx)&&(id2<nx))
	{
		int ii,jj,kk,mm;
		T xx;
		for(jj=0;jj<I.N;jj++)
		{
			mm	= I.x[jj].fnd(id1);	// положение столбца id1 в тек. строке
			kk	= I.x[jj].fnd(id2);	// положение столбца id2 в тек. строке
			if((kk!=-1)&&(mm!=-1))
			{
				xx	= S.x[jj].x[kk];
				S.x[jj].x[kk]	= S.x[jj].x[mm];
				S.x[jj].x[mm]	= xx;
			}else
			{
				if((kk!=-1)&&(mm==-1))
				{
					I.x[jj].rem(1,kk);// удалить указание на столбец id2
					xx	= S.x[jj].x[kk];
					S.x[jj].rem(1,kk);
					for(ii=0;((ii<I.x[jj].N)&&(I.x[jj].x[ii]<id1));ii++); // найти первый индекс превышающий id1
					I.x[jj].add(id1,ii);
					S.x[jj].add(xx,ii);
				}
				else
				{
					if((kk==-1)&&(mm!=-1))
					{
						I.x[jj].rem(1,mm);// удалить указание на столбец id1
						xx	= S.x[jj].x[mm];
						S.x[jj].rem(1,mm);
						for(ii=0;((ii<I.x[jj].N)&&(I.x[jj].x[ii]<id2));ii++); // найти первый индекс превышающий id2
						I.x[jj].add(id2,ii);
						S.x[jj].add(xx,ii);
					}
				}
			}
		}
	}
}
//____________________________________
template <class T>
void SparseMatr<T>::tns()	// транспонирование матрицы
{
	vecT<vecT <T> > S1(nx);	// массив стоблцов значений;
	vecT<vecT <int> > I1(nx);	// массив индексов строк;
	I1.N	= S1.N	= nx;
	int i,j;
	for(i=0;i<S.N;i++)// перебор строк
	{
		for(j=0;j<S.x[i].N;j++) // вдоль строки
		{
			S1.x[I.x[i].x[j]].add(S.x[i].x[j]);
			I1.x[I.x[i].x[j]].add(i);
		}
	}
	S.swp(S1);
	I.swp(I1);
	nx	= ny;
	ny	= S.N;
}
//____________________________________
template <class T>
void SparseMatr<T>::GetNormMatrix(SparseMatr<T> & R) // возвращает в R=A*A`,A- тек. матрица, A`- транспонированная A
{
	R.setSize(ny,ny);
	int i,j,k,p,q;
	vecT<vec2int> id;
	id.setmem(nx);	// для хранения индексов пересечения
	T z;
	for(i=0;i<ny;i++)
	{
		z	= 0;
		for(j=0;j<I.x[i].N;j++)
		{
			z	+= S.x[i].x[j]*S.x[i].x[j];
		}
		R.set(i,i)	= z;
	}
	for(i=0;i<ny;i++)
	{
		for(j=i+1;j<ny;j++)
		{
			I.x[i].itssi(I.x[j],id);
			if(id.N!=0)
			{
				z	= 0;
				for(k=0;k<id.N;k++)
				{
					p	= id.x[k].x[0];
					q	= id.x[k].x[1];
					z	+= S.x[i].x[p]*S.x[j].x[q];
				}
				if (z!=0) R.set(j,i)	= R.set(i,j)	= z;
			}
		}
	}
}
//____________________________________
template <class T>
void SparseMatr<T>::Householder(vecT<T> & u, int &is, const int ic)
{//ic - номер строки по которой строиться вектор хаусхолдера 'u'
	T a;
	int i;
	for(i = 0;(i<I.x[ic].N)&&(ic>I.x[ic].x[i]);i++); //определить первый элемент справа от главной диагонали, либо диагональ
	if(i<I.x[ic].N) //если найден таковой ненулевой элемент
	{
		is	= i;
		u.N	= I.x[ic].N-i;
		if (I.x[ic].x[i]==ic)
		{
			memcpy(u.x,(S.x[ic].x+i),u.N*sizeof(T));
			a	= u.ssqr();
			a	= sqrt(a);
			u.x[0]	+= u.x[0]<0 ? -a : a;
		}else
		{
			u.N++;
			u.x[0]	= 0;
			memcpy(u.x+1,(S.x[ic].x+i),u.N*sizeof(T));
			a	= u.ssqr();
			a	= sqrt(a);
			u.x[0]	= a;
		}
	}else
	{
		u.N	=	0;
	}
}
//________________________________________
template <class T>
void SparseMatr<T>::qrIrtUpd(SparseMatr<T> &Q, vecT<T> &u,int &is, const int ic) // 
{
	T *xc,u0,z;
	if(u.N!=0)
	{
		u0	= -0.5*u.ssqr();
		Q.S.x[ic].pst(u);// запомнить вектор хаусхолдера
		if (is==ic)
		{
			Q.I.x[ic].add(I.x[ic].x+is,u.N);
		}else
		{
			Q.I.x[ic].add(ic);
			Q.I.x[ic].add(I.x[ic].x+is,(u.N-1));
		}
		//static vecT<vec2int> id(nx);
		vecT<vec2int> id(nx);
		vecT<int> id1(nx);
		vecT<int> id2(nx);
		if(ic==0) if(id.mN<nx) id.setmem(nx);
		// A -= A*u*u`
		//xc	 = S.x[ic].x[is];
		//if (I.x[ic].x[is]==ic) {S.x[ic].x[is]-= u.x[0];}// если был найден ненулевой диагональный элемент
		//I.x[ic].x[0]= ic;
		for(int i =ic+1;i<ny;i++) // проход по всем строкам вниз матрицы
		{
			xc	= S.x[i].x; // запомнить указатель на текущую строку
			Q.I.x[ic].itssi(I.x[i],id); // выделение в id номеров элементов с совпадающими индексами ненулевых элементов тек. строки и вектора 'u'
			if(id.N!=0)
			{
				z	= 0;
				for(int j =0;j<id.N;j++)
				{
					z	+= xc[id.x[j].x[1]]*u.x[id.x[j].x[0]];// свётрка текущей строки и вектора хаусхолдера
				}
				z	/= u0;

				for(int j =0;j<id.N;j++) // проход по текущей строке
				{
					xc[id.x[j].x[1]]	+= z*u.x[id.x[j].x[0]]; // умножение на вектор хаусхолдера
				}
				if (id.N<Q.I.x[ic].N)
				{
					int k,m;
					Q.I.x[ic].unis(I.x[i],id1);
					m	= k	= 0;
					for(int j =0;j<id1.N;j++) 
					{
						if(I.x[i].x[k]!=id1.x[j])
						{
							S.x[i].add(k,0);						
							S.x[i].x[k]	= z*u.x[m];
							m++;
						}else
						{
							k++;
						}
					}
					I.x[i].pst(id1);
				}
			}
		}
		if (I.x[ic].x[is]>ic)
		{
			I.x[ic].x[is]	= ic;
			S.x[ic].x[is]	= -u.x[0];			
		}else
		{
			S.x[ic].x[is]	-= u.x[0];			
		}
		S.x[ic].N	= is+1;
		I.x[ic].N	= is+1;
	}
}
//________________________________________
template <class T>
void SparseMatr<T>::QR(SparseMatr<T> &Q) // QR - разложение
{
	vecT<T> u(nx);
	int k,is;
	k = ny>(nx-1) ? nx-1 : ny;
	Q.setSize(k,nx);
	for(int i=0;i<k;i++)
	{
		//cout<<endl;
		//showfull(*this);
		showfull_infile(*this,"QR.txt");
		//cout<<endl;
		Householder(u,is,i);
		qrIrtUpd(Q,u,is,i); // в Q - транспонированная матрица Q по отношению к QR разложению
		
	}
	showfull_infile(*this,"R.txt");
	showfull_infile(Q,"Q.txt");
}
//____________________________________
template <class T>
void SparseMatr<T>::QR_MatrPrepating(SparseMatr<T> &R) // копирование текущей матрицы в R, R-имеет сигнатуру разрежённости конечной верхнетреугольной матрицы. 
{
	int i,j,k;
	vecT<vec2int> id(nx);
	vecT<int> hv(nx);
	vecT<int> hs(nx);

	R.setSize(nx,ny);

	for(i=0;i<ny;i++)
	{
		for(j = 0;(j<R.I.x[i].N)&&(i>R.I.x[i].x[j]);j++); //определить первый элемент справа от главной диагонали, либо диагональ
		k	= R.I.x[i].N-j;
		if (k>0)
		{
			hv.pst(R.I.x[i].x+j,k);
			hv.itssi(R.I.x[i],id);
			if(id.N>0)
			{
				if(id.N!=hv.N)
				{
					R.I.x[i].unis(hv,hs);
				}else
				{

				}
			}
		}

	}
}
//____________________________________
template <class T>
void SparseMatr<T>::QR_solver(vecT<T> &b,vecT<T> &z) // решение СЛАУ с текущей матрицей с помощью QR-разложения
{
	T a,nrb;
	SparseMatr<T> A;
	int i,j;
	nrb	= sqrt(b.ssqr());
	b	/= nrb;
	A.setCopy(*this);
	if(nx>ny)
	{
		SparseMatr<T> Q;
		vecT<T> y;
		QR(Q);	// QR применяется к транспонированной матрице
	}
	/*	y.setlen(ny);
		for(i = 0;i<ny;i++)
		{
			a	= 0;
			for(j = 0;j<I.x[i].N;j++)
			{
				a	+= y.x[I.x[i].x[j]]*S.x[i].x[j];
			}
			y.x[i]	= (b.x[i]-a)/S.x[i].x[0];
		}
		z.setlen(nx);
		memcpy(z.x,y.x,y.N*sizeof(T));
		T *xc;
		for(i=Q.N-1;i>=0;i--)
		{
			a	= 0;
			xc	= z.x+i;
			for(j = 0;j<Q.x[i].N;j++)
			{
				a	+= xc[j]*Q.x[i].x[j];
			}
			a	/= -0.5*Q.x[i].ssqr();
			for(j=0;j<Q.x[i].N;j++) xc[j] += Q.x[i].x[j]*a;
		}
	}/*else
	{
		QR(b);
		z.setlen(nx);
		for(i = ny-1;i>=0;i--)
		{
			a	= 0;
			for(j = i+1;j<ny;j++)
			{
				a	+= z.x[j]*x.x[i][j];
			}
			z.x[i]	= (b.x[i]-a)/x.x[i][i];
		}
	}*/

	z	*= nrb;
}
//____________________________________
template <class T>
void SparseMatr<T>::OrthoBin(int &jj,int &ii,int &n,vecT<T> &u, vecT<T> &y, double &a)	// основная функция бинарной ортогонализации
{
	//  jj - номер первого столбца в матрице хранения результ. вектора текущего уровня
	//  ii - номер строки в матрице хранения результ.вектора текущего уровня
	//  n  - размерность вектора текущего уровня
	//  *ptr - указатель на первый элемент текущего уровня из всего вектора u (ptr = u.x + jj)  ??? (обошлось без указателя)
	//  y_out - вектор переходящий на уровень выше
	//  a_out - длина переходящая на уровень выше
	if(n==2)
	{
		vecT<T> x;
		x.setlen(2);
		x.x[0]	= u.x[jj+1];
		x.x[1]	= -u.x[jj];
		a		= sqrt((double) x.ssqr());
		x/= (T) a;
		y.setlen(2);
		y.x[0]	= -x.x[1]; // u.x[jj]/a_out
		y.x[1]	= x.x[0];  // u.x[jj+1]/a_out

		// запись вектора x в матрицу (позднее можно будет сам х убрать и писать сразу в строку S.x[ii])
		I.x[ii].setlen(2);
		I.x[ii].x[0]	= jj;
		I.x[ii].x[1]	= jj+1;
		S.x[ii].pst(x);
	}else
	{
		int n1, j1,j2,i1,i2;
		vecT<T> y1,y2;
		double a1,a2;

		n1	= n>>1;

		j1	= jj;
		j2	= jj+n1;
		i1	= ii-n1;
		i2	= ii-1;
		OrthoBin(j1,i1,n1,u,y1,a1);
		OrthoBin(j2,i2,n1,u,y2,a2);

		vecT<T> x;
		x.setlen(y1.N+y2.N);
		y.setlen(x.N);
		a	= sqrt(a1*a1+a2*a2);

		for(int in =0;in<y1.N;in++)
		{
			x.x[in]	= a2*y1.x[in];
			y.x[in]	= a1*y1.x[in];
		}
		for(int in =0;in<y2.N;in++)
		{
			x.x[y1.N+in]	= -a1*y2.x[in];
			y.x[y1.N+in]	= a2*y2.x[in];
		}
		x	/= (T) a;
		y	/= (T) a;

		// запись вектора x в матрицу (позднее можно будет сам х убрать и писать сразу в строку S.x[ii])
		I.x[ii].setlen(x.N);
		for(int in=0;in<x.N;in++){I.x[ii].x[in] = jj+in;}
		S.x[ii].pst(x);
	}
}
//____________________________________
template <class T>
void SparseMatr<T>::SetOrthoBasis(vecT<T> &u) // установить в текущую матрицу строки-вектора ортогонального базиса ортогонального заданному вектору u.
{
	/*
	В текущей матрице генерируются вектор-строки ортогнормированного базиса ортогонального заданному вектору. 
	Разметрность базиса - n-1, где n-размерность вектора n; [n/2] векторов имеют лишь 2 ненулевых компоненты, [n/4] - 4 ненулевых компоненты и т.д.
	во входном векторе u предполагается отсутсвие нулевых элементов
	*/

	//T * ptr;	// указатель - для доспута к элементам вектора u

	setSize(u.N-1,u.N);

	vecT<int> ck,in;	// массив 2-ного представления размерности вектора u

	ck.setbindec(u.N);	// представление размернонсти в виде суммы чисел 2^k 
	in.setmem(ck.N);
	int ii,jj,ij,n;

	for(ii=0;ii<ck.N;ii++){if(ck.x[ii]!=0){in.add(ii);}} // выделеине ненулевых элементов из ck

	vecT< vecT<T> > y;
	vecT<double> a;
//	double a1;
//	vecT<T> y1;
	y.setlen(in.N);
	a.setlen(y.N);
	jj	= 0;
	ii	= -1;
	ij	= 0;
	if(ck.x[in[0]])  //ij	= ck.x[in[0]]== 1 ? 1 : 0; // если исходная размерноть нечётная, то начать цикл с минимальной размерности 2 или более
	{
		ij	= 1; // переход к следующему блоку размерности
		jj	= 1; // сместить на единицу начало вектора u
		// записать вектор y1 размерности 1
		y.x[0].add(1);
		a.x[0]=u.x[0]; // запомнить первую компоненту вектора u
	}
	for(;ij<in.N;ij++) // проход по ненулевым - основной цикл заполнения матрицы
	{
		//  jj - номер первого столбца в матрице хранения результ. вектора текущего уровня
		//  ii - номер строки в матрице хранения результ.вектора текущего уровня
		//  n  - размерность вектора текущего уровня
		//  *ptr - указатель на первый элемент текущего уровня из всего вектора u (ptr = u.x + jj)  ???
		//  y_out - вектор переходящий на уровень выше
		//  a_out - длина переходящая на уровень выше
		n	= ck.x[in.x[ij]];
		ii	+= n-1;
		OrthoBin(jj,ii,n,u,y.x[ij],a.x[ij]);	// основная функция бинарной ортогонализации
		jj	+= n;
	}

	vecT<T> xc,yc;
	double ac;
	n	= y.x[0].N;
	ac	= a.x[0];
	yc.pst(y.x[0]);
	for(ij=1;ij<in.N;ij++) // цикл остаточного заполнения матрицы
	{
		n	+= y.x[ij].N;
		xc.setlen(n);
		
		for(int i =0;i<yc.N;i++)	// x = a2*y1-a1*y2
		{
			xc.x[i]	= a.x[ij]*yc.x[i];
		}
		for(int i =0;i<y.x[ij].N;i++)  // x = a2*y1
		{
			xc.x[yc.N+i]	= -ac*y.x[ij].x[i];
		}

		yc	*= ac;	// a1*y1
		y.x[ij] *= a.x[ij]; // a2*y2
		yc.add(y.x[ij]);	// a1*y1+a2*y2

		ac	*= ac;
		ac	+= a.x[ij]*a.x[ij];
		ac	=  sqrt(ac); // ac = sqrt(a1*a1+a2*a2);

		// Нормировка
		xc	/= (T) ac;
		yc	/= (T) ac;

		// запись вектора x в матрицу (позднее можно будет сам х убрать и писать сразу в строку S.x[ii])
		ii++;
		I.x[ii].setlen(xc.N);
		for(int i=0;i<xc.N;i++){I.x[ii].x[i] = i;}
		S.x[ii].pst(xc);
	}

}
//____________________________________
template <class T>
vecT<T> & SparseMatr<T>::pmv(const vecT<T> &a, vecT<T> &b) // умножение разреженной матрицы на вектор 'a' результат в 'b'
{
	T x;
	b.N	= ny;
	memset(b.x,0,b.N*sizeof(T));
	for(int i=0;i<S.N;i++)
	{
		x	= 0;
		for(int j=0;j<S.x[i].N;j++)
		{
			x+=S.x[i].x[j]*a.x[I.x[i].x[j]];
		}
		b.x[i]	= x;
	}
	return b;
}//____________________________________
template <class T>
vecT<T> SparseMatr<T>::getdiag()	// возвращает диагональ матрицы
{
	vecT<T> A;
	int i,j,nd;
	nd	= nx>ny ? ny : nx;
	A.setlen(nd);
	for(i=0;i<nd;i++)
	{
		j	= I.x[i].fnd(i);
		A.x[i]	= (j!=-1) ? S.x[i].x[j] : 0;
	}
	return A;
}
//____________________________________
template <class T>
vecT<T>  SparseMatr<T>::CG_solve(vecT<T> &b)	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица
{
	vecT<T> xk;
	if (nx!=ny) return xk;
	vecT<T> z,pk,yk,rk;
	T mk,nk,hk,res;
	const T rmin = 1e-14;
	int k;
	z.setlen(ny);
	pk.setlen(nx);
	yk.setlen(nx);
	rk.setlen(ny);
	xk.setlen(nx);
	memcpy(rk.x,b.x,nx*sizeof(T));
	memcpy(pk.x,b.x,nx*sizeof(T));
	k	= 0;
	do
	{
		k++;
		pmv(pk,z);
		hk	= rk.ssqr();
		nk	= hk/(pk.scpr(z));
		memcpy(yk.x,pk.x,nx*sizeof(T));
		yk	*= nk;
		xk	+= yk;
		memcpy(yk.x,z.x,nx*sizeof(T));
		yk	*= nk;
		rk	-= yk;		
		mk	= rk.ssqr()/hk;
		pk	*= mk;
		pk	+= rk;
		res	= rk.snrm();
	}while(res>rmin);
	return xk;
}
//____________________________________
template <class T>
vecT<T>  SparseMatr<T>::CGNORM_solve(vecT<T> &b)	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица
{
	SparseMatr<T> At(*this);
	vecT<T> z,pk,yk,rk,xk,bk,xh;
	T mk,nk,hk,res;
	const T rmin = 1e-16;
	//int k;
	bk.setlen(nx);
	z.setlen(nx);
	pk.setlen(nx);
	yk.setlen(nx);
	rk.setlen(nx);
	xk.setlen(nx);
	xh.setlen(ny);


	At.tns();
	At.pmv(b,bk);

	memcpy(rk.x,bk.x,bk.N*sizeof(T));
	memcpy(pk.x,bk.x,bk.N*sizeof(T));
	int k	= 0;
	do
	{
		k++;
		pmv(pk,xh);
		At.pmv(xh,z);
		hk	= rk.ssqr();
		nk	= hk/(pk.scpr(z));
		memcpy(yk.x,pk.x,yk.N*sizeof(T));
		yk	*= nk;
		xk	+= yk;
		memcpy(yk.x,z.x,yk.N*sizeof(T));
		yk	*= nk;
		rk	-= yk;		
		mk	= rk.ssqr()/hk;
		pk	*= mk;
		pk	+= rk;
		res	= rk.snrm();
	}while(res>rmin);
	return xk;
}
//____________________________________
template <class T>
vecT<T>  SparseMatr<T>::CGNORM2_solve(vecT<T> &b,T rmin)	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица
{
	SparseMatr<T> At(*this);
	vecT<T> z,pk,yk,rk,xk,bk,xh;
	T mk,nk,hk,res;
	//const T rmin = 1e-16;
	//int k;
	bk.setlen(ny);
	z.setlen(ny);
	pk.setlen(ny);
	yk.setlen(ny);
	rk.setlen(ny);
	xk.setlen(ny);
	xh.setlen(nx);

	At.tns();
	//At.pmv(b,bk);

	memcpy(rk.x,b.x,b.N*sizeof(T));
	memcpy(pk.x,b.x,b.N*sizeof(T));
	int k	= 0;
	do
	{
		k++;
		At.pmv(pk,xh);
		pmv(xh,z);
		hk	= rk.ssqr();
		nk	= hk/(pk.scpr(z));
		memcpy(yk.x,pk.x,yk.N*sizeof(T));
		yk	*= nk;
		xk	+= yk;
		memcpy(yk.x,z.x,yk.N*sizeof(T));
		yk	*= nk;
		rk	-= yk;		
		mk	= rk.ssqr()/hk;
		pk	*= mk;
		pk	+= rk;
		res	= rk.snrm();
	}while(res>rmin);
	At.pmv(xk,xh);
	return xh;
}
//____________________________________
template <class T>
vecT<T>  SparseMatr<T>::CGMNORM2_solve(vecT<T> &b,T rmin = 1e-16)	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты к нормализованным уравнения)
{
	SparseMatr<T> B;
	vecT<T> z,pk,yk,rk,xk,bk,xh;
	T mk,nk,hk,res;
	//const T rmin = 1e-16;
	//int k;
	bk.setlen(ny);
	z.setlen(ny);
	pk.setlen(ny);
	yk.setlen(ny);
	rk.setlen(ny);
	xk.setlen(ny);
	xh.setlen(nx);

	GetNormMatrix(B);
	//At.pmv(b,bk);

	memcpy(rk.x,b.x,b.N*sizeof(T));
	memcpy(pk.x,b.x,b.N*sizeof(T));
	int k	= 0;
	do
	{
		k++;
		B.pmv(pk,z);
		//At.pmv(pk,xh);
		//pmv(xh,z);
		hk	= rk.ssqr();
		nk	= hk/(pk.scpr(z));
		memcpy(yk.x,pk.x,yk.N*sizeof(T));
		yk	*= nk;
		xk	+= yk;
		memcpy(yk.x,z.x,yk.N*sizeof(T));
		yk	*= nk;
		rk	-= yk;		
		mk	= rk.ssqr()/hk;
		pk	*= mk;
		pk	+= rk;
		res	= rk.snrm();
	}while(res>rmin);
	//At.pmv(xk,xh);
	B.setCopy(*this);
	B.tns();
	B.pmv(xk,xh);
	return xh;
}
//____________________________________
template <class T>
vecT<T>  SparseMatr<T>::StCGNORM2_solve(vecT<T> &b,T rmin)	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица
{
	SparseMatr<T> At(*this);
	static vecT<T> z,pk,yk,rk,xk,bk,xh;
	T mk,nk,hk,res;
	static int fst =0;
	
	if(fst==0)
	{
		bk.setlen(ny);
		z.setlen(ny);
		pk.setlen(ny);
		yk.setlen(ny);
		rk.setlen(ny);
		xk.setlen(ny);		
		xh.setlen(nx);
		fst	=1;
	}

	At.tns();
	//At.pmv(b,bk);
	xk	= 0;

	memcpy(rk.x,b.x,b.N*sizeof(T));
	memcpy(pk.x,b.x,b.N*sizeof(T));
	int k	= 0;
	do
	{
		k++;
		At.pmv(pk,xh);
		pmv(xh,z);
		hk	= rk.ssqr();
		nk	= hk/(pk.scpr(z));
		memcpy(yk.x,pk.x,yk.N*sizeof(T));
		yk	*= nk;
		xk	+= yk;
		memcpy(yk.x,z.x,yk.N*sizeof(T));
		yk	*= nk;
		rk	-= yk;		
		mk	= rk.ssqr()/hk;
		pk	*= mk;
		pk	+= rk;
		res	= rk.snrm();
	}while(res>rmin);
	At.pmv(xk,xh);
	return xh;
}
//____________________________________
template <class T>
void SparseMatr<T>::UniMatr(SparseMatr<T> &r)
{
	S.pad(r.S);
	I.pad(r.I);
	for (int ii	= ny;ii<S.N;ii++){I.x[ii]+=nx;}
	nx	+= r.nx;
	ny	= S.N;
}
//____________________________________
template <class T>
SparseMatr<T>	SparseMatr<T>::operator * (SparseMatr<T> &a)
{
	SparseMatr<T> R;
	SparseMatr<T> Tr(a);
	int i,j,k,p,q;
	vecT<vec2int> id;
	T z;
	id.setmem(nx);	// для хранения индексов пересечения
	Tr.tns();
	R.setSize(ny,Tr.ny);
	for(i=0;i<ny;i++)
	{
		for(j=0;j<Tr.ny;j++)
		{
			I.x[i].itssi(Tr.I.x[j],id);
			if(id.N!=0)
			{
				z	= 0;
				for(k=0;k<id.N;k++)
				{
					p	= id.x[k].x[0];
					q	= id.x[k].x[1];
					z	+= S.x[i].x[p]*Tr.S.x[j].x[q];
				}
				if (z!=0) R.set(i,j)	= z;
			}
		}
	}
	return R;
}
//____________________________________
template <class T>
vecT<T> & SparseMatr<T>::getrow(int ir,vecT<T> &u)
{
	u.setlen(nx);
	for(ii=0;ii<I.x[ir].N;ii++){u.x[I.x[ir].x[ii]]=S.x[ir].x[ii];}
	return u;
}
//____________________________________
template <class W>
void showfull ( SparseMatr<W> &a)
{
	cout.precision(4);
	cout<<scientific;
	for(int i=0;i<a.ny;i++)
	{
		for(int j = 0;j<a.nx;j++)
		{
			cout<<a.get(i,j)<<"	";
		}
		cout<<endl;
	}
}
//____________________________________
template <class W>
void showfull_infile ( SparseMatr<W> &a,const char *fname)
{
	fstream sss;
	sss.open(fname,ios::out);
	sss.precision(17);
	//cout.precision(4);
	//sss<<scientific;
	for(int i=0;i<a.ny;i++)
	{
		for(int j = 0;j<a.nx;j++)
		{
			sss<<a.get(i,j)<<"	";
		}
		sss<<endl;
	}
	sss.close();
}
//____________________________________
template <class T>
void  SparseMatr<T>::interp_dstrb(vecT<T> & X, vecT<T> & Z)
{
	// массивы X и Y должны быть отсортированны по возрастанию
	setSize(Z.N, X.N);

	if ((X.x[0] < Z.last())&(X.last() > Z.x[0])) // пересечение множеств X и Z не нулевое
	{
		int inz, inx1, inx2;
		double dxx, dxz;
		inz = 0;
		inx1 = X.fmr(Z.x[inz]);

		if(inx1>0)
		{
			dxx = X.x[inx1] - X.x[inx1 - 1];
			dxz = Z.x[inz]  - X.x[inx1 - 1];
			set(inz, inx1 - 1) = (1 - dxz / dxx);
			dxz = X.x[inx1] - Z.x[inz];
			set(inz, inx1) = (1 - dxz / dxx);// здесь нужно применить более быстрый метод
		}
		for (; inz < Z.N; inz++)
		{
			inx2 = X.fmr(Z.x[inz], inx1);
			if (inx2 > 0)
			{
				dxx = X.x[inx2] - X.x[inx2 - 1];
				dxz = Z.x[inz] - X.x[inx2 - 1];
				set(inz, inx2 - 1) = (1 - dxz / dxx);
				dxz = X.x[inx2] - Z.x[inz];
				set(inz, inx2) = (1 - dxz / dxx);

				inx1 = inx2;
			}
		}
	//	memory_compress();
	}
}
template<class T>
void SparseMatr<T>::memory_compress()
{
	SparseMatr<T> r(*this);

	this->swp(r);
	/*int nn;
	nn = 0;
	for (int ii = 0; ii < I.N; ii++)
	{
		nn += I.x[ii].N;
	}
	T *xx;
	xx = new T [nn];
	nn = 0;
	for (int ii = 0; ii < I.N; ii++)
	{
		memcpy(xx+nn,S.x[ii].x,S.x[ii].N*sizeof(T));
		delete S.x[ii].x;
		S.x[ii].x = xx + nn;
		nn += S.x[ii].N;
	}
	xx = 0x0;*/
}
//____________________________________


//____________________________class	SparseMatr____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________




/*int ii;
vecT<T> d_Z;
vecT<T> d_X;  //границы элементов

// X:      .   .   .   .   .   .   .   .   .   .   .     - значения аргументов элементов
//d_X:   |   |   |   |   |   |   |   |   |   |   |   |   - границы элементов

// Z:      .     .     .     .     .     .     .     .     - значения аргументов элементов
//d_Z:  |     |     |     |     |     |     |     |     |  - границы элементов

d_Z.fsetlen(Z.N + 1);
d_X.fsetlen(X.N + 1);

d_X.x[0] = X.x[0] - (X.x[1] - X.x[0]) / 2.0;
for (ii = 1; ii < X.N; ii++) { d_X[ii] = X.x[ii] - (X.x[ii] - X.x[ii-1]) / 2; } //
d_X.last() = X.last() + (X.last() - X.x[X.N - 2]) / 2.0;

d_Z.x[0] = Z.x[0] - (Z.x[1] - Z.x[0]) / 2.0;
for (ii = 1; ii < Z.N; ii++) { d_Z[ii] = Z.x[ii] - (Z.x[ii] - Z.x[ii-1]) / 2; } //
d_Z.last() = Z.last() + (Z.last() - Z.x[Z.N - 2]) / 2.0;

if ((d_X.x[0] < d_Z.last())&(d_X.last()>d_Z.x[0])) // пересечение множеств d_X и d_Z не нулевое
{
int inx1, inx2, inz1, inz2;
T dxz, dzx, dxx, dzz;

inz1 = 0;

inx1 = d_X.fmr(d_Z.x[inz1]);
if (inx1>0)
{
if (d_X.x[inx1] <= d_Z.x[inz1])
{
dxz = d_X.x[inx1] - d_Z.x[inz1];
dxx = d_X.x[inx1] - d_X.x[inx1 - 1];
set(inz1, inx1 - 1) = dxz / dxx;
}
else
{

}
}
for (inz2 = 1; inz2 < Z.N; inz2++) // перебор всех границ из d_Z и опреление оносящихся к ним элементов из d_X
{
inx2 = d_X.fmr(d_Z.x[inz2], inx1); // найти границу d_X спарва для тeкущего элемента d_Z
if (inx2 != -1)
{
inx1++;
for (; inx1 < inx2; inx1++) // цикл для тех элементов из d_X которые целиком входят в текущий d_Z
{
set(inx1, inz1) = 1.0;
}
// здесь всегда должно быть inx1 == inx2;
inx2--;
dxz = d_Z.x[inz2] - d_X.x[inx2];
dxx = d_X.x[inx1] - d_X.x[inx2];
set( inz1,inx2) = dxz / dxx;
}
inz1 = inz2;
}

}*/

//____________________________class	FullMatrix____________________________________________________________________________
//________________________________Реализация методов________________________________________________________________
//____________________________________
template <class T>
FullMatrix<T>::FullMatrix(FullMatrix<T> & r)	// конструктор копий
{
	nx	= r.nx;
	ny	= r.ny;
	s.pst(r.s);
	x.setlen(ny);
	x.x[0]= s.x;
	for(int i=1;i<ny;i++)x.x[i]	= x.x[i-1]+nx;	
}
//____________________________________
template <class T>
void  FullMatrix<T>::setSize(const int my,const int mx)	// установка размеров матрицы
{
	
	nx	= mx;
	ny	= my;
	s.setlen(mx*my);
	x.setlen(my);
	x.x[0]	= s.x;
	for(int i=1;i<ny;i++)x.x[i]	= x.x[i-1]+nx;
	//memset(s.x,0,s.N*sizeof(T));
}
//____________________________________
template <class T>
void  FullMatrix<T>::setCopy(const FullMatrix<T> &r)
{
	nx	= r.nx;
	ny	= r.ny;
	s.pst(r.s);
	x.setlen(ny);
	x.x[0]= s.x;
	for(int i=1;i<ny;i++)x.x[i]	= x.x[i-1]+nx;	
}
//____________________________________
template <class T>
void  FullMatrix<T>::setCopy(const SparseMatr<T> & r)
{
	setSize(r.ny,r.nx);
	for(int i=0;i<ny;i++)
	{
		for(int j=0;j<r.I.x[i].N;j++)
		{
			x.x[i][r.I.x[i].x[j]]	= r.S.x[i].x[j];
		}
	}
}
//____________________________________
template <class T>
void  FullMatrix<T>::setEye(const int m) // установиь квадратную единичную матрицу
{
	setSize(m,m);
	for(int i=0;i<m;i++)x.x[i][i] =1;
}
//____________________________________
template <class T>
vecT<T>  FullMatrix<T>::getdiag()	// возвращает диагональ матрицы
{
	vecT<T> b;
	int i;
	i	= nx>ny ? ny:nx;
	b.setlen(i);
	for(i=0;i<b.N;i++)b.x[i]=x.x[i][i];
	return b;
}
//____________________________________
template <class T>
void FullMatrix<T>::tns()	// транспонирование матрицы
{
	FullMatrix<T> A;
	A.setSize(nx,ny);
	for(int i=0;i<ny;i++)
	{
		for(int j=0;j<nx;j++)
		{
			A.x.x[j][i] = x.x[i][j];
		}
	}
	s.swp(A.s);
	x.swp(A.x);
	nx	= A.nx;
	ny	= A.ny;
}
//____________________________________
template <class T>
bool FullMatrix<T>::SymmTest()	// тест на симметричность матрицы
{
	//bool ch = true;
	for(int i=0;i<ny;i++)
	for(int j=i+1;j<nx;j++)
	{
		if(x.x[i][j]!=x.x[j][i]) return false;
	}
	return true;
}
//____________________________________
template <class T>
void FullMatrix<T>::getSub(FullMatrix<T> &R,const int ibeg,const int iend,const int jbeg,const int jend)
{
	T *xc;
	ny	= iend-ibeg+1;
	nx	= jend-jbeg+1;
	if(s.mN<nx*ny) s.setmem(ny*nx);
	if(x.mN<ny) x.setmem(ny);
	s.N	= nx*ny;
	x.N	= ny;
	ConnectPointer();
	xc	= R.x.x[ibeg]+jbeg;
	for(int i=0;i<ny;i++)
	{
		memcpy(x.x[i],xc,nx*sizeof(T));
		xc	+= R.nx;
	}
}
//____________________________________
template <class T>
template <class W>
void FullMatrix<T>::getSub_(FullMatrix<W> &R, const int ibeg, const int iend, const int jbeg, const int jend)
{
	W *xc;
	ny = iend - ibeg + 1;
	nx = jend - jbeg + 1;
	if (s.mN<nx*ny) s.setmem(ny*nx);
	if (x.mN<ny) x.setmem(ny);
	s.N = nx*ny;
	x.N = ny;
	ConnectPointer();
	xc = R.x.x[ibeg] + jbeg;
	T *xx;
	for (int i = 0; i<ny; i++)
	{
		xx = x.x[i];
		//memcpy(x.x[i], xc, nx * sizeof(T));
		for (int jj = 0; jj < nx; jj++)
		{
			xx[jj] = xc[jj];
		}
		xc += R.nx;
	}
}

/*
//____________________________________
template <class T>
void FullMatrix<T>::addRow() // добавить строку в конец
{
	int nwx = ny + 1;
	FullMatrix<T> L;
	L.setSize(ny, nwx);
	L.s.add(s.x, s.N);

}*/

//____________________________________
/*//____________________________________
void FullMatrix::getSub(FullMatrix<T> &R,const int ibeg,const int ni, const int di,const int jbeg,const int nj,const int dj)
{
	T *xc;
	ny	= iend-ibeg+1;
	nx	= jend-jbeg+1;
	if(s.mN<nx*ny) s.setmem(ny*nx);
	if(x.mN<ny) x.setmem(ny);
	s.N	= nx*ny;
	x.N	= ny;
	ConnectPointer();
	xc	= R.x.x[ibeg]+jbeg;
	for(int i=0;i<ny;i++)
	{
		memcpy(x.x[i],xc,nx*sizeof(T));
		xc	+= R.nx;
	}
}*/
//____________________________________
template <class T>
void FullMatrix<T>::GetNormMatrix(FullMatrix<T> & R) // возвращает в R=A*A`,A- тек. матрица, A`- транспонированная A
{
	R.setSize(ny,ny);
	T z;
	for(int i=0;i<ny;i++)
	{
		z	= 0;
		for(int k=0;k<nx;k++){z+= x.x[i][k]*x.x[i][k];}
		R.x.x[i][i]	= z;
	}
	for(int i=0;i<ny;i++)
	{
		for(int j=i+1;j<ny;j++)
		{
			z	= 0;
			for(int k=0;k<nx;k++){z+= x.x[i][k]*x.x[j][k];}
			R.x.x[j][i]	= R.x.x[i][j]	= z;
		}
	}
}
//____________________________________
template <class T>
vecT<T> & FullMatrix<T>::pmv(const vecT<T> &a, vecT<T> &b) // умножение  матрицы на вектор 'a' результат в 'b'
{
	b.N	= ny;
	memset(b.x,0,b.N*sizeof(T));
	for(int i=0;i<ny;i++) for(int j=0;j<nx;j++)	b.x[i]+=x.x[i][j]*a.x[j];
	return b;
}
//____________________________________
template<class T>
void FullMatrix<T>::sumRow(vecT<T>& a)
{
	a.fsetlen(nx);
	memset(a.x, 0, sizeof(T)*nx);
	for (ii = 0;ii < ny;ii++)
	{
		for (int jj = 0;jj < nx;jj++)
		{
			a.x[jj] += x.x[ii][jj];
		}
	}
}
//____________________________________
template<class T>
void FullMatrix<T>::sumCol(vecT<T>& a)
{
	a.fsetlen(ny);
	memset(a.x, 0, sizeof(T)*ny);
	for (ii = 0;ii < ny;ii++)
	{
		for (int jj = 0;jj < nx;jj++)
		{
			a.x[ii] += x.x[ii][jj];
		}
	}
}
//____________________________________
template <class T>
vecT<T>	FullMatrix<T>::operator * (vecT<T> &a)	// умножение на вектор;
{
	vecT<T> b;
	b.setlen(ny);
	for(int i=0;i<ny;i++) for(int j=0;j<nx;j++)	b.x[i]+=x.x[i][j]*a.x[j];
	return b;
}
//____________________________________
template <class T>
vec3T<T>	FullMatrix<T>::operator * (vec3T<T> &a)	// умножение на вектор;
{
	vec3T<T> b;

	b.x[0]	= x.x[0][0]*a.x[0]+x.x[0][1]*a.x[1]+x.x[0][2]*a.x[2];
	b.x[1]	= x.x[1][0]*a.x[0]+x.x[1][1]*a.x[1]+x.x[1][2]*a.x[2];
	b.x[2]	= x.x[2][0]*a.x[0]+x.x[2][1]*a.x[1]+x.x[2][2]*a.x[2];
	return b;
}
//____________________________________
template <class T>
T & FullMatrix<T>::set(const int my,const int mx) // доступ к элементу A(my,mx);
{
	if ((my>=ny)||(mx>=nx))
	{
		int nx_=nx;
		int ny_=ny;
		ny	= my>=ny ? my+1 : ny;
		nx	= mx>=nx ? mx+1 : nx;
		vecT<T*>	x1;
		vecT<T>		s1; 
		s1.setlen(nx*ny);
		x1.setlen(ny);
		x1.x[0]	= s1.x;
		for(int i=1;i<ny;i++) x1.x[i]	= x1.x[i-1]+nx;
		for(int i=0;i<ny_;i++) 
		{
			memcpy(x1.x[i],x.x[i],nx_*sizeof(T));
		}
		x.swp(x1);
		s.swp(s1);
		//return x.x[my][mx];
	}
	return x.x[my][mx];
}
//____________________________________
template <class T>
FullMatrix<T>	FullMatrix<T>::operator * (const FullMatrix<T> &a)
{
	T z;
	FullMatrix<T> R;
	R.setSize(ny,a.nx);
	for(int i=0;i<ny;i++)
	{
		for(int j=0;j<a.nx;j++)
		{
			z	= 0;
			for(int k=0;k<nx;k++)
			{
				z	+= x.x[i][k]*a.x.x[k][j];
			}
			if (z!=0) R.x[i][j]	= z;
		}
	}
	return R;
}//____________________________________
template <class T>
void FullMatrix<T>::Householder(vecT<T> & u, const int ibeg, const int iend, const int j)
{
	//int i;
	int k;
	T a,*xc;
	u.N	= iend-ibeg+1;
	xc	= x.x[ibeg]+j;
	for(k=0;k<u.N;k++)
	{
		u.x[k]	= xc[0];
		xc	+= nx;
	}
	a	= u.ssqr();
	//for(i=0;i<u.N;i++) a+=u.x[i]*u.x[i];
	a	= sqrt(a);
	u.x[0]	+= u.x[0]<0 ? -a : a;
}
//____________________________________
template <class T>
void FullMatrix<T>::HouseholderSymm(vecT<T> & u, const int ibeg, const int iend, const int j)
{
	T a,*xc;
	u.N	= iend-ibeg+1;
	xc	= x.x[j]+ibeg;
	memcpy(u.x,xc,u.N*sizeof(T));
	a	= u.ssqr();
	a	= sqrt(a);
	u.x[0]	+= u.x[0]<0 ? -a : a;
}
//____________________________________
template <class T>
void FullMatrix<T>::setHouse(vecT<T> & u)	//	установить матрицу отражения по вектору 'u';
{
	T z;
	int i;
	s.N	= u.N*u.N;
	x.N	= u.N;
	nx	= ny = x.N;
	ConnectPointer();
	memset(s.x,0,s.N*sizeof(T));
	z	= 0;
	for(i=0;i<u.N;i++) z+=u.x[i]*u.x[i];
	z	/= 2;
	for(i=0;i<ny;i++) x.x[i][i]	= 1-u.x[i]*u.x[i]/z;
	for(i=0;i<ny;i++)
	{
		for(int j=i+1;j<nx;j++)
		{
			x.x[j][i] = x.x[i][j]	= -u.x[i]*u.x[j]/z;
		}
	}
}
//____________________________________
template <class T>
void FullMatrix<T>::HessenbergItr(FullMatrix<T> &P,const int ic)	//	итерация приведения тек. матрицы к форме Хесенберга
{
	T z,*xc,*xp;
	static FullMatrix<T> R(ny,ny);
	if(ic==0) if(ny>R.x.mN) R.setSize(ny,ny);
	int i,ic1;
	// 1 вычисление подматрицы А12
	ic1	= ic+1;
	R.ny= ic1;
	R.nx= ny-R.ny;
	R.s.N= R.ny*R.nx;
	R.ConnectPointer();
	//R.x.x[0]	= R.s.x;
	//for(i=1;i<R.ny;i++)	{R.x.x[i]	= R.x.x[i-1]+R.nx;}
	for(i=0;i<R.ny;i++)
	{
		xc	= x.x[i]+R.ny;
		for(int j=0;j<P.ny;j++)
		{
			z =0;
			xp	= P.x.x[j];
			for(int k=0;k<P.nx;k++)
			{
				z	+= xc[k]*xp[k];
			}
			R.x[i][j]	= z;
		}
	}
	xc	= x.x[0]+R.ny;
	for(i=0;i<R.ny;i++)
	{
		memcpy(xc,R.x[i],R.nx*sizeof(T));
		xc	+= nx;
	}

	// 2 вычисление подматрицы А22
	R.ny= R.nx;
	R.s.N= R.ny*R.nx;
	for(i=1;i<R.ny;i++)	{R.x.x[i]	= R.x.x[i-1]+R.nx;}

	for(i=0;i<R.ny;i++)
	{
		xc	= x.x[i+ic1]+ic1;			
		for(int j=0;j<P.ny;j++)
		{
			xp	= P.x.x[j];
			z =0;
			for(int k=0;k<P.nx;k++)
			{
				z	+= xc[k]*xp[k];
			}
			R.x[j][i]	= z;
		}
	}

	for(i=0;i<P.ny;i++)
	{
		xp	= P.x.x[i];
		for(int j=0;j<R.ny;j++)
		{
			z =0;
			xc	= R.x.x[j];
			for(int k=0;k<P.nx;k++)
			{
				z	+= xc[k]*xp[k];
				//z	+= xp[k]*R.x.x[j][k];
			}
			x.x[i+ic1][j+ic1]	= z;
		}
	}

	// 3 вычисление ненулевого элемента подматрицы А21 и обнуление остальных элементов
	xc	= x.x[ic1]+ic;
	z	= P.x.x[0][0]*xc[0];
	for(i=1;i<P.nx;i++)
	{
		xc	+= nx;
		z	+= P.x.x[0][i]*xc[0];
		xc[0] = 0;
	}
	x.x[ic1][ic]	= z;
}
//____________________________________
template <class T>
void FullMatrix<T>::HessenbergItr(vecT<T> &u,const int ic)	//	итерация приведения тек. матрицы к форме Хесенберга
{
	T u0,z,*xc,*xp,uau;
	static vecT<T> uh(ny);
	static vecT<T> ul(ny);
	if (ic==0) if(uh.mN<ny){uh.setmem(ny);ul.setmem(ny);}
	int i,j,ic1;
	ic1	= ic+1;

	u0	= u.ssqr()/2;
	
	// 1 вычисление подматрицы А12 (не меняется на первом умножении (I-2uu')*A, но меняется на втором A*(I-2u'u))

	for(i=0;i<ic1;i++)
	{
		xc	 = x.x[i]+ic1;
		z	= 0;
		for(j =0;j<u.N;j++)z	+= xc[j]*u.x[j];
		z	/= u0;
		for(j =0;j<u.N;j++)	xc[j]	-= z*u.x[j];		
	}
	// 2 вычисление подматрицы А22

	ul.N	= uh.N	= u.N;
	for(i=0;i<u.N;i++)
	{
		xc	= x.x[i+ic1]+ic1;  // смещение к элементу A(ic+1+i,ic+1), т.е. этим указателем в цикле перебираются строки
		xp	= x.x[ic1]+i+ic1;  // смещение к элементу A(ic+1,ic+1+i), т.е. этим указателем перебираются столбцы
		z	= 0;
		uau	= 0;
		for(j =0;j<u.N;j++)// цикл скалярного умножения с вектором u
		{
			z	+= xc[j]*u.x[j]; // умножение строки
			uau	+= u.x[j]*(xp[0]); // умножение столбца
			xp	+= nx;
		}
		uh.x[i]	= z/u0;	// запомнить результат скалярного умножения текущей строки на  вектор u  + нормировка 
		ul.x[i]	= uau/u0; // запомнить результат скалярного умножения текущего столбца на вектор u  + нормировка
	}/**/
	// uau = u`*A*u
	uau	= u.scpr(uh)/u0;

	//  u*u`*A*u*u` = uau*(u*u`)
	for(i=0;i<u.N;i++)
	{
		z	= uau*u.x[i]-uh.x[i];
		xc	= x.x[i+ic1]+ic1;
		for(j=0;j<u.N;j++) xc[j]	+= z*u.x[j]-ul.x[j]*u.x[i];//z*u.x[j]-ul.x[j]*uau;
	}
	
	// 3 вычисление ненулевого элемента подматрицы А21 и обнуление остальных элементов
	x.x[ic1][ic]-=u.x[0];
	for(i=ic1+1;i<ny;i++)	x.x[i][ic] = 0;
}/**/
//____________________________________
template <class T>
void FullMatrix<T>::HessenbergItrSymm(vecT<T> &u,const int ic)	//	итерация приведения тек. матрицы к форме Хесенберга (варинта для симметричной матрицы)
{
	T u0,z,*xc,uau;
	static vecT<T> uh(ny);
	if (ic==0) if(uh.mN<ny){uh.setmem(ny);}
	int i,j,ic1;
	ic1	= ic+1;
	u0	= u.ssqr()/2;	
	// 2 вычисление подматрицы А22
	uh.N	= u.N;
	for(i=0;i<u.N;i++)
	{
		xc	 = x.x[i+ic1]+ic1;
		z	= 0;
		for(j =0;j<u.N;j++)
		{
			z	+= xc[j]*u.x[j];
		}
		uh.x[i]	= z/u0;
	}
	uau	= u.scpr(uh)/u0;
	//  u*u`*A*u*u` = uau*(u*u`)
	for(i=0;i<u.N;i++)
	{
		z	= uau*u.x[i]-uh.x[i];
		xc	 = x.x[i+ic1]+ic1;
		for(j=0;j<u.N;j++)	xc[j]	+= z*u.x[j]-uh.x[j]*u.x[i];
	}
	// 3 вычисление ненулевого элемента подматрицы А21 и обнуление остальных элементов
	x.x[ic][ic1] = x.x[ic1][ic]-=u.x[0];
	for(i=ic1+1;i<ny;i++)	x.x[ic][i]=x.x[i][ic] = 0;
}/**/
//____________________________________
//____________________________________
template <class T>
void FullMatrix<T>::HessenbergForm()	// приведение тек. матрицы к форме Хесенберга
{
	vecT<T> u(ny);
	if(!SymmTest())
	{
		for(int i=0;i<ny-2;i++)
		{
			Householder(u,i+1,ny-1,i);
			HessenbergItr(u,i);
		}
	}else
	{
		for(int i=0;i<ny-2;i++)
		{
			HouseholderSymm(u,i+1,nx-1,i);
			HessenbergItrSymm(u,i);
		}
	}
}
//________________________________________
template <class T>
void FullMatrix<T>::HessenbergForm(FullMatrix<T> &Q)	// приведени тек. матрицы к форме Хесенберга с выводом матрицы перехода Q
{
	vecT<T> u(ny);
	Q.setEye(ny);
	if(!SymmTest())
	{
		for(int i=0;i<ny-2;i++)
		{
			Householder(u,i+1,ny-1,i);
			HessenbergItr(u,i);
			Q.selfsubprod(u,i);
		}
	}else
	{
		for(int i=0;i<ny-2;i++)
		{
			HouseholderSymm(u,i+1,ny-1,i);
			HessenbergItrSymm(u,i);
			Q.selfsubprod(u,i);
		}
	}
	Q.tns();
}
//________________________________________
template <class T>
void FullMatrix<T>::selfsubprod(const FullMatrix<T> &P,const int ibeg,const int iend,const int jbeg,const int jend,bool flag) // умножение разреженной матрицы на вектор 'a' результат в 'b' A(ibeg:iend,jbeg:jend)=A(ibeg:iend,jbeg:jend)*P'
{
	static vecT<T> R(nx);
	if (flag) if(R.mN<ny) R.setmem(ny);
	T *xc,z;
	int nx_,ny_;
	nx_	= jend-jbeg+1;
	ny_	= iend-ibeg+1;
	R.N		= nx_;
	xc	= x.x[ibeg]+jbeg;
	for(int i = 0;i<ny_;i++)
	{
		for(int j=0;j<nx_;j++)
		{
			z	= 0;
			for(int k=0;k<nx_;k++)
			{
				z	+= xc[k]*P.x.x[j][k];
			}
			R.x[j]	= z;
		}
		memcpy(xc,R.x,nx_*sizeof(T));
		xc	+= nx;
	}
}
//________________________________________
template <class T>
void FullMatrix<T>::selfsubprod( vecT<T> &u,const int ic) // умножение разреженной матрицы на вектор 'a' результат в 'b' A(ibeg:iend,jbeg:jend)=A(ibeg:iend,jbeg:jend)*P'
{
	T *xc,u0,z;
	int ic1=ic+1;
	u0	= u.ssqr()/2;
	// Q -= Q*u*u`
	for(int i =1;i<ny;i++)
	{
		xc	 = x.x[i]+ic1;
		z	= 0;
		for(int j =0;j<u.N;j++)
		{
			z	+= xc[j]*u.x[j];
		}
		z	/= u0;
		for(int j =0;j<u.N;j++)
		{
			xc[j]	-= z*u.x[j];
		}
	}
	
}
//________________________________________
template <class T>
void FullMatrix<T>::qrIrtUpd( vecT<T> &u,const int ic) // 
{
	T *xc,u0,z;
	u0	= -0.5*u.ssqr();
	// A -= A*u*u`
	xc	 = x.x[ic]+ic;
	xc[0]-= u.x[0];
	xc++;
	memset(xc,0,(u.N-1)*sizeof(T));
	for(int i =ic+1;i<ny;i++)
	{
		xc	 = x.x[i]+ic;
		z	= 0;
		for(int j =0;j<u.N;j++)
		{
			z	+= xc[j]*u.x[j];
		}
		z	/= u0;
		for(int j =0;j<u.N;j++)
		{
			xc[j]	+= z*u.x[j];
		}
	}
	
}
//________________________________________
template <class T>
void FullMatrix<T>::qrIrtUpd(vecT<vecT<T> > &P, vecT<T> &u, const int ic) // 
{

	T *xc,u0,z;
	u0	= -0.5*u.ssqr();
	// A -= A*u*u`
	xc	 = x.x[ic]+ic;
	xc[0]-= u.x[0];
	xc++;
	memset(xc,0,(u.N-1)*sizeof(T));
	for(int i =ic+1;i<ny;i++)
	{
		xc	 = x.x[i]+ic;
		z	= 0;
		for(int j =0;j<u.N;j++)
		{
			z	+= xc[j]*u.x[j];
		}
		z	/= u0;
		for(int j =0;j<u.N;j++)
		{
			xc[j]	+= z*u.x[j];
		}
	}
	P.x[ic].pst(u);
}
//________________________________________
template <class T>
void FullMatrix<T>::QR(vecT<T> &b) // QR - разложение, метод для применения к решения СЛАУ b - вектор правой части СЛАУ преобразуется в вектор Q'*b 
{
	vecT<T> u(ny);
	T z,u0,*xc;
	int k;
	k	= nx>(ny-1) ? ny-1 : nx;
	tns();
	for(int i=0;i<k;i++)
	{
		Householder(u,i);
		qrIrtUpd(u,i);

		u0	= -0.5*u.ssqr();
		z	= 0;
		xc	= b.x+i;
		for(int j=0;j<u.N;j++)
		{
			z	+= u.x[j]*xc[j];
		}
		z	/= u0;
		for(int j=0;j<u.N;j++) xc[j] += u.x[j]*z;
	}
	tns();
//	if(ny>nx) memset(b.x+nx,0,(ny-nx)*sizeof(T));
}
//________________________________________
template <class T>
void FullMatrix<T>::QR(vecT<vecT<T> > &P) // QR - разложение, в P - набор столбцов дающих факторизованное представление для самой ортогональной матрицы , в текщей матрице -  получается R
{
	vecT<T> u(nx);
	int k;
	k = ny>(nx-1) ? nx-1 : ny;
	P.setlen(k);
	for(int i=0;i<k;i++)
	{
		Householder(u,i);
		qrIrtUpd(P,u,i); // в P - транспонированная матрица (факторизованный вид) Q по отношению к QR разложению
	}
}
//____________________________________
template <class T>
void FullMatrix<T>::Householder(vecT<T> & u, const int ic)
{
	T a;
	u.N	= nx-ic;
	memcpy(u.x,(x.x[ic]+ic),u.N*sizeof(T));
	a	= u.ssqr();
	a	= sqrt(a);
	u.x[0]	+= u.x[0]<0 ? -a : a;
}
//____________________________________
template <class T>
void FullMatrix<T>::getQformP(FullMatrix<T> &Q,vecT<vecT<T> > &P) // вычисление матрицы Q по её факторизавнному представлению в виде набора столбцов в P
{
	Q.setSize(ny,nx);
}
template<class T>
vecT<T> FullMatrix<T>::CG_solve(vecT<T>& b)
{
	vecT<T> xk;
	if (nx != ny) return xk;
	vecT<T> z, pk, yk, rk;
	T mk, nk, hk, res;
	const T rmin = 1e-14;
	int k;
	z.setlen(ny);
	pk.setlen(nx);
	yk.setlen(nx);
	rk.setlen(ny);
	xk.setlen(nx);
	memcpy(rk.x, b.x, nx * sizeof(T));
	memcpy(pk.x, b.x, nx * sizeof(T));
	k = 0;
	do
	{
		k++;
		pmv(pk, z);
		hk = rk.ssqr();
		nk = hk / (pk.scpr(z));
		memcpy(yk.x, pk.x, nx * sizeof(T));
		yk *= nk;
		xk += yk;
		memcpy(yk.x, z.x, nx * sizeof(T));
		yk *= nk;
		rk -= yk;
		mk = rk.ssqr() / hk;
		pk *= mk;
		pk += rk;
		res = rk.snrm();
	} while (res>rmin);
	return xk;
}
//____________________________________
template<class T>
vecT<T> & FullMatrix<T>::CG_solve(vecT<T> &xk, vecT<T>& b)
{
	if (nx != ny) return xk;
	vecT<T> z, pk, yk, rk;
	T mk, nk, hk, res;
	const T rmin = 1e-14;
	int k;
	z.fsetlen(ny);
	pk.fsetlen(nx);
	yk.fsetlen(nx);
	rk.fsetlen(ny);
	//xk.setlen(nx);
	memcpy(rk.x, b.x, nx * sizeof(T));
	memcpy(pk.x, b.x, nx * sizeof(T));
	memset(xk.x, 0, nx * sizeof(T));
	k = 0;
	do
	{
		k++;
		pmv(pk, z);
		hk = rk.ssqr();
		nk = hk / (pk.scpr(z));
		memcpy(yk.x, pk.x, nx * sizeof(T));
		yk *= nk;
		xk += yk;
		memcpy(yk.x, z.x, nx * sizeof(T));
		yk *= nk;
		rk -= yk;
		mk = rk.ssqr() / hk;
		pk *= mk;
		pk += rk;
		res = rk.snrm();
	} while (res>rmin);
	return xk;
}

//____________________________________
template <class T>
void FullMatrix<T>::QR_solver(vecT<T> &b,vecT<T> &z) // решение СЛАУ с текущей матрицей с помощью QR-разложения
{
	T a,nrb;
	int i,j;
	nrb	= sqrt(b.ssqr());
	b	/= nrb;
	if(nx>ny)
	{
		vecT<vecT<T> > Q;
		vecT<T> y;
		QR(Q);	// QR применяется к транспонированной матрице
		y.setlen(ny);
		for(i = 0;i<ny;i++)
		{
			a	= 0;
			for(j = 0;j<i;j++)
			{
				a	+= y.x[j]*x.x[i][j];
			}
			y.x[i]	= (b.x[i]-a)/x.x[i][i];
		}
		z.setlen(nx);
		memcpy(z.x,y.x,y.N*sizeof(T));
		T *xc;
		for(i=Q.N-1;i>=0;i--)
		{
			a	= 0;
			xc	= z.x+i;
			for(j = 0;j<Q.x[i].N;j++)
			{
				a	+= xc[j]*Q.x[i].x[j];
			}
			a	/= -0.5*Q.x[i].ssqr();
			for(j=0;j<Q.x[i].N;j++) xc[j] += Q.x[i].x[j]*a;
		}
	}else
	{
		QR(b);
		z.setlen(nx);
		for(i = ny-1;i>=0;i--)
		{
			a	= 0;
			for(j = i+1;j<ny;j++)
			{
				a	+= z.x[j]*x.x[i][j];
			}
			z.x[i]	= (b.x[i]-a)/x.x[i][i];
		}
	}

	z	*= nrb;
	/*QR(b);
	cout<<"this : "<<endl;
	showfull(*this);
	cout<<endl;

	k	= (nx>ny)? ny : nx;

	z.setlen(nx);
	for(i = k-1;i>=0;i--)
	{
		a	= 0;
		for(j = i+1;j<k;j++)
		{
			a	+= z.x[j]*x.x[i][j];
		}
		z.x[i]	= (b.x[i]-a)/x.x[i][i];
	}
	if(nx>ny)
	{
		T *xc,*xp;
		int p,q;
		p	= nx-ny;
		FullMatrix<T> mz;
		vecT<double> al;
		vecT<double> bl;
		mz.setSize(p,ny);
		al.setlen(p);
		bl.setlen(p);

		// построение доп. решений
		for(q=0;q<p;q++)
		{
			xc	= mz.x.x[q];	// указатель прохода по сторке матрицы доп. решений
			xp	= x.x[0]+q+ny;	// указатель прохода по столбцу матрицы
			for(i = ny-1;i>=0;i--)
			{
				a	= 0;
				for(j = i+1;j<ny;j++)
				{
					a	+= xc[j]*x.x[i][j];
				}
				xc[i]	= (xp[0]-a)/x.x[i][i];
				xp	+= nx;
			}
		}
		a	= z.ssqr();
		mz.pmv(z,bl);// bl - вектор проекций доп решений на основное решение
		al.divd(a,bl); // al - вектор коэффициентов для потроения доп решений ортогональных к основному

	}/**/
/*
	if(nx>ny)
	{
		T *xc;//f,fa,fb;
		vecT<T> c(b);
		//vecT<T> y;
		FullMatrix<T> A;
		A.getSub(*this,0,ny-1,ny,nx-1);
		A.QR(c);
		y.setlen(nx);
		xc	= y.x+ny;
		for(i = A.nx-1;i>=0;i--)
		{
			a	= 0;
			for(j = i+1;j<A.nx;j++)
			{
				a	+= xc[j]*A.x[i][j];
			}
			xc[i]	= (c.x[i]-a)/A.x[i][i];
		}
	}/**/
}
//____________________________________
template <class T>
void FullMatrix<T>::swp(FullMatrix<T> &r)	// своп с матрицей r
{
	r.s.swp(s);
	r.x.swp(x);
	//ConnectPointer();
	//r.ConnectPointer();
	int i;
	i	= r.nx;
	r.nx= nx;
	nx	= i;
	i	= r.ny;
	r.ny= ny;
	ny	= i;
}
//____________________________________
template <class T>
T FullMatrix<T>::Det() // возвращает детерминант матрицы вычисленный рекурсивно
{
	if(ny!=nx) return 0;

	ConnectPointer();
	vecT<bool> frbd;
	frbd.setlen(ny);
	frbd	= true;
	return hdet(0,0,frbd);
}
//____________________________________
template <class T>
T FullMatrix<T>::hdet(int iy, int ix,vecT<bool> &frbd)
{
	
	if(ix==(nx-1))
	{
		return  x.x[iy][ix];
	}else
	{
		if(x.x[iy][ix]==0)
		{
			return 0;
		}
		else
		{
			//frbd.add(ix);
			bool ch	 = true;
			T d,d0,d1;	// переменная для вычисления детерминанта текущего уровня
//			frbd.x[ix]	= false;	// пометить текущую строку как запрещённую
			//d1	= x.x[iy][ix];	// значение текущего элемента
			//ix++;
			vecT<int> v(ny); // вектор разрешённых индексов строк
			for(int ii=0;ii<ny;ii++){if(frbd.x[ii]) {v.add(ii);}} // заполнение по маске запрещённых индексов
			d	= 0;
			int iy_;
			for(int ii=0;ii<v.N;ii++)	// оснвной цикл
			{
				iy	= v.x[ii];	// присвоить значение текущей главной строки
				d0	= x.x[iy][ix];
				iy_	= iy;
				frbd.x[iy]	= false;	// пометить текущую строку как запрещённую
				iy	= frbd.fnd(true);	// установить номер строки по первому ненулевому элементу маски запрещений
				d0	*= hdet(iy,ix+1,frbd);	// вычислить детерминант мартицы нижнего уровня
				ch ? d+=d0 : d-=d0; // в  d помещается сумма всех детерминатнов нижнего уровня (с учётом знака -)
				//d	+= d0;
				frbd.x[iy_]	= true;	// разрешить текущую строку
				ch = !ch;	// изменить статус знака
			}
//			frbd.x[ix]	= true;	// разрешить текущую строку
			return d;
		}
	}
	return 0;
}
//____________________________________
template <class T>
void FullMatrix<T>::Shift() // перемещает края матрицы в центр, а центр на края
{
	FullMatrix<T> A;
	A.setSize(ny,nx);
	int mx,my;
	mx = nx/2;
	my = ny/2;
	ConnectPointer();
	for (int ii = 0;ii<my;ii++)
	{
		for(int jj = 0;jj<mx;jj++)
		{
			A.fst(ii,jj) = fst((ny-my)+ii,(nx-mx)+jj);
		}
	}
	for (int ii = 0;ii<my;ii++)
	{
		for(int jj = mx;jj<nx;jj++)
		{
			A.fst(ii,jj) = fst((ny-my)+ii,jj-mx);
		}
	}
	for (int ii = my;ii<ny;ii++)
	{
		for(int jj = mx;jj<nx;jj++)
		{
			A.fst(ii,jj) = fst(ii-my,jj-mx);
		}
	}
	for (int ii = my;ii<ny;ii++)
	{
		for(int jj = 0;jj<mx;jj++)
		{
			A.fst(ii,jj) = fst(ii-my,(nx-mx)+jj);
		}
	}
	s.swp(A.s);
	ConnectPointer();
}
template<class T>
void FullMatrix<T>::getRow(int nrow,vecT<T> &V) // 
{
	if (V.x != 0x0)
	{
		V.setempty();
		//exit(1);
		//delete V.x;
	}
	V.x = x.x[nrow];
	V.N = V.mN = nx;
}
//____________________________________
template <class T>
void FullMatrix<T>::PartCorrelation(FullMatrix<T> & C,int dny,int dnx)
{
	vecT<T> Loc(s);
	vecT<int> idpp(s.N),id0(s.N);
	T GSum,Z;
	int *hx;
	idpp.var1D(0,1,s.N-1);
	GSum = 0;
	for (int ii = 0;ii<s.N;ii++){GSum += s.x[ii];} 
	GSum /= s.N;
	Loc	-= GSum;
	C.setSize(2*dny,2*dnx);
	for (int ii=0;ii<dny;ii++)
	{
		id0.pst(idpp);
		for(int jj=0;jj<dnx;jj++)
		{
			Z = 0;
			for(int kk =0;kk<Loc.N;kk++){Z += Loc.x[kk]*Loc.x[idpp.x[kk]];}
			C.x.x[ii][jj] = Z;
			--idpp;
			hx = idpp.x+jj;
			for(int kk=0;kk<Loc.N;kk+=nx){hx[kk]+=nx;}
		}

		idpp.pst(id0);
		for(int jj=1;jj<dnx;jj++)
		{
			
			++idpp;
			hx = idpp.x+nx-jj;
			for(int kk=0;kk<Loc.N;kk+=nx){hx[kk]-=nx;}

			Z = 0;
			for(int kk =0;kk<Loc.N;kk++){Z += Loc.x[kk]*Loc.x[idpp.x[kk]];}
			C.x.x[ii][C.nx-jj] = Z;

		}

		idpp.pst(id0);
		idpp -= nx;
		hx = idpp.x+ii*nx;
		for(int kk=0;kk<nx;kk++){hx[kk]+=Loc.N;}
	}
	C.s	/=	(T)s.N;

	//C.Shift();
	for (int ii=1;ii<=dny;ii++)
	{
		for(int jj=1;jj<=dnx;jj++)
		{
			C.x.x[C.ny-ii][C.nx-jj] = C.x.x[ii][jj];//fst(C.ny-ii,C.nx-jj) = C.fst(ii,jj);
			C.x.x[C.ny-ii][jj] = C.x.x[ii][C.nx-jj];//fst(ii-1,C.nx-jj);
		}
	}
	for(int ii = 1;ii<dny;ii++)
	{
		C.x.x[C.ny-ii][0] = C.x.x[ii][0];
	}

}
//____________________________________
template <class T>
void FullMatrix<T>::FullCorrelation(FullMatrix<T> & C)
{
	vecT<T> Loc(s);
	vecT<int> idpp(s.N);
	T GSum,Z;
	int *hx;
	idpp.var1D(0,1,s.N-1);
	for (int ii = 0;ii<s.N;ii++){GSum += s.x[ii];} 
	GSum /= s.N;
	Loc	-= GSum;
	C.setSize(ny,nx);
	for (int ii=0;ii<ny;ii++)
	{
		for(int jj=0;jj<nx;jj++)
		{
			Z = 0;
			for(int kk =0;kk<Loc.N;kk++){Z += Loc.x[kk]*Loc.x[idpp.x[kk]];}
			C.x.x[ii][jj] = Z;
			--idpp;
			hx = idpp.x+jj;
			for(int kk=0;kk<Loc.N;kk+=nx){hx[kk]+=nx;}
		}
		idpp -= nx;
		hx = idpp.x+ii*nx;
		for(int kk=0;kk<nx;kk++){hx[kk]+=Loc.N;}
	}
	C.s	/=	(T)s.N;
}
//____________________________________
template <class T>
void FullMatrix<T>::FullCorrelationInt(FullMatrix<T> & C)
{
	vecT<T> Loc(s);
	vecT<int> idpp(s.N);
	T Z;
	int *hx;
	idpp.var1D(0,1,s.N-1);
	C.setSize(ny,nx);
	for (int ii=0;ii<ny;ii++)
	{
		for(int jj=0;jj<nx;jj++)
		{
			Z = 0;
			for(int kk =0;kk<Loc.N;kk++){Z += Loc.x[kk]*Loc.x[idpp.x[kk]];}
			C.x.x[ii][jj] = Z;
			--idpp;
			hx = idpp.x+jj;
			for(int kk=0;kk<Loc.N;kk+=nx){hx[kk]+=nx;}
		}
		idpp -= nx;
		hx = idpp.x+ii*nx;
		for(int kk=0;kk<nx;kk++){hx[kk]+=Loc.N;}
	}
}
//____________________________________
template <class W>
void showfull ( FullMatrix<W> &a)
{
	cout.precision(4);
	cout<<scientific;
	for(int i=0;i<a.ny;i++)
	{
		for(int j = 0;j<a.nx;j++)
		{
			cout<<a.x.x[i][j]<<"	";
		}
		cout<<endl;
	}
}
//____________________________________
template <class T>
void FullMatrix<T>::showfull_infile (const char *fname)
{
	fstream sss;
	sss.open(fname,ios::out);
	sss.precision(17);
	//cout.precision(4);
	//sss<<scientific;
	for(int i=0;i<ny;i++)
	{
		for(int j = 0;j<nx;j++)
		{
			sss<<get(i,j)<<"	";
		}
		sss<<endl;
	}
	sss.close();
}
//____________________________________
//____________________________________


//____________________________class	FullMatrix____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________




//____________________________class	TriDiag____________________________________________________________________________
//_______________________________Реализацяи методов___________________________________________________________________
template <class T>
TriDiag<T>::TriDiag(TriDiag<T> &r)	//
{
	n=r.N; D.pst(r.D);L.pst(r.L);U.pst(r.U);
}
//____________________________________
template <class T>
void TriDiag<T>::setCopy(FullMatrix<T> &r)	// создать по 3 диагоналям плотной матрицы r
{
	n	= r.ny>r.nx ? r.nx : r.ny;
	D.setlen(n);L.setlen(n-1);U.setlen(n-1);
	D.x[0]	= r.fst(0,0);
	if(n>1)
	{
		U.x[0]	= r.fst(0,1);
		r.ConnectPointer();
		T *x;
		int ii;
		for(ii=1;ii<n-1;ii++)
		{
			x		= r.x.x[ii]+ii-1;
			L.x[ii-1]	= *x;
			x++;
			D.x[ii]	= *x;
			x++;
			U.x[ii]	= *x;
		}
		ii	= n-1;
		L.x[ii-1]	= r.fst(ii,ii-1);
		D.x[ii]	= r.fst(ii,ii);
	}
}
//____________________________________
template <class T>
void TriDiag<T>::setCopy(SparseMatr<T> &r)	// создать по 3 диагоналям разрежённой матрицы r
{
	n	= r.ny>r.nx ? r.nx : r.ny;
	D.setlen(n);L.setlen(n-1);U.setlen(n-1);
	D.x[0]	= r.get(0,0);
	for(int ii=1;ii<n;ii++)
	{
		L.x[ii-1]	= r.get(ii-1,ii);
		D.x[ii]		= r.get(ii,ii);
		U.x[ii-1]	= r.get(ii,ii-1);
	}
}
//____________________________________
template <class T>
T  TriDiag<T>::get(const int iy, const int ix)	// вернуть значение элемента трёхдиагональной матрицы
{

	if(iy==ix)
	{
		return D.x[ix];
	}
	else
	{
		if(ix==iy+1)
		{
			return U.x[iy];
		}else
		{
			if(iy==ix+1)
			{
				return L.x[ix];
			}else
				return  0;
		}

	}
	return 0;
}
//____________________________________
template <class T>
vecT<T> & TriDiag<T>::pmv(const vecT<T> &a, vecT<T> &b) // умножение  матрицы на вектор 'a' результат в 'b'
{
	b.N	= n;
	memset(b.x,0,b.N*sizeof(T));
	for(int i=0;i<n;i++)	{b.x[i]	=  D.x[i].*a.x[i];}
	for(int i=0;i<n-1;i++)	{b.x[i]	+= U.x[i].*a.x[i+1];}
	for(int i=0;i<n-1;i++){b.x[i+1]	+= L.x[i].*a.x[i];}
	return b;
}
//____________________________________
template <class T>
void TriDiag<T>::getsub(TriDiag<T> &Tr,const int & ibeg,const int & iend)	// выдать часть трёхдиагональную матрицы в Тr от (ibeg:iend,ibeg:iend)
{
	int k;
	k	= iend-ibeg+1;
	if(k>0)
	{
		Tr.n	= k;
		Tr.D.add(D.x+ibeg,k);
		k--;
		Tr.U.add(U.x+ibeg,k);
		Tr.L.add(L.x+ibeg,k);
	}
}
//____________________________________
template <class T>
void TriDiag<T>::separation(TriDiag<T> &T1, TriDiag<T> &T2, const int & nsep) // разделить исходную матрицу на две, с номером - разделителем nsep
{
	if((nsep>0)&&(nsep<n))
	{
	/*	T1.n	= k	= nsep;
		T1.D.x	= D.x;
		T1.U.x	= U.x;
		T1.L.x	= L.x;
		T1.D.N	= k;
		k--;
		T1.D.N	= T1.U.N = k;

		T2.n	= k = n-nsep;
		T2.D.x	= D.x+nsep;
		T2.U.x	= U.x+nsep;
		T2.L.x	= L.x+nsep;
		T2.D.N	= k;
		k--;
		T2.D.N	= T2.U.N = k;*/

		int k;
		T1.n= k	= nsep;
		T1.D.add(D.x,k);
		k--;
		T1.U.add(U.x,k);
		T1.L.add(L.x,k);

		T2.n= k = n-nsep;
		T2.D.add(D.x+nsep,k);
		k--;
		T2.U.add(U.x+nsep,k);
		T2.L.add(L.x+nsep,k);
		/**/
	}
}
//____________________________________
template <class T>
void TriDiag<T>::DC_eig(TriDiag<T> &Tr, SparseMatr<T> &Q, vecT<T> &D)	// решение задачи на собсвенные значение методом "разделяй и властвуй"
{
	if(Tr.n==1)
	{
		Q.setSize(1,1);
		Q.set(0,0)	= 1;
		D.setlen(1);
		D.x[0]	= Tr.D.x[0];
	}else
	{
		// 1 представить T= [T1 0 ; T2 0] + b_m*v*v'
		int n1;
		n1	= Tr.n>>1;	// номер -разделитель исходной матрицы
		TriDiag<T> T1,T2;
		separation(T1,T2,n1);	// разделение исходной матрицы на две T1 и T2 (без создания копий)
		T b_m;
		b_m	= T.U.x[n1-1];	// выделение наддиагонального элемента
		
		// 2 DC_eig(T1,Q1,D1);DC_eig(T2,Q2,D2);
		vecT<T> D1,D2;
		SparseMatr<T> Q1,Q2;
		DC_eig(T1,Q1,D1);
		DC_eig(T2,Q2,D2);

		// 3 построить DD+b_m*u*u' по D1,D2,Q1,Q2 и вычислить спектр D
		vecT<T> u1,u2;
		if(D1.x[D1.N-1]>D2.x[0]) // проверка крайних собственных значений - для удержания порядка возрастнания. 
		{
			D1.swp(D2); // свопы матриц
			Q1.swp(Q2);
		}
		Q1.getrow(Q1.nx-1,u1).add(Q2.getrow(0,u2)); // в u1 - объединение последней строки Q1 и первой строки Q2
		Q1.UniMatr(Q2);	//  объеденение исходных Q1 и Q2 в Q1
		//Q1.tns();	// транспонирование - для хранения векторов q по строкам
		// проверка входных собственных значений на кратность
		D1.add(D2);	// объединение исходных собсвенных значений
		vecT< vec2T<int> > singular; // массив номеров кратных собвенных значений и их кратность.
		vecT<int> nslg(D1.N);	// номера из D1 для однократного выбора собсвтенных значений
		{
			vec2T< int> locsin;
			singular.N = 0;
			bool ch = true;
			for(int ii=1;ii<D1.N;ii++)
			{
				if(D1.x[i-1]==D.x[x])
				{
					if(ch)
					{
						locsin.x[0]	= i-1;
						locsin.x[1]	= 2;
						singular.add(locsin);
						ch	= false;
						nslg.add(ii);
					}else
					{
						singular.x[singular.N-1].x[1]++;
					}
				}else
				{
					nslg.add(ii);
					ch	= true;
				}
			}
		}
		// обработка кратных корней
		vecT<T> u_;	// вектор для хранения части вектора u по которой выстравается ортогональное подпространство
		D.setlen(D1.N);
		Q.setSize(Q1.ny,Q1.nx);
		for(int ii=0;ii<singular.N;ii++)	// перебор групп кратных корней - проверка равенства нулю компоненты i вектора u (d_(i)=d_(i+1))
		{
			for(jj=0;jj<singular.x[ii].x[1];jj++)
			{
				if(u.x[ii+jj]==0)
				{
					D.x[ii+jj]	= D1.x[ii+jj];
					
				}
			}
		}


		// и матрицу собственных векторов Q` для матрицы DD+ro*u*u'
		// построить матрицу Q=[Q1 0; 0 Q2]*Q`

		// сброс указатей в матрицах Т1 и Т2
	/*	T1.D.x	= 0x0;T1.D.N	= 0;
		T1.L.x	= 0x0;T1.U.N	= 0;
		T1.U.x	= 0x0;T1.L.N	= 0;
		T2.D.x	= 0x0;T2.D.N	= 0;
		T2.L.x	= 0x0;T2.U.N	= 0;
		T2.U.x	= 0x0;T2.L.N	= 0;
		T2.n	= T1.n	= 0;/**/
	}
}
//____________________________________
template <class T>
void TriDiag<T>::showfull_infile (const char *fname)
{
	fstream sss;
	sss.open(fname,ios::out);
	sss.precision(17);
	//cout.precision(4);
	//sss<<scientific;
	for(int i=0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			sss<<get(i,j)<<"	";
		}
		sss<<endl;
	}
	sss.close();
}
//____________________________________
//____________________________class	TriDiag____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________





//____________________________class	Quaternion____________________________________________________________________________
//________________________________Реализация методов________________________________________________________________
//____________________________________
template <class T>
Quaternion<T>  Quaternion<T>::operator * (const Quaternion<T> & r)
{
	Quaternion<T> v;
	
	v.x[0]	= x[0]*r.x[0]-x[1]*r.x[1]-x[2]*r.x[2]-x[3]*r.x[3];
	v.x[1]	= x[0]*r.x[1]+x[1]*r.x[0]+x[2]*r.x[3]-x[3]*r.x[2];
	v.x[2]	= x[0]*r.x[2]+x[2]*r.x[0]+x[3]*r.x[1]-x[1]*r.x[3];
	v.x[3]	= x[0]*r.x[3]+x[3]*r.x[0]+x[1]*r.x[2]-x[2]*r.x[1];

	return v;
}
//____________________________________
template <class T>
Quaternion<T> & Quaternion<T>::operator *= (const Quaternion<T> & r)
{
	Quaternion<T> v(*this);

	x[0]	= v.x[0]*r.x[0]-v.x[1]*r.x[1]-v.x[2]*r.x[2]-v.x[3]*r.x[3];
	x[1]	= v.x[0]*r.x[1]+v.x[1]*r.x[0]+v.x[2]*r.x[3]-v.x[3]*r.x[2];
	x[2]	= v.x[0]*r.x[2]+v.x[2]*r.x[0]+v.x[3]*r.x[1]-v.x[1]*r.x[3];
	x[3]	= v.x[0]*r.x[3]+v.x[3]*r.x[0]+v.x[1]*r.x[2]-v.x[2]*r.x[1];

	return *this;
}
//____________________________________
template <class T>
Quaternion<T> Quaternion<T>::operator /(const Quaternion<T> & r)
{
	Quaternion<T> v;
	const T nr	= r.norm();
	
	v.x[0]	= (x[0]*r.x[0]+x[1]*r.x[1]+x[2]*r.x[2]+x[3]*r.x[3])/nr;
	v.x[1]	= (-x[0]*r.x[1]+x[1]*r.x[0]-x[2]*r.x[3]+x[3]*r.x[2])/nr;
	v.x[2]	= (-x[0]*r.x[2]+x[2]*r.x[0]-x[3]*r.x[1]+x[1]*r.x[3])/nr;
	v.x[3]	= (-x[0]*r.x[3]+x[3]*r.x[0]-x[1]*r.x[2]+x[2]*r.x[1])/nr;

	return v;
}
//____________________________________
template <class T>
Quaternion<T> & Quaternion<T>::operator /=(const Quaternion<T> & r)
{
	Quaternion<T> v(*this);

	const T nr	= r.norm();
	
	x[0]	= (v.x[0]*r.x[0]+v.x[1]*r.x[1]+v.x[2]*r.x[2]+v.x[3]*r.x[3])/nr;
	x[1]	= (-v.x[0]*r.x[1]+v.x[1]*r.x[0]-v.x[2]*r.x[3]+v.x[3]*r.x[2])/nr;
	x[2]	= (-v.x[0]*r.x[2]+v.x[2]*r.x[0]-v.x[3]*r.x[1]+v.x[1]*r.x[3])/nr;
	x[3]	= (-v.x[0]*r.x[3]+v.x[3]*r.x[0]-v.x[1]*r.x[2]+v.x[2]*r.x[1])/nr;

	return *this;
}
//____________________________________
template <class T>
vecT<T> Quaternion<T>::rotat()
{
	vecT<T> v;
	v.setlen(4);
	T sn;

	v.x[0]	= acos(x[0]);
	sn	= sin(v.x[0]);
	v.x[0]	*=2;
	v.x[1]	= x[1].*sn;
	v.x[2]	= x[2].*sn;
	v.x[3]	= x[3].*sn;

	return v;
}
//____________________________________
template <class T>
Quaternion<T> & Quaternion<T>::rotat(double &fi,vec3T<T> &r)
{
	T	sn;
	sn	= sin(fi/2);
	x[0]	= cos(fi/2);
	x[1]	= r.x[0]*sn;
	x[2]	= r.x[1]*sn;
	x[3]	= r.x[2]*sn;

	return *this;
}
//____________________________________
template <class T>
void Quaternion<T>::rotation(vecT<T> &r)
{
	FullMatrix<T> A;
	A	= qua2matrR();
	r	= A*r;
}
//____________________________________
template <class T>
FullMatrix<T> Quaternion<T>::qua2matrA()
{
	FullMatrix<T> A;
	A.setSize(4,4);

	A.fst(0,0)=A.fst(1,1)=A.fst(2,2)=A.fst(3,3)	= x[0];
	A.fst(0,1)=A.fst(2,3)=-A.fst(1,0)=A.fst(3,2)=x[1];
	A.fst(2,0)=A.fst(1,3)=-A.fst(0,2)=A.fst(3,1)=-x[2];
	A.fst(0,3)=A.fst(1,2)=-A.fst(2,1)=A.fst(3,0)=x[3];

	return A;
}
//____________________________________
template <class T>
FullMatrix<T> Quaternion<T>::qua2matrB()
{
	FullMatrix<T> A;
	A.setSize(4,4);

	A.fst(0,0)=A.fst(1,1)=A.fst(2,2)=A.fst(3,3)	= x[0];
	A.fst(0,1)=A.fst(2,3)=-A.fst(1,0)=A.fst(3,2)=x[1];
	A.fst(0,2)=A.fst(1,3)=-A.fst(2,0)=A.fst(3,1)=x[2];
	A.fst(0,3)=A.fst(2,1)=-A.fst(1,2)=A.fst(3,0)=x[3];

	return A;
}
//____________________________________
template <class T>
FullMatrix<T> Quaternion<T>::qua2matrR()
{
	FullMatrix<T> R;
	R.setSize(3,3);

	R.fst(0,0)	= x[0]*x[0]+x[1]*x[1]-x[2]*x[2]-x[3]*x[3];
	R.fst(1,1)	= x[0]*x[0]-x[1]*x[1]+x[2]*x[2]-x[3]*x[3];
	R.fst(2,2)	= x[0]*x[0]-x[1]*x[1]-x[2]*x[2]+x[3]*x[3];

	R.fst(0,1)	= 2*(x[1]*x[2]-x[0]*x[3]);
	R.fst(1,0)	= 2*(x[1]*x[2]+x[0]*x[3]);

	R.fst(0,2)	= 2*(x[1]*x[3]+x[0]*x[2]);
	R.fst(2,0)	= 2*(x[1]*x[3]-x[0]*x[2]);

	R.fst(1,2)	= 2*(x[2]*x[3]-x[0]*x[1]);
	R.fst(2,1)	= 2*(x[2]*x[3]+x[0]*x[1]);

	return R;
}
//____________________________________
//____________________________________

//____________________________class	Quaternion____________________________________________________________________________
//_______________________________Конец реализации методов_____________________________________________________________





#endif