#ifndef GAUSSAPPROX_H
#define GAUSSAPPROX_H


#include "linalg.h" 

//const int GaussApproxDim = 5;
//class GaussApproximator;
//typedef void (GaussApproximator::*AprxFun)( vecdb &xx, vecdb &yy);

class GaussApproximator // ����� ��� ���������� ������������� ������ �������� ���� y(x) = A*exp(-((x-B)/C)^2)+D*x+E ������� ���������� ��������� 
{
public:
	
	GaussApproximator();
	~GaussApproximator() {};

	//AprxFun AF;

	const int dim = 5; // ����������� ������������� - ����� 5 ����������

	double kx, ky, bx, by; // ������������ ��� �������� ������ � ������� ��������: x -> [-1..1]; y -> [0..1];
	double k_, b_; 
	int sign; // ��������� "������������ ����" - �������� ��� ��� ����������
	double usr_eps; // ��������������� ������������� ������� 
	int    usr_Nittr; // ��������������� ������������� ������������ ����� ���������


	vecdb x,y; // ������ ��� �������������
	vecdb f; // ���������������� ������� (�������)
	vecdb hexp; // ��� �������� ���������
	vecdb hf1, hf2;// ��������������� ������� ��� ��������� ����������
	vecdb dfy; // ������� (f-y)

	double err; // ������ �������������
	vecdb P,S,S_,R,R_,X,X_; // ������� ��� ������ �����������
	vecdb Grd; // ������ ��������
	FullMatrix<double> H; // ������� ������ �����������
	
	vecT<vecdb>  grad_data; // ��������� ������
	//FullMatrix<vecdb> hess_data; // ������ ����������� ������	
	vecdb hess_data_12;
	vecdb hess_data_13;
	vecdb hess_data_22;
	vecdb hess_data_23;
	vecdb hess_data_33;

	void setdata(vecdb &x_in, vecdb &y_in); // ��������� ������ ��� �������������

	void fitfun(vecdb &Xk); // ���������� ������� �������������
	void ErrFun(vecdb &Xk); // ���������� ������
	void gradFun(vecdb &Xk); // ���������� ��������� ������
	void hessFun(vecdb &Xk); // ���������� ������� ������ �����������

	void GradErr(vecdb &Xk);
	void HessErr(vecdb &Xk);

	void initguess(vecdb &Xk); // ��������� ����������� - �� ������ ����

	void MinErrFind(); // ��������� ����������� ���������� �������������� ������ �������������

	void Finalize(); // ���������� � ��������� ��������, ���������� �������������� ���������� 

	void Fun(vecdb &xx, vecdb &yy); // ���������� ���������������� ������� �� ���������� xx ��������� - � yy (�� ���������� �� X)

//	AprxFun retptr() { return this->*Fun; }

};

#endif
