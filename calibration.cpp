#ifndef CALIBRATION_CPP
#define CALIBRATION_CPP

#include <QApplication>
#include <QWidget>
#include <QClipboard>
#include <QMimeData>
#include "calibration.h"
//#include "linalg.cpp"
#include "linalg.h"


/*
vecdb hexp;

void aFn(const vecdb &Prm, const vecdb &x,  vecdb & y)
{
	double h1;
	for (int ii = 0;ii < x.N;ii++)	
	{
		h1 = (x.x[ii] - Prm.x[1]) / Prm.x[2];
		h1 *= h1;
		hexp.x[ii] = exp(-h1);
	}
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = Prm.x[0] * hexp.x[ii] + Prm.x[3] * x.x[ii] + Prm.x[4];
	}
}

void grdFn1(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = hexp.x[ii];
	}
}

void grdFn2(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = 2*Prm.x[0]*hexp.x[ii]*(x.x[ii]-Prm.x[1])/(Prm.x[2]*Prm.x[2]);
	}
}

void grdFn3(const vecdb & Prm, const vecdb & x, vecdb & y)
{
	grdFn2(Prm,x,y);
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] *=  (x.x[ii] - Prm.x[1]) / ( Prm.x[2]);
	}
}

void grdFn4(const vecdb & Prm, const vecdb & x,  vecdb & y){	y = x;}

void grdFn5(const vecdb & Prm, const vecdb & x,  vecdb & y){	y = 1.0;}



void hssFn11(const vecdb & Prm, const vecdb & x,  vecdb & y){	y.zero();}

void hssFn12(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = 2 * hexp.x[ii] * (x.x[ii] - Prm.x[1]) / (Prm.x[2] * Prm.x[2]);
	}
}

void hssFn13(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	hssFn12(Prm, x, y);
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] *= (x.x[ii] - Prm.x[1]) / (Prm.x[2]);
	}
}

void hssFn14(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn15(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn22(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = 2 * Prm.x[0] * hexp.x[ii] * ( 2*(x.x[ii] - Prm.x[1])*(x.x[ii] - Prm.x[1])/(Prm.x[2] * Prm.x[2]) - 1 ) / ( Prm.x[2] * Prm.x[2]);
	}
}

void hssFn23(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = 4 * Prm.x[0] * (x.x[ii] - Prm.x[1]) * hexp.x[ii] * ( (x.x[ii] - Prm.x[1])*(x.x[ii] - Prm.x[1]) / (Prm.x[2] * Prm.x[2]) - 1 ) / (Prm.x[2] * Prm.x[2] * Prm.x[2]);
	}
}

void hssFn24(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn25(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn33(const vecdb & Prm, const vecdb & x,  vecdb & y)
{
	for (int ii = 0;ii < x.N;ii++)
	{
		y.x[ii] = 2 * Prm.x[0] * (x.x[ii] - Prm.x[1])*(x.x[ii] - Prm.x[1]) * hexp.x[ii] * (2*(x.x[ii] - Prm.x[1])*(x.x[ii] - Prm.x[1]) / (Prm.x[2] * Prm.x[2]) - 3) / (Prm.x[2] * Prm.x[2]* Prm.x[2] * Prm.x[2]);
	}
}

void hssFn34(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn35(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn44(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn45(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero(); }

void hssFn55(const vecdb & Prm, const vecdb & x,  vecdb & y){ y.zero();}

*/

ClbrWidget::ClbrWidget(QWidget *parent) : QWidget(parent)
{
	int Dx;
	pxspln = 120;
	pxsphg = 100;
	pixScale = 2; 
	clbr_pic = new PicView(this);
	clbr_pic->setsz(pxspln, pxsphg);
	clbr_pic->BlackFill();
	clbr_pic->setpnts(0., 0., 0., 0.);
	clbr_pic->settype(1);

	clbrTbl = 0x0;; // таблица kалибровочных данных
	dataTbl = 0x0; // аблица калиброванных данных

	clbr_grf = new PlotGraph(this);
	clbr_grf->setNgrphx(4);
	clbr_grf->xlabel(QApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\262 \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270 (x,y) [\320\277\320\270\321\201\320\272\320\265\320\273\320\270]", 0));
	clbr_grf->ylabel(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 [\320\276\321\202\320\275. \320\265\320\264.]", 0));//tr("Int. a.u."));

	darkLevelR = 0.0;
	darkLevelG1 = 0.0;
	darkLevelG2 = 0.0;
	darkLevelB = 0.0;

	//scrollArea = new QScrollArea(this);

/*	AprxFun ApFun;
	clFun cF;

	ApFun = GssApprx.AF;
/*	__asm
	{
		mov eax, dword ptr [ApFun]
		mov dword ptr [cF], eax
	}
	/** /
	//cF	  =  reinterpret_cast<clFun>(ApFun);
	clbr_grf->Fun = cF;
	*/
	//QPainter painter;

	clbr_grf->p_gsaprx = &GssApprx;
	clbr_grf->p_loraprx = &LorApprx;
	aprxtype = 0;

	clbr_grf->FrameSetUp();// DrawAxes(painter);
	dw = clbr_grf->fontMetrics().width("-0.000");
	Dx = clbr_grf->get_lShift();
	clbr_pic->set_lShft(Dx);
	Dx = dw + pxspln-1;
	clbr_grf->setFixedWidth(Dx);
	clbr_grf->setTcsTpx(0);
	clbr_grf->setTcsTpy(1);


	isClbrDone = 0; //  идентификатор того что проведена калибровка 0 - нет  1 - проведена


	chanel_id = -1; // по умолчанию нет выбранного канала

	groupBox = new QGroupBox(tr("\320\232\320\260\320\275\320\260\320\273\040\320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270\040\320\277\320\270\320\272\320\260"));// QApplication::translate("Channel for peak approximation", 0), this);


	red = new QRadioButton(QApplication::translate("MainWindow", "\320\232\321\200\320\260\321\201\320\275\321\213\320\271", 0),this);//Red channel
	green1 = new QRadioButton(QApplication::translate("MainWindow", "\320\227\320\265\320\273\321\221\320\275\321\213\320\271\040\061", 0), this);//Green1 channel
	green2 = new QRadioButton(QApplication::translate("MainWindow", "\320\227\320\265\320\273\321\221\320\275\321\213\320\271\040\062", 0), this);//Green2 channel
	blue = new QRadioButton(QApplication::translate("MainWindow", "\320\241\320\270\320\275\320\270\320\271", 0), this);//Blue channel

	QGridLayout * gbox;
	gbox = new QGridLayout();

	gbox->addWidget(red,0,0);
	gbox->addWidget(green1, 0,1);
	gbox->addWidget(green2, 1, 0);
	gbox->addWidget(blue, 1, 1);

	groupBox->setLayout(gbox);

	//yfuntext = new QLabel(tr("Approximation function: f(x) = A*exp(-( (x-B)/C)^2 ) + D*(x-B) + E"));

	groupBox2 = new QGroupBox(tr("\320\220\320\277\320\277\321\200\320\276\321\201\320\272\320\270\320\274\320\270\321\200\321\203\321\216\321\211\320\260\321\217\040\321\204\321\203\320\275\320\272\321\206\320\270\321\217"));//  Type of a peak approximation              QApplication::translate("Channel for peak approximation", 0), this);

	lorents = new QRadioButton(QApplication::translate("MainWindow", "\320\233\320\276\321\200\320\265\320\275\321\206: f(x) = A/((x-B)^2+C^2) +D*(x-B) + E ", 0), this);//Lorents fit
	gauss = new QRadioButton(QApplication::translate("MainWindow", "\320\223\320\260\321\203\321\201\321\201: f(x) =  A*exp(-( (x-B)/C)^2 ) + D*(x-B) + E ", 0), this);//Gauss fit

	QVBoxLayout * vbox5;
	vbox5 = new QVBoxLayout();
	vbox5->addWidget(gauss);
	vbox5->addWidget(lorents);
	groupBox2->setLayout(vbox5);
	groupBox2->setFixedSize(300,80);


	addPeakDataInClbrBtn = new QPushButton(QString("\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214\040\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265\040\320\277\320\270\320\272\320\260\040\320\262\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\321\203\321\216\040\321\202\320\260\320\261\320\273\320\270\321\206\321\203"),this);//Send a peak position data to the calibration table
//	addPeakDataInClbrBtn->setText(QString("Send peak position data to calibration table"));
	addPeakDataInClbrBtn->setFixedWidth(300);
//	formula = new QLabel(this);
//	formula->setPixmap(QPixmap(QString("formula.png")));


	QHBoxLayout * hbox1;
	hbox1 = new QHBoxLayout();
	hbox1->addWidget(groupBox);
	hbox1->addStretch();

	QVBoxLayout * vbox2;
	vbox2 = new QVBoxLayout();
	vbox2->addLayout(hbox1);
	vbox2->addWidget(groupBox2);
//	vbox2->addWidget(yfuntext);
//	vbox2->addWidget(formula);
	

	fiterrtxt = new QLabel(tr("\320\236\321\210\320\270\320\261\320\272\320\260\040\320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270 Err(A,B,C,D,E) = "));//Fit error 
	fiterrdata = new QLabel(tr(" "));
	QHBoxLayout * hbox4;
	hbox4 = new QHBoxLayout();
	hbox4->addWidget(fiterrtxt);
	hbox4->addWidget(fiterrdata);	
	hbox4->addStretch();

	vbox2->addLayout(hbox4);

	QStringList LblNms;
	LblNms.append(QString(tr("\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265")));//Value
	LblNms.append(QString(tr("\320\236\321\210\320\270\320\261\320\272\320\260")));//Error
	QStringList PrmNms;
	PrmNms.append(QString(tr("A [Counts]")));
	PrmNms.append(QString(tr("B [Pixels]")));
	PrmNms.append(QString(tr("C [Pixels]")));
	PrmNms.append(QString(tr("D [Cnt/Pxl]")));
	PrmNms.append(QString(tr("E [Counts]")));

	fitParTbl =	 new QTableWidget(this);
	fitParTbl->setColumnCount(2);
	fitParTbl->setRowCount(5);
	fitParTbl->setVerticalHeaderLabels(PrmNms);
	fitParTbl->setHorizontalHeaderLabels(LblNms);
	fitParTbl->setFixedSize(300, 175);// 175);


	fP_A = new  QTableWidgetItem();
	fP_sgA = new  QTableWidgetItem();
	fP_B = new  QTableWidgetItem();
	fP_sgB = new  QTableWidgetItem();
	fP_C = new  QTableWidgetItem();
	fP_sgC = new  QTableWidgetItem();
	fP_D = new  QTableWidgetItem();
	fP_sgD = new  QTableWidgetItem();
	fP_E = new  QTableWidgetItem();
	fP_sgE = new  QTableWidgetItem();

	fitParTbl->setItem(0, 0, fP_A);
	fitParTbl->setItem(0, 1, fP_sgA);
	fitParTbl->setItem(1, 0, fP_B);
	fitParTbl->setItem(1, 1, fP_sgB);
	fitParTbl->setItem(2, 0, fP_C);
	fitParTbl->setItem(2, 1, fP_sgC);
	fitParTbl->setItem(3, 0, fP_D);
	fitParTbl->setItem(3, 1, fP_sgD);
	fitParTbl->setItem(4, 0, fP_E);
	fitParTbl->setItem(4, 1, fP_sgE);

	QStringList XDXNms;
	XDXNms.append(QString(tr(" X")));
	XDXNms.append(QString(tr(" \316\224X")));//dX
	QStringList ValNms;
	ValNms.append(QString(tr("\320\222\321\213\320\264\320\265\320\273\320\265\320\275\320\275\320\260\321\217\040\320\276\320\261\320\273\320\260\321\201\321\202\321\214")));//Selected Value

	selXTbl = new QTableWidget(this);
	selXTbl->setColumnCount(2);
	selXTbl->setRowCount(1);
	selXTbl->setVerticalHeaderLabels(ValNms);
	selXTbl->setHorizontalHeaderLabels(XDXNms);
	selXTbl->setColumnWidth(0, 75);
	selXTbl->setColumnWidth(1, 75);
	selXTbl->setFixedSize(300, 58);


	addSelectDataInClbrBtn = new QPushButton(QString("\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214\040\320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265\040\320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265\040\320\262\040\321\202\320\260\320\261\320\273\320\270\321\206\321\203\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\270:"), this); //Send a selected pixels data to the calibration table добавить выбранное значение в таблицу калибровки
	addSelectDataInClbrBtn->setFixedWidth(300);

	slXTbl = new  QTableWidgetItem();
	slDXTbl = new  QTableWidgetItem();

	selXTbl->setItem(0, 0, slXTbl);
	selXTbl->setItem(0, 1, slDXTbl);

	QGroupBox *cl_tb_grbx;
	cl_tb_grbx = new QGroupBox(tr("\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\320\260\321\217\040\321\202\320\260\320\261\320\273\320\270\321\206\320\260"));//Calibration table
	cl_tb_grbx->setMaximumWidth(320);
	QVBoxLayout * vbox6;
	vbox6 = new QVBoxLayout();


	//clbrTbl = new SmplTableView(this);
	//clbrTblMdl = new SmplTableModel(this);
	//clbrTblMdl->setItemData(0.0, 0, 0);

	//ClbrData.setSize(3, 100);
	int initNN = 10;
	lmbds.setmem(initNN);
	idpix.setmem(initNN);
	sgpix.setmem(initNN);

	lambda.setmem(initNN);
	sglambda.setmem(initNN);

	nClbrPnts = 0;

	QStringList ClbNms;
	ClbNms.append(QString("\316\273 [\303\205] "));//lambda[Anstr]
	ClbNms.append(QString("# pixel"));
	ClbNms.append(QString("\316\224 pixel"));
	

	clbrTbl = new SmplTableView(this);// QTableWidget(this);
	clbrTbl->setColumnCount(3);
	clbrTbl->setRowCount(idpix.mN);
	clbrTbl->setHorizontalHeaderLabels(ClbNms);
	clbrTbl->setColumnWidth(0,85);
	clbrTbl->setColumnWidth(1,85);
	clbrTbl->setColumnWidth(2,80);
	clbrTbl->setFixedHeight(200);
	clbrTbl->setMaximumWidth(300);

	QTableWidgetItem *hItm;
	for (int ii = 0; ii < idpix.mN; ii++)
	{
		hItm = new  QTableWidgetItem();
		clbrTbl->setItem(ii,0,hItm);
		hItm = new  QTableWidgetItem();
		clbrTbl->setItem(ii, 1, hItm);
		hItm = new  QTableWidgetItem();
		clbrTbl->setItem(ii, 2, hItm);
	}

	calibrate_button = new QPushButton(QString("\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214\040\320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\270"), this); //  ѕровести калибровку
	calibrate_button->setEnabled(false);
	clbrCalc_button = new QPushButton(QString("\320\237\321\200\320\276\320\262\320\265\321\201\321\202\320\270\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\321\203"));
	clbrCalc_button->setEnabled(false);


	QStringList DatNms;
	DatNms.append(QString("\316\273 [\303\205] "));//lambda[Anstr]
	DatNms.append(QString("\316\224\316\273 [\303\205]"));

	dataTbl = new SmplTableView(this);// QTableWidget(this);
	dataTbl->setColumnCount(2);
	dataTbl->setRowCount(idpix.mN);
	dataTbl->setHorizontalHeaderLabels(DatNms);
	dataTbl->setColumnWidth(0, 85);
	dataTbl->setColumnWidth(1, 85);
	dataTbl->setFixedHeight(200);
	dataTbl->setMaximumWidth(300);
	dataTbl->setEnabled(false);

	for (int ii = 0; ii < lambda.mN; ii++)
	{
		hItm = new  QTableWidgetItem();
		dataTbl->setItem(ii, 0, hItm);
		hItm = new  QTableWidgetItem();
		dataTbl->setItem(ii, 1, hItm);
	}

	tabTbl = new QTabWidget();
	tabTbl->addTab(clbrTbl, QString("\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260")); // калибровка
	tabTbl->addTab(dataTbl,QString("\320\224\320\260\320\275\320\275\321\213\320\265"));  // данные

	//vbox6->addWidget(clbrTbl);
	vbox6->addWidget(tabTbl);
	vbox6->addWidget(calibrate_button);
	vbox6->addWidget(clbrCalc_button);

/*	newCblTblBtn = new QPushButton(QString("New table"), this);
	setCblTblBtn = new QPushButton(QString("Set table"), this); // установить данные в таблицу калибровки дл€ дальнейшей обработки
	getCblTblBtn = new QPushButton(QString("Get table"), this); // загрузить ранее сформированныую таблицу калибровки
	newCblTblBtn->setEnabled(false);
	setCblTblBtn->setEnabled(false);
	getCblTblBtn->setEnabled(false);
	QHBoxLayout * hbox5;
	hbox5 = new QHBoxLayout();
	hbox5->addWidget(newCblTblBtn);
	hbox5->addWidget(setCblTblBtn);
	hbox5->addWidget(getCblTblBtn);
	//vbox6->addLayout(hbox5);*/
	cl_tb_grbx->setLayout(vbox6);

	
	vbox2->addWidget(fitParTbl);
	vbox2->addWidget(addPeakDataInClbrBtn);
	vbox2->addWidget(selXTbl);
	vbox2->addWidget(addSelectDataInClbrBtn);
	vbox2->addWidget(cl_tb_grbx);
	vbox2->addStretch();

	QWidget *locW = new QWidget(this);
	scrollArea = new QScrollArea(this);
	locW->setLayout(vbox2);
	scrollArea->setWidget(locW);
	scrollArea->setWidgetResizable(true);

	QVBoxLayout * vbox1;

	vbox1 = new QVBoxLayout();

	vbox1->addWidget(clbr_pic);
	vbox1->addWidget(clbr_grf);
//	vbox1->addStretch();

	QHBoxLayout * hbox0;
	hbox0 = new QHBoxLayout();
	hbox0->addLayout(vbox1);
	hbox0->addWidget(scrollArea); //addLayout(vbox2);


	

	
//	scrollArea->setWidgetResizable(true);
//	scrollArea->setLayout(hbox0);

	this->setLayout(hbox0);

	//istblclck = false;



	connect(clbr_grf, SIGNAL(selDataReady()), this, SLOT(addPeakData()));
	connect(clbr_grf, SIGNAL(selXReady()), this, SLOT(addXselData()));

	connect(red, SIGNAL(clicked()), this, SLOT(setRed()));
	connect(green1, SIGNAL(clicked()), this, SLOT(setGreen1()));
	connect(green2, SIGNAL(clicked()), this, SLOT(setGreen2()));
	connect(blue, SIGNAL(clicked()), this, SLOT(setBlue()));

	connect(gauss, SIGNAL(clicked()), this, SLOT(setGauss()));
	connect(lorents, SIGNAL(clicked()), this, SLOT(setLor()));

	connect(clbr_pic, SIGNAL(getnewpic()), this, SIGNAL(clbr_pic_udp_req()));

//	connect(addPeakDataInClbrBtn, SIGNAL(clicked()), this, SLOT(aproxData2ClbrTable()));
//	connect(addSelectDataInClbrBtn, SIGNAL(clicked()), this, SLOT(selectData2ClbrTable()));
	
	connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
//	connect(clbrTbl, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(setclckflag(QTableWidgetItem *)));
//	connect(clbrTbl, SIGNAL(itemSelectionChanged()), this, SLOT(setclckflag_()));

	connect(clbrTbl, SIGNAL(Table2Clipboad()), this, SLOT(putClbrTbl2Clpbrd()));
	connect(clbrTbl, SIGNAL(Clipboad2Table()), this, SLOT(putClpbrd2ClbrTbl()));
	connect(clbrTbl, SIGNAL(TableClearAll()), this, SLOT(ClearClbrTbl()));

	connect(dataTbl, SIGNAL(Table2Clipboad()), this, SLOT(putDataTbl2Clpbrd()));
	connect(dataTbl, SIGNAL(Clipboad2Table()), this, SLOT(putClpbrd2DataTbl()));
	connect(dataTbl, SIGNAL(TableClearAll()), this, SLOT(ClearDataTbl()));

	connect(calibrate_button, SIGNAL(clicked()), this, SLOT(doLambdaCalibration()));
	connect(clbrCalc_button, SIGNAL(clicked()), this, SLOT(go2lambda()));

	gauss->click();

	cnct_id = 0; // идентификатор установлени€ св€зи сигналов


/*	Param.setlen(5);

	gradFun.fsetlen(Param.N);
	hessFun.setSize(Param.N, Param.N);

	hesserr.setSize(Param.N, Param.N);
	graderr.fsetlen(Param.N);*/
}

void ClbrWidget::setCalibrData(vec4FMushort * Dat, int y1, int y2)
{
	FullMatrix<unsigned short> R, G1,G2,G3, B;
	int len,ym;
	QImage l_Img;
	
	if (y1 > y2) 
	{
		len = y1;
		y1 = y2;
		y2 = len;
	}
	if (y1 == y2) if (y2 < Dat->x[0].ny - 1) y2++; else if (y1 > 0) y1--; else return;
	len = Dat->x[0].nx - 1;
	// выделение рабочей части изображени€
	R.getSub (Dat->x[0], y1, y2, 0, len);
	G1.getSub(Dat->x[1], y1, y2, 0, len);
	B.getSub (Dat->x[2], y1, y2, 0, len);
	G2.getSub(Dat->x[3], y1, y2, 0, len);

	G3 = G1;
	G3.s += G2.s;
	G3.s /= 2.0;

	clbr_pic->setpicdata(R,G3,B,1);
	pxspln = clbr_pic->getlen();
	clbr_pic->setsz(pxspln, pxsphg);

	l_Img = clbr_pic->getPic();
	clbr_pic->setPic(l_Img.scaled(pxspln, pxsphg, Qt::IgnoreAspectRatio, Qt::FastTransformation));

	
	clbr_grf->setSelActText(tr("\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214\040\320\277\320\270\320\272\040\320\264\320\273\321\217\040\320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270"));//Select Peak
	clbr_grf->rsz_All(R.nx);
	
	clbr_grf->setFixedWidth(clbr_grf->get_lShift() + dw + pxspln - 1);
	ym = (y2-y1) / 2;

	vecdb ix(R.nx);

	ix.var1D_(0.0, 1.0,R.nx );
	//clbr_grf->setXdata(ix);
	clbr_grf->setXdata(0, ix);
	clbr_grf->setXdata(2, ix);
	ix += 0.5;
	clbr_grf->setXdata(1, ix);
	clbr_grf->setXdata(3, ix);

	clbr_grf->ZoomReset();

	memset(ix.x, 0, sizeof(double)*R.nx);
	for (int ii = 0;ii < R.ny;ii++)	{for (int jj = 0;jj < R.nx;jj++){	ix.x[jj] += R.x.x[ii][jj];	}}
	ix /= double(R.ny);
	clbr_grf->setYdata(0, ix);

	memset(ix.x, 0, sizeof(double)*G1.nx);
	for (int ii = 0;ii < G1.ny;ii++) { for (int jj = 0;jj < G1.nx;jj++) { ix.x[jj] += G1.x.x[ii][jj]; } }
	ix /= double(G1.ny);
	clbr_grf->setYdata(1, ix);

	memset(ix.x, 0, sizeof(double)*G2.nx);
	for (int ii = 0;ii < G2.ny;ii++) { for (int jj = 0;jj < G2.nx;jj++) { ix.x[jj] += G2.x.x[ii][jj]; } }
	ix /= double(G2.ny);
	clbr_grf->setYdata(2, ix);

	memset(ix.x, 0, sizeof(double)*B.nx);
	for (int ii = 0;ii < B.ny;ii++) { for (int jj = 0;jj < B.nx;jj++) { ix.x[jj] += B.x.x[ii][jj]; } }
	ix /= double(B.ny);
	clbr_grf->setYdata(3, ix);

	/*vecdb ixx;
	vecdb x0;
	vecdb L0;
	int a_, n_;
	a_ = 3;
	n_ = 10;
	x0.var1D(double(-a_), 1.0 / n_, double(a_));
	L0.lncz(x0, a_);  // вычисление контура сплайн-функции соответсвующей фильтру Ћанцоша
	ixx.Lanczos_interp( ix, n_, a_,x0,L0);*/

	/*
	for (int ii = 0;ii < R.nx;ii++) { ix.x[ii] = R.fst(ym, ii);	}
	clbr_grf->setYdata(0,ix);
	for (int ii = 0;ii < G1.nx;ii++) { ix.x[ii] = G1.fst(ym, ii); }
	clbr_grf->setYdata(1, ix);
	for (int ii = 0;ii < G2.nx;ii++) { ix.x[ii] = G2.fst(ym, ii); }
	clbr_grf->setYdata(2, ix);
	for (int ii = 0;ii < B.nx;ii++) { ix.x[ii] = B.fst(ym, ii); }
	clbr_grf->setYdata(3, ix);
	*/

	clbr_grf->setmnmx();
	clbr_grf->adpmnmx();
	clbr_grf->FrameSetUp();

	len = clbr_grf->dataLength() / pixScale;//2; //(clbr_grf->mnmx[1] - clbr_grf->mnmx[0]) / 2;
	clbr_grf->setFixedWidth(clbr_grf->get_lShift() + dw + len);

	update();

	//d->imgs = d->bigIm.scaled(320, 240, Qt::KeepAspectRatio, Qt::FastTransformation);

}

void ClbrWidget::setCalibrData(vec4FMushort * Dat, vec4T<vecdb>& cIS, int y1, int y2, int x1, int x2, int n_)
{
	FullMatrix<unsigned short> R, G1, G2, G3, B;
	int len;// , ym;
	QImage l_Img;

	if (y1 > y2)
	{
		len = y1;
		y1 = y2;
		y2 = len;
	}
	if (y1 == y2) if (y2 < Dat->x[0].ny - 1) y2++; else if (y1 > 0) y1--; else return;
	if (x1 > x2)
	{
		len = x1;
		x1 = x2;
		x2 = len;
	}
	if (x1 == x2) if (x2 < Dat->x[0].nx - 1) x2++; else if (x1 > 0) x1--; else return;
	//len = Dat->x[0].nx - 1;
	len = x2-x1+1; // длина 
	// выделение рабочей части изображени€
	R.getSub(Dat->x[0], y1, y2, x1, x2);
	G1.getSub(Dat->x[1], y1, y2, x1, x2);
	B.getSub(Dat->x[2], y1, y2, x1, x2);
	G2.getSub(Dat->x[3], y1, y2, x1, x2);

	G3 = G1;
	G3.s += G2.s;
	G3.s /= 2.0;

	clbr_pic->setpicdata(R, G3, B, 1);
	pxspln = clbr_pic->getlen();
	clbr_pic->setsz(pxspln, pxsphg);

	l_Img = clbr_pic->getPic();
	clbr_pic->setPic(l_Img.scaled(pxspln, pxsphg, Qt::IgnoreAspectRatio, Qt::FastTransformation));

	vecdb xx;
	xx.fsetlen((R.nx - 1)*n_ + 1);
	xx.var1D_(0.0, 1.0 / double(n_), (R.nx - 1)*n_ + 1);

	clbr_grf->setSelActText(tr("\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214\040\320\277\320\270\320\272\040\320\264\320\273\321\217\040\320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270"));//Select PeakSelect Peak"));
	clbr_grf->rsz_All(xx.N);

	//clbr_grf->xlabel(QString("\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\262 \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270 (x,y) [\320\277\320\270\321\201\320\272\320\265\320\273\320\270]"));
	clbr_grf->xlabel(QApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\262 \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270 (x,y) [\320\277\320\270\321\201\320\272\320\265\320\273\320\270]", 0));
	clbr_grf->ylabel(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 [\320\276\321\202\320\275. \320\265\320\264.]", 0));//tr("Int. a.u."));


	clbr_grf->setFixedWidth(clbr_grf->get_lShift() + dw + pxspln - 1);
//	ym = (y2 - y1) / 2;

	//vecdb ix(R.nx);

	//ix.var1D_(0.0, 1.0, R.nx);

	clbr_grf->setXdata(0, xx);
	clbr_grf->setXdata(2, xx);
	//xx += 0.5;
	clbr_grf->setXdata(1, xx);
	clbr_grf->setXdata(3, xx);

	clbr_grf->ZoomReset();

	clbr_grf->setYdata(0, cIS.x[0]);
	clbr_grf->setYdata(1, cIS.x[1]);
	clbr_grf->setYdata(2, cIS.x[2]);
	clbr_grf->setYdata(3, cIS.x[3]);

	clbr_grf->setmnmx();
	clbr_grf->adpmnmx();
	clbr_grf->FrameSetUp();

	len = clbr_grf->dataLength() / pixScale;//2; //(clbr_grf->mnmx[1] - clbr_grf->mnmx[0]) / 2;
	clbr_grf->setFixedWidth(clbr_grf->get_lShift() + dw + len);

	isClbrDone = 0;
	clbrTbl->setEnabled(true);
	dataTbl->setEnabled(false);

	connectionSetup();

	if ((idpix.N == lmbds.N) && (idpix.N > 3))
	{
		calibrate_button->setEnabled(true);
	}
	else
	{
		calibrate_button->setEnabled(false);
	}

	update();
}

void ClbrWidget::setPixelScale(int idSc)
{
	pixScale = idSc;
	clbr_pic->setPixelScale(idSc);
}

void ClbrWidget::setApptxTol(double toll)
{
	GssApprx.usr_eps = toll;
	LorApprx.usr_eps = toll;
	GarApprx.usr_eps = toll;
}

void ClbrWidget::setApptxNitr( int nitr)
{
	GssApprx.usr_Nittr = nitr;
	LorApprx.usr_Nittr = nitr;
	GarApprx.usr_Nittr = nitr;
}

void ClbrWidget::doLambdaCalibration()
{
	if ((lmbds.N == idpix.N) && (lmbds.N > 3))
	{
		GarApprx.setdata(lmbds, idpix);
		GarApprx.MinErrFind();
		if (isClbrDone == 0)
		{
			clbrCalc_button->setEnabled(true);
			isClbrDone = 1;
		}
	}
}

void ClbrWidget::go2lambda()
{
	vecdb xloc;
	vecdb yloc;
	vecdb dNdlmbd;
	vecint idns;

	xloc.fsetlen(clbr_grf->X().x[0].N);
	yloc.fsetlen(clbr_grf->X().x[0].N);
	idns.fsetlen(clbr_grf->X().x[0].N);
	dNdlmbd.fsetlen(clbr_grf->X().x[0].N);

	GarApprx.InvFun(clbr_grf->X().x[0],xloc);  // в xloc - длины волн посчитанные по калибровочным параметрам
	if (xloc.x[0] > xloc.last()) // массив 
	{
		idns.var1D_(xloc.N - 1, -1, xloc.N);
	}else
	{
		idns.var1D_(0, 1, xloc.N);
	}
	xloc.ind(idns, clbr_grf->X().x[0]);        // помен€ть пор€док массива x на обратный
	GarApprx.dFun(clbr_grf->X().x[0], dNdlmbd);
	dNdlmbd.vec_abs();
	yloc.pst(clbr_grf->Y().x[0]);
	yloc.ind(idns, clbr_grf->Y().x[0]);
	clbr_grf->Y().x[0] -= darkLevelR;
	clbr_grf->Y().x[0] *= dNdlmbd;
	//clbr_grf->setXdata(0, xloc);

	GarApprx.InvFun(clbr_grf->X().x[1], xloc);
	xloc.ind(idns, clbr_grf->X().x[1]);        // помен€ть пор€док массива x на обратный
	GarApprx.dFun(clbr_grf->X().x[1], dNdlmbd);
	dNdlmbd.vec_abs();
	yloc.pst(clbr_grf->Y().x[1]);
	yloc.ind(idns, clbr_grf->Y().x[1]);
	clbr_grf->Y().x[1] -= darkLevelG1;
	clbr_grf->Y().x[1] *= dNdlmbd;
	//clbr_grf->setXdata(1, xloc);

	GarApprx.InvFun(clbr_grf->X().x[2], xloc);
	xloc.ind(idns, clbr_grf->X().x[2]);        // помен€ть пор€док массива x на обратный
	GarApprx.dFun(clbr_grf->X().x[2], dNdlmbd);
	dNdlmbd.vec_abs();
	yloc.pst(clbr_grf->Y().x[2]);
	yloc.ind(idns, clbr_grf->Y().x[2]);
	clbr_grf->Y().x[2] -= darkLevelG2;
	clbr_grf->Y().x[2] *= dNdlmbd;
	//clbr_grf->setXdata(2, xloc);

	GarApprx.InvFun(clbr_grf->X().x[3], xloc);
	xloc.ind(idns, clbr_grf->X().x[3]);        // помен€ть пор€док массива x на обратный
	GarApprx.dFun(clbr_grf->X().x[3], dNdlmbd);
	dNdlmbd.vec_abs();
	yloc.pst(clbr_grf->Y().x[3]);
	yloc.ind(idns, clbr_grf->Y().x[3]);
	clbr_grf->Y().x[3] -= darkLevelB;
	clbr_grf->Y().x[3] *= dNdlmbd;
	//clbr_grf->setXdata(3, xloc);
	
	clbrCalc_button->setEnabled(false); // "выключаем" кнопку, чтобы не было повторного пересчЄта масштаба оси x
	calibrate_button->setEnabled(false);
	clbrTbl->setEnabled(false);
	dataTbl->setEnabled(true);

	clbr_grf->ZoomReset(); // сброс зума графика
	clbr_grf->setDfltMode();
	clbr_grf->xlabel(QString("\xD0\x94\xD0\xBB\xD0\xB8\xD0\xBD\xD0\xB0\x20\xD0\xB2\xD0\xBE\xD0\xBB\xD0\xBD\xD1\x8B  [\303\205]"));
	clbr_grf->ylabel(QString("\xD0\xA1\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0\xD0\xBB\xD1\x8C\xD0\xBD\xD0\xB0\xD1\x8F\x20\xD0\xBF\xD0\xBB\xD0\xBE\xD1\x82\xD0\xBD\xD0\xBE\xD1\x81\xD1\x82\xD1\x8C\x20\xD0\xB8\xD0\xBD\xD1\x82\xD0\xB5\xD0\xBD\xD1\x81\xD0\xB8\xD0\xB2\xD0\xBD\xD0\xBE\xD1\x81\xD1\x82\xD0\xB8\x20\x5B\xD1\x83\xD1\x81\xD0\xBB\x2E\xD0\xB5\xD0\xB4\x2E\x5D"));

	connectionSetup();

	update();
}

void ClbrWidget::connectionSetup()
{
	if (isClbrDone == 0)
	{
		if (cnct_id != 1)
		{
			disconnect(addPeakDataInClbrBtn, SIGNAL(clicked()), this, SLOT(aproxData2DataTable()));
			disconnect(addSelectDataInClbrBtn, SIGNAL(clicked()), this, SLOT(selectData2DataTable()));
			connect(addPeakDataInClbrBtn, SIGNAL(clicked()), this, SLOT(aproxData2ClbrTable()));
			connect(addSelectDataInClbrBtn, SIGNAL(clicked()), this, SLOT(selectData2ClbrTable()));
			cnct_id = 1;
		}
	}
	else
	{
		if (cnct_id != 2)
		{
			disconnect(addPeakDataInClbrBtn, SIGNAL(clicked()), this, SLOT(aproxData2ClbrTable()));
			disconnect(addSelectDataInClbrBtn, SIGNAL(clicked()), this, SLOT(selectData2ClbrTable()));
			connect(addPeakDataInClbrBtn, SIGNAL(clicked()), this, SLOT(aproxData2DataTable()));
			connect(addSelectDataInClbrBtn, SIGNAL(clicked()), this, SLOT(selectData2DataTable()));
			cnct_id = 2;
		}
	}
}


void ClbrWidget::addPeakData()
{
	vecdb xx;	// аргумент аппроксимирующей функции
	vecdb ff;	// значени€ аппроксимирующей функции

	if ((chanel_id >= 0) && (chanel_id <= 3))
	{
		if (clbr_grf->SelectedIds.x[chanel_id].N > 3)
		{
			xx.fsetlen(clbr_grf->SelectedIds.x[chanel_id].N);
			ff.fsetlen(clbr_grf->SelectedIds.x[chanel_id].N);

			clbr_grf->X().x[chanel_id].ind(clbr_grf->SelectedIds.x[chanel_id], xx); // выбор в xx значений агрумента выбранного диапазона
			clbr_grf->Y().x[chanel_id].ind(clbr_grf->SelectedIds.x[chanel_id], ff); // выбор в ff значений интесивности выбранного диапазона

			clbr_grf->fun_x1 = xx.x[0];
			clbr_grf->fun_x2 = xx.last();


			if (aprxtype == 0)
			{
				GssApprx.setdata(xx, ff);
				GssApprx.MinErrFind();

				fiterrdata->setText(QString().setNum(GssApprx.err, 'g', 6));

				fP_A->setText(QString().setNum(GssApprx.X.x[0], 'g', 6));
				fP_sgA->setText(QString().setNum(GssApprx.X_.x[0], 'g', 4));
				fP_B->setText(QString().setNum(GssApprx.X.x[1], 'g', 8));
				fP_sgB->setText(QString().setNum(GssApprx.X_.x[1], 'g', 4));
				fP_C->setText(QString().setNum(GssApprx.X.x[2], 'g', 8));
				fP_sgC->setText(QString().setNum(GssApprx.X_.x[2], 'g', 4));
				fP_D->setText(QString().setNum(GssApprx.X.x[3], 'g', 6));
				fP_sgD->setText(QString().setNum(GssApprx.X_.x[3], 'g', 4));
				fP_E->setText(QString().setNum(GssApprx.X.x[4], 'g', 6));
				fP_sgE->setText(QString().setNum(GssApprx.X_.x[4], 'g', 4));

				clbr_grf->setFundata();
			}
			else
			{
				LorApprx.setdata(xx, ff);
				LorApprx.MinErrFind();

				fiterrdata->setText(QString().setNum(LorApprx.err, 'g', 6));

				fP_A->setText(QString().setNum(LorApprx.X.x[0], 'g', 6));
				fP_sgA->setText(QString().setNum(LorApprx.X_.x[0], 'g', 4));
				fP_B->setText(QString().setNum(LorApprx.X.x[1], 'g', 8));
				fP_sgB->setText(QString().setNum(LorApprx.X_.x[1], 'g', 4));
				fP_C->setText(QString().setNum(LorApprx.X.x[2], 'g', 8));
				fP_sgC->setText(QString().setNum(LorApprx.X_.x[2], 'g', 4));
				fP_D->setText(QString().setNum(LorApprx.X.x[3], 'g', 6));
				fP_sgD->setText(QString().setNum(LorApprx.X_.x[3], 'g', 4));
				fP_E->setText(QString().setNum(LorApprx.X.x[4], 'g', 6));
				fP_sgE->setText(QString().setNum(LorApprx.X_.x[4], 'g', 4));

				clbr_grf->setFundata2();
			}
		}
	}
	/*SetGaussApproxFun();

	yy.fsetlen(xx.N);
	dy.fsetlen(xx.N);
	ddy.fsetlen(xx.N);
	hexp.fsetlen(xx.N);

	dataNormalize();

	Approx();*/
	//ii = clbr_grf->SelectedIds.N;
	//clbr_grf->SelectedIds();
}

void ClbrWidget::addXselData()
{
	slX = clbr_grf->selX;
	slDX = clbr_grf->selDX;

	slXTbl->setText(QString().setNum(slX, 'g', 6));
	slDXTbl->setText(QString().setNum(slDX, 'g', 4));

}

void ClbrWidget::aproxData2DataTable()
{

	//disconnect(dataTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2DataTable(QTableWidgetItem *)));
	if (lambda.N >= dataTbl->rowCount())
	{
		int rcn, rcn1;
		rcn = dataTbl->rowCount();
		rcn1 = rcn + 16;
		dataTbl->setRowCount(rcn1);
		QTableWidgetItem *hItm;
		for (int ii = rcn; ii < rcn1; ii++)
		{
			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 0, hItm);

			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 1, hItm);

			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 2, hItm);
		}
	}

	{
		double B, dB;
		if (aprxtype == 0)
		{
			B = GssApprx.X.x[1];
			dB = GssApprx.X_.x[1];
		}
		else
		{
			B = LorApprx.X.x[1];
			dB = LorApprx.X_.x[1];
		}

		lambda.add(B);
		sglambda.add(dB);
		
		QTableWidgetItem * tbItm;
		int idcur;
		idcur = lambda.N - 1;
		tbItm = dataTbl->item(idcur, 0);
		tbItm->setText(QString().setNum(B, 'g', 8));
		tbItm = dataTbl->item(idcur, 1);
		tbItm->setText(QString().setNum(dB, 'g', 4));
		tbItm = 0x0;
		//tbItm->setText(QString().setNum(B, 'g', 8));
	}
	//connect(dataTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2DataTable(QTableWidgetItem *)));

	update();

}

void ClbrWidget::selectData2DataTable()
{

	//(dataTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2DataTable(QTableWidgetItem *)));
	if (lambda.N >= dataTbl->rowCount())
	{
		int rcn, rcn1;
		rcn = dataTbl->rowCount();
		rcn1 = rcn + 16;
		dataTbl->setRowCount(rcn1);
		QTableWidgetItem *hItm;
		for (int ii = rcn; ii < rcn1; ii++)
		{
			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 0, hItm);

			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 1, hItm);

			hItm = new  QTableWidgetItem();
			dataTbl->setItem(ii, 2, hItm);
		}
	}

	lambda.add(clbr_grf->selX);
	sglambda.add(clbr_grf->selDX);

	QTableWidgetItem * tbItm;
	int idcur;
	idcur = lambda.N - 1;
	tbItm = dataTbl->item(idcur, 0);
	tbItm->setText(QString().setNum(slX, 'g', 8));
	tbItm = dataTbl->item(idcur, 1);
	tbItm->setText(QString().setNum(slDX, 'g', 4));
	tbItm = 0x0;

	//connect(dataTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2DataTable(QTableWidgetItem *)));

	update();

}

void  ClbrWidget::aproxData2ClbrTable()
{
	disconnect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	if (idpix.N >= clbrTbl->rowCount())
	{
		int rcn,rcn1;
		rcn = clbrTbl->rowCount();
		rcn1 = rcn + 16;
		clbrTbl->setRowCount(rcn1);
		QTableWidgetItem *hItm;
		for (int ii = rcn; ii < rcn1; ii++)
		{
			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 0, hItm);

			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 1, hItm);

			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 2, hItm);
		}
	}

	{
		double B, dB;
		if (aprxtype == 0)
		{
			B = GssApprx.X.x[1];
			dB = GssApprx.X_.x[1];
		}
		else
		{
			B = LorApprx.X.x[1];
			dB = LorApprx.X_.x[1];
		}

		idpix.add(B);
		sgpix.add(dB);
		if (idpix.N > lmbds.mN) lmbds.addmem();

		QTableWidgetItem * tbItm;
		int idcur;
		idcur = idpix.N - 1;
		tbItm = clbrTbl->item(idcur, 1);
		tbItm->setText(QString().setNum(B, 'g', 8));
		tbItm = clbrTbl->item(idcur, 2);
		tbItm->setText(QString().setNum(dB, 'g', 4));
		tbItm = 0x0;
		//tbItm->setText(QString().setNum(B, 'g', 8));
	}
	connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	if ((idpix.N == lmbds.N)&(idpix.N > 3))
	{
		calibrate_button->setEnabled(true);
	}else
	{
		calibrate_button->setEnabled(false);
	}
	update();
}

void ClbrWidget::selectData2ClbrTable()
{
	disconnect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	if (idpix.N >= clbrTbl->rowCount())
	{
		int rcn, rcn1;
		rcn = clbrTbl->rowCount();
		rcn1 = rcn + 16;
		clbrTbl->setRowCount(rcn1);
		QTableWidgetItem *hItm;
		for (int ii = rcn; ii < rcn1; ii++)
		{
			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 0, hItm);

			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 1, hItm);

			hItm = new  QTableWidgetItem();
			clbrTbl->setItem(ii, 2, hItm);
		}
	}

	idpix.add(clbr_grf->selX);
	sgpix.add(clbr_grf->selDX);
	if (idpix.N > lmbds.mN) lmbds.addmem();

	QTableWidgetItem * tbItm;
	int idcur;
	idcur = idpix.N - 1;
	tbItm = clbrTbl->item(idcur, 1);
	tbItm->setText(QString().setNum(slX, 'g', 8));
	tbItm = clbrTbl->item(idcur, 2);
	tbItm->setText(QString().setNum(slDX, 'g', 4));
	tbItm = 0x0;

	connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));

	if ((idpix.N == lmbds.N)&(idpix.N > 3))
	{
		calibrate_button->setEnabled(true);
	}else
	{
		calibrate_button->setEnabled(false);
	}
	update();
}

void  ClbrWidget::addData2ClbrTable(QTableWidgetItem *tbItm) // добавить данные в таблицу калибровки
{
	//if (istblclck)
	disconnect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	{
	//	istblclck = false;
		double x;
		int ix, iy;
		bool isok;
		ix = clbrTbl->column(tbItm);
		iy = clbrTbl->row(tbItm);

		isok = false;
		x = (tbItm->data(Qt::DisplayRole)).toDouble(&isok);

		if (isok)
		{
			switch (ix)
			{
			case 0:
				lmbds.setValue(x, iy);
				tbItm->setText(QString().setNum(x, 'g', 8));
				break;
			case 1:
				idpix.setValue(x, iy);
				tbItm->setText(QString().setNum(x, 'g', 8));
				break;
			case 2:
				sgpix.setValue(x, iy);
				tbItm->setText(QString().setNum(x, 'g', 4));
				break;
			}
		}
		else
		{// 
			vecT<double> *hx;
			int res;
			switch (ix)
			{
			case 0:
				lmbds.rem(1,iy);
				hx = &lmbds;
				res = 8;
				break;
			case 1:
				idpix.rem(1,iy);
				hx = &idpix;
				res = 8;
				break;
			case 2:
				sgpix.rem(1,iy);
				hx = &sgpix;
				res = 4;
				break;
			}
			tbItm->setData(Qt::DisplayRole, QVariant());
			for (int ii = iy; ii < hx->N; ii++)
			{
				if(hx->x[ii]!=0) clbrTbl->item(ii, ix)->setText(QString().setNum(hx->x[ii], 'g', res));
				else  clbrTbl->item(ii, ix)->setData(Qt::DisplayRole, QVariant());
			}
			if (clbrTbl->item(hx->N, ix)!=0) clbrTbl->item(hx->N, ix)->setData(Qt::DisplayRole, QVariant());
			hx = 0x0;
		}
	}
	connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));

	if ((idpix.N == lmbds.N)&(idpix.N > 3))
	{
		calibrate_button->setEnabled(true);
	}else
	{
		calibrate_button->setEnabled(false);
	}
	update();
	/*else
	 {
		bool isok;
		isok = false;
		(tbItm->data(Qt::DisplayRole)).toDouble(&isok);
		if (!isok) tbItm->setData(Qt::DisplayRole, QVariant());
	}*/
//	istblclck = false; 
}

void ClbrWidget::newClbTblPrc()
{
	// проверить есть-ли несохранЄнна€ таблица, сохраниеть, если така€ есть (или спросить нужно ли сохран€ть)
	idpix.N = 0;
	sgpix.N = 0;
	lmbds.N = 0;
	int nt;

	nt = clbrTbl->rowCount();
	for (int ii = 0; ii < nt; ii++)
	{
		clbrTbl->item(ii, 0)->setData(Qt::DisplayRole, QVariant());
		clbrTbl->item(ii, 1)->setData(Qt::DisplayRole, QVariant());
		clbrTbl->item(ii, 2)->setData(Qt::DisplayRole, QVariant());
	}
	calibrate_button->setEnabled(false);
}

void ClbrWidget::setClbTblPrc()
{
	FullMatrix<double> lClbMtr;

}

void ClbrWidget::getClbTblPrc()
{
}

void ClbrWidget::putClbrTbl2Clpbrd()
{
	QClipboard *clpbrd = QApplication::clipboard();

	int Nx;
	Nx = lmbds.N > idpix.N ? lmbds.N : idpix.N;
	Nx = Nx > sgpix.N ? Nx : sgpix.N;
	QString qstr;
	for (int ii=0;ii<Nx;ii++)
	{
		if (lmbds.N>ii)  qstr.append(QString().setNum(lmbds.x[ii], 'g', 16)); else  qstr.append(QString().setNum(0.0, 'g', 16));
		qstr.append(' ');
		if (idpix.N>ii) qstr.append(QString().setNum(idpix.x[ii], 'g', 16)); else  qstr.append(QString().setNum(0.0, 'g', 16));
		qstr.append(' ');
		if (sgpix.N>ii)  qstr.append(QString().setNum(sgpix.x[ii], 'g', 16)); else  qstr.append(QString().setNum(0.0, 'g', 16));
		qstr.append('\n');
	}
	clpbrd->setText(qstr);
}

void ClbrWidget::putClpbrd2ClbrTbl()
{
	QClipboard *clpbrd = QApplication::clipboard();
	const QMimeData *mimeData = clpbrd->mimeData();

	if (mimeData->hasText()) 
	{
		// анализ текста и заполение таблицы
		QString clpbrText; // дл€ хранени€ текста из буфера
		QString hlp,hlp1;
		QStringList strlist, numlist;
		FullMatrix<double> xmtr;
		QTableWidgetItem *hItm;

		int jm,jmx;
		double xloc;
		bool ok_;
		xmtr.setSize(50, 3);
		ok_ = false;
		clpbrText = clpbrd->text(); // из буфера в 'clpbrText'
		strlist = clpbrText.split(QChar('\n')); // разделить на строки
		jmx = 0;
		for (int ii = 0; ii < strlist.count(); ii++)
		{
			hlp1 = strlist.at(ii);
			numlist = hlp1.split(QChar(' ')); // разделить на слова, которые должны быть числами
			jm = 0;
			for (int jj = 0; ((jj < numlist.count())&&(jm<3)); jj++)
			{
				hlp = numlist.at(jj);
				xloc = hlp.toDouble(&ok_);
				if (ok_)
				{
					xmtr.set(ii, jm) = xloc;
					jm++;
					jmx = jmx < ii ? ii : jmx;
				}
			}
		}

		if (jmx>0)
		{
			jmx++;
			ClearClbrTbl();

			disconnect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));

			idpix.fsetlen(jmx);
			sgpix.fsetlen(jmx);
			lmbds.fsetlen(jmx);

			int ix;// , ix1;
			ix = clbrTbl->rowCount();
			if (ix < jmx)
			{
				clbrTbl->setRowCount(jmx);
				for (int ii = ix; ii < jmx; ii++)
				{
					hItm = new  QTableWidgetItem();
					clbrTbl->setItem(ii, 0, hItm);

					hItm = new  QTableWidgetItem();
					clbrTbl->setItem(ii, 1, hItm);

					hItm = new  QTableWidgetItem();
					clbrTbl->setItem(ii, 2, hItm);
				}
			}

			for (int ii = 0; ii < jmx; ii++)
			{
				lmbds.x[ii] = xmtr.fst(ii, 0);
				idpix.x[ii] = xmtr.fst(ii, 1);
				sgpix.x[ii] = xmtr.fst(ii, 2);

				clbrTbl->item(ii, 0)->setData(Qt::DisplayRole, QVariant(lmbds.x[ii]));
				clbrTbl->item(ii, 1)->setData(Qt::DisplayRole, QVariant(idpix.x[ii]));
				clbrTbl->item(ii, 2)->setData(Qt::DisplayRole, QVariant(sgpix.x[ii]));
			}

			connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));

			if ((idpix.N == lmbds.N)&(idpix.N > 3))
			{
				calibrate_button->setEnabled(true);
			}else
			{
				calibrate_button->setEnabled(false);
			}
			update();
		}
	}
}

void ClbrWidget::ClearClbrTbl()
{
	disconnect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	int Nx;
	Nx = clbrTbl->rowCount();
	for (int ii = 0; ii < Nx; ii++)
	{
		clbrTbl->item(ii, 0)->setData(Qt::DisplayRole, QVariant());
		clbrTbl->item(ii, 1)->setData(Qt::DisplayRole, QVariant());
		clbrTbl->item(ii, 2)->setData(Qt::DisplayRole, QVariant());
	}
	idpix.N = 0;
	sgpix.N = 0;
	lmbds.N = 0;
	connect(clbrTbl, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(addData2ClbrTable(QTableWidgetItem *)));
	calibrate_button->setEnabled(false);
}

void ClbrWidget::putDataTbl2Clpbrd()
{
	QClipboard *clpbrd = QApplication::clipboard();
	int Nx;
	Nx = lambda.N > sglambda.N ? lambda.N : sglambda.N;
	QString qstr;
	for (int ii = 0; ii<Nx; ii++)
	{
		if (lambda.N>ii)  qstr.append(QString().setNum(lambda.x[ii], 'g', 16)); else  qstr.append(QString().setNum(0.0, 'g', 16));
		qstr.append(' ');
		if (sglambda.N>ii) qstr.append(QString().setNum(sglambda.x[ii], 'g', 16)); else  qstr.append(QString().setNum(0.0, 'g', 16));
		qstr.append('\n');
	}
	clpbrd->setText(qstr);
}

void ClbrWidget::putClpbrd2DaTbl()
{
}

void ClbrWidget::ClearDataTbl()
{
	int Nx;
	Nx = dataTbl->rowCount();
	for (int ii = 0; ii < Nx; ii++)
	{
		dataTbl->item(ii, 0)->setData(Qt::DisplayRole, QVariant());
		dataTbl->item(ii, 1)->setData(Qt::DisplayRole, QVariant());
	}
	lambda.N = 0;
	sglambda.N = 0;
}

/*
void ClbrWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);

	//clbr_grf->paintEvent(event);


	painter.end();
	event->accept();
}*/

/*
void ClbrWidget::SetGaussApproxFun()
{


	Fun = aFn;

	gradFun.x[0] = grdFn1;
	gradFun.x[1] = grdFn2;
	gradFun.x[2] = grdFn3;
	gradFun.x[3] = grdFn4;
	gradFun.x[4] = grdFn5;

	hessFun.fst(0, 0) = hssFn11;
	hessFun.fst(1, 0) = hessFun.fst(0, 1) = hssFn12;
	hessFun.fst(2, 0) = hessFun.fst(0, 2) = hssFn13;
	hessFun.fst(3, 0) = hessFun.fst(0, 3) = hssFn14;
	hessFun.fst(4, 0) = hessFun.fst(0, 4) = hssFn15;

	hessFun.fst(1, 1) = hssFn22;
	hessFun.fst(2, 1) = hessFun.fst(1, 2) = hssFn23;
	hessFun.fst(3, 1) = hessFun.fst(1, 3) = hssFn24;
	hessFun.fst(4, 1) = hessFun.fst(1, 4) = hssFn25;

	hessFun.fst(2, 2) = hssFn33;
	hessFun.fst(3, 2) = hessFun.fst(2, 3) = hssFn34;
	hessFun.fst(4, 2) = hessFun.fst(2, 4) = hssFn35;

	hessFun.fst(3, 3) = hssFn44;
	hessFun.fst(4, 3) = hessFun.fst(3, 4) = hssFn45;
	
	hessFun.fst(4, 4) = hssFn55;

}

void ClbrWidget::ErrFun()
{
	Fun(Param, xx, yy);
	yy -= ff;
	err = yy.snrm();
}

void ClbrWidget::GradFun()
{
	Fun(Param, xx, yy);
	yy -= ff;
	for(int ii = 0;ii < graderr.N;ii++)
	{
		gradFun.x[ii](Param, xx, dy);
		graderr.x[ii] = 2*yy.scpr(dy)/yy.N;
	}
}

void ClbrWidget::HessFun()
{
	Fun(Param, xx, yy);
	yy -= ff;
	for (int ii = 0;ii < hesserr.ny;ii++)
	{
		gradFun.x[ii](Param, xx, dy);
		for (int jj = 0;jj < ii;jj++)
		{
			gradFun.x[jj](Param, xx, ddy);
			hesserr.fst(ii, jj) = dy.scpr(ddy);
			hessFun.fst(ii, jj)(Param, xx, ddy);
			hesserr.fst(ii,jj) += yy.scpr(ddy);
			hesserr.fst(jj, ii) = hesserr.fst(ii, jj) *= 2.0/yy.N;
		}
		hesserr.fst(ii, ii) = dy.ssqr();
		hessFun.fst(ii, ii)(Param, xx, ddy);
		hesserr.fst(ii, ii) += yy.scpr(ddy);
		hesserr.fst(ii, ii) *= 2.0/yy.N;
	}
}
void ClbrWidget::dataNormalize()
{
	double mx, mn;

	mx = xx.max();
	mn = xx.min();

	k_x = 2.0 / (mx-mn);
	b_x = (mx+mn) / (mn-mx);

	mx = ff.max();
	mn = ff.min();

	k_y = 1. / (mx - mn);
	b_y = mn / (mn - mx);

	xx *= k_x;
	xx += b_x;

	ff *= k_y;
	ff += b_y;


}
void ClbrWidget::Approx()
{


	Param.x[4] = (ff.x[0] + ff.x[ff.N - 1]) / 2;
	Param.x[3] = (ff.x[ff.N - 1] - ff.x[0]) / 2;
	Param.x[0] = 1.0 - Param.x[4];
	Param.x[1] = 0.;
	Param.x[2] = 0.25;

	vecdb Pk,Sk,Rk,Sk_,Rk_;
	double lmb,eps,wk;

	Pk.fsetlen(Param.N);
	Sk.fsetlen(Param.N);
	Rk.fsetlen(Param.N);
	Sk_.fsetlen(Param.N);
	Rk_.fsetlen(Param.N);

	Pk = Param;
	GradFun();
	Rk_ = Sk_ = -graderr;
	HessFun();

	lmb = Sk_.ssqr() / (Sk_.scpr(hesserr * Sk_));
	Param = Pk += Sk_ * lmb;

	eps = (Rk_.snrm());
	int kk = 0;
	while (eps > 1e-10)
	{
		GradFun();
		Rk = -graderr;
		wk = Rk.ssqr() / Rk_.ssqr();
		Sk = Rk + Sk_*wk;
		HessFun();
		lmb = (Rk.scpr(Sk)) / (Sk.scpr(hesserr * Sk));
		Pk = Param + Sk*lmb;
		Param = Pk;
		Sk_ = Sk;
		Rk_ = Rk;
		eps = Rk.snrm();
		kk++;
	}
}*/
/*
void ClbrWidget::aFn(const vecdb & Prm, const vecdb & x, const vecdb & y)
{
	double h1;
	for (int ii = 0;ii < x.N;ii++)
	{
		h1 = (x.x[ii] - Prm.x[1]) / Prm.x[2];
		h1 *= h1;
		y.x[ii] = Prm.x[0] * exp(-h1) + Prm.x[3] * x.x[ii] + Prm.x[4];
	}
}
*/

#endif


