//#pragma once
#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H


#include "linalg.h"

class Interpolator
{
public:
	Interpolator() { n = 0; a = 0; type = 0; };
	~Interpolator() {};

	void SetLanczos(int n_, int a_); // настройть интерполятор Ланцоша порядка a_ для кратности секти n_ 
	void SetDblLncz(int n_); // настройть двойной интерполятор Ланцоша порядка 2 и 3 для кратности секти n_ 
	void SetLinear(int n_); // настроить линейный интерполятор 
	//void SetQuadr(int n_); //  настроить квадратичный интеполятор
	void SetCubic(int n_); //  настроить кубический интеполятор
	void SetTypeInterp(int n_); // настроить интерполятор по типу type


	vecdb & DoInterpolatoin(vecdb &y_out, const vecdb &y_in); // интерполяция данных y_in на сетку в n раз гуще выбранныной моделью интерполяции сплайнами порядка a; результат в массив y_out; предполагается равномерная сетка аргументов для y_in
	vecdb & DoDoubleLanczos(vecdb &y_out, vecdb &y_in); // двойная интерполяция данных y_in на сетку в n раз гуще выбранныной моделью интерполяции сплайнами порядка a; результат в массив y_out; предполагается равномерная сетка аргументов для y_in

	vecdb & DoTypeInterp(vecdb &y_out, vecdb &y_in);

	vecdb & sinc(vecdb &y_out, vecdb &x_in);  // вычисление sinc(x) для элементов текущего массива, результат в масив y_out
	vecdb & lncz(vecdb &y_out, vecdb &x_in, int a);  // вычисление sinc(x)*sinc(x/a) для элементов текущего массива, результат в масив y_out

	void setexp(int y_inN);// vecdb &y_in); // настроить csy и sny  
	void setlin(vecdb &y_in); // определить параметры klin и blin  

	inline void settype(int n) { type = n; }

	inline int interplength() { return csy.N; }// возвращает длину вектора интеролированного массива

private:
	int n; // кратность сгущения сетки
	int a; // половина длины базисного сплайна в единицах исходной сетки
	vecdb L0; // вектор описывающий базисный сплайн
	vecdb L1; // вспомогательный базисный сплайн
	int type; // тип интеполяции

	vecdb yh0; // вспомогательный массив
	vecdb yh3; // вспомогательный массив
	vecdb yh2; // вспомогательный массив
	vecdb csy, sny; // вспомогательные массивы для хранения cos(x) и sin(x) на новой сетке (используется в двойной интерполяции Ланцоша) 

	double k_lin, b_lin; // коэффицинты линенной зависимости вычитаемой как "подставка"  под графиком y_in

};
#endif // !INTERPOLATOR_H#define 
