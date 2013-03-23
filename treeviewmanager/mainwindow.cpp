#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1250"));

    ui->setupUi(this);
    menuUlubione = new QMenu(this);
    fsystem=new FileSystemController(this);
    dodajUlubiony(L"Dodaj");
    dodajUlubiony(L"Usuñ");
    ui->webView->hide();
    ifWwwOn=false;
    QObject::connect(ui->BOtworz,SIGNAL(clicked()),fsystem, SLOT(otworzFolder()));
    QObject::connect(ui->BKopiuj,SIGNAL(clicked()),fsystem, SLOT(kopiujPlik()));
    QObject::connect(ui->BUsun,SIGNAL(clicked()),fsystem, SLOT(kasujPlik()));
    QObject::connect(ui->BWytnij,SIGNAL(clicked()),fsystem, SLOT(wytnijPlik()));
    QObject::connect(ui->BWklej,SIGNAL(clicked()),fsystem, SLOT(wklejPlik()));
    QObject::connect(ui->BZmienNazwe,SIGNAL(clicked()),fsystem, SLOT(zmienNazwe()));
    QObject::connect(ui->BNowyFolder,SIGNAL(clicked()),fsystem, SLOT(nowyKatalog()));
    QObject::connect(ui->BOdswiez,SIGNAL(clicked()),fsystem, SLOT(odswiez()));
    QObject::connect(ui->BUstalKatalogStartowy,SIGNAL(clicked()),fsystem, SLOT(ustawKatalogStartowy()));
    QObject::connect(ui->BKolory,SIGNAL(clicked()),fsystem, SLOT(ustawKolory()));
    QObject::connect(ui->BStart,SIGNAL(clicked()),fsystem,SLOT(otworzKatalogStartowy()));
    QObject::connect(ui->BWyjscie,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->BWindows,SIGNAL(clicked()),fsystem,SLOT(toWindows()));
    QObject::connect(ui->BPrzejdz,SIGNAL(clicked()),this,SLOT(przejdzNaAdres()));
    QObject::connect(ui->BAdres,SIGNAL(returnPressed()),this,SLOT(przejdzNaAdres()));

    QObject::connect(ui->treeView,SIGNAL(directoryChanged(FileSystem::Path)), fsystem, SLOT(aktywujKatalog(FileSystem::Path)));
    QObject::connect(ui->treeView,SIGNAL(selectedElements(std::vector<FileSystem::Path>)), fsystem,SLOT(zaznaczPliki(std::vector<FileSystem::Path>)));
    QObject::connect(ui->treeView,SIGNAL(openFile(FileSystem::Path)),fsystem,SLOT(otworzZewnetrznie(FileSystem::Path)));


    QObject::connect(fsystem,SIGNAL(setStatusBarWMain(const QString)),this->statusBar(), SLOT(showMessage(const QString)));
    QObject::connect(fsystem,SIGNAL(dodanieUlubionego(std::wstring)),this,SLOT(dodajUlubiony(std::wstring)));
    QObject::connect(fsystem,SIGNAL(usuniecieUlubionego(std::wstring)),this,SLOT(usunUlubione(std::wstring)));
    QObject::connect(fsystem,SIGNAL(otwarcieKatalogu(FileSystem::Path)),ui->treeView,SLOT(setDirectory(FileSystem::Path)));
    QObject::connect(fsystem,SIGNAL(styleChanged(TreeViewStyle)),ui->treeView,SLOT(setStyle(TreeViewStyle)));
    QObject::connect(fsystem,SIGNAL(changeWWW(bool)),this,SLOT(changeWWW(bool)));
    QObject::connect(fsystem,SIGNAL(odswiezWWW()),this,SLOT(przejdzNaAdres()));


    QObject::connect(this,SIGNAL(wwwChanged(bool)),fsystem,SLOT(onWwwChange(bool)));

    QObject::connect(fsystem,SIGNAL(setAdres(QString)),ui->BAdres, SLOT(setText(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();

    fsystem->poUtworzeniuGlownegoOkna();

}

void MainWindow::dodajUlubiony(wstring s)
{
    UlubioneAction* a=new UlubioneAction(QString::fromStdWString(s), this);

    menuUlubione->addAction(a);
    if(!s.compare(L"Usuñ"))
    {
        menuUlubione->addSeparator();
    }
    ui->BUlubione->setMenu (menuUlubione );
    QObject::connect(a,SIGNAL(sygnalUlubione(std::wstring)),fsystem, SLOT(ulubione(std::wstring)));
}

void MainWindow::usunUlubione(wstring szukany)
{
    foreach (QAction* a, menuUlubione->actions())
    {
        if(dynamic_cast<UlubioneAction*>(a) && dynamic_cast<UlubioneAction*>(a)->getVal()==szukany)
        {
            menuUlubione->removeAction(a);
        }
    }
}

void MainWindow::przejdzNaAdres()
{
    QString adres=ui->BAdres->text();
    if(adres.startsWith("http"))
    {
        changeWWW(true);
        ui->webView->setUrl(adres);
        ui->statusBar->showMessage("Tryb www");

    }
    else if(adres.startsWith("www"))
    {
        adres = "http://"+adres;
        ui->BAdres->setText(adres);
        changeWWW(true);
        ui->webView->setUrl(adres);
        ui->statusBar->showMessage("Tryb www");

    }
    else
    {
        if( adres[0].isLetter() && (adres[1]==':') )
        {
            adres[0]=adres[0].toUpper();
        }
/*        if( adres[0].isLetter()&& adres[1].isLetter() && (adres[2]==':') )
        {
            adres[0]=adres[0].toUpper();
            adres[1]=adres[1].toUpper();
        }*/
        if( adres.endsWith("/") || adres.endsWith("\\") )
        {
            adres.remove(adres.size()-1,1);
        }
        fsystem->otworzKatalog(adres.toStdWString());
    }

}

void MainWindow::changeWWW(bool wlacz)
{
    if(wlacz && !ifWwwOn)
    {
        ui->webView->show();
        ui->treeView->hide();

        emit wwwChanged(ifWwwOn=true);
    }
    else if(!wlacz && ifWwwOn)
    {
        ui->webView->hide();
        ui->treeView->show();


        emit wwwChanged(ifWwwOn=false);
    }
}


