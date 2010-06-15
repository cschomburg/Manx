/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 15 00:31:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_File;
    QAction *action_Quit;
    QAction *action_Export_to_Image;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnOpen;
    QPushButton *btnExport;
    QProgressBar *progressExport;
    QCheckBox *checkDetails;
    QLabel *label_3;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(725, 493);
        action_Open_File = new QAction(MainWindow);
        action_Open_File->setObjectName(QString::fromUtf8("action_Open_File"));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Export_to_Image = new QAction(MainWindow);
        action_Export_to_Image->setObjectName(QString::fromUtf8("action_Export_to_Image"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 10, 38, 48));
        QFont font;
        font.setPointSize(30);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        label->setFont(font);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 10, 38, 48));
        label_2->setFont(font);
        btnOpen = new QPushButton(tab);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(10, 60, 191, 51));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnOpen->sizePolicy().hasHeightForWidth());
        btnOpen->setSizePolicy(sizePolicy);
        btnOpen->setMinimumSize(QSize(0, 0));
        btnExport = new QPushButton(tab);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setEnabled(false);
        btnExport->setGeometry(QRect(260, 60, 191, 51));
        sizePolicy.setHeightForWidth(btnExport->sizePolicy().hasHeightForWidth());
        btnExport->setSizePolicy(sizePolicy);
        btnExport->setMinimumSize(QSize(0, 0));
        progressExport = new QProgressBar(tab);
        progressExport->setObjectName(QString::fromUtf8("progressExport"));
        progressExport->setEnabled(true);
        progressExport->setGeometry(QRect(500, 80, 191, 21));
        progressExport->setMaximum(100);
        progressExport->setValue(0);
        checkDetails = new QCheckBox(tab);
        checkDetails->setObjectName(QString::fromUtf8("checkDetails"));
        checkDetails->setGeometry(QRect(290, 130, 131, 21));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(580, 10, 38, 48));
        label_3->setFont(font);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 725, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Open_File);
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Manx", 0, QApplication::UnicodeUTF8));
        action_Open_File->setText(QApplication::translate("MainWindow", "&Open File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Open_File->setToolTip(QApplication::translate("MainWindow", "Open a new Minecraft File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Open_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Export_to_Image->setText(QApplication::translate("MainWindow", "&Export to Image", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "1.", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "2.", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("MainWindow", "Open Minecraft Level", 0, QApplication::UnicodeUTF8));
        btnExport->setText(QApplication::translate("MainWindow", "Export Map to Image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkDetails->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">With this option, the map will be rendered with <span style=\" font-weight:600;\">textures</span> instead of pixels.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The map will be <span style=\" font-weight:600;\">16*16 times larger</span> and much more <span style=\" font-weight:600;\">slowly</span> to render!</p></body></html"
                        ">", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkDetails->setText(QApplication::translate("MainWindow", "Detailed Textures", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "3.", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Exporter", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Map Viewer", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
