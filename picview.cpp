#ifndef PICVIEW_CPP
#define PICVIEW_CPP

#include <QRect>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include "picview.h"
//#include "linalg.cpp"
#include "linalg.h"


PicView::PicView(QWidget *parent) : QWidget(parent)
{
	//picdata		= 0x0;
	//picdatalen	= 0;

	//pixmap.QPixmap();

	x1 = 0.1;
	y1 = 0.1;
	x2 = 0.9;
	y2 = 0.1;
	szx = 600;
	szy = 400;
	lShft = 0;
	this->setFixedSize(szx+lShft,szy);

	pxmp = QImage(szx,szy,QImage::Format_RGB32);
	pxmp.fill(0);

	movtype = 0;
	setUpdatesEnabled(true);
	setFocusPolicy(Qt::ClickFocus);
	dd = 0.25;
	type = 0;
	idnull = 2048;

	pixScale = 2; 



	bright = 50;
	contrast = 80;
	gamma = 50;

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


	cnbr_label = new QLabel(QString("\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260\040\321\217\321\200\320\272\320\276\321\201\321\202\320\270\040\320\270\040\320\272\320\276\320\275\321\202\321\200\320\260\321\201\321\202\320\260\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217"));//Setup brightness and contrast
	cn_lbl = new QLabel(QString("\320\232\320\276\320\275\321\202\321\200\320\260\321\201\321\202"));//Contast
	br_lbl = new QLabel(QString("\320\257\321\200\320\272\320\276\321\201\321\202\321\214"));//Brightness
	gm_lbl = new QLabel(QString("\320\223\320\260\320\274\320\274\320\260\055\320\272\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217"));//Gamma


	vbox1 = new QVBoxLayout(pic_setup_box);
	hbox2 = new QHBoxLayout(pic_setup_box);
	hbox1 = new QHBoxLayout(pic_setup_box);
	hbox3 = new QHBoxLayout(pic_setup_box);

	hbox1->addWidget(bright_sldr);
	hbox1->addWidget(br_lbl);
	hbox2->addWidget(contrast_sldr);
	hbox2->addWidget(cn_lbl);
	hbox3->addWidget(gamma_sldr);
	hbox3->addWidget(gm_lbl);

	vbox1->addWidget(cnbr_label);
	vbox1->addLayout(hbox1);
	vbox1->addLayout(hbox2);
	vbox1->addLayout(hbox3);


	//pic_setup_box->setText(QString("Setup brigth and contrast"));

	pic_setup_box->setLayout(vbox1);

	pic_setup_box->setModal(false);

	cntxMenu = new QMenu(this); // конеткстное меню
	actionPictureSetup = new QAction(cntxMenu);
	actionPictureSetup->setText(QString("\320\257\321\200\320\272\320\276\321\201\321\202\321\214\057\320\232\320\276\320\275\321\202\321\200\320\260\321\201\321\202"));//Contrast/Brigth

	cntxMenu->addAction(actionPictureSetup);

	connect(actionPictureSetup, SIGNAL(triggered()), pic_setup_box, SLOT(exec()));

	connect(bright_sldr, SIGNAL(valueChanged(int)), this, SLOT(br_ch(int)));
	connect(contrast_sldr, SIGNAL(valueChanged(int)), this, SLOT(cn_ch(int)));
	connect(gamma_sldr, SIGNAL(valueChanged(int)), this, SLOT(gm_ch(int)));
}
/*
void PicView::setpicdata(FullMatrix<unsigned short> &M)
{
	QRect rct = this->rect();//this->visibleRegion().boundingRect();
	int Dx,Dy,S; // размеры видимой области
	//int Npx; // количество элементов исходного изображения умещающихся в одном пикселе экранной картинки

	unsigned char * picdata; // данные для рисования картинки
	unsigned int picdatalen; // длина буфера picdata

	unsigned short *xm;

	// размеры видимой области
	Dx = rct.width();  // szx
	Dy = rct.height(); // szy
	//picdatalen = 

	
	unsigned int * xl;

	picdatalen = Dx*Dy; // предполагается глубина цвета - 32 бита.
	S	= Dx*Dy;
	
	double z,v;
	unsigned int xx,nx;
	unsigned char w;
	xx = 0;
	for(unsigned int ii = 0;ii<picdatalen;ii++){ xx = xx<M.s.x[ii] ? M.s.x[ii] : xx;}
	//xx = 262144;
	nx = 0xffffffff;
	for(unsigned int ii = 0;ii<picdatalen;ii++){ nx = nx>M.s.x[ii] ? M.s.x[ii] : nx;}
	v	= log(double(xx)/double(nx));
	//LocM.showfull_infile("LocM.txt");
	picdata = new  unsigned char [4*picdatalen];

	for(unsigned int ii = 0;ii<picdatalen;ii++)
	{
		z	= M.s.x[ii];
		z	/= xx;
		//z	= log(z);
		//z	/= v;
		z	*= 255.0;
		w	= unsigned char(z);
		picdata[4*ii]	= w;
		picdata[4*ii+1]	= w;
		picdata[4*ii+2]	= w;
		picdata[4*ii+3]	= 0xff;
	}
	//picdatalen *= 4;
	//pixmap->loadFromData(picdata,picdatalen,"BMP",Qt::MonoOnly);
	pxmp	= QImage(picdata,szx,szy,QImage::Format_RGB32);

	update();

	picdata = 0x0;
}
*/

void PicView::setpicdata(FullMatrix<unsigned short> &M)
{
	QRect rct = this->rect();//this->visibleRegion().boundingRect();
	int Dx, Dy, S; // размеры видимой области
	int Npx; // количество элементов исходного изображения умещающихся в одном пикселе экранной картинки

	unsigned char * picdata; // данные для рисования картинки
	unsigned int picdatalen; // длина буфера picdata

	//unsigned short *xm;

	// размеры видимой области
	Dx = rct.width();  // szx
	Dy = rct.height(); // szy
					   //picdatalen = 


	//unsigned int * xl;

	picdatalen = Dx*Dy; // предполагается глубина цвета - 32 бита.
	S = Dx*Dy;
	//picdata = new [picdatalen] unsigned char; 

	Npx = pixScale;


	double z, v, dz, ww;
	unsigned int xx, nx;
	unsigned char w;
	xx = 0;
	for (unsigned int ii = 0; ii<picdatalen; ii++) { xx = xx<M.s.x[ii] ? M.s.x[ii] : xx; }
	//xx = 262144;
	nx = 0xffffffff;
	for (unsigned int ii = 0; ii<picdatalen; ii++) { nx = nx>M.s.x[ii] ? M.s.x[ii] : nx; }
	//v	= log(double(xx)/double(nx));

	v = 4.0*contrast / 300.0 + 1 / 3.0;
	dz = 2.0*bright / 300.0 - 1 / 3.0;
	ww = 2.0*gamma / 100.0;
	//LocM.showfull_infile("LocM.txt");
	picdata = new  unsigned char[4 * picdatalen];
	for (unsigned int ii = 0; ii<picdatalen; ii++)
	{
		z = (int)(M.s.x[ii]) - nx;
		z = z>1 ? z : 1;
		z /= (double)xx;
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w = unsigned char(z);
		picdata[4 * ii] = w;
		picdata[4 * ii + 1] = w;
		picdata[4 * ii + 2] = w;
		picdata[4 * ii + 3] = 0xff;
	}
	//picdatalen *= 4;
	//pixmap->loadFromData(picdata,picdatalen,"BMP",Qt::MonoOnly);

	pxmp = QImage(picdata, szx, szy, QImage::Format_RGB32);;

	update();

	picdata = 0x0;

	//delete [] picdata;

}

void PicView::setpicdata(FullMatrix<double> &AC)
{

	FullMatrix<unsigned short> R1;
	double z, v, dz, ww;
	R1.setSize(szy, szx);
	double Gx, Gn;// , kk;
	Gx = AC.s.max();
	Gn = AC.s.min();

	//kk = 255/(Gx-Gn); // коэффиц. масштабирования на 8 бит

	v = 4.0*contrast / 300.0 + 1 / 3.0;
	dz = 2.0*bright / 300.0 - 1 / 3.0;
	ww = 2.0*gamma / 100.0;

	double ax, ay;

	ax = szx / AC.nx;
	ay = szy / AC.ny;

	if (ax>ay)
	{ // картинку увеличивать только в ay раз
	}
	else
	{// картинку увеличивать в ax раз
		ay = ax;
	}
	int nn, mm;
	//zy = ay*AC.ny;
	//zx = ax*AC.nx;
	for (int ii = 0; ii<szy; ii++)
	{
		nn = ii / ay;
		for (int jj = 0; jj<szx; jj++)
		{
			mm = jj / ax;
			z = AC.fst(nn, mm) - Gn;
			z = z>1 ? z : 1;
			z /= Gx;
			z = v*z + dz;
			z = z>1 ? 1 : z;
			z = z<0 ? 0 : z;
			z *= 255.0;

			R1.fst(ii, jj) = z;
		}
	}

	unsigned char * picdata; // данные для рисования картинки
	unsigned int picdatalen; // длина буфера picdata
	unsigned char w;

	picdatalen = szx*szy; // предполагается глубина цвета - 32 бита.

	picdata = new  unsigned char[4 * picdatalen];
	for (unsigned int ii = 0; ii<picdatalen; ii++)
	{
		w = unsigned char(R1.s.x[ii]);
		picdata[4 * ii] = w;
		picdata[4 * ii + 1] = w;
		picdata[4 * ii + 2] = w;
		picdata[4 * ii + 3] = 0xff;
	}
	pxmp = QImage(picdata, szx, szy, QImage::Format_RGB32);
	update();
	picdata = 0x0;
}

void PicView::setpicdata(const FullMatrix<unsigned short> &MR,const FullMatrix<unsigned short> &MG,const FullMatrix<unsigned short> &MB, int nupdt)
{
	QRect rct;// = this->rect();//this->visibleRegion().boundingRect();
	int Dx,Dy,S; // размеры видимой области
	int Npx; // количество элементов исходного изображения умещающихся в одном пикселе экранной картинки

	unsigned char * picdata; // данные для рисования картинки
	unsigned int picdatalen; // длина буфера picdata

	unsigned int X;
	unsigned short *xm;

	// размеры видимой области
	Npx = pixScale;
	setsz(MR.nx/Npx,MR.ny/Npx);
	//this->setFixedSize(szx,szy); // ??? эта команда уже есть в setsz
	rct = this->rect();
	Dx = rct.width();  // szx
	Dy = rct.height(); // szy
	//picdatalen = 

	FullMatrix<unsigned int> LocMR(Dy,Dx);
	FullMatrix<unsigned int> LocMG(Dy,Dx);
	FullMatrix<unsigned int> LocMB(Dy,Dx);

	unsigned int * xl;

	picdatalen = 4*Dx*Dy; // предполагается глубина цвета - 32 бита.
	S	= Dx*Dy;
	//picdata = new [picdatalen] unsigned char; 

	//Npx = 4;
	memset(LocMR.s.x,0,LocMR.s.N*sizeof(unsigned int));
	memset(LocMG.s.x,0,LocMR.s.N*sizeof(unsigned int));
	memset(LocMB.s.x,0,LocMR.s.N*sizeof(unsigned int));

	for(int ii = 0;ii<LocMR.ny;ii++)
	{
		xl = LocMR.x.x[ii];
		for(int ij=0;ij<Npx;ij++)
		{
			xm = MR.x.x[ii*Npx+ij];
			for(int jj = 0; jj<LocMR.nx;jj++)
			{
				X = 0;
				for(int ji=0;ji<Npx;ji++) X+=xm[ij];
				xl[jj] += X;
				xm	+= Npx;
			}
		}
	}

	for(int ii = 0;ii<LocMG.ny;ii++)
	{
		xl = LocMG.x.x[ii];
		for(int ij=0;ij<Npx;ij++)
		{
			xm = MG.x.x[ii*Npx+ij];
			for(int jj = 0; jj<LocMG.nx;jj++)
			{
				X = 0;
				for(int ji=0;ji<Npx;ji++) X+=xm[ij];
				xl[jj] += X;
				xm	+= Npx;
			}
		}
	}

	for(int ii = 0;ii<LocMB.ny;ii++)
	{
		xl = LocMB.x.x[ii];
		for(int ij=0;ij<Npx;ij++)
		{
			xm = MB.x.x[ii*Npx+ij];
			for(int jj = 0; jj<LocMB.nx;jj++)
			{
				X = 0;
				for(int ji=0;ji<Npx;ji++) X+=xm[ij];
				xl[jj] += X;
				xm	+= Npx;
			}
		}
	}

	picdatalen = LocMR.nx*LocMR.ny;
	

	double z,v,ww,dz;
	unsigned int xx,xg,xb,nx,ng,nb,istart;
	unsigned char w;
	xg = xb = xx = 0;
	istart = LocMR.ny > 1 ?  LocMR.nx : 0;
	for(unsigned int ii = istart;ii<picdatalen;ii++){ xx = xx<LocMR.s.x[ii] ? LocMR.s.x[ii] : xx;}
	for(unsigned int ii = istart;ii<picdatalen;ii++){ xg = xg<LocMG.s.x[ii] ? LocMG.s.x[ii] : xg;}
	for(unsigned int ii = istart;ii<picdatalen;ii++){ xb = xb<LocMB.s.x[ii] ? LocMB.s.x[ii] : xb;}
	//xx = 262144;
	ng = nb = nx = 0xffffffff;
	for(unsigned int ii = istart;ii<picdatalen;ii++){ nx = nx>LocMR.s.x[ii] ? LocMR.s.x[ii] : nx;}
	for(unsigned int ii = istart;ii<picdatalen;ii++){ ng = ng>LocMG.s.x[ii] ? LocMG.s.x[ii] : ng;}
	for(unsigned int ii = istart;ii<picdatalen;ii++){ nb = nb>LocMB.s.x[ii] ? LocMB.s.x[ii] : nb;}
	//v	= log(double(xx)/double(nx));
	//LocM.showfull_infile("LocM.txt");v

	xg = xb = xx = xx > xb ? (xx > xg ? xx : (xg > xb ? xg : xb)) : (xb > xg ? xb : (xx > xg ? xx : xg));

	ng = nb = nx = nx < nb ? (nx < ng ? nx : (ng < nb ? ng : nb)) : (nb < ng ? nb : (nx < ng ? nx : ng));

	picdata = new  unsigned char [4*picdatalen];

	//unsigned int dL = 1024;//2048;//dnull;//1024;//4100;
	//double z0, z1;
	//dL = nx;
	xx -= nx;
	xg -= ng;
	xb -= nb;
	xx == 0 ? 1 : xx;
	xg == 0 ? 1 : xg;
	xb == 0 ? 1 : xb;
	//ww  = 1;
	//v	= log(double(xx)/ww);///double(dL));
	//ww = 0.4;//0.2;//0.3

	v = 4.0*contrast / 300.0 + 1 / 3.0;
	dz = 2.0*bright / 300.0 - 1 / 3.0;
	ww = 2.0*gamma / 100.0;

	for(unsigned int ii = 0;ii<picdatalen;ii++)
	{
		z	= ((int)(LocMB.s.x[ii])-nb);
		z   = z>1 ? z : 1;
		z	/= (double)xb;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w	= unsigned char(z);
		picdata[4*ii]	= w;

		z	= ((int)(LocMG.s.x[ii])-ng);
		z   = z>1 ? z : 1;
		z	/= (double)xg;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w	= unsigned char(z);
		picdata[4*ii+1]	= w;

		z	= ((int)(LocMR.s.x[ii])-nx);
		z   = z>1 ? z : 1;
		z	/= (double)xx;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w	= unsigned char(z);
		picdata[4*ii+2]	= w;

		picdata[4*ii+3]	= 0xff;
	}
	//picdatalen *= 4;
	//pixmap->loadFromData(picdata,picdatalen,"BMP",Qt::MonoOnly);
	pxmp = QImage(picdata,szx,szy,QImage::Format_RGB32);
	//delete [] picdata;
	picdata = 0x0;

	if (nupdt == 0) 	update();

}


/*void PicView::setpicdata(FullMatrix<unsigned short> &MR, FullMatrix<unsigned short> &MG, FullMatrix<unsigned short> &MB)
{
	QRect rct = this->rect();//this->visibleRegion().boundingRect();
	int Dx, Dy, S; // размеры видимой области
	int Npx; // количество элементов исходного изображения умещающихся в одном пикселе экранной картинки

	unsigned char * picdata; // данные для рисования картинки
	unsigned int picdatalen; // длина буфера picdata

	unsigned int X;
	unsigned short *xm;

	// размеры видимой области
	Npx = 4;
	setsz(MR.nx / Npx, MR.ny / Npx);

	Dx = this->rect().width();  // szx
	Dy = this->rect().height(); // szy
								//picdatalen = 

	FullMatrix<unsigned int> LocMR(Dy, Dx);
	FullMatrix<unsigned int> LocMG(Dy, Dx);
	FullMatrix<unsigned int> LocMB(Dy, Dx);

	unsigned int * xl;

	picdatalen = 4 * Dx*Dy; // предполагается глубина цвета - 32 бита.
	S = Dx*Dy;
	//picdata = new [picdatalen] unsigned char; 

	for (int ii = 0; ii<LocMR.ny; ii++)
	{
		xl = LocMR.x.x[ii];
		for (int ij = 0; ij<Npx; ij++)
		{
			xm = MR.x.x[ii*Npx + ij];
			for (int jj = 0; jj<LocMR.nx; jj++)
			{
				X = 0;
				for (int ji = 0; ji<Npx; ji++) X += xm[ij];
				xl[jj] += X;
				xm += Npx;
			}
		}
	}

	for (int ii = 0; ii<LocMG.ny; ii++)
	{
		xl = LocMG.x.x[ii];
		for (int ij = 0; ij<Npx; ij++)
		{
			xm = MG.x.x[ii*Npx + ij];
			for (int jj = 0; jj<LocMG.nx; jj++)
			{
				X = 0;
				for (int ji = 0; ji<Npx; ji++) X += xm[ij];
				xl[jj] += X;
				xm += Npx;
			}
		}
	}

	for (int ii = 0; ii<LocMB.ny; ii++)
	{
		xl = LocMB.x.x[ii];
		for (int ij = 0; ij<Npx; ij++)
		{
			xm = MB.x.x[ii*Npx + ij];
			for (int jj = 0; jj<LocMB.nx; jj++)
			{
				X = 0;
				for (int ji = 0; ji<Npx; ji++) X += xm[ij];
				xl[jj] += X;
				xm += Npx;
			}
		}
	}

	picdatalen = LocMR.nx*LocMR.ny;


	double z, v, dz;
	unsigned int xx, xg, xb, nx;
	unsigned char w;
	xx = 0;
	for (unsigned int ii = 3 * LocMR.nx; ii<picdatalen; ii++) { xx = xx<LocMR.s.x[ii] ? LocMR.s.x[ii] : xx; }
	for (unsigned int ii = 3 * LocMR.nx; ii<picdatalen; ii++) { xx = xx<LocMG.s.x[ii] ? LocMG.s.x[ii] : xx; }
	for (unsigned int ii = 3 * LocMR.nx; ii<picdatalen; ii++) { xx = xx<LocMB.s.x[ii] ? LocMB.s.x[ii] : xx; }
	//xx = 262144;
	nx = 0xffffffff;
	for (unsigned int ii = 3 * LocMR.nx; ii<picdatalen; ii++) { nx = nx>LocMR.s.x[ii] ? LocMR.s.x[ii] : nx; }
	//v	= log(double(xx)/double(nx));
	//LocM.showfull_infile("LocM.txt");
	picdata = new  unsigned char[4 * picdatalen];
	//xx = 13500*Npx*Npx;
	unsigned int dL = nx;//2048*Npx;
	xx -= dL;
	/*v = double(contrast)/100.0;//0.2;
	dz = double(bright)/100.0;//0.1;
	double z0,z1;
	z0 = 0;//1-1/(exp((0.0-dz)/v)+1);
	z1 = 1;//1-1/(exp((1.0-dz)/v)+1);
	* /
	v = 4.0*contrast / 300.0 + 1 / 3.0;
	dz = 2.0*bright / 300.0 - 1 / 3.0;
	//xg -= dL;
	//xb -= dL;
	for (unsigned int ii = 0; ii<picdatalen; ii++)
	{
		z = (int)(LocMB.s.x[ii] - dL);
		z = z>1 ? z : 1;
		z /= (double)xx;
		//z   = pow(z,v);
		//z	= log(z*v);
		//z	/= v;
		//z   = ((1-1/(exp((z-dz)/v)+1))-z0)/(z1-z0);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w = unsigned char(z);
		picdata[4 * ii] = w;
		z = ((int)(LocMG.s.x[ii] - dL));
		z = z>1 ? z : 1;
		z /= (double)xx;
		//z   = pow(z,v);
		//z	= log(z*v);
		//z	/= v;
		//z   = ((1-1/(exp((z-dz)/v)+1))-z0)/(z1-z0);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w = unsigned char(z);
		picdata[4 * ii + 1] = w;
		z = ((int)(LocMR.s.x[ii] - dL));
		z = z>1 ? z : 1;
		z /= (double)xx;
		//z   = pow(z,v);
		//z	= log(z*v);
		//z	/= v;
		//z   = ((1-1/(exp((z-dz)/v)+1))-z0)/(z1-z0);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z *= 255.0;
		w = unsigned char(z);
		picdata[4 * ii + 2] = w;
		picdata[4 * ii + 3] = 0xff;
	}
	//picdatalen *= 4;
	//pixmap->loadFromData(picdata,picdatalen,"BMP",Qt::MonoOnly);

	pxmp = QImage(picdata, szx, szy, QImage::Format_RGB32);

	update();

	picdata = 0x0;

	//delete [] picdata;

}*/

void PicView::setpicdataFull(FullMatrix<unsigned short> &MR,FullMatrix<unsigned short> &MG,FullMatrix<unsigned short> &MB)
{
	unsigned char * picdata; // данные для рисования картинки
	setsz(MR.nx,MR.ny);
	unsigned int picdatalen = MR.nx*MR.ny;
	picdata = new  unsigned char [4*picdatalen];


	double z;
	unsigned int xx,nx,w,xb,xg;
	xb= xg = xx = 0;
	for(unsigned int ii = 0;ii<picdatalen;ii++){ xx = xx<MR.s.x[ii] ? MR.s.x[ii] : xx;}
	for(unsigned int ii = 0;ii<picdatalen;ii++){ xg = xg<MG.s.x[ii] ? MG.s.x[ii] : xg;}
	for(unsigned int ii = 0;ii<picdatalen;ii++){ xb = xb<MB.s.x[ii] ? MB.s.x[ii] : xb;}
	//xx = 262144;
	nx = 0xffffffff;
	for(unsigned int ii = 0;ii<picdatalen;ii++){ nx = nx>MR.s.x[ii] ? MR.s.x[ii] : nx;}
	for(unsigned int ii = 0;ii<picdatalen;ii++){ nx = nx>MG.s.x[ii] ? MG.s.x[ii] : nx;}
	for(unsigned int ii = 0;ii<picdatalen;ii++){ nx = nx>MB.s.x[ii] ? MB.s.x[ii] : nx;}

	//xb -= nx;
	//xg -= nx;
	//xx -= nx;
	xb = xg = xx -= nx;
	xx == 0 ? 1 : xx;
	xg == 0 ? 1 : xg;
	xb == 0 ? 1 : xb;

	double dz, v, ww;
	v = 4.0*contrast / 300.0 + 1 / 3.0;
	dz = 2.0*bright / 300.0 - 1 / 3.0;
	ww = 2.0*gamma / 100.0;

	for(unsigned int ii = 0;ii<picdatalen;ii++)
	{
		z	= (double)(MB.s.x[ii]-nx);
		z	/= (double)xb;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z	*= 255.0;
		w	= unsigned char(z);
		picdata[4*ii]	= w;
		z	= (double)(MG.s.x[ii]-nx);
		z	/= (double)xg;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z	*= 255.0;
		w	= unsigned char(z);
		picdata[4*ii+1]	= w;
		z	= (double)(MR.s.x[ii]-nx);
		z	/= (double)xx;
		z = pow(z, ww);
		z = v*z + dz;
		z = z>1 ? 1 : z;
		z = z<0 ? 0 : z;
		z	*= 255.0;
		w	= unsigned char(z);
		picdata[4*ii+2]	= w;
		picdata[4*ii+3]	= 0xff;
	}

	pxmp = QImage(picdata,szx,szy,QImage::Format_RGB32);
	update();
	picdata = 0x0;
}


void PicView::contextMenuEvent(QContextMenuEvent *event)
{
	cntxMenu->exec(QCursor::pos());
}

void PicView::setPic(const QImage &img)
{
	setsz(img.size().width() + lShft,img.size().height());
	//this->setFixedSize(szx,szy);
	pxmp = img;
	//rct = this->rect();
}

void PicView::paintEvent(QPaintEvent *event)
{
	QPainter qp(this);

	qp.begin(this);
	//qp.drawPixmap(0,0,*pxmp);
	qp.drawImage(lShft,0,pxmp);

	qp.setRenderHint(QPainter::Antialiasing,false);
	qp.setPen(QPen(Qt::white, 1, Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));


	if(type == 0)
	{
		qp.drawLine(szx*x1,szy*y1,szx*x2,szy*y2);
		qp.drawEllipse(szx*x1-3,szy*y1-3,5,5);
		qp.drawEllipse(szx*x2-3,szy*y2-3,5,5);
	}else
	{
		qp.drawRect(szx*x1,szy*y1,szx*(x2-x1),szy*(y2-y1));
		qp.drawEllipse(szx*x1-3,szy*y1-3,5,5);
		qp.drawEllipse(szx*x2-3,szy*y2-3,5,5);
	}

	qp.end();
	emit updtcrd();

	event->accept();
}

void PicView::mousePressEvent(QMouseEvent *event)
{
	int lx,ly,wx1,wy1,wx2,wy2;
	double rr1,rr2;

	lx = event->x();
	ly = event->y();

	wx1	= lx-szx*x1;
	wy1	= ly-szy*y1;
	rr1 = (wx1*wx1)+(wy1*wy1);
	wx2	= lx-szx*x2;
	wy2	= ly-szy*y2;
	rr2 = (wx2)*(wx2)+(wy2)*(wy2);
	

	if(rr1<17)
	{
		movtype = 1;
	}else
	{
		if(rr2<17) 
		{
			movtype = 2;
		}else
		{
			if ((wx1*wx2<0)&&(wy1*wy2<0))
			{
				movtype = 3;
				msx = lx;
				msy = ly;
			}
		}
	}

	event->accept();
}

void PicView::mouseReleaseEvent(QMouseEvent *event)
{
	if(movtype != 0)
	{
		emit recalc();
	}
	movtype = 0;
	event->accept();
}

void PicView::mouseMoveEvent(QMouseEvent *event)
{
	int lx,ly;
	switch (movtype)
	{
	case 1:
		lx = event->x();
		x1 = lx< szx ? (lx>=0 ? double(lx)/szx : x1) : x1 ;
		ly = event->y();
		y1 = ly<szy ? (ly>=0 ? double(ly)/szy : y1) : y1;
		recalc();
		break;
	case 2:
		lx = event->x();
		x2 = lx< szx ? (lx>=0 ? double(lx)/szx : x2) : x2 ;
		ly = event->y();
		y2 = ly<szy ? (ly>=0 ? double(ly)/szy : y2) : y2;
		recalc();
		break;
	case 3:
		int dx,dy;//,x1_,x2_,y1_,y2_;
		lx = event->x();
		ly = event->y();
		dx = lx - msx;
		dy = ly - msy;
		/*x1_ = x1*szx + dx;
		x2_ = x2*szx + dx;
		y1_ = y1*szy + dy;
		y2_ = y2*szy + dy;

		x1 = (x1_>0)&(x1_<szx) ? double(x1_)/double(szx) : x1;
		y1 = (y1_>0)&(y1_<szy) ? double(y1_)/double(szy) : y1;
		x2 = (x2_>0)&(x2_<szx) ? double(x2_)/double(szx) : x2;
		y2 = (y2_>0)&(y2_<szy) ? double(y2_)/double(szy) : y2;
*/
		double ddx,ddy,h1,h2;

		ddx = double(dx)/szx;
		ddy = double(dy)/szy;

		h1 = x1 + ddx;
		h2 = x2 + ddx;
		x1 = (h1>0)&(h1<1) ? h1 : x1;
		x2 = (h2>0)&(h2<1) ? h2 : x2;

		h1 = y1 + ddy;
		h2 = y2 + ddy;
		y1 = (h1>0)&(h1<1) ? h1 : y1;
		y2 = (h2>0)&(h2<1) ? h2 : y2;
		


		msy = ly;
		msx = lx;
		recalc();
		break;
	}
	/*if(movtype == 1)
	{
		int lx;
		lx = event->x();
		x1 = lx< szx ? (lx>=0 ? double(lx)/szx : x1) : x1 ;
		lx = event->y();
		y1 = lx<szy ? (lx>=0 ? double(lx)/szy : y1) : y1;
		//emit recalc();
	}
	if(movtype == 2)
	{
		int lx;
		lx = event->x();
		x2 = lx< szx ? (lx>=0 ? double(lx)/szx : x2) : x2 ;
		lx = event->y();
		y2 = lx<szy ? (lx>=0 ? double(lx)/szy : y2) : y2;
		//emit recalc();
	}*/

	update();
	event->accept();
}

void PicView::keyPressEvent(QKeyEvent *event)
{
	double dx = dd/double(szx);
	double dy = dd/double(szy);
	double x1_,y1_,x2_,y2_;
	switch (event->key())
	{
		case Qt::Key_Up :
			y1 -= (y1>dy) ? dy : 0;
			y2 -= (y2>dy) ? dy : 0;
			break;
		case Qt::Key_Left :
			x1 -= (x1>dx) ? dx : 0;
			x2 -= (x2>dx) ? dx : 0;
			break;
		case Qt::Key_Down :
			y1 += (y1<(1-dy)) ? dy : 0;
			y2 += (y2<(1-dy)) ? dy : 0;
			break;
		case Qt::Key_Right :
			x1 += (x1<(1-dy)) ? dx : 0;
			x2 += (x2<(1-dy)) ? dx : 0;
			break;
		case (Qt::Key_Control) :
			dd = 2.5;
			break;
		case (Qt::Key_Minus) :
			
			x1_ = x1*0.95+x2*0.05;
			y1_ = y1*0.95+y2*0.05;
			x2_ = x1*0.05+x2*0.95;
			y2_ = y1*0.05+y2*0.95;
			x1 = (x1_>0)&(x1_<1) ? x1_ : x1;
			y1 = (y1_>0)&(y1_<1) ? y1_ : y1;
			x2 = (x2_>0)&(x2_<1) ? x2_ : x2;
			y2 = (y2_>0)&(y2_<1) ? y2_ : y2;
			break;
		case (Qt::Key_Plus) :
			//double x1_,y1_,x2_,y2_;
			x1_ = x1*1.05-x2*0.05;
			y1_ = y1*1.05-y2*0.05;
			x2_ = -x1*0.05+x2*1.05;
			y2_ = -y1*0.05+y2*1.05;
			x1 = (x1_>0)&(x1_<1) ? x1_ : x1;
			y1 = (y1_>0)&(y1_<1) ? y1_ : y1;
			x2 = (x2_>0)&(x2_<1) ? x2_ : x2;
			y2 = (y2_>0)&(y2_<1) ? y2_ : y2;
			
			break;
		case (Qt::Key_Escape) :
			if (this->isFullScreen())
			{
				this->close();
			}
			break;
	}
	emit recalc();
	QPaintEvent *qpe;
	qpe = new QPaintEvent(this->rect());
	paintEvent(qpe);
	event->accept();
}

void PicView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key()==Qt::Key_Control)
	{
		dd = 0.25;
	}
	event->accept();
}

#endif

