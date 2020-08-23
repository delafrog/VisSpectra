#ifndef PREVW_CPP
#define PREVW_CPP

#include <QObject>
#include <QImage>
#include <QAbstractListModel>
#include <QPainter>
#include <QList>
#include <QVariant>
#include <QListView>
#include "prevw.h"
#include <QMenu>
#include <QAction>
#include <QModelIndexList>




IIMData::IIMData()//QObject *parent) : QObject(parent)
{
	d = new IIMDataPtr;
	d->type = -1;
}
IIMData::IIMData(const IIMData &other)
{
	d = new IIMDataPtr(*other.d);
}
IIMData::~IIMData()
{
	delete d;
}
IIMData& IIMData::operator = (const IIMData& other)
{
	*d = *other.d;
	return *this;
}
void IIMData::gensmall()
{
	d->imgs = d->bigIm.scaled(320,240,Qt::KeepAspectRatio,Qt::FastTransformation);
}

void IIMData::setcalibr_type()
{
	d->type = 0;
}
void IIMData::setwork_type()
{
	d->type = 1;
}

void IIMData::setdark_type()
{
	d->type = 2;
}
//view
/*ImageIconView::ImageIconView(QObject *parent) : QTableView(parent){}

QModelIndex ImageIconView::indexAt(const QPoint &pos) const
{
	QModelIndex Id;
	
}*/
//________________________
// model
ImageIconModel::ImageIconModel(QObject *parent) : QAbstractListModel(parent)
{
	//d = new IIMData;
	//selected_id = -1;
	//imgs << 12<<13<<54<<2<<21<<65<<23<<39475089<<32984<<348927<<43089217<<329847<<4382901<<489302<<4093824<<120938<<4783209<<567	<<12<<654<<9283<<2390<<5734<<190<<8359<<4839<<392<< 123<<193<<-323<<238<<-909<<323<<329<<-390<<54<<656<<-3454<<76<<7483<<32<<90<<-9327<<32<<4<<32<<43<<65<<43<<8<<65<<12<<98<<54<<90<<12<<43<<2902<<91<<49<<21<<65<<94<<901;
}

Qt::ItemFlags ImageIconModel::flags ( const QModelIndex & index ) const // возращает флаг атрибутов элемента
{
	if(!index.isValid())
		return Qt::NoItemFlags;
	
	return Qt::ItemIsEnabled|Qt::ItemIsSelectable; // элемент может быть изменён и отмечен как выбраный
}

QVariant ImageIconModel::data ( const QModelIndex & index, int role ) const // возвращает данные элемента
{
	if(!index.isValid())
	{
		return QVariant();
	}
	int id = index.row();
	switch (role)
	{
	case Qt::DisplayRole : 	
		return qVariantFromValue(dts.at(id));
	case Qt::ToolTipRole:
		return qVariantFromValue(dts.at(id).d->filename);//index.row();	
	default :
		return QVariant();	
	}
}

bool ImageIconModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
     if (index.isValid() && role == Qt::EditRole) 
	 {
         index.data() = value;
         emit dataChanged(index, index);
         return true;
     }
     return false;
 }

void ImageIconModel::setTypeData(const QModelIndex &index, const int type)
{
	if (index.isValid())
	{
		int ii;
		ii = index.row();
		dts[ii].d->type = type;
		emit dataChanged(index, index);
	}
}

QVariant ImageIconModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
	return QVariant();	
}

int ImageIconModel::rowCount ( const QModelIndex & parent ) const // возращает количество элементов списка
{
	return dts.count();
}

void ImageIconModel::addImgData(const IIMData &img_)
{
	/*IIMData Ldat;
	
	Ldat.d->bigIm= img_.d
	Ldat.d->imgs = img_.d->imgs.scaled(320,240,Qt::KeepAspectRatio,Qt::FastTransformation);//Qt::SmoothTransformation);
	Ldat.d->filename = img_.d->filename;*/
//	selected_id = imgs.count();

	beginResetModel();

	dts.append(img_);
	//modelReset();
	endResetModel();
}
void ImageIconModel::delImgData(const QModelIndex &index) // удалить снимок по его индексу
{
	if (index.isValid())
	{
		int ii;
		ii = index.row();
		beginResetModel();
		dts.removeAt(ii);
		endResetModel();
	}
}
//_________________________
// delegate
ImageIconDelegate::ImageIconDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}
QSize ImageIconDelegate::sizeHint(const QStyleOptionViewItem &option,  const QModelIndex &index ) const
{
	return QSize(330,300);
}
void ImageIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
	{ // отрисовка фона при выделении элемента
		painter->fillRect(option.rect, option.palette.highlight());
	}

	//index.row()

	painter->save();

	painter->setRenderHint(QPainter::Antialiasing, true);

	 if (option.state & QStyle::State_Selected)
	 {
		 painter->setBrush(option.palette.highlightedText());
	 }    else
	 {
      	painter->setBrush(QBrush(Qt::gray));
	 }
	painter->drawRect(option.rect);
	//painter->drawImage(option.rect,index.data().value<QImage>());
	painter->drawImage(option.rect.x()+5,option.rect.y()+5,index.data().value<IIMData>().d->imgs,0,0,-1,-1,Qt::AutoColor);
	painter->drawText(option.rect.x()+5,option.rect.y()+240,index.data().value<IIMData>().d->filename);
	switch (index.data().value<IIMData>().d->type)
	{
	case 0:
			painter->drawText(option.rect.x()+5,option.rect.y()+255,QString("\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\321\213\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200"));//Calibration spectr
			break;
	case 1:
			painter->drawText(option.rect.x()+5,option.rect.y()+255,QString("\320\230\321\201\321\201\320\273\320\265\320\264\321\203\320\265\320\274\321\213\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200"));//Measure spectr
			break;
	case 2:
			painter->drawText(option.rect.x() + 5, option.rect.y() + 255, QString("Dark level distribution"));
			break;
	case 3:
			painter->drawText(option.rect.x() + 5, option.rect.y() + 255, QString("Thermal distribution"));
			break;
	default :
			painter->drawText(option.rect.x()+5,option.rect.y()+255,QString("\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265"));//Unspecialized picture
			break;
	}


	//painter->drawEllipse(option.rect);

	painter->restore();

	//QStyledItemDelegate::paint(painter,option,index);
}



ListView::ListView(QWidget *parent) : QListView(parent)
{
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectItems);


	contextMenu1		= new QMenu(this);
	contextAction1_1	= new QAction(tr("\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214\040\320\272\320\260\320\272\040\320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\321\213\320\271\040\321\201\320\277\320\265\320\272\321\202\321\200"),this);//Set as &calibration spectr

	contextAction1_2	= new QAction(tr("\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214\040\320\272\320\260\320\272\040\321\200\320\260\320\261\320\276\321\207\320\270\320\271\040\050\320\270\321\201\321\201\320\273\320\265\320\264\321\203\320\265\320\274\321\213\320\271\051\040\321\201\320\277\320\265\320\272\321\202\321\200"),this);//Set as &work spectr

	contextAction1_3 = new QAction(tr("Set as &dark level"), this);

	contextAction1_sav = new QAction(tr("\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214\040\320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265\040\321\201\320\277\320\265\320\272\321\202\321\200\320\260\040\320\262\040\320\261\320\270\320\275\320\260\321\200\320\275\320\276\320\274\040\320\262\320\270\320\264\320\265"), this);//&Save spectr as
	contextAction1_del = new QAction(tr("\320\243\320\261\321\200\320\260\321\202\321\214\040\321\201\320\277\320\265\320\272\321\202\321\200\040\320\270\320\267\040\321\201\320\277\320\270\321\201\320\272\320\260"), this);//&Remove spectr

	
	contextMenu1->addAction(contextAction1_1);
	contextMenu1->addAction(contextAction1_2);
	//contextMenu1->addAction(contextAction1_3);
	contextMenu1->addSeparator();
	contextMenu1->addAction(contextAction1_sav);
	contextMenu1->addAction(contextAction1_del);

	galcaIcon = new QIcon(QString("galka2.png"));

	connect(contextAction1_1,SIGNAL(triggered()),this,SLOT(setclbr()));
	connect(contextAction1_2,SIGNAL(triggered()),this,SLOT(setwork()));
	connect(contextAction1_3, SIGNAL(triggered()), this, SLOT(setdark()));

	connect(contextAction1_sav, SIGNAL(triggered()), this, SLOT(getsave()));
	connect(contextAction1_del, SIGNAL(triggered()), this, SLOT(delspec()));

}

void ListView::contextMenuEvent(QContextMenuEvent *e)
{
	QModelIndex modelindex;
	modelindex = currentIndex();//selectedIndexes();

	if (modelindex.isValid())
	{
		emit clicked(modelindex);
		switch (modelindex.data().value<IIMData>().d->type)
		{
		case 0:
		{
			contextAction1_1->setIcon(*galcaIcon);
			contextAction1_2->setIcon(QIcon());
			contextAction1_3->setIcon(QIcon());
			break;
		}
		case 1:
		{
			contextAction1_2->setIcon(*galcaIcon);
			contextAction1_1->setIcon(QIcon());
			contextAction1_3->setIcon(QIcon());
			break;
		}
		case 2:
		{
			contextAction1_3->setIcon(*galcaIcon);
			contextAction1_1->setIcon(QIcon());
			contextAction1_2->setIcon(QIcon());
			break;
		}
		default:
		{
			contextAction1_2->setIcon(QIcon());
			contextAction1_1->setIcon(QIcon());
			contextAction1_3->setIcon(QIcon());
			break;
		}
		}
		contextMenu1->exec(QCursor::pos());
	}

}
void ListView::setclbr()
{
	QModelIndex modelindex;
	ImageIconModel *ptr;
	modelindex	= currentIndex();//selectedIndexes();
	ptr = reinterpret_cast<ImageIconModel *> (model());
	ptr->setTypeData(modelindex,0);
	update(modelindex);
	//model()->reset();
}
void ListView::setwork()
{
	QModelIndex modelindex;
	ImageIconModel *ptr;
	modelindex	= currentIndex();//selectedIndexes();
	ptr = reinterpret_cast<ImageIconModel *> (model());
	ptr->setTypeData(modelindex,1);
	update(modelindex);
}

void ListView::setdark()
{
	QModelIndex modelindex;
	ImageIconModel *ptr;
	modelindex = currentIndex();//selectedIndexes();
	ptr = reinterpret_cast<ImageIconModel *> (model());
	ptr->setTypeData(modelindex, 2);
	update(modelindex);
}

void ListView::getsave()
{
	QModelIndex modelindex;
	modelindex = currentIndex();//selectedIndexes();
	emit save(modelindex);
}
void ListView::delspec()
{
	QModelIndex modelindex;
//	ImageIconModel *ptr;
	modelindex = currentIndex();//selectedIndexes();
	//ptr = reinterpret_cast<ImageIconModel *> (model());
	//ptr->delImgData(modelindex);
	emit del(modelindex);
}
#endif