#ifndef MAINWIN_CPP
#define MAINWIN_CPP

#include <QPaintEvent>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextDocument>

#include "ui_gui_.h"
#include "mainwin.h"
//#include "linalg.cpp"
#include "linalg.h"
#include "picview.h"
#include "plotgraph.h"
#include "prevw.h"
#include "calibration.h"


MainWin::MainWin()
{
	//Ui::MainWindow *guiWin;
	guiWin = new Ui::MainWindow;

	guiWin->setupUi(this);
	
	connect(guiWin->actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(guiWin->action_FullFrame, SIGNAL(triggered()), this, SLOT(saveFullPic()));
	connect(guiWin->action_SelFrame, SIGNAL(triggered()), this, SLOT(saveSlctFrm()));

	connect(guiWin->actionClbTbl, SIGNAL(triggered()), this, SLOT(exportClbrTbl()));
	connect(guiWin->actionSpCurve, SIGNAL(triggered()), this, SLOT(exportCurvLns()));
	connect(guiWin->actionClbGrph, SIGNAL(triggered()), this, SLOT(exportClbtGrf()));
	connect(guiWin->actionCurSpectr, SIGNAL(triggered()), this, SLOT(exportCurSpct()));

	connect(guiWin->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
	connect(guiWin->actionWholeDescr, SIGNAL(triggered()), this, SLOT(helpsummary()));
	connect(guiWin->actionImrvLsDescr, SIGNAL(triggered()), this, SLOT(helpstrline()));
	connect(guiWin->actionClbrDescr, SIGNAL(triggered()), this, SLOT(helpcalibrt()));
	connect(guiWin->actionLnDestDescr, SIGNAL(triggered()), this, SLOT(helpspctlns()));


	guiWin->action_WorkFrame->setEnabled(false);
	guiWin->action_WorlFrClbr->setEnabled(false);

	actionAbout = guiWin->actionAbout;
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(AboutMsg()));
	connect(guiWin->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(AboutMsgQt()));

	actionOpenImage	= guiWin->actionOpen_Image_Data_File;
	actionOpenImage->setStatusTip(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 *.cr2 \321\204\320\260\320\271\320\273", 0 ));//tr("Load *.cr2 raw file"));
	connect(actionOpenImage,SIGNAL(triggered()), this, SLOT(openImageFile()));

	//actionExit		= guiWin->actionExit;
	actionSaveProject = guiWin->actionSave_Prj;

	actionSaveBin	= guiWin->actionSave_Binary_Data;
	actionSaveBin->setStatusTip(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214\040\320\264\320\260\320\275\320\275\321\213\320\265\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217\040\320\262\040\320\262\320\270\320\264\320\265\040\064\055\321\221\321\205\040\321\204\320\260\320\271\320\273\320\276\320\262\040\050\122\040\107\040\107\040\102\051\040\320\262\040\320\261\320\270\320\275\320\260\321\200\320\275\320\276\320\274\040\320\262\320\270\320\264\320\265\040\050\061\066\040\320\261\320\270\321\202\040\320\275\320\260\040\320\277\320\270\320\272\321\201\320\265\320\273\321\214\051", 0 ));//tr("Load *.cr2 raw file"));
	connect(actionSaveBin,SIGNAL(triggered()), this, SLOT(SaveBinFile()));

	actionLinInterp = guiWin->actionLinearInterp;
	connect(actionLinInterp, SIGNAL(triggered()), this, SLOT(setLinearInterp()));
	actionDbLszInrp = guiWin->actionDblLancszInterp;
	connect(actionDbLszInrp, SIGNAL(triggered()), this, SLOT(setDblLszInterp()));
	actionCubInterp = guiWin->actionCubicInterp;
	connect(actionCubInterp, SIGNAL(triggered()), this, SLOT(setCubicInterp()));

	actionInterpInt_1 = guiWin->action_nbInt_1;
	actionInterpInt_3 = guiWin->action_nbInt_3;
	actionInterpInt_5 = guiWin->action_nbInt_5;
	actionInterpInt_10 = guiWin->action_nbInt_10;
	actionInterpInt_20 = guiWin->action_nbInt_20;

	connect(actionInterpInt_1, SIGNAL(triggered()), this, SLOT(setNmbrInterp1()));
	connect(actionInterpInt_3, SIGNAL(triggered()), this, SLOT(setNmbrInterp3()));
	connect(actionInterpInt_5, SIGNAL(triggered()), this, SLOT(setNmbrInterp5()));
	connect(actionInterpInt_10, SIGNAL(triggered()), this, SLOT(setNmbrInterp10()));
	connect(actionInterpInt_20, SIGNAL(triggered()), this, SLOT(setNmbrInterp20()));

	galcaIcon = new QIcon(QString("galka2.png"));
	actionInterpInt_10->setIcon(*galcaIcon);
	actionLinInterp->setIcon(*galcaIcon);

	m_line = -1;
	beg_line = -1;
	end_line = -1;
	n_interp = 10;// actionInterpInt_10

	interpolator = new Interpolator();
	interpolator->SetDblLncz(n_interp);

	QVBoxLayout * vbox11;
	QHBoxLayout *hbox11, *hbox12, *hbox13;

	PxSc = 3;
	PxGrSc = 2; // множтель для размера графика (аналогичен PxSc)

	size_setup_box  = new QDialog(this);
	okImSizeBtn = new QPushButton(this);
	okImSizeBtn->setText(QString("Ok"));

	QLabel *label_Px,*label_PxGr,*label_all;
	label_all = new QLabel(QString("\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\275\321\213\320\271\040\320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\072"));// \320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213\040\320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217:"));
	label_Px   = new QLabel(QString("\320\224\320\273\321\217\040\321\200\320\260\320\261\320\276\321\207\320\265\320\263\320\276\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217\072\040"));
	label_PxGr = new QLabel(QString("\320\224\320\273\321\217\040\320\263\321\200\320\260\321\204\320\270\320\272\320\260\040\321\201\320\277\320\265\320\272\321\202\321\200\320\276\320\262\072\040"));

	hbox11 = new QHBoxLayout();// size_setup_box);
	hbox12 = new QHBoxLayout();// size_setup_box);
	hbox13 = new QHBoxLayout();// size_setup_box);

	spBox_1 = new QSpinBox();// size_setup_box);
	spBox_1->setMinimum(1);
	spBox_1->setMaximum(10);
	spBox_1->setValue(PxSc);
	spBox_2 = new QSpinBox();// size_setup_box);
	spBox_2->setMinimum(1);
	spBox_2->setMaximum(10);
	spBox_2->setValue(PxGrSc);

	hbox13->addWidget(label_all);
    hbox13->addStretch();

	hbox11->addWidget(label_Px);
	hbox11->addWidget(spBox_1);

	hbox12->addWidget(label_PxGr);
	hbox12->addWidget(spBox_2);

	vbox11 = new QVBoxLayout(size_setup_box);
	vbox11->addLayout(hbox13);
	//vbox11->addWidget(label_all);
	vbox11->addLayout(hbox11);
	vbox11->addLayout(hbox12);
	vbox11->addWidget(okImSizeBtn);

	size_setup_box->setLayout(vbox11);

	connect(guiWin->actionSizeSetup, SIGNAL(triggered()), size_setup_box, SLOT(exec()));
	connect(spBox_1, SIGNAL(valueChanged(int)), this, SLOT(setPxSc(int)));
	connect(spBox_2, SIGNAL(valueChanged(int)), this, SLOT(setPxGrSc(int)));
	connect(size_setup_box, SIGNAL(rejected()), this, SLOT(updtpics()));
	connect(okImSizeBtn, SIGNAL(clicked()), this, SLOT(updtpics()));
	connect(okImSizeBtn, SIGNAL(clicked()), size_setup_box, SLOT(close()));





	approx_setup_box = new QDialog(this); // окошко для настройки параметров аппроксимации

	okApprxParBtn = new QPushButton(this); // кнопка ok в окошке параметров аппроксимации
	okApprxParBtn->setText(QString("Ok"));

	QLabel *label_ApprxNittr, *label_ApprxTol, *alabel_all;
	alabel_all = new QLabel(QString("\xD0\x9F\xD0\xB0\xD1\x80\xD0\xB0\xD0\xBC\xD0\xB5\xD1\x82\xD1\x80\xD1\x8B\x20\xD0\xBE\xD1\x81\xD1\x82\xD0\xB0\xD0\xBD\xD0\xBE\xD0\xB2\xD0\xB0\x20\xD0\xBE\xD0\xBF\xD1\x82\xD0\xB8\xD0\xBC\xD0\xB8\xD0\xB7\xD0\xB8\xD1\x80\xD1\x83\xD1\x8E\xD1\x89\xD0\xB8\xD1\x85\x20\xD0\xB0\xD0\xBB\xD0\xB3\xD0\xBE\xD1\x80\xD0\xB8\xD1\x82\xD0\xBC\xD0\xBE\xD0\xB2\x20\xD0\xBC\xD0\xB5\xD1\x82\xD0\xBE\xD0\xB4\xD0\xB0\x0A\xD0\xBD\xD0\xB0\xD0\xB8\xD0\xBC\xD0\xB5\xD0\xBD\xD1\x8C\xD1\x88\xD0\xB8\xD1\x85\x20\xD0\xBA\xD0\xB2\xD0\xB0\xD0\xB4\xD1\x80\xD0\xB0\xD1\x82\xD0\xBE\xD0\xB2\x2E\x20\x28\xD0\x98\xD1\x81\xD0\xBF\xD0\xBE\xD0\xBB\xD1\x8C\xD0\xB7\xD1\x83\xD1\x8E\xD1\x82\xD1\x81\xD1\x8F\x20\xD0\xB4\xD0\xBB\xD1\x8F\x20\xD0\xB0\xD0\xBF\xD0\xBF\xD1\x80\xD0\xBE\xD0\xBA\xD1\x81\xD0\xB8\xD0\xBC\xD0\xB0\xD1\x86\xD0\xB8\xD0\xB8\x20\x0A\xD1\x81\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0\xD0\xBB\xD1\x8C\xD0\xBD\xD1\x8B\xD1\x85\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD0\xBE\xD0\xB2\x20\xD0\xB8\x20\xD0\xB2\xD1\x8B\xD1\x87\xD0\xB8\xD1\x81\xD0\xBB\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB8\x20\xD0\xBA\xD0\xBE\xD1\x8D\xD1\x84\xD1\x84\xD0\xB8\xD1\x86\xD0\xB8\xD0\xB5\xD0\xBD\xD1\x82\xD0\xBE\xD0\xB2\x20\xD0\xBA\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBA\xD0\xB8\x29\x2E")); // параметры оптимизатора аппроксиматоров
 	label_ApprxNittr = new QLabel(QString("\xD0\x9C\xD0\xB0\xD0\xBA\xD1\x81\xD0\xB8\xD0\xBC\xD0\xB0\xD0\xBB\xD1\x8C\xD0\xBD\xD0\xBE\xD0\xB5\x20\xD0\xBA\xD0\xBE\xD0\xBB\xD0\xB8\xD1\x87\xD0\xB5\xD1\x81\xD1\x82\xD0\xB2\xD0\xBE\x20\xD0\xB8\xD1\x82\xD0\xB5\xD1\x80\xD0\xB0\xD1\x86\xD0\xB8\xD0\xB9\x3A")); // Максимальное количество иттраций (10-10000)
	label_ApprxTol = new QLabel(QString("\xD0\x97\xD0\xBD\xD0\xB0\xD1\x87\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xBD\xD0\xB5\xD0\xB2\xD1\x8F\xD0\xB7\xD0\xBA\xD0\xB8\x20\x28\x31\x65\x2D\x33\x20\x2E\x2E\x20\x31\x65\x2D\x31\x33\x29\x3A")); // максимальная невязка (1e-3 - 1e-15)


	usr_eps = 1e-10; // устанавливаемая пользователем невязка 
	usr_Nittr = 100; // устанавливаемое пользователем максимальное число иттераций 



	QVBoxLayout * avbox11;
	QHBoxLayout *ahbox11, *ahbox12, *ahbox13;

	ahbox11 = new QHBoxLayout();// size_setup_box);
	ahbox12 = new QHBoxLayout();// size_setup_box);
	ahbox13 = new QHBoxLayout();// size_setup_box);

	spBox_tol = new QDoubleSpinBox();// size_setup_box);
	spBox_tol->setMinimum(1e-13);
	spBox_tol->setMaximum(1e-3);	
	spBox_tol->setDecimals(16);
	spBox_tol->setValue(usr_eps);
	//spBox_tol->setSingleStep(usr_eps / 2.0);


	spBox_Nittr = new QSpinBox();// size_setup_box);
	spBox_Nittr->setMinimum(10);
	spBox_Nittr->setMaximum(1000);
	spBox_Nittr->setValue(usr_Nittr);

	ahbox13->addWidget(alabel_all);
	ahbox13->addStretch();

	ahbox11->addWidget(label_ApprxTol);
	ahbox11->addWidget(spBox_tol);

	ahbox12->addWidget(label_ApprxNittr);
	ahbox12->addWidget(spBox_Nittr);

	avbox11 = new QVBoxLayout(approx_setup_box);
	avbox11->addLayout(ahbox13);
	//vbox11->addWidget(label_all);
	avbox11->addLayout(ahbox11);
	avbox11->addLayout(ahbox12);
	avbox11->addWidget(okApprxParBtn);

	approx_setup_box->setLayout(avbox11);

	connect(guiWin->actionApprox, SIGNAL(triggered()), approx_setup_box, SLOT(exec()));
	connect(spBox_tol, SIGNAL(valueChanged(double)), this, SLOT(setTol(double)));
	connect(spBox_Nittr, SIGNAL(valueChanged(int)), this, SLOT(setNittr(int)));
	connect(okApprxParBtn, SIGNAL(clicked()), approx_setup_box, SLOT(close()));

	



	tabWidget = new QTabWidget();

	tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	tabWidget->setEnabled(true);

	tabWidget->setTabPosition(QTabWidget::North);
	tabWidget->setTabShape(QTabWidget::Rounded);
	tabWidget->setElideMode(Qt::ElideNone);
	tabWidget->setUsesScrollButtons(false);
	tabWidget->setDocumentMode(false);
	tabWidget->setTabsClosable(false);
	tabWidget->setMovable(true);


	iiMdl = new ImageIconModel(this);

	/*tblVw = new QTableView();
	
	
	tblVw->setShowGrid(false);
	tblVw->verticalHeader()->hide();
	tblVw->horizontalHeader()->hide();
	tblVw->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
	tblVw->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	tblVw->horizontalHeader()->setMinimumSectionSize(336);
	tblVw->horizontalHeader()->setDefaultSectionSize(336);
	tblVw->verticalHeader()->setMinimumSectionSize(272);
	tblVw->verticalHeader()->setDefaultSectionSize(272);
	tblVw->setModel(iiMdl);*/

	lstVw = new ListView(this);
	lstVw->setViewMode(QListView::IconMode);
	lstVw->setWrapping(true);
	lstVw->setFlow(QListView::LeftToRight);
	lstVw->setSpacing(5);
	//lstVw->setGridSize(QSize(330,300));
	lstVw->setResizeMode(QListView::Adjust);
	lstVw->setModel(iiMdl);

	iiDlg = new ImageIconDelegate();

	lstVw->setItemDelegate(iiDlg);

	tabWidget->addTab(lstVw,QString(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\266\320\265\320\275\320\275\321\213\320\265\040\321\201\320\277\320\265\320\272\321\202\321\200\321\213", 0 )));// загруженные спектры

	pvw = new PicView;
	pvw->setpnts(0.1,0.1,0.9,0.9);
	pvw->settype(1);
	pvw->setPixelScale(PxSc);
//	pFllScrn = new PicView;
	//tabWidget->addTab(pvw,QString());
	//tabWidget->addTab();

	plt1D = new PlotGraph();

	plt1D->setNgrphx(4); // установка количества графиков - 4 красный, зелёный, синий, зелёный


	setHln = new QPushButton(QString(QApplication::translate("MainWindow", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\320\276\320\265 \320\262\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265", 0 )));
	setVln = new QPushButton(QString(QApplication::translate("MainWindow", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\320\276\320\265 \320\262\321\213\321\200\320\260\320\262\320\275\320\270\320\262\320\260\320\275\320\270\320\265", 0 )));
	setCM  = new QPushButton(QString(QApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0 )));; // центрирование по центру масс

	row_sum = new QPushButton(QString(QApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265  \320\277\320\276  \321\201\321\202\321\200\320\276\320\272\320\260\320\274", 0 )));; // суммирование по строкам
	col_sum = new QPushButton(QString(QApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\320\276 \321\201\321\202\320\276\320\273\320\261\321\206\320\260\320\274", 0 )));; // суммирование по столбцам


	setDarkLevelBtn = new QPushButton(QString(QApplication::translate("MainWindow", "\xD0\xA3\xD1\x81\xD1\x82\xD0\xB0\xD0\xBD\xD0\xBE\xD0\xB2\xD0\xB8\xD1\x82\xD1\x8C\x20\xD1\x83\xD1\x80\xD0\xBE\xD0\xB2\xD0\xB5\xD0\xBD\xD1\x8C\x20\xD1\x82\xD0\xB5\xD0\xBC\xD0\xBD\xD0\xBE\xD0\xB2\xD0\xBE\xD0\xB3\xD0\xBE\x20\xD1\x84\xD0\xBE\xD0\xBD\xD0\xB0", 0)));; // установка темнового фона;
	isDarkLevel = false;

	clbr_button = new QPushButton(QString(QApplication::translate("MainWindow", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\321\213\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200", 0 )));//Send to calibration
	clbr_button->setEnabled(false);


	imprn_lines_btn = new QPushButton(QString(QApplication::translate("MainWindow", "\042\320\230\321\201\320\277\321\200\320\260\320\262\320\270\321\202\321\214\042\040\320\273\320\270\320\275\320\270\320\270", 0))); // Improve lines
	imprn_lines_btn->setEnabled(false);

	set_work_frame_btn = new QPushButton(QString(QApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214\040\321\200\320\260\320\261\320\276\321\207\321\203\321\216\040\320\276\320\261\320\273\320\260\321\201\321\202\321\214", 0)));//Setup work area
	set_work_frame_btn->setEnabled(false);

	work_spectr_button = new QPushButton(QString(QApplication::translate("MainWindow", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214\040\321\200\320\260\320\261\320\276\321\207\320\270\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200", 0))); // Send to spectr
	work_spectr_button->setEnabled(false);

	QGroupBox *grp1 = new QGroupBox(tr("\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260\040\321\200\320\260\320\261\320\276\321\207\320\265\320\271\040\320\276\320\261\320\273\320\260\321\201\321\202\320\270"));//Tune the work region

	QGroupBox *grp2 = new QGroupBox(tr("\320\240\320\260\320\274\320\272\320\260\040\320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\321\217\040\320\277\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\276\320\271\040\320\276\320\261\320\273\320\260\321\201\321\202\320\270"));//Параметры рамки выделения

	QGroupBox *grp3 = new QGroupBox(tr("\320\244\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265\040\320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262\040\321\201\320\277\320\265\320\272\321\202\321\200\320\276\320\262"));//Параметры рамки выделения


	QWidget *wdg;
	wdg = new QWidget();
	
	QHBoxLayout * hbox1,*hbox2,*hbox3,*hbox4,*hbox5,*hbox6;
	QVBoxLayout * vbox1,*vbox0,*vbox2;

	hbox1 = new QHBoxLayout();
	hbox2 = new QHBoxLayout();
	hbox3 = new QHBoxLayout();
	hbox4 = new QHBoxLayout();
	hbox5 = new QHBoxLayout();
	hbox6 = new QHBoxLayout();
	vbox0 = new QVBoxLayout();
	vbox1 = new QVBoxLayout();
	vbox2 = new QVBoxLayout();

	str_p1 = new QLabel(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 (x1,y1) \321\202\320\276\321\207\320\272\320\270 \342\204\2261 :", 0 ));
	str_p2 = new QLabel(QApplication::translate("MainWindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 (x2,y2) \321\202\320\276\321\207\320\272\320\270 \342\204\2262 :", 0 ));
	str_CM_xy = new QLabel(QApplication::translate("MainWindow", "(xc,yc) : ", 0 ));
	str_p3 = new QLabel(QApplication::translate("MainWindow", "| (Dx,Dy): ", 0 ));

	data_x1 = new QLineEdit();
	data_x1->setMaxLength(4);
	data_x1->setMaximumWidth(30);
	data_y1 = new QLineEdit();
	data_y1->setMaxLength(4);
	data_y1->setMaximumWidth(30);

	data_x2 = new QLineEdit();
	data_x2->setMaxLength(4);
	data_x2->setMaximumWidth(30);
	data_y2 = new QLineEdit();
	data_y2->setMaxLength(4);
	data_y2->setMaximumWidth(30);
	data_dx = new QLineEdit();
	data_dx->setMaxLength(4);
	data_dx->setMaximumWidth(30);
	data_dx->setReadOnly(true);
	data_dy = new QLineEdit();
	data_dy->setMaxLength(4);
	data_dy->setMaximumWidth(30);
	data_dy->setReadOnly(true);

	//data_x1->setInputMask(QString("9999"));
	
	hbox1->addWidget(str_p1);
	hbox1->addWidget(data_x1);
	hbox1->addWidget(data_y1);
	hbox1->addStretch();

	hbox4->addWidget(setVln);
	hbox4->addWidget(setHln);
	hbox4->addStretch();
		
	hbox2->addWidget(str_p2);
	hbox2->addWidget(data_x2);
	hbox2->addWidget(data_y2);
	hbox2->addStretch();

	hbox5->addWidget(setCM);
	hbox5->addWidget(str_CM_xy);
	hbox5->addWidget(str_p3);
	hbox5->addWidget(data_dx);
	hbox5->addWidget(data_dy);
	hbox5->addStretch();


	hbox6->addWidget(imprn_lines_btn);
	hbox6->addWidget(set_work_frame_btn);
	grp1->setLayout(hbox6);
	grp1->setFixedWidth(350);
	

	hbox3->addWidget(row_sum);
	//hbox3->addStretch();
	hbox3->addWidget(col_sum);
	

	hbox3->addStretch();
		
	vbox0->addLayout(hbox1);
	vbox0->addLayout(hbox2);
	vbox0->addLayout(hbox5);
	vbox0->addLayout(hbox4);
	vbox0->addLayout(hbox3);
	vbox0->addWidget(setDarkLevelBtn);
	grp2->setLayout(vbox0);
	grp2->setFixedWidth(350);
	vbox2->addWidget(clbr_button);
	vbox2->addWidget(work_spectr_button);
	grp3->setLayout(vbox2);
	grp3->setFixedWidth(350);
	vbox1->addWidget(grp2);
	vbox1->addWidget(grp1);
	vbox1->addWidget(grp3);
	vbox1->addStretch();
	//vbox1->addStretch();
	

	wdg->setLayout(vbox1);

	scrollArea = new QScrollArea(this);

	scrollArea->setWidget(pvw);
	//scrollArea->setBaseSize(1200, 800);

	QSplitter *V_split;
	V_split = new QSplitter();
	V_split->setOrientation(Qt::Horizontal); 
	//V_split->addWidget(pvw);
	V_split->addWidget(scrollArea);
	V_split->addWidget(wdg);
	QList<int> ql;
	ql.append(1300);
	ql.append(350);
	//V_split->setSizes(ql);
	V_split->setStretchFactor(0,1);
	

	QSplitter *H_split;
	H_split = new QSplitter();
	H_split->setOrientation(Qt::Vertical);
	//H_split->setObjectName(QString::fromUtf8());


	H_split->addWidget(V_split);
	H_split->addWidget(plt1D);
	ql.clear();
	ql.append(800);
	ql.append(200);
	//H_split->setSizes(ql);
	H_split->setStretchFactor(1,1);
	H_split->setStretchFactor(0, 1);

	tabWidget->addTab(H_split,QString(QApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\207\320\270\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200", 0 ))); // tr("I(x,y)")// Рабочий спектр
/*
	pvHist = new PicView;
	//tabWidget->addTab(pvw,QString());
	//tabWidget->addTab();
	pvHist->setpnts(0.1,0.1,0.9,0.9);
	pvHist->settype(1);
	pvHist->setPixelScale(PxSc);

	Hist	= new PlotGraph;
	LogHist = new PlotGraph;
	Hist->setNgrphx(4);
	LogHist->setNgrphx(4);


	QWidget *wdg1;
	wdg1 = new QWidget();
	flscrbt = new QPushButton(QString(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214\040\320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\203\321\216\040\320\276\320\261\320\273\320\260\321\201\321\202\321\214\040\320\262\040\320\277\320\276\320\273\320\275\320\276\321\215\320\272\321\200\320\260\320\275\320\275\320\276\320\274\040\321\200\320\265\320\266\320\270\320\274\320\265\056\040", 0 )),wdg1); // tr("Calc AutoCorrelation")selected on full screen
	setcentrbt = new QPushButton(QString(QApplication::translate("MainWindow", "Calc mass center", 0 ))); // tr("Calc AutoCorrelation")
	//wdg1->insest


	QSplitter *V_split1;
	V_split1 = new QSplitter();
	V_split1->setOrientation(Qt::Vertical); 
	V_split1->addWidget(pvHist);
	V_split1->addWidget(wdg1);
	//V_split1->addWidget(wdg4);
	V_split1->setStretchFactor(1,1);
	

	QSplitter *H_split1;
	H_split1 = new QSplitter();
	H_split1->setOrientation(Qt::Horizontal);
	//H_split->setObjectName(QString::fromUtf8());


	QSplitter *V_split3;
	V_split3 = new QSplitter();
	V_split3->setOrientation(Qt::Vertical);
	V_split3->addWidget(Hist);
	V_split3->addWidget(LogHist);

	H_split1->addWidget(V_split1);
	H_split1->addWidget(V_split3);
	H_split1->setStretchFactor(1,1);


	tabWidget->addTab(H_split1,QString(QApplication::translate("MainWindow", "\320\223\320\270\321\201\321\202\320\276\320\263\321\200\320\260\320\274\320\274\320\260", 0 ))); // tr("Histogram dN(I)")


	Corr	= new PlotGraph;
	Cor2D	= new PicView;
	Cor2D->setpnts(0.1,0.1,0.1,0.15);
	Cor2D->setPixelScale(PxSc);

	QWidget *wdg2;
	wdg2 = new QWidget();

	
	gcrbt = new QPushButton(QString(QApplication::translate("MainWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214 \321\204\321\203\320\275\320\272\321\206\320\270\321\216 \320\260\320\262\321\202\320\276\320\272\320\276\321\200\321\200\320\265\320\273\321\217\321\206\320\270\320\270", 0 )),wdg2); // tr("Calc AutoCorrelation")
	//gcrbt->

	QSplitter *V_split2;
	V_split2 = new QSplitter();
	V_split2->setOrientation(Qt::Vertical); 
	V_split2->addWidget(Cor2D);
	V_split2->addWidget(wdg2);
	V_split2->setStretchFactor(1,1);
	

	QSplitter *H_split2;
	H_split2 = new QSplitter();
	H_split2->setOrientation(Qt::Horizontal);
	//H_split->setObjectName(QString::fromUtf8());


	H_split2->addWidget(V_split2);
	H_split2->addWidget(Corr);
	H_split2->setStretchFactor(1,1);


	acnx = 400;
	acny = 10;
	*/
	//tabWidget->addTab(H_split2,QString(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\320\272\320\276\321\200\321\200\320\265\320\273\321\217\321\206\320\270\321\217", 0 ))); // tr("Correlation")


	clWdgt = new ClbrWidget(this);

	tabWidget->addTab(clWdgt, QString(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272\320\270\040\321\201\320\277\320\265\320\272\321\202\321\200\320\276\320\262", 0)));//Calibration of Spectra

	
	clWdgt->setPixelScale(PxGrSc);


	setCentralWidget(tabWidget);




	plt1D->xlabel(QApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\262 \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270 (x,y) [\320\277\320\270\321\201\320\272\320\265\320\273\320\270]", 0 ));//tr("(x,y) displacment "));
	plt1D->ylabel(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 [\320\276\321\202\320\275. \320\265\320\264.]", 0 ));//tr("Int. a.u."));
	plt1D->setTcsTpx(1);
	plt1D->setTcsTpy(1);

/*	LogHist->xlabel(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 [\320\261\320\270\321\202]", 0 ));//tr("Intencity [Counts]"));
	LogHist->ylabel(QApplication::translate("MainWindow", "ln(\321\207\320\270\321\201\320\273\320\276 \320\277\320\270\320\272\321\201\320\265\320\273\320\265\320\271 / \320\261\320\270\321\202 )/ln(10)", 0 ));//tr("log(Number of pixels)/log(10)"));
	LogHist->setTcsTpx(2);
	LogHist->setTcsTpy(1);

	Hist->xlabel(QApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 [\320\261\320\270\321\202]", 0 ));//tr("Intencity [Counts]"));
	Hist->ylabel(QApplication::translate("MainWindow", "\321\207\320\270\321\201\320\273\320\276 \320\277\320\270\320\272\321\201\320\265\320\273\320\265\320\271 / \320\261\320\270\321\202", 0 ));//tr("log(Number of pixels)/log(10)"));
	Hist->setTcsTpx(2);
	Hist->setTcsTpy(1);

	Corr->setTcsTpy(2);
	Corr->xlabel(QApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\260\320\262\321\202\320\276\320\272\320\276\321\200\321\200\320\265\320\273\321\217\321\206\320\270\320\270 [\320\277\320\270\320\272\321\201\320\265\320\273\320\270]", 0 ));//tr("Numder of pixel"));
	Corr->ylabel(QApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \321\204\321\203\320\275\320\272\321\206\320\270\320\270 \320\260\320\262\321\202\320\276\320\272\320\276\321\200\321\200\320\265\320\273\321\217\321\206\320\270\320\270 ", 0 ));//tr("Correlation function value"));	

*/

	setUpConnections();

	bright = 10;
	contrast = 100;
	gamma = 20;

	pic_setup_box = new QDialog(this);

	bright_sldr = new QSlider(Qt::Horizontal, pic_setup_box);
	bright_sldr->setTickPosition(QSlider::TicksAbove);
	bright_sldr->setMaximum(100);
	bright_sldr->setMinimum(0);
	bright_sldr->setSliderPosition(bright);
	bright_sldr->setFixedWidth(300);
	bright_sldr->setTracking(false);
	contrast_sldr = new QSlider(Qt::Horizontal, pic_setup_box);
	contrast_sldr->setTickPosition(QSlider::TicksBelow);
	contrast_sldr->setMaximum(100);
	contrast_sldr->setMinimum(0);
	contrast_sldr->setSliderPosition(contrast);
	contrast_sldr->setFixedWidth(300);
	contrast_sldr->setTracking(false);
	gamma_sldr = new QSlider(Qt::Horizontal, pic_setup_box);
	gamma_sldr->setTickPosition(QSlider::TicksBelow);
	gamma_sldr->setMaximum(100);
	gamma_sldr->setMinimum(0);
	gamma_sldr->setSliderPosition(gamma);
	gamma_sldr->setFixedWidth(300);
	gamma_sldr->setTracking(false);



	pcnbr_label = new QLabel(QString("\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260\040\321\217\321\200\320\272\320\276\321\201\321\202\320\270\040\320\270\040\320\272\320\276\320\275\321\202\321\200\320\260\321\201\321\202\320\260\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217"));//Setup brightness and contrast
	pcn_lbl = new QLabel(QString("\320\232\320\276\320\275\321\202\321\200\320\260\321\201\321\202"));//Contast
	pbr_lbl = new QLabel(QString("\320\257\321\200\320\272\320\276\321\201\321\202\321\214"));//Brightness
	pgm_lbl = new QLabel(QString("\320\223\320\260\320\274\320\274\320\260\055\320\272\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217"));//Gamma


	pvbox1 = new QVBoxLayout(pic_setup_box);
	phbox2 = new QHBoxLayout(pic_setup_box);
	phbox1 = new QHBoxLayout(pic_setup_box);
	phbox3 = new QHBoxLayout(pic_setup_box);

	phbox1->addWidget(bright_sldr);
	phbox1->addWidget(pbr_lbl);
	phbox2->addWidget(contrast_sldr);
	phbox2->addWidget(pcn_lbl);
	phbox3->addWidget(gamma_sldr);
	phbox3->addWidget(pgm_lbl);

	pvbox1->addWidget(pcnbr_label);
	pvbox1->addLayout(phbox1);
	pvbox1->addLayout(phbox2);
	pvbox1->addLayout(phbox3);


	//pic_setup_box->setText(QString("Setup brigth and contrast"));

	pic_setup_box->setLayout(pvbox1);

	pic_setup_box->setModal(false);

	pactionPictureSetup = guiWin->actionPicColor;
	pactionPictureSetup->setText(QString("\320\257\321\200\320\272\320\276\321\201\321\202\321\214\057\320\232\320\276\320\275\321\202\321\200\320\260\321\201\321\202"));//Contrast/Brigth

	connect(pactionPictureSetup, SIGNAL(triggered()), pic_setup_box, SLOT(exec()));


	connect(bright_sldr, SIGNAL(valueChanged(int)), this, SLOT(br_ch(int)));
	connect(contrast_sldr, SIGNAL(valueChanged(int)), this, SLOT(cn_ch(int)));
	connect(gamma_sldr, SIGNAL(valueChanged(int)), this, SLOT(gm_ch(int)));

	connect( pic_setup_box, SIGNAL(finished(int)),this, SLOT(setClrs(int)));


	pvw->setBrCnGm(bright,contrast,gamma);
	clWdgt->getPicPnt()->setBrCnGm(bright, contrast, gamma);


	setTol(usr_eps);
	setNittr(usr_Nittr);

	clgr_type = 0;

	plt1D->tp_mxy = 0;

	IIMData Ldat;
	actual_pic_id = -1;
	loadbin();
	addImage(R,G1,G2,B);
	pvw->setpicdata(R,G3,B);
//	pvHist->setpicdata(R,G3,B);
	Ldat.d->bigIm = pvw->getPic();
	Ldat.d->filename = QString("\320\240\320\260\320\275\320\265\320\265\040\320\267\320\260\320\263\321\200\321\203\320\266\320\265\320\275\320\275\321\213\320\271");//From last binary
	Ldat.gensmall();
	iiMdl->addImgData(Ldat);
	data_x1->setValidator(new QIntValidator(0,R.nx-1,this));
	data_y1->setValidator(new QIntValidator(0,R.ny-1,this));
	data_x2->setValidator(new QIntValidator(0,R.nx-1,this));
	data_y2->setValidator(new QIntValidator(0,R.ny-1,this));
	setcrd_1();
	lstVw->update();
	pvw->recalc();



	this->showMaximized();

/** /	vecdb XX;
	vecdb ZZ;

	XX.var1D(1, 0.1, 5);
	ZZ.var1D(0.91, 0.02, 5.5);
	for (int ii = 0; ii < ZZ.N; ii++)
	{
		ZZ.x[ii] = sin(ZZ.x[ii] / 5.5*1.57)*5.5;
	}
	SparseMatr<double> MM;

	MM.interp_dstrb(XX, ZZ);

	showfull_infile(MM, "MM.txt");/**/


/**/
}


void MainWin::setUpConnections()
{

	

	connect(pvw, SIGNAL(recalc()), this, SLOT(getpicslice_sum_x()));//getpicslice_sum_x()));
																	//	connect(pvHist,SIGNAL(recalc()), this, SLOT(gethistdata2()));
																	//	connect(gcrbt,SIGNAL(clicked()),this,SLOT(autoCorr()));
																	//	connect(Cor2D,SIGNAL(recalc()), this, SLOT(getpicsliceAC()));

																	//	connect(flscrbt,SIGNAL(clicked()),this,SLOT(showFullScrn()));

	connect(pvw, SIGNAL(updtcrd()), this, SLOT(setcrd_1()));
	connect(data_x1, SIGNAL(editingFinished()), this, SLOT(updcrd_1()));
	connect(data_y1, SIGNAL(editingFinished()), this, SLOT(updcrd_1()));
	connect(data_x2, SIGNAL(editingFinished()), this, SLOT(updcrd_1()));
	connect(data_y2, SIGNAL(editingFinished()), this, SLOT(updcrd_1()));

	connect(setHln, SIGNAL(clicked()), this, SLOT(hrznalgm()));
	connect(setVln, SIGNAL(clicked()), this, SLOT(vrtcalgm()));
	connect(setCM, SIGNAL(clicked()), this, SLOT(cntposCM()));

	connect(row_sum, SIGNAL(clicked()), this, SLOT(getpicslice_sum_x()));
	connect(col_sum, SIGNAL(clicked()), this, SLOT(getpicslice_sum_y()));

	connect(lstVw, SIGNAL(clicked(const QModelIndex &)), this, SLOT(updatepic(const QModelIndex &)));
	connect(iiMdl, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(type_change(const QModelIndex &, const QModelIndex &)));

	connect(lstVw, SIGNAL(save(const QModelIndex &)), this, SLOT(SaveFile(const QModelIndex &)));
	connect(lstVw, SIGNAL(del(const QModelIndex &)), this, SLOT(DelSpectr(const QModelIndex &)));


	connect(pvw, SIGNAL(getnewpic()), this, SLOT(newpicgen1()));
	//	connect(pvHist, SIGNAL(getnewpic()), this, SLOT(newpicgen2()));
	//	connect(Cor2D, SIGNAL(getnewpic()), this, SLOT(newpicgen3()));
	//	connect(pFllScrn, SIGNAL(getnewpic()), this, SLOT(showFullScrn()));

	connect(imprn_lines_btn, SIGNAL(clicked()), this, SLOT(setRepLine()));
	connect(set_work_frame_btn, SIGNAL(clicked()), this, SLOT(setWorkArea()));


	connect(clbr_button, SIGNAL(clicked()), this, SLOT(sendClbr()));
	connect(clWdgt, SIGNAL(clbr_pic_udp_req()), this, SLOT(sendClWf()));

	connect(work_spectr_button, SIGNAL(clicked()), this, SLOT(sendWrkSpcrt()));

	connect(setDarkLevelBtn, SIGNAL(clicked()), this, SLOT(setDarkLevel()));


}



void MainWin::newpicgen1() // генерирование новой картинки
{
	pvw->setpicdata(R, G1, B);
	update();
}
void MainWin::newpicgen2() // генерирование новой картинки
{
//	pvHist->setpicdata(R, G1, B);
	update();
}
void MainWin::newpicgen3() // генерирование новой картинки
{
//	Cor2D->setpicdata(AC);
	update();
}

bool MainWin::okToContinue()
{
//	if()
	/*if(isWindowModified())
	{
		int r	= QMessageBox::warning(this,tr("ImProc"), tr("Save the changes?"),
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
		if (r==QMessageBox::Yes)
		{
			return save();
		}else
			if (r==QMessageBox::Cancel)
			{
				return false;
			}
	}*/
	return true;
}

void MainWin::openImageFile()
{
	char *fnm;
	QByteArray Qf;
	if(okToContinue())
	{
		QString	fileName	= QFileDialog::getOpenFileName(this,tr("\320\236\321\202\320\272\321\200\321\213\321\202\321\214\040\162\141\167\055\321\204\320\260\320\271\320\273\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217"),curDir,tr("Canon or Nikon raw files (*.cr2 *.nef *.x3f *.dng)"));//
		if(!fileName.isEmpty())
		{	
			IIMData Ldat;
			//loadFile(fileName);
			setCurrentFile(fileName);
			QString	cstr("wdcraw.exe -4 ");
			cstr.append(fileName);
			Qf = cstr.toLatin1();
			fnm = Qf.data();
			//dcraw();
			system(fnm);
			loadbin();
			Ldat.d->filename = QFileInfo(fileName).fileName();
			addImage(R,G1,G2,B);
			pvw->setpicdata(R,G3,B);
	//		pvHist->setpicdata(R,G3,B);
			Ldat.d->bigIm = pvw->getPic();
			Ldat.gensmall();
			iiMdl->addImgData(Ldat);
			lstVw->update();	
			data_x1->setValidator(new QIntValidator(0,R.nx-1,this));
			data_y1->setValidator(new QIntValidator(0,R.ny-1,this));
			data_x2->setValidator(new QIntValidator(0,R.nx-1,this));
			data_y2->setValidator(new QIntValidator(0,R.ny-1,this));
		}
	}
}

void MainWin::set_wfrm()// установка прямоугольника рабочей области
{
	double wfx1,wfy1,wfx2,wfy2;
	int Nx1,Nx2,Ny1,Ny2;
	pvw->getpnts(wfx1,wfy1,wfx2,wfy2);
	Nx1 = R.nx*wfx1;
	Ny1 = R.ny*wfy1;
	Nx2 = R.nx*wfx2;
	Ny2 = R.ny*wfy2;

	wfrm_rect.setCoords(Nx1,Ny1,Nx2,Ny2);
}

void MainWin::setRepLine()
{
	improveSpLines();
	/*int in1, in2;
	in1 = data_y1->displayText().toInt();
	in2 = data_y2->displayText().toInt();
	m_line = (in1 + in2) / 2;*/
}

void MainWin::setWorkArea()
{
	int in1, in2;

	in1 = data_x1->displayText().toInt();
	in2 = data_x2->displayText().toInt();

	if (in1 > in2)
	{
		beg_col = in2;
		end_col = in1;
	}
	else
	{
		beg_col = in1;
		end_col = in2;
	}

	in1 = data_y1->displayText().toInt();
	in2 = data_y2->displayText().toInt();

	if (in1 > in2)
	{
		beg_line = in2;
		end_line = in1;
	}
	else
	{
		beg_line = in1;
		end_line = in2;
	}
	m_line = (in1 + in2) / 2;

	setup_ImpSpcLns();
	//improveSpLines();
	/*in1 = end_line - beg_line + 1;
	for (int ii = 0; ii < 4; ii++)
	{
	//	Mtrxs.x[ii].fsetlen(in1);
		kxz.x[ii].fsetlen(in1);
		bxz.x[ii].fsetlen(in1);
	}*/

	//dbR.setSize(in1, R.nx);
	//dbG1.setSize(in1, G1.nx);
	//dbG2.setSize(in1, G2.nx);
	//dbB.setSize(in1, B.nx);


	
	/*

	dbR.getSub_(R, beg_line, end_line, 0, R.nx - 1);
	dbG1.getSub_(G1, beg_line, end_line, 0, G1.nx - 1);
	dbG2.getSub_(G2, beg_line, end_line, 0, G2.nx - 1);
	dbB.getSub_(B, beg_line, end_line, 0, B.nx - 1);
	//improveSpLines();

	{
		vecT<double> V;

		dbR.getRow(0, V);
		double mode, sigma,rlev;
		int Nres;
		Nres = 2000;
		V.StatDistr(Nres, mode, sigma); // опредедение среднего уровня фона и его разброса

		rlev = mode + sigma; // уровень отсечки сигнала

		// определить наборы подмассивов с непрервыной индексацией (то есть спектральные пики) для каждой строки из dbX, потом по этим пикам выровнить каждую строку (как выравнивать?)
		// ? нужно-ли сглаживание?

		V.x = 0x0;
		V.N = V.mN = 0;
	}*/
}

void MainWin::type_change(const QModelIndex & index,const QModelIndex & index1)
{
	if(index.data().value<IIMData>().d->type == 0)
	{
	//	clbr_button->setEnabled(true);
		work_spectr_button->setEnabled(false);
		set_work_frame_btn->setEnabled(isDarkLevel);
	}else
	{
		clbr_button->setEnabled(false);
		set_work_frame_btn->setEnabled(false);
	}
}
void MainWin::updatepic(const QModelIndex & index)
{
	int id;
	if (index.data().value<IIMData>().d->type == 0)
	{
		//	clbr_button->setEnabled(true);
		work_spectr_button->setEnabled(false);
		set_work_frame_btn->setEnabled(isDarkLevel);
	}else
	{
		clbr_button->setEnabled(false);
		set_work_frame_btn->setEnabled(false);
	}
	id = index.row();
	if (id!= actual_pic_id)
	{
		R = Img_datas.x[id].x[0];
		G1 = Img_datas.x[id].x[1];
		B = Img_datas.x[id].x[2];
		G2 = Img_datas.x[id].x[3];

		G3 = G1;
		G3.s += G2.s;
		G3.s /= 2.0;
		//pvw->setpicdata(R,G3,B);
		//pvHist->setpicdata(R,G3,B);
		pvw->setPic(index.data().value<IIMData>().d->bigIm);
	//	pvHist->setPic(index.data().value<IIMData>().d->bigIm);
		actual_pic_id = id;
	}
	tabWidget->update();
	pvw->recalc();
}

void MainWin::DelSpectr(const QModelIndex & index)
{
	if (index.isValid())
	{
		int id;
		id = index.row();
		for (int ii = id;ii < (Img_datas.N-1);ii++) // цикл сдвигающий указатели на удаляемые матрицы в конец массива
		{
			Img_datas.x[ii].x[0].swp(Img_datas.x[ii + 1].x[0]);
			Img_datas.x[ii].x[1].swp(Img_datas.x[ii + 1].x[1]);
			Img_datas.x[ii].x[2].swp(Img_datas.x[ii + 1].x[2]);
			Img_datas.x[ii].x[3].swp(Img_datas.x[ii + 1].x[3]);
		}
		Img_datas.N--; // просто уменьшаем актуальный размер массива - последние матрицы оказыыются за пределами массива
		iiMdl->delImgData(index); // удаление информации об удаляемом спектре из данных для отображения иконок
		actual_pic_id = -1;

		if (Img_datas.N > 0)
		{
			id = id < Img_datas.N ? id : --id; // смена нового актуального номера спектра. Если удалялся последний спектр, то номер уменьшаем на единицу
			const ImageIconModel *ptr;
			ptr = reinterpret_cast<const ImageIconModel *> (index.model());
			updatepic(ptr->index(id));
		}
		else clearAll();

		lstVw->update();
		//tabWidget->update();
		update();
	}
}

void MainWin::sendClbr()
{
//	clWdgt->setCalibrData(&Img_datas.x[actual_pic_id], data_y1->displayText().toInt(), data_y2->displayText().toInt());
	//clWdgt->setCalibrData(&Img_datas.x[actual_pic_id], IntrpSpectrs/* ClbrIntrpSpctrs*/, beg_line, end_line,n_interp);//
	clWdgt->setCalibrData(&Img_datas.x[actual_pic_id],  ClbrIntrpSpctrs, beg_line, end_line,beg_col,end_col, n_interp);
	clgr_type = 0;
}

void MainWin::sendWrkSpcrt()
{
	clWdgt->setCalibrData(&Img_datas.x[actual_pic_id], IntrpSpectrs, beg_line, end_line,0, Img_datas.x[actual_pic_id].x[0].nx-1, n_interp);
	clgr_type = 1;
}

void MainWin::sendClWf()
{
	if (clgr_type == 0)
	{
		clWdgt->setCalibrData(&Img_datas.x[actual_pic_id], ClbrIntrpSpctrs, beg_line, end_line, beg_col, end_col, n_interp);
	}
	else
	{
		clWdgt->setCalibrData(&Img_datas.x[actual_pic_id], IntrpSpectrs, beg_line, end_line, 0, Img_datas.x[actual_pic_id].x[0].nx - 1, n_interp);
	}
}

void MainWin::clearAll()
{
	R.s	 = 0;
	G1.s = 0;
	G2.s = 0;
	B.s = 0;
	pvw->setpicdata(R, G1, B);
//	pvHist->setpicdata(R,G1,B);
	clbr_button->setEnabled(false);
}

void MainWin::setLinearInterp()
{
	interpolator->settype(0);
	clbr_button->setEnabled(false);
	work_spectr_button->setEnabled(false);
	//set_work_frame_btn->setEnabled(false);
	imprn_lines_btn->setEnabled(false);
	actionLinInterp->setIcon(*galcaIcon);
	actionDbLszInrp->setIcon(QIcon());
	actionCubInterp->setIcon(QIcon());
}

void MainWin::setDblLszInterp()
{
	interpolator->settype(1);
	clbr_button->setEnabled(false);
	work_spectr_button->setEnabled(false);
	//set_work_frame_btn->setEnabled(false);
	imprn_lines_btn->setEnabled(false);
	actionLinInterp->setIcon(QIcon());
	actionCubInterp->setIcon(QIcon());
	actionDbLszInrp->setIcon(*galcaIcon);
}

void MainWin::setCubicInterp()
{
	interpolator->settype(2);
	clbr_button->setEnabled(false);
	work_spectr_button->setEnabled(false);
	//set_work_frame_btn->setEnabled(false);
	imprn_lines_btn->setEnabled(false);
	actionCubInterp->setIcon(*galcaIcon);
	actionDbLszInrp->setIcon(QIcon());
	actionLinInterp->setIcon(QIcon());
}

void MainWin::setNmbrInterp1()
{
	n_interp = 1;
	interpolator->SetDblLncz(n_interp);
	actionInterpInt_1->setIcon(*galcaIcon);
	actionInterpInt_3->setIcon(QIcon());
	actionInterpInt_5->setIcon(QIcon());
	actionInterpInt_10->setIcon(QIcon());
	actionInterpInt_20->setIcon(QIcon());
}

void MainWin::setNmbrInterp3()
{
	n_interp = 3; 
	interpolator->SetDblLncz(n_interp); 
	actionInterpInt_1->setIcon(QIcon());
	actionInterpInt_3->setIcon(*galcaIcon); 
	actionInterpInt_5->setIcon(QIcon());
	actionInterpInt_10->setIcon(QIcon());
	actionInterpInt_20->setIcon(QIcon());
}

void MainWin::setNmbrInterp5()
{
	n_interp = 5;
	interpolator->SetDblLncz(n_interp);
	actionInterpInt_5->setIcon(*galcaIcon);
	actionInterpInt_1->setIcon(QIcon());
	actionInterpInt_3->setIcon(QIcon());
	actionInterpInt_10->setIcon(QIcon());
	actionInterpInt_20->setIcon(QIcon());
}

void MainWin::setNmbrInterp10()
{
	n_interp = 10;
	interpolator->SetDblLncz(n_interp);
	actionInterpInt_10->setIcon(*galcaIcon);
	actionInterpInt_1->setIcon(QIcon());
	actionInterpInt_3->setIcon(QIcon());
	actionInterpInt_5->setIcon(QIcon());
	actionInterpInt_20->setIcon(QIcon());
}

void MainWin::setNmbrInterp20()
{
	n_interp = 20;
	interpolator->SetDblLncz(n_interp);
	actionInterpInt_20->setIcon(*galcaIcon);
	actionInterpInt_1->setIcon(QIcon());
	actionInterpInt_3->setIcon(QIcon());
	actionInterpInt_5->setIcon(QIcon());
	actionInterpInt_10->setIcon(QIcon());
}

void MainWin::SaveBinFile()
{
	//char *fnm;
	//QByteArray Qf;
	if(okToContinue())
	{
		QString	fileName	= QFileDialog::getSaveFileName(this,tr("\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214\040\320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\265\040\321\204\320\260\320\271\320\273\321\213"),curDir,tr("Binary Files (*.bin)"));//Save Binary File
		if(!fileName.isEmpty())
		{	
			//loadFile(fileName);
			//setCurrentFile(fileName);
			//QString	cstr("wdcraw.exe -4 ");
			//cstr.append(fileName);
			//Qf = cstr.toAscii();
			//fnm = Qf.data();
			//dcraw();
			//system(fnm);
			//loadbin();
			//pvw->setpicdata(R,G1,B);
			//pvHist->setpicdata(R,G1,B);
			savebin(R,G1,G2,B,fileName);
		}
	}
}

void MainWin::SaveFile(const QModelIndex & index)
{
	FullMatrix<unsigned short> R_,G1_,G2_,B_;
	int id;
	//char *fnm;
	id = index.row();

	R_ = Img_datas.x[id].x[0];
	G1_ = Img_datas.x[id].x[1];
	B_ = Img_datas.x[id].x[2];
	G2_ = Img_datas.x[id].x[3];

	if (okToContinue())
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214\040\320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\265\040\321\204\320\260\320\271\320\273\321\213"), curDir, tr("Binary Files (*.bin)"));//Save Binary File
		if (!fileName.isEmpty())
		{
			savebin(R_, G1_, G2_, B_, fileName);
		}
	}
}

void MainWin::setCurrentFile(const QString &fileName)
{
	curFile	= fileName;
	//setWindowModified(false);

	//QString shownName	= "Untitled";
	if(!curFile.isEmpty())
	{
		//shownName	= StrippedName(curFile);
		
		curDir = QFileInfo(fileName).absolutePath();
//		recentFiles.removeAll(curFile);
//		recentFiles.prepend(curFile);
//		updateRecentFileActions();
	}
//	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Molred")));
}

void MainWin::loadbin()
{
	FILE *fid;
	int rh,rw,ii,rh2,rw2,i2,j2,jj,kk;
	unsigned short *raw_image;

	raw_image = 0x0;
	fid = fopen("image.bin","rb");
	if(fid!=NULL)
	{
		fread(&rw,4,1,fid);
		fread(&rh,4,1,fid);
		ii = rw*rh;
		raw_image = new unsigned short [ii];
		fread(raw_image,2,ii,fid);
		fclose(fid);
	}else
	{
		rw = 4800;
		rh = 3200;
		ii = rw*rh;
		raw_image = new unsigned short [ii];
		memset(raw_image,0,ii*sizeof(unsigned short));
	}

	rw2 =rw/2;
	rh2 =rh/2;

	R.setSize(rh2,rw2);
	G1.setSize(rh2,rw2);
	G2.setSize(rh2,rw2);
	B.setSize(rh2,rw2);

	i2 = 0;
	if ((rw2==2672)&&(rh2==1758))
	{
		for (ii = 0;ii < rh2;ii++)
		{
			j2 = 0;
			for (jj = 0;jj < rw2;jj++)
			{
				kk = j2 + i2*rw;
				G2.x[ii][jj] = raw_image[kk];
				kk++;
				B.x[ii][jj] = raw_image[kk];
				j2 += 2;
			}
			j2 = 0;
			i2++;
			for (jj = 0;jj < rw2;jj++)
			{
				kk = j2 + i2*rw;
				R.x[ii][jj] = raw_image[kk];
				kk++;
				G1.x[ii][jj] = raw_image[kk];
				j2 += 2;
			}
			i2++;
		}
	}
	else  // ((rw2==2416)&&(rh2==1602))
	{
		for (ii = 0;ii < rh2;ii++)
		{
			j2 = 0;
			for (jj = 0;jj < rw2;jj++)
			{
				kk = j2 + i2*rw;
				R.x[ii][jj] = raw_image[kk];
				kk++;
				G1.x[ii][jj] = raw_image[kk];
				j2 += 2;
			}
			j2 = 0;
			i2++;
			for (jj = 0;jj < rw2;jj++)
			{
				kk = j2 + i2*rw;
				G2.x[ii][jj] = raw_image[kk];
				kk++;
				B.x[ii][jj] = raw_image[kk];
				j2 += 2;
			}
			i2++;
		}
	}
	G3=G1;
	G3.s+=G2.s;
	G3.s/=2.0;
	//FullMatrix<unsigned short> Loc;
	//Loc.getSub(R,13,R.ny-1,31,R.nx-1);
	plt1D->user_max_y = 13500;//(double)Loc.s.max();
	delete [] raw_image;
}

void MainWin::savebin(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B,const QString &fileName)
{
	QString fnmR(fileName);
	QString fnmG1(fileName);
	QString fnmG2(fileName);
	QString fnmB(fileName);
	fnmR.chop(4);
	fnmG1.chop(4);
	fnmG2.chop(4);
	fnmB.chop(4);
	fnmR.append("R.bin");
	fnmG1.append("G1.bin");
	fnmG2.append("G2.bin");
	fnmB.append("B.bin");



	FILE *fir, *fig1, *fig2, *fib;
	fir = fopen(fnmR.toLatin1().constData(),"wb");
	fwrite(&R.nx, sizeof(int), 1, fir);
	fwrite(&R.ny, sizeof(int), 1, fir);
	fwrite(R.s.x, sizeof(unsigned short),R.s.N, fir);
	fclose(fir);

	fig1 = fopen(fnmG1.toLatin1().constData(),"wb");
	fwrite(&G1.nx, sizeof(int), 1, fir);
	fwrite(&G1.ny, sizeof(int), 1, fir);
	fwrite(G1.s.x, sizeof(unsigned short),G1.s.N, fir);
	fclose(fig1);

	fig2 = fopen(fnmG2.toLatin1().constData(),"wb");
	fwrite(&G2.nx, sizeof(int), 1, fir);
	fwrite(&G2.ny, sizeof(int), 1, fir);
	fwrite(G2.s.x, sizeof(unsigned short),G2.s.N, fir);
	fclose(fig2);

	fib = fopen(fnmB.toLatin1().constData(),"wb");
	fwrite(&B.nx, sizeof(int), 1, fir);
	fwrite(&B.ny, sizeof(int), 1, fir);
	fwrite(B.s.x, sizeof(unsigned short),B.s.N, fir);
	fclose(fib);

}


void MainWin::addImage(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B)
{
	Img_datas.adz(); // инициировать новый нулевой элемент в конце массива
	Img_datas.last().x[0] = R;
	Img_datas.last().x[1] = G1;
	Img_datas.last().x[2] = B;
	Img_datas.last().x[3] = G2;
	actual_pic_id = Img_datas.N-1;
}

void MainWin::improveSpLines() // вызывать только после setup_ImpSpcLns()
{
	dbRGB.x[0].getSub_(R, beg_line, end_line, 0, R.nx - 1);
	dbRGB.x[1].getSub_(G1, beg_line, end_line, 0, G1.nx - 1);
	dbRGB.x[2].getSub_(G2, beg_line, end_line, 0, G2.nx - 1);
	dbRGB.x[3].getSub_(B, beg_line, end_line, 0, B.nx - 1);


	interpolator->setexp(R.nx);	// перенастроика интерполятора на полную строку

	vecdb ff1, ff3, ffs;
	ffs.fsetlen(interpolator->interplength());
	ff1.setempty();

	for (int jj = 0; jj < 4; jj++)
	{
		IntrpSpectrs.x[jj].fsetlen(interpolator->interplength());
		IntrpSpectrs.x[jj].zero();
		for (int ii = 0; ii < dbRGB.x[jj].ny; ii++)
		{
			ff1.x = 0x0; // отвязываем второй указатель 
			dbRGB.x[jj].getRow(ii, ff1); // два указателя на одну область памяти!
			//interpolator->DoDoubleLanczos(ff3, ff1);
			interpolator->DoTypeInterp(ff3, ff1);
			ff3.cycle_shift(ffs,shfts_lines.x[jj].x[ii] ); // сдвинуть 
			IntrpSpectrs.x[jj] += ffs;  // сбор всех сдвинутых спекров в один массив
		}
		IntrpSpectrs.x[jj] *= double(1.0 / dbRGB.x[jj].ny);
	}
	ff1.x = 0x0; // отвязываем второй указатель 

	work_spectr_button->setEnabled(true);
}
// ниже старый вариант
/*	vecdb XX,ZZ,X0;
	XX.var1D(100.0, 1.0, R.nx - 100.0);
	ZZ.fsetlen(XX.N);
	X0.fsetlen(R.nx);
	X0.var1D(0.,1.,R.nx-1.0);
	vecdb bb,crl;
	
	
	SparseMatr<double> M;
	FullMatrix<unsigned short> *Dt[4];
	Dt[0] = &R;
	Dt[1] = &G1;
	Dt[2] = &G2;
	Dt[3] = &B;

	vecdb yy, ff,yf;
	yy.fsetlen(XX.N);
	ff.fsetlen(XX.N);
	yf.fsetlen(R.nx);
	
	int kk,ik;
	double syy,cl1;
	for (int ic = 0; ic < 4; ic++)
	{
		for (int ii = 0; ii < XX.N; ii++)
		{
			kk = (int)XX.x[ii];
			yy.x[ii] = Dt[ic]->fst(m_line, kk);
		}
		syy = yy.ssqr();

		for (int ii = beg_line; ii < end_line; ii++)
		{
			for (int ll = 0; ll < R.nx; ll++)
			{
				yf.x[ll] = Dt[ic]->fst(ii, ll);
			}
			bb.var1D(-20, 1, 40);
			crl.fsetlen(bb.N);
			
			for (int jj = 0; jj < bb.N; jj++)
			{
				for (int ll = 0; ll <XX.N; ll++) ZZ.x[ll] = bb.x[jj] + XX.x[ll];
				M.interp_dstrb(X0, ZZ);
				M.pmv(yf, ff);
				ff -= yy;
				crl.x[jj] = ff.ssqr()/syy;
				//crl.x[jj] = ff.scpr(yy) / sqrt(syy*ff.ssqr());
			}
			crl.min(ik);

			bb.var1D(bb.x[ik]-1, 0.1, bb.x[ik] +1);
			crl.fsetlen(bb.N);
			
			for (int jj = 0; jj < bb.N; jj++)
			{
				for (int ll = 0; ll <XX.N; ll++) ZZ.x[ll] = bb.x[jj] + XX.x[ll];
				M.interp_dstrb(X0, ZZ);
				M.pmv(yf, ff);
				ff -= yy;
				crl.x[jj] = ff.ssqr() / syy;
			}
			crl.min(ik);

			bb.var1D(bb.x[ik] - 0.1, 0.01, bb.x[ik] + 0.1);
			crl.fsetlen(bb.N);
			
			for (int jj = 0; jj < bb.N; jj++)
			{
				for (int ll = 0; ll <XX.N; ll++) ZZ.x[ll] = bb.x[jj] + XX.x[ll];
				M.interp_dstrb(X0, ZZ);
				M.pmv(yf, ff);
				ff -= yy;
				crl.x[jj] = ff.ssqr() / syy;
			}
			crl.min(ik);

		//	for (int ll = 0; ll <XX.N; ll++) ZZ.x[ll] = bb.x[ik] + XX.x[ll];
		//	M.interp_dstrb(X0, ZZ);
			bxz.x[ic].x[ii- beg_line] = bb.x[ik];
		//	Mtrxs.x[ic].x[ii].setCopy(M);
		}
	}
	
	
	
}*/

void MainWin::setup_ImpSpcLns()
{
	int Rnx;

	Rnx = end_col - beg_col + 1;

	dbRGB.x[0].getSub_(R, beg_line, end_line, beg_col ,end_col );// 0, R.nx - 1);
	dbRGB.x[1].getSub_(G1, beg_line, end_line, beg_col, end_col);//0, G1.nx - 1);
	dbRGB.x[2].getSub_(G2, beg_line, end_line, beg_col, end_col);//0, G2.nx - 1);
	dbRGB.x[3].getSub_(B, beg_line, end_line, beg_col, end_col);//0, B.nx - 1);

	dbRGB.x[0].s -= darkLevelR;
	dbRGB.x[1].s -= darkLevelG1;
	dbRGB.x[2].s -= darkLevelG2;
	dbRGB.x[3].s -= darkLevelB;

	//interpolator->SetDblLncz(n_interp);		// настроика интерполятора
	//interpolator->SetLinear(n_interp);		// настроика линейного интерполятора
	interpolator->SetTypeInterp(n_interp); // по type
	interpolator->setexp(Rnx);	// настроика интерполятора

	vecdb ff1,ff2,ff3,ffs;

	ffs.fsetlen(interpolator->interplength());
	ff1.setempty();
	int id0,gs,idmx;
	id0 = 0;// m_line - beg_line;

	ff1.x = 0x0;
	dbRGB.x[0].getRow(id0, ff1);
	//interpolator->DoDoubleLanczos(ff2, ff1);
	interpolator->DoTypeInterp(ff2, ff1);
	ff2.diff(); // длина уменьшается на единицу
	for (int jj = 0; jj < 4; jj++)
	{
		gs = 0;
		ClbrIntrpSpctrs.x[jj].fsetlen(ff2.N+1);
		ClbrIntrpSpctrs.x[jj].zero();
		shfts_lines.x[jj].fsetlen(dbRGB.x[jj].ny);
		for (int ii = 0; ii < dbRGB.x[jj].ny; ii++)
		{
			ff1.x = 0x0; // отвязываем второй указатель 
			dbRGB.x[jj].getRow(ii, ff1); // два указателя на одну область памяти!
			//interpolator->DoDoubleLanczos(ff3, ff1);
			interpolator->DoTypeInterp(ff3, ff1);
			ffs.pst(ff3); // сохранить массив до дифференцирования
			ff3.diff(); // здесь длина уменьшается на единицу
			idmx = ff2.max_crl_shft(ff3, gs); // определение оптимального сдвига - максимизирующего корреляцию
			gs = idmx;
			shfts_lines.x[jj].x[ii] = idmx;	// запомнить сдвиг
			ff3.N = ffs.N; // нужно восстановление длины ff3 который уменьшается на 1 при дифференцировании
			ffs.cycle_shift(ff3, idmx); // сдвинуть 
			ClbrIntrpSpctrs.x[jj] += ff3;  // сбор всех сдвинутых спекров в один массив
		}
		ClbrIntrpSpctrs.x[jj] *= double(1.0 / dbRGB.x[jj].ny);
	}
	ff1.x = 0x0; // отвязываем второй указатель


	work_spectr_button->setEnabled(false);
	imprn_lines_btn->setEnabled(true);
	clbr_button->setEnabled(true);
}

void MainWin::saveFullPic()
{
	if (R.s.N != 0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xB8\xD0\xB7\xD0\xBE\xD0\xB1\xD1\x80\xD0\xB0\xD0\xB6\xD0\xB5\xD0\xBD\xD0\xB8\xD1\x8F\x20\xD0\xBF\xD0\xBE\xD0\xBB\xD0\xBD\xD0\xBE\xD0\xB3\xD0\xBE\x20\xD0\xBA\xD0\xB0\xD0\xB4\xD1\x80\xD0\xB0\x20\xD1\x82\xD0\xB5\xD0\xBA\xD1\x83\xD1\x89\xD0\xB5\xD0\xB3\xD0\xBE\x20\xD1\x81\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0"), curDir, tr("picture files (*.jpeg)"));
		if (!fileName.isEmpty())
		{
			pvw->getPic().save(fileName,'\0', 100);
		}
	}
}

void MainWin::saveSlctFrm()
{
	if (R.s.N != 0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xB8\xD0\xB7\xD0\xBE\xD0\xB1\xD1\x80\xD0\xB0\xD0\xB6\xD0\xB5\xD0\xBD\xD0\xB8\xD1\x8F\x20\xD0\xB2\xD1\x8B\xD0\xB4\xD0\xB5\xD0\xBB\xD0\xB5\xD0\xBD\xD0\xBD\xD0\xBE\xD0\xB3\xD0\xBE\x20\xD1\x84\xD1\x80\xD0\xB0\xD0\xB3\xD0\xBC\xD0\xB5\xD0\xBD\xD1\x82\xD0\xB0\x20\xD1\x81\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0"), curDir, tr("picture files (*.jpeg)"));
		if (!fileName.isEmpty())
		{
			PicView *locpic = new PicView(this);
			int br, cn, gm;
			pvw->getBrCnGm(br, cn, gm);
			locpic->setBrCnGm(br, cn, gm);
			locpic->setPixelScale(1);

			double x1, y1, x2, y2;
			int Nx1, Ny1, Nx2, Ny2, NN;

			pvw->getpnts(x1, y1, x2, y2);
			Nx1 = R.nx*x1;
			Ny1 = R.ny*y1;
			Nx2 = R.nx*x2;
			Ny2 = R.ny*y2;

			FullMatrix<unsigned short> locR, locG1, locG2, locB;

			locR.getSub(R, Ny1, Ny2, Nx1, Nx2);
			locG1.getSub(G1, Ny1, Ny2, Nx1, Nx2);
			locG2.getSub(G2, Ny1, Ny2, Nx1, Nx2);
			locB.getSub(B, Ny1, Ny2, Nx1, Nx2);
			locG2.s += locG1.s;
			locG2.s /= 2.0;

			locpic->setpicdata(locR, locG2, locB, 1);
			locpic->getPic().save(fileName, '\0', 100);
		}
	}
}

void MainWin::exportClbrTbl()
{
	if (clWdgt->getClbTbl() != 0x0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xBA\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBE\xD1\x87\xD0\xBD\xD0\xBE\xD0\xB9\x20\xD1\x82\xD0\xB0\xD0\xB1\xD0\xBB\xD0\xB8\xD1\x86\xD1\x8B"), curDir, tr("text files (*.txt)"));
		if (!fileName.isEmpty())
		{
			FILE *f_id;
			vecT<char> headstr;
			//QString locStr;
			headstr.add("Калибровочная таблица \nдлина волны | номер пикселя | погр. номера пикселя \n");
			headstr.add('\0');
			//locStr.append("\xD0\x9A\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBE\xD1\x87\xD0\xBD\xD0\xB0\xD1\x8F\x20\xD1\x82\xD0\xB0\xD0\xB1\xD0\xBB\xD0\xB8\xD1\x86\xD0\xB0\x0A\xD0\x94\xD0\xBB\xD0\xB8\xD0\xBD\xD0\xB0\x20\xD0\xB2\xD0\xBE\xD0\xBB\xD0\xBD\xD1\x8B\x20\x28\xD0\x90\xD0\xBD\xD0\xB3\xD1\x81\xD1\x82\x2E\x29\x7C\xD0\x9D\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x20\x7C\x20\xD0\xBF\xD0\xBE\xD0\xB3\xD1\x80\x2E\x20\xD0\xBD\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\xD0\xB0\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x0A\x20");
			f_id = fopen(fileName.toLatin1().constData(), "wt");
			fwrite(headstr.x, sizeof(char),headstr.N , f_id);
			fprintf(f_id, "\n");
			for (int ii = 0; ii < clWdgt->get_lmbds()->N; ii++)
			{
				fprintf(f_id, "%.15g		%.15g		%.6g	\n", clWdgt->get_lmbds()->x[ii], clWdgt->get_idpix()->x[ii], clWdgt->get_sgpix()->x[ii] );
			}
			fclose(f_id);
		}
	}
}

void MainWin::exportClbtGrf()
{
	if (clWdgt->getGrfPnt()->X().N != 0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xBF\xD0\xB0\xD1\x80\xD0\xB0\xD0\xBC\xD0\xB5\xD1\x82\xD1\x80\xD0\xBE\xD0\xB2\x20\xD0\xBA\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBA\xD0\xB8"), curDir, tr("text files (*.txt)"));
		if (!fileName.isEmpty())
		{
			FILE *f_id;
			vecT<char> headstr;
			//QString locStr;
			headstr.add("Аппроксимирующая функция: l = A + C/(N-B), \n где N - номер пикселя, l - длина волны в ангстремах \n");
			headstr.add('\0');
			//locStr.append("\xD0\x9A\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBE\xD1\x87\xD0\xBD\xD0\xB0\xD1\x8F\x20\xD1\x82\xD0\xB0\xD0\xB1\xD0\xBB\xD0\xB8\xD1\x86\xD0\xB0\x0A\xD0\x94\xD0\xBB\xD0\xB8\xD0\xBD\xD0\xB0\x20\xD0\xB2\xD0\xBE\xD0\xBB\xD0\xBD\xD1\x8B\x20\x28\xD0\x90\xD0\xBD\xD0\xB3\xD1\x81\xD1\x82\x2E\x29\x7C\xD0\x9D\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x20\x7C\x20\xD0\xBF\xD0\xBE\xD0\xB3\xD1\x80\x2E\x20\xD0\xBD\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\xD0\xB0\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x0A\x20");
			f_id = fopen(fileName.toLatin1().constData(), "wt");
			fwrite(headstr.x, sizeof(char), headstr.N, f_id);
			fprintf(f_id, "\n");
			fprintf(f_id, "Параметры аппроскимации : \n");
			fprintf(f_id, "A = %g  +- %g \n", clWdgt->getGarApprx()->X.x[0], clWdgt->getGarApprx()->X_.x[0]);
			fprintf(f_id, "B = %g  +- %g \n", clWdgt->getGarApprx()->X.x[1], clWdgt->getGarApprx()->X_.x[1]);
			fprintf(f_id, "C = %g  +- %g \n", clWdgt->getGarApprx()->X.x[2], clWdgt->getGarApprx()->X_.x[2]);
			fprintf(f_id, " \n");
			/*fprintf(f_id, "Калибровочный график: \n");
			fprintf(f_id, "Номер пискеля	|	Длина волны \n");
			for (int ii = 0; ii < clWdgt->get_lmbds()->N; ii++)
			{
				fprintf(f_id, "%.15g		%.15g		%.6g	\n", clWdgt->get_lmbds()->x[ii], clWdgt->get_idpix()->x[ii], clWdgt->get_sgpix()->x[ii]);
			}*/
			fclose(f_id);
		}
	}
}

void MainWin::exportCurSpct()
{
	if (clWdgt->getGrfPnt()->X().N != 0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD1\x82\xD0\xB5\xD0\xBA\xD1\x83\xD1\x89\xD0\xB5\xD0\xB3\xD0\xBE\x20\xD1\x81\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0"), curDir, tr("text files (*.txt)"));
		if (!fileName.isEmpty())
		{
			FILE *f_id;
			vecT<char> headstr;
			//QString locStr;
			if (clWdgt->isClDn())
			{
				headstr.add(" длина волны (ангстремы) | спектральная плостноть интерсивности (усл. ед.)  (R G1 G2 B)\n");
				headstr.add('\0');
			}
			else
			{
				headstr.add(" номер пикселя	|	Интенсивность (усл. ед.)   (R G1 G2 B)\n");
				headstr.add('\0');
			}
			f_id = fopen(fileName.toLatin1().constData(), "wt");
			fwrite(headstr.x, sizeof(char), headstr.N, f_id);
			fprintf(f_id, "\n");
			
			for (int ii = 0; ii < clWdgt->getGrfPnt()->X().x[0].N; ii++)
			{
			fprintf(f_id, "%7f	%7f	%7f	%7f	%7f\n", clWdgt->getGrfPnt()->X().x[0].x[ii], clWdgt->getGrfPnt()->Y().x[0].x[ii],  clWdgt->getGrfPnt()->Y().x[1].x[ii],  clWdgt->getGrfPnt()->Y().x[2].x[ii], clWdgt->getGrfPnt()->Y().x[3].x[ii]);
			}
			fclose(f_id);
		}
	}
}

void MainWin::exportCurvLns()
{
	if (shfts_lines.x[0].N != 0)
	{
		QString	fileName = QFileDialog::getSaveFileName(this, tr("\xD0\xA1\xD0\xBE\xD1\x85\xD1\x80\xD0\xB0\xD0\xBD\xD0\xB5\xD0\xBD\xD0\xB8\xD0\xB5\x20\xD0\xBA\xD0\xBE\xD0\xBD\xD1\x82\xD1\x83\xD1\x80\xD0\xB0\x20\xD0\xB8\xD0\xB7\xD0\xB3\xD0\xB8\xD0\xB1\xD0\xB0\x20\xD1\x81\xD0\xBF\xD0\xB5\xD0\xBA\xD1\x82\xD1\x80\xD0\xB0\xD0\xBB\xD1\x8C\xD0\xBD\xD1\x8B\xD1\x85\x20\xD0\xBB\xD0\xB8\xD0\xBD\xD0\xB8\xD0\xB9\x0A\x20"), curDir, tr("text files (*.txt)"));
		if (!fileName.isEmpty())
		{
			FILE *f_id;
			vecT<char> headstr;
			//QString locStr;
			headstr.add("Номер строки | сдвиг строки R (в пикселях) | сдвиг строки G1 (в пикселях) | сдвиг строки G2 (в пикселях) | сдвиг строки B (в пикселях) \n");
			headstr.add('\0');
			//locStr.append("\xD0\x9A\xD0\xB0\xD0\xBB\xD0\xB8\xD0\xB1\xD1\x80\xD0\xBE\xD0\xB2\xD0\xBE\xD1\x87\xD0\xBD\xD0\xB0\xD1\x8F\x20\xD1\x82\xD0\xB0\xD0\xB1\xD0\xBB\xD0\xB8\xD1\x86\xD0\xB0\x0A\xD0\x94\xD0\xBB\xD0\xB8\xD0\xBD\xD0\xB0\x20\xD0\xB2\xD0\xBE\xD0\xBB\xD0\xBD\xD1\x8B\x20\x28\xD0\x90\xD0\xBD\xD0\xB3\xD1\x81\xD1\x82\x2E\x29\x7C\xD0\x9D\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x20\x7C\x20\xD0\xBF\xD0\xBE\xD0\xB3\xD1\x80\x2E\x20\xD0\xBD\xD0\xBE\xD0\xBC\xD0\xB5\xD1\x80\xD0\xB0\x20\xD0\xBF\xD0\xB8\xD0\xBA\xD1\x81\xD0\xB5\xD0\xBB\xD1\x8F\x0A\x20");
			f_id = fopen(fileName.toLatin1().constData(), "wt");
			fwrite(headstr.x, sizeof(char), headstr.N, f_id);
			fprintf(f_id, "\n");
			for (int ii = 0; ii < shfts_lines.x[0].N; ii++)
			{
				fprintf(f_id, "%d	%g	%g	%g	%g\n",ii+beg_line,((double)(shfts_lines.x[0].x[ii]))/(n_interp), ((double)(shfts_lines.x[1].x[ii])) / (n_interp), ((double)(shfts_lines.x[2].x[ii])) / (n_interp), ((double)(shfts_lines.x[3].x[ii])) / (n_interp));
			}
			fclose(f_id);
		}
	}
}

void MainWin::saveWrkFrStgh()
{
}

void MainWin::saveWrkFrClbr()
{
}

void MainWin::getpicslice()
{
	getpicslice_(0);
	//getpicslice_sum_x();
}
void MainWin::getpicslice_(int dd=0)
{
	if(R.s.N!=0)
	{
		double x1,y1,x2,y2,ax,ay,ro;
		int Nx1,Ny1,Nx2,Ny2,NN;

		pvw->getpnts(x1,y1,x2,y2);

		Nx1 = R.nx*x1;
		Ny1 = R.ny*y1;

		Nx2 = R.nx*x2;
		Ny2 = R.ny*y2;

		NN = abs(Nx2-Nx1)>abs(Ny2-Ny1) ? abs(Nx2-Nx1) : abs(Ny2-Ny1);

		ax = (double(Nx2-Nx1))/double(NN);
		ay = (double(Ny2-Ny1))/double(NN);

		ro = sqrt(ax*ax+ay*ay);
		lhlpvr.var1D_(0,ro,NN);

		plt1D->rsz_All(NN);

		plt1D->setXdata(lhlpvr);

		double dx, dy;
		int nx, ny;
		for(int ii = 0;ii<NN;ii++)
		{
			dx = ax*ii;
			dy = ay*ii;
			nx = Nx1+dx;
			ny = Ny1+dy;
			plt1D->Y().x[0].x[ii] = R.fst(ny,nx);
			plt1D->Y().x[1].x[ii] = G1.fst(ny,nx);
			plt1D->Y().x[2].x[ii] = G2.fst(ny, nx);
			plt1D->Y().x[3].x[ii] = B.fst(ny,nx);
		}
		plt1D->ZoomReset();
		update();
	}
}

void MainWin::getpicslice_sum_x()
{
	if(R.s.N!=0)
	{
		double x1, y1, x2, y2;// , ax, ay;
		int Nx1,Ny1,Nx2,Ny2,NN,nx,ny;

		pvw->getpnts(x1,y1,x2,y2);

		Nx1 = (R.nx-1)*x1;
		Ny1 = (R.ny - 1)*y1;

		Nx2 = (R.nx - 1)*x2;
		Ny2 = (R.ny - 1)*y2;

		if (Nx1>Nx2) {NN = Nx1; Nx1 = Nx2; Nx2 = NN;}
		if (Ny1>Ny2) {NN = Ny1; Ny1 = Ny2; Ny2 = NN;}
		if (Nx1==Nx2) {Nx2 = Nx1+1;}
		if (Ny1==Ny2) {Ny2 = Ny1+1;}

		nx = Nx2 - Nx1 + 1;
		ny = Ny2 - Ny1 + 1;

		plt1D->rsz_All(nx);

		lhlpvr.var1D_(Nx1, 1, nx);
		plt1D->setXdata(0, lhlpvr);
		plt1D->setXdata(2, lhlpvr);
		lhlpvr += 0.5;
		plt1D->setXdata(1, lhlpvr);
		plt1D->setXdata(3, lhlpvr);

		memset(plt1D->Y().x[0].x, 0, sizeof(double)*nx);
		memset(plt1D->Y().x[1].x, 0, sizeof(double)*nx);
		memset(plt1D->Y().x[2].x, 0, sizeof(double)*nx);
		memset(plt1D->Y().x[3].x, 0, sizeof(double)*nx);

		unsigned short *hxr,*hxg1,*hxg2,*hxb;
		double *hxd0, *hxd1, *hxd2, *hxd3;
		hxd0 = plt1D->Y().x[0].x;
		for (int ii = Ny1;ii <= Ny2;ii++) {	hxr = R.x[ii] + Nx1;   for (int jj = 0;jj<nx;jj++) {hxd0[jj] += (double)hxr[jj]; }}
		hxd1 = plt1D->Y().x[1].x;
		for (int ii = Ny1;ii <= Ny2;ii++) {	hxg1 = G1.x[ii] + Nx1; for (int jj = 0;jj<nx;jj++) {hxd1[jj] += (double)hxg1[jj];}}
		hxd2 = plt1D->Y().x[2].x;
		for (int ii = Ny1;ii <= Ny2;ii++) {	hxg2 = G2.x[ii] + Nx1; for (int jj = 0;jj<nx;jj++) {hxd2[jj] += (double)hxg2[jj];}}
		hxd3 = plt1D->Y().x[3].x;
		for(int ii = Ny1;ii<=Ny2;ii++)    { hxb  = B.x[ii] + Nx1;  for (int jj = 0;jj<nx;jj++) {hxd3[jj] += (double)hxb[jj]; }}
		
		plt1D->Y().x[0]/= (double)ny;
		plt1D->Y().x[1]/= (double)ny;
		plt1D->Y().x[2]/= (double)ny;
		plt1D->Y().x[3]/= (double)ny;
		
		plt1D->ZoomReset();
		update();
	}
}

void MainWin::getpicslice_sum_y()
{
	if(R.s.N!=0)
	{
		double x1, y1, x2, y2;// , ax, ay;
		int Nx1,Ny1,Nx2,Ny2,NN,nx,ny;

//FullMatrix<unsigned short> LocR,LocG1,LocG2,LocB;

		pvw->getpnts(x1,y1,x2,y2);

		Nx1 = R.nx*x1;
		Ny1 = R.ny*y1;

		Nx2 = R.nx*x2;
		Ny2 = R.ny*y2;

		if (Nx1>Nx2) {NN = Nx1; Nx1 = Nx2; Nx2 = NN;}
		if (Ny1>Ny2) {NN = Ny1; Ny1 = Ny2; Ny2 = NN;}
		if (Nx1==Nx2) {Nx2 = Nx1+1;}
		if (Ny1==Ny2) {Ny2 = Ny1+1;}

		nx = Nx2 - Nx1 + 1;
		ny = Ny2 - Ny1 + 1;

		plt1D->rsz_All(ny);

		lhlpvr.var1D_(Ny1, 1, ny);
		plt1D->setXdata(0, lhlpvr);
		plt1D->setXdata(3, lhlpvr);
		lhlpvr += 0.5;
		plt1D->setXdata(1, lhlpvr);
		plt1D->setXdata(2, lhlpvr);

		plt1D->Y().x[0].zero();
		plt1D->Y().x[1].zero();
		plt1D->Y().x[2].zero();
		plt1D->Y().x[3].zero();


		/*memset(plt1D->Y().x[0].x, 0, sizeof(double)*ny);
		memset(plt1D->Y().x[1].x, 0, sizeof(double)*ny);
		memset(plt1D->Y().x[2].x, 0, sizeof(double)*ny);
		memset(plt1D->Y().x[3].x, 0, sizeof(double)*ny);
		*/
		unsigned short *hxr, *hxg1, *hxg2, *hxb;
		double *hxd0, *hxd1, *hxd2, *hxd3;
		hxd0 = plt1D->Y().x[0].x;
		for (int ii = Ny1;ii <= Ny2;ii++) { hxr = R.x[ii] + Nx1;   for (int jj = Nx1;jj <= Nx2;jj++) { *hxd0 += (double)hxr[jj]; } hxd0++; }
		hxd1 = plt1D->Y().x[1].x;
		for (int ii = Ny1;ii <= Ny2;ii++) { hxg1 = G1.x[ii] + Nx1; for (int jj = Nx1;jj <= Nx2;jj++) { *hxd1 += (double)hxg1[jj]; } hxd1++; }
		hxd2 = plt1D->Y().x[2].x;
		for (int ii = Ny1;ii <= Ny2;ii++) { hxg2 = G2.x[ii] + Nx1; for (int jj = Nx1;jj <= Nx2;jj++) { *hxd2 += (double)hxg2[jj]; } hxd2++; }
		hxd3 = plt1D->Y().x[3].x;
		for (int ii = Ny1;ii <= Ny2;ii++) { hxb = B.x[ii] + Nx1;   for (int jj = Nx1;jj <= Nx2;jj++) { *hxd3 += (double)hxb[jj]; } hxd3++; }

		plt1D->Y().x[0] /= (double)nx;
		plt1D->Y().x[1] /= (double)nx;
		plt1D->Y().x[2] /= (double)nx;
		plt1D->Y().x[3] /= (double)nx;
		plt1D->ZoomReset();
		update();
	}
}


//void MainWin::getpicsliceAC()
//{
	/*if (AC.s.N!=0)
	{
		double x1,y1,x2,y2,ax,ay;
		int Nx1,Ny1,Nx2,Ny2,NN;
		int zx,zy;

		Cor2D->getpnts(x1,y1,x2,y2);
		Cor2D->getsz(zx,zy);

		Nx1 = AC.nx*x1;
		Ny1 = AC.ny*y1;

		Nx2 = AC.nx*x2;
		Ny2 = AC.ny*y2;


		NN = sqrt((x1-x2)*(x1-x2)*AC.nx*AC.nx+(y1-y2)*(y1-y2)*AC.ny*AC.ny);

		ax = (double(Nx2-Nx1))/double(NN);
		ay = (double(Ny2-Ny1))/double(NN);



		Corr->x.clear();
		Corr->y.clear();
		Corr->x.resize(NN);
		Corr->y.resize(NN);


		double dx,dy;
		int nx,ny;
		for(int ii = 0;ii<NN;ii++)
		{
			dx = ax*ii;
			dy = ay*ii;
			nx = Nx1+dx;
			ny = Ny1+dy;
			Corr->y[ii]=AC.fst(ny,nx);
			Corr->x[ii]=ii;
		}

		QPaintEvent *qpe;

		qpe = new QPaintEvent(Corr->rect());
		Corr->paintEvent(qpe);
	}
	//plt1D->setUpdatesEnabled(true);
	//plt1D->update();
	//setUpdatesEnabled(true);
	//repaint();
	//plt1D->setUpdatesEnabled(false);
	*/
//}


//void MainWin::gethistdata()
//{
/*	if (R.s.N!=0)
	{
		double x1,y1,x2,y2;
		int Nx1,Ny1,Nx2,Ny2,NN;
		unsigned short Imx, Imn, DI;

		FullMatrix<unsigned short> LocR,LocG1,LocG2,LocB;

//		pvHist->getpnts(x1,y1,x2,y2);

		Nx1 = R.nx*x1;
		Ny1 = R.ny*y1;

		Nx2 = R.nx*x2;
		Ny2 = R.ny*y2;

		if (Nx1>Nx2) {NN = Nx1; Nx1 = Nx2; Nx2 = NN;}
		if (Ny1>Ny2) {NN = Ny1; Ny1 = Ny2; Ny2 = NN;}
		if (Nx1==Nx2) {Nx2 = Nx1+1;}
		if (Ny1==Ny2) {Ny2 = Ny1+1;}

		LocR.getSub(R,Ny1,Ny2,Nx1,Nx2);	
		LocG1.getSub(G1,Ny1,Ny2,Nx1,Nx2);
		LocG2.getSub(G2,Ny1,Ny2,Nx1,Nx2);
		LocB.getSub(B,Ny1,Ny2,Nx1,Nx2);


		Imx = LocR.s.max();
		DI  = LocG1.s.max();
		Imx = Imx<DI ? DI:Imx;
		DI  = LocG2.s.max();
		Imx = Imx<DI ? DI:Imx;
		DI  = LocB.s.max();
		Imx = Imx<DI ? DI:Imx;

		Imn = LocR.s.min();
		DI  = LocG1.s.min();
		Imn = Imn>DI ? DI:Imn;
		DI  = LocG2.s.min();
		Imn = Imn>DI ? DI:Imn;
		DI  = LocB.s.min();
		Imn = Imn>DI ? DI:Imn;

		DI = Imx - Imn + 1;

		Hist->rsz_All((int)DI);
		
		//	Loc.s.qsort();
		for (int ii = 0;ii<DI;ii++)
		{
			Hist->X().x[0].x[ii] = Hist->X().x[1].x[ii] = Hist->X().x[2].x[ii] = Hist->X().x[3].x[ii] =  ii+Imn;	
		}

		int jj;
		for (int ii = 0;ii<LocR.s.N;ii++)
		{
			jj = LocR.s.x[ii]-Imn;
			Hist->Y().x[0].x[jj]++;
			jj = LocG1.s.x[ii]-Imn;
			Hist->Y().x[1].x[jj]++;
			jj = LocG2.s.x[ii]-Imn;
			Hist->Y().x[2].x[jj]++;
			jj = LocB.s.x[ii]-Imn;
			Hist->Y().x[3].x[jj]++;
		}

		double xx,yy;
		yy = log(10.);
		for (int ii = 0;ii<DI;ii++)
		{
			for(int jj =0;jj<4;jj++)
			{
				xx = Hist->Y().x[jj].x[ii];
				xx = (xx==0)? 0.95 : xx;
				xx = log(xx)/yy;
				Hist->Y().x[jj].x[ii] = xx;
			}
		}
		Hist->ZoomReset();
		//QPaintEvent *qpe;

		//qpe = new QPaintEvent(Hist->rect());
		//Hist->paintEvent(qpe);
		update();
	}*/
//}

//void MainWin::gethistdata2()
//{
	/*if (R.s.N!=0)
	{
		
		double x1,y1,x2,y2;
		int Nx1,Ny1,Nx2,Ny2,NN;
		unsigned short Imx, Imn, DI;
		FullMatrix<unsigned short> LocR,LocG1,LocG2,LocB;

	//	pvHist->getpnts(x1,y1,x2,y2);

		Nx1 = R.nx*x1;
		Ny1 = R.ny*y1;

		Nx2 = R.nx*x2;
		Ny2 = R.ny*y2;

		if (Nx1>Nx2) {NN = Nx1; Nx1 = Nx2; Nx2 = NN;}
		if (Ny1>Ny2) {NN = Ny1; Ny1 = Ny2; Ny2 = NN;}
	//	if (Nx1==Nx2) {Nx2 = Nx1+1;}
	//	if (Ny1==Ny2) {Ny2 = Ny1+1;}

		/*LocR.getSub(R,Ny1,Ny2,Nx1,Nx2);	
		LocG1.getSub(G1,Ny1,Ny2,Nx1,Nx2);
		LocG2.getSub(G2,Ny1,Ny2,Nx1,Nx2);
		LocB.getSub(B,Ny1,Ny2,Nx1,Nx2);* /

		Imx = 0; 	for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) Imx = Imx < R.fst(ii, jj) ? R.fst(ii, jj) : Imx; }
		DI = 0;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI < G1.fst(ii, jj) ? G1.fst(ii, jj) : DI; }
		Imx = Imx<DI ? DI:Imx;
		DI = 0;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI < G2.fst(ii, jj) ? G2.fst(ii, jj) : DI; }
		Imx = Imx<DI ? DI:Imx;
		DI = 0;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI < B.fst(ii, jj) ? B.fst(ii, jj) : DI; }
		Imx = Imx<DI ? DI:Imx;

		Imn = 0x0000ffff;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) Imn = Imn > R.fst(ii, jj) ? R.fst(ii, jj) : Imn; }
		DI = 0x0000ffff;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI > G1.fst(ii, jj) ? G1.fst(ii, jj) : DI; }
		Imn = Imn>DI ? DI:Imn;
		DI = 0x0000ffff;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI > G2.fst(ii, jj) ? G2.fst(ii, jj) : DI; }
		Imn = Imn>DI ? DI:Imn;
		DI = 0x0000ffff;		for (int ii = Ny1;ii <= Ny2;ii++) { for (int jj = Nx1;jj <= Nx2;jj++) DI = DI > B.fst(ii, jj) ? B.fst(ii, jj) : DI; }
		Imn = Imn>DI ? DI:Imn;

		DI = Imx - Imn + 1;

		int dNgx; // число интервалов по оси x
		dNgx = Hist->pixelLength();//Hist->frame[2] - Hist->frame[0]; //число пикселей вдоль оси x на графике


		//int kx;
		//kx = DI/dNgx;

		//if (kx>0) dNgx = DI/kx;

		Hist->rsz_All(dNgx);
		Hist->Y().x[0].zero();
		Hist->Y().x[1].zero();
		Hist->Y().x[2].zero();
		Hist->Y().x[3].zero();

		double kgx;
		kgx = double(DI)/double(dNgx);

		//	Loc.s.qsort();
		lhlpvr.var1D_(Imn, kgx, dNgx);
		Hist->setXdata(lhlpvr);

		/*for (int ii = 0;ii<dNgx;ii++)
		{
			Hist->X().x[0].x[ii] = Hist->X().x[1].x[ii] = Hist->X().x[2].x[ii] = Hist->X().x[3].x[ii] =  double(ii)*kgx+Imn;
		}* /

		int kk;
		for (int ii = Ny1;ii <= Ny2;ii++)
		{
			for (int jj = Nx1;jj <= Nx2;jj++)
			{
				kk = (R.fst(ii, jj) - Imn) / kgx;
			//	if (kk < 0) {	kk = 0;	}else if (kk >= dNgx)	{	kk = dNgx - 1;	}
				Hist->Y().x[0].x[kk]++;
			}
		}

		for (int ii = Ny1;ii <= Ny2;ii++)
		{
			for (int jj = Nx1;jj <= Nx2;jj++)
			{
				kk = (G1.fst(ii, jj) - Imn) / kgx;
			//	if (kk < 0)	{	kk = 0;	}else if (kk >= dNgx){	kk = dNgx - 1;	}
				Hist->Y().x[1].x[kk]++;
			}
		}

		for (int ii = Ny1;ii <= Ny2;ii++)
		{
			for (int jj = Nx1;jj <= Nx2;jj++)
			{
				kk = (G2.fst(ii, jj) - Imn) / kgx;
			//	if (kk < 0)	{	kk = 0;	}else	if (kk >= dNgx)	{kk = dNgx - 1;	}
				Hist->Y().x[2].x[kk]++;
			}
		}

		for (int ii = Ny1;ii <= Ny2;ii++)
		{
			for (int jj = Nx1;jj <= Nx2;jj++)
			{
				kk = (B.fst(ii, jj) - Imn) / kgx;
			//	if (kk < 0)	{kk = 0;}	else	if (kk >= dNgx)	{	kk = dNgx - 1;}
				Hist->Y().x[3].x[kk]++;
			}
		}


		/*int jj;
		for (int ii = 0;ii<LocR.s.N;ii++)
		{
			jj = (LocR.s.x[ii]-Imn)/kgx;
			Hist->Y().x[0].x[jj]++;
			jj = (LocG1.s.x[ii]-Imn)/kgx;
			Hist->Y().x[1].x[jj]++;
			jj = (LocG2.s.x[ii]-Imn)/kgx;
			Hist->Y().x[2].x[jj]++;
			jj = (LocB.s.x[ii]-Imn)/kgx;
			Hist->Y().x[3].x[jj]++;
		}* /

		LogHist->rsz_All(dNgx);
		LogHist->X() = Hist->X();
		LogHist->Y() = Hist->Y();
		
		double xx,yy;

		yy = log(10.);
		for (int ii = 0;ii<dNgx;ii++)
		{
			for(int jj =0;jj<4;jj++)
			{
				xx = LogHist->Y().x[jj].x[ii];
				xx = (xx==0)? 0.95 : xx;
				xx = log(xx)/yy;
				LogHist->Y().x[jj].x[ii] = xx;
			}
		}
		Hist->ZoomReset();
		LogHist->ZoomReset();
		/*QPaintEvent *qpe;
		qpe = new QPaintEvent(Hist->rect());
		Hist->paintEvent(qpe);
		QPaintEvent *qpe2;
		qpe2 = new QPaintEvent(LogHist->rect());
		LogHist->paintEvent(qpe);
		* /
		update();
	}*/
//}

//void MainWin::autoCorr()
//{
/*	if(R.s.N!=0)
	{
		double x1,y1,x2,y2;
		int Nx1,Ny1,Nx2,Ny2,NN;
		FullMatrix<unsigned short> Loc;
		vecT<double> DbLoc;
		//double GSum;

//		pvHist->getpnts(x1,y1,x2,y2);

		Nx1 = R.nx*x1;
		Ny1 = R.ny*y1;

		Nx2 = R.nx*x2;
		Ny2 = R.ny*y2;

		if (Nx1>Nx2) {NN = Nx1; Nx1 = Nx2; Nx2 = NN;}
		if (Ny1>Ny2) {NN = Ny1; Ny1 = Ny2; Ny2 = NN;}
		if (Nx1==Nx2) {Nx2 = Nx1+1;}
		if (Ny1==Ny2) {Ny2 = Ny1+1;}

		Loc.getSub(R,Ny1,Ny2,Nx1,Nx2);
		DbLoc.setlen(Loc.s.N);
		for(int ii = 0;ii<Loc.s.N;ii++) {DbLoc.x[ii] = (double) Loc.s.x[ii];}
		AC.setSize(acny,acnx);

		FullMatrix<double> Mtest;
		Mtest.setSize(Loc.ny,Loc.nx);
		Mtest.s.pst(DbLoc);
		Mtest.ConnectPointer();
		//Mtest.FullCorrelation(AC);
		Mtest.PartCorrelation(AC,40,60);

		AC.Shift();


		Cor2D->setpicdata(AC);
		update();
/*

		FullMatrix<unsigned short> R1;
		int zx,zy;
		Cor2D->getsz(zx,zy);
		R1.setSize(zy,zx);
		double Gx,Gn,kk;
		Gx = AC.s.max();
		Gn = AC.s.min();

		kk = 255/(Gx-Gn); // коэффиц. масштабирования на 8 бит

		double ax,ay;

		ax = zx/AC.nx;
		ay = zy/AC.ny;

		if (ax>ay)
		{ // картинку увеличивать только в ay раз
		}else
		{// картинку увеличивать в ax раз
			ay = ax;
		}
		int nn,mm;
		zy = ay*AC.ny;
		zx = ax*AC.nx;
		for (int ii=0;ii<zy;ii++)
		{
			nn = ii/ay;
			for(int jj=0;jj<zx;jj++)
			{
				mm = jj/ax;
				R1.fst(ii,jj) = (AC.fst(nn,mm)-Gn)*kk;
			}
		}

		Cor2D->setpicdata(R1);

		/*QPaintEvent *qpe;

		qpe = new QPaintEvent(Cor2D->rect());
		Cor2D->paintEvent(qpe);* /
		//AC.showfull_infile("fullcor.txt");

	}*/
//}



void MainWin::badPixelsRemove(FullMatrix<unsigned short>& M)
{
	/*int jjbeg;
	int iibeg;
	int ii,jj;
	jjbeg = 100;
	iibeg = 50;
	unsigned short *xi_m1, *xi_0, *xi_p1,sm;

	xi_m1 = &M.x.x[jjbeg-1][iibeg];
	xi_0  = &M.x.x[jjbeg][iibeg];
	xi_p1 = &M.x.x[jjbeg + 1][iibeg];

	jj = M.s.N - M.nx - 1;
	ii = M.nx*jjbeg + iibeg;

	for (; ii < jj; ii++)
	{
		sm = xi_m1[0] + xi_m1[1] + xi_m1[2];
		sm += (xi_0[0] + xi_0[2]);
		sm += (xi_p1[0] + xi_p1[1] + xi_p1[2]);

		sm >> 3; // sm /= 8; 8 = 2^3
		if (xi_0[1])


	}*/
}

//void MainWin::setFlScrPic()
//{ // катринка заполняется по данным размера рамки определяемой в режиме "Гистограмма"
/*	double x1,y1,x2,y2;
//	pvHist->getpnts(x1,y1,x2,y2);
	int i1,i2,j1,j2,nnx,nny;

	j1 = x1*R.nx;
	j2 = x2*R.nx;
	i1 = y1*R.ny;
	i2 = y2*R.ny;

	if(i2<i1) {nny = i1; i1 = i2; i2 = nny;}
	if(j2<j1) {nnx = j1; j1 = j2; j2 = nnx;}

	nnx = j2-j1;
	nny = i2-i1;

	FullMatrix<unsigned short> LR,LG1,LG2,LB;

	LR.getSub(R,i1,i2,j1,j2);
	LG1.getSub(G1,i1,i2,j1,j2);
	LG2.getSub(G2,i1,i2,j1,j2);
	LB.getSub(B,i1,i2,j1,j2);

	LG1.s += LG2.s;
	LG1.s /= 2;

	pFllScrn->setpnts(0,0,0,0);
	pFllScrn->setpicdataFull(LR,LG1,LB);
}

void MainWin::showFullScrn()
{
	setFlScrPic();
	pFllScrn->setWindowState(Qt::WindowFullScreen);
	//pFllScrn->setForegroundRole(QPalette::Shadow);
	pFllScrn->showFullScreen();

	//QPaintEvent *qpe;

	//qpe = new QPaintEvent(pFllScrn->rect());
	//Cor2D->paintEvent(qpe);
		*/
//}

void MainWin::setcrd_1()
{
	int nx,ny;
	double x1,x2,y1,y2;
	QString hstr;
	
	pvw->getpnts(x1,y1,x2,y2);
	nx = x1*R.nx;
	ny = y1*R.ny;
	hstr.setNum(nx);
	data_x1->clear();
	data_x1->insert(hstr);
	hstr.setNum(ny);
	data_y1->clear();
	data_y1->insert(hstr);
	nx = x2*R.nx;
	ny = y2*R.ny;
	hstr.setNum(nx);
	data_x2->clear();
	data_x2->insert(hstr);
	hstr.setNum(ny);
	data_y2->clear();
	data_y2->insert(hstr);
	nx = (x2-x1)*R.nx;
	hstr.setNum(nx);
	data_dx->clear();
	data_dx->insert(hstr);
	ny = (y2-y1)*R.ny;
	hstr.setNum(ny);
	data_dy->clear();
	data_dy->insert(hstr);
}

void MainWin::updcrd_1()
{
	//int nx,ny;
	double x1,x2,y1,y2;
	QString hstr;
	hstr = data_x1->displayText();
	x1 = hstr.toDouble()/R.nx;
	hstr = data_y1->displayText();
	y1 = hstr.toDouble()/R.ny;
	hstr = data_x2->displayText();
	x2 = hstr.toDouble()/R.nx;
	hstr = data_y2->displayText();
	y2 = hstr.toDouble()/R.ny;
	pvw->setpnts(x1,y1,x2,y2);
	//getpicslice();
	//QPaintEvent *qpe;
	//qpe = new QPaintEvent(pvw->rect());
	//pvw->paintEvent(qpe);
	update();
	pvw->update();
	pvw->recalc();
}

void MainWin::hrznalgm()
{
	double x1,x2,y1,y2;
	pvw->getpnts(x1,y1,x2,y2);
	x1 = x2 = (x1+x2)/2;
	pvw->setpnts(x1,y1,x2,y2);
	y1 = y1<y2 ? y1 : y2;
	getpicslice_(y1*R.ny);
	//QPaintEvent *qpe;
	//qpe = new QPaintEvent(pvw->rect());
	//pvw->paintEvent(qpe);
	update();
}

void MainWin::vrtcalgm()
{
	double x1,x2,y1,y2;
	pvw->getpnts(x1,y1,x2,y2);
	y1 = y2 = (y1+y2)/2;
	pvw->setpnts(x1,y1,x2,y2);
	x1 = x1<x2 ? x1 : x2;
	getpicslice_(x1*R.nx);
	//QPaintEvent *qpe;
	//qpe = new QPaintEvent(pvw->rect());
	//pvw->paintEvent(qpe);
	update();
}

void MainWin::cntposCM()
{
	double x1,x2,y1,y2;

	int ii,jj;

	FullMatrix<unsigned short> locR;

	locR.getSub(R,13,R.ny-1,0,30);
	double sz0;
	sz0 = 0.0;
	for(ii=0;ii<locR.s.N;ii++) 	{sz0 += locR.s.x[ii]; }
	sz0 /= locR.s.N;

	locR.getSub(R,13,R.ny-1,31,R.nx-1);

	double sxc,syc,xc,yc,sz;
	sxc = syc = sz = xc = yc = 0.0;
	for(ii=0;ii<locR.ny;ii++)
	{
		for(jj=0;jj<locR.nx;jj++)
		{
			yc += (locR.x[ii][jj]-sz0)*ii;
			xc += (locR.x[ii][jj]-sz0)*jj;
		}
	}
	for(ii=0;ii<locR.s.N;ii++) 	{sz += (locR.s.x[ii]-sz0); }

	xc /= sz;
	yc /= sz;

	for(ii=0;ii<locR.ny;ii++)
	{
		for(jj=0;jj<locR.nx;jj++)
		{
			syc += (locR.x[ii][jj]-sz0)*(ii-xc)*(ii-xc);
			sxc += (locR.x[ii][jj]-sz0)*(jj-yc)*(jj-yc);
		}
	}

	sxc = sqrt(sxc/sz);
	syc = sqrt(syc/sz);

	xc += 31; 
	yc += 13;

	QString hstr("(xc,yc): ");
	
	hstr.append(QString().setNum(int(xc)));
	hstr.append(", ");
	hstr.append(QString().setNum(int(yc)));

	str_CM_xy->setText(hstr);

	xc /= (double)R.nx;
	yc /= (double)R.ny;

	sxc /= (double)R.nx;
	syc /= (double)R.ny;




	x1 = xc - sxc;
	y1 = yc - syc;
	x2 = xc + sxc;
	y2 = yc + syc;
	
	x1 = x1<=0 ? 0 : x1;
	x1 = x1>=1 ? 1 : x1;

	y1 = y1<=0 ? 0 : y1;
	y1 = y1>=1 ? 1 : y1;

	x2 = x2<=0 ? 0 : x2;
	x2 = x2>=1 ? 1 : x2;

	y2 = y2<=0 ? 0 : y2;
	y2 = y2>=1 ? 1 : y2;


	pvw->setpnts(x1,y1,x2,y2);
	//getpicslice();
	/*QPaintEvent *qpe;
	qpe = new QPaintEvent(pvw->rect());
	pvw->paintEvent(qpe);*/
		//<unsigned short> R
	update();
	pvw->update();
	pvw->recalc();
}

void MainWin::setPxSc(int pp)
{
	PxSc = pp;
	pvw->setPixelScale(PxSc);
//	pvHist->setPixelScale(PxSc);
//	pvw->setpicdata(R, G3, B);
//	pvHist->setpicdata(R, G3, B);
//	update();
}

void MainWin::setDarkLevel()
{
	double x1, x2, y1, y2;
	int Nx1, Ny1, Nx2, Ny2, NN;

	pvw->getpnts(x1, y1, x2, y2);

	Nx1 = R.nx*x1;
	Ny1 = R.ny*y1;

	Nx2 = R.nx*x2;
	Ny2 = R.ny*y2;

	if (Nx1>Nx2) { NN = Nx1; Nx1 = Nx2; Nx2 = NN; }
	if (Ny1>Ny2) { NN = Ny1; Ny1 = Ny2; Ny2 = NN; }
	if (Nx1 == Nx2) { Nx2 = Nx1 + 1; }
	if (Ny1 == Ny2) { Ny2 = Ny1 + 1; }

	darkLevelR = 0.0;
	darkLevelG1 = 0.0;
	darkLevelG2 = 0.0;
	darkLevelB = 0.0;
	for(int ii = Ny1;ii<Ny2;ii++)
		for (int jj = Nx1; jj < Nx2; jj++)
		{
			darkLevelR += (double)(R.fst(ii, jj));
			darkLevelG2 += (double)(G1.fst(ii, jj));
			darkLevelG1 += (double)(G2.fst(ii, jj));
			darkLevelB += (double)(B.fst(ii, jj));
		}
	darkLevelR /= (double)(Nx2 - Nx1)*(Ny2 - Ny1);
	darkLevelG1 /= (double)(Nx2 - Nx1)*(Ny2 - Ny1);
	darkLevelG2 /= (double)(Nx2 - Nx1)*(Ny2 - Ny1);
	darkLevelB /= (double)(Nx2 - Nx1)*(Ny2 - Ny1);

	clWdgt->setDark(darkLevelR, darkLevelG1, darkLevelG2, darkLevelB);

	isDarkLevel = true;

	updatepic(lstVw->currentIndex());
}

void MainWin::help()
{
	HelpBrowser::showPage("index.html");
}

void MainWin::helpsummary()
{
	HelpBrowser::showPage("index_summary.html");
}

void MainWin::helpstrline()
{
	HelpBrowser::showPage("improve_spectra_lines.html");
}

void MainWin::helpcalibrt()
{
	HelpBrowser::showPage("index_calibrt.html");
}

void MainWin::helpspctlns()
{
	HelpBrowser::showPage("index_spctlines.html");
}

void MainWin::AboutMsg()
{
	const QString title = QString("\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260\040 VisSpectra");
	QString text;
	text.append("VisSpectra - \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260\040\320\264\320\273\321\217\040\320\270\321\201\321\201\320\273\320\265\320\264\320\276\320\262\320\260\320\275\320\270\321\217\040\320\276\320\277\321\202\320\270\321\207\320\265\321\201\320\272\320\270\321\205\040\321\201\320\277\320\265\320\272\321\202\321\200\320\276\320\262\054\040\012\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\321\203\320\265\320\274\321\213\321\205\040\321\201\040\320\277\320\276\320\274\320\276\321\211\321\214\321\216\040\321\206\320\270\321\204\321\200\320\276\320\262\320\276\320\263\320\276\040\320\267\320\265\321\200\320\272\320\260\320\273\321\214\320\275\320\276\320\263\320\276\040\321\204\320\276\321\202\320\276\320\260\320\277\320\277\320\260\321\200\320\260\321\202\320\260\054\040\321\201\040\320\270\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\320\275\320\270\320\265\320\274\040\122\101\127\055\321\204\320\260\320\271\320\273\320\276\320\262\056\040\n\n");
	text.append("\320\220\320\262\321\202\320\276\321\200\040\320\226\320\260\320\261\320\270\320\275\040\320\241\056\320\235\056\040\n");
	text.append("\320\232\320\260\321\204\320\265\320\264\321\200\320\260\040\320\236\320\261\321\211\320\265\320\271\040\320\244\320\270\320\267\320\270\320\272\320\270\040\320\234\320\244\320\242\320\230\040\062\060\061\067 - 2020\n");

	QMessageBox::about(this, title,text);
}

void MainWin::AboutMsgQt()
{
	const QString title = QString("\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260\040 VisSpectra");
	
	QMessageBox::aboutQt(this, title);
}

void MainWin::keyPressEvent(QKeyEvent *event)
{
	event->accept();
}

#endif