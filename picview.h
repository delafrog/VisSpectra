#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>
#include <QImage>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QContextMenuEvent>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QSlider>
//#include <QPainter>
//#include <QPaintEvent>

#include "linalg.h"

class PicView : public QWidget
{
	Q_OBJECT
public:
	PicView(QWidget *parent = 0);
	~PicView(){ };//if (picdata!= 0x0) delete [] picdata;};

	void setpicdata(FullMatrix<unsigned short> &M); // генерирование буфера картинки из исходных данных матрицы M
	void setpicdata(FullMatrix<double> &AC); // генерирование буфера картинки из исходных данных матрицы
	void setpicdata(const FullMatrix<unsigned short> &MR, const FullMatrix<unsigned short> &MG, const FullMatrix<unsigned short> &MB, int nupdt = 0);
	void setpicdataFull(FullMatrix<unsigned short> &MR,FullMatrix<unsigned short> &MG,FullMatrix<unsigned short> &MB);

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

	void contextMenuEvent(QContextMenuEvent *event);


	void getpnts(double &x1_,double &y1_,double &x2_,double &y2_){x1_ = x1; x2_ = x2; y1_ = y1; y2_ = y2;}
	void setpnts(double x1_, double y1_, double x2_, double y2_) { x1 = x1_; x2 = x2_; y1 = y1_; y2 = y2_; }
	void settype(int t){type = t;}
	void getsz(int &zx,int &zy){zx = szx; zy = szy;}
	int & getlen() { return szx; }
	void setsz(int zx,int zy){szx = zx;szy = zy;this->setFixedSize(szx, szy);}
	void BlackFill() {pxmp = QImage(szx, szy, QImage::Format_RGB32);pxmp.fill(0);}

	QImage & getPic(){return pxmp;}
	void setPic(const QImage &img);
	void setnulloffset(int id) { idnull = id; }
	void set_lShft(int lSh) { lShft = lSh; }

	void setPixelScale(int idSc) { pixScale = idSc; }

	void setBrCnGm(int br, int cn, int gm) {bright = br; contrast = cn; gamma = gm; bright_sldr->setSliderPosition(bright); contrast_sldr->setSliderPosition(contrast); gamma_sldr->setSliderPosition(gamma);	}
	void getBrCnGm(int &br, int &cn, int &gm) { 	br = bright ;  cn = contrast;gm = gamma ; 	}

signals:
	void recalc();
	void updtcrd();
	void getnewpic();// сигнал для вызова генерирования новой картинки

public slots:
	void br_ch(int br) { bright = br; getnewpic(); }
	void cn_ch(int cn) { contrast = cn; getnewpic(); }
	void gm_ch(int gm) { gamma = gm; getnewpic(); }

protected:
		void paintEvent(QPaintEvent *event);
private:


	QDialog *pic_setup_box; // окошко для настройки параметров изображения
	QSlider *bright_sldr, *contrast_sldr,*gamma_sldr; // ползунки для установки яркости и контраста
	int bright, contrast,gamma; // значения констант яркости и контраста
	QVBoxLayout *vbox1;
	QHBoxLayout *hbox1, *hbox2,*hbox3;
	QMenu *cntxMenu; // конеткстное меню
	QAction *actionPictureSetup; // действие - вызвать окно настройки яркости
	QLabel *cnbr_label, *cn_lbl, *br_lbl, *gm_lbl;

	QImage pxmp;
	//unsigned char * picdata; // данные для рисования картинки

	int szx,szy;
	double x1,x2,y1,y2,dd; // координаты концов отрезка определяющего сечение картинки для рисования графика зависимости интенсивности от координаты
	int movtype,msx,msy;
	int lShft; // число пикселей для сдвига картинки от левого края вправо

	//QRect * rect; // прямоугольник для определения области построения гистограммы

	int type;
	int idnull;

	int pixScale; 
};

#endif