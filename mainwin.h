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
//	QPushButton *flscrbt; // ������ ������ �������� � ������������� ������
	QPushButton *setcentrbt; // ������ ���������� ������ ���� ��������
	QPushButton *setVln,*setHln; // ������ �������������� � ������������� ������������
	QPushButton *setCM; // ������������� �� ������ ����
	QPushButton *row_sum; // ������������ �� ������� 
	QPushButton *col_sum; // ������������ �� ��������
	QPushButton *clbr_button; // ������ ������������ ������� ����������
	QPushButton *work_spectr_button; // ������ ������������ �������� �������
	QPushButton *set_work_frame_btn; // ������ ��������� ������� �������  - ������������ � ���������� ������� ������ ������. 
	QPushButton *imprn_lines_btn; // ������ ����������� �������� ������� � ������ �������
	QPushButton *okImSizeBtn; // ������ ok � ������ ��������� ���������� �������������
	QPushButton *okApprxParBtn; // ������ ok � ������ ���������� �������������
	QPushButton *setDarkLevelBtn; // ������ ��������� ������ ��������� ����

//	PicView *pFllScrn; // ����� ��� �������� ������������ � ������ fullscreen

	QLineEdit *data_x1,*data_x2,*data_y1,*data_y2,*data_dx,*data_dy;
	QLabel *str_p1,*str_p2,*str_CM_xy,*str_p3;

	//void set_wf_ids(int dix,int idy); // ��������� �������� ������� ������� �������

	ClbrWidget *clWdgt; // ��������� � �������������� ��������� � ���������

	Interpolator *interpolator; // c���������� ����� ��� ���������� ������������
	

public slots:
	void openImageFile();

	void saveFullPic(); // ���������� ������� ����� � jpeg
	void saveSlctFrm(); // ���������� ���������� �������

	void exportClbrTbl(); // ��������� ���. ������. �������
	void exportClbtGrf(); // ��������� ���� ������������� ������
	void exportCurSpct(); // ��������� ������� ������

	void exportCurvLns(); // ��������� ������ ������ ������������ �����

	void saveWrkFrStgh(); // ��������� ������� ������� �� ������������ �������
	void saveWrkFrClbr(); // ��������� ������� ������� ����� ���������� - �������������� ��� - ����� �����



	void getpicslice();
	void getpicslice_(int dd);
	void getpicslice_sum_x();
	void getpicslice_sum_y();
//	void getpicsliceAC();
//	void gethistdata();
//	void gethistdata2();
//	void autoCorr(); // ���������� ��������������
//	void showFullScrn(); // �������� ���������� �������� �� ������ �����
	void setcrd_1(); // ��������� ������ ��������� ��� ������� "�����������"
	void updcrd_1();
	void hrznalgm();// �������������� ������������
	void vrtcalgm();// ������������ ������������
	void cntposCM();// ������������� ���������
	void SaveBinFile(); // ���������� ����� � �������� ���� (4 �����)
	void SaveFile(const QModelIndex & index); // ���������� ����� (������������ ��� ������ ����� ����������� ����)
	void set_wfrm();// ��������� �������������� ������� �������
	void setRepLine(); // �������� ����� �� ����� ����������� ����������; ����� improveSpLines();
	void setWorkArea(); // ��������� ������� ������� - ����������� beg_line , end_line � ������ ������� ������ ��������������
	void newpicgen1(); // ������������� ����� ��������
	void newpicgen2(); // ������������� ����� ��������
	void newpicgen3(); // ������������� ����� ��������

	void setPicPixSz(int pxsz) { PxSc = pxsz; }

	void updatepic(const QModelIndex & index);
	void type_change(const QModelIndex & index,const QModelIndex & index1);

	void DelSpectr(const QModelIndex & index); // �������� ������� �� ��� �������

	void sendClbr(); // ��������� ������ �� ����������

	void sendWrkSpcrt(); // ���������� ������ ��� ��������� �������
	void sendClWf(); //��������� ������ �� ��������� �������

	void clearAll(); // ������� ������ ����������� - ���� � ������� R,G1,G2,B � �������������� ������ ��� pvw � pvHist

	void setLinearInterp();
	void setDblLszInterp();
	void setCubicInterp();

	void setNmbrInterp1();
	void setNmbrInterp3();
	void setNmbrInterp5();// { n_interp = 5; interpolator->SetDblLncz(n_interp); }
	void setNmbrInterp10();// { n_interp = 10; interpolator->SetDblLncz(n_interp); }
	void setNmbrInterp20();// { n_interp = 20; interpolator->SetDblLncz(n_interp); }
	//void updt_n_interp();
	//void newClbTblPrc(); // ������������ ����� ������������� �������
	//void setClbTblPrc(); // ���������� ������� ������� ��� �������������
	//void getClbTblPrc(); // ��������� ����� �������������� ������������� �������

	void setPxSc(int pp);// { PxSc = pp; pvw->setPixelScale(PxSc); pvHist->setPixelScale(PxSc);  update(); }
	void setPxGrSc(int pp) { PxGrSc = pp; clWdgt->setPixelScale(PxGrSc); update(); }
	void updtpics() {	pvw->setpicdata(R, G3, B); if(beg_line!=-1) sendClWf(); /*	pvHist->setpicdata(R, G3, B);*/ update(); }

	void setDarkLevel(); // ��������� ������ ��������� ����

	void br_ch(int br) { bright = br; }
	void cn_ch(int cn) { contrast = cn; }
	void gm_ch(int gm) { gamma = gm; }

	void setClrs(int res) { pvw->setBrCnGm(bright, contrast, gamma);	clWdgt->getPicPnt()->setBrCnGm(bright, contrast, gamma); update(); }

	void setTol(double tol) { usr_eps = tol;spBox_tol->setSingleStep(usr_eps / 2.0); clWdgt->setApptxTol(tol); }
	void setNittr(int nitr) { usr_Nittr = nitr; clWdgt->setApptxNitr(nitr); }


	void help();
	void helpsummary(); // ������ �������� ���������
	void helpstrline(); // ���������� �����
	void helpcalibrt(); // ����������
	void helpspctlns(); // ��������� ������������ �����


	void AboutMsg();
	void AboutMsgQt();


	
protected:
	void keyPressEvent(QKeyEvent *event);
private:

	void setUpConnections(); // ��������� ������� ��������

	void badPixelsRemove(FullMatrix<unsigned short> &M); // ������ ������� ����������� �� ������� ����� �������� � ����������� ���� ������� ������� ������������ �� ��������� ������� 

//	void setFlScrPic(); //��������� �������� ��� �������������� �����������

	bool okToContinue();
	void setCurrentFile(const QString &fileName);
	
	void loadbin();
	void savebin(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B,const QString &fileName);


	void addImage(FullMatrix<unsigned short> &R,FullMatrix<unsigned short> &G1,FullMatrix<unsigned short> &G2,FullMatrix<unsigned short> &B); // �������� ������ � ������ ������ � �������
	
	void improveSpLines(); // ��������� ���������� ������������ ����� � ������������� ����� ����������� ���������� ����� � ������������

	void setup_ImpSpcLns(); // ��������� ����������� ���������� ��� ���������� ������������ ����� 



	//double BaseLevel(double *x,int Nlen);// ����������� ������� ����� ��� ������� ��  

	//std::valarray<unsigned short> R,G1,G2,B;
	FullMatrix<unsigned short> R,G1,G2,B,G3;
	FullMatrix<double> AC; // ������� ��������������

	FullMatrix<double> dbR, dbG1, dbG2, dbB; // ������� ����������������� ���������� ����������� (���������� ����� �������)
	vec4FMdouble dbRGB; // ������� ������� ������� ���������� (������� ���������� ������������ �����)

	vecT< vec4FMushort > Img_datas; // ������ ������ � ������� � ����������� ������� 
	int actual_pic_id; // ����� ���������� �������

	vecdb lhlpvr; // ��������������� ������
	//FullMatrix<unsigned short> LocR, LocG1, LocG2, LocB; // ��������������� �������

	QRect wfrm_rect;
	int acnx,acny; 
	//int wf_id_x,wf_id_y; // ������� ������� �������. (����� ��� ���� �������� ������ ����������)
	
	int PxSc;// ������ ���������� ������� ��� ����������� �������� �������
	int PxGrSc; // �������� ��� ������� ������� (���������� PxSc)

	double darkLevelR; // ������� ������� ��������
	double darkLevelG1; // ������� ������� ��������
	double darkLevelG2; // ������� ������� ��������
	double darkLevelB; // ������� ������� ��������
	bool isDarkLevel; // ��������� ��������� ������ ����

	int m_line; // ����� ������� ������ - ��� ������ ������������ ������������ �����
	int beg_line; // �����  ������ ������� ������������ �������
	int end_line; // �����  ����� ������� ������������ �������
	int beg_col; // �����  ������ ������� ������������ �������
	int end_col; // �����  ����� ������� ������������ �������
	int n_interp; // ���������� ������������ - ��� ������ ������������ ����������� �����
	vec4T<vecint> shfts_lines;  // ������� �������� ����� ��� ������������ 
	vec4T<vecdb> ClbrIntrpSpctrs; // ������������� ������� ���������� �� ����������� � ������
	vec4T<vecdb> IntrpSpectrs; // ������� ���������� ������������ � �������
	vec4T<vecT<SparseMatr<double>>> Mtrxs; // ������� ��� ������������ ����� ����������� - ��� �������� ������������ �����
	vec4T<vecdb> kxz, bxz; // ������������ ��� �������� ����� - ��� ������������ ������������ �����

	vec4T<vecdb> LmbdsInterp; // ������� ���� ����
	vec4T<vecdb> ClbrSpercts; // ������� ������������� �������� ���������� ����� ����������


	int bright, contrast,gamma;// ������� ��������� � ����� - ����� ��� ���� ���������

	int clgr_type; // ��� ������� 0 - clbr; 1 - wrk


	//QStringList recentFiles;
	QString curFile;
	QString curDir;



/*	vecT<FullMatrix<double>> CalibrTables; // ����� ������������� ������
	vecT<vecT<int>> ImgClb_ids; // ������ �������� ��������� �� Img_datas ��������������� ������������� ��������
	vecT<vecT<int>> ImgWrk_ids; // ������ �������� ��������� �� Img_datas ��������������� ������� ��������
	vecT<vec2int> line_ids; // ������ ������� ����� ������� ������� ��� ������� �������� ������ (��������� � ���� ����� ������������� � ������� ��������)
*/
	QDialog *size_setup_box; // ������ ��� ��������� ������� �����������
	QSpinBox *spBox_1, *spBox_2; // 

	QDialog *pic_setup_box; // ������ ��� ��������� ���������� �����������
	QSlider *bright_sldr, *contrast_sldr, *gamma_sldr; // �������� ��� ��������� ������� � ���������

	QVBoxLayout *pvbox1;
	QHBoxLayout *phbox1, *phbox2, *phbox3;
	QAction *pactionPictureSetup; // �������� - ������� ���� ��������� �������
	QLabel *pcnbr_label, *pcn_lbl, *pbr_lbl, *pgm_lbl;


	QDialog *approx_setup_box; // ������ ��� ��������� ���������� �������������
	QSpinBox  *spBox_Nittr; // ���������� ��� ��������� ���������� �������������
	QDoubleSpinBox *spBox_tol ;
	double usr_eps; // ��������������� ������������� ������� 
	int    usr_Nittr; // ��������������� ������������� ������������ ����� ��������� 


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