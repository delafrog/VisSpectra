#ifndef PLOTGRAPH_CPP
#define PLOTGRAPH_CPP

#include <QWidget>
#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <math.h>
#include "plotgraph.h"
#include <QBrush>
#include <QColor>
#include <QClipboard>
#include <QApplication>
//#include "mainwin.h"
//#include "linalg.cpp"
#include "linalg.h"


PlotGraph::PlotGraph(QWidget * parent) :  QWidget(parent)//QGraphicsView(parent)
{
	mnmx[0]=0;
	mnmx[1]=1;
	mnmx[2]=0;
	mnmx[3]=1;

	adpX.mn = mnmx[0];
	adpX.mx = mnmx[1];
	adpY.mn = mnmx[2];
	adpY.mx = mnmx[3];

//	adpX.dq = 0.;
//	adpY.dq = 0.;
 
	tickLength = 2;

//	dxzr = 0;
//	dyzr = 0;
//	Fun = 0x0;
	p_gsaprx = 0x0;
	p_loraprx = 0x0;
	fun_x1 = fun_x2 = 0;

	selX = selDX = 0.0;
	
	xlabel(QString("Axis X"));
	ylabel(QString("Axis Y"));
//	ticstypex = 0;
//	ticstypey = 0;
	setMinimumSize(50,20);

	tp_mxy = 0;
	user_max_y = 0;

	Xdata.x = 0x0;
	Ydata.x = 0x0;
	Z_idx.x = 0x0;
	SelectedIds.x = 0x0;

	clrs.setlen(10);
	clrs.x[0] = Qt::red;
	clrs.x[1] = Qt::green;
	clrs.x[2] = Qt::darkGreen;
	clrs.x[3] = Qt::blue;
	clrs.x[4] = Qt::darkBlue;
	clrs.x[5] = Qt::cyan;
	clrs.x[6] = Qt::darkCyan;
	clrs.x[7] = Qt::darkMagenta;
	clrs.x[8] = Qt::darkYellow;
	clrs.x[9] = Qt::darkGray;

	//ctnx_menu_type = 0;

	xps_dsl = new QLabel(QString("0.0"));
	yps_dsl = new QLabel(QString("0.0"));

	dftCnxMn	= new QMenu(this);
	LogScale = new QMenu(tr("Axes Scale"),this);

	dflCnAc		= new QAction(tr("default"), this);
	SelectAction = new QAction (tr("Select"),this); // переход в режим выделения области на графике
	ZoomAction   = new QAction (tr("Zoom"),this); // переход в режим изменения масштаба
	PanAction = new QAction (tr("Pan"),this); // переход в режим перемещения по плоскости графика
	DataCursorAction = new QAction (tr("DataCursor"),this); // переход в режим отображения данных на графике

	Log_Lin_Y  = new QAction (tr("Log/Lin Scale Y"),this); // переключение между логарифмическим и линейным масштабом
	Log_Lin_X  = new QAction (tr("Log/Lin Scale X"),this); // переключение между логарифмическим и линейным масштабом

	dftCnxMn->addAction(dflCnAc);
	dftCnxMn->addAction(SelectAction);
	dftCnxMn->addAction(ZoomAction);
	dftCnxMn->addAction(PanAction);
	dftCnxMn->addAction(DataCursorAction);



	LogScale->addAction(Log_Lin_X);
	LogScale->addAction(Log_Lin_Y);

	galcaIcon = new QIcon(QString("galka2.png"));

	TicksTp = new QMenu (tr("Axes ticks types"),this); // подменю выбора типов шкалы
	TicksX = new QMenu(tr("X axis "), this); // подменю выбора типов шкалы
	TicksY = new QMenu(tr("Y axis "), this); // подменю выбора типов шкалы


	XTicks0 = new QAction(tr("Simple scale"),this); //  мекти на оси X типа 0
	XTicks1 = new QAction(tr("Factor scale "), this); //  мекти на оси X типа 1
	XTicks2 = new QAction(tr("Zero at begin "), this); //  мекти на оси X типа 2
	XTicks3 = new QAction(tr("Zero in center "), this); //  мекти на оси X типа 3

	YTicks0 = new QAction(tr("Simple scale"), this); //  мекти на оси X типа 0
	YTicks1 = new QAction(tr("Factor scale "), this); //  мекти на оси X типа 1
	YTicks2 = new QAction(tr("Zero at begin "), this); //  мекти на оси X типа 2
	YTicks3 = new QAction(tr("Zero in center "), this); //  мекти на оси X типа 3

	Copy2ClipBoadrd = new QAction(tr("Copy graphics to clipboard"), this); // коировать графики в буфер

	XTicks0->setIcon(*galcaIcon);
	XTicks1->setIcon(*galcaIcon);
	XTicks2->setIcon(*galcaIcon);
	XTicks3->setIcon(*galcaIcon);

	YTicks0->setIcon(*galcaIcon);
	YTicks1->setIcon(*galcaIcon);
	YTicks2->setIcon(*galcaIcon);
	YTicks3->setIcon(*galcaIcon);

	TicksX->addAction(XTicks0);
	TicksX->addAction(XTicks1);
	TicksX->addAction(XTicks2);
	TicksX->addAction(XTicks3);

	TicksY->addAction(YTicks0);
	TicksY->addAction(YTicks1);
	TicksY->addAction(YTicks2);
	TicksY->addAction(YTicks3);


	TicksTp->addMenu(TicksX);
	TicksTp->addMenu(TicksY);
	

	dftCnxMn->addMenu(LogScale);
	dftCnxMn->addMenu(TicksTp);
	dftCnxMn->addSeparator();
	dftCnxMn->addAction(Copy2ClipBoadrd);

	cntxMenuItAc = NoGraphContextMenuAction; 

	beg_id_x = beg_id_y = end_id_x = end_id_y = 0;




	dw_ = this->fontMetrics().width("-0.000000");// textwidth("0.000")+3; // ширина 5 символов
	dwX = this->fontMetrics().width("-0.000"); // ширина подписи-метки
	dwY = this->fontMetrics().height()+3; // высота подписи-метки

	//connect(setHln, SIGNAL(clicked()), this, SLOT(hrznalgm()));
	connect(SelectAction, SIGNAL(triggered()), this, SLOT(setSelectMode()));
	connect(ZoomAction, SIGNAL(triggered()), this, SLOT(setZoomMode()));
	connect(PanAction, SIGNAL(triggered()), this, SLOT(setPanMode()));
	connect(dflCnAc, SIGNAL(triggered()), this, SLOT(setDfltMode()));
	connect(DataCursorAction, SIGNAL(triggered()), this, SLOT(setDataCursorMode()));

	connect(XTicks0, SIGNAL(triggered()), this, SLOT(tcksX0()));
	connect(XTicks1, SIGNAL(triggered()), this, SLOT(tcksX1()));
	connect(XTicks2, SIGNAL(triggered()), this, SLOT(tcksX2()));
	connect(XTicks3, SIGNAL(triggered()), this, SLOT(tcksX3()));

	connect(YTicks0, SIGNAL(triggered()), this, SLOT(tcksY0()));
	connect(YTicks1, SIGNAL(triggered()), this, SLOT(tcksY1()));
	connect(YTicks2, SIGNAL(triggered()), this, SLOT(tcksY2()));
	connect(YTicks3, SIGNAL(triggered()), this, SLOT(tcksY3()));

	connect(Copy2ClipBoadrd, SIGNAL(triggered()), this, SLOT(graphics2clipboard()));


	isFrameDraw		= false;
	inActiveMove	= false;
	ZoomFrame		= false;
	selFrame		= false;

	isXDataReg = false;
	isYDataReg = false;

	fungron = false;

	tcksX1();
	tcksY1();
}


void PlotGraph::setXdata(int id, double *xx,const int N)
{
	Xdata.x[id].N = 0;
	Xdata.x[id].add(xx, N);
}
void PlotGraph::setYdata(int id, double *yy, const int N)
{
	Ydata.x[id].N = 0;
	Ydata.x[id].add(yy, N);
}

void PlotGraph::paintEvent(QPaintEvent *event)
{
	//static long itr;
	QPainter painter;
	painter.begin(this);

	setUpdatesEnabled(true);

	painter.setBackground(QBrush(QColor(255,255,255,255)));
	
	painter.eraseRect(this->rect());
 	painter.setRenderHint(QPainter::Antialiasing,false);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	//painter.drawEllipse(20,10,350,100);
	if (Xdata.x[0].N > 2)
	{
		if (!ZoomFrame)
		{
			if (tp_mxy == 0) { setmnmx(); }	else { setmnmx_my(); }
			adpmnmx();
		}
		FrameSetUp();
		DrawAxisXY(painter);
		DrawTicksX(painter);
		DrawTicksY(painter);
		DrawLabel(painter);
		DrawOnAx(painter);
	}else
	{
		//DrawAxes(painter);
		FrameSetUp();
		DrawAxisXY(painter);
		DrawTicksX(painter);
		DrawTicksY(painter);
		DrawLabel(painter);
	}

	//painter.drawText(100,100,QString().setNum(itr));
	//itr++;

	//setUpdatesEnabled(true);
	//setUpdatesEnabled(false);

	if (isFrameDraw)
	{
		DrawSelRect(painter);
	}
	if (selFrame)
	{
		DrawSelLines(painter);
	}
	if (isXDataReg)
	{
		DrawDataCursorLines(painter);
	}


	if (fungron) {		DrawFunOnAx(painter);	}

	painter.end();
	

	event->accept();
}

void PlotGraph::setmnmx()
{
	double h,*x;
	int *iz;
	mnmx[0] = 1e200;
	mnmx[1] = -1e200;
	mnmx[2] = 1e200;
	mnmx[3] = -1e200;

	for(int i = 0;i<Z_idx.N;i++)
	{
		iz = Z_idx.x[i].x;
		x = Xdata.x[i].x;
		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h > x[iz[jj]] ? x[iz[jj]] : h; } // min X
		mnmx[0] = mnmx[0]>h ? h : mnmx[0];

		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h < x[iz[jj]] ? x[iz[jj]] : h; } // max X
		mnmx[1] = mnmx[1]<h ? h : mnmx[1];

		x = Ydata.x[i].x;
		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h > x[iz[jj]] ? x[iz[jj]] : h; } // min Y
		mnmx[2] = mnmx[2]>h ? h : mnmx[2];

		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h < x[iz[jj]] ? x[iz[jj]] : h; } // max Y
		mnmx[3] = mnmx[3]<h ? h : mnmx[3];
	}

	if (mnmx[1] == mnmx[0]) { mnmx[1]++;mnmx[0]--; }
	if (mnmx[3] == mnmx[2]) { mnmx[3]++;mnmx[2]--; }
}

void PlotGraph::setmnmx_my()
{
	double h, *x;
	int *iz;
	mnmx[0] = 1e200;
	mnmx[1] = -1e200;
	mnmx[2] = 1e200;
	mnmx[3] = -1e200;
	/*for(int i = 0;i<Xdata.N;i++)
	{
		h = Xdata.x[i].min();
		mnmx[0] = mnmx[0]>h ? h : mnmx[0];
		h = Xdata.x[i].max();
		mnmx[1] = mnmx[1]<h ? h : mnmx[1];
		h = Ydata.x[i].min();
		mnmx[2] = mnmx[2]>h ? h : mnmx[2];
	}*/

	for (int i = 0;i<Z_idx.N;i++)
	{
		iz = Z_idx.x[i].x;
		x = Xdata.x[i].x;
		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h > x[iz[jj]] ? x[iz[jj]] : h; } // min X
		mnmx[0] = mnmx[0]>h ? h : mnmx[0];

		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h < x[iz[jj]] ? x[iz[jj]] : h; } // max X
		mnmx[1] = mnmx[1]<h ? h : mnmx[1];

		x = Ydata.x[i].x;
		h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h > x[iz[jj]] ? x[iz[jj]] : h; } // min Y
		mnmx[2] = mnmx[2]>h ? h : mnmx[2];

		/*h = x[iz[0]];
		for (int jj = 1;jj < Z_idx.x[i].N;jj++) { h = h < x[iz[jj]] ? x[iz[jj]] : h; } // max Y
		mnmx[3] = mnmx[3]<h ? h : mnmx[3];
		*/
	}

	mnmx[3] = user_max_y;

	if (mnmx[1] == mnmx[0]) { mnmx[1]++;mnmx[0]--; }
	if (mnmx[3] == mnmx[2]) { mnmx[3]++;mnmx[2]--; }
}

void PlotGraph::setNgrphx(int ngr ) // установить количество графиков (по умолчанию -1)
{
	clearAll();
	Xdata.setlen(ngr);
	Ydata.setlen(ngr);
	Z_idx.setlen(ngr);
	SelectedIds.setlen(ngr);
}
void PlotGraph::clearAll() // удалить все данные о графиках
{
	if(Xdata.x!=0x0)
	{
		delete [] Xdata.x;
		Xdata.x =0x0;
	}
	if(Ydata.x!=0x0)
	{
		delete [] Ydata.x;
		Ydata.x =0x0;
	}
	if (Z_idx.x != 0x0)
	{
		delete[] Z_idx.x;
		Z_idx.x = 0x0;
	}
}

void PlotGraph::rsz_All(int nw) // переустановить новую длину данных для графиков
{
	if(Xdata.x!=0x0)
	{
		for(int ii=0;ii<Xdata.N;ii++)
		{
			Xdata.x[ii].fsetlen(nw);
			Ydata.x[ii].fsetlen(nw);
			Z_idx.x[ii].fsetlen(nw);
		}
	}
}

void PlotGraph::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (cntxMenuItAc != NoGraphContextMenuAction)
		{
			idx0 = beg_id_x = event->x();
			idy0 = beg_id_y = event->y();
			fungron = false;
			isXDataReg = false;

			switch (cntxMenuItAc)
			{
			case SelectGraphContextMenuAction:
				fungron = false;
				break;
				/*case ZoomGraphContextMenuAction:
				{
					break;
				}
				case PanGraphContextMenuAction:
					break;
				case DataCursorGraphContextMenuAction:
					break;*/
			case DataCursorGraphContextMenuAction:
				isXDataReg = true;
				end_id_x = beg_id_x;
				end_id_y = beg_id_y;
				/*isFrameDraw = false;
				inActiveMove = false;
				end_id_x = event->x();
				end_id_y = event->y();
				update();
				event->accept();*/
				break;
			default:
				//event->ignore();
				break;
			}
			event->accept();
		}
		else
		{
			event->ignore();
		}
	}
}

void PlotGraph::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (cntxMenuItAc != NoGraphContextMenuAction)
		{
			if (inActiveMove)
			{
				switch (cntxMenuItAc)
				{
				case ZoomGraphContextMenuAction:
					end_id_x = event->x();
					end_id_y = event->y();
					isFrameDraw = false;
					inActiveMove = false;
					ZoomFrame = true;
					ZoomPointsSelect();
					update();
					event->accept();
					break;
				case PanGraphContextMenuAction:
					inActiveMove = false;
					ZoomFrame = true;
					PanPointsSelect();
					d_idx = 0;
					d_idy = 0;
					update();
					event->accept();
					break;
				case SelectGraphContextMenuAction:
					selFrame = false;
					end_id_x = event->x();
					end_id_y = event->y();
					SelPointsSelect();
					selDataReady();
					fungron = true;
					update();
					event->accept();
					break;

				case DataCursorGraphContextMenuAction:
					//isXDataReg = false;
					isFrameDraw = false;
					inActiveMove = false;
					end_id_x = event->x();
					end_id_y = event->y();
					
				
					
					update();
					event->accept();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			event->ignore();
		}
	}
}

void PlotGraph::mouseMoveEvent(QMouseEvent * event)
{
	//if ( == Qt::LeftButton)
	{
		if (cntxMenuItAc != NoGraphContextMenuAction)
		{
			switch (cntxMenuItAc)
			{
			case ZoomGraphContextMenuAction:
				isFrameDraw = true;
				inActiveMove = true;
				end_id_x = event->x();
				end_id_y = event->y();
				update();
				event->accept();
				break;
			case PanGraphContextMenuAction:
				double dd;
				//int dn;
				inActiveMove = true;
				ZoomFrame = true;
				d_idx = idx0;
				d_idy = idy0;
				idx0 = event->x();
				idy0 = event->y();
				d_idx -= idx0;
				d_idy -= idy0;
				dd = double(d_idx) / adpX.k;
				adpX.mn += dd;
				adpX.mx += dd;
				dd = double(d_idy) / adpY.k;
				adpY.mn += dd;
				adpY.mx += dd;
				PanPointsSelect();
				update();
				event->accept();
				break;
			case SelectGraphContextMenuAction:
				inActiveMove = true;
				selFrame = true;
				end_id_x = event->x();
				end_id_y = event->y();
				update();
				event->accept();
				break;
			case DataCursorGraphContextMenuAction:
				isXDataReg = true;
				isFrameDraw = false;
				inActiveMove = true;
				end_id_x = event->x();
				end_id_y = event->y();
			
				update();
				event->accept();
				break;
			default:
				break;
			}						
		}
		else
		{
			event->ignore();
		}
	}
}

void PlotGraph::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (cntxMenuItAc == ZoomGraphContextMenuAction)
	{
		ZoomReset();
		isFrameDraw = false;
		ZoomFrame = false;
		update();
		event->accept();
	}
}


void PlotGraph::SelPointsSelect()
{
	vec2db p1, p2;
	int ix, iy, jx, jy, mnx, mxx;

	if (beg_id_x > end_id_x) { ix = end_id_x; jx = beg_id_x; }
	else { ix = beg_id_x; jx = end_id_x; }
	if (beg_id_y > end_id_y) { iy = end_id_y; jy = beg_id_y; }
	else { iy = beg_id_y; jy = end_id_y; }

	p1 = getLocPos(ix, iy);
	p2 = getLocPos(jx, jy);

	for (int ii = 0;ii < Z_idx.N;ii++)
	{
		SelectedIds.x[ii].fsetlen(Xdata.x[ii].N); //  индексы отображаемых точек при зуммировании
		SelectedIds.x[ii].N = 0;
		mnx = Xdata.x[ii].fmre(p1.x[0]);		  //находит первый элемента массива больше либо равен 'a'
		mxx = Xdata.x[ii].fmre(p2.x[0]);		 
		mnx = mnx == -1 ? 0 : mnx;
		mxx = mxx == -1 ? Xdata.x[ii].N - 1 : --mxx;	
		SelectedIds.x[ii].var1D(mnx, 1, mxx);
	}
}


void PlotGraph::ZoomPointsSelect()
{
	vec2db p1, p2;
	int ix, iy, jx, jy,mnx,mxx;

	if (beg_id_x > end_id_x) { ix = end_id_x; jx = beg_id_x; }
	else { ix = beg_id_x; jx = end_id_x; }
	if (beg_id_y > end_id_y) { iy = end_id_y; jy = beg_id_y; }
	else { iy = beg_id_y; jy = end_id_y; }

	p1 = getLocPos(ix, iy);
	p2 = getLocPos(jx, jy);

	adpX.mn = p1.x[0];
	adpX.mx = p2.x[0];
	adpY.mn = p2.x[1];
	adpY.mx = p1.x[1];
	
	for (int ii = 0;ii < Z_idx.N;ii++)
	{
		Z_idx.x[ii].fsetlen(Xdata.x[ii].N); //  индексы отображаемых точек при зуммировании
		mnx = Xdata.x[ii].fmre(p1.x[0]);			//находит первый элемента массива больше либо равен 'a'
		mxx = Xdata.x[ii].fmre(p2.x[0]);
		mnx = mnx == -1 ? 0 : mnx>0 ? --mnx :  0;
		mxx = mxx == -1 ?  Xdata.x[ii].N - 1 : mxx<(Xdata.x[ii].N - 1) ? ++mxx : Xdata.x[ii].N - 1;
		//if (mnx > 0) mnx--;
		//if (mxx < (Xdata.x[ii].N - 1)) mxx++;
		Z_idx.x[ii].var1D(mnx, 1, mxx);
	}
}

void PlotGraph::PanPointsSelect()
{
	int mnx, mxx;
	for (int ii = 0;ii < Z_idx.N;ii++)
	{
		Z_idx.x[ii].fsetlen(Xdata.x[ii].N); //  индексы отображаемых точек при зуммировании
		mnx = Xdata.x[ii].fmre(adpX.mn);			//находит первый элемента массива больше либо равен 'a'
		mxx = Xdata.x[ii].fmre(adpX.mx);
		mnx = mnx == -1 ? 0 : mnx>0 ? --mnx : 0;
		mxx = mxx == -1 ? Xdata.x[ii].N - 1 : mxx<(Xdata.x[ii].N - 1) ? ++mxx : Xdata.x[ii].N - 1;
		//mxx = mxx != -1 ? mxx : Xdata.x[ii].N - 1;
		Z_idx.x[ii].var1D(mnx, 1, mxx);
	}
}

void PlotGraph::ZoomReset()
{
	for (int ii = 0;ii < Z_idx.N;ii++)
	{
		Z_idx.x[ii].var1D(0, 1, Xdata.x[ii].N-1);
	}
}

void PlotGraph::FrameSetUp()//QPainter &painter)
{
	
	// вычисление координат осей
	frame[0] = dw_ + 1.5*dwY; // x - координата нижнего левого угла рамки графика на виджете, в пискелях
	frame[1] = rect().height() - 3 * dwY; // y - координата нижнего левого угла рамки графика на виджете, в пискелях
	frame[2] = rect().width() - dwX; // x - координата верхнего правого угла рамки графика на виджете, в пискелях
	frame[3] = dwY; //  y - координата верхнего правого угла рамки графика на виджете, в пискелях

	AxDivide(pixelLength(), dwX, adpX);
	AxDivide( pixelHigh(), dwY, adpY);

	mnmx[0] = adpX.mn;//mnx;//mnmx[0]>x[i] ? x[i] : mnmx[0];
	mnmx[1] = adpX.mx;//mxx;//mnmx[1]<x[i] ? x[i] : mnmx[1];
	mnmx[2] = adpY.mn;//mny;//mnmx[2]>y[i] ? y[i] : mnmx[2];
	mnmx[3] = adpY.mx;//mxy;//mnmx[3]<y[i] ? y[i] : mnmx[3];

	//kx = pixelLength() / dataLength();
	//ky = pixelHigh() / dataHigh();
	
	/*if (adpX.dq == 0)
	{
		adpX.dq = adpX.dTicks*ceil(adpX.mn / adpX.dTicks) - adpX.mn; // смещение до первой метки от края графика
		dxzr = adpX.dq*kx; // смещение в пикселях
	}*/

//	adpX.dq = adpX.dTicks*ceil(adpX.mn / adpX.dTicks) - adpX.mn; // смещение до первой метки от края графика
//	adpY.dq = adpY.dTicks*ceil(adpY.mn / adpY.dTicks) - adpY.mn; // смещение до первой метки от края графика

//	dxzr = adpX.dq*kx; // смещение в пикселях
}
/*
void PlotGraph::InBuffDraw(int axtp, QPainter &painter)
{
	//FrameSetUp();
	
	painter.drawLine(frame[0],frame[1], frame[2], frame[1]); // ось x
	painter.drawLine(frame[0], frame[1], frame[0], frame[2]); // ось y

	switch (ticstypex)
	{
	case 0: // обычные метки шкалы

		for (int i = 0;i <= adpX.nTicks;i++)
		{
			dc = (int)((double)(i)*(kx*adpX.dTicksa4));
			painter.drawLine(xi0 + dc, yi0 - 2, xi0 + dc, yi0 + 2);
			a3 = mnx + a4*i;
			//a3 = ismedianx ? dsx*(i-nx_2) : dsx*i;
			//if (fabs(a3)<1e-14) {a3 =0;}
			qstr.clear();
			qstr.setNum(a3, 'g', 3);
			painter.drawText(xi0 + dc - dw / 2, yi0, dw, dh, Qt::AlignCenter, qstr);
		}
		break;
	}


}
*/

void  PlotGraph::DrawAxisXY(QPainter &painter) // рисование оси X
{
	painter.setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(frame[0], frame[1], frame[2], frame[1]); // ось x
	int dc, i, di;// , iend;
	double dd;

	di = adpX.dpx + frame[0];
	dd = adpX.dTicks*adpX.k;
	for (i = 0;i < adpX.nTicks;i++)
	{
		dc = (int)((double)(i)*dd) + di;
		painter.drawLine( dc, frame[1] - tickLength, dc, frame[1] + tickLength);
	}

	painter.drawLine(frame[0], frame[1], frame[0], frame[3]); // ось y
	di = adpY.dpx + frame[1];
	dd = adpY.dTicks*adpY.k;
	for (i = 0;i < adpY.nTicks;i++)
	{
		dc = (int)((double)(i)*dd) + di;
		painter.drawLine(frame[0] - tickLength, dc, frame[0] + tickLength, dc);
	}

	painter.setPen(QPen(Qt::gray, 0.5, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

	di = adpX.dpx + frame[0];
	dd = adpX.dTicks*adpX.k;
	for (i = 0;i < adpX.nTicks;i++)
	{
		dc = (int)((double)(i)*dd) + di;
		painter.drawLine(dc, frame[1] - tickLength, dc, frame[3]);
	}

	di = adpY.dpx + frame[1];
	dd = adpY.dTicks*adpY.k;
	for (i = 0;i < adpY.nTicks;i++)
	{
		dc = (int)((double)(i)*dd) + di;
		painter.drawLine( frame[0] + tickLength, dc, frame[2],dc);
	}

	/*dd = kx*adpX.dTicks;
	di = dxzr % (int)(dd);
	i = di < 0 ? 1 : 0;
	iend = adpX.nTicks+i;
	dc = frame[0] + (int)iend*dd + di;
	if ( dc > frame[2]) iend--;
	for (;i <=iend;i++)
	{
		dc = (int)((double)(i)*dd) + di;//xzr;
		painter.drawLine(frame[0] + dc, frame[1] - tickLength, frame[0] + dc, frame[3]);
	}*/


	/*
	dd = ky*adpY.dTicks;
	for (i = 1;i <= adpY.nTicks;i++)
	{
		dc = (int)((double)(i)*dd) + dyzr;
		painter.drawLine(frame[0] + tickLength, frame[1] + dc, frame[2], frame[1] + dc);
	}*/
}

void  PlotGraph::DrawTicksX(QPainter &painter)
{
	int dc, i,di;
	double dd,a3,j;
	painter.setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	switch (ticstypex)
	{
	case 0: // обычные метки шкалы
		di = adpX.dpx + frame[0] - dwX ;
		dd = adpX.dTicks*adpX.k;
		for (i = 0;i < adpX.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = adpX.fst + adpX.dTicks*(i);
			hStr.clear();
			hStr.setNum(a3,'g',6);
			painter.drawText(dc, frame[1], 2*dwX, dwY, Qt::AlignCenter, hStr);
		}
		break;
	case 1: // шкала с вынесеным экспоненциальным множителем 10^px

		j = (adpX.fst) / pow(10., adpX.p);
		di = adpX.dpx + frame[0]-dwX;
		dd = adpX.dTicks*adpX.k;
		for (i = 0;i < adpX.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = j + adpX.dS*(i);
			hStr.clear();
			hStr.setNum(a3,'g',6);
			painter.drawText(dc, frame[1], 2*dwX, dwY, Qt::AlignCenter, hStr);
		}
		if (adpX.p != 0) { painter.drawText(frame[2] - dwX, frame[1] + dwY, dwX * 2, dwY, Qt::AlignCenter, QString("x10^").append(QString().setNum(int(adpX.p)))); }
		break;
	case 2: // шкала с вынесеным множителем и вынесеным началом оси

		di = adpX.dpx + frame[0] - dwX;
		dd = adpX.dTicks*adpX.k;
		for (i = 0;i < adpX.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = adpX.dS*(i);
			hStr.clear();
			hStr.setNum(a3,'g',6);
			painter.drawText(dc, frame[1], 2*dwX, dwY, Qt::AlignCenter, hStr);
		}
		if (adpX.p != 0) { painter.drawText(frame[2] - dwX, frame[1] + dwY, dwX * 2, dwY, Qt::AlignCenter, QString("x10^").append(QString().setNum(int(adpX.p)))); }
		if (adpX.fst != 0) { painter.drawText(frame[0] - dwX, frame[1] + dwY, dwX * 3, dwY, Qt::AlignCenter, QString().setNum(adpX.fst,'g',10).append("+")); }
		break;
	case 3: // шкала с вынесеным множителем и вынесеным центром шкалы
		int nx;
		nx = adpX.nTicks >> 1;
		di = adpX.dpx + frame[0] - dwX;
		dd = adpX.dTicks*adpX.k;
		for (i=0;i < adpX.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = adpX.dS*(i-nx);
			hStr.clear();
			hStr.setNum(a3, 'g', 6);
			painter.drawText(dc, frame[1], 2 * dwX, dwY, Qt::AlignCenter, hStr);
		}
		if (adpX.p != 0) { painter.drawText(frame[2] - dwX, frame[1] + dwY, dwX * 2, dwY, Qt::AlignCenter, QString("x10^").append(QString().setNum(int(adpX.p)))); }
		j = adpX.fst + adpX.dTicks *(nx);
		if (j != 0) { painter.drawText(frame[0] - dwX, frame[1] + dwY, dwX * 3, dwY, Qt::AlignCenter, QString().setNum(j, 'g', 10).append("+")); }
		break;
	}
}


void  PlotGraph::DrawTicksY(QPainter &painter)
{
	int dc, i, xi0, yi0,di;
	double dd, a3, j;
	dd = adpY.k*adpY.dTicks;
	xi0 = frame[0] - tickLength - 1 - dw_;
	yi0 = frame[1] - dwY/2 ;
	painter.setPen(QPen(Qt::black, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	switch (ticstypey)
	{
	case 0: // обычные метки шкалы

		for (i = 0;i <= adpY.nTicks;i++)
		{
			dc = (int)((double)(i)*dd);
			a3 = adpY.mn + adpY.dTicks*i;
			hStr.clear();
			hStr.setNum(a3, 'g', 3);
			painter.drawText(xi0, yi0 + dc, dw_, dwY, Qt::AlignRight, hStr);
		}
		break;
	case 1:

		j = (adpY.fst) / pow(10., adpY.p);
		di = adpY.dpx + frame[1];
		dd = adpY.dTicks*adpY.k;
		for (i = 0;i < adpY.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = j + adpY.dS*(i);
			hStr.clear();
			hStr.setNum(a3);
			painter.drawText(xi0, dc, dw_, dwY, Qt::AlignRight, hStr);
		}
		if (adpY.p != 0) { painter.drawText(1, frame[3] + dwY, dwX * 2, dwY, Qt::AlignLeft, QString("x10^").append(QString().setNum(int(adpY.p)))); }
		break;
	case 2:
		di = adpY.dpx + frame[1];
		dd = adpY.dTicks*adpY.k;
		for (i = 0;i < adpY.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = adpY.dS*(i);
			hStr.clear();
			hStr.setNum(a3,'g',6);
			painter.drawText(xi0, dc, dw_, dwY, Qt::AlignRight, hStr);
		}
		if (adpY.p != 0) { painter.drawText(1, frame[3] + dwY, dwX * 2, dwY, Qt::AlignLeft, QString("x10^").append(QString().setNum(int(adpY.p)))); }
		if (adpY.fst != 0)
		{
			painter.rotate(-90);
			painter.drawText(-(frame[1] + 2*dwX), dwY, dwX * 3, dwY, Qt::AlignCenter, QString().setNum(adpY.fst,'g',10).append("+"));
			painter.rotate(90);
		}

		break;
	case 3:
		int ny;
		ny = adpY.nTicks >> 1;
		di = adpY.dpx + frame[1];
		dd = adpY.dTicks*adpY.k;
		for (i = 0;i < adpY.nTicks;i++)
		{
			dc = (int)((double)(i)*dd) + di;
			a3 = adpY.dS*(i-ny);
			hStr.clear();
			hStr.setNum(a3, 'g', 6);
			painter.drawText(xi0, dc, dw_, dwY, Qt::AlignRight, hStr);
		}
		if (adpY.p != 0) { painter.drawText(1, frame[3] + dwY, dwX * 2, dwY, Qt::AlignLeft, QString("x10^").append(QString().setNum(int(adpY.p)))); }
		j = adpY.fst + adpY.dTicks *(ny);
		if (j != 0)
		{
			painter.rotate(-90);
			painter.drawText(-(frame[1] + 2 * dwX), dwY, dwX * 3, dwY, Qt::AlignCenter, QString().setNum(j, 'g', 10).append("+"));
			painter.rotate(90);
		}
		break;
	}
}


void PlotGraph::AxDivide(int rxy, int drx, AxsDvdPrm &adp) //  вычисление оптимального разбиения оси, rxy - длина отображаемой оси в пикселях, drx - ширина на одну метку в пикселях, dmnmx - длина оси в единицах графика
{
	double a1, a2, mna, mxx;
	int ii, jj, dc, im;
			
	// вычисление масштаба цены деления
	Nticks = 20; // максимальное число меток
	ii = abs(rxy) / drx; ii--;// максимальное количество меток
	Nticks = ii < Nticks ? ii : Nticks; // не должно превышать Nticks
	mna = 2.0;//0x7fffffff; // заведомо большое число, для поиска минимального отклонения от целого
	mxx = adp.mx-adp.mn; // длина отображаемой области вдоль оси в координанах графика
	//mnx = adp.mn;
	jj = 0;
	dc = 0;
	for (ii = 0;ii < 5;ii++) // перебор мантис - выбор наилучшей мантисы цены деления - наименьшее увеличение области графика за пределы данных
	{
		a1 = (mxx) / double(Nticks*wAx[ii]); // масштабный коэффициент текущей мантисы - примерная цена деления для текущей матнисы
		a1 = log10(a1); // показатель степени 10-ти для текущей цены деления
		a2 = floor(a1); // целая часть показателя степени 10 для текущей мантисы
		a1 -= a2; // дробная часть от a1 (показателя степени 10-ки)
		im = 0; // поправка на показатель степени
		if (a1 > 0.5) // используемая, если a1 ближе к целому числу a2+1, чем к a2
		{
			a1 = 1 - a1; // изменения дробной части
			im = 1; // показатель степени увеличиваем на единицу
		}
		if (a1 < mna) // если кратность текущей мантисы лучше чем предыдущей - т.е. дробная часть показателя степени меньше
		{
			mna = a1;// минимальное отклонение от целого
			jj = ii;	 // номер наилучшей мантисы
			dc = a2 + im; // показатель степени 10 наилучшей мантисы
		}
	}

	adp.dS = wAx[jj]; // запоминаем мантису
	adp.p = dc; // запоминаем показатель степени
	adp.dTicks = adp.dS*pow(10., adp.p); // вычисляем цену деления
	if ((adp.p == 1)||(adp.p==-1))
	{
		adp.dS = adp.dTicks;
		adp.p = 0;
	}

//	adp.mn = adp.dTicks*floor(adp.mn / adp.dTicks); // ближайший кратный минимум (приближение снизу) 
//	adp.mx = adp.dTicks*ceil(adp.mx / adp.dTicks); // ближайший кратный максимум (приближение сверху)

	adp.fst = adp.dTicks*ceil(adp.mn / adp.dTicks); // ближайший кратный минимум (приближение сверху) - задаёт значение первой метки
	adp.k = rxy / (adp.mx - adp.mn); // масштабный коэффициент
	adp.dpx = (adp.fst - adp.mn)*adp.k; // положение первой метки от начала оси (в пикселях)
	adp.nTicks = (int)((adp.mx - adp.fst) / adp.dTicks) + 1;// число отрезков 
}

void PlotGraph::DrawSelRect(QPainter &painter)
{
	int ix, iy, dx, dy;
	painter.setPen(QPen(Qt::black, 0.5, Qt::DashLine, Qt::SquareCap, Qt::MiterJoin));
	if (beg_id_x > end_id_x) { ix = end_id_x; dx = beg_id_x - end_id_x; }	else { ix = beg_id_x; dx = end_id_x - beg_id_x; }
	if (beg_id_y > end_id_y) { iy = end_id_y; dy = beg_id_y - end_id_y; }	else { iy = beg_id_y; dy = end_id_y - beg_id_y; }
	painter.drawRect(ix,iy,dx,dy);
}

void PlotGraph::DrawSelLines(QPainter &painter)
{
	//int ix, iy, dx, dy;
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	/*if (beg_id_x > end_id_x) { ix = end_id_x; dx = beg_id_x - end_id_x; }
	else { ix = beg_id_x; dx = end_id_x - beg_id_x; }
	if (beg_id_y > end_id_y) { iy = end_id_y; dy = beg_id_y - end_id_y; }
	else { iy = beg_id_y; dy = end_id_y - beg_id_y; }
	*/
	painter.drawLine(beg_id_x, frame[1], beg_id_x, frame[3]);//ix, iy, dx, dy);
	painter.drawLine(end_id_x, frame[1], end_id_x, frame[3]);
}

void PlotGraph::DrawDataCursorLines(QPainter &painter)
{
	int dx;//ix, iy, , dy
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	/*if (beg_id_x > end_id_x) { ix = end_id_x; dx = beg_id_x - end_id_x; }
	else { ix = beg_id_x; dx = end_id_x - beg_id_x; }
	if (beg_id_y > end_id_y) { iy = end_id_y; dy = beg_id_y - end_id_y; }
	else { iy = beg_id_y; dy = end_id_y - beg_id_y; }
	*/
	dx = abs(end_id_x - beg_id_x)/4.0;

	painter.drawLine(beg_id_x-dx, frame[1], beg_id_x-dx, frame[3]);//ix, iy, dx, dy);
	painter.drawLine(beg_id_x+dx, frame[1], beg_id_x+dx, frame[3]);

	vec2db lcrd;
	lcrd = getLocPos(beg_id_x-dx, 0);
	selX = lcrd.x[0];
	lcrd = getLocPos(beg_id_x + dx, 0);
	selDX = (lcrd.x[0] - selX) / 2.0;
	selX += lcrd.x[0];
	selX /= 2.0;

	selXReady();
}

void PlotGraph::DrawLabel(QPainter &painter) // рисование подписей к осям
{
	// рисование подписей осей
	int dw;
	dw = this->fontMetrics().width(xname);
	painter.drawText((frame[0] + frame[2]) / 2 - dw / 2, frame[1] + 1.5*dwY, this->fontMetrics().width(xname), dwY, Qt::AlignCenter, xname);
	dw = this->fontMetrics().width(yname) / 2;
	painter.rotate(-90.);
	//dwy = (this->fontMetrics().width(yname))/2; yi1+dh
	painter.drawText(-((frame[1]+ frame[3]) / 2 + dw), frame[0] - dw_ - dwY, this->fontMetrics().width(yname), dwY, Qt::AlignCenter, yname);
	painter.rotate(90.);
}
/*
void PlotGraph::DrawAxes(QPainter &painter)
{
	QRect rect;
	rect = painter.viewport();
	if(rect.width()<2) rect = this->rect();
	//painter.drawText(rect.width()/2,rect.height()/2,QString("xlabel"));

	double wax[] = {1,2,3,4,5};  // допустимые значения мантисы цены деления

	double a1,a2,a3,a4,mna,dsx,dsy,mnx,mny,mxx,mxy;
	int Nl;
	int i,j,dc,im,dh,dw,dwy;
	int px,py,nx,ny,nx_2,ny_2;
	//char hstr[20];
	QString qstr;
	int xi0,yi0,xi1,yi1;

	if (mnmx[1]==mnmx[0]) {mnmx[1]++;mnmx[0]--;}
	if (mnmx[3]==mnmx[2]) {mnmx[3]++;mnmx[2]--;}
	
	// вычисление масштаба цены деления
	Nl	= 20; // максимальное число меток
	dwy	= this->fontMetrics().width("-0.000000");// textwidth("0.000")+3; // ширина 5 символов
	dw = this->fontMetrics().width("-0.000");
	i	= (rect.width()-dw)/dw; // максимальное количество меток
	Nl	= i<Nl ? i : Nl; // не должно превышать Nl
	mna	= 100; // заведомо большое число, для поиска минимального отклонения от целого
	j	= 0;
	dc  = 0;
	for(i=0;i<5;i++) // перебор мантис
	{
		a1	= (mnmx[1]-mnmx[0])/double(Nl*wax[i]); // масштабный коэффициент текущей мантисы
		a2	= log10(a1); // 
		a3	= floor(a2); // 
		a4	= a2-a3;
		im	= 0; // поправка на показатель степени
		if(a4>0.5) // используемая, если a2 ближе к целому числу a3+1, чем к a3
		{
			a4	= 1-a4; 
			im	= 1;
		}
		if(a4<mna) // если кратность текущей мантисы лучше чем предыдущей
		{
			mna	= a4;// минимальное отклонение от целого
			j	= i;	// номер наилучшей мантисы
			dc	= a3+im; // показатель степени 10 наилучшей мантисы
		}
	}
	dsx	= wax[j]; // выбранная мантиса цены деления
	px	= dc; // показатель степени выбранной мантисы
	a1	= (dsx*pow(10.,px)); // цена деления
	mnx	= a1*floor(mnmx[0]/a1); // ближайший кратный минимум
	mxx	= a1*ceil(mnmx[1]/a1); // ближайший кратный максимум

	nx	= (int)((mxx-mnx)/a1);// число отрезков
	nx_2 = nx>>1;


	Nl	= 20; //максимальное число меток
//	dh	= textheight("0.000")+3;
	dh	= this->fontMetrics().height()+3;// textwidth("0.000")+3; // ширина 5 символов
	i		= (rect.height()-dh)/dh; // (frame[3]-dh)/dh; // максимальное количество меток
	Nl	= i<Nl ? i : Nl; // не должно превышать Nl 
	mna	= 100;  // заведомо большое число, для поиска минимального отклонения от целого
	j	= 0;
	dc  = 0;
	for(i=0;i<5;i++) // перебор мантис
	{
		a1	= (mnmx[3]-mnmx[2])/double(Nl*wax[i]); // масштабный коэффициент текущей мантисы
		a2	= log10(a1);
		a3	= floor(a2);
		a4	= a2-a3;
		im	= 0; // поправка на показатель степени
		if(a4>0.5) // используемая, если a2 ближе к целому числу a3+1, чем к a3
		{
			a4	= 1-a4;
			im	= 1;
		}
		if(a4<mna) // если кратность текущей мантисы лучше чем предыдущей
		{ 
			mna	= a4;// минимальное отклонение от целого
			j	= i;	// номер наилучшей мантисы
			dc	= a3+im; // показатель степени 10 наилучшей мантисы
		}
	}
	dsy	= wax[j];  // выбранная мантиса цены деления
	py	= dc;  // показатель степени выбранной мантисы
	a1	= (dsy*pow(10.,py)); // цена деления
	mny	= a1*floor(mnmx[2]/a1); // ближайший кратный минимум
	mxy	= a1*ceil(mnmx[3]/a1); // ближайший кратный максимум

	ny	= (int)((mxy-mny)/a1);// число отрезков
	ny_2= ny>>1;

	// вычисление координат осей
	xi0	= dwy+1.5*dh;
	yi0	= rect.height()-3*dh;
	xi1	= rect.width()-dw;
	yi1	= dh;

	frame[0] = xi0;
	frame[1] = yi0;
	frame[2] = xi1;
	frame[3] = yi1;

	mnmx[0] = mnx;//mnmx[0]>x[i] ? x[i] : mnmx[0];
	mnmx[1] = mxx;//mnmx[1]<x[i] ? x[i] : mnmx[1];
	mnmx[2] = mny;//mnmx[2]>y[i] ? y[i] : mnmx[2];
	mnmx[3] = mxy;//mnmx[3]<y[i] ? y[i] : mnmx[3];

	painter.drawLine(xi0,yi0,xi1,yi0); // ось x
	painter.drawLine(xi0,yi0,xi0,yi1); // ось y


	// установление меток и шкалы
	xi1	-= xi0; //rect.width()-2*dw;
	yi1	-= yi0;//rect.width()-2*dh;
	yi1 = -yi1;
	a1	= mxx-mnx;
	a2	= mxy-mny;
	kx	= xi1/a1;
	ky	= yi1/a2;

	a4	= dsx*pow(10.,px);
	
	switch (ticstypex)
	{
	case 0: // обычные метки шкалы

		for(i=0;i<=nx;i++)
		{
			dc	= (int)((double)(i)*(kx*a4));
			painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0+2);
			a3	= mnx+a4*i;
			//a3 = ismedianx ? dsx*(i-nx_2) : dsx*i;
			//if (fabs(a3)<1e-14) {a3 =0;}
			qstr.clear();
			qstr.setNum(a3,'g',3);
			painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,qstr);
		}
		break;

	case 1: // шкала вынесеным экспоненциальным множителем 10^px
		j	= mnx/pow(10.,px);
		for(i=0;i<=nx;i++)
		{
			dc	= (int)((double)(i)*(kx*a4));
			painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0+2);
			//a3	= (mnx+a4*i);
			a3 =  j+dsx*i;
			//if (fabs(a3)<1e-14) {a3 =0;}
			qstr.clear();
			qstr.setNum(a3);
			painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,qstr);
		}
		if (px!=0) {painter.drawText(xi0+dc-dw,yi0+dh,dw*2,dh,Qt::AlignCenter,QString("x10^").append(QString().setNum(int(px))));}	
		break;

	case 2: // шкала с вынесеным множителем и вынесеным началом оси

		for(i=0;i<=nx;i++)
		{
			dc	= (int)((double)(i)*(kx*a4));
			painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0+2);
			a3 =  dsx*i;
			qstr.clear();
			qstr.setNum(a3,'g',3);
			painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,qstr);
		}
		if (mnx!=0) {painter.drawText(xi0-dw,yi0+dh,dw*2,dh,Qt::AlignCenter, QString().setNum(mnx).append("+"));}
		if (px!=0) {painter.drawText(xi0+dc-dw,yi0+dh,dw*2,dh,Qt::AlignCenter,QString("x10^").append(QString().setNum(int(px))));}
		break;

	case 3: // шкала с вынесеным множителем и вынесеным центром шкалы

		for(i=0;i<=nx;i++)
		{
			dc	= (int)((double)(i)*(kx*a4));
			painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0+2);
			a3 =  dsx*(i-nx_2);
			qstr.clear();
			qstr.setNum(a3,'g',3);
			painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,qstr);
		}
		mnx+=a4*nx_2;
		if (mnx!=0) {painter.drawText(xi0-dw,yi0+dh,dw*2,dh,Qt::AlignCenter, QString().setNum(mnx).append("+")); }
		mnx-=a4*nx_2;
		if (px!=0) {painter.drawText(xi0+dc-dw,yi0+dh,dw*2,dh,Qt::AlignCenter,QString("x10^").append(QString().setNum(int(px))));}
		break;
	}
	/*if (abs(px)<3) {dsx *= pow(10.,px);px=0;}
	for(i=0;i<=nx;i++)
	{
		dc	= (int)((double)(i)*(kx*a4));
		painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0+2);
		a3	= mnx+a4*i;
		//a3 = ismedianx ? dsx*(i-nx_2) : dsx*i;
		//if (fabs(a3)<1e-14) {a3 =0;}
		qstr.clear();
		qstr.setNum(a3);
		painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,qstr);
		//_gcvt(a3,4,hstr);
		//painter.drawText(xi0+dc-dw/2,yi0,dw,dh,Qt::AlignCenter,QString(hstr));
	}
//	if (ismedianx) mnx+=a4*nx_2;
	if(mnx!=0) {painter.drawText(xi0-dw,yi0+dh,dw*2,dh,Qt::AlignCenter, QString().setNum(mnx).append(" + "));}
//	if (ismedianx) mnx-=a4*nx_2;
	if (px!=0) {painter.drawText(xi0+dc-dw,yi0+dh,dw*2,dh,Qt::AlignCenter,QString("x10^").append(QString().setNum(int(px))));}
* /

	a4	= dsy*pow(10.,py);
	switch (ticstypey)
	{
	case 0:
		for(i=0;i<=ny;i++)
		{
			dc	= (int)((double)(i)*(ky*a4));
			painter.drawLine(xi0-2,yi0-dc,xi0+2,yi0-dc);
			a3	= mny+a4*i;
			qstr.clear();
			qstr.setNum(a3,'g',15);
			painter.drawText(xi0-3-dwy,yi0-dc-dh/2,dwy,dh,Qt::AlignRight,qstr);
		}
		break;
	case 1:
		j	= mnx/pow(10.,px);
		for(i=0;i<=ny;i++)
		{
			dc	= (int)((double)(i)*(ky*a4));
			painter.drawLine(xi0-2,yi0-dc,xi0+2,yi0-dc);
			a3	= j+dsy*i;
			qstr.clear();
			qstr.setNum(a3);
			painter.drawText(xi0-3-dwy,yi0-dc-dh/2,dwy,dh,Qt::AlignRight,qstr);
		}
		if (py!=0) {painter.drawText(5,yi0-dc-dh/2,dw*2,dh,Qt::AlignLeft,QString("x10^").append(QString().setNum(int(py))));}
		break;
	case 2:
		for(i=0;i<=ny;i++)
		{
			dc	= (int)((double)(i)*(ky*a4));
			painter.drawLine(xi0-2,yi0-dc,xi0+2,yi0-dc);
			a3	= dsy*i;
			qstr.clear();
			qstr.setNum(a3);
			painter.drawText(xi0-3-dwy,yi0-dc-dh/2,dwy,dh,Qt::AlignRight,qstr);
		}
		if (py!=0) {painter.drawText(5,yi0-dc-dh/2,dw*2,dh,Qt::AlignLeft,QString("x10^").append(QString().setNum(int(py))));}
		if(mny!=0) 
		{
			painter.rotate(-90);
			painter.drawText(-(yi0+dh),dw,dw*3,dh,Qt::AlignCenter, QString().setNum(mny).append("+"));
			painter.rotate(90);
		}
		break;
	case 3:
		for(i=0;i<=ny;i++)
		{
			dc	= (int)((double)(i)*(ky*a4));
			painter.drawLine(xi0-2,yi0-dc,xi0+2,yi0-dc);
			a3	= dsy*(i-ny_2);
			qstr.clear();
			qstr.setNum(a3);
			painter.drawText(xi0-3-dwy,yi0-dc-dh/2,dwy,dh,Qt::AlignRight,qstr);
		}
		if (py!=0) {painter.drawText(5,yi0-dc-dh/2,dw*2,dh,Qt::AlignLeft,QString("x10^").append(QString().setNum(int(py))));}
		mny+=a4*ny_2;
		if(mny!=0) 
		{
			painter.rotate(-90);
			painter.drawText(-(yi0+dh),dw,dw*3,dh,Qt::AlignCenter, QString().setNum(mny).append("+"));
			painter.rotate(90);
		}
		mny-=a4*ny_2;
		break;
	}

	/*if (abs(py)<3) {dsy *= pow(10.,py);py=0;}
	for(i=0;i<=ny;i++)
	{
		dc	= (int)((double)(i)*(ky*a4));
		painter.drawLine(xi0-2,yi0-dc,xi0+2,yi0-dc);
		a3	= mny+a4*i;
		//a3 = ismediany ? dsy*(i-ny_2) : dsy*i;
		//if (fabs(a3)<1e-14) {a3 =0;}
		qstr.clear();
		//qstr.setNum(a3,'g',3);
		qstr.setNum(a3);
		painter.drawText(xi0-3-dwy,yi0-dc-dh/2,dwy,dh,Qt::AlignRight,qstr);
		//_gcvt(a3,4,hstr);
		//painter.drawText(xi0-3-dw,yi0-dc-dh/2,dw,dh,Qt::AlignRight,QString(hstr));
		//outtextxy(xi0-3,yi0-dc,hstr);
	}* /

//	if (ismediany) mny+=a4*ny_2;
	if(mny!=0) 
	{
		painter.rotate(-90);
		painter.drawText(yi0-dh/2,-dw*2,dh,5,Qt::AlignLeft, QString().setNum(mny).append(" + "));
		painter.rotate(90);
	}
//	if (ismediany) mny-=a4*ny_2;
//	if (py!=0) {painter.drawText(5,yi0-dc-dh/2,dw*2,dh,Qt::AlignLeft,QString("x10^").append(QString().setNum(int(py))));}

	// рисование подписей осей
	dw = this->fontMetrics().width(xname);
	painter.drawText(xi0+xi1/2-dw/2,yi0+1.5*dh,this->fontMetrics().width(xname),dh,Qt::AlignCenter,xname);
	dc = this->fontMetrics().width(yname)/2;
	painter.rotate(-90.);
	//dwy = (this->fontMetrics().width(yname))/2; yi1+dh
	painter.drawText(-(yi0-yi1/2+dc),xi0-dwy-dh,this->fontMetrics().width(yname),dh,Qt::AlignCenter,yname);
	painter.rotate(90.);

  // рисование сетки

	painter.setPen(QPen(Qt::gray, 0.5, Qt::DashLine,Qt::RoundCap,Qt::RoundJoin));
	a4	= dsx*pow(10.,px);
	for(i=1;i<=nx;i++)
	{
		dc	= (int)((double)(i)*(kx*a4));
		painter.drawLine(xi0+dc,yi0-2,xi0+dc,yi0-yi1);
	}

	a4	= dsy*pow(10.,py);
	for(i=1;i<=ny;i++)
	{
		dc	= (int)((double)(i)*(ky*a4));
		painter.drawLine(xi0+2,yi0-dc,xi0+xi1,yi0-dc);
	}


  
}*/


void PlotGraph::DrawOnAx(QPainter &painter)
//void PlotGraph::DrawOnAx(QPainter &painter,QVector<double> &x,QVector<double> &y)
{
	double mnx,mny,hx,hy;//,mxy,mxx;
	int i,rr,iz;
	int xi0,yi0,xc,yc,xc1,yc1;
	
	mnx = adpX.mn;//mnmx[0];
	mny = adpY.mn;//mnmx[2];

	xi0	= frame[0];
	yi0	= frame[1];
	xc1 = frame[2];
	yc1 = frame[3];

	xc1 -= xi0;
	yc1 -= yi0;
//	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setClipRect(xi0,yi0,xc1,yc1,Qt::ReplaceClip);

	//xc	= xi0+kx*(x[0]-mnx);
	//yc	= yi0+ky*(y[0]-mny);
	for(int jj=0;jj< Z_idx.N;jj++)
	{
		if (jj<10) painter.setPen(QPen(clrs.x[jj], 1, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
		else painter.setPen(QPen(Qt::darkRed, 2, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

		iz = Z_idx.x[jj].x[0];
		xc	= xi0+adpX.k*(Xdata.x[jj].x[iz]-mnx);
		yc	= yi0+adpY.k*(Ydata.x[jj].x[iz]-mny);
		painter.drawPoint(xc,yc);
		for(i=1;i<Z_idx.x[jj].N;i++)
		{
			iz = Z_idx.x[jj].x[i];
			hx = Xdata.x[jj].x[iz];
			hy = Ydata.x[jj].x[iz];
			xc1	= xi0+adpX.k*(Xdata.x[jj].x[iz]-mnx);
			yc1	= yi0+adpY.k*(Ydata.x[jj].x[iz]-mny);
			rr = (xc1-xc)*(xc1-xc)+(yc1-yc)*(yc1-yc);
			if(rr>1)
			{
				painter.drawLine(xc,yc,xc1,yc1);
			//	painter.drawPoint(xc1,yc1);
				painter.drawEllipse(xc1-1, yc1-1, 2, 2);
				xc = xc1;
				yc = yc1;
			}
			//painter.drawPoint(xc,yc);
			//painter.drawLine(xi0+kx*(x[i]-mnx),yi0-ky*(y[i]-mny),xi0+kx*(x[i-1]-mnx),yi0-ky*(y[i-1]-mny));
		}
	}
}

void PlotGraph::DrawFunOnAx(QPainter & painter)
{
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	for (int ii = 1; ii < lix.N; ii++)
	{
		//painter.drawPoint(lix.x[ii], liy.x[ii]);
		painter.drawLine(lix.x[ii-1], liy.x[ii-1], lix.x[ii], liy.x[ii]);
	}
}

void PlotGraph::setFundata()
{
	int  Npnt;
	double dx;
	vecdb locx, locy;
	Npnt = adpX.k*(fun_x2 - fun_x1);
	dx = (fun_x2 - fun_x1) / Npnt;
	locx.var1D(fun_x1, dx, fun_x2);
	//locy.fsetlen(locx.N);
	//(Fun)(locx, locy);
	p_gsaprx->Fun(locx, locy);
	lix.fsetlen(locx.N);
	liy.fsetlen(locx.N);
	for (int ii = 0; ii < locx.N; ii++)
	{
		lix.x[ii] = frame[0] + adpX.k*(locx.x[ii] - adpX.mn);
		liy.x[ii] = frame[1] + adpY.k*(locy.x[ii] - adpY.mn);
	}
}

void PlotGraph::setFundata2()
{
	int  Npnt;
	double dx;
	vecdb locx, locy;
	Npnt = adpX.k*(fun_x2 - fun_x1);
	dx = (fun_x2 - fun_x1) / Npnt;
	locx.var1D(fun_x1, dx, fun_x2);
	//locy.fsetlen(locx.N);
	//(Fun)(locx, locy);
	p_loraprx->Fun(locx, locy);
	lix.fsetlen(locx.N);
	liy.fsetlen(locx.N);
	for (int ii = 0; ii < locx.N; ii++)
	{
		lix.x[ii] = frame[0] + adpX.k*(locx.x[ii] - adpX.mn);
		liy.x[ii] = frame[1] + adpY.k*(locy.x[ii] - adpY.mn);
	}
}

vec2db PlotGraph::getLocPos(int xpos, int ypos) // определение координат точки на графике по её координатам на рисунке
{
	vec2db dbpos;

	dbpos.x[0] = adpX.k!=0 ? adpX.mn + double(xpos - frame[0]) / adpX.k : 0;
	dbpos.x[1] = adpY.k!=0 ? adpY.mn + double(ypos - frame[1]) / adpY.k : 0;

	return dbpos;
}

void PlotGraph::keyPressEvent(QKeyEvent *event)
{

	QPainter painter(this);
	painter.eraseRect(this->rect());
	event->accept();
}

void PlotGraph::contextMenuEvent(QContextMenuEvent *e)
{
	//vec2db dbpos;
	//QPoint Pos;
	//QString str;
	
	//Pos = e->pos();

	/*dbpos = getLocPos(Pos.rx(), Pos.ry());

	str.number(dbpos.x[0]);
	xps_dsl->setText(str);
	str.number(dbpos.x[1]);
	yps_dsl->setText(str);*/

	isFrameDraw = false;

	dftCnxMn->exec(QCursor::pos());//(e->pos());
	//dftCnxMn->activateWindow();
	//dftCnxMn->raise();
	
	//e->accept();
}

void PlotGraph::setSelActText(const QString &text)
{
	SelectAction->setText(text);
}



void PlotGraph::graphics2clipboard()
{
	QClipboard *clpbrd = QApplication::clipboard();

	QString qstr;
	for (int ii = 0; ii<Xdata.x[0].N; ii++)
	{
		for (int jj = 0; jj < Xdata.N; jj++)
		{
			qstr.append(QString().setNum(Xdata.x[jj].x[ii], 'g', 16));
			qstr.append(' ');
			qstr.append(QString().setNum(Ydata.x[jj].x[ii], 'g', 16));
			qstr.append(' ');
			
		}
		qstr.append('\n');
	}
	clpbrd->setText(qstr);
}



#endif
