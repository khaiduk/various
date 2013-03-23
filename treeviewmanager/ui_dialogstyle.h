/********************************************************************************
** Form generated from reading UI file 'dialogstyle.ui'
**
** Created: Sun 16. Sep 23:31:43 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSTYLE_H
#define UI_DIALOGSTYLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogStyle
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *BCzionka;
    QPushButton *BAktywny;
    QPushButton *BNieaktywny;
    QPushButton *BZaznaczony;
    QPushButton *BWybrany;
    QLabel *labelAkt;
    QLabel *labelNAkt;
    QLabel *labelZazn;
    QLabel *labelWyb;
    QLineEdit *labelCzcionka;
    QHBoxLayout *horizontalLayout;
    QPushButton *BZaakceptuj;
    QPushButton *BOdrzuc;

    void setupUi(QDialog *DialogStyle)
    {
        if (DialogStyle->objectName().isEmpty())
            DialogStyle->setObjectName(QString::fromUtf8("DialogStyle"));
        DialogStyle->resize(400, 300);
        gridLayout = new QGridLayout(DialogStyle);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BCzionka = new QPushButton(DialogStyle);
        BCzionka->setObjectName(QString::fromUtf8("BCzionka"));

        gridLayout_2->addWidget(BCzionka, 0, 0, 1, 1);

        BAktywny = new QPushButton(DialogStyle);
        BAktywny->setObjectName(QString::fromUtf8("BAktywny"));

        gridLayout_2->addWidget(BAktywny, 1, 0, 1, 1);

        BNieaktywny = new QPushButton(DialogStyle);
        BNieaktywny->setObjectName(QString::fromUtf8("BNieaktywny"));

        gridLayout_2->addWidget(BNieaktywny, 2, 0, 1, 1);

        BZaznaczony = new QPushButton(DialogStyle);
        BZaznaczony->setObjectName(QString::fromUtf8("BZaznaczony"));

        gridLayout_2->addWidget(BZaznaczony, 3, 0, 1, 1);

        BWybrany = new QPushButton(DialogStyle);
        BWybrany->setObjectName(QString::fromUtf8("BWybrany"));

        gridLayout_2->addWidget(BWybrany, 4, 0, 1, 1);

        labelAkt = new QLabel(DialogStyle);
        labelAkt->setObjectName(QString::fromUtf8("labelAkt"));

        gridLayout_2->addWidget(labelAkt, 1, 1, 1, 1);

        labelNAkt = new QLabel(DialogStyle);
        labelNAkt->setObjectName(QString::fromUtf8("labelNAkt"));

        gridLayout_2->addWidget(labelNAkt, 2, 1, 1, 1);

        labelZazn = new QLabel(DialogStyle);
        labelZazn->setObjectName(QString::fromUtf8("labelZazn"));

        gridLayout_2->addWidget(labelZazn, 3, 1, 1, 1);

        labelWyb = new QLabel(DialogStyle);
        labelWyb->setObjectName(QString::fromUtf8("labelWyb"));

        gridLayout_2->addWidget(labelWyb, 4, 1, 1, 1);

        labelCzcionka = new QLineEdit(DialogStyle);
        labelCzcionka->setObjectName(QString::fromUtf8("labelCzcionka"));
        labelCzcionka->setEchoMode(QLineEdit::Normal);
        labelCzcionka->setReadOnly(true);

        gridLayout_2->addWidget(labelCzcionka, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BZaakceptuj = new QPushButton(DialogStyle);
        BZaakceptuj->setObjectName(QString::fromUtf8("BZaakceptuj"));

        horizontalLayout->addWidget(BZaakceptuj);

        BOdrzuc = new QPushButton(DialogStyle);
        BOdrzuc->setObjectName(QString::fromUtf8("BOdrzuc"));

        horizontalLayout->addWidget(BOdrzuc);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DialogStyle);

        QMetaObject::connectSlotsByName(DialogStyle);
    } // setupUi

    void retranslateUi(QDialog *DialogStyle)
    {
        DialogStyle->setWindowTitle(QApplication::translate("DialogStyle", "Dialog", 0, QApplication::UnicodeUTF8));
        BCzionka->setText(QApplication::translate("DialogStyle", "Czcionka", 0, QApplication::UnicodeUTF8));
        BAktywny->setText(QApplication::translate("DialogStyle", "Wybierz kolor aktywnego elementu", 0, QApplication::UnicodeUTF8));
        BNieaktywny->setText(QApplication::translate("DialogStyle", "Wybierz kolor nieaktywnego elementu", 0, QApplication::UnicodeUTF8));
        BZaznaczony->setText(QApplication::translate("DialogStyle", "Wybierz kolor zaznaczonego elementu", 0, QApplication::UnicodeUTF8));
        BWybrany->setText(QApplication::translate("DialogStyle", "Wybierz kolor wybranego elementu", 0, QApplication::UnicodeUTF8));
        labelAkt->setText(QString());
        labelNAkt->setText(QString());
        labelZazn->setText(QString());
        labelWyb->setText(QString());
        labelCzcionka->setText(QApplication::translate("DialogStyle", "Pulpit Desktop Docs", 0, QApplication::UnicodeUTF8));
        BZaakceptuj->setText(QApplication::translate("DialogStyle", "Zaakceptuj", 0, QApplication::UnicodeUTF8));
        BOdrzuc->setText(QApplication::translate("DialogStyle", "Odrzu\304\207 zmiany", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogStyle: public Ui_DialogStyle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSTYLE_H
