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
	
	//inline void			nrml()	{T a =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); x[0] /=a;  x[1] /=a; x[2] /=a;}	// ����������
	//inline T			norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}		// ����� �������� ������ 
	//inline T			sqnr()	{return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}			// ������� ����� �������� ������ 
	//inline T			scpr(vec3T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]+x[2]*a.x[2]);}		// ��������� ������������ �������� ������ � ������� 'a'
	//inline vec3T<T>&	crss(vec3T<T> &a,vec3T<T>	&b)	// ��������� ������������ [a x b] ��������� � ������� ������
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
	
	inline void			nrml()	{T a =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); x[0] /=a;  x[1] /=a; x[2] /=a;}	// ����������
	inline T			norm()	{return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}		// ����� �������� ������ 
	inline T			sqnr()	{return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);}			// ������� ����� �������� ������ 
	inline T			scpr(vec3T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]+x[2]*a.x[2]);}		// ��������� ������������ �������� ������ � ������� 'a'
	inline vec3T<T>&	crss(vec3T<T> &a,vec3T<T>	&b)	// ��������� ������������ [a x b] ��������� � ������� ������
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
	
	inline T	scpr(vec2T<T> &a)	{return (x[0]*a.x[0]+x[1]*a.x[1]);}				// ��������� ������������ �������� ������� � ������� 'a'
	inline T	crss(vec2T<T> &a)	{return x[0]*a.x[1]-x[1]*a.x[0];}	// ��������� ������������ �������� ������� � ������� 'a'


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

//bool dlt;	// ������������� ��������
template <class T>
class vecT
{
public:
	T	*x;	// ��������� �� ������.
	int N;	// ����� �������. !!! ����������, ������ ������� ��������� ������ 'N'!!!
	int mN;	// ������� ���������� ���������� ������ ��� ������� (� �������� ��������� �������)
	static const int sz = sizeof(T);
	static const int dN	= 32;
//____________________________________
	// ������������
	vecT();				// �� ���������
	vecT(int n);			// ������ ��������� ������ �� 'n' ���������.
	vecT(const T *a,int n);	// ����������� �������� ����������
	vecT(const T *a,int n,int m);		// ����������� ����������� ��������� ������
	vecT(const vecT <T> &r);			// ����������� �����
	vecT(const char *a);	// ����������� ��� �����

	~vecT(){delete [] x;}				// ����������

	// ������ ��������� ������

	void addmem(int n);			// �������� ������������� ������ �� 'n' ���������. ���������� ������ �����������
	void addmem();				// �������� ������������� ������ �� 'dN' ���������. ���������� ������ �����������
	void setmem(int n);			// �������� ������ �� 'n' ���������. ���������� ������ ����������
	void setmem();				// �������� ������ �� 'dN' ���������. ���������� ������ ����������

	void setlen(int n);			// �������� ������ �� 'n' ��������� � ���������� ����� ������ N. ���������� ������ ����������
	void fsetlen(int n);			// �������� ������ �� 'n' ���������, ���� �����, � ���������� ����� ������ n.
	inline void zero(); // �������� ��� ��������(���������� ������ ���� ���������)

	void setValue(const T &y, int pos);  // ���������� �������� y �� ������� pos

	// ������ ��������
	void add(const T &y);				// �������� ���� ������� � ����� �������
	void add(const T &y, int pos);	// ��������� ���� ������� � ������ �� ������� 'pos'
	void add(const vecT<T> &y);		// �������� ������ ������ � ����� ������� �������
	void add(const vecT<T> &y,int &pos);		// �������� ������ ������ � ������ ������ � ������� 'pos'
	void add(const T* y, const int n);	// �������� � ����� ������ �� 'n' ��������� �� ��������� 'y'.
	void add(const char* y);	// �������� � ����� ������ �� 'n' ��������� �� ��������� 'y'.
	//void adt(T &a,T &b);	// �������� ��� �������� � �����
	void pst(const vecT<T> &y);	// �������� ������� ������ �� ������ 'y' (� ��������� �������)
	void swp(vecT<T> &y);	// �������� ���� � ������ ������� ������ � ������ 'y'
	void pad(vecT<T> &y);		// �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� 
	void pad(T &y);		// �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� 
	void adp(T &y);
//	void pad(T &y);		// �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� ����� ���� ���������
	//template <class W>
	//void pad(vecT<T> &y); // �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� �������� �������� ���� msT<T>
	void adz(); // �������� ������� ������� � ����� �������

	void rem();				// ������� ��������� �������.
	void rem(int y);		// ������� 'y' ��������� ���������.
	void rem(int y, int pos);	// ������� 'y' ��������� ������� � ������� 'pos'.


	vecT<T>	&	ind(vecT<int> &in, vecT<T> &a);	// ������ � ������ 'a' ��������� �������� ������� � ��������� �� ������� 'in'.
	vecT<T>	&	its(vecT<T> & a, vecT<T> & b);	// ���������� ����������� �������� ������� � ������� 'a'.
	vecT<T>	&	itss(vecT<T> & a,vecT<T> & b);	// ���������� ����������� �������� ������� � ������� 'a'. ���������������� ����� ��� ��������������� ��������.
	void		itssi(vecT<T> & a,vecT<vec2int> &id);	// ���������� ������� ����������� �������� ������� � ������� 'a'. ���������������� ����� ��� ��������������� ��������.
	void		itssi_(vecT<T> & a,vecT<vec2int> &id);	// ���������� itssi(), �� ��� �������� ����� � ���. ������� ������� ������������� ��������
	vecT<T>	&	uni(vecT<T> & a, vecT<T> & b);	// ���������� � b ����������� �������� ������� � ������� 'a'.
	vecT<T>	&	unis(vecT<T> & a,vecT<T> & b);	// ���������� � b ����������� �������� ������� � ������� 'a'. ���������������� ����� ��� ��������������� ��������.
	void		unisi(vecT<T> & a,vecT<T> &b,vecT<int> &id);	// ���������� ������� ����������� �������� ������� � ������� 'a'. ���������������� ����� ��� ��������������� ��������.
	vecT<int> &	fnd(vecT<int> &in,T a);			// ������� ������ ��������� ������� ������ 'a'.
	vecT<int> &	fnd(vecT<bool> &in,vecT<int> &a);// ������� ������ ������� ��������� ������� 'in' � �������� �� � 'a'.
	void fnd(vecT<bool> &in,vecT<int> &a,vecT<int> &b);// ������� ������ ������� ��������� ������� 'in' � �������� �� � 'a'
														// , � ������ ������ - � 'b'.

	int			fnd(const T &a,const T &b);	// ���������� ������ ����� ������� ������� �� ����� 'a' � �� ����� 'b'.
	int			fnd(const T &a);		// ������� ����� ������� �������� � ������� �������, ������� ����� 'a'

	int			fmr(const T &a);	//������� ������ �������� ������� ������ 'a'
	int			fmre(const T &a);	//������� ������ �������� ������� ������ ���� ����� 'a'

	int			fmr(const T &a, int beg);	//������� ������ �������� ������� ������ 'a', ������� ����� � ������  beg
	int			fmre(const T &a, int beg);	//������� ������ �������� ������� ������ ���� ����� 'a', ������� ����� � ������  beg

	int idscheck();	// ���������� ����� ���������� ��������� � �� ��������� ���

	void sort();					// ���������� �������. (����� ��������)
	void sort(vecT<T> &a);			// �??�??�??�??�?? �??�??�??�??�??�??�??�??�??�??'a'.
	void sort(vecT<T> &a, vecT<int> &j);// �??�??�??�??�?? �??�??�??�??�??�??�??�??�??�??'a', �??'j' - �??�??�?? �??�??�??�??�?? 'a'.
	void sort_(vecT<int> &j);	// ���������� �������. � 'j' - ������� ������������

	void qsort(); // ������� ���������� (����������� ����� �������)
	
	void setbindec(int n);	// ��������� ������� ������ ������� 2^k ����� ������� ��� ������� ����� n

	inline T & operator [](const int &i) {return x[i];}	// ���������� ��������� ����������

	inline T & last(){return x[N-1];}

	void setempty() { delete[] x; N = mN = 0; x = 0x0; } // ���������� ������� ������  

	T scpr(vecT<T> &r); // ��������� ������������ �������� ������� �� ������ r
	T ssqr(){T a=0; for(int i=0;i<N;++i) a+=x[i]*x[i]; return a;}	// ������� ����� ������� � ���������� �������
	T snrm(){T a=0; for(int i=0;i<N;++i) a+=x[i]*x[i]; return (a/N);}	// ������� ����� ������� � ���������� �������
	T sum() { T a = 0; for (int i = 0; i<N; ++i) a += x[i] ; return a; }

	T shft_crl(vecT<T> &r, int dn); // ������ �������� ������� � �������� r ��������� ��������� �� dn ������� ������  sum(x[ii]*r.x[ii-dn]) 
	int max_crl_shft(vecT<T> &r, int gs);  // ����������� ���������� ������ ������� r � ������ ���������� ����������, � ��������� �������������� gs 
	void cycle_shift(vecT<T> &r, int dn); //  ����������� ����� �������� ������� �� dn ��������� ������, ��������� � r; r(ii) = x(ii-dn)

	vecT<T> & vec_abs() { for (int i = 0; i < N; i++) x[i] = abs(x[i]); return *this; } // ������

	T max(){T d = x[0]; for(int i=0;i<N;i++) d = d<x[i] ? x[i] : d; return d;}
	T min(){T d = x[0]; for(int i=0;i<N;i++) d = d>x[i] ? x[i] : d; return d;}

	T max(int &id) { id = 0; T d = x[0]; for (int i = 0; i < N; i++) if (d < x[i]) { d = x[i]; id = i; }  return d; }
	T min(int &id) { id = 0; T d = x[0]; for (int i = 0; i < N; i++) if (d > x[i]) { d = x[i]; id = i; }  return d; }

	void var1D(const T &xbeg,const T &dx,const T &xend);	// ��������� �������� �� xbeg ��  xend  � ����� dx
	void var1D_(const T &xbeg, const T &dx, const int &N1); // ��������� �������� �� xbeg � ����� dx �� NN ���������

	void interp1(const vecT<T>& x_in, const vecT<T>& y_in, const vecT<T>& x_out); // �������� ������������ ����������� y_in(x_in) �� ��������� �������� x_out  ��������� � ������� ������  x_in � x_out - ������ ���� �������������
	void Lanczos_interp( const vecT<T>&y_in, int n_, int a_); // ������������ �� ����� � n ��� ���� ��������� ������� ������� a; ��������� � ������� ������; �������������� ����������� ����� ���������� ��� y_in
	void Lanczos_interp(const vecT<T>&y_in, int n_, int a_,const vecT<T> &x0, const vecT<T> &L0); // ������������ �� ����� � n ��� ���� ��������� ������� ������� a; ��������� � ������� ������; �������������� ����������� ����� ���������� ��� y_in


	T ModeLevel(int Nres); // - �������� � ���������� �������������, Nres - ���������� ���������� ��������� ��� ���������� �����������  
	void StatDistr(int Nres, T & mode, T & sigma); // ����������� ��������� ������������� mode � �������� sigma

		// ���������� ����������
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


	vecT<T> &	diff() { T *xx; xx = x; for (int i = 1; i < N; i++)  {*xx -= x[i];	*xx = -*xx;	xx++;} 	N--; return *this; } // ��������� ����������������� � ����������� ������� ������� �� �������

	// ���. ������� - ����������� ��� ������ �������� �����������
	void plus(vecT<T> &a,vecT<T> &b); // x = a+b, ��� x - ���. ������ 
	void minus(vecT<T> &a,vecT<T> &b);// x = a-b, ��� x - ���. ������ 
	void prod(vecT<T> &a,vecT<T> &b); // x = a*b, ��� x - ���. ������ 
	void divd(vecT<T> &a,vecT<T> &b); // x = a/b, ��� x - ���. ������ 
	void plus(T &a,vecT<T> &b); // x = a+b, ��� x - ���. ������ 
	void minus(T &a,vecT<T> &b);// x = a-b, ��� x - ���. ������ 
	void prod(T &a,vecT<T> &b); // x = a*b, ��� x - ���. ������ 
	void divd(T &a,vecT<T> &b); // x = a/b, ��� x - ���. ������ 

	template <class W>
	friend void showfull (vecT<W> &a);

	template <class W>	friend std::istream & operator >>(std::istream &stream,const vecT<W> &a);
	template <class W>	friend std::ostream & operator << (std::ostream &stream,const vecT<W> &a);

	vecT<T> & sinc(vecT<T> &x_in);  // ���������� sinc(x) ��� ��������� �������� �������, ��������� �  ������� �����
	vecT<T> & lncz(vecT<T> &x_in, int a);  // ���������� sinc(x)*sinc(x/a) ��� ��������� �������� �������, ��������� �  ������� �����
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
	//static bool dlt;	// ������������� ��������

	msT();
	msT(int n);			// ������ ��������� ������ �� 'n' ���������.
	msT(const T *a,int n);	// ����������� �������� ����������
	msT(const T *a,int n,int m);		// ����������� ����������� ��������� ������
	msT(const msT <T> &r);			// ����������� �����
	msT(const vecT <T> &r);			// ����������� �����

	void pad(msT<T> &y);		// �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� 
	void pad(T &y);		// �������� ������ ������ � ����� ������� ������� � ������ ���� ������� ������� 

	~msT()
	{
		if (dlt)
		{
			delete [] x;
		}
	}				// ����������
};
/**/
/*
template<class T>
class sparse
{public :
	vecT<vecT<T> > S;
	int nx,ny;

	sparse() {};	// �� ���������	
	sparse(int n,int m);	// 
	sparse(sparse<T> & r);	// ����������� �����
};

/**/
template<class T>
class sparse
{public :
	vecT<T>	S;		// ������ ��� �������� ���������� ���������
	vecT<int> I;	// ������ ��� �������� ������� ������� ��������� ���������
	vecT<int> J;	// ������ � �������� ������ ��������� ��������� � ������
	int nx,ny;		// ������� �������

	sparse() {nx=ny=0;};	// �� ���������	
	sparse(sparse<T> & cpspr);	// ����������� �����

	void init(int n, int nz); // ������������� ������� n_x_n  c nz ���������� ����������.

	T get(const int my,const int mx); // ������ � �������� A(my,mx);
	T & set(const int my,const int mx); // ������ � �������� A(my,mx);
	T & fst(const int my,const int mx); // ������� ������ � �������� A(my,mx) ��� ��������� � �������� ������������� ��������

	void tns();	// ���������������� �������
	vecT<T> & pmv_f(vecT<T> &a, vecT<T> &b); // ��������� ����������� ������� �� ������ 'a' ��������� � 'b' (���������� �����)
	vecT<T> & pmv(vecT<T> &a, vecT<T> &b); // ��������� ����������� ������� �� ������ 'a' ��������� � 'b'
private:
	T& addpos(const int my,const int mx,const int i);	// ������������� ������ �������� �� ������� mx, � ������� i � ������� S (������������ � set)

};/**/

template<class T> class FullMatrix;

// ������ ���������� ����������� �������
template<class T>
class SparseMatr
{public :
	vecT<vecT<T> >	 S;	// ������ �������
	vecT<vecT<int> > I;	// ������� ��������
	int nx,ny;	// ������� �������

	SparseMatr() {nx=ny=0;};	// �� ���������	
	SparseMatr(SparseMatr<T> & r);	// ����������� �����
	~SparseMatr(){}

	void setSize(const int my,const int mx);	// ��������� �������� �������

	void reSize(const int my,const int mx);	// ��������� ����� �������� ������� � ����������� ������.

	void setCopy(SparseMatr<T> & r);
	void setCopy(FullMatrix<T> & r);
	template<class W>
	void setCopyW(SparseMatr<W> & r);

	void setSignature(vecT<vecint> & id); // ��������� ��������� ��������� ��������� ������� - ����������� ��������� ������. � id - ������� ��������� ���������
		
	T get(const int my,const int mx); // ������ � �������� A(my,mx);
	T & set(const int my,const int mx); // ������ � �������� A(my,mx);
	T & fst(const int my,const int mx); // ������� ������ � �������� A(my,mx) ��� ��������� � �������� ������������� ��������

	void swp(SparseMatr<T> & r);	// ���� ������ � �������� r

	void del(const int my,const int mx); // ������� (��������� �������� 0) ������� A(my,mx)
	void delsym(const int my); // ������� ������ � ������� my � ������������ ��������� ������ �� ����� 'my' (�������� ��� ������������ �������)

	void symswp(const int my);	// �������� ������� ������ � ������� my � ��������� ������� � �������� (�������� ��� ������������ �������)
	void ColumnSwap(const int &id1,const int &id2); // �������� ������� 2 �������
	void RowSwap(const int &id1,const int &id2){if((id1>=0)&&(id2>=0)&&(id1<ny)&&(id2<ny)){S.x[id1].swp(S.x[id2]);I.x[id1].swp(I.x[id2]);}}

	vecT<T> getdiag();	// ���������� ��������� �������

	void tns();	// ���������������� �������

	void GetNormMatrix(SparseMatr<T> & R); // ���������� � R=A*A`,A- ���. �������, A`- ����������������� A

	void Householder(vecT<T> & u, int &is, const int ic);	// ���������� ������� �����������
	void qrIrtUpd(SparseMatr<T> &Q, vecT<T> &u,int &is, const int ic); // ���������� ������� �� ���� ��� �������� ��������� �����������
	void QR(SparseMatr<T> &Q); // QR - ����������
	void QR_MatrPrepating(SparseMatr<T> &R); // ����������� ������� ������� � R, R-����� ��������� ������������ �������� ����������������� �������. 
	void QR_solver(vecT<T> &b,vecT<T> &z); // ������� ���� � ������� �������� � ������� QR-����������

	void SetOrthoBasis(vecT<T> &u); // ���������� � ������� ������� ������-������� �������������� ������ �������������� ��������� ������� u.
	void OrthoBin(int &jj,int &ii,int &n,vecT<T> &u, vecT<T> &y, double &a);	// �������� ������� �������� ���������������

	 vecT<T> & getrow(int ir,vecT<T> &u); // ������ � u ������ � ������� ir;


	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // ��������� ����������� ������� �� ������ 'a' ��������� � 'b'

	vecT<T> CG_solve(vecT<T> &b);	// ������� ������� �������� ��������� Ax=b, ��� A- ������� ����������� ������� (���������� ���������)
	vecT<T> CGNORM_solve(vecT<T> &b);	// ������� ������� �������� ��������� Ax=b, ��� A- ������� ����������� ������� (���������� ��������� � ��������������� ���������)
	vecT<T> CGNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// ������� ������� �������� ��������� Ax=b, ��� A- ������� ����������� ������� (���������� ��������� � ��������������� ���������)
	vecT<T> CGMNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// ������� ������� �������� ��������� Ax=b, ��� A- ������� ����������� ������� (���������� ��������� � ��������������� ���������)
	vecT<T> StCGNORM2_solve(vecT<T> &b,T rmin = 1e-16);	// ������� ������� �������� ��������� Ax=b, ��� A- ������� ����������� ������� (���������� ��������� � ��������������� ���������)


	void interp_dstrb(vecT<T> &X, vecT<T> &Z); // ���������� ������� M ��� ������������ ������� �������������  Y(�) �� ������� ����������� Z; F(Z)= M*Y(X) 

	void memory_compress(); // ��������� ������ ����� �������� ������ - ��� ����� �������� ������� ������


	SparseMatr<T> &	operator = (SparseMatr<T> &a) {setCopy(a);return *this;}
	//SparseMatr<T>	operator + (SparseMatr<T> &a);
	//SparseMatr<T>	operator - (SparseMatr<T> &a);
	SparseMatr<T>	operator * (SparseMatr<T> &a);
	//SparseMatr<T>	operator + (SparseMatr<T> &a);

	void UniMatr(SparseMatr<T> &r);	 // ����������� ���� ������ � ������� �������. ������� r ����������� �� ��������� ����� ������.

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
	//vecT<T* > S;	//	������ ����������
	vecT<T*>	x; 	//	������ ���������� �� ������ ������ ������
	vecT<T>		s;  // ������ ������
	int nx,ny;	// ����� �������� � �����

	FullMatrix() {x=0x0; nx=ny=0;}	// �� ���������	
	FullMatrix(const int my,const int mx) {setSize(my, mx);}
	FullMatrix(FullMatrix<T> & r);	// ����������� �����
	~FullMatrix(){}

	void ConnectPointer(){x.x[0]=s.x;for(int i=1;i<ny;i++)	{x.x[i]	= x.x[i-1]+nx;}}	// �������� ���������

	void setSize(const int my,const int mx);	// ��������� �������� �������
	void setEye(const int m); // ��������� ���������� ��������� �������

	void setCopy(const FullMatrix<T> & r);
	void setCopy(const SparseMatr<T> & r);

	inline T get(const int my,const int mx){return (my<ny)&&(mx<nx) ? x.x[my][mx] : 0 ;} // ������ � �������� A(my,mx);
	inline T & fst(const int my,const int mx){return x.x[my][mx];} // ������ � �������� A(my,mx);
	T & set(const int my,const int mx); // ������ � �������� A(my,mx);

	vecT<T> getdiag();	// ���������� ��������� �������


/*	void addRow(); // �������� ������ � �����
	void addRow(int ps); // �������� ������ �� ������� ps �� ������� ��������� ����� ����
	void remRow(); // ������� ��������� ������
	void remRow(int ps); // ������� ������ � ������� ps

	void addColumn(); // �������� ������� � ����� �������
	void addColumn(int ps); // �������� ������� �� ������� ps 
	void remColumn(); // ������� ��������� �������
	void remColumn(int ps); // ������� ������� � ������� ps
	*/

	void tns();	// ���������������� �������
	void getSub(FullMatrix<T> &R,const int ibeg,const int iend,const int jbeg,const int jend);
	template<class W>
	void getSub_(FullMatrix<W> &R, const int ibeg, const int iend, const int jbeg, const int jend);
	//void getSub(FullMatrix<T> &R,const int ibeg,const int ni, const int di,const int jbeg,const int nj,const int dj);
	void Shift(); // ���������� ���� ������� � �����, � ����� �� ����

	void getRow(int nrow,vecT<T> &V); // ������� � V ������ �������� ������ � ������� nrow (! V.x ������ ���� ����� 0!!!)


	void GetNormMatrix(FullMatrix<T> & R); // ���������� � R=A*A`,A- ���. �������, A`- ����������������� A

	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // ��������� ������� �� ������ 'a' ��������� � 'b'

	void sumRow(vecT<T> &a); // ���������� � 'a' ����� �� ������� (������������ ����� �������)
	void sumCol(vecT<T> &a); // ���������� � 'a' ����� �� �������� (������������ ����� �����)

	bool SymmTest();	// ���� �� �������������� �������

	void selfsubprod(const FullMatrix<T> &P,const int ibeg,const int iend,const int jbeg,const int jend, bool flag =false); // ��������� ����������� ������� �� ������ 'a' ��������� � 'b'
	void selfsubprod( vecT<T> &u,const int ic); // ��������� ����������� ������� �� ������ 'a' ��������� � 'b'

	void Householder(vecT<T> & u, const int ibeg,const int iend, const int j);	// ���������� ������� ����������� �� �������
	void HouseholderSymm(vecT<T> & u, const int ibeg,const int iend, const int j);	// ���������� ������� ����������� �� ������
	void Householder(vecT<T> & u, const int ic);	// ���������� ������� ����������� �� ������

	void setHouse(vecT<T> & u);	//	���������� ������� ��������� �� ������� 'u';

	void HessenbergItr(FullMatrix<T> &P,const int ic);	//	�������� ���������� ���. ������� � ����� ����������
	void HessenbergItr(vecT<T> & u,const int ic);	//	�������� ���������� ���. ������� � ����� ����������

	void HessenbergItrSymm(vecT<T> &u,const int ic);	//	�������� ���������� ���. ������� � ����� ���������� (������� ��� ������������ �������)

	void HessenbergForm();	// ���������� ���. ������� � ����� ����������
	void HessenbergForm(FullMatrix<T> &Q);	// ���������� ���. ������� � ����� ���������� � ������� ������� �������� Q

	void QR(vecT<T> &b); // QR - ����������, ����� ��� ���������� � ������� ���� b - ������ ������ ����� ���� ������������� � ������ Q'*b 
	void QR(vecT<vecT<T> > &P); // QR - ����������, � P - ��������������� ������������ �������, � ������ ������� -  ���������� R
	void qrIrtUpd( vecT<T> &u,const int ic); // ��� qr - ��������, 
	void qrIrtUpd(vecT<vecT<T> > &P, vecT<T> &u, const int ic); //  ��� qr - ��������, 
	void QR_solver(vecT<T> &b,vecT<T> &z); // ������� ���� � ������� �������� � ������� QR-����������
	void getQformP(FullMatrix<T> &Q,vecT<vecT<T> > &P); // ���������� ������� Q �� � ��������������� ������������� � ���� ������ �������� � P



	vecT<T> CG_solve(vecT<T> &b);// ������� ������� �������� ��������� Ax=b, ��� A- ������� ������� (���������� ���������)
	vecT<T> & CG_solve(vecT<T> &xk, vecT<T> &b);// ������� ������� �������� ��������� Ax=b, ��� A- ������� ������� (���������� ���������)

	FullMatrix<T> &	operator = (const FullMatrix<T> &a) {setCopy(a);return *this;}
	//FullMatrix<T>	operator + (FullMatrix<T> &a);
	//FullMatrix<T>	operator - (FullMatrix<T> &a);
	FullMatrix<T>	operator * (const FullMatrix<T> &a);
	//FullMatrix<T>	operator + (FullMatrix<T> &a);

	void swp(FullMatrix<T> &r);	// ���� � �������� r

	vecT<T>	operator * (vecT<T> &a);	// ��������� �� ������;

	vec3T<T>	operator * (vec3T<T> &a);	// ��������� �� ������;


	void FullCorrelation(FullMatrix<T> & C); // ���������� � C ������� ���������� ������� ������� 
	void FullCorrelationInt(FullMatrix<T> & C); // ���������� � C ������� ���������� ������� ������� 
	void PartCorrelation(FullMatrix<T> & C,int dny,int dnx); // ���������� � C ������� ���������� ������� �������. ������ ������� �������� - (0:dnx,0:dny)

	T Det(); // ���������� ����������� ������� ����������� ����������  (�� ��������� ��� ������� ������� ����� ��� 11);
	T hdet(int iy, int ix,vecT<bool> &frbd); // ���������� ���������� ������� ��� ���������� ������������

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
class TriDiag	// ����� ��������������� �������
{
public:
	int n;	// ������ ������� nxn
	vecT<T> D;	// ������� ���������
	vecT<T> L;	// ������ ���������
	vecT<T> U;	// ������� ���������

	TriDiag(){n=0;}
	TriDiag(TriDiag<T> & r);// r����������� �����
	~TriDiag(){}

	void setSize(const int i){n=i; D.setlen(n);L.setlen(n-1);U.setlen(n-1);}
	void setCopy(FullMatrix<T> &r);	// ������� �� 3 ���������� ������� ������� r
	void setCopy(SparseMatr<T> &r);	// ������� �� 3 ���������� ����������� ������� r

	vecT<T> & pmv(const vecT<T> &a, vecT<T> &b); // ��������� ������� �� ������ 'a' ��������� � 'b'

	void getsub(TriDiag<T> &Tr,const int & ibeg,const int & iend);	// ������ ����� ��������������� ������� � � �� (ibeg:iend,ibeg:iend)
	void separation(TriDiag<T> &T1, TriDiag<T> &T2, const int & nsep); // ��������� �������� ������� �� ���, � ������� - ������������ nsep

	//void DC_eig(FullMatrix<T> &Q, vecT<T> &D);	// ������� ������ �� ���������� �������� ������� "�������� � ��������"
	void DC_eig(TriDiag<T> &Tr, SparseMatr<T> &Q, vecT<T> &D);	// ������� ������ �� ���������� �������� ������� "�������� � ��������"

	T get(const int iy, const int ix);	// ������� �������� �������� ��������������� �������

	void showfull_infile (const char *fname);
};

template<class T>
class Quaternion
{
public :
	T x[4];	// ��������� �����������

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

	inline Quaternion<T> conj(){Quaternion<T> v; v.x[0]=x[0];v.x[1]=-x[1];v.x[2]=-x[2]; v.x[3]=-x[3];return v; }	// ���������� ��������� ���������
	inline Quaternion<T> & conjugate(){x[1]=-x[1];x[2]=-x[2];x[3]=-x[3]; return *this;} // ���������� �������� �����������

	inline T norm(){ return (x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]);}	// ����� �����������
	inline T nmml(){T nr =sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]+x[3]*x[3]); x[0]/=nr;x[1]/=nr;x[2]/=nr;x[3]/=nr; return nr; }

	inline Quaternion<T> & invs(){T nr=(*this).norm(); x[0]/=nr x[1]/=-nr;x[2]/=-nr;x[3]/=-nr; return *this;}
	inline Quaternion<T>  inv(){T nr=(*this).norm(); Quaternion<T> v; v.x[0]=x[0]/nr;v.x[1]=-x[1]/nr;v.x[2]=-x[2]/nr;v.x[3]=-x[3]/nr; return v;}

	inline Quaternion<T> operator / (const Quaternion<T> & r);//{ T nr=r.norm();Quaternion<T> v(r); v.x[0]/=nr; v.x[1]/=-nr; v.x[2]/=-nr; v.x[3]/=-nr;  return (*this)*=r; }
	inline Quaternion<T> & operator /= (const Quaternion<T> & r);//{ x[0]/=r.x[0];x[1]/=r.x[1];x[2]/=r.x[2]; return *this; }


	vecT<T> rotat();	// ��������� ���� �������� � ����������� ��� �������� ������������� �������������� ����������� (������ ��� ����������� ������������) 

	void rotation(vecT<T> &r);	// ���������� ������� ������� r ������ ��� ����������� �� ���� ������������� ������������

	Quaternion<T> & rotat(double &fi,vec3T<T> &r); // ���������� ���������� ����������� ��� �������� �������� ������ ��� r �� ���� fi

	FullMatrix<T> qua2matrA();	// ��������� ���������� ������������� � ���� A-�������
	FullMatrix<T> qua2matrB();	// ��������� ���������� ������������� � ���� B-�������

	FullMatrix<T> qua2matrR();	// ��������� ���������� ������������� � ���� ������� 3D ��������

	void clear(){memset(x,0x0,4*sizeof(T));}
	void zerospin(){memset(x,0x0,4*sizeof(T));x[0]=1.0;}


};

#include "linalg.cpp"

#endif