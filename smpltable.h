#ifndef SMPLTABLE_H
#define SMPLTABLE_H

#include <QTableWidget>
//#include <QAbstractTableModel> 
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include "linalg.h"
//#include "linalg.cpp"



/*

class SmplTableModel : public QAbstractTableModel // ������ ������ - �������
{
	Q_OBJECT
public:
	SmplTableModel(QObject *parent = 0);

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const; // ���������� ������ ��������
	Qt::ItemFlags flags(const QModelIndex & index) const; // ��������� ���� ��������� ��������
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const; // ���������� ������ ��� ��������� 
	int rowCount(const QModelIndex & parent = QModelIndex()) const; // ��������� ���������� ��������� ������
	int columnCount(const QModelIndex & parent = QModelIndex()) const; // ��������� ���������� ��������� ������

	bool setData(const QModelIndex &index, const QVariant &value, int role);

//	void setTypeData(const QModelIndex &index, const int type);

	//void setImgData(const vecT< vec4FMushort > &imgs_);//{imgs = imgs_}; // ���������� ����� �������
//	void addImgData(const IIMData &img_);//{imgs = imgs_}; // �������� ���� ������ � �����
//	void delImgData(const QModelIndex &index); // ������� ������ �� ��� �������
	void setItemData(const double &x, int iy, int ix) { Mtr.set(iy, ix) = x; }

private :
	FullMatrix<double> Mtr;
};

class SmplTableView : public QTableView
{
	Q_OBJECT
public:
	SmplTableView(QWidget *parent = 0);
	~SmplTableView() {};

};*/

class SmplTableView : public QTableWidget
{
	Q_OBJECT
public:
	SmplTableView(QWidget *parent = 0);
	~SmplTableView() {};

	void contextMenuEvent(QContextMenuEvent *e);

signals:
	void Table2Clipboad();
	void Clipboad2Table();
	void TableClearAll();

private:

	QMenu *contextMenu; // ����������� ���� ��� �������� ������� � �����
	QAction *contextAction; // �������� ������� �����
	QAction *contextClearAllAction; // �������� ������� �����
	QAction *contextPasteAction; // �������� ������ �� ������ � �������
}; 

#endif