#include "filesystemcontroller.h"

/////////Konstruktor&&Destruktor//////////////////////////////////////////////////
FileSystemController::FileSystemController(QObject *parent) :
    QObject(parent)
{
    _stylWidoku.aktywny=QColor("#ff1e29");
    _stylWidoku.nieaktywny=QColor("#aaffff");
    _stylWidoku.zaznaczony=QColor("#00aa00");
    _stylWidoku.wybrany=QColor("#00ffff");
    wczytajUstawienia();
    QObject::connect(this,SIGNAL(zakomunikuj(QString,QString)),this,SLOT(komunikat(QString,QString)));


}
FileSystemController::~FileSystemController()
{
    zapiszUstawienia();
}
//////////////////////////////////////////////////////////////////////////////////


///////SLOTY//////////////////////////////////////////////////////////////////////

void FileSystemController::otworzFolder()
{
    std::wstring filename = QFileDialog::getExistingDirectory().toStdWString();
    if(filename.size()>0)
    {
        otworzKatalog(filename);
    }
}
///////////////////////////////////////////////////////////////////////////////////

void FileSystemController::kopiujPlik()
{
    _skopiowanePliki=_zaznaczonePliki;
    _kopiowanie=KOPIA;
}

//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::kasujPlik()
{
    unsigned int wynik= QMessageBox::question(0,"Ostrzezenie", "Czy na pewno TRWALE usun¹æ?",QMessageBox::Yes|QMessageBox::No);
    //std::wstring ws=sciezkaPliku(_zaznaczonePliki.front());
    if(wynik == QMessageBox::Yes)
    {
        TabIdPlikow biezace_pliki(_zaznaczonePliki.begin(),_zaznaczonePliki.end());
        QtConcurrent::run(this, &FileSystemController::watekKasowania,biezace_pliki);
    }
}

//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::wklejPlik()
{
    if( _kopiowanie == KOPIA )
    {
        TabIdPlikow biezace_pliki(_skopiowanePliki.begin(),_skopiowanePliki.end());
        IdPliku biezacy_katalog=_aktywnyKatalog;
        QtConcurrent::run(this, &FileSystemController::watekKopiowania, biezace_pliki, biezacy_katalog);

    }
    else if(_kopiowanie==WYCIECIE)
    {
        TabIdPlikow biezace_pliki(_skopiowanePliki.begin(),_skopiowanePliki.end());
        IdPliku biezacy_katalog=_aktywnyKatalog;
        QtConcurrent::run(this, &FileSystemController::watekPrzenoszenia, biezace_pliki, biezacy_katalog);
    }
}

//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::wytnijPlik()
{
    _skopiowanePliki=_zaznaczonePliki;
    _kopiowanie=WYCIECIE;
}

//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::zaznaczPliki(std::vector<FileSystem::Path> nazwy)
{
    _zaznaczonePliki=nazwy;
    QString statusInfo=QString::fromStdWString(L"Zaznaczone: ");
    if(_zaznaczonePliki.size())
    {

        foreach(IdPliku s, _zaznaczonePliki)
        {
            statusInfo+=QString::fromStdWString(nazwaPliku(s))+"; ";
        }
        rmFromStatus(statusInfo);
        addToStatus(statusInfo);
    }
    else
    {
        rmFromStatus(statusInfo);
    }
}

/////////////////////////////////////////////////////////////////////////
void FileSystemController::zmienNazwe()
{
    bool ok;
    std::wstring text;
    if(_zaznaczonePliki.size() <= 0)
    {
    }
    else  if(  ( text= QInputDialog::getText(
                     NULL,
                     tr("Nowa nazwa"),
                     tr("Podaj now¹ nazwê:"),
                     QLineEdit::Normal,
                     "",
                     &ok).toStdWString()).size() && ok )
    {
        if(FileSystem::Globals::exists(sciezkaPliku(_zaznaczonePliki.front())+L"\\"+text))
        {
            QMessageBox::information(0,"Plik o podanej nazwie istnieje","Plik o podanej nazwie istnieje",QMessageBox::Ok);
        }
        else if(_zaznaczonePliki.size() == 1)
        {
            FileSystem::Globals::rename(_zaznaczonePliki.front(),sciezkaPliku(_zaznaczonePliki.front())+L"\\"+text);
        }
    }
    if(_zaznaczonePliki.size()) otworzKatalog( sciezkaPliku(_zaznaczonePliki.front()));
}


/////////////////////////////////////////////////////////////////////////
void FileSystemController::odswiez()
{
    if(ifWwwOn=true)
    {
        emit odswiezWWW();
    }
    else otworzKatalog(_aktywnyKatalog);
}
/////////////////////////////////////////////////////////////////////////
void FileSystemController::nowyKatalog()
{
    bool ok;
    std::wstring text = QInputDialog::getText(
                NULL,
                tr("Nowa nazwa"),
                tr("Podaj now¹ nazwê:"),
                QLineEdit::Normal,
                "",
                &ok).toStdWString();
    if( ok && text.size() )
    {
        int i=1;
        std::wstringstream ss;
        ss<<text;
        while(FileSystem::Globals::exists(_aktywnyKatalog+L"\\"+ss.str()))
        {
            ss.str(L"");
            ss<<text<<"("<<i++<<")";
        }
        FileSystem::Globals::createDir(_aktywnyKatalog+L"\\"+ss.str());
    }
    odswiez();
}
//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::aktywujKatalog(FileSystem::Path nazwa)
{
    _aktywnyKatalog=nazwa;
    emit setAdres(QString::fromStdString(nazwa));
}




//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::ustawKatalogStartowy()
{
    std::wstring filename = QFileDialog::getExistingDirectory().toStdWString();;
    if(filename.size())
        _startowyKatalog=filename;
}



//////////////////////////////////////////////////////////////////////////////////
void FileSystemController::poUtworzeniuGlownegoOkna()
{   
    wczytajUlubione();

    otworzKatalog(_startowyKatalog);
}


void FileSystemController::ulubione(std::wstring k)
{

    if(!k.compare(L"Dodaj"))
    {
        std::wstring filename = QFileDialog::getExistingDirectory().toStdWString();;
        if(filename.size())
        {
            dodajUlubiony(filename);
        }
    }
    else if(!k.compare(L"Usuñ"))
    {
        bool ok;
        QStringList lista;

        for(std::map<std::wstring,IdPliku>::iterator it=_ulubione.begin(); it!=_ulubione.end();it++)
        {
            QString s=QString::fromStdWString((*it).first);
            lista.append(s);
        }

        std::wstring text = QInputDialog::getItem(
                    NULL,
                    tr("Usuñ ulubiony"),
                    tr("Wybierz do usuniêcia z ulubionych:"),
                    lista,
                    0,
                    false,
                    &ok).toStdWString();
        if( ok && text.size() )
        {
            _ulubione.erase(text);
            emit usuniecieUlubionego(text);
        }
    }
    else if(k.size())
    {
        otworzKatalog(_ulubione[k]);
    }
}



void FileSystemController::dodajUlubiony(wstring filename)
{
    std::wstring name=nazwaPliku(filename);
    emit dodanieUlubionego(name);
    _ulubione.insert(make_pair(name, filename));
}


FileSystemController::IdPliku FileSystemController::sciezkaPliku(std::wstring plik)
{
    if(plik.size())
    {
        int last=plik.find_last_of('\\');
        if(last<=0)
        {
            last=plik.find_last_of('/');
        }
        std::wstring name(plik.begin(),plik.begin()+last);
        return name;
    }
    else
    {
        return _aktywnyKatalog;
    }
}

std::wstring FileSystemController::nazwaPliku(std::wstring filename)
{
    QString qs=QString::fromStdWString(filename);
    QRegExp rx("(\\w:)\\\\");
    if(rx.exactMatch(qs))
    {
        return rx.cap(1).toStdWString();
    }
    else{
        int last=filename.find_last_of('\\')+1;
        if(last<=1)
        {
            last=filename.find_last_of('/')+1;
        }
        std::wstring name(filename.begin()+last,filename.end());
        return name;
    }
}

//////funkcje prywatne////////////////////////////////////////////////////////////

void FileSystemController::wczytajUstawienia()
{
    _startowyKatalog=L"";
    QDomDocument doc( "Settings" );
    QFile file( "settings.xml" );
    if( file.open(QIODevice::ReadOnly ) )
    {
        doc.setContent( &file );
        file.close();
        if(doc.elementsByTagName("_startowykatalog").size()>0)
            _startowyKatalog=doc.elementsByTagName("_startowykatalog").at(0).firstChild().nodeValue().toStdWString();
    }

    if(_startowyKatalog==L"")
    {
        std::wstring pPath(QString(getenv("userprofile")).toStdWString());
        if (pPath.size()>0)
        {
            pPath+=L"\\Desktop";
            _startowyKatalog=pPath;
        }
    }

    if(_startowyKatalog==L"")
    {
        ustawKatalogStartowy();
    }
}
//////////////////////////////////////////////////////////
void FileSystemController::wczytajUlubione()
{
    QDomDocument doc( "Settings" );
    QFile file( "settings.xml" );
    if( file.open(QIODevice::ReadOnly ) )
    {
        doc.setContent( &file );
        file.close();
        QDomNodeList lu=doc.elementsByTagName("ulubiony");
        for(unsigned int i=0;i<lu.length();i++)
        {
            dodajUlubiony(lu.at(i).firstChild().nodeValue().toStdWString());
        }

        _stylWidoku=TreeViewStyle::fromString(doc.elementsByTagName("_stylwidoku").at(0).firstChild().nodeValue().toStdWString())  ;
    }
    emit styleChanged(_stylWidoku);
}

///////////////////////////////////////////////////////////////////////////////
void FileSystemController::ustawKolory()
{
    DialogStyle* okienko=new DialogStyle(_stylWidoku, static_cast<QWidget*>(this->parent()));
    QObject::connect(okienko,SIGNAL(styleChanged(TreeViewStyle)),this, SLOT(wyslijStyl(TreeViewStyle)));
    okienko->show();

}

///////////////////////////////////////////////////////////////////////////////
void FileSystemController::wyslijStyl(TreeViewStyle s)
{
    _stylWidoku=s;
    emit styleChanged(_stylWidoku);
}

void FileSystemController::otworzKatalogStartowy()
{

    otworzKatalog(_startowyKatalog);
}

void FileSystemController::onWwwChange(bool b)
{
    ifWwwOn=b;
}

void FileSystemController::changeStatus()
{
    QString ms;
    foreach(QString s, currentStatus)
    {
        ms+=s+" ";
    }

    emit setStatusBarWMain(ms);
}
void FileSystemController::addToStatus(QString s)
{
    currentStatus.push_back(s);
    changeStatus();
}
void FileSystemController::rmFromStatus(QString s)
{
    if(s.startsWith("Zaznaczone"))
    {
        for (QList<QString>::iterator i = currentStatus.begin(); i != currentStatus.end(); ++i)
        {
            if(i->startsWith("Zaznaczone"))
            {
                currentStatus.erase(i);
            }
        }
    }
    else
    {
         currentStatus.removeAll(s);
    }
    changeStatus();
}

void FileSystemController::toWindows()
{
    otworzZewnetrznie(_aktywnyKatalog);
}


///////////////////////////////////////////////////////////////////////////////
void FileSystemController::otworzKatalog(wstring kat)
{
    if(ifWwwOn)
        changeWWW(false);

    aktywujKatalog(kat);
    emit otwarcieKatalogu(kat);
}

void FileSystemController::otworzZewnetrznie(FileSystem::Path p)
{
    {

        QString tmp=QDir::currentPath();
        QUrl qu=QUrl("file:///"+QString::fromStdString(p), QUrl::TolerantMode);
        QDir::setCurrent(QString::fromStdString(FileSystem::File(p).parent()));
        QDesktopServices::openUrl(qu);
        QDir::setCurrent(tmp);
    }
}

void FileSystemController::komunikat(QString title, QString opis)
{
    QMessageBox::information((QWidget*)this->parent(),title, opis);
    odswiez();
}

void FileSystemController::watekKopiowania(TabIdPlikow biezace_pliki, IdPliku biezacy_katalog)
{
    for(TabIdPlikow::iterator it=biezace_pliki.begin(); it!=biezace_pliki.end(); it++)
    {  
        FileSystem::Path p=static_cast<std::wstring>(biezacy_katalog)+L"/"+nazwaPliku(*it);
        addToStatus("Kopiowanie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
        FileSystem::Globals::copy(*it, p);
        rmFromStatus("Kopiowanie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
    }

    emit zakomunikuj(QString("Kopiowanie zakoñczone"),QString("Kopiowanie zosta³o zakoñczone"));
}

void FileSystemController::watekPrzenoszenia(TabIdPlikow biezace_pliki, IdPliku biezacy_katalog)
{
    for(TabIdPlikow::iterator it=biezace_pliki.begin(); it!=biezace_pliki.end(); it++)
    {
        FileSystem::Path p=static_cast<std::wstring>(biezacy_katalog)+L"/"+nazwaPliku(*it);
        addToStatus("Przenoszenie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
        FileSystem::Globals::move(*it, p);
        rmFromStatus("Przenoszenie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
    }
    emit zakomunikuj(QString("Przenoszenie zakoñczone"),QString("Przenoszenie zosta³o zakoñczone"));
}

void FileSystemController::watekKasowania(TabIdPlikow biezace_pliki)
{
    for(TabIdPlikow::iterator it=biezace_pliki.begin(); it!=biezace_pliki.end(); it++)
    {
        addToStatus("Kasowanie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
        FileSystem::Globals::remove(*it);
        rmFromStatus("Kasowanie pliku: "+QString::fromStdWString(nazwaPliku(*it)));
    }
    emit zakomunikuj(QString("Kasowanie zakoñczone"),QString("Kasowanie zosta³o zakoñczone"));
}
///////////////////////////////////////////////////////////////////////////////
void FileSystemController::zapiszUstawienia()
{
    QDomDocument doc("Settings");
    QDomElement root=doc.createElement("settings");
    doc.appendChild(root);
    QDomElement ustawienia=doc.createElement("ustawienia");
    root.appendChild(ustawienia);
    QDomElement katStartowy=doc.createElement("_startowykatalog");
    ustawienia.appendChild(katStartowy);
    katStartowy.appendChild(doc.createTextNode(QString::fromStdWString(_startowyKatalog)));
    QDomElement stylWidoku=doc.createElement("_stylwidoku");
    ustawienia.appendChild(stylWidoku);
    stylWidoku.appendChild(doc.createTextNode(QString::fromStdWString(_stylWidoku.toString())));

    QDomElement ulubione=doc.createElement("ulubione");
    root.appendChild(ulubione);
    for(std::map<std::wstring,std::wstring>::iterator it=_ulubione.begin();it!=_ulubione.end();++it)
    {
        QDomElement ulubiony=doc.createElement("ulubiony");
        ulubione.appendChild(ulubiony);
        ulubiony.appendChild(doc.createTextNode(QString::fromStdWString(it->second)));
    }


    QFile file("settings.xml");
    if( file.open(QIODevice::WriteOnly  ) )
    {
        QTextStream ts( &file );
        ts << doc.toString();
        file.close();
    }

}
//////////////////////////////////////////////////////////////////////////////////
