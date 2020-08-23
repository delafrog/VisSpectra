#ifndef LORENTSAPPROX_H
#define LORENTSAPPROX_H

#include "linalg.h" 

class LorentsApproximator
{
public:

	LorentsApproximator();
	~LorentsApproximator() {};

	//AprxFun AF;

	const int dim = 5; // ����������� ������������� - ����� 5 ����������

	double kx, ky, bx, by; // ������������ ��� �������� ������ � ������� ��������: x -> [-1..1]; y -> [0..1];
	double k_, b_;
	int sign; // ��������� "������������ ����" - �������� ��� ��� ����������
	double usr_eps; // ��������������� ������������� ������� 
	int    usr_Nittr; // ��������������� ������������� ������������ ����� ���������

	vecdb x, y; // ������ ��� �������������
	vecdb f; // ���������������� ������� (�������)
	vecdb hexp,sqhexp; // ��� �������� ���������
	vecdb hf1, hf2;// ��������������� ������� ��� ��������� ����������
	vecdb dfy; // ������� (f-y)

	double err; // ������ �������������
	vecdb P, S, S_, R, R_, X, X_; // ������� ��� ������ �����������
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
};

#endif