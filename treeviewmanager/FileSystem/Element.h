/**
///\file Element.h
///\brief definicja i deklaracja klasy Element
///
///jest to klasa definiuj¹ca ogólne metody tylko do odziedziczenia przez klasy File i Directory. Metody mog¹ byæ wykonane zarówno dla plików jak i katalógow
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////


//do³¹czenie plików nag³ówkowych
#ifndef _ELEMENT_H_
 #define _ELEMENT_H_

 #include "Path.h"
 #include "Globals.h"




namespace FileSystem
{

/**
  ///\brief klasa nadrzêdna dla katalógow i plików
*/
class Element
{
  public:
    /**
    ///\brief typ gromadz¹cy wszystkie prawa dostepu
    */
    enum perms{read, write, execute, readWrite, readExecute, writeExecute, all, none};

    /**
      ///\brief pomocnicza struktura nios¹ca informacje o prawach dostepu
    */
    struct Perms
    {
        perms owner;
        perms group;
        perms others;
    };

    /**
      ///\brief ustawia sciezkê typu Path do tego Elementu
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
      ///\brief zwraca w postaci stringa nazwê aktualnego elementu
    */
    string getName() const;

    /**
      ///\brief metoda zwracaj¹ca informacje o prawach dostêpu w postaci obiektu Element::Perms. Jesli plik lub katalog nie istnieje zwróci prawa 'none' dla wszystkich
    */
    Perms permissions() const;

    /**
      ///\brief zwraca prawa w postaci ciagu znaków np rwxrwxrwx. Jeœli element nie istnieje zwroci --------
    */
    const char* permissionsStr() const;

    /**
      ///\brief zwraca typ wyliczeniowy Globals::type mowi¹cy czy element jest plikiem czy katalogiem czy czymœ innym
    */
    Globals::type whatIs() const;

    /**
      ///\brief kopiowanie do nowego miejsca, drugi parametr jako opcjonalny mówi czy zamienic istniejece pliki i foldery
    */
    void copy(const Path& dokad, Globals::copy_move_option option=Globals::fail_if_exists) const;

    /**
      ///\brief usuwa plik/katalog. Jeœli nie ma nie robi nic
    */
    void remove();

    /**
      ///\brief zmienia œcie¿kê na nowa - na koñcu nowej œcie¿ki musi pojawic siê nazwa pliku!
    */
    void rename(const Path& nowaSciezka);

    /**
      ///\brief zmienia nazwê pliku/katalogu w aktualnym katalogu na now¹ (podajemy nazwê a nie sciezke)
    */
    void rename(const char* nowaNazwa);

    /**
      ///\brief zwraca rozmiar piku lub katalogu
    */
    uintmax_t size() const;

    /**
      ///\brief przenosi plik/katalog do nowego miejsca. Pamiêtamy o drugim opcjonalnym parametrze
    */
    void move(const Path& dokad, Globals::copy_move_option option=Globals::fail_if_exists);

    /**
      ///\brief zwraca w postaci liczby calkowitej pozycjê aktualnego elementu wzglêdem innego.
      ///
      ///NP: mamy c:/a/b oraz c:/a/b/c jeœli dla c:/a/b wywolamy funkcjê pyt¹jc siê o pozycje wzglêdem c:/a/b/c
      ///zwróci nam 1 (bo musimy sie zag³êbic o 1) jeœli dla c:/a/b/c wywolamy funkcjê i w parametrze przeka¿emy
      ///c:/a/b to zwroci -1. Jesli wywolamy dla c:/a/b/c funkcje ale w parametrze damy c:/ to zwroci -2.
      ///funkcja wywo³ana dla elementów w tym samym katalogu(na tym samym poziomie zwróci 0)
      ///funkcja pokazuje jakby wzglêdny poziom zag³ebienia
      ///DZIA³A DLA PLIKOW/KATALOGÓW KTÓRE NIE ISTNIEJ¥
    */
    int positionTo(const Path& p) const;

    /**
      ///\brief zwraca obiekt Path rodzica tego elementu
    */
    Path parent() const;

    /**
      ///\brief zwraca imiê rodzica w posciaci const char*, jesli nie istnieje zwroci NULL
    */
    const char* parentName() const;

    /**
      ///\brief zwraca true jeœli element istnieje i false jesli nie
    */
    bool exists() const;

    /**
      ///\brief zwraca obiekt Path do roota tego elementu. Potrafi to zrobiæ takze dla nieistniej¹cych elementów
    */
    Path rootDirectory() const;

  protected:
    /**
      ///\brief obiekt przechowuj¹cy inf o œcie¿ce do aktualnego elementu
    */
    Path path;
};

}///end of namespace

#endif
