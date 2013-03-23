#include "dialogstyle.h"
#include "ui_dialogstyle.h"

DialogStyle::DialogStyle(const TreeViewStyle& s,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStyle),
    styl(s),
    orygStyl(s)
{
    ui->setupUi(this);
    QObject::connect(ui->BCzionka, SIGNAL(clicked()),this, SLOT(setCzcionka()));
    QObject::connect(ui->BAktywny, SIGNAL(clicked()),this, SLOT(setAktywny()));
    QObject::connect(ui->BNieaktywny, SIGNAL(clicked()),this, SLOT(setNieaktywny()));
    QObject::connect(ui->BWybrany, SIGNAL(clicked()),this, SLOT(setWybrany()));
    QObject::connect(ui->BZaznaczony, SIGNAL(clicked()),this, SLOT(setZaznaczony()));
    QObject::connect(ui->BZaakceptuj, SIGNAL(clicked()),this, SLOT(zaakceptuj()));
    QObject::connect(ui->BOdrzuc, SIGNAL(clicked()),this, SLOT(odrzuc()));


    QPixmap a(180,18);

    a.fill(styl.nieaktywny);
    ui->labelNAkt->setPixmap(a);
    a.fill(styl.aktywny);
    ui->labelAkt->setPixmap(a);
    a.fill(styl.wybrany);
    ui->labelWyb->setPixmap(a);
    a.fill(styl.zaznaczony);
    ui->labelZazn->setPixmap(a);
    ui->labelCzcionka->setFont(styl.font);
}

DialogStyle::~DialogStyle()
{
    delete ui;
}

void DialogStyle::setCzcionka()
{
    bool ok=false;
    QFont tmp=QFontDialog::getFont(&ok);
    if(ok)
    {
        styl.font=tmp;
    }
    ui->labelCzcionka->setFont(styl.font);
}

void DialogStyle::setNieaktywny()
{
    styl.nieaktywny=QColorDialog::getColor();
    QPixmap a(180,18);
    a.fill(styl.nieaktywny);
    ui->labelNAkt->setPixmap(a);
}


void DialogStyle::setAktywny()
{
    styl.aktywny=QColorDialog::getColor();
    QPixmap a(180,18);
    a.fill(styl.aktywny);
    ui->labelAkt->setPixmap(a);
}

void DialogStyle::setWybrany()
{
    styl.wybrany=QColorDialog::getColor();
    QPixmap a(180,18);
    a.fill(styl.wybrany);
    ui->labelWyb->setPixmap(a);
}

void DialogStyle::setZaznaczony()
{
    styl.zaznaczony=QColorDialog::getColor();
    QPixmap a(180,18);
    a.fill(styl.zaznaczony);
    ui->labelZazn->setPixmap(a);
}

void DialogStyle::zaakceptuj()
{
    emit styleChanged(styl);
    close();
}

void DialogStyle::odrzuc()
{
    close();
}
