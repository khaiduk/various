/**
///\file Element.h
///\brief definicja i deklaracja klasy Element
///
///jest to klasa definiuj�ca og�lne metody tylko do odziedziczenia przez klasy File i Directory. Metody mog� by� wykonane zar�wno dla plik�w jak i katal�gow
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////


//do��czenie plik�w nag��wkowych
#ifndef _ELEMENT_H_
 #define _ELEMENT_H_

 #include "Path.h"
 #include "Globals.h"




namespace FileSystem
{

/**
  ///\brief klasa nadrz�dna dla katal�gow i plik�w
*/
class Element
{
  public:
    /**
    ///\brief typ gromadz�cy wszystkie prawa dostepu
    */
    enum perms{read, write, execute, readWrite, readExecute, writeExecute, all, none};

    /**
      ///\brief pomocnicza struktura nios�ca informacje o prawach dostepu
    */
    struct Perms
    {
        perms owner;
        perms group;
        perms others;
    };

    /**
      ///\brief ustawia sciezk� typu Path do tego Elementu
    */
    void setPath(const Path& p);

    /**
      ///\brief konwersja do cost Path&
    */
    operator const Path&() const;

    /**
      ///\brief zwraca jawnie obiekt const Path tego elementu
    */
    const Path& getPath() const;

    /**
      ///\brief zwraca obiekt Path tego elementu
    */
    Path getPath();

    /**
      ///\brief zwraca w postaci stringa nazw� aktualnego elementu
    */
    string getName() const;

    /**
      ///\brief metoda zwracaj�ca informacje o prawach dost�pu w postaci obiektu Element::Perms. Jesli plik lub katalog nie istnieje zwr�ci prawa 'none' dla wszystkich
    */
    Perms permissions() const;

    /**
      ///\brief zwraca prawa w postaci ciagu znak�w np rwxrwxrwx. Je�li element nie istnieje zwroci --------
    */
    const char* permissionsStr() const;

    /**
      ///\brief zwraca typ wyliczeniowy Globals::type mowi�cy czy element jest plikiem czy katalogiem czy czym� innym
    */
    Globals::type whatIs() const;

    /**
      ///\brief kopiowanie do nowego miejsca, drugi parametr jako opcjonalny m�wi czy zamienic istniejece pliki i foldery
    */
    void copy(const Path& dokad, Globals::copy_move_option option=Globals::fail_if_exists) const;

    /**
      ///\brief usuwa plik/katalog. Je�li nie ma nie robi nic
    */
    void remove();

    /**
      ///\brief zmienia �cie�k� na nowa - na ko�cu nowej �cie�ki musi pojawic si� nazwa pliku!
    */
    void rename(const Path& nowaSciezka);

    /**
      ///\brief zmienia nazw� pliku/katalogu w aktualnym katalogu na now� (podajemy nazw� a nie sciezke)
    */
    void rename(const char* nowaNazwa);

    /**
      ///\brief zwraca rozmiar piku lub katalogu
    */
    uintmax_t size() const;

    /**
      ///\brief przenosi plik/katalog do nowego miejsca. Pami�tamy o drugim opcjonalnym parametrze
    */
    void move(const Path& dokad, Globals::copy_move_option option=Globals::fail_if_exists);

    /**
      ///\brief zwraca w postaci liczby calkowitej pozycj� aktualnego elementu wzgl�dem innego.
      ///
      ///NP: mamy c:/a/b oraz c:/a/b/c je�li dla c:/a/b wywolamy funkcj� pyt�jc si� o pozycje wzgl�dem c:/a/b/c
      ///zwr�ci nam 1 (bo musimy sie zag��bic o 1) je�li dla c:/a/b/c wywolamy funkcj� i w parametrze przeka�emy
      ///c:/a/b to zwroci -1. Jesli wywolamy dla c:/a/b/c funkcje ale w parametrze damy c:/ to zwroci -2.
      ///funkcja wywo�ana dla element�w w tym samym katalogu(na tym samym poziomie zwr�ci 0)
      ///funkcja pokazuje jakby wzgl�dny poziom zag�ebienia
      ///DZIA�A DLA PLIKOW/KATALOG�W KT�RE NIE ISTNIEJ�
    */
    int positionTo(const Path& p) const;

    /**
      ///\brief zwraca obiekt Path rodzica tego elementu
    */
    Path parent() const;

    /**
      ///\brief zwraca imi� rodzica w posciaci const char*, jesli nie istnieje zwroci NULL
    */
    const char* parentName() const;

    /**
      ///\brief zwraca true je�li element istnieje i false jesli nie
    */
    bool exists() const;

    /**
      ///\brief zwraca obiekt Path do roota tego elementu. Potrafi to zrobi� takze dla nieistniej�cych element�w
    */
    Path rootDirectory() const;

  protected:
    /**
      ///\brief obiekt przechowuj�cy inf o �cie�ce do aktualnego elementu
    */
    Path path;
};

}///end of namespace

#endif
