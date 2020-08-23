/*
main.cpp 
загрузка и запуск приложения.
--------------

*/
#include <QApplication>
#include <fstream>
#include <QMessageBox>
//#include "ui_base_win.h"
#include "mainwin.h"

int main(int argc, char *argv[]) 
{ 
	//setlocale(LC_ALL, "rus");
	QApplication app(argc, argv,true);
	//app.setAttribute(Qt::AA_DontShowIconsInMenus);
	MainWin *mainWin =  new MainWin();
	mainWin->show();
	return app.exec();
}