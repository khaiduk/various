/**
///\file Globals.h
///\brief definicja i deklaracja klasy Globals - klasa posiada zestaw statycznych metod umożliwiających różne operacje na plikach czy katalogach
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBALS_H_
  #define _GLOBALS_H_

//do��czenie plik�w nag��wkowych
#include <iostream>
#include <string>
#include "Path.h"
#include <vector>
#include <boost/filesystem.hpp>
#include <windows.h>
#include <tchar.h>


namespace FileSystem
{

/**
  ///\brief klasa p�l, metod i enum�w globalnych
*/
class Globals
{
  public:

    /**
      ///\brief ingormacja czy co� jest plikiem czy folderem, je�li other to nie istnieje lub jest problem z dostaniem informacji
    */
    enum type{file, dir, other};

    /**
      ///\brief opcje przy kopiowaniu i przenoszeniu m�wi�ce czy zamieni� istniej�ce pliki i katalogi
    */
    enum copy_move_option{fail_if_exists, overwrite_if_exists};

    /**
      ///\brief zwraca true je�li plik lub folder podany w parametrze jest pusty lub nie istnieje
    */
    static bool isEmpty(const Path& p);

    /**
      ///\brief zwraca enum type m�wi�ce czy co� jest plikiem, katalogiem czy jest problem z odczytem - wtedy zwr�ci other
    */
    static type whatIs(const Path& p);

    /**
      ///\brief metoda kopiuje plik lub katalog z zawarto�ci� w podane miejsce. Trzeci parametr m�wi o zachowaniu gdyby w miejscu docelowym ju� by�� plik lub folder o danej nazwie. Parametr 'dokad' musi miec w sobie nazw� pliku czy folderu docelowego
    */
    static void copy(const Path& skad, const Path& dokad, copy_move_option option=fail_if_exists);

    /**
      ///\brief tworzy pusty folder w miejscu okre�lonym przez argument. Je�li si� powiedzie zwr�ci true. Potrafi stworzy� ca�� hierarchi� np c:/a/b/c - stworzy a/b/c
    */
    static bool createDir(const Path& sciezka);

    /**
      ///\brief zwr�ci true je�li istnieje plik/katalog o podanej �cie�ce
    */
    static bool exists(const Path& sciezka);

    /**
      ///\brief usunie plik lub folder razem z zawarto�ci�. Us�wa z dysku, nie przenosi do kosza
    */
    static void remove(const Path& sciezka);

    /**
      ///\brief zmieni nazw� pliku lub katalogu. W parametrze podajemy �cie�k� i na ko�cu now� nazw� elementu.
    */
    static void rename(const Path& stara, const Path& nowa);

    /**
      ///\brief metoda gdzie w drugim parametrze podajemy jedynie now� nazw�
    */
    static void rename(const Path& stara, const char* nowaNazwa);

    /**
      ///\brief przenosi plik lub katalog ze starego do nowego miejsca. Jak zawsze w parametrze 'dokad' ma byc na ko�cu nowa nazwa (lub stara) przenoszonego elementu. Ostatni parametr decyduje o tym co robi� gdy w miejscu docelowym ju� istnieje plik/katalog o tej samej nazwie
    */
    static void move(const Path& skad, const Path& dokad, copy_move_option option=fail_if_exists);

    /**
      ///\brief zwraca �cie�k� korzenia dla danego elementu. Dzia�a dla nieistniej�cych �cierzek
    */
    static Path rootDirectory(const Path& p);

    /**
      ///\brief zwraca rozmiar pliku/katalogu z zawarto�ci�
    */
    static boost::uintmax_t size(const Path& p);

    /**
      ///\brief zwraca w postaci liczby calkowitej pozycj� elementu wzgl�dem innego.
        ///
        ///NP: mamy c:/a/b oraz c:/a/b/c je�li dla c:/a/b wywolamy funkcj� pytaj�c si� o pozycj� wzgl�dem c:/a/b/c
        ///zwr�ci nam 1 (bo musimy sie zag��bic o 1) je�li dla c:/a/b/c wywolamy funkcj� i w parametrze przeka�emy
        ///c:/a/b to zwroci -1. Je�li wywolamy dla c:/a/b/c funkcje ale w parametrze damy c:/ to zwroci -2.
        ///funkcja wywo�ana dla element�w w tym samym katalogu(na tym samym poziomie zwr�ci 0)
        ///funkcja pokazuje jakby wzgl�dny poziom zag��bienia
        ///DZIA�A DLA PLIKOW/KATALOG�W KT�RE NIE ISTNIEJ�
    */
    static int positionTo(const Path& p1, const Path& p2);

    /**
      ///\brief metoda zwraca wektor z obiektami Path reprezentuj�cymi wszystkie dyski. Dzia�a dla Windowsa
    */
    static vector<FileSystem::Path> getDisks();
};

}///end of namespace

#endif
