
#ifndef INTERPOLATOR_CPP
#define INTERPOLATOR_CPP

#include "interpolator.h"
//#include "linalg.cpp"
#include "linalg.h"








void Interpolator::SetLanczos(int n_, int a_)
{
	n = n_;
	a = a_;
	vecdb x0;
	x0.var1D(double(-a), 1.0 /double(n), double(a));
	lncz(L0,x0, a);  // вычисление контура сплайн-функции соответсвующей фильтру Ћанцоша
}

void Interpolator::SetDblLncz(int n_)
{
	n = n_;
	a = 2;
	vecdb x0;
	x0.var1D(double(-a), 1.0 / double(n), double(a));
	lncz(L1, x0, a);  // вычисление контура сплайн-функции соответсвующей фильтру Ћанцоша
	a = 3;
	x0.var1D(double(-a), 1.0 / double(n), double(a));
	lncz(L0, x0, a);  // вычисление контура сплайн-функции соответсвующей фильтру Ћанцоша
}

void Interpolator::SetLinear(int n_)
{
	n = n_;
	a = 1;
	vecdb x0;
	x0.var1D(double(-a), 1.0 / double(n), double(a));
	x0.x[a*n] = 0.0;
	L0.fsetlen(x0.N);
	for (int ii = 0; ii < x0.N; ii++)
	{
		L0.x[ii] = 1.0-fabs(x0.x[ii]);
	}
}

/*void Interpolator::SetQuadr(int n_)
{
}*/

void Interpolator::SetCubic(int n_)
{
	n = n_;
	a = 2;
	vecdb x0;
	double in6, loc;
	x0.var1D(double(-a), 1.0 / double(n), double(a));
	x0.x[a*n] = 0.0;
	L0.fsetlen(x0.N);
	int ii,jj;
	in6 = 1.0 / 6.0;
	for (ii = 0; ii < n; ii++)
	{
		loc = (x0.x[ii] + 2.0);
		L0.x[ii] = loc*loc*loc*in6;
	}
	jj = a*n;
	for (; ii <= jj; ii++)
	{
		loc = x0.x[ii] + 1.0;
		L0.x[ii] = in6 + 0.5*loc*(1 + loc*(1 - loc));
	}
	for (; ii < x0.N; ii++)
	{
		L0.x[ii] = L0.x[jj - (ii - jj)];
	}
}

void Interpolator::SetTypeInterp(int n_)
{
	switch (type)
	{
	case 0:
	{
		return SetLinear(n_);
		break;
	}
	case 1:
	{
		return SetDblLncz(n_);
		break;
	}
	case 2:
	{
		return  SetCubic(n_);
		break;
	}
	}
}

vecdb & Interpolator::DoInterpolatoin(vecdb & y_out, const vecdb & y_in)
{
	int ii, ie, ib, ilb;
	ii = (y_in.N - 1)*n + 1;
	if (y_out.mN < ii) y_out.setlen(ii); else { y_out.N = ii; y_out.zero(); }

	for (ii = 0; ii < a; ii++)
	{
		ib = 0;
		ie = (ii + a)*n + 1;
		ilb = (a - ii)*n;
		for (int jj = ib; jj < ie; jj++)
		{
			y_out.x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N - a; ii++)
	{
		ib = (ii - a)*n;
		ie = (ii + a)*n + 1;
		ilb = 0;
		for (int jj = ib; jj < ie; jj++)
		{
			y_out.x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	for (; ii < y_in.N; ii++)
	{
		ib = (ii - a)*n;
		ilb = 0;
		for (int jj = ib; jj < y_out.N; jj++)
		{
			y_out.x[jj] += y_in.x[ii] * L0.x[ilb++];
		}
	}
	return y_out;
}

vecdb & Interpolator::DoDoubleLanczos(vecdb & y_out,  vecdb & y_in)
{
	yh0.fsetlen(y_in.N);

	k_lin = (y_in.last() - y_in.x[0])/(n*(y_in.N-1));
	b_lin = y_in.x[0];//y_in.last() - k_lin*(y_in.N - 1);
	//k_lin /= double(n);
	//b_lin += 5000;

	yh0.pst(y_in);

	for (int ii = 0; ii < y_in.N; ii++) { yh0.x[ii] -= k_lin*ii*n + b_lin; }

	Interpolator::DoInterpolatoin(yh3, yh0); // интерпол€ци€ 3-го пор€дка
	L0.swp(L1);
	a = 2;
	Interpolator::DoInterpolatoin(yh2, yh0); // интерпол€ци€ 2-го пор€дка ;
	L0.swp(L1);
	a = 3;
	
	double ft2, ft3,fr2,fi2,fr3,fi3;
	//ft2 = ft3 = fr2 = fi2 = fr3 = fi3 = 0.0;
	fr2 = yh2.scpr(csy);
	fi2 = yh2.scpr(sny);

	fr3 = yh3.scpr(csy);
	fi3 = yh3.scpr(sny);

	ft2 = sqrt(fr2*fr2 + fi2*fi2);
	ft3	= sqrt(fr3*fr3 + fi3*fi3);

	yh2 *= ft3;
	yh3 *= ft2;

	y_out.pst(yh2);
	y_out += yh3;
	y_out *= (1.0 / (ft2 + ft3));

	for (int ii = 0; ii < y_out.N; ii++) { y_out.x[ii] += k_lin*ii + b_lin; }

	return  y_out;
}

vecdb & Interpolator::DoTypeInterp(vecdb & y_out, vecdb & y_in)
{
	switch (type)
	{
		case 0:
		{
			return DoInterpolatoin(y_out, y_in);
			break;
		}
		case 1:
		{
			return DoDoubleLanczos(y_out, y_in);
			break;
		}
		case 2:
		{
			return DoInterpolatoin(y_out, y_in);
			break;
		}
	}
	return y_out;
}

vecdb & Interpolator::sinc(vecdb & y_out, vecdb & x_in)
{
	double loc;
	y_out.fsetlen(x_in.N);
	int idz = x_in.fnd(double(0));
	if (idz == -1)
	{
		for (int ii = 0; ii < y_out.N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
		}
	}
	else
	{
		for (int ii = 0; ii < idz; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
		}
		y_out.x[idz] = 1;
		for (int ii = idz + 1; ii < y_out.N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
		}
	}
	return y_out;
}

vecdb & Interpolator::lncz(vecdb & y_out, vecdb & x_in, int a)
{
	double loc;
	y_out.fsetlen(x_in.N);
	int idz = x_in.fnd(double(0));
	if (idz == -1)
	{
		for (int ii = 0; ii < y_out.N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
			loc /= a;
			y_out.x[ii] *= sin(loc) / loc;
		}
	}
	else
	{
		for (int ii = 0; ii < idz; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
			loc /= a;
			y_out.x[ii] *= sin(loc) / loc;
		}
		y_out.x[idz] = 1;
		for (int ii = idz + 1; ii <y_out.N; ii++)
		{
			loc = x_in.x[ii] * pi_num;
			y_out.x[ii] = sin(loc) / loc;
			loc /= a;
			y_out.x[ii] *= sin(loc) / loc;
		}
	}
	return y_out;
}

void Interpolator::setexp(int y_inN)// vecdb &y_in)
{
	int N = (y_inN - 1)*(n)+1; // полное чило точек в интеполированной кривой (y_out)
	csy.fsetlen(N);
	sny.fsetlen(N);
	double h,hp;
	hp = (2.0*pi_num*y_inN) / double(N);
	for (int ii = 0; ii < N; ii++)
	{
		h = hp*ii;
		csy.x[ii] = cos(h);
		sny.x[ii] = sin(h);
	}
}

void Interpolator::setlin(vecdb & y_in)
{
	k_lin = (y_in.last() - y_in.x[0]) / (n*(y_in.N - 1));
	b_lin = y_in.x[0];//y_in.last() - k_lin*(y_in.N - 1);
}


#endif // !INTERPOLATOR_CPP