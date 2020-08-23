//#pragma once
#ifndef GARTAPPROX_H
#define GARTAPPROX_H


#include "linalg.h" 

//const int GaussApproxDim = 5;
//class GaussApproximator;
//typedef void (GaussApproximator::*AprxFun)( vecdb &xx, vecdb &yy);

class GartmanApproximator // ����� ��� ���������� ������������� ������ �������� ���� y(x) =  ������� ���������� ��������� 
{
public:

	GartmanApproximator();
	~GartmanApproximator() {};

	//AprxFun AF;

	const int dim = 3; // ����������� ������������� - ����� 3 ���������

	double kx, ky, bx, by; // ������������ ��� �������� ������ � ������� ��������: x -> [-1..1]; y -> [0..1];
	double k_, b_;
	int sign; // ��������� "������������ ����" - �������� ��� ��� ����������

	double usr_eps; // ��������������� ������������� ������� 
	int    usr_Nittr; // ��������������� ������������� ������������ ����� ���������

	vecdb x, y; // ������ ��� �������������
	vecdb f; // ���������������� ������� (�������)
	vecdb hexp, sqhexp; // ��� �������� ���������
	vecdb hf1, hf2;// ��������������� ������� ��� ��������� ����������
	vecdb dfy; // ������� (f-y)

	double err; // ������ �������������
	vecdb P, S, S_, R, R_, X, X_; // ������� ��� ������ �����������
	vecdb Grd; // ������ ��������
	FullMatrix<double> H; // ������� ������ �����������

	vecT<vecdb>  grad_data; // ��������� ������
							//FullMatrix<vecdb> hess_data; // ������ ����������� ������	
	vecdb hess_data_11;
	vecdb hess_data_13;


	void setdata(vecdb &x_in, vecdb &y_in); // ��������� ������ ��� �������������

	void fitfun(vecdb &Xk); // ���������� ������� �������������
	void ErrFun(vecdb &Xk); // ���������� ������
	void gradFun(vecdb &Xk); // ���������� ��������� ������
	void hessFun(vecdb &Xk); // ���������� ������� ������ �����������

	void GradErr(vecdb &Xk);
	void HessErr(vecdb &Xk);

	void initguess();// vecdb &Xk); // ��������� ����������� - �� ������� ��������������� �������

	void MinErrFind(); // ��������� ����������� ���������� �������������� ������ �������������

	void Finalize(); // ���������� � ��������� ��������, ���������� �������������� ���������� 

	void Fun(vecdb &xx, vecdb &yy); // ���������� ���������������� ������� �� ���������� xx ��������� - � yy (�� ���������� �� X)
	void InvFun(vecdb &xx, vecdb &yy); // ���������� �������� ���������������� ������� �� ���������� xx ��������� - � yy (�� ���������� �� X)
	void dInvFun(vecdb &xx, vecdb &yy);// ���������� ����������� �������� ���������������� ������� �� ���������� xx ��������� - � yy (�� ���������� �� X)
									//	AprxFun retptr() { return this->*Fun; }

	void dFun(vecdb &xx, vecdb &yy);// ���������� ����������� ���������������� ������� �� ���������� xx ��������� - � yy (�� ���������� �� X)
									   


};



#endif