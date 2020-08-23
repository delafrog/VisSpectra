#ifndef SMPLTABLE_CPP
#define SMPLTABLE_CPP

#include "smpltable.h"

/*SmplTableModel::SmplTableModel(QObject *parent) : QAbstractTableModel(parent)
{
	
}

Qt::ItemFlags SmplTableModel::flags(const QModelIndex & index) const // возращает флаг атрибутов элемента
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable; // элемент может быть изменён и отмечен как выбраный
}

QVariant SmplTableModel::data(const QModelIndex & index, int role) const // возвращает данные элемента
{
	if (!index.isValid())
	{
		return QVariant();
	}
	int ix, iy;
	double x;
	ix = index.column();
	iy = index.row();
	x = Mtr.x.x[iy][ix];// fst(iy, ix);
	switch (role)
	{
	case Qt::DisplayRole:
		return qVariantFromValue(x);
	case Qt::ToolTipRole:
		return qVariantFromValue(x);//index.row();	
	default:
		return QVariant();
	}
}


QVariant SmplTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

bool SmplTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		index.data() = value;
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

int SmplTableModel::rowCount(const QModelIndex & parent) const // возращает количество элементов списка
{
	return Mtr.ny;
}
int SmplTableModel::columnCount(const QModelIndex & parent) const // возращает количество элементов списка
{
	return Mtr.nx;
}


SmplTableView::SmplTableView(QWidget *parent) : QTableView(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectItems);


}*/


SmplTableView::SmplTableView(QWidget *parent) : QTableWidget(parent)
{
	contextMenu = new QMenu(this);
	contextAction = new QAction(tr("Copy Table"), this);
	contextPasteAction = new QAction(tr("Paste Table"), this);
	contextClearAllAction  = new QAction(tr("Clear Table"), this); // передать данныев буфер

	contextMenu->addAction(contextAction);
	contextMenu->addAction(contextPasteAction);
	contextMenu->addAction(contextClearAllAction);

	connect(contextAction, SIGNAL(triggered()), this, SIGNAL(Table2Clipboad()));
	connect(contextPasteAction, SIGNAL(triggered()), this, SIGNAL(Clipboad2Table()));

	connect(contextClearAllAction, SIGNAL(triggered()), this, SIGNAL(TableClearAll()));
	
	setContextMenuPolicy(Qt::DefaultContextMenu);
}

void SmplTableView::contextMenuEvent(QContextMenuEvent *e)
{
	contextMenu->exec(QCursor::pos());
}

#endif