#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QVector>
#include <QString>
#include <QChar>
#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
//#include <QCore>
#include "linalg.h"
#include "gaussapprox.h"
#include "lorentsapprox.h"


//class QWidget;

#define NoGraphContextMenuAction			0
#define SelectGraphContextMenuAction		1
#define ZoomGraphContextMenuAction			2
#define PanGraphContextMenuAction			3
#define DataCursorGraphContextMenuAction	4


//class SomeClass;
//typedef void (SomeClass::*SomeClassFunction) (void);
/*
void Invoke(cls1 *pClass, c1vfun funcptr)
{
(pClass->*funcptr)(0);
};*/

/*template<class T>
typedef void (T::*TFun)(void)
template<class T>
void InvokeT(T *cls, TFun * tfun)
{
	cls->*tfun();
}
*/
//class PlotGraph;
//typedef void (PlotGraph::*clFun)( p_vecdb xx, p_vecdb yy);

//typedef void (*clFun) (vecdb &x, vecdb &y); // ��������� �� ������� - ��� ���������� �������� ������� �������� ��� ������� ��������

struct AxsDvdPrm  // ��������� ������ ��� ��������� ��� �������
{
	int nTicks; // ����� ����� �� ���
	double dS; // ������� ���� �������
	double p; // ���������� ������� ���� �������
	double dTicks; // ���� ������� ����� ��  ���
	double mn; // ������� ������ �� ��� 
	double mx; // �������� ������ �� ��� 
	//double dq; // ��������� �������� ������ ��������� (������������ ��� ������������ �� ��������� �������)
	double fst; // �������� ������ �����
	int dpx;	// �������� ������ ����� �� ������ ��� (�������)
	double k;   // ���������� ����������� 
};

class PlotGraph : public QWidget//QGraphicsView
{
	Q_OBJECT
public :
	PlotGraph(QWidget *parent = 0);
	~PlotGraph(){};

	int tp_mxy; // ��� ����������� ��������� �� ��� y
	double user_max_y;

	//clFun Fun; // ��������� �� ������� ������� ��� ���������� � ������� � ������� �������������� ����
	GaussApproximator * p_gsaprx;
	LorentsApproximator *p_loraprx;
	double fun_x1, fun_x2; // ������� ��������� ��������� ������� ������� fun
	double selX, selDX; // �������� ���������� X � ��������� DX;

	vecT<vecint> SelectedIds; // ������ ����� ��������� �� ������� � ������ Select 
	//int ctnx_menu_type;
	//int dw;	// ������ 5 ��������
	//QFont font;

	//QPainter *painter;
	
	void contextMenuEvent(QContextMenuEvent *e);
	

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	//void mouseDoubleClickEvent(QMouseEvent *event)

	void SelPointsSelect(); // ����� ����� � ������ select - ���������� �������� SelectIds
	void ZoomPointsSelect(); // ����� ����� ������������ ��� ������������
	void PanPointsSelect(); // ����� ����� ������������ ��� ����������� �� ��������� �������
	void ZoomReset(); // ����� ��������� ������������ - ������� � ��������� ��������

	void FrameSetUp();//QPainter &painter); // ��������� ���������� ��������� �������
	//void InBuffDraw(QPainter &painter); // ��������� � ����� ������������ ��������� � �������� � ���� �������
	
	void DrawAxisXY(QPainter &painter); // ��������� ���� X � Y ��� ��������
	void DrawTicksX(QPainter &painter); // ��������� �������� ����� 
	void DrawTicksY(QPainter &painter); // ��������� �������� ����� 
	void DrawLabel(QPainter &painter); // ��������� �������� � ����

	void AxDivide(int rxy, int drx, AxsDvdPrm &adp); //  ���������� ������������ ��������� ���,  axtp - ��� ��� 0 - x 1 - y;  //rxy - ����� ������������ ��� � ��������, drx - ������ �� ���� ����� � ��������, dmnmx - ����� ��� � �������� �������

	void DrawSelRect(QPainter &painter);
	void DrawSelLines(QPainter &painter);
	void DrawDataCursorLines(QPainter &painter);

	//void DrawAxes(QPainter &painter);
	void DrawOnAx(QPainter &painter);
	void DrawFunOnAx(QPainter &painter);
	//void DrawOnAx(QPainter &painter,QVector<double> &x,QVector<double> &y);

	void setFundata(); // ������������ ������ ��� ��������� ����� �������������
	void setFundata2();
	
	inline void setTcsTpx(int n){ticstypex=n;}
	inline void setTcsTpy(int n) { ticstypey = n; }
	inline void xlabel(const QString &s){xname = s;}
	inline void ylabel(const QString &s){yname = s;}
	inline void xlabel(char *s){xname = QString(s);}
	inline void ylabel(char *s){yname = QString(s);}
	void setmnmx();
	void setmnmx_my();
	void adpmnmx() { adpX.mn = mnmx[0];adpX.mx = mnmx[1]; adpY.mn = mnmx[2];  adpY.mx = mnmx[3]; }
	
	inline void setXdata(int id, double *xx, const int N);
	inline void setYdata(int id, double *yy, const int N);
	inline void setXdata(int id, vecdb &xx) { Xdata.x[id].pst(xx); }
	inline void setYdata(int id, vecdb &yy) { Ydata.x[id].pst(yy); }
	inline void setXdata(vecdb &xx) { for (int id = 0;id < Xdata.N; id++) Xdata.x[id].pst(xx); }
	inline void setYdata(vecdb &xx) { for (int id = 0;id < Ydata.N; id++) Ydata.x[id].pst(xx); }

	int getNgrphx() { return Xdata.N; } // ������� ���������� �������� 
	void setNgrphx(int ngr = 1); // ���������� ���������� �������� (�� ��������� -1)
	void clearAll(); // ������� ��� ������ � ��������
	void rsz_All(int nw); // �������������� ����� ����� ������ ��� ��������

	vec2db getLocPos(int xpos, int ypos); // ����������� ��������� ����� �� ������� �� � ����������� �� �������
	int get_lShift() { return  frame[0]; } // ���������� ���������� �������� �� ������� �������� ������ ������� �� ������ ���� ����� (�������. ��� ��������� �������� �������)


	inline double  dataLength() {  return	 (mnmx[1] - mnmx[0]); } // ����� ������������ ����� ������� �� ��� X � �������� ������� Xdata
	inline double  dataHigh() {  return 	(mnmx[3] - mnmx[2]); } // ������ ������������ ����� ������� �� ��� Y � �������� ������� Ydata
	inline int  pixelLength() { return	 (frame[2] - frame[0]); } // ����� ������������ ����� ������� �� ��� X � ��������
	inline int  pixelHigh() {   return	(frame[3] - frame[1]); } // ������ ������������ ����� ������� �� ��� Y � ��������
	inline double & koeffX() { return adpX.k; }
	inline double & koeffY() { return adpY.k; }

	inline vecT< vecdb > & X() { return Xdata; }
	inline vecT< vecdb > & Y() { return Ydata; }

	void setSelActText(const QString &text);

public	slots:
	void setZoomMode() { cntxMenuItAc = ZoomGraphContextMenuAction;  ZoomFrame = true; update(); }
	void setDfltMode() { cntxMenuItAc = NoGraphContextMenuAction; ZoomFrame = false; isFrameDraw = false; update(); }
	void setPanMode() { cntxMenuItAc = PanGraphContextMenuAction; ZoomFrame = true; update(); }
	void setSelectMode() { cntxMenuItAc = SelectGraphContextMenuAction; ZoomFrame = true; update(); }
	void setDataCursorMode() { cntxMenuItAc = DataCursorGraphContextMenuAction; ZoomFrame = true; update(); }

	void rstcicX() { XTicks0->setIconVisibleInMenu(false);XTicks1->setIconVisibleInMenu(false);	XTicks2->setIconVisibleInMenu(false);	XTicks3->setIconVisibleInMenu(false);}
	void rstcicY() { YTicks0->setIconVisibleInMenu(false);YTicks1->setIconVisibleInMenu(false);	YTicks2->setIconVisibleInMenu(false);	YTicks3->setIconVisibleInMenu(false); }

	void tcksX0() { ticstypex = 0; rstcicX(); XTicks0->setIconVisibleInMenu(true);	update(); }
	void tcksX1() { ticstypex = 1; rstcicX(); XTicks1->setIconVisibleInMenu(true);	update();}
	void tcksX2() { ticstypex = 2; rstcicX(); XTicks2->setIconVisibleInMenu(true);	update();}
	void tcksX3() { ticstypex = 3; rstcicX(); XTicks3->setIconVisibleInMenu(true);	update();}
	void tcksY0() { ticstypey = 0; rstcicY(); YTicks0->setIconVisibleInMenu(true);	update();}
	void tcksY1() { ticstypey = 1; rstcicY(); YTicks1->setIconVisibleInMenu(true);  update();}
	void tcksY2() { ticstypey = 2; rstcicY(); YTicks2->setIconVisibleInMenu(true);  update();}
	void tcksY3() { ticstypey = 3; rstcicY(); YTicks3->setIconVisibleInMenu(true);  update();}

	void graphics2clipboard(); // ���������� ������� � ������

signals:
	void selDataReady(); // ������ � ���, ��� ������ ������ ������
	void selXReady(); // ������ � ���������� ��������� ������ �� x ���
 
protected :
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *event);

private:


	//QGraphicsScene graphScene;
	double mnmx[4]; // ������ ������������ ������� ��������� : min(x) max(x) min(y) max(y)
	int frame[4]; // ������� ��������������  ������������ ���� xn,yn,xx,yx
	//double kx, ky; // ������������ ���������
	vecT< vecdb > Xdata;
	vecT< vecdb > Ydata;
	QString xname;
	QString yname;
	int ticstypex; // ��� ����������� ����� ��� x
	int ticstypey; // ��� ����������� ����� ��� y
	vecT<QColor> clrs; // ����� ��������

	vecT< vecint> Z_idx; //  ������� ������������ ����� ��� ������������

	vecint lix, liy; // ����� ������� ��������� ������� ��������

	//QImage GridBuff;  // ����� ����������� ������������ ����� � �������� � ��������


	const double wAx[5] = { 1,2,3,4,5 };  // ���������� �������� ������� ���� �������
	
	int Nticks;	// ����� �����;

	int dwX; // ������������ ������ ������-������� ����� ��� ������ ������� �� �������
	int dwY; // ������ ������-������� ����� � ����� �� �������
	int dw_; // ������ ������� ��� Y �� ������ ���� ����� ������� �������
	//int dxzr;// �������� ������ ����� �� ��� x
	//int dyzr;// �������� ������ ����� �� ��� y
	//int nXticks; // ���������� ����� �� ��� X
	//int nYticks; // ���������� ����� �� ��� Y
	//double dXticks; // ���� ������� ����� ��  ��� X
	//double d�ticks; // ���� ������� ����� ��  ��� Y
	int tickLength; // ����� ����� (�������� �� 2 ;   ����� 2  �� ��������� )

	/*double dsX; // ������� ���� ������� �� ��� X
	double dsY; // ������� ���� ������� �� ��� Y
	double pX; // ���������� ������� ��� ���� ������� �� ��� X
	double pY; // ���������� ������� ��� ���� ������� �� ��� Y*/

	AxsDvdPrm adpX; // ��������� ��������� ��� x
	AxsDvdPrm adpY; // ��������� ��������� ��� y

	QString hStr; // ������ ��� ��������� ������


	QLabel *xps_dsl;
	QLabel *yps_dsl;

	QMenu *dftCnxMn; // ����������� ����
	QMenu *LogScale; // ������� ��� �������������� ��������
	QMenu *TicksTp; // ������� ������ ����� �����
	QMenu *TicksX; // ������� ������ ����� �����
	QMenu *TicksY; // ������� ������ ����� �����
	QAction *dflCnAc; // ����� �� ��������� - ��� ������� ����������� ��������
	QAction *SelectAction; // ������� � ����� ��������� ������� �� �������
	QAction *ZoomAction; // ������� � ����� ��������� ��������
	QAction *PanAction; // ������� � ����� ����������� �� ��������� �������
	QAction *DataCursorAction; // ������� � ����� ����������� ������ �� �������
	QAction *Log_Lin_Y; // ������������ ����� ��������������� � �������� ���������
	QAction *Log_Lin_X; // ������������ ����� ��������������� � �������� ���������

	QAction *XTicks0; //  ����� �� ��� X ���� 0
	QAction *XTicks1; //  ����� �� ��� X ���� 1
	QAction *XTicks2; //  ����� �� ��� X ���� 2
	QAction *XTicks3; //  ����� �� ��� X ���� 3

	QAction *YTicks0; //  ����� �� ��� Y ���� 0
	QAction *YTicks1; //  ����� �� ��� Y ���� 1
	QAction *YTicks2; //  ����� �� ��� Y ���� 2
	QAction *YTicks3; //  ����� �� ��� Y ���� 3


	QAction *Copy2ClipBoadrd; // ���������� ������� � �����

	QIcon *galcaIcon;

	int cntxMenuItAc; // ��� ��������� ������ ������������ ����

	//QRect VisRegion;  // ������������� ������� ����� �������
	int beg_id_x, beg_id_y; // ������� ������� ���� �������������� ��������� �������
	int end_id_x, end_id_y; // ������� ���������������� ���� ��������������

	int idx0,  idy0; // ������� ������ ������� �������� ���� � ������ Pan
	int d_idx, d_idy; // ������� ��������

	bool isFrameDraw; // ��������� ��������� ����� ������������
	bool inActiveMove; // ��������� ��������� �������� ���� - ��� ������� ���� ����������� �������
	bool ZoomFrame; // ��������� ������� ������ ������� ������� �������. true - ����������� �� �������� �����;  false - ����������� �� ������
	bool selFrame; // ��������� ��������� ������� ������
	bool isXDataReg; // ��������� ��������� ������� ��������� �� x-���
	bool isYDataReg; // ��������� ��������� ������� ��������� �� y-���
	bool fungron; // ��������� �������� ��������������� �������

	
	
};

//PlotGraph::wax = { 1.,2.,3.,4.,5. };
#endif