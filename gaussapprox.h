#ifndef GAUSSAPPROX_H
#define GAUSSAPPROX_H


#include "linalg.h" 

//const int GaussApproxDim = 5;
//class GaussApproximator;
//typedef void (GaussApproximator::*AprxFun)( vecdb &xx, vecdb &yy);

class GaussApproximator // класс для проведения аппроксимации данных функцией вида y(x) = A*exp(-((x-B)/C)^2)+D*x+E методом наименьших квадратов 
{
public:
	
	GaussApproximator();
	~GaussApproximator() {};

	//AprxFun AF;

	const int dim = 5; // размерность аппроскимации - всего 5 параметров

	double kx, ky, bx, by; // коэффициенты для перевода данных в рабочий диапазон: x -> [-1..1]; y -> [0..1];
	double k_, b_; 
	int sign; // индикатор "перевёрнуного пика" - например как при поглощении
	double usr_eps; // устанавливаемая пользователем невязка 
	int    usr_Nittr; // устанавливаемое пользователем максимальное число иттераций


	vecdb x,y; // данные для аппроксимации
	vecdb f; // аппроксимирующая функция (значния)
	vecdb hexp; // для хранения экспонент
	vecdb hf1, hf2;// вспомогательные массивы для ускорения вычислений
	vecdb dfy; // разница (f-y)

	double err; // ошибка аппроксимации
	vecdb P,S,S_,R,R_,X,X_; // вектора для метода оптимизации
	vecdb Grd; // вектор градиент
	FullMatrix<double> H; // матрица вторых производных
	
	vecT<vecdb>  grad_data; // градиенты данных
	//FullMatrix<vecdb> hess_data; // вторые производные данных	
	vecdb hess_data_12;
	vecdb hess_data_13;
	vecdb hess_data_22;
	vecdb hess_data_23;
	vecdb hess_data_33;

	void setdata(vecdb &x_in, vecdb &y_in); // установка данных для аппроксимации

	void fitfun(vecdb &Xk); // вычисление функции аппроксимации
	void ErrFun(vecdb &Xk); // вычисление ошибки
	void gradFun(vecdb &Xk); // вычисление градиента ошибки
	void hessFun(vecdb &Xk); // вычисление матрицы вторых производных

	void GradErr(vecdb &Xk);
	void HessErr(vecdb &Xk);

	void initguess(vecdb &Xk); // начальное приближение - по ценрту масс

	void MinErrFind(); // процедура определения параметров минимизирующих ошибку аппроксимации

	void Finalize(); // возращение к исходному масштабу, вычисление доверитенльных интервалов 

	void Fun(vecdb &xx, vecdb &yy); // вычисление аппроксимирующей функции по аргументам xx результат - в yy (по параметрам из X)

//	AprxFun retptr() { return this->*Fun; }

};

#endif
