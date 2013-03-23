/**
///\file Globals.h
///\brief definicja i deklaracja klasy Globals - klasa posiada zestaw statycznych metod umoÅ¼liwiajÄ…cych rÃ³Å¼ne operacje na plikach czy katalogach
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBALS_H_
  #define _GLOBALS_H_

//do³¹czenie plików nag³ówkowych
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
  ///\brief klasa pól, metod i enumów globalnych
*/
class Globals
{
  public:

    /**
      ///\brief ingormacja czy coœ jest plikiem czy folderem, jeœli other to nie istnieje lub jest problem z dostaniem informacji
    */
    enum type{file, dir, other};

    /**
      ///\brief opcje przy kopiowaniu i przenoszeniu mówi¹ce czy zamieniæ istniej¹ce pliki i katalogi
    */
    enum copy_move_option{fail_if_exists, overwrite_if_exists};

    /**
      ///\brief zwraca true jeœli plik lub folder podany w parametrze jest pusty lub nie istnieje
    */
    static bool isEmpty(const Path& p);

    /**
      ///\brief zwraca enum type mówi¹ce czy coœ jest plikiem, katalogiem czy jest problem z odczytem - wtedy zwróci other
    */
    static type whatIs(const Path& p);

    /**
      ///\brief metoda kopiuje plik lub katalog z zawartoœci¹ w podane miejsce. Trzeci parametr mówi o zachowaniu gdyby w miejscu docelowym ju¿ by³‚ plik lub folder o danej nazwie. Parametr 'dokad' musi miec w sobie nazwê pliku czy folderu docelowego
    */
    static void copy(const Path& skad, const Path& dokad, copy_move_option option=fail_if_exists);

    /**
      ///\brief tworzy pusty folder w miejscu okreœlonym przez argument. Jeœli siê powiedzie zwróci true. Potrafi stworzyæ ca³¹ hierarchiê np c:/a/b/c - stworzy a/b/c
    */
    static bool createDir(const Path& sciezka);

    /**
      ///\brief zwróci true jeœli istnieje plik/katalog o podanej œcie¿ce
    */
    static bool exists(const Path& sciezka);

    /**
      ///\brief usunie plik lub folder razem z zawartoœci¹. Usówa z dysku, nie przenosi do kosza
    */
    static void remove(const Path& sciezka);

    /**
      ///\brief zmieni nazwê pliku lub katalogu. W parametrze podajemy œcie¿kê i na koñcu now¹ nazwê elementu.
    */
    static void rename(const Path& stara, const Path& nowa);

    /**
      ///\brief metoda gdzie w drugim parametrze podajemy jedynie now¹ nazwê
    */
    static void rename(const Path& stara, const char* nowaNazwa);

    /**
      ///\brief przenosi plik lub katalog ze starego do nowego miejsca. Jak zawsze w parametrze 'dokad' ma byc na koñcu nowa nazwa (lub stara) przenoszonego elementu. Ostatni parametr decyduje o tym co robiæ gdy w miejscu docelowym ju¿ istnieje plik/katalog o tej samej nazwie
    */
    static void move(const Path& skad, const Path& dokad, copy_move_option option=fail_if_exists);

    /**
      ///\brief zwraca œcie¿kê korzenia dla danego elementu. Dzia³a dla nieistniej¹cych œcierzek
    */
    static Path rootDirectory(const Path& p);

    /**
      ///\brief zwraca rozmiar pliku/katalogu z zawartoœci¹
    */
    static boost::uintmax_t size(const Path& p);

    /**
      ///\brief zwraca w postaci liczby calkowitej pozycjê elementu wzglêdem innego.
        ///
        ///NP: mamy c:/a/b oraz c:/a/b/c jeœli dla c:/a/b wywolamy funkcjê pytaj¹c siê o pozycjê wzglêdem c:/a/b/c
        ///zwróci nam 1 (bo musimy sie zag³êbic o 1) jeœli dla c:/a/b/c wywolamy funkcjê i w parametrze przeka¿emy
        ///c:/a/b to zwroci -1. Jeœli wywolamy dla c:/a/b/c funkcje ale w parametrze damy c:/ to zwroci -2.
        ///funkcja wywo³ana dla elementów w tym samym katalogu(na tym samym poziomie zwróci 0)
        ///funkcja pokazuje jakby wzglêdny poziom zag³êbienia
        ///DZIA£A DLA PLIKOW/KATALOGÓW KTÓRE NIE ISTNIEJ¥
    */
    static int positionTo(const Path& p1, const Path& p2);

    /**
      ///\brief metoda zwraca wektor z obiektami Path reprezentuj¹cymi wszystkie dyski. Dzia³a dla Windowsa
    */
    static vector<FileSystem::Path> getDisks();
};

}///end of namespace

#endif
