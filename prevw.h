#ifndef PREVW_H
#define PREVW_H


#include <QObject>
#include <QImage>
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QList>
#include <QSize>
#include <QVariant>
#include <QListView>
//#include <QPainter>
//#include <QPaintEvent>

#include "linalg.h"
#include "picview.h"

class QMenu;
class QAction;
class QIcon;
//class QModelIndexList;


struct IIMDataPtr
{
	QImage imgs; // данные для иконки
	QImage bigIm; // данные для большого изображения
	QString filename; // имя файла
	int type;  // тип спектра - калибровочный - 0 или рабочий - 1

};


class IIMData //: public QObject
{
	//Q_OBJECT
public:
	IIMData();//QObject *parent = 0);
	IIMData(const IIMData &other);
	~IIMData();

	IIMData & operator = (const IIMData& other);

	void gensmall();

	void setcalibr_type(); // установить калибровочный тип спектра
	void setwork_type(); // установить рабочий тип спектра
	void setdark_type(); // установить рабочий тип спектра

//private:
	IIMDataPtr *d;
};
Q_DECLARE_METATYPE(IIMData)

/*class PrView : public QWidget
{
	Q_OBJECT
public:
	PrView(QWidget *parent = 0);
	~PrView(){};
}*/

/*

class ImageIconView : public QTableView
{
	Q_OBJECT
public:
	ImageIconView(QBject *parent = 0);

	QModelIndex ImagIconView::indexAt ( const QPoint & pos ) const ;
};
*/



class ImageIconModel : public QAbstractListModel // модель данных - линейный массив - ближе всего модель списка
{
	Q_OBJECT
public :
	ImageIconModel(QObject *parent =0);
	//ImageIconModel(const ImageIconModel &other);
	//~ImageIconModel();

	//ImageIconModel& operator = (const ImageIconModel& other);

	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const; // возвращает данные элемента
	Qt::ItemFlags flags ( const QModelIndex & index ) const; // возращает флаг атрибутов элемента
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const; // возвращает данные для заголовка 
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const; // возращает количество элементов списка

	bool setData(const QModelIndex &index, const QVariant &value, int role);

	void setTypeData(const QModelIndex &index, const int type);

	//void setImgData(const vecT< vec4FMushort > &imgs_);//{imgs = imgs_}; // установить набор снимков
	void addImgData(const IIMData &img_);//{imgs = imgs_}; // добавить один снимок в конец
	void delImgData(const QModelIndex &index); // удалить снимок по его индексу

//public signals:
//	void type_change(int tp){tp = }

private :
	//vecT< vec4FMushort > *imgs;
	//QList<QImage> imgs;// набор уменьшенных изображений снимков
	QList<IIMData> dts;
	//int selected_id;
	//QList<int> imgs;
};



class ImageIconDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	ImageIconDelegate(QObject *parent =0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; // рисование ячейки элемента
	QSize sizeHint(const QStyleOptionViewItem &option,  const QModelIndex &index ) const;

	//QWidget create
 //public slots:


 //private:
     
};


class ListView : public QListView
{
	Q_OBJECT
public: 
	ListView(QWidget *parent = 0);
	~ListView(){};

	void contextMenuEvent ( QContextMenuEvent *e);

public slots:
	void setclbr();
	void setwork();
	void setdark();
	void getsave();
	void delspec();

signals:
	void save(const QModelIndex &);
	void del(const QModelIndex &);

private:

	QMenu *contextMenu1; // контекстное меню для выбора типа спектра
	QAction *contextAction1_1; // обозначить спектр как калибровочный
	QAction *contextAction1_2; // обозначить спектр как рабочий
	QAction *contextAction1_3; // обозначить спектр как фоновый

	QAction *contextAction1_sav; // сохранить спектр
	QAction *contextAction1_del; // выгрузить спектр из программы

	QIcon *galcaIcon;

	//QModelIndex modelindex;

};

#endif