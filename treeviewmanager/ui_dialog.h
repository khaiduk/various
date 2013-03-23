/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue 19. Jun 14:50:44 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

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

class Ui_Dialog
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

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        BCzionka = new QPushButton(Dialog);
        BCzionka->setObjectName(QString::fromUtf8("BCzionka"));

        gridLayout_2->addWidget(BCzionka, 0, 0, 1, 1);

        BAktywny = new QPushButton(Dialog);
        BAktywny->setObjectName(QString::fromUtf8("BAktywny"));

        gridLayout_2->addWidget(BAktywny, 1, 0, 1, 1);

        BNieaktywny = new QPushButton(Dialog);
        BNieaktywny->setObjectName(QString::fromUtf8("BNieaktywny"));

        gridLayout_2->addWidget(BNieaktywny, 2, 0, 1, 1);

        BZaznaczony = new QPushButton(Dialog);
        BZaznaczony->setObjectName(QString::fromUtf8("BZaznaczony"));

        gridLayout_2->addWidget(BZaznaczony, 3, 0, 1, 1);

        BWybrany = new QPushButton(Dialog);
        BWybrany->setObjectName(QString::fromUtf8("BWybrany"));

        gridLayout_2->addWidget(BWybrany, 4, 0, 1, 1);

        labelAkt = new QLabel(Dialog);
        labelAkt->setObjectName(QString::fromUtf8("labelAkt"));

        gridLayout_2->addWidget(labelAkt, 1, 1, 1, 1);

        labelNAkt = new QLabel(Dialog);
        labelNAkt->setObjectName(QString::fromUtf8("labelNAkt"));

        gridLayout_2->addWidget(labelNAkt, 2, 1, 1, 1);

        labelZazn = new QLabel(Dialog);
        labelZazn->setObjectName(QString::fromUtf8("labelZazn"));

        gridLayout_2->addWidget(labelZazn, 3, 1, 1, 1);

        labelWyb = new QLabel(Dialog);
        labelWyb->setObjectName(QString::fromUtf8("labelWyb"));

        gridLayout_2->addWidget(labelWyb, 4, 1, 1, 1);

        labelCzcionka = new QLineEdit(Dialog);
        labelCzcionka->setObjectName(QString::fromUtf8("labelCzcionka"));
        labelCzcionka->setEchoMode(QLineEdit::Normal);
        labelCzcionka->setReadOnly(true);

        gridLayout_2->addWidget(labelCzcionka, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BZaakceptuj = new QPushButton(Dialog);
        BZaakceptuj->setObjectName(QString::fromUtf8("BZaakceptuj"));

        horizontalLayout->addWidget(BZaakceptuj);

        BOdrzuc = new QPushButton(Dialog);
        BOdrzuc->setObjectName(QString::fromUtf8("BOdrzuc"));

        horizontalLayout->addWidget(BOdrzuc);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        BCzionka->setText(QApplication::translate("Dialog", "Czcionka", 0, QApplication::UnicodeUTF8));
        BAktywny->setText(QApplication::translate("Dialog", "Wybierz kolor aktywnego elementu", 0, QApplication::UnicodeUTF8));
        BNieaktywny->setText(QApplication::translate("Dialog", "Wybierz kolor nieaktywnego elementu", 0, QApplication::UnicodeUTF8));
        BZaznaczony->setText(QApplication::translate("Dialog", "Wybierz kolor zaznaczonego elementu", 0, QApplication::UnicodeUTF8));
        BWybrany->setText(QApplication::translate("Dialog", "Wybierz kolor wybranego elementu", 0, QApplication::UnicodeUTF8));
        labelAkt->setText(QString());
        labelNAkt->setText(QString());
        labelZazn->setText(QString());
        labelWyb->setText(QString());
        labelCzcionka->setText(QApplication::translate("Dialog", "Pulpit Desktop Docs", 0, QApplication::UnicodeUTF8));
        BZaakceptuj->setText(QApplication::translate("Dialog", "Zaakceptuj", 0, QApplication::UnicodeUTF8));
        BOdrzuc->setText(QApplication::translate("Dialog", "Odrzu\304\207 zmiany", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
