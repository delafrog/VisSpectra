/********************************************************************************
** Form generated from reading UI file 'gui_.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI__H
#define UI_GUI__H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Image_Data_File;
    QAction *actionSave_Binary_Data_;
    QAction *actionSave_Prj;
    QAction *action_1;
    QAction *action;
    QAction *actionLinearInterp;
    QAction *actionDblLancszInterp;
    QAction *action_nbInt_3;
    QAction *actionApprox;
    QAction *actionClbr;
    QAction *actionWholeDescr;
    QAction *actionImrvLsDescr;
    QAction *actionClbrDescr;
    QAction *actionLnDestDescr;
    QAction *actionClbTbl;
    QAction *actionClbGrph;
    QAction *actionCurSpectr;
    QAction *actionPicColor;
    QAction *actionAbout;
    QAction *actionSpCurve;
    QAction *actionExit;
    QAction *action_nbInt_5;
    QAction *action_nbInt_10;
    QAction *action_nbInt_20;
    QAction *actionCubicInterp;
    QAction *action_FullFrame;
    QAction *action_SelFrame;
    QAction *action_WorkFrame;
    QAction *action_WorlFrClbr;
    QAction *action_6;
    QAction *action_7;
    QAction *actionAbout_Qt;
    QAction *actionSizeSetup;
    QAction *actionSave_Binary_Data;
    QAction *actionHelp;
    QAction *action_nbInt_1;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuExport;
    QMenu *menu_jpeg;
    QMenu *menuOptions;
    QMenu *menuInterpolator;
    QMenu *menu;
    QMenu *menuPicture;
    QMenu *menuHelp;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 323);
        QIcon icon;
        icon.addFile(QString::fromUtf8("visspec.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpen_Image_Data_File = new QAction(MainWindow);
        actionOpen_Image_Data_File->setObjectName(QString::fromUtf8("actionOpen_Image_Data_File"));
        actionSave_Binary_Data_ = new QAction(MainWindow);
        actionSave_Binary_Data_->setObjectName(QString::fromUtf8("actionSave_Binary_Data_"));
        actionSave_Prj = new QAction(MainWindow);
        actionSave_Prj->setObjectName(QString::fromUtf8("actionSave_Prj"));
        action_1 = new QAction(MainWindow);
        action_1->setObjectName(QString::fromUtf8("action_1"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        actionLinearInterp = new QAction(MainWindow);
        actionLinearInterp->setObjectName(QString::fromUtf8("actionLinearInterp"));
        actionDblLancszInterp = new QAction(MainWindow);
        actionDblLancszInterp->setObjectName(QString::fromUtf8("actionDblLancszInterp"));
        action_nbInt_3 = new QAction(MainWindow);
        action_nbInt_3->setObjectName(QString::fromUtf8("action_nbInt_3"));
        actionApprox = new QAction(MainWindow);
        actionApprox->setObjectName(QString::fromUtf8("actionApprox"));
        actionClbr = new QAction(MainWindow);
        actionClbr->setObjectName(QString::fromUtf8("actionClbr"));
        actionWholeDescr = new QAction(MainWindow);
        actionWholeDescr->setObjectName(QString::fromUtf8("actionWholeDescr"));
        actionImrvLsDescr = new QAction(MainWindow);
        actionImrvLsDescr->setObjectName(QString::fromUtf8("actionImrvLsDescr"));
        actionClbrDescr = new QAction(MainWindow);
        actionClbrDescr->setObjectName(QString::fromUtf8("actionClbrDescr"));
        actionLnDestDescr = new QAction(MainWindow);
        actionLnDestDescr->setObjectName(QString::fromUtf8("actionLnDestDescr"));
        actionClbTbl = new QAction(MainWindow);
        actionClbTbl->setObjectName(QString::fromUtf8("actionClbTbl"));
        actionClbGrph = new QAction(MainWindow);
        actionClbGrph->setObjectName(QString::fromUtf8("actionClbGrph"));
        actionCurSpectr = new QAction(MainWindow);
        actionCurSpectr->setObjectName(QString::fromUtf8("actionCurSpectr"));
        actionPicColor = new QAction(MainWindow);
        actionPicColor->setObjectName(QString::fromUtf8("actionPicColor"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionSpCurve = new QAction(MainWindow);
        actionSpCurve->setObjectName(QString::fromUtf8("actionSpCurve"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        action_nbInt_5 = new QAction(MainWindow);
        action_nbInt_5->setObjectName(QString::fromUtf8("action_nbInt_5"));
        action_nbInt_10 = new QAction(MainWindow);
        action_nbInt_10->setObjectName(QString::fromUtf8("action_nbInt_10"));
        action_nbInt_20 = new QAction(MainWindow);
        action_nbInt_20->setObjectName(QString::fromUtf8("action_nbInt_20"));
        actionCubicInterp = new QAction(MainWindow);
        actionCubicInterp->setObjectName(QString::fromUtf8("actionCubicInterp"));
        action_FullFrame = new QAction(MainWindow);
        action_FullFrame->setObjectName(QString::fromUtf8("action_FullFrame"));
        action_SelFrame = new QAction(MainWindow);
        action_SelFrame->setObjectName(QString::fromUtf8("action_SelFrame"));
        action_WorkFrame = new QAction(MainWindow);
        action_WorkFrame->setObjectName(QString::fromUtf8("action_WorkFrame"));
        action_WorlFrClbr = new QAction(MainWindow);
        action_WorlFrClbr->setObjectName(QString::fromUtf8("action_WorlFrClbr"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionSizeSetup = new QAction(MainWindow);
        actionSizeSetup->setObjectName(QString::fromUtf8("actionSizeSetup"));
        actionSave_Binary_Data = new QAction(MainWindow);
        actionSave_Binary_Data->setObjectName(QString::fromUtf8("actionSave_Binary_Data"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        action_nbInt_1 = new QAction(MainWindow);
        action_nbInt_1->setObjectName(QString::fromUtf8("action_nbInt_1"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 494, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuExport = new QMenu(menuFile);
        menuExport->setObjectName(QString::fromUtf8("menuExport"));
        menu_jpeg = new QMenu(menuExport);
        menu_jpeg->setObjectName(QString::fromUtf8("menu_jpeg"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuInterpolator = new QMenu(menuOptions);
        menuInterpolator->setObjectName(QString::fromUtf8("menuInterpolator"));
        menu = new QMenu(menuInterpolator);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuPicture = new QMenu(menuOptions);
        menuPicture->setObjectName(QString::fromUtf8("menuPicture"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen_Image_Data_File);
        menuFile->addSeparator();
        menuFile->addAction(menuExport->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuExport->addAction(actionSave_Binary_Data);
        menuExport->addAction(menu_jpeg->menuAction());
        menuExport->addSeparator();
        menuExport->addAction(actionClbTbl);
        menuExport->addAction(actionClbGrph);
        menuExport->addAction(actionCurSpectr);
        menuExport->addSeparator();
        menuExport->addAction(actionSpCurve);
        menu_jpeg->addAction(action_FullFrame);
        menu_jpeg->addAction(action_SelFrame);
        menu_jpeg->addAction(action_WorkFrame);
        menu_jpeg->addAction(action_WorlFrClbr);
        menuOptions->addAction(menuPicture->menuAction());
        menuOptions->addSeparator();
        menuOptions->addAction(menuInterpolator->menuAction());
        menuOptions->addAction(actionApprox);
        menuInterpolator->addAction(actionLinearInterp);
        menuInterpolator->addAction(actionDblLancszInterp);
        menuInterpolator->addAction(actionCubicInterp);
        menuInterpolator->addSeparator();
        menuInterpolator->addAction(menu->menuAction());
        menu->addAction(action_nbInt_1);
        menu->addAction(action_nbInt_3);
        menu->addAction(action_nbInt_5);
        menu->addAction(action_nbInt_10);
        menu->addAction(action_nbInt_20);
        menuPicture->addAction(actionSizeSetup);
        menuPicture->addAction(actionPicColor);
        menuHelp->addAction(actionWholeDescr);
        menuHelp->addAction(actionImrvLsDescr);
        menuHelp->addAction(actionClbrDescr);
        menuHelp->addAction(actionLnDestDescr);
        menuAbout->addAction(actionHelp);
        menuAbout->addSeparator();
        menuAbout->addAction(actionAbout);
        menuAbout->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VisSpectra", nullptr));
        actionOpen_Image_Data_File->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 RAW \321\204\320\260\320\271\320\273 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        actionSave_Binary_Data_->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\271 \321\201\320\277\320\265\320\272\321\202\321\200", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_Binary_Data_->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionSave_Binary_Data_->setStatusTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\265\320\265 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265  \320\262 4-\321\221\321\205 \320\276\321\202\320\264\320\265\320\273\321\214\320\275\321\213\321\205 \321\204\320\260\320\271\320\273\320\260\321\205 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\320\262\321\203\321\216\321\211\320\270\321\205 \321\206\320\262\320\265\321\202\320\260\320\274 \320\272\321\200\320\260\321\201\320\275\321\213\320\271 \320\267\320\265\320\273\321\221\320\275\321\213\320\271 \320\267\320\265\320\273\321\221\320\275\321\213\320\271 \321\201\320\270\320\275\320\270\320\271.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        actionSave_Binary_Data_->setWhatsThis(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\265\320\265 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265  \320\262 4-\321\221\321\205 \320\276\321\202\320\264\320\265\320\273\321\214\320\275\321\213\321\205 \321\204\320\260\320\271\320\273\320\260\321\205 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\320\262\321\203\321\216\321\211\320\270\321\205 \321\206\320\262\320\265\321\202\320\260\320\274 \320\272\321\200\320\260\321\201\320\275\321\213\320\271 \320\267\320\265\320\273\321\221\320\275\321\213\320\271 \320\267\320\265\320\273\321\221\320\275\321\213\320\271 \321\201\320\270\320\275\320\270\320\271.", nullptr));
#endif // QT_CONFIG(whatsthis)
        actionSave_Prj->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        action_1->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\320\276 \321\201\321\202\320\276\320\273\320\261\321\206\320\260\320\274", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\202\320\276\321\200", nullptr));
        actionLinearInterp->setText(QCoreApplication::translate("MainWindow", "\320\233\320\270\320\275\320\265\320\271\320\275\320\260\321\217 \320\270\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\206\320\270\321\217", nullptr));
        actionDblLancszInterp->setText(QCoreApplication::translate("MainWindow", "\320\224\320\262\320\276\320\271\320\275\320\260\321\217 \320\270\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\206\320\270\321\217 \320\233\320\260\320\275\321\210\320\276\321\206\320\260", nullptr));
        action_nbInt_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        actionApprox->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\202\320\276\321\200", nullptr));
        actionClbr->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260 \321\201\320\277\320\265\320\272\321\202\321\200\320\260", nullptr));
        actionWholeDescr->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \321\200\320\260\320\261\320\276\321\202\321\213 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271", nullptr));
        actionImrvLsDescr->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\321\217\320\274\320\273\320\265\320\275\320\270\320\265 \321\201\320\277\320\265\320\272\321\202\321\200\320\260\320\273\321\214\320\275\321\213\321\205 \320\273\320\270\320\275\320\270\320\271", nullptr));
        actionClbrDescr->setText(QCoreApplication::translate("MainWindow", " \320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260 \321\201\320\277\320\265\320\272\321\202\321\200\320\260", nullptr));
        actionLnDestDescr->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217 c\320\277\320\265\320\272\321\202\321\200\320\260\320\273\321\214\320\275\321\213\321\205 \320\273\320\270\320\275\320\270\320\271", nullptr));
        actionClbTbl->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\321\203\321\216 \320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\276\321\207\320\275\321\203\321\216 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        actionClbGrph->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\270", nullptr));
        actionCurSpectr->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\271 \321\201\320\277\320\265\320\272\321\202\321\200", nullptr));
        actionPicColor->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202\320\276\320\262\320\260\321\217 \320\272\320\276\321\200\321\200\320\265\321\206\320\270\321\217", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        actionSpCurve->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\272\320\276\320\275\321\202\321\203\321\200 \320\270\320\267\320\263\320\270\320\261\320\260 \321\201\320\277\320\265\320\272\321\202\321\200\320\260\320\273\321\214\320\275\320\276\320\271 \320\273\320\270\320\275\320\270\320\270", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213x\320\276\320\264", nullptr));
        action_nbInt_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        action_nbInt_10->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        action_nbInt_20->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        actionCubicInterp->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\261\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \320\270\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\206\320\270\321\217 (\320\274\320\276\320\264\320\270\321\204.)", nullptr));
        action_FullFrame->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\321\213\320\271 \320\272\320\260\320\264\321\200", nullptr));
        action_SelFrame->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\264\320\265\320\273\320\265\320\275\320\275\320\260\321\217 \320\276\320\261\320\273\320\260\321\201\321\202\321\214", nullptr));
        action_WorkFrame->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\207\320\260\321\217 \320\276\320\261\320\273\320\260\321\201\321\202\321\214 \321\201\320\276 \321\201\320\277\321\200\321\217\320\274\320\273\321\221\320\275\320\275\321\213\320\274\320\270 \320\273\320\270\320\275\320\270\321\217\320\274\320\270", nullptr));
        action_WorlFrClbr->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\207\320\260\321\217 \320\276\320\261\320\273\320\260\321\201\321\202\321\214 \320\277\320\276\321\201\320\273\320\265 \320\272\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\270", nullptr));
        action_6->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        action_7->setText(QString());
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        actionSizeSetup->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        actionSave_Binary_Data->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\271 \321\201\320\277\320\265\320\272\321\202\321\200 \320\262 \320\261\320\270\320\275\320\260\321\200\320\275\320\276\320\274 \320\262\320\270\320\264\320\265", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\211\320\265\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        action_nbInt_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menuExport->setTitle(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        menu_jpeg->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\265\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\201\320\277\320\265\320\272\321\202\321\200\320\260 \320\262 jpeg", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        menuInterpolator->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\320\277\320\276\320\273\321\217\321\202\320\276\321\200", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\321\200\320\276\320\274\320\265\320\266\321\203\321\202\320\276\321\207\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272", nullptr));
        menuPicture->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI__H
