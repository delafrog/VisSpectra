#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QGraphicsView>
#include <QSize>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QLCDNumber>
#include <QVector>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QTableView>
#include <QListView>
#include <QModelIndex>
#include <QSpinBox>
#include <QScrollArea> 
#include <QTextDocument>

#include "ui_gui_.h"
//#include <valarray>
#include "linalg.h"
#include "picview.h"
#include "plotgraph.h"
#include "prevw.h"
#include "calibration.h"
#include "interpolator.h"
#include "helpbrowser.h"

struct IIMDataPtr;

class MainWin : public QMainWindow
{
	Q_OBJECT
public:
	MainWin();

	Ui::MainWindow *guiWin;

	QTabWidget *tabWidget;

	//QTableView *tblVw;
	ListView *lstVw;
	ImageIconModel *iiMdl;
	ImageIconDelegate *iiDlg;


	PicView *pvw;
	PlotGraph *plt1D;

//	PicView *pvHist;
//	PlotGraph *Hist;
//	PlotGraph *LogHist;
//	PicView *Cor2D;
//	PlotGraph *Corr;
//	QPushButton *gcrbt;
//	QPushButton *flscrbt; // кнопка показа картинки в полноэкранном режиме
	QPushButton *setcentrbt; // кнопка вычисления центра масс картинки
	QPushButton *setVln,*setHln; // кнопки горизонального и вертикального выравнивания
	QPushButton *setCM; // центрирование по центру масс
	QPushButton *row_sum; // суммирование по строкам 
	QPushButton *col_sum; // суммирование по столбцам
	QPushButton *clbr_button; // кнопка формирования спектра калибровки
	QPushButton *work_spectr_button; // кнопка формирования рабочего спектра
	QPushButton *set_work_frame_btn; // кнопка установки рабочей области  - интерполяция и вычисление сдвигов каждой строки. 
	QPushButton *imprn_lines_btn; // кнопка интерполяци рабочего спектра с учётом сдвигов
	QPushButton *okImSizeBtn; // кнопка ok в окошке установке масштабных коэффициентов
	QPushButton *okApprxParBtn; // кнопка ok в окошке параметров аппроксимации
	QPushButton *setDarkLevelBtn; // кнопка установки уровня темнового фона

//	PicView *pFllScrn; // буфер для картинки отображаемой в режиме fullscreen

	QLineEdit *data_x1,*data_x2,*data_y1,*data_y2,*data_dx,*data_dy;
	QLabel *str_p1,*str_p2,*str_CM_xy,*str_p3;

	//void set_wf_ids(int dix,int idy); // установка индексов рабочей области спектра

	ClbrWidget *clWdgt; // страничка с калибровочными спектрами и графиками

	Interpolator *interpolator; // cпециальный класс для проведения интерполяции
	

public slots:
	void openImageFile();

	void saveFullPic(); // сохранение полного кадра в jpeg
	void saveSlctFrm(); // сохранение выделенной области

	void exportClbrTbl(); // выгрузить тек. калибр. таблицу
	void exportClbtGrf(); // выгрузить текю калибровочный график
	void exportCurSpct(); // выгрузить текущий спектр

	void exportCurvLns(); // выгрузить контур изгиба спектральных линий

	void saveWrkFrStgh(); // сохранить рабочую область со спрямлённными линиями
	void saveWrkFrClbr(); // сохранить рабочую область после кабибровки - горихонтальная ось - длина волны



	void getpicslice();
	void getpicslice_(int dd);
	void getpicslice_sum_x();
	void getpicslice_sum_y();
//	void getpicsliceAC();
//	void gethistdata();
//	void gethistdata2();
//	void autoCorr(); // вычисление автокорреляции
//	void showFullScrn(); // показать выделенную катринку на полный экран
	void setcrd_1(); // установка данных координат для раздела "Индикатриса"
	void updcrd_1();
	void hrznalgm();// горизонтальное выравнивание
	void vrtcalgm();// вертикальное выравнивание
	void cntposCM();// центрирование положения
	void SaveBinFile(); // сохранение файла в бинарном виде (4 файла)
	void SaveFile(const QModelIndex & index); // сохранение файла (используется при вызаве через контекстное меню)
	void set_wfrm();// установка прямоугольника рабочей области
	void setRepLine(); // выравние линий по ранее вычисленным парамтерам; вызов improveSpLines();
	void setWorkArea(); // установка рабочей области - определение beg_line , end_line и размер массива матриц преобразования
	void newpicgen1(); // генерирование новой картинки
	void newpicgen2(); // генерирование новой картинки
	void newpicgen3(); // генерирование новой картинки

	void setPicPixSz(int pxsz) { PxSc = pxsz; }

	void updatepic(const QModelIndex & index);
	void type_change(const QModelIndex & index,const QModelIndex & index1);

	void DelSpectr(const QModelIndex & index); // удаление спектра по его индексу

	void sendClbr(); // опправить данные на калибровку

	void sendWrkSpcrt(); // фотправить данные нна отрисовку спектра
	void sendClWf(); //отправить данные на отрисовку спектра

	void clearAll(); // очистка данных изображения - нули в матрицы R,G1,G2,B и соответсвующие вызовы для pvw и pvHist

	void setLinearInterp();
	void setDblLszInterp();
	void setCubicInterp();

	void setNmbrInterp1();
	void setNmbrInterp3();
	void setNmbrInterp5();// { n_interp = 5; interpolator->SetDblLncz(n_interp); }
	void setNmbrInterp10();// { n_interp = 10; interpolator->SetDblLncz(n_interp); }
	void setNmbrInterp20();// { n_interp = 20; interpolator->SetDblLncz(n_interp); }
	//void updt_n_interp();
	//void newClbTblPrc(); // инициоровать новую калибровочную таблицу
	//void setClbTblPrc(); // установить текущую таблицу как калибровочную
	//void getClbTblPrc(); // загрузить ранее сформированную калибровочную таблицу

	void setPxSc(int pp);// { PxSc = pp; pvw->setPixelScale(PxSc); pvHist->setPixelScale(PxSc);  update(); }
	void setPxGrSc(int pp) { PxGrSc = pp; clWdgt->setPixelScale(PxGrSc); update(); }
	void updtpics() {	pvw->setpicdata(R, G3, B); if(beg_line!=-1) sendClWf(); /*	pvHist->setpicdata(R, G3, B);*/ update(); }

	void setDarkLevel(); // установка уровня темнового фона

	void br_ch(int br) { bright = br; }
	void cn_ch(int cn) { contrast = cn; }
	void gm_ch(int gm) { gamma = gm; }

	void setClrs(int res) { pvw->setBrCnGm(bright, contrast, gamma);	clWdgt->getPicPnt()->setBrCnGm(bright, contrast, gamma); update(); }

	void setTol(double tol) { usr_eps = tol;spBox_tol->setSingleStep(usr_eps / 2.0); clWdgt->setApptxTol(tol); }
	void setNittr(int nitr) { usr_Nittr = nitr; clWdgt->setApptxNitr(nitr); }


	void help();
	void helpsummary(); // общиее описание программы
	void helpstrline(); // спрямление линий
	void helpcalibrt(); // калибровка
	void helpspctlns(); // положение спектральных линий


	void AboutMsg();
	void AboutMsgQt();


	
protected:
	void keyPressEvent(QKeyEvent *event);
private:

	void setUpConnections(); // установка системы сигналов

	void badPixelsRemove(FullMatrix<unsigned short> &M); // Анализ матрицы изображения на предмет битых пикселей и исправление этой матрицы методом интерполяции по ближайшим соседям 

//	void setFlScrPic(); //заполнить картинку для полноэкранного отображения

	bool okToContinue();
	void setCurrentFile(const QString &fileName);
	
	void loadbin();
	void savebin(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B,const QString &fileName);


	void addImage(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B); // добавить снимок в массив данных о снимках
	
	void improveSpLines(); // процедура спрямления спектральных линий с использванием ранее вычисленных параметров сдвга и интерполяции

	void setup_ImpSpcLns(); // процедура определения параметров для спрялмения спектральных линий 



	//double BaseLevel(double *x,int Nlen);// определение базовой линии для массива из  

	//std::valarray<unsigned short> R,G1,G2,B;
	FullMatrix<unsigned short> R,G1,G2,B,G3;
	FullMatrix<double> AC; // матрица автокорреляции

	FullMatrix<double> dbR, dbG1, dbG2, dbB; // матрицы скорректированных фрагментов изображения (спрямлённые линии спектра)
	vec4FMdouble dbRGB; // матрицы рабочей области изображния (область спрямления спектральных линий)

	vecT< vec4FMushort > Img_datas; // массив матриц с данными о загруженных снимках 
	int actual_pic_id; // номер акуального спектра

	vecdb lhlpvr; // вспомогательный массив
	//FullMatrix<unsigned short> LocR, LocG1, LocG2, LocB; // вспомогательные массивы

	QRect wfrm_rect;
	int acnx,acny; 
	//int wf_id_x,wf_id_y; // индексы рабочей области. (Общие для всех спектров единой калибровки)
	
	int PxSc;// размер составного пикселя для изобращения рабочего спектра
	int PxGrSc; // множтель для размера графика (аналогичен PxSc)

	double darkLevelR; // уровень нулевой засветки
	double darkLevelG1; // уровень нулевой засветки
	double darkLevelG2; // уровень нулевой засветки
	double darkLevelB; // уровень нулевой засветки
	bool isDarkLevel; // индикатор установки тёмного фона

	int m_line; // номер опорной строки - для метода выравнивания спектральных линий
	int beg_line; // номер  начала области выравнивания спектра
	int end_line; // номер  конца области выравнивания спектра
	int beg_col; // номер  начала области выравнивания спектра
	int end_col; // номер  конца области выравнивания спектра
	int n_interp; // крантность интерпоялции - для метода выравнивания спктральных линий
	vec4T<vecint> shfts_lines;  // массивы свдвигов строк для выравнивания 
	vec4T<vecdb> ClbrIntrpSpctrs; // калибровочные спектры полученные из интеполяции и сдвига
	vec4T<vecdb> IntrpSpectrs; // спектры полученные интрполяцией и сдвигом
	vec4T<vecT<SparseMatr<double>>> Mtrxs; // матрицы для интерполяции строк изображения - для выравния спектральных линий
	vec4T<vecdb> kxz, bxz; // коэффициенты для переноса строк - при выравнивании спектральных линий

	vec4T<vecdb> LmbdsInterp; // массивы длин волн
	vec4T<vecdb> ClbrSpercts; // массивы калиброванных спектров полученных после калибровки


	int bright, contrast,gamma;// яркость констраст и гамма - общие для всей программы

	int clgr_type; // тип графика 0 - clbr; 1 - wrk


	//QStringList recentFiles;
	QString curFile;
	QString curDir;



/*	vecT<FullMatrix<double>> CalibrTables; // набор калибровочных таблиц
	vecT<vecT<int>> ImgClb_ids; // наборы индексов элементов из Img_datas соответствующих калибровочным спектрам
	vecT<vecT<int>> ImgWrk_ids; // наборы индексов элементов из Img_datas соответствующих рабочим спектрам
	vecT<vec2int> line_ids; // наборы номеров строк рабочей области для каждого рабочего набора (влючющего в себя набор калибровочных и рабочих спектров)
*/
	QDialog *size_setup_box; // окошко для настройки размера изображения
	QSpinBox *spBox_1, *spBox_2; // 

	QDialog *pic_setup_box; // окошко для настройки параметров изображения
	QSlider *bright_sldr, *contrast_sldr, *gamma_sldr; // ползунки для установки яркости и контраста

	QVBoxLayout *pvbox1;
	QHBoxLayout *phbox1, *phbox2, *phbox3;
	QAction *pactionPictureSetup; // действие - вызвать окно настройки яркости
	QLabel *pcnbr_label, *pcn_lbl, *pbr_lbl, *pgm_lbl;


	QDialog *approx_setup_box; // окошко для настройки параметров аппроксимации
	QSpinBox  *spBox_Nittr; // интерфейсы для изменения парамтеров аппроскимации
	QDoubleSpinBox *spBox_tol ;
	double usr_eps; // устанавливаемая пользователем невязка 
	int    usr_Nittr; // устанавливаемое пользователем максимальное число иттераций 


	QAction *actionOpenImage;

	QAction *actionSaveBin;

	QAction *actionSaveProject;

	QAction *actionExit;


	QAction *actionLinInterp;
	QAction *actionDbLszInrp;
	QAction *actionCubInterp;
	QAction *actionInterpInt_1;
	QAction *actionInterpInt_3;
	QAction *actionInterpInt_5;
	QAction *actionInterpInt_10;
	QAction *actionInterpInt_20;

	

	QAction *actionAbout;
	QIcon *galcaIcon; 

	QScrollArea  *scrollArea;

};


#endif 