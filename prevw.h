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
	QImage imgs; // ������ ��� ������
	QImage bigIm; // ������ ��� �������� �����������
	QString filename; // ��� �����
	int type;  // ��� ������� - ������������� - 0 ��� ������� - 1

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

	void setcalibr_type(); // ���������� ������������� ��� �������
	void setwork_type(); // ���������� ������� ��� �������
	void setdark_type(); // ���������� ������� ��� �������

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



class ImageIconModel : public QAbstractListModel // ������ ������ - �������� ������ - ����� ����� ������ ������
{
	Q_OBJECT
public :
	ImageIconModel(QObject *parent =0);
	//ImageIconModel(const ImageIconModel &other);
	//~ImageIconModel();

	//ImageIconModel& operator = (const ImageIconModel& other);

	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const; // ���������� ������ ��������
	Qt::ItemFlags flags ( const QModelIndex & index ) const; // ��������� ���� ��������� ��������
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const; // ���������� ������ ��� ��������� 
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const; // ��������� ���������� ��������� ������

	bool setData(const QModelIndex &index, const QVariant &value, int role);

	void setTypeData(const QModelIndex &index, const int type);

	//void setImgData(const vecT< vec4FMushort > &imgs_);//{imgs = imgs_}; // ���������� ����� �������
	void addImgData(const IIMData &img_);//{imgs = imgs_}; // �������� ���� ������ � �����
	void delImgData(const QModelIndex &index); // ������� ������ �� ��� �������

//public signals:
//	void type_change(int tp){tp = }

private :
	//vecT< vec4FMushort > *imgs;
	//QList<QImage> imgs;// ����� ����������� ����������� �������
	QList<IIMData> dts;
	//int selected_id;
	//QList<int> imgs;
};



class ImageIconDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	ImageIconDelegate(QObject *parent =0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; // ��������� ������ ��������
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

	QMenu *contextMenu1; // ����������� ���� ��� ������ ���� �������
	QAction *contextAction1_1; // ���������� ������ ��� �������������
	QAction *contextAction1_2; // ���������� ������ ��� �������
	QAction *contextAction1_3; // ���������� ������ ��� �������

	QAction *contextAction1_sav; // ��������� ������
	QAction *contextAction1_del; // ��������� ������ �� ���������

	QIcon *galcaIcon;

	//QModelIndex modelindex;

};

#endif