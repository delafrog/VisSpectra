#ifndef HELPBROWSER_CPP
#define HELPBROWSER_CPP

#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &path, const QString &page,	QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_GroupLeader);

	textBrowser = new QTextBrowser(this);
	//textBrowser->

	homeButton = new QPushButton(tr("&Home"), this);
	backButton = new QPushButton(tr("&Back"), this);
	closeButton = new QPushButton(tr("Close"), this);
	closeButton->setShortcut(tr("Esc"));

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	buttonLayout->addWidget(homeButton);
	buttonLayout->addWidget(backButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(closeButton);

	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(textBrowser);

	setLayout(mainLayout);

	connect(homeButton, SIGNAL(clicked()),	textBrowser, SLOT(home()));
	connect(backButton, SIGNAL(clicked()),	textBrowser, SLOT(backward()));
	connect(closeButton, SIGNAL(clicked()),	this, SLOT(close()));
	connect(textBrowser, SIGNAL(sourceChanged(const QUrl &)),	this, SLOT(updateWindow()));

	textBrowser->setSearchPaths(QStringList() << path << ":/images");
	textBrowser->setSource(page);
}


void HelpBrowser::updateCaption()
{
	setWindowTitle(tr("Help: %1").arg(textBrowser->documentTitle()));
}

void HelpBrowser::showPage(const QString &page)
{
	QString path = QDir(QString("doc")).absolutePath();
	HelpBrowser *browser = new HelpBrowser(path, page);
	browser->resize(500, 400);
	browser->show();
}

#endif