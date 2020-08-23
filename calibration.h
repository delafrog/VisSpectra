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
typedef void(*approxFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // указатель на аппроксимирующую функцию
typedef void(*diffFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // указатель на частную производную аппроксимирующей функции
typedef void(*ddFun)(const vecdb & Prm, const vecdb & x,  vecdb & y); // указатель на вторую частную производную аппроксимирующей функции

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


class ClbrWidget : public QWidget // класс для отображения окна калибровки
{
	//QObject;
	Q_OBJECT
public:
	ClbrWidget(QWidget *parent = 0);
	~ClbrWidget(){ };//if (picdata!= 0x0) delete [] picdata;};

	void setCalibrData(vec4FMushort *Dat,int y1,int y2); // функция загрузки данных для проведения калибровки
	void setCalibrData(vec4FMushort *Dat, vec4T<vecdb> &cIS, int y1, int y2, int x1,int x2, int n_); // перегрузка для обработки случая с передачей данных для интеполированных графиков

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

	void addPeakData(); // добавить данные для выбранного пика  
	void addXselData(); // отобразить выбраную координату по оси X
	void setRed() { chanel_id = 0; }
	void setGreen1() { chanel_id = 1; }
	void setGreen2() { chanel_id = 2; }
	void setBlue() { chanel_id = 3; }
	void setLor() { aprxtype = 1; }
	void setGauss() { aprxtype = 0; }

	void aproxData2DataTable(); // добавить текущую точку в таблицу калибровки
	void selectData2DataTable(); // добавить выбранную область в таблицу

	void aproxData2ClbrTable(); // добавить текущую точку в таблицу калибровки
	void selectData2ClbrTable(); // добавить выбранную область в таблицу
	void addData2ClbrTable(QTableWidgetItem *tbItm); // добавить данные в таблицу калибровки

	void newClbTblPrc(); // инициоровать новую калибровочную таблицу
	void setClbTblPrc(); // установить текущую таблицу как калибровочную
	void getClbTblPrc(); // загрузить ранее сформированную калибровочную таблицу

	void putClbrTbl2Clpbrd(); // таблицу в буфер
	void putClpbrd2ClbrTbl(); // из буфера в таблицу
	void ClearClbrTbl(); // очистить таблицу

	void putDataTbl2Clpbrd(); // таблицу в буфер
	void putClpbrd2DaTbl(); // из буфера в таблицу
	void ClearDataTbl(); // очистить таблицу

	void doLambdaCalibration(); // провести калибровку для длин волн по данным калибровочной таблицы
	void go2lambda(); // пересчитать ось "пикселей" в ось длин волн на основе параметров калибровки

	void connectionSetup();

//	void setclckflag(QTableWidgetItem *tbItm) { istblclck = true; }
//	void setclckflag_() { istblclck = true; }
	//void cpur() { emit clbr_pic_udt_req(); }
/*	void SetGaussApproxFun(); // установка аппроксимирующей функции и её производных  f(x) = A*exp(-((x-B)/C)^2)+d*x+E  

	void ErrFun();  // функция ошибки
	void GradFun(); // градиент функции ошибки
	void HessFun(); // матрица вторых производных функции ошибки

	void dataNormalize();
	void Approx(); // */
signals:
	void clbr_pic_udp_req();
	
private:

	PicView *clbr_pic; // отображение "узкой" картинки с изображением спектра
	PlotGraph *clbr_grf; // график спектра взятый по центральной строке изображения, либо суммарный - после обработки

//	PlotGraph *clbr_tbl; // график калибровки: длина волны от номера пикселя (для центральной строки)
	int pxspln; // длина спектра в пикселях - для отображения картинки и графика
	int pxsphg; // выстоа каринки со спектром
	int dw; // сдвиг для рисования осей графика

	int pixScale;  // множитель масштабирования изображения

	int isClbrDone; //  идентификатор того что проведена калибровка
	int cnct_id; // идентификатор установления связи сигналов  0 - не установлена связь, 1 - установлена связь с таблицей калибровки, 2 - установлена связь с таблицей данных
	



/*	vecdb Param; // параметры аппроксимации
	vecdb xx;	// аргумент аппроксимирующей функции
	vecdb yy;	// значения аппроксимирующей функции
	vecdb dy;   // 
	vecdb ddy;  // 
	vecdb ff;   // значения экспериметнальных значений

	double k_x, k_y, b_x, b_y; // коэфф. нормализаци данных для  апроксимации
*/
//	double err; // ошибка 
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
	QRadioButton *red, *green1, *green2, *blue; // кнопки для выбора канала 
	int chanel_id; // номер канала

	QRadioButton *gauss, *lorents; // кнопки для выбора типа аппроскимации
	int aprxtype; // тип аппроксимирующей функции 0 - гаусс, 1 - лоренц

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

	//SmplTableView *clbrTbl; // таблица калибровочных данных
	//SmplTableModel *clbrTblMdl; // модель данных для таблиц

	//QTableWidget *clbrTbl; // таблица алибровочных данных
	//QList<QTableWidgetItem> *pxlsClmn; // список ячеек для отображения номеров пикселей
	//QList<QTableWidgetItem> *dpxlClmn; // список ячеек для отображения ошибки номеров пикселей
	//QList<QTableWidgetItem> *lmbdClmn; // список ячеек для отбражения длин волн
	SmplTableView *clbrTbl; // таблица kалибровочных данных
	SmplTableView *dataTbl; // аблица калиброванных данных
	QTabWidget *tabTbl; // 
 

	vecT<double> lmbds,idpix,sgpix; // массивы калибровочных данных
	vecT<double> lambda, sglambda; // массивы длин волн измеренных о спектру после калибровки

	double darkLevelR, darkLevelG1, darkLevelG2, darkLevelB ;

	double slX, slDX; 

	int nClbrPnts; // количество точек калибровочного графика

	QPushButton *addPeakDataInClbrBtn; // добавить данные в таблицу калибровки
	QPushButton *addSelectDataInClbrBtn; // добавить выбранное значение в таблицу калибровки
	QPushButton *newCblTblBtn; // инициировать новую таблицу калибровки (без данных)
	QPushButton *setCblTblBtn; // установить данные в таблицу калибровки для дальнейшей обработки
	QPushButton *getCblTblBtn; // загрузить ранее сформированныую таблицу калибровки

	QPushButton *calibrate_button; // кнопка коэффициентов калибровки 
	QPushButton *clbrCalc_button; // кнопка вычисления калибровки - определение шкалы длин волн

	//bool istblclck; // флаг клика по ячейке таблицы

protected :
	//void paintEvent(QPaintEvent *event);

};
/*
class ClbrTableData // класс данных калибровочной таблицы
{
public:
	ClbrTableData();//QObject *parent = 0);
	ClbrTableData(const ClbrTableData &other);
	~ClbrTableData();

	//ClbrTableData & operator = (const IIMData& other);

	

};
/*
class Calibrator // класс для проведения расчётов калибровки
{
//	QObject;
public:
	Calibrator();
	~Calibrator(){};
private:

	VecT<FullMatrix<double>> ClbrTables; // данные калибровочных таблиц


};*/



#endif