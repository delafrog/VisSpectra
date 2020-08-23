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

//typedef void (*clFun) (vecdb &x, vecdb &y); // указатель на функцию - для построения графиков заанных формулой или внешней функцией

struct AxsDvdPrm  // структура данных для разбиения оси метками
{
	int nTicks; // число меток на оси
	double dS; // мантиса цены деления
	double p; // показатель степени цены деления
	double dTicks; // цена деления меток по  оси
	double mn; // минимум данных по оси 
	double mx; // максимум данных по оси 
	//double dq; // локальное смещение начала координат (используется при пееремещении по плоскости графика)
	double fst; // значение первой метки
	int dpx;	// смещение первой метки от начала оси (пиксели)
	double k;   // масштабный коэффициент 
};

class PlotGraph : public QWidget//QGraphicsView
{
	Q_OBJECT
public :
	PlotGraph(QWidget *parent = 0);
	~PlotGraph(){};

	int tp_mxy; // тип отображения максимума по оси y
	double user_max_y;

	//clFun Fun; // указатель на внешнюю функцию для построения её графика в заранее сформированных осях
	GaussApproximator * p_gsaprx;
	LorentsApproximator *p_loraprx;
	double fun_x1, fun_x2; // границы диапазона рисования графика функции fun
	double selX, selDX; // значения выбранного X и интервала DX;

	vecT<vecint> SelectedIds; // номера точек выбранных на графике в режиме Select 
	//int ctnx_menu_type;
	//int dw;	// ширина 5 символов
	//QFont font;

	//QPainter *painter;
	
	void contextMenuEvent(QContextMenuEvent *e);
	

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	//void mouseDoubleClickEvent(QMouseEvent *event)

	void SelPointsSelect(); // выбор точек в режиме select - заполнение массивов SelectIds
	void ZoomPointsSelect(); // выбор точек отображаемых при зуммировании
	void PanPointsSelect(); // выбор точек отображаемых при перемещении по плоскости графика
	void ZoomReset(); // сброс параметро зуммирования - возврат к исходному масштабу

	void FrameSetUp();//QPainter &painter); // настройка параметров рисования графика
	//void InBuffDraw(QPainter &painter); // рисование в буфер координатной плоскости и подписей к осям графика
	
	void DrawAxisXY(QPainter &painter); // рисование осей X и Y без подписей
	void DrawTicksX(QPainter &painter); // рисование числовых меток 
	void DrawTicksY(QPainter &painter); // рисование числовых меток 
	void DrawLabel(QPainter &painter); // рисование подписей к осям

	void AxDivide(int rxy, int drx, AxsDvdPrm &adp); //  вычисление оптимального разбиения оси,  axtp - тип оси 0 - x 1 - y;  //rxy - длина отображаемой оси в пикселях, drx - ширина на одну метку в пикселях, dmnmx - длина оси в единицах графика

	void DrawSelRect(QPainter &painter);
	void DrawSelLines(QPainter &painter);
	void DrawDataCursorLines(QPainter &painter);

	//void DrawAxes(QPainter &painter);
	void DrawOnAx(QPainter &painter);
	void DrawFunOnAx(QPainter &painter);
	//void DrawOnAx(QPainter &painter,QVector<double> &x,QVector<double> &y);

	void setFundata(); // формирование данных для рисования линии аппроскимации
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

	int getNgrphx() { return Xdata.N; } // вернуть количество графиков 
	void setNgrphx(int ngr = 1); // установить количество графиков (по умолчанию -1)
	void clearAll(); // удалить все данные о графиках
	void rsz_All(int nw); // переустановить новую длину данных для графиков

	vec2db getLocPos(int xpos, int ypos); // определение координат точки на графике по её координатам на рисунке
	int get_lShift() { return  frame[0]; } // возвращает количество пискелей на которое сдвинуто начало графика от левого края рамки (использ. для рисования картинки спектра)


	inline double  dataLength() {  return	 (mnmx[1] - mnmx[0]); } // длина отображаемой части графика по оси X в единицах величин Xdata
	inline double  dataHigh() {  return 	(mnmx[3] - mnmx[2]); } // высота отображаемой части графика по оси Y в единицах величин Ydata
	inline int  pixelLength() { return	 (frame[2] - frame[0]); } // длина отображаемой части графика по оси X в пикселях
	inline int  pixelHigh() {   return	(frame[3] - frame[1]); } // высота отображаемой части графика по оси Y в пикселях
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

	void graphics2clipboard(); // копировать графики в буффер

signals:
	void selDataReady(); // сигнал о том, что данные выбора готовы
	void selXReady(); // сигнал о готовности выбранных данных по x оси
 
protected :
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *event);

private:


	//QGraphicsScene graphScene;
	double mnmx[4]; // размер отображаемой области плоскости : min(x) max(x) min(y) max(y)
	int frame[4]; // размеры прямоугольника  координатынх осей xn,yn,xx,yx
	//double kx, ky; // коэффициенты масшатаба
	vecT< vecdb > Xdata;
	vecT< vecdb > Ydata;
	QString xname;
	QString yname;
	int ticstypex; // тип отображения шкалы оси x
	int ticstypey; // тип отображения шкалы оси y
	vecT<QColor> clrs; // цвета графиков

	vecT< vecint> Z_idx; //  индексы отображаемых точек при зуммировании

	vecint lix, liy; // линия графика заданного внешней функцией

	//QImage GridBuff;  // буфер изображения координатной сетки и подписей к графикам


	const double wAx[5] = { 1,2,3,4,5 };  // допустимые значения мантисы цены деления
	
	int Nticks;	// число меток;

	int dwX; // максимальная ширина строки-надписи числа под меткой деления на графике
	int dwY; // высота строки-надписи числа у метки на графике
	int dw_; // ширина отступа оси Y от левого края рамки видимой области
	//int dxzr;// смещение первой метки по оси x
	//int dyzr;// смещение первой метки по оси y
	//int nXticks; // количество меток на оси X
	//int nYticks; // количество меток на оси Y
	//double dXticks; // цена деления меток по  оси X
	//double dНticks; // цена деления меток по  оси Y
	int tickLength; // длина меток (делённаая на 2 ;   равна 2  по умолчанию )

	/*double dsX; // матниса цены деления по оси X
	double dsY; // матниса цены деления по оси Y
	double pX; // показатель степени для цены деления по оси X
	double pY; // показатель степени для цены деления по оси Y*/

	AxsDvdPrm adpX; // параметры разбиения оси x
	AxsDvdPrm adpY; // параметры разбиения оси y

	QString hStr; // строка для отрисвоки текста


	QLabel *xps_dsl;
	QLabel *yps_dsl;

	QMenu *dftCnxMn; // контекстное меню
	QMenu *LogScale; // подменю для переключателей масштаба
	QMenu *TicksTp; // подменю выбора типов шкалы
	QMenu *TicksX; // подменю выбора типов шкалы
	QMenu *TicksY; // подменю выбора типов шкалы
	QAction *dflCnAc; // режим по умолчанию - нет никаких специальных действий
	QAction *SelectAction; // переход в режим выделения области на графике
	QAction *ZoomAction; // переход в режим изменения масштаба
	QAction *PanAction; // переход в режим перемещения по плоскости графика
	QAction *DataCursorAction; // переход в режим отображения данных на графике
	QAction *Log_Lin_Y; // переключение между логарифмическим и линейным масштабом
	QAction *Log_Lin_X; // переключение между логарифмическим и линейным масштабом

	QAction *XTicks0; //  мекти на оси X типа 0
	QAction *XTicks1; //  мекти на оси X типа 1
	QAction *XTicks2; //  мекти на оси X типа 2
	QAction *XTicks3; //  мекти на оси X типа 3

	QAction *YTicks0; //  мекти на оси Y типа 0
	QAction *YTicks1; //  мекти на оси Y типа 1
	QAction *YTicks2; //  мекти на оси Y типа 2
	QAction *YTicks3; //  мекти на оси Y типа 3


	QAction *Copy2ClipBoadrd; // копировать графики в буфер

	QIcon *galcaIcon;

	int cntxMenuItAc; // тип активного пункта контекстного меню

	//QRect VisRegion;  // прямоугольник рабочей части графика
	int beg_id_x, beg_id_y; // индексы первого угла прямоугольника выделения области
	int end_id_x, end_id_y; // индексы противоположного улга прямоугольника

	int idx0,  idy0; // индексы начала вектора смещения мыши в режиме Pan
	int d_idx, d_idy; // индексы смещения

	bool isFrameDraw; // индикатор рисования рамки зуммирования
	bool inActiveMove; // индикатор активного движения мыши - при двжении мыши перерисовка виджета
	bool ZoomFrame; // индикатор способа выбора рабочей области графика. true - определение по заданной рамке;  false - определение по данным
	bool selFrame; // индикатор рисования области выбора
	bool isXDataReg; // индикатор рисования области выделения по x-оси
	bool isYDataReg; // индикатор рисования области выделения по y-оси
	bool fungron; // индикатор рисовния апроксимирующей функции

	
	
};

//PlotGraph::wax = { 1.,2.,3.,4.,5. };
#endif