/**
  *@author S�awomir Gefert
  *@date 2012-06-13
  */
#ifndef FILESYSTEMCONTROLLER_H
#define FILESYSTEMCONTROLLER_H


#include <vector>
#include <string>
#include <map>

#include <QObject>
#include <QInputDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QtConcurrentRun>
#include <QRegExp>
#include <QtXml>

#include "FileSystem/FileSystem.h"
#include "dialogstyle.h"
#include "treeviewstyle.h"




/**
  @class FileSystemController
  @brief G��wna klasa steruj�ca.

  Odpowiada za wybieranie odpowiednich funkcji z biblioteki FileSystem.
  */
class FileSystemController : public QObject
{
    Q_OBJECT
    typedef std::wstring IdPliku;
    typedef std::vector<FileSystem::Path> TabIdPlikow;
    enum KOPIOWANIE{
        KOPIA, WYCIECIE
    };
public:
    /**
      @brief Konstruktor klasy. Dodatkowo wczytuje ustawienia z pliku.
      @param rodzic tego obiektu
      */
    explicit FileSystemController(QObject *parent = 0);
    /**
      @brief Destruktor klasy. Dodatkowo zapisuje ustawienia do pliku.
      */
    ~FileSystemController();





signals:

    /**
      @brief Sygna� do g��wnego okna celem zmiany napisu.
      @param s nowy napis
      */
    void setStatusBarWMain(const QString s);


    /**
      @brief Sygna� do g��wnego okna celem dodania ulubionego.
      @param s nowy ulubiony
      */
    void dodanieUlubionego(std::wstring s);

    /**
      @brief Sygna� do g��wnego okna celem usuni�cia ulubionego.
      @param s usuwany ulubiony
      */
    void  usuniecieUlubionego(std::wstring);

    /**
      @brief sygnal do widoku nakazujacy przeniesienie sie do danego katalogu
      @param sciezka do katalogu
      */
    void otwarcieKatalogu(FileSystem::Path);

    /**
      @brief sygnal do slotu wyswietlajacego komunikat
      @param tytul komunikatu
      @param tresc komunikatu
      */
    void zakomunikuj(QString,QString);

    /**
      @brief sygnal do widoku o zmiane stylu
      @param nowy styl
      */
    void styleChanged(TreeViewStyle);

    /**
      @brief sygnal do widoku o zmiane wyswietlania (wlaczenie managera plikow lub przegladarki www)
      @param bool, jesli "true" to wlaczenie przegladarki jesli "false" to wlaczenie managera plikow
      */
    void changeWWW(bool);

    /**
      @brief sygnal do widoku o zmiane wyswietlania adresu w pasku adresu
      @param nowy adres
      */
    void setAdres(QString s);

    /**
      @brief sygnal do widoku o odswierzenie strony www
      */
    void odswiezWWW();

public slots:

    /**
    @brief Slot otwieraj�cy wybrany katalog z menu dialogowego.
    */
    void otworzFolder();

    /**
      @brief Slot zapisuj�cy wybrany katalog/plik w _zaznaczonePliki do _skopiowanePliki.

      Ustawia akcje w _kopiowanie na KOPIA.
      */
    void kopiujPlik();

    /**
      @brief Slot kasuj�cy wybrany katalog/plik z _zaznaczonePliki.

      Usuwa trwale.
      */
    void kasujPlik();

    /**
      @brief Slot kopiuj�cy lub wklejaj�co-wycinaj�cy wybrany katalog/plik zapisany w _skopiowanePliki.

      Dzia�a w zale�no�ci jaka akcja zosta�a ustawiona w _kopiowanie.
      */
    void wklejPlik();

    /**
      @brief Slot zapisuj�cy wybrany katalog/plik w _zaznaczonePliki do _skopiowanePliki.

      Ustawia akcje w _kopiowanie na WYCIECIE.
      */
    void wytnijPlik();

    /**
      @brief Slot zmieniaj�cy nazwe wybranego katalogu/pliku z _zaznaczonePliki.

      Dzia�a je�li wybrany zosta� tylko jeden plik/katalog.
      */
    void zmienNazwe();

    /**
      @brief Slot tworz�cy nowy katalog w katalogu _aktywnyKatalog;

      Prosi o nazw� w oknie dialogowym.
      */
    void nowyKatalog();

    /**
      @brief Slot wysy�aj�cy sygna� do klasy widoku systemu plik�w celem wczytania na nowo struktury plik�w.
      */
    void odswiez();

    /**
      @brief Slot ustawiaj�cy _zaznaczonePliki.
      @param nazwy tablica ze �cie�kami plik�w.
      */
    void zaznaczPliki(std::vector<FileSystem::Path> nazwy);

    /**
      @brief Slot ustawiaj�cy _aktywnyKatalog.
      @param nazwy tablica ze �cie�k� do katalogu.
      */
    void aktywujKatalog(FileSystem::Path nazwa);

    /**
      @brief funkcja pomocnicza uruchamiania po utworzeniu g��wnego okna w celu wczytania ulubionych oraz ustawienia statusu na pasku.
      */
    void poUtworzeniuGlownegoOkna();


    /**
      @brief otwiera menu dialogowe wyboru katalogu startowego i go ustawia
      */

    void ustawKatalogStartowy();


    /**
      @brief Slot obs�uguj�cy ulubione.
      @param s nazwa ulubionego

      Wybiera odpowiednie dzia�anie w zale�no�ci od paramatru.
      Mo�e doda� nowy ulubiony, usun�� lub otworzy�.
      Dodawanie oraz usuwanie zrealizowane poprzez okna dialogowe.
      */
    void ulubione(std::wstring s);

    /**
      @brief Funkcja wczytuj�ca ulubione z pliku oraz wysy�aj�ca sygna�y celem uaktualnienia menuUlubione.
      */
    void wczytajUlubione();

    /**
      @brief wybor kolor�w i czcionki w widoku
      */
    void ustawKolory();

    /**
      @brief metoda wysylajaca sygnal celem otwarcia w widoku dnaego katalogu
      @param sciezka katalogu
      */
    void otworzKatalog(std::wstring kat);

    /**
      @brief funkcja otwierajaca dany plik w programie zewnetrznym (domyslnym dla danego rozszerzenia)
      @param sciezka do pliku
      */
    void otworzZewnetrznie(FileSystem::Path p);

    /**
    @brief slot wyswietlajacy komunikat oraz odswiezajacy widok
    @param tytul komunikatu
    @param tresc komunikatu
    */
    void komunikat(QString title, QString opis);

    /**
      @brief slot otrzymuje w parametrze nowy styl widoku i emituje sygnal do widoku o zmiane stylu
      @param nowy styl
      */
    void wyslijStyl(TreeViewStyle);

    /**
      @brief otwiera katalog startowy
      */
    void otworzKatalogStartowy();

    /**
      @brief ustawia aktualny status dzialania (czy przegladarka czy manager plikow)
      @param true-przegladarka www, false-manager plikow
      */
    void onWwwChange(bool);


    /**
     @brief emituje sygna� do g��wnego okna celem zmiany napisu na currentStatus
     */
    void changeStatus();

    /**
     @brief dodaje informacje do currentStatus (aktualnego statusu jaki ma byc wyswietlony)
     */
    void addToStatus(QString s);

    /**
     @brief usuwa dana informacje z currentStatus (aktualnego statusu jaki ma byc wyswietlony)
     */
    void rmFromStatus(QString s);

    /**
     @brief otwiera aktywny katalog w domyslnym eksploratorze systemowy (przewaznie Windows Explorer)
     */
    void toWindows();


private:

    /**
      @brief funkcja wywolujaca kopiowanie, a po jego zakonczeniu emitujaca sygnal z komunikatem
      */
    void watekKopiowania(TabIdPlikow biezace_pliki, IdPliku biezacy_katalog);

    /**
      @brief funkcja wywolujaca przenoszenie, a po jego zakonczeniu emitujaca sygnal z komunikatem
      */
    void watekPrzenoszenia(TabIdPlikow biezace_pliki, IdPliku biezacy_katalog);

    /**
      @brief funkcja wywolujaca kasowanie, a po jego zakonczeniu emitujaca sygnal z komunikatem
      */
    void watekKasowania(TabIdPlikow biezace_pliki);

    /**
      @brief Funkcja wczytuj�ca ustawienia z pliku
      */
    void wczytajUstawienia();

    /**
      @brief Funkcja zapisuj�c ustawienia do pliku
      */
    void zapiszUstawienia();

    /**
      @brief Funkcja dodaj�ca ulubiony.
      @param �cie�ka nowego ulubionego

      Dodaje do mapy _ulubione par�, gdzie kluczem jest nazw� pliku a warto�ci� �cie�ka.
      Emituje sygna� do g��wnego okna celem dodania ulubionego do menu.
      */
    void dodajUlubiony(std::wstring);

    /**
      @brief funkcja zwracajac sciezke do katalogu w ktorym podany w parametrze plik/katalog sie znajduje
      */
    IdPliku sciezkaPliku(std::wstring);

    /**
      @brief funkcja zwracajac nazwa pliku/katalogu
      @param pelna sciezka do pliku/katalogu
      */
    std::wstring nazwaPliku(std::wstring);

    /**
      @brief Tablica zaznaczonych plik�w.
      */
    TabIdPlikow _zaznaczonePliki;

    /**
      @brief Tablica skopiowanych b�d� wyci�tych plik�w.
      */
    TabIdPlikow _skopiowanePliki;

    /**
      @brief Mapa ulubionych, gdzie kluczem jest nazw� pliku a warto�ci� �cie�ka.
      */
    std::map<std::wstring, IdPliku> _ulubione;

    /**
    * @brief Informacja, czy elementy znajduj�ce sie w skopiowanych plikach sa do kopiowania czy do wyciecia i wklejenia.
    */
    KOPIOWANIE _kopiowanie;

    /**
    * @brief �cie�ka do aktywnego katalogu w ktorym to beda tworzyly sie nowe foldery, beda wklejane pliki, _aktywny!=zaznaczony
    */
    IdPliku _aktywnyKatalog;

    /**
    * @brief Katalog z ktorego bedzie sie rozpoczynalo przegladanie (zapisana informacja w pliku o nim)
    */
    IdPliku _startowyKatalog;

    /**
    * @brief Wygl�d czionki w TreeView
    */
    TreeViewStyle _stylWidoku;

    /**
    * @brief aktualny status dzialania (czy przegladarka czy manager plikow): true-przegladarka www, false-manager plikow
    */
    bool ifWwwOn;

    /**
    * @brief aktualny status jaki jest wyswietlany
    */
    QList<QString> currentStatus;

    IdPliku sciezkaStartowa;

};

#endif // FILESYSTEMCONTROLLER_H
