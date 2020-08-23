//#pragma once
#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H


#include "linalg.h"

class Interpolator
{
public:
	Interpolator() { n = 0; a = 0; type = 0; };
	~Interpolator() {};

	void SetLanczos(int n_, int a_); // ��������� ������������ ������� ������� a_ ��� ��������� ����� n_ 
	void SetDblLncz(int n_); // ��������� ������� ������������ ������� ������� 2 � 3 ��� ��������� ����� n_ 
	void SetLinear(int n_); // ��������� �������� ������������ 
	//void SetQuadr(int n_); //  ��������� ������������ �����������
	void SetCubic(int n_); //  ��������� ���������� �����������
	void SetTypeInterp(int n_); // ��������� ������������ �� ���� type


	vecdb & DoInterpolatoin(vecdb &y_out, const vecdb &y_in); // ������������ ������ y_in �� ����� � n ��� ���� ����������� ������� ������������ ��������� ������� a; ��������� � ������ y_out; �������������� ����������� ����� ���������� ��� y_in
	vecdb & DoDoubleLanczos(vecdb &y_out, vecdb &y_in); // ������� ������������ ������ y_in �� ����� � n ��� ���� ����������� ������� ������������ ��������� ������� a; ��������� � ������ y_out; �������������� ����������� ����� ���������� ��� y_in

	vecdb & DoTypeInterp(vecdb &y_out, vecdb &y_in);

	vecdb & sinc(vecdb &y_out, vecdb &x_in);  // ���������� sinc(x) ��� ��������� �������� �������, ��������� � ����� y_out
	vecdb & lncz(vecdb &y_out, vecdb &x_in, int a);  // ���������� sinc(x)*sinc(x/a) ��� ��������� �������� �������, ��������� � ����� y_out

	void setexp(int y_inN);// vecdb &y_in); // ��������� csy � sny  
	void setlin(vecdb &y_in); // ���������� ��������� klin � blin  

	inline void settype(int n) { type = n; }

	inline int interplength() { return csy.N; }// ���������� ����� ������� ����������������� �������

private:
	int n; // ��������� �������� �����
	int a; // �������� ����� ��������� ������� � �������� �������� �����
	vecdb L0; // ������ ����������� �������� ������
	vecdb L1; // ��������������� �������� ������
	int type; // ��� �����������

	vecdb yh0; // ��������������� ������
	vecdb yh3; // ��������������� ������
	vecdb yh2; // ��������������� ������
	vecdb csy, sny; // ��������������� ������� ��� �������� cos(x) � sin(x) �� ����� ����� (������������ � ������� ������������ �������) 

	double k_lin, b_lin; // ����������� �������� ����������� ���������� ��� "���������"  ��� �������� y_in

};
#endif // !INTERPOLATOR_H#define 
