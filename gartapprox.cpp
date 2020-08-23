#ifndef GARTAPPROX_CPP
#define GARTAPPROX_CPP

#include <QMessageBox>
#include "gartapprox.h"
//#include "linalg.cpp"
#include "linalg.h"

GartmanApproximator::GartmanApproximator()
{
	P.setlen(dim);
	S.setlen(dim);
	S_.setlen(dim);
	R.setlen(dim);
	R_.setlen(dim);
	X.setlen(dim);
	X_.setlen(dim);

	Grd.setlen(dim);
	H.setSize(dim, dim);

	grad_data.setlen(dim);

	usr_eps = 1e-10; // устанавливаемая пользователем невязка 
	usr_Nittr = 100; // устанавливаемое пользователем максимальное число иттераций

	//AF = &LorentsApproximator::Fun;
	//	hess_data.setSize(dim,dim);
}


void GartmanApproximator::setdata(vecdb & x_in, vecdb & y_in)
{
	double mx, mn;// , yn, yx;

	x.fsetlen(x_in.N);
	y.fsetlen(y_in.N);
	f.fsetlen(x_in.N);

	mx = x_in.max();
	mn = x_in.min();

	kx = 1. / (mx - mn);
	bx = mn / (mn - mx);

	mx = y_in.max();
	mn = y_in.min();

	ky = 1. / (mx - mn);
	by = mn / (mn - mx);

	x = x_in;

	x *= kx;
	x += bx;

	y = y_in;
	y *= ky;
	y += by;

	for (int ii = 0; ii<dim; ii++)
	{
		grad_data.x[ii].fsetlen(x.N);
	}

	hess_data_11.fsetlen(x.N);
	hess_data_13.fsetlen(x.N);

	hexp.fsetlen(x.N);
	hf1.fsetlen(x.N);
	hf2.fsetlen(x.N);
	sqhexp.fsetlen(x.N);
}

void GartmanApproximator::fitfun(vecdb & Xk)
{
	for (int ii = 0; ii < x.N; ii++)
	{
		hexp.x[ii] = 1.0 / (x.x[ii] - Xk.x[0]);  // 1/(x-A);
	}
	for (int ii = 0; ii < x.N; ii++)
	{
		f.x[ii] = Xk.x[1] + Xk.x[2] * hexp.x[ii];  // B + C/(x-A);
	}
}

void GartmanApproximator::ErrFun(vecdb & Xk)
{
	fitfun(Xk);
	dfy = f;
	dfy -= y;
	err = dfy.ssqr() / dfy.N;
}

void GartmanApproximator::gradFun(vecdb & Xk)
{
	ErrFun(Xk);

	sqhexp *= sqhexp = hexp;

	grad_data.x[0] = Xk.x[2] * sqhexp;
	grad_data.x[1] = 1.0;
	grad_data.x[2] = hexp;
}

void GartmanApproximator::GradErr(vecdb & Xk)
{
	gradFun(Xk);

	Grd.x[0] = 2 * dfy.scpr(grad_data.x[0]) / x.N;  
	Grd.x[1] = 2 * dfy.sum() / x.N;// явно учтено, что grad_data.x[1] = 1;
	Grd.x[2] = 2 * dfy.scpr(hexp) / x.N;// явно учтёно, что  grad_data.x[0] = hexp
}

void GartmanApproximator::hessFun(vecdb & Xk)
{
	hess_data_11 = sqhexp; // вторые производные данных
	hess_data_11 *= hexp;
	hess_data_11 *= 2.0*Xk.x[2];

	hess_data_13 = hexp;
}

void GartmanApproximator::HessErr(vecdb & Xk)
{
	GradErr(Xk);
	hessFun(Xk);

	H.fst(0, 0) = 2 * (grad_data.x[0].ssqr() + dfy.scpr(hess_data_11)) / x.N;
	H.fst(1, 0) = H.fst(0, 1) = 2 * (grad_data.x[0].sum()) / x.N;// явно учтёно, что hess_data_12 = 0 и grad_data.x[1] = 1.0;
	H.fst(2, 0) = H.fst(0, 2) = 2 * (grad_data.x[0].scpr(grad_data.x[2]) + dfy.scpr(hess_data_13)) / x.N;

	H.fst(1, 1) = 2.0;// явно учтёно, что hess_data_22 = 0  и grad_data.x[1] = 1.0;
	H.fst(2, 1) = H.fst(1, 2) = 2 * (grad_data.x[2].sum() ) / x.N;// явно учтёно, что hess_data_23 = 0 и  grad_data.x[1] = 1.0;

	H.fst(2, 2) = 2 * (grad_data.x[2].ssqr()) / x.N;// явно учтёно, что hess_data_33 = 0 
}


void GartmanApproximator::initguess()//vecdb & Xk)
{
	FullMatrix<double> M;
	M.setSize(3, 3);
	// начальное приближение определяется по методу наименьших квадраторв для зависимости вида Npix(lmbd-B) = A*lmbd+C, который сводится к решению СЛАУ
	
	// матрица "средних"
	M.fst(0, 0) = x.ssqr() / x.N;
	M.fst(0, 1) = M.fst(1, 0) = x.scpr(y) / x.N;
	M.fst(0, 2) = M.fst(2, 0) = x.sum() / x.N;

	M.fst(1, 1) = y.ssqr() / x.N;
	M.fst(1, 2) = M.fst(2, 1) = y.sum() / x.N;

	M.fst(2, 2) = 1.0;

	// Вектор "проекций" экспериментальных значений
	f.pst(x);
	f *= f;
	X.x[0] = f.scpr(y) / x.N;
	f.pst(y);
	f *= f;
	X.x[1] = f.scpr(x) / x.N;
	X.x[2] = y.scpr(x) / x.N;

	M.CG_solve(X_, X); // решение СЛАУ методом сопряжённых градиентов
	
	// переход в "координаты" принятые в основном алгоритме аппроксимации
	X.x[0] = X_.x[1];
	X.x[1] = X_.x[0];
	X.x[2] = X_.x[2]+X_.x[0]*X_.x[1];
}

void GartmanApproximator::MinErrFind()
{
	double  eps;//lmb, wk,
	initguess();// X); в X помещется начальное приближение
	
	vecT<double> xx, yy;
	xx.var1D(-1.0, 0.03, 1.0);
	yy.fsetlen(xx.N);

	int kk, in;
	kk = 0;
	eps = 1;

	while ((eps > usr_eps)&(kk<usr_Nittr))
	{
		HessErr(X);  // вычисление первых и вторых производных
					 //H2 = H;
		R = -Grd;
		eps = R.snrm();
		H.CG_solve(S, R);// S = H\R
		for (int jj = 0; jj < xx.N; jj++)
		{
			X_ = X + S*xx.x[jj];
			ErrFun(X_);
			yy.x[jj] = err;
		}
		yy.min(in);

		S *= xx.x[in];
		X += S;
		kk++;
	}
	if (kk < usr_Nittr)
	{
		P = X; // 
		Finalize();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("\320\222\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\320\265\040\320\277\321\200\320\276\320\262\320\265\321\201\321\202\320\270\040\320\275\320\265\040\321\203\320\264\320\260\320\273\320\276\321\201\321\214\056\040\320\237\321\200\320\276\320\262\320\265\321\200\321\214\321\202\320\265\040\320\264\320\260\320\275\320\275\321\213\320\265\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\320\276\320\271\040\321\202\320\260\320\261\320\273\320\270\321\206\321\213\056");
		msgBox.exec();
		P = X; // 
		Finalize();
	}
}

void GartmanApproximator::Finalize()
{
	ErrFun(P);
	X_.x[0] = sqrt(2 * err / H.fst(0, 0));
	X_.x[1] = sqrt(2 * err / H.fst(1, 1));
	X_.x[2] = sqrt(2 * err / H.fst(2, 2));

	// возвращение к исходному масштабу
	X.x[0] = (P.x[0] - bx) / kx;
	X.x[1] = (P.x[1] - by) / ky;
	X.x[2] = P.x[2] / (kx*ky);

	X_.x[0] = X_.x[0] / kx;
	X_.x[1] = X_.x[1] / kx;
	X_.x[2] = X_.x[2] / (kx*ky);
}


void GartmanApproximator::Fun(vecdb  &xx, vecdb  &yy)
{
	yy.fsetlen(xx.N);
	for (int ii = 0; ii < xx.N; ii++)
	{
		yy.x[ii] = X.x[1] + X.x[2] / (xx.x[ii] - X.x[0]);
	}
}

void GartmanApproximator::InvFun(vecdb & xx, vecdb & yy)
{
	yy.fsetlen(xx.N);
	for (int ii = 0; ii < xx.N; ii++)
	{
		yy.x[ii] = X.x[0] + X.x[2] / (xx.x[ii] - X.x[1]);
	}
}

void GartmanApproximator::dInvFun(vecdb & xx, vecdb & yy)
{
	yy.fsetlen(xx.N);
	for (int ii = 0; ii < xx.N; ii++)
	{
		yy.x[ii] = 1/ (xx.x[ii] - X.x[1]);
		yy.x[ii] *= yy.x[ii];
		yy.x[ii] *= (X.x[2]);
	}
}

void GartmanApproximator::dFun(vecdb & xx, vecdb & yy)
{
	yy.fsetlen(xx.N);
	for (int ii = 0; ii < xx.N; ii++)
	{
		yy.x[ii] = 1 / (xx.x[ii] - X.x[0]);
		yy.x[ii] *= yy.x[ii];
		yy.x[ii] *= (X.x[2]);
	}
}

#endif