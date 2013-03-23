/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 16. Sep 23:31:43 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>
#include "treeview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *glownyWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *BAdres;
    QPushButton *BPrzejdz;
    QTabWidget *tabWidget;
    QWidget *Menu;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *BOdswiez;
    QPushButton *BUlubione;
    QPushButton *BStart;
    QFrame *line_3;
    QPushButton *BOtworz;
    QPushButton *BKopiuj;
    QPushButton *BWytnij;
    QPushButton *BWklej;
    QPushButton *BUsun;
    QFrame *line_4;
    QPushButton *BZmienNazwe;
    QPushButton *BNowyFolder;
    QFrame *line_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *BWindows;
    QPushButton *BWyjscie;
    QWidget *Ustawienia;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BUstalKatalogStartowy;
    QPushButton *BKolory;
    QFrame *line;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_2;
    QWebView *webView;
    TreeView *treeView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        glownyWidget = new QWidget(MainWindow);
        glownyWidget->setObjectName(QString::fromUtf8("glownyWidget"));
        gridLayout = new QGridLayout(glownyWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMaximumSize);
        BAdres = new QLineEdit(glownyWidget);
        BAdres->setObjectName(QString::fromUtf8("BAdres"));
        BAdres->setDragEnabled(false);

        horizontalLayout_6->addWidget(BAdres);

        BPrzejdz = new QPushButton(glownyWidget);
        BPrzejdz->setObjectName(QString::fromUtf8("BPrzejdz"));

        horizontalLayout_6->addWidget(BPrzejdz);


        horizontalLayout_5->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_5);

        tabWidget = new QTabWidget(glownyWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 80));
        tabWidget->setBaseSize(QSize(0, 0));
        Menu = new QWidget();
        Menu->setObjectName(QString::fromUtf8("Menu"));
        horizontalLayout_2 = new QHBoxLayout(Menu);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BOdswiez = new QPushButton(Menu);
        BOdswiez->setObjectName(QString::fromUtf8("BOdswiez"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/menu/ikony/Refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        BOdswiez->setIcon(icon);
        BOdswiez->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BOdswiez);

        BUlubione = new QPushButton(Menu);
        BUlubione->setObjectName(QString::fromUtf8("BUlubione"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/menu/ikony/Favourites2.png"), QSize(), QIcon::Normal, QIcon::Off);
        BUlubione->setIcon(icon1);
        BUlubione->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BUlubione);

        BStart = new QPushButton(Menu);
        BStart->setObjectName(QString::fromUtf8("BStart"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/menu/ikony/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        BStart->setIcon(icon2);
        BStart->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BStart);

        line_3 = new QFrame(Menu);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        BOtworz = new QPushButton(Menu);
        BOtworz->setObjectName(QString::fromUtf8("BOtworz"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/menu/ikony/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        BOtworz->setIcon(icon3);
        BOtworz->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BOtworz);

        BKopiuj = new QPushButton(Menu);
        BKopiuj->setObjectName(QString::fromUtf8("BKopiuj"));
        BKopiuj->setLayoutDirection(Qt::LeftToRight);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/menu/ikony/Copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        BKopiuj->setIcon(icon4);
        BKopiuj->setIconSize(QSize(22, 22));
        BKopiuj->setCheckable(false);

        horizontalLayout->addWidget(BKopiuj);

        BWytnij = new QPushButton(Menu);
        BWytnij->setObjectName(QString::fromUtf8("BWytnij"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/menu/ikony/Cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        BWytnij->setIcon(icon5);
        BWytnij->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BWytnij);

        BWklej = new QPushButton(Menu);
        BWklej->setObjectName(QString::fromUtf8("BWklej"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/menu/ikony/Paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        BWklej->setIcon(icon6);
        BWklej->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BWklej);

        BUsun = new QPushButton(Menu);
        BUsun->setObjectName(QString::fromUtf8("BUsun"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/menu/ikony/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        BUsun->setIcon(icon7);
        BUsun->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BUsun);

        line_4 = new QFrame(Menu);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_4);

        BZmienNazwe = new QPushButton(Menu);
        BZmienNazwe->setObjectName(QString::fromUtf8("BZmienNazwe"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/menu/ikony/Rename.png"), QSize(), QIcon::Normal, QIcon::Off);
        BZmienNazwe->setIcon(icon8);
        BZmienNazwe->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BZmienNazwe);

        BNowyFolder = new QPushButton(Menu);
        BNowyFolder->setObjectName(QString::fromUtf8("BNowyFolder"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/menu/ikony/NewFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        BNowyFolder->setIcon(icon9);
        BNowyFolder->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BNowyFolder);

        line_5 = new QFrame(Menu);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BWindows = new QPushButton(Menu);
        BWindows->setObjectName(QString::fromUtf8("BWindows"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/menu/ikony/Windows.png"), QSize(), QIcon::Normal, QIcon::Off);
        BWindows->setIcon(icon10);
        BWindows->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BWindows);

        BWyjscie = new QPushButton(Menu);
        BWyjscie->setObjectName(QString::fromUtf8("BWyjscie"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/menu/ikony/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        BWyjscie->setIcon(icon11);
        BWyjscie->setIconSize(QSize(22, 22));

        horizontalLayout->addWidget(BWyjscie);


        horizontalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(Menu, QString());
        Ustawienia = new QWidget();
        Ustawienia->setObjectName(QString::fromUtf8("Ustawienia"));
        horizontalLayout_4 = new QHBoxLayout(Ustawienia);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BUstalKatalogStartowy = new QPushButton(Ustawienia);
        BUstalKatalogStartowy->setObjectName(QString::fromUtf8("BUstalKatalogStartowy"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/menu/ikony/SetStartFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        BUstalKatalogStartowy->setIcon(icon12);
        BUstalKatalogStartowy->setIconSize(QSize(22, 22));

        horizontalLayout_3->addWidget(BUstalKatalogStartowy);

        BKolory = new QPushButton(Ustawienia);
        BKolory->setObjectName(QString::fromUtf8("BKolory"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/menu/ikony/Font.png"), QSize(), QIcon::Normal, QIcon::Off);
        BKolory->setIcon(icon13);
        BKolory->setIconSize(QSize(22, 22));

        horizontalLayout_3->addWidget(BKolory);

        line = new QFrame(Ustawienia);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        line_2 = new QFrame(Ustawienia);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        tabWidget->addTab(Ustawienia, QString());

        verticalLayout->addWidget(tabWidget);

        webView = new QWebView(glownyWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        verticalLayout->addWidget(webView);

        treeView = new TreeView(glownyWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(glownyWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget, BWytnij);
        QWidget::setTabOrder(BWytnij, BWklej);
        QWidget::setTabOrder(BWklej, BUstalKatalogStartowy);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TreeChartManager", 0, QApplication::UnicodeUTF8));
        BPrzejdz->setText(QApplication::translate("MainWindow", "Przejd\305\272", 0, QApplication::UnicodeUTF8));
        BOdswiez->setText(QApplication::translate("MainWindow", "Od\305\233wie\305\274", 0, QApplication::UnicodeUTF8));
        BOdswiez->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        BUlubione->setText(QApplication::translate("MainWindow", "Ulubionee", 0, QApplication::UnicodeUTF8));
        BStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        BOtworz->setText(QApplication::translate("MainWindow", "Otw\303\263rz", 0, QApplication::UnicodeUTF8));
        BOtworz->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        BKopiuj->setText(QApplication::translate("MainWindow", "Kopiuj", 0, QApplication::UnicodeUTF8));
        BKopiuj->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        BWytnij->setText(QApplication::translate("MainWindow", "Wytnij", 0, QApplication::UnicodeUTF8));
        BWytnij->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        BWklej->setText(QApplication::translate("MainWindow", "Wklej", 0, QApplication::UnicodeUTF8));
        BWklej->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        BUsun->setText(QApplication::translate("MainWindow", "Usu\305\204", 0, QApplication::UnicodeUTF8));
        BUsun->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));
        BZmienNazwe->setText(QApplication::translate("MainWindow", "Zmie\305\204 nazw\304\231", 0, QApplication::UnicodeUTF8));
        BNowyFolder->setText(QApplication::translate("MainWindow", "Nowy Folder", 0, QApplication::UnicodeUTF8));
        BNowyFolder->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        BWindows->setText(QApplication::translate("MainWindow", "Windows", 0, QApplication::UnicodeUTF8));
        BWyjscie->setText(QApplication::translate("MainWindow", "Wyj\305\233cie", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Menu), QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        BUstalKatalogStartowy->setText(QApplication::translate("MainWindow", "Ustaw Katalog Startowy", 0, QApplication::UnicodeUTF8));
        BKolory->setText(QApplication::translate("MainWindow", "Ustaw wygl\304\205d", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Ustawienia), QApplication::translate("MainWindow", "Ustawienia", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
