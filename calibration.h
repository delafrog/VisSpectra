#ifndef CALIBRATION_H
#define CALIBRATION_H


#include <QWidget>
#include <QPaintEvent>
#include <QRadioButton>
#include <QGroupBox>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include <QScrollArea>

#include "picview.h"
#include "plotgraph.h"
#include "linalg.h"
#include "gaussapprox.h"
#include "lorentsapprox.h"
#include "smpltable.h"
#include "gartapprox.h"

/*
typedef void(*approxFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // ��������� �� ���������������� �������
typedef void(*diffFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // ��������� �� ������� ����������� ���������������� �������
typedef void(*ddFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // ��������� �� ������ ������� ����������� ���������������� �������

//vecT<diffFun> gradFun;
//FullMatrix<ddFun> hessFun;
void aFn(const vecdb &Prm, const vecdb &x,  vecdb & y);

void grdFn1(const vecdb & Prm, const vecdb & x,  vecdb & y);
void grdFn2(const vecdb & Prm, const vecdb & x,  vecdb & y);
void grdFn3(const vecdb & Prm, const vecdb & x,  vecdb & y);
void grdFn4(const vecdb & Prm, const vecdb & x,  vecdb & y);
void grdFn5(const vecdb & Prm, const vecdb & x,  vecdb & y);

void hssFn11(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn12(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn13(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn14(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn15(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn22(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn23(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn24(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn25(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn33(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn34(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn35(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn44(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn45(const vecdb & Prm, const vecdb & x,  vecdb & y);
void hssFn55(const vecdb & Prm, const vecdb & x,  vecdb & y);
*/


class ClbrWidget : public QWidget // ����� ��� ����������� ���� ����������
{
	//QObject;
	Q_OBJECT
public:
	ClbrWidget(QWidget *parent = 0);
	~ClbrWidget(){ };//if (picdata!= 0x0) delete [] picdata;};

	void setCalibrData(vec4FMushort *Dat,int y1,int y2); // ������� �������� ������ ��� ���������� ����������
	void setCalibrData(vec4FMushort *Dat, vec4T<vecdb> &cIS, int y1, int y2, int x1,int x2, int n_); // ���������� ��� ��������� ������ � ��������� ������ ��� ���������������� ��������

	void setPixelScale(int idSc);

	void setApptxTol(double toll);
	void setApptxNitr(int nitr);
	void setDark(double drkr, double drkg1, double drkg2, double drkb) { darkLevelR = drkr; darkLevelG1 = drkg1; darkLevelG2 = drkg2; darkLevelB = drkb;	}

	PicView * getPicPnt() { return clbr_pic; }
	PlotGraph *getGrfPnt() { return clbr_grf; }

	SmplTableView *getClbTbl() { return clbrTbl; }

	GartmanApproximator *getGarApprx() { return &GarApprx; }
	
	vecT<double> * get_lmbds() { return &lmbds; }
	vecT<double> * get_idpix() { return &idpix; }
	vecT<double> * get_sgpix() { return &sgpix; }
	
	int isClDn() { return isClbrDone; }

public	slots:

	void addPeakData(); // �������� ������ ��� ���������� ����  
	void addXselData(); // ���������� �������� ���������� �� ��� X
	void setRed() { chanel_id = 0; }
	void setGreen1() { chanel_id = 1; }
	void setGreen2() { chanel_id = 2; }
	void setBlue() { chanel_id = 3; }
	void setLor() { aprxtype = 1; }
	void setGauss() { aprxtype = 0; }

	void aproxData2DataTable(); // �������� ������� ����� � ������� ����������
	void selectData2DataTable(); // �������� ��������� ������� � �������

	void aproxData2ClbrTable(); // �������� ������� ����� � ������� ����������
	void selectData2ClbrTable(); // �������� ��������� ������� � �������
	void addData2ClbrTable(QTableWidgetItem *tbItm); // �������� ������ � ������� ����������

	void newClbTblPrc(); // ������������ ����� ������������� �������
	void setClbTblPrc(); // ���������� ������� ������� ��� �������������
	void getClbTblPrc(); // ��������� ����� �������������� ������������� �������

	void putClbrTbl2Clpbrd(); // ������� � �����
	void putClpbrd2ClbrTbl(); // �� ������ � �������
	void ClearClbrTbl(); // �������� �������

	void putDataTbl2Clpbrd(); // ������� � �����
	void putClpbrd2DaTbl(); // �� ������ � �������
	void ClearDataTbl(); // �������� �������

	void doLambdaCalibration(); // �������� ���������� ��� ���� ���� �� ������ ������������� �������
	void go2lambda(); // ����������� ��� "��������" � ��� ���� ���� �� ������ ���������� ����������

	void connectionSetup();

//	void setclckflag(QTableWidgetItem *tbItm) { istblclck = true; }
//	void setclckflag_() { istblclck = true; }
	//void cpur() { emit clbr_pic_udt_req(); }
/*	void SetGaussApproxFun(); // ��������� ���������������� ������� � � �����������  f(x) = A*exp(-((x-B)/C)^2)+d*x+E  

	void ErrFun();  // ������� ������
	void GradFun(); // �������� ������� ������
	void HessFun(); // ������� ������ ����������� ������� ������

	void dataNormalize();
	void Approx(); // */
signals:
	void clbr_pic_udp_req();
	
private:

	PicView *clbr_pic; // ����������� "�����" �������� � ������������ �������
	PlotGraph *clbr_grf; // ������ ������� ������ �� ����������� ������ �����������, ���� ��������� - ����� ���������

//	PlotGraph *clbr_tbl; // ������ ����������: ����� ����� �� ������ ������� (��� ����������� ������)
	int pxspln; // ����� ������� � �������� - ��� ����������� �������� � �������
	int pxsphg; // ������ ������� �� ��������
	int dw; // ����� ��� ��������� ���� �������

	int pixScale;  // ��������� ��������������� �����������

	int isClbrDone; //  ������������� ���� ��� ��������� ����������
	int cnct_id; // ������������� ������������ ����� ��������  0 - �� ����������� �����, 1 - ����������� ����� � �������� ����������, 2 - ����������� ����� � �������� ������
	



/*	vecdb Param; // ��������� �������������
	vecdb xx;	// �������� ���������������� �������
	vecdb yy;	// �������� ���������������� �������
	vecdb dy;   // 
	vecdb ddy;  // 
	vecdb ff;   // �������� ����������������� ��������

	double k_x, k_y, b_x, b_y; // �����. ����������� ������ ���  ������������
*/
//	double err; // ������ 
//	vecdb graderr;
//	FullMatrix<double> hesserr;

	
	//vecT<>


//	approxFun Fun;
//	vecT<diffFun> gradFun;
//	FullMatrix<ddFun> hessFun;

	QScrollArea *scrollArea;

	GaussApproximator GssApprx;
	LorentsApproximator LorApprx;
	GartmanApproximator GarApprx;

	QGroupBox *groupBox, *groupBox2;
	QRadioButton *red, *green1, *green2, *blue; // ������ ��� ������ ������ 
	int chanel_id; // ����� ������

	QRadioButton *gauss, *lorents; // ������ ��� ������ ���� �������������
	int aprxtype; // ��� ���������������� ������� 0 - �����, 1 - ������

//	QLabel *yfuntext;//
	QLabel *formula;

	QLabel *fiterrtxt;
	QLabel *fiterrdata;

	QTableWidget *fitParTbl;

	QTableWidgetItem *fP_A, *fP_sgA;
	QTableWidgetItem *fP_B, *fP_sgB;
	QTableWidgetItem *fP_C, *fP_sgC;
	QTableWidgetItem *fP_D, *fP_sgD;
	QTableWidgetItem *fP_E, *fP_sgE;

	QTableWidget *selXTbl;
	QTableWidgetItem *slXTbl, *slDXTbl;

	//SmplTableView *clbrTbl; // ������� ������������� ������
	//SmplTableModel *clbrTblMdl; // ������ ������ ��� ������

	//QTableWidget *clbrTbl; // ������� ������������ ������
	//QList<QTableWidgetItem> *pxlsClmn; // ������ ����� ��� ����������� ������� ��������
	//QList<QTableWidgetItem> *dpxlClmn; // ������ ����� ��� ����������� ������ ������� ��������
	//QList<QTableWidgetItem> *lmbdClmn; // ������ ����� ��� ���������� ���� ����
	SmplTableView *clbrTbl; // ������� k������������ ������
	SmplTableView *dataTbl; // ������ ������������� ������
	QTabWidget *tabTbl; // 
 

	vecT<double> lmbds,idpix,sgpix; // ������� ������������� ������
	vecT<double> lambda, sglambda; // ������� ���� ���� ���������� � ������� ����� ����������

	double darkLevelR, darkLevelG1, darkLevelG2, darkLevelB ;

	double slX, slDX; 

	int nClbrPnts; // ���������� ����� �������������� �������

	QPushButton *addPeakDataInClbrBtn; // �������� ������ � ������� ����������
	QPushButton *addSelectDataInClbrBtn; // �������� ��������� �������� � ������� ����������
	QPushButton *newCblTblBtn; // ������������ ����� ������� ���������� (��� ������)
	QPushButton *setCblTblBtn; // ���������� ������ � ������� ���������� ��� ���������� ���������
	QPushButton *getCblTblBtn; // ��������� ����� ��������������� ������� ����������

	QPushButton *calibrate_button; // ������ ������������� ���������� 
	QPushButton *clbrCalc_button; // ������ ���������� ���������� - ����������� ����� ���� ����

	//bool istblclck; // ���� ����� �� ������ �������

protected :
	//void paintEvent(QPaintEvent *event);

};
/*
class ClbrTableData // ����� ������ ������������� �������
{
public:
	ClbrTableData();//QObject *parent = 0);
	ClbrTableData(const ClbrTableData &other);
	~ClbrTableData();

	//ClbrTableData & operator = (const IIMData& other);

	

};
/*
class Calibrator // ����� ��� ���������� �������� ����������
{
//	QObject;
public:
	Calibrator();
	~Calibrator(){};
private:

	VecT<FullMatrix<double>> ClbrTables; // ������ ������������� ������


};*/



#endif