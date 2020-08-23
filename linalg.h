#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include <memory.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>

#define pi_num 3.1415926535897932384626433832795

template <class T>
class vec4T
{
public:

	T x[4];

	inline vec4T() {};
	inline vec4T(const T &inx,const T &iny,const T &inz,const T &in4){x[0] = inx; x[1] = iny; x[2] = inz; x[3] = in4;}
	inline vec4T(vec4T<T> &r)  {memcpy(x,r.x,4*sizeof(T));}

	//static const int T_size	= 3*sizeof(T);
	
	//inline void			nrml()	{T a =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); x[0] /=a;  x[1] /=a; x[2] /=a;}	// нормировка
	//inline T			norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}		// норма текущего вектра 
	//inline T			sqnr()	{return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}			// квадрат норма текущего вектра 
	//inline T			scpr(vec3T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]+x[2]*a.x[2]);}		// скалярное произведение текущего вектра и вектора 'a'
	//inline vec3T<T>&	crss(vec3T<T> &a,vec3T<T>	&b)	// векторное произведение [a x b] результат в текущий вектор
	//	{x[0]	= a.x[1]*b.x[2]-a.x[2]*b.x[1];x[1]	= a.x[2]*b.x[0]-a.x[0]*b.x[2];x[2]	= a.x[0]*b.x[1]-a.x[1]*b.x[0];return *this;	}

	inline vec4T<T> operator + (const vec4T<T> & r){vec4T<T> v(*this); v.x[0]+=r.x[0];v.x[1]+=r.x[1];v.x[2]+=r.x[2];v.x[3]+=r.x[3]; return v; }
	inline vec4T<T> & operator += (const vec4T<T> & r){ x[0]+=r.x[0];x[1]+=r.x[1];x[2]+=r.x[2];x[3]+=r.x[3]; return *this; }

	inline vec4T<T> operator - (const vec4T<T> & r){vec4T<T> v(*this); v.x[0]-=r.x[0];v.x[1]-=r.x[1];v.x[2]-=r.x[2];v.x[3]-=r.x[3]; return v; }
	inline vec4T<T> & operator -= (const vec4T<T> & r){ x[0]-=r.x[0];x[1]-=r.x[1];x[2]-=r.x[2];x[3]-=r.x[3]; return *this; }

	inline vec4T<T> operator * (const vec4T<T> & r){vec4T<T> v(*this); v.x[0]*=r.x[0];v.x[1]*=r.x[1];v.x[2]*=r.x[2];v.x[3]*=r.x[3]; return v; }
	inline vec4T<T> & operator *= (const vec4T<T> & r){ x[0]*=r.x[0];x[1]*=r.x[1];x[2]*=r.x[2];x[3]*=r.x[3]; return *this; }
	inline vec4T<T> & operator *= (const T & r){ x[0]*=r;x[1]*=r;x[2]*=r;x[3]*=r; return *this; }

	inline vec4T<T> operator / (const vec4T<T> & r){vec4T<T> v(*this); v.x[0]/=r.x[0];v.x[1]/=r.x[1];v.x[2]/=r.x[2];v.x[3]/=r.x[3]; return v; }
	inline vec4T<T> & operator /= (const vec4T<T> & r){ x[0]/=r.x[0];x[1]/=r.x[1];x[2]/=r.x[2];x[3]/=r.x[3]; return *this; }
	inline vec4T<T> & operator /= (const T & r){ x[0]/=r;x[1]/=r;x[2]/=r;x[3]/=r; return *this; }

	inline vec4T<T> & operator = (const vec4T<T> & r){x[0]=r.x[0];x[1]=r.x[1];x[2]=r.x[2];x[3]=r.x[3]; return *this; }
	inline vec4T<T> & operator = (const T & r){x[0]=r;x[1]=r;x[2]=r;x[3]=r; return *this; }

//	template <class W>	friend std::istream &	operator >>(std::istream &stream,const vec4T<W> &a);/**/
//	template <class W>	friend std::ostream & operator << (std::ostream &stream,const vec4T<W> &a);
};

template <class T>
class vec3T
{
public:

	T x[3];

	inline vec3T() {};
	inline vec3T(const T &inx,const T &iny,const T &inz){x[0] = inx; x[1] = iny; x[2] = inz;}
	inline vec3T(vec3T<T> &r)  {memcpy(x,r.x,3*sizeof(T));}

	//static const int T_size	= 3*sizeof(T);
	
	inline void			nrml()	{T a =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); x[0] /=a;  x[1] /=a; x[2] /=a;}	// нормировка
	inline T			norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}		// норма текущего вектра 
	inline T			sqnr()	{return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}			// квадрат норма текущего вектра 
	inline T			scpr(vec3T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]+x[2]*a.x[2]);}		// скалярное произведение текущего вектра и вектора 'a'
	inline vec3T<T>&	crss(vec3T<T> &a,vec3T<T>	&b)	// векторное произведение [a x b] результат в текущий вектор
		{x[0]	= a.x[1]*b.x[2]-a.x[2]*b.x[1];x[1]	= a.x[2]*b.x[0]-a.x[0]*b.x[2];x[2]	= a.x[0]*b.x[1]-a.x[1]*b.x[0];return *this;	}

	inline vec3T<T> operator + (const vec3T<T> & r){vec3T<T> v(*this); v.x[0]+=r.x[0];v.x[1]+=r.x[1];v.x[2]+=r.x[2]; return v; }
	inline vec3T<T> & operator += (const vec3T<T> & r){ x[0]+=r.x[0];x[1]+=r.x[1];x[2]+=r.x[2]; return *this; }

	inline vec3T<T> operator - (const vec3T<T> & r){vec3T<T> v(*this); v.x[0]-=r.x[0];v.x[1]-=r.x[1];v.x[2]-=r.x[2]; return v; }
	inline vec3T<T> & operator -= (const vec3T<T> & r){ x[0]-=r.x[0];x[1]-=r.x[1];x[2]-=r.x[2]; return *this; }

	inline vec3T<T> operator * (const vec3T<T> & r){vec3T<T> v(*this); v.x[0]*=r.x[0];v.x[1]*=r.x[1];v.x[2]*=r.x[2]; return v; }
	inline vec3T<T> & operator *= (const vec3T<T> & r){ x[0]*=r.x[0];x[1]*=r.x[1];x[2]*=r.x[2]; return *this; }
	inline vec3T<T> operator * (const T &r){vec3T<T> v(*this); v.x[0]*=r;v.x[1]*=r;v.x[2]*=r; return v; }
	inline vec3T<T> & operator *= (const T & r){ x[0]*=r;x[1]*=r;x[2]*=r; return *this; }

	inline vec3T<T> operator / (const vec3T<T> & r){vec3T<T> v(*this); v.x[0]/=r.x[0];v.x[1]/=r.x[1];v.x[2]/=r.x[2]; return v; }
	inline vec3T<T> & operator /= (const vec3T<T> & r){ x[0]/=r.x[0];x[1]/=r.x[1];x[2]/=r.x[2]; return *this; }
	inline vec3T<T> operator / (const T &r){vec3T<T> v(*this); v.x[0]/=r;v.x[1]/=r;v.x[2]/=r; return v; }
	inline vec3T<T> & operator /= (const T & r){ x[0]/=r;x[1]/=r;x[2]/=r; return *this; }

	inline vec3T<T> & operator = (const vec3T<T> & r){x[0]=r.x[0];x[1]=r.x[1];x[2]=r.x[2]; return *this; }
	inline vec3T<T> & operator = (const T & r){x[0]=r;x[1]=r;x[2]=r; return *this; }

	template <class W>	friend std::istream &	operator >>(std::istream &stream,const vec3T<W> &a);/**/
	template <class W>	friend std::ostream & operator << (std::ostream &stream,const vec3T<W> &a);
};

template <class W> 
std::istream &	operator >>(std::istream &stream,const vec3T<W> &a){stream>> a.x[0];stream>> a.x[1];stream>> a.x[2]; return stream;};
template <class W> 
std::ostream &	operator <<(std::ostream &stream,const vec3T<W> &a){stream<< a.x[0]<<" "<<a.x[1]<<" "<<a.x[2]<<'\n'; return stream;}



template <class T>
class vec2T
{
public:

	T x[2];

	inline vec2T() {};
	inline vec2T(const T &inx,const T &iny){x[0] = inx; x[1] = iny;}
	inline vec2T(vec2T &r)  {memcpy(x,r.x,2*sizeof(T));}

	//static const int T_size	= 2*sizeof(T);
	
	inline T	scpr(vec2T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]);}				// скалярное произведение текущего вектора и вектора 'a'
	inline T	crss(vec2T<T> &a)	{return x[0]*a.x[1]-x[1]*a.x[0];}	// векторное произведение текущего вектора и вектора 'a'


	inline vec2T operator + (const vec2T & r){vec2T v(*this); v.x[0]+=r.x[0];v.x[1]+=r.x[1]; return v; }
	inline vec2T & operator += (const vec2T & r){ x[0]+=r.x[0];x[1]+=r.x[1]; return *this; }
	inline vec2T & operator += (const T & r){ x[0]+=r;x[1]+=r; return *this; }\

	inline vec2T operator - (const vec2T & r){vec2T v(*this); v.x[0]-=r.x[0];v.x[1]-=r.x[1]; return v; }
	inline vec2T & operator -= (const vec2T & r){ x[0]-=r.x[0];x[1]-=r.x[1]; return *this; }

	inline vec2T operator * (const vec2T & r){vec2T v(*this); v.x[0]*=r.x[0];v.x[1]*=r.x[1]; return v; }
	inline vec2T & operator *= (const vec2T & r){ x[0]*=r.x[0];x[1]*=r.x[1]; return *this; }

	inline vec2T operator / (const vec2T & r){vec2T v(*this); v.x[0]/=r.x[0];v.x[1]/=r.x[1]; return v; }
	inline vec2T & operator /= (const vec2T & r){ x[0]/=r.x[0];x[1]/=r.x[1]; return *this; }

	inline vec2T & operator = (const vec2T & r){x[0]=r.x[0];x[1]=r.x[1]; return *this; }
	inline vec2T & operator = (const T & r){x[0]=r;x[1]=r; return *this; }

	inline bool  operator == (const vec2T<T> & r){return ((x[0]==r.x[0])&(x[1]==r.x[1]));}
	inline bool  operator != (const vec2T<T> & r){return !((x[0]==r.x[0])&(x[1]==r.x[1]));}

	template <class W>	friend std::istream &	operator >>(std::istream &stream,const vec2T<W> &a);/**/
	template <class W>	friend std::ostream & operator << (std::ostream &stream,const vec2T<W> &a);

};

template <class W> 
std::istream &	operator >>(std::istream &stream,const vec2T<W> &a){stream>> a.x[0];stream>> a.x[1]; return stream;};
template <class W> 
std::ostream &	operator <<(std::ostream &stream,const vec2T<W> &a){stream<< a.x[0]<<" "<<a.x[1]<<'\n'; return stream;}

typedef	vec3T<double> vec3db;
typedef	vec2T<double> vec2db;
typedef	vec4T<int> vec4int;
typedef	vec3T<int> vec3int;
typedef	vec2T<int> vec2int;


//template<class T> class msT;

//bool dlt;	// идентификатор удаления
template <class T>
class vecT
{
public:
	T	*x;	// указатель на массив.
	int N;	// длина массива. !!! эффективно, длинна массива считается равной 'N'!!!
	int mN;	// текущее количество выделенной мамяти для массива (в единицах элементов массива)
	static const int sz = sizeof(T);
	static const int dN	= 32;
//____________________________________
	// Конструкторы
	vecT();				// по умолчанию
	vecT(int n);			// только выделение памяти на 'n' элементов.
	vecT(const T *a,int n);	// конструктор обычного заполнения
	vecT(const T *a,int n,int m);		// конструктор избыточного выделения памяти
	vecT(const vecT <T> &r);			// конструктор копий
	vecT(const char *a);	// конструктор для строк

	~vecT(){delete [] x;}				// деструктор

	// Методы выделения памяти

	void addmem(int n);			// выделить дополнительно память на 'n' элементов. Предыдущие данные сохраняются
	void addmem();				// выделить дополнительно память на 'dN' элементов. Предыдущие данные сохраняются
	void setmem(int n);			// выделить память на 'n' элементов. Предыдущие данные забываются
	void setmem();				// выделить память на 'dN' элементов. Предыдущие данные забываются

	void setlen(int n);			// выделить память на 'n' элементов и установить длину равную N. Предыдущие данные забываются
	void fsetlen(int n);			// выделить память на 'n' элементов, если нужно, и установить длину равную n.
	inline void zero(); // обнулить все значения(заполнение нулями всех элементов)

	void setValue(const T &y, int pos);  // установить значение y на позицию pos

	// Методы множеств
	void add(const T &y);				// добавить один элемент в конец массива
	void add(const T &y, int pos);	// встатвить один элемент в массив на позикию 'pos'
	void add(const vecT<T> &y);		// добавить другой массив в конец данного массива
	void add(const vecT<T> &y,int &pos);		// вставить другой массив в данный массив с позиции 'pos'
	void add(const T* y, const int n);	// вставить в конец массив из 'n' элементов по указателю 'y'.
	void add(const char* y);	// вставить в конец массив из 'n' элементов по указателю 'y'.
	//void adt(T &a,T &b);	// добавить два элемента в конец
	void pst(const vecT<T> &y);	// заменить текущий массив на массив 'y' (с проверкой размера)
	void swp(vecT<T> &y);	// поменять друг с другом текущий массив и массив 'y'
	void pad(vecT<T> &y);		// добавить другой массив в конец данного массива в случае если элемент массива 
	void pad(T &y);		// добавить другой массив в конец данного массива в случае если элемент массива 
	void adp(T &y);
//	void pad(T &y);		// добавить другой массив в конец данного массива в случае если элемент массива имеет поле указателя
	//template <class W>
	//void pad(vecT<T> &y); // добавить другой массив в конец данного массива в случае если элемент массива является массивом типа msT<T>
	void adz(); // добавить нулевой элемент в конец массива

	void rem();				// удаляет последний элемент.
	void rem(int y);		// удаляет 'y' последних элементов.
	void rem(int y, int pos);	// удаляет 'y' элементов начиная с позиции 'pos'.


	vecT<T>	&	ind(vecT<int> &in, vecT<T> &a);	// запись в массив 'a' элементов текущего массива с позициями из массива 'in'.
	vecT<T>	&	its(vecT<T> & a, vecT<T> & b);	// возвращает пересечение текущего массива и массива 'a'.
	vecT<T>	&	itss(vecT<T> & a,vecT<T> & b);	// возвращает пересечение текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
	void		itssi(vecT<T> & a,vecT<vec2int> &id);	// возвращает индексы пересечения текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
	void		itssi_(vecT<T> & a,vecT<vec2int> &id);	// аналогично itssi(), но дла случавев когда в тек. массиве имеются повторяющиеся элементы
	vecT<T>	&	uni(vecT<T> & a, vecT<T> & b);	// возвращает в b объеденение текущего массива и массива 'a'.
	vecT<T>	&	unis(vecT<T> & a,vecT<T> & b);	// возвращает в b объеденение текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
	void		unisi(vecT<T> & a,vecT<T> &b,vecT<int> &id);	// возвращает индексы объединения текущего массива и массива 'a'. оптимизированный метод для отсортированных массивов.
	vecT<int> &	fnd(vecT<int> &in,T a);			// находит номера элементов массива равных 'a'.
	vecT<int> &	fnd(vecT<bool> &in,vecT<int> &a);// находит номера истиных элементов массива 'in' и помещает их в 'a'.
	void fnd(vecT<bool> &in,vecT<int> &a,vecT<int> &b);// находит номера истиных элементов массива 'in' и помещает их в 'a'
														// , а номера ложных - в 'b'.

	int			fnd(const T &a,const T &b);	// определяет первый номер массива который не равен 'a' и не равен 'b'.
	int			fnd(const T &a);		// находит номер первого элемента в текущем массиве, который равен 'a'

	int			fmr(const T &a);	//находит первый элемента массива больше 'a'
	int			fmre(const T &a);	//находит первый элемента массива больше либо равен 'a'

	int			fmr(const T &a, int beg);	//находит первый элемента массива больше 'a', начиная поиск с номера  beg
	int			fmre(const T &a, int beg);	//находит первый элемента массива больше либо равен 'a', начиная поиск с номера  beg

	int idscheck();	// возвращает число совпадений элементов с их индексами для

	void sort();					// сортировка массива. (метод пузырька)
	void sort(vecT<T> &a);			// я??я??я??я??я?? я??я??я??я??я??я??я??я??я??я??'a'.
	void sort(vecT<T> &a, vecT<int> &j);// я??я??я??я??я?? я??я??я??я??я??я??я??я??я??я??'a', я??'j' - я??я??я?? я??я??я??я??я?? 'a'.
	void sort_(vecT<int> &j);	// сортировка массива. в 'j' - индексы перестановок

	void qsort(); // быстрая сортировка (рекурсивный метод слияний)
	
	void setbindec(int n);	// заполнить текущий массив числами 2^k сумма которых даёт входное число n

	inline T & operator [](const int &i) {return x[i];}	// перегрузка оператора индексации

	inline T & last(){return x[N-1];}

	void setempty() { delete[] x; N = mN = 0; x = 0x0; } // опустошает текущий массив  

	T scpr(vecT<T> &r); // скалярное произведение текущего вектора на вектор r
	T ssqr(){T a=0; for(int i=0;i<N;++i) a+=x[i]*x[i]; return a;}	// квадрат длины вектора в Евклидовой метрике
	T snrm(){T a=0; for(int i=0;i<N;++i) a+=x[i]*x[i]; return (a/N);}	// квадрат длины вектора в Евклидовой метрике
	T sum() { T a = 0; for (int i = 0; i<N; ++i) a += x[i] ; return a; }

	T shft_crl(vecT<T> &r, int dn); // свёртка текущего вектора с вектором r циклчески сдвинутым на dn позиций вправо  sum(x[ii]*r.x[ii-dn]) 
	int max_crl_shft(vecT<T> &r, int gs);  // определение наилучшего сдвига вектора r в смысле макмальной корреляции, с начальным предположением gs 
	void cycle_shift(vecT<T> &r, int dn); //  циклический сдвиг текущего массива на dn элементов вправо, результат в r; r(ii) = x(ii-dn)

	vecT<T> & vec_abs() { for (int i = 0; i < N; i++) x[i] = abs(x[i]); return *this; } // модуль

	T max(){T d = x[0]; for(int i=0;i<N;i++) d = d<x[i] ? x[i] : d; return d;}
	T min(){T d = x[0]; for(int i=0;i<N;i++) d = d>x[i] ? x[i] : d; return d;}

	T max(int &id) { id = 0; T d = x[0]; for (int i = 0; i < N; i++) if (d < x[i]) { d = x[i]; id = i; }  return d; }
	T min(int &id) { id = 0; T d = x[0]; for (int i = 0; i < N; i++) if (d > x[i]) { d = x[i]; id = i; }  return d; }

	void var1D(const T &xbeg,const T &dx,const T &xend);	// заполнить массивом от xbeg до  xend  с шагом dx
	void var1D_(const T &xbeg, const T &dx, const int &N1); // заполнить массивом от xbeg с шагом dx на NN элементов

	void interp1(const vecT<T>& x_in, const vecT<T>& y_in, const vecT<T>& x_out); // линейная интерполяция зависимости y_in(x_in) на множество значений x_out  Результат в текущий массив  x_in и x_out - должны быть отсортированы
	void Lanczos_interp( const vecT<T>&y_in, int n_, int a_); // интерполяция на сетку в n раз гуще сплайнами Ланцоша порядка a; результат в текуший массив; предполагается равномерная сетка аргументов для y_in
	void Lanczos_interp(const vecT<T>&y_in, int n_, int a_,const vecT<T> &x0, const vecT<T> &L0); // интерполяция на сетку в n раз гуще сплайнами Ланцоша порядка a; результат в текуший массив; предполагается равномерная сетка аргументов для y_in


	T ModeLevel(int Nres); // - значение с максимумом распределения, Nres - количество интервалов разбиения для построения гистограммы  
	void StatDistr(int Nres, T & mode, T & sigma); // определение максимума распределения mode и разброса sigma

		// парегрузка операторов
	vecT<T> &	operator = (const vecT<T> &a) 
	{
		if(N<a.N) setmem(a.N); 
		N=a.N; 
		for(int i = 0;i<N;++i)
		{
			x[i]=a.x[i];
		}
		return *this;
	}//{pst(a);return *this;}
	vecT<T> &	operator = (const T &a) {for(int i = 0;i<N;++i) x[i]=a; return *this;}
	vecT<T>		operator + (const vecT<T> &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]+=a.x[i]; return r;}
	vecT<T>		operator - (const vecT<T> &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]-=a.x[i]; return r;}
	vecT<T>		operator * (const vecT<T> &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]*=a.x[i]; return r;}
	vecT<T>		operator / (const vecT<T> &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]/=a.x[i]; return r;}
	vecT<T>		operator + (const T &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]+=a; return r;}
	vecT<T>		operator - (const T &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]-=a; return r;}
	vecT<T>		operator * (const T &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]*=a; return r;}
	vecT<T>		operator / (const T &a){vecT<T> r(*this); for(int i = 0;i<N;++i) r.x[i]/=a; return r;}
	vecT<T> &	operator +=(const vecT<T> &a){for(int i = 0;i<N;++i) x[i]+=a.x[i]; return *this;}
	vecT<T> &	operator -=(const vecT<T> &a){for(int i = 0;i<N;++i) x[i]-=a.x[i]; return *this;}
	vecT<T> &	operator *=(const vecT<T> &a){for(int i = 0;i<N;++i) x[i]*=a.x[i]; return *this;}
	vecT<T> &	operator /=(const vecT<T> &a){for(int i = 0;i<N;++i) x[i]/=a.x[i]; return *this;}
	vecT<T> &	operator +=(const T &a){for(int i = 0;i<N;++i) x[i]+=a; return *this;}
	vecT<T> &	operator -=(const T &a){for(int i = 0;i<N;++i) x[i]-=a; return *this;}
	vecT<T> &	operator *=(const T &a){for(int i = 0;i<N;++i) x[i]*=a; return *this;}
	vecT<T> &	operator /=(const T &a){for(int i = 0;i<N;++i) x[i]/=a; return *this;}
	vecT<T> &	operator --(){for(int i = 0;i<N;++i) x[i]--; return *this;}
	vecT<T> &	operator ++(){for(int i = 0;i<N;++i) x[i]++; return *this;}

	

	template <class W>	friend vecT<W> operator - (vecT<W> &a);

	template <class W> friend vecT<W> operator +(const W &a,const vecT<W> &b);
	template <class W> friend vecT<W> operator -(const W &a,const vecT<W> &b);
	template <class W> friend vecT<W> operator *(const W &a,const vecT<W> &b);
	template <class W> friend vecT<W> operator /(const W &a,const vecT<W> &b);


	vecT<T> &	diff() { T *xx; xx = x; for (int i = 1; i < N; i++)  {*xx -= x[i];	*xx = -*xx;	xx++;} 	N--; return *this; } // численное дифференцирование с уменьшением размера массива на единицу

	// доп. функции - оптимизация для обхода излишних копирований
	void plus(vecT<T> &a,vecT<T> &b); // x = a+b, где x - тек. вектор 
	void minus(vecT<T> &a,vecT<T> &b);// x = a-b, где x - тек. вектор 
	void prod(vecT<T> &a,vecT<T> &b); // x = a*b, где x - тек. вектор 
	void divd(vecT<T> &a,vecT<T> &b); // x = a/b, где x - тек. вектор 
	void plus(T &a,vecT<T> &b); // x = a+b, где x - тек. вектор 
	void minus(T &a,vecT<T> &b);// x = a-b, где x - тек. вектор 
	void prod(T &a,vecT<T> &b); // x = a*b, где x - тек. вектор 
	void divd(T &a,vecT<T> &b); // x = a/b, где x - тек. вектор 

	template <class W>
	friend void showfull (vecT<W> &a);

	template <class W>	friend std::istream & operator >>(std::istream &stream,const vecT<W> &a);
	template <class W>	friend std::ostream & operator << (std::ostream &stream,const vecT<W> &a);

	vecT<T> & sinc(vecT<T> &x_in);  // вычисление sinc(x) для элементов текущего массива, результат в  текущий масив
	vecT<T> & lncz(vecT<T> &x_in, int a);  // вычисление sinc(x)*sinc(x/a) для элементов текущего массива, результат в  текущий масив
};

typedef	vecT<double> vecdb;
typedef vecT<int> vecint;
typedef vecdb* p_vecdb;
typedef vecint* p_vecint;

template <class W> 
std::istream &	operator >>(std::istream &stream,const vecT<W> &a)
{
	int N;
	stream>> N;
	if(N>a.mN) a.setlen(N);
	a.N	= N;
	for(int i =0;i<a.N;i++) stream>>a.x[i];
}
template <class W> 
std::ostream &	operator <<(std::ostream &stream,const vecT<W> &a)
{
	stream<<a.N<<'\n';
	for(int i =0;i<a.N;i++) stream<<" "<<a.x[i];
	stream<<'\n';
	return stream;
}



/*
template<class T>
class msT	: public vecT<T>
{
public:
	//static bool dlt;	// идентификатор удаления

	msT();
	msT(int n);			// только выделение памяти на 'n' элементов.
	msT(const T *a,int n);	// конструктор обычного заполнения
	msT(const T *a,int n,int m);		// конструктор избыточного выделения памяти
	msT(const msT <T> &r);			// конструктор копий
	msT(const vecT <T> &r);			// конструктор копий

	void pad(msT<T> &y);		// добавить другой массив в конец данного массива в случае если элемент массива 
	void pad(T &y);		// добавить другой массив в конец данного массива в случае если элемент массива 

	~msT()
	{
		if (dlt)
		{
			delete [] x;
		}
	}				// деструктор
};
/**/
/*
template<class T>
class sparse
{public :
	vecT<vecT<T> > S;
	int nx,ny;

	sparse() {};	// по умолчанию	
	sparse(int n,int m);	// 
	sparse(sparse<T> & r);	// конструктор копий
};

/**/
template<class T>
class sparse
{public :
	vecT<T>	S;		// массив для хранения ненулевыхх элементов
	vecT<int> I;	// массив для хранения номеров стобцов ненулевых элементов
	vecT<int> J;	// массив с номерами первых ненулевых элементов в строке
	int nx,ny;		// размеры матрицы

	sparse() {nx=ny=0;};	// по умолчанию	
	sparse(sparse<T> & cpspr);	// конструктор копий

	void init(int n, int nz); // инициалилация матрицы n_x_n  c nz ненулевыми элементами.

	T get(const int my,const int mx); // доступ к элементу A(my,mx);
	T & set(const int my,const int mx); // доступ к элементу A(my,mx);
	T & fst(const int my,const int mx); // быстрый доступ к элементу A(my,mx) при обращении к заведомо существующему элементу

	void tns();	// транспонирование матрицы
	vecT<T> & pmv_f(vecT<T> &a, vecT<T> &b); // умножение разреженной матрицы на вектор 'a' результат в 'b' (ускоренный метод)
	vecT<T> & pmv(vecT<T> &a, vecT<T> &b); // умножение разреженной матрицы на вектор 'a' результат в 'b'
private:
	T& addpos(const int my,const int mx,const int i);	// инициализация нового элеметна со строкой mx, и номеров i в массиве S (используется в set)

};/**/

template<class T> class FullMatrix;

// другая реализация разреженной матрицы
template<class T>
class SparseMatr
{public :
	vecT<vecT<T> >	 S;	// данные матрицы
	vecT<vecT<int> > I;	// индексы стоблцов
	int nx,ny;	// размеры матрицы

	SparseMatr() {nx=ny=0;};	// по умолчанию	
	SparseMatr(SparseMatr<T> & r);	// конструктор копий
	~SparseMatr(){}

	void setSize(const int my,const int mx);	// установка размеров матрицы

	void reSize(const int my,const int mx);	// установка новых размеров матрицы с сохранением данных.

	void setCopy(SparseMatr<T> & r);
	void setCopy(FullMatrix<T> & r);
	template<class W>
	void setCopyW(SparseMatr<W> & r);

	void setSignature(vecT<vecint> & id); // установка сигнатуры ненулевых элементов матрица - специальное выделение памяти. в id - индексы ненулевых элементов
		
	T get(const int my,const int mx); // доступ к элементу A(my,mx);
	T & set(const int my,const int mx); // доступ к элементу A(my,mx);
	T & fst(const int my,const int mx); // быстрый доступ к элементу A(my,mx) при обращении к заведомо существующему элементу

	void swp(SparseMatr<T> & r);	// своп данных с матрицей r

	void del(const int my,const int mx); // удалить (присвоить занчение 0) элемент A(my,mx)
	void delsym(const int my); // удалить строку и столбец my с перемещением последней строки на место 'my' (алгоритм для симмертичной мартицы)

	void symswp(const int my);	// поменять местами строку и столбец my с последней строкой и столбцом (алгоритм для симмертичной мартицы)
	void ColumnSwap(const int &id1,const int &id2); // поменять местами 2 столбца
	void RowSwap(const int &id1,const int &id2){if((id1>=0)&&(id2>=0)&&(id1<ny)&&(id2<ny)){S.x[id1].swp(S.x[id2]);I.x[id1].swp(I.x[id2]);}}

	vecT<T> getdiag();	// возвращает диагональ матрицы

	void tns();	// транспонирование матрицы

	void GetNormMatrix(SparseMatr<T> & R); // возвращает в R=A*A`,A- тек. матрица, A`- транспонированная A

	void Householder(vecT<T> & u, int &is, const int ic);	// вычисление вектора Хаусхолдера
	void qrIrtUpd(SparseMatr<T> &Q, vecT<T> &u,int &is, const int ic); // обновление матрицы за один шаг итерации отражения хаусхолдера
	void QR(SparseMatr<T> &Q); // QR - разложение
	void QR_MatrPrepating(SparseMatr<T> &R); // копирование текущей матрицы в R, R-имеет сигнатуру разрежённости конечной верхнетреугольной матрицы. 
	void QR_solver(vecT<T> &b,vecT<T> &z); // решение СЛАУ с текущей матрицей с помощью QR-разложения

	void SetOrthoBasis(vecT<T> &u); // установить в текущую матрицу строки-вектора ортогонального базиса ортогонального заданному вектору u.
	void OrthoBin(int &jj,int &ii,int &n,vecT<T> &u, vecT<T> &y, double &a);	// основная функция бинарной ортогонализации

	 vecT<T> & getrow(int ir,vecT<T> &u); // выдать в u строку с номером ir;


	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // умножение разреженной матрицы на вектор 'a' результат в 'b'

	vecT<T> CG_solve(vecT<T> &b);	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты)
	vecT<T> CGNORM_solve(vecT<T> &b);	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты к нормализованным уравнения)
	vecT<T> CGNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты к нормализованным уравнения)
	vecT<T> CGMNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты к нормализованным уравнения)
	vecT<T> StCGNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// решение системы линейных уравнений Ax=b, где A- текущая разреженная матрица (сопряжённые градиенты к нормализованным уравнения)


	void interp_dstrb(vecT<T> &X, vecT<T> &Z); // вычисление матрицы M для интерполяция функции распределения  Y(Х) на область опреледения Z; F(Z)= M*Y(X) 

	void memory_compress(); // выделение памяти одним сплошным блоком - так чтобы занимать минимум памяти


	SparseMatr<T> &	operator = (SparseMatr<T> &a) {setCopy(a);return *this;}
	//SparseMatr<T>	operator + (SparseMatr<T> &a);
	//SparseMatr<T>	operator - (SparseMatr<T> &a);
	SparseMatr<T>	operator * (SparseMatr<T> &a);
	//SparseMatr<T>	operator + (SparseMatr<T> &a);

	void UniMatr(SparseMatr<T> &r);	 // объединение двух матриц в текущей матрице. Матрица r добавляется по диагонали снизу справа.

	template <class W>
	friend void showfull (SparseMatr<W> &a);

	template <class W>
	friend void showfull_infile ( SparseMatr<W> &a,const char *fname);
};

/*template<class T>
class SparseMatrSym : public SparseMatr
{

}*/

template<class T>
class FullMatrix
{public :
	//vecT<T* > S;	//	массив указателей
	vecT<T*>	x; 	//	массив указателей на начало каждой строки
	vecT<T>		s;  // массив данных
	int nx,ny;	// число столбцов и строк

	FullMatrix() {x=0x0; nx=ny=0;}	// по умолчанию	
	FullMatrix(const int my,const int mx) {setSize(my, mx);}
	FullMatrix(FullMatrix<T> & r);	// конструктор копий
	~FullMatrix(){}

	void ConnectPointer(){x.x[0]=s.x;for(int i=1;i<ny;i++)	{x.x[i]	= x.x[i-1]+nx;}}	// привязка указателя

	void setSize(const int my,const int mx);	// установка размеров матрицы
	void setEye(const int m); // установиь квадратную единичную матрицу

	void setCopy(const FullMatrix<T> & r);
	void setCopy(const SparseMatr<T> & r);

	inline T get(const int my,const int mx){return (my<ny)&&(mx<nx) ? x.x[my][mx] : 0 ;} // доступ к элементу A(my,mx);
	inline T & fst(const int my,const int mx){return x.x[my][mx];} // доступ к элементу A(my,mx);
	T & set(const int my,const int mx); // доступ к элементу A(my,mx);

	vecT<T> getdiag();	// возвращает диагональ матрицы


/*	void addRow(); // добавить строку в конец
	void addRow(int ps); // вставить строку на позицию ps со сдвигом остальных строк вних
	void remRow(); // удалить последнюю строку
	void remRow(int ps); // цдалить строку с позиции ps

	void addColumn(); // добавить столбец в конец матрицы
	void addColumn(int ps); // вставить столбец на позицию ps 
	void remColumn(); // удалить последний столбец
	void remColumn(int ps); // удалить столбец с позиции ps
	*/

	void tns();	// транспонирование матрицы
	void getSub(FullMatrix<T> &R,const int ibeg,const int iend,const int jbeg,const int jend);
	template<class W>
	void getSub_(FullMatrix<W> &R, const int ibeg, const int iend, const int jbeg, const int jend);
	//void getSub(FullMatrix<T> &R,const int ibeg,const int ni, const int di,const int jbeg,const int nj,const int dj);
	void Shift(); // перемещает края матрицы в центр, а центр на края

	void getRow(int nrow,vecT<T> &V); // вернуть в V вектор хранящий строку с номером nrow (! V.x должно быть равно 0!!!)


	void GetNormMatrix(FullMatrix<T> & R); // возвращает в R=A*A`,A- тек. матрица, A`- транспонированная A

	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // умножение матрицы на вектор 'a' результат в 'b'

	void sumRow(vecT<T> &a); // возвращает в 'a' сумму по строкам (суммирование вдоль столбца)
	void sumCol(vecT<T> &a); // возвращает в 'a' сумму по столбцам (суммирование вдоль строк)

	bool SymmTest();	// тест на симметричность матрицы

	void selfsubprod(const FullMatrix<T> &P,const int ibeg,const int iend,const int jbeg,const int jend, bool flag =false); // умножение разреженной матрицы на вектор 'a' результат в 'b'
	void selfsubprod( vecT<T> &u,const int ic); // умножение разреженной матрицы на вектор 'a' результат в 'b'

	void Householder(vecT<T> & u, const int ibeg,const int iend, const int j);	// вычисление вектора Хаусхолдера по столбцу
	void HouseholderSymm(vecT<T> & u, const int ibeg,const int iend, const int j);	// вычисление вектора Хаусхолдера по строке
	void Householder(vecT<T> & u, const int ic);	// вычисление вектора Хаусхолдера по строке

	void setHouse(vecT<T> & u);	//	установить матрицу отражения по вектору 'u';

	void HessenbergItr(FullMatrix<T> &P,const int ic);	//	итерация приведения тек. матрицы к форме Хесенберга
	void HessenbergItr(vecT<T> & u,const int ic);	//	итерация приведения тек. матрицы к форме Хесенберга

	void HessenbergItrSymm(vecT<T> &u,const int ic);	//	итерация приведения тек. матрицы к форме Хесенберга (вариант для симметричной матрицы)

	void HessenbergForm();	// приведение тек. матрицы к форме Хесенберга
	void HessenbergForm(FullMatrix<T> &Q);	// приведение тек. матрицы к форме Хесенберга с выводом матрицы перехода Q

	void QR(vecT<T> &b); // QR - разложение, метод для применения к решения СЛАУ b - вектор правой части СЛАУ преобразуется в вектор Q'*b 
	void QR(vecT<vecT<T> > &P); // QR - разложение, в P - факторизованная ортогоналная матрица, в текщей матрице -  получается R
	void qrIrtUpd( vecT<T> &u,const int ic); // шаг qr - итерации, 
	void qrIrtUpd(vecT<vecT<T> > &P, vecT<T> &u, const int ic); //  шаг qr - итерации, 
	void QR_solver(vecT<T> &b,vecT<T> &z); // решение СЛАУ с текущей матрицей с помощью QR-разложения
	void getQformP(FullMatrix<T> &Q,vecT<vecT<T> > &P); // вычисление матрицы Q по её факторизавнному представлению в виде набора столбцов в P



	vecT<T> CG_solve(vecT<T> &b);// решение системы линейных уравнений Ax=b, где A- текущая матрица (сопряжённые градиенты)
	vecT<T> & CG_solve(vecT<T> &xk, vecT<T> &b);// решение системы линейных уравнений Ax=b, где A- текущая матрица (сопряжённые градиенты)

	FullMatrix<T> &	operator = (const FullMatrix<T> &a) {setCopy(a);return *this;}
	//FullMatrix<T>	operator + (FullMatrix<T> &a);
	//FullMatrix<T>	operator - (FullMatrix<T> &a);
	FullMatrix<T>	operator * (const FullMatrix<T> &a);
	//FullMatrix<T>	operator + (FullMatrix<T> &a);

	void swp(FullMatrix<T> &r);	// своп с матрицей r

	vecT<T>	operator * (vecT<T> &a);	// умножение на вектор;

	vec3T<T>	operator * (vec3T<T> &a);	// умножение на вектор;


	void FullCorrelation(FullMatrix<T> & C); // возвращает в C матрицу коллеляции текущей матрицы 
	void FullCorrelationInt(FullMatrix<T> & C); // возвращает в C матрицу коллеляции текущей матрицы 
	void PartCorrelation(FullMatrix<T> & C,int dny,int dnx); // возвращает в C матрицу коллеляции текущей матрицы. размер области смещений - (0:dnx,0:dny)

	T Det(); // возвращает детерминант матрицы вычисленный рекурсивно  (не применять для размера матрицы более чем 11);
	T hdet(int iy, int ix,vecT<bool> &frbd); // рекурсивно вызываемая функция для вычисления детерминанта

	template <class W>
	friend void showfull (FullMatrix<W> &a);

//		template <class W>
	void showfull_infile (const char *fname);
/**/
};

typedef	vec4T<FullMatrix <unsigned int> > vec4FMuint;
typedef	vec4T<FullMatrix <unsigned short> > vec4FMushort;
typedef vec4T<FullMatrix <double> > vec4FMdouble;

template <class T>
class TriDiag	// класс трёхдиагональной матрицы
{
public:
	int n;	// размер матрицы nxn
	vecT<T> D;	// главная диагональ
	vecT<T> L;	// нижняя диагональ
	vecT<T> U;	// верхняя диагональ

	TriDiag(){n=0;}
	TriDiag(TriDiag<T> & r);// rконструктор копий
	~TriDiag(){}

	void setSize(const int i){n=i; D.setlen(n);L.setlen(n-1);U.setlen(n-1);}
	void setCopy(FullMatrix<T> &r);	// создать по 3 диагоналям плотной матрицы r
	void setCopy(SparseMatr<T> &r);	// создать по 3 диагоналям разреженной матрицы r

	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // умножение матрицы на вектор 'a' результат в 'b'

	void getsub(TriDiag<T> &Tr,const int & ibeg,const int & iend);	// выдать часть трёхдиагональную матрицы в Т от (ibeg:iend,ibeg:iend)
	void separation(TriDiag<T> &T1, TriDiag<T> &T2, const int & nsep); // разделить исходную матрицу на две, с номером - разделителем nsep

	//void DC_eig(FullMatrix<T> &Q, vecT<T> &D);	// решение задачи на собсвенные значение методом "разделяй и властвуй"
	void DC_eig(TriDiag<T> &Tr, SparseMatr<T> &Q, vecT<T> &D);	// решение задачи на собсвенные значение методом "разделяй и властвуй"

	T get(const int iy, const int ix);	// вернуть значение элемента трёхдиагональной матрицы

	void showfull_infile (const char *fname);
};

template<class T>
class Quaternion
{
public :
	T x[4];	// компонеты кватерниона

	inline Quaternion() {};
	inline Quaternion(const T &in0,const T &inx,const T &iny,const T &inz){x[0] = in0;x[1] = inx; x[2] = iny; x[3] = inz;}
	inline Quaternion(Quaternion<T> &r)  {memcpy(x,r.x,4*sizeof(T));}

	inline Quaternion<T> operator + (const Quaternion<T> & r){Quaternion<T> v(*this); v.x[0]+=r.x[0];v.x[1]+=r.x[1];v.x[2]+=r.x[2];v.x[3]+=r.x[3]; return v; }
	inline Quaternion<T> & operator += (const Quaternion<T> & r){ x[0]+=r.x[0];x[1]+=r.x[1];x[2]+=r.x[2];x[3]+=r.x[3]; return *this; }

	inline Quaternion<T> operator - (const Quaternion<T> & r){Quaternion<T> v(*this); v.x[0]-=r.x[0];v.x[1]-=r.x[1];v.x[2]-=r.x[2]; v.x[3]-=r.x[3];return v; }
	inline Quaternion<T> & operator -= (const Quaternion<T> & r){ x[0]-=r.x[0];x[1]-=r.x[1];x[2]-=r.x[2]; x[3]-=r.x[3];return *this; }

	inline Quaternion<T> operator * (const Quaternion<T> & r);//{Quaternion<T> v(*this); v.x[0]*=r.x[0];v.x[1]*=r.x[1];v.x[2]*=r.x[2]; return v; }
	inline Quaternion<T> & operator *= (const Quaternion<T> & r);//{ x[0]*=r.x[0];x[1]*=r.x[1];x[2]*=r.x[2]; return *this; }

	inline Quaternion<T> & operator = (const Quaternion<T> & r){x[0]=r.x[0];x[1]=r.x[1];x[2]=r.x[2]; x[3]=r.x[3];return *this; }
	inline Quaternion<T> & operator = (const T & r){x[0]=r;x[1]=r;x[2]=r; x[3]=r; return *this; }

	inline Quaternion<T> conj(){Quaternion<T> v; v.x[0]=x[0];v.x[1]=-x[1];v.x[2]=-x[2]; v.x[3]=-x[3];return v; }	// возвращает сопряжёный кватерион
	inline Quaternion<T> & conjugate(){x[1]=-x[1];x[2]=-x[2];x[3]=-x[3]; return *this;} // сопряжение текущего кватерниона

	inline T norm(){ return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]);}	// норма кватерниона
	inline T nmml(){T nr =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]); x[0]/=nr;x[1]/=nr;x[2]/=nr;x[3]/=nr; return nr; }

	inline Quaternion<T> & invs(){T nr=(*this).norm(); x[0]/=nr x[1]/=-nr;x[2]/=-nr;x[3]/=-nr; return *this;}
	inline Quaternion<T>  inv(){T nr=(*this).norm(); Quaternion<T> v; v.x[0]=x[0]/nr;v.x[1]=-x[1]/nr;v.x[2]=-x[2]/nr;v.x[3]=-x[3]/nr; return v;}

	inline Quaternion<T> operator / (const Quaternion<T> & r);//{ T nr=r.norm();Quaternion<T> v(r); v.x[0]/=nr; v.x[1]/=-nr; v.x[2]/=-nr; v.x[3]/=-nr;  return (*this)*=r; }
	inline Quaternion<T> & operator /= (const Quaternion<T> & r);//{ x[0]/=r.x[0];x[1]/=r.x[1];x[2]/=r.x[2]; return *this; }


	vecT<T> rotat();	// возращает угол поворота и направление оси поворота ссответвующий нормированному кватерниону (только для нормироаных кватернионов) 

	void rotation(vecT<T> &r);	// производит поворот вектора r вокруг оси кватерниона на угол опредлеляемый кватернионом

	Quaternion<T> & rotat(double &fi,vec3T<T> &r); // определяет компоненты кватерниона для описания поворота вокруг оси r на угол fi

	FullMatrix<T> qua2matrA();	// генерация матричного представления в виде A-матрицы
	FullMatrix<T> qua2matrB();	// генерация матричного представления в виде B-матрицы

	FullMatrix<T> qua2matrR();	// генерация матричного представления в виде матрицы 3D поворота

	void clear(){memset(x,0x0,4*sizeof(T));}
	void zerospin(){memset(x,0x0,4*sizeof(T));x[0]=1.0;}


};

#include "linalg.cpp"

#endif