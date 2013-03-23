/**
///\file File.h
///\brief deklaracja i definicja klasy File reprezêtujacej pliki
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////


#ifndef _FILE_H_
  #define _FILE_H_


//dolaczenie plikow nag³ókowych
#include "Element.h"
#include <iostream>
#include <string>


using namespace std;


namespace FileSystem
{

/**
  ///\brief klasa reprezentuj¹ca plik dziedziczy po ogólnej klasie Element
*/
class File : public Element
{
  public:

    /**
      ///\brief konstruktor domyœlny
    */
    File(){};

    /**
      ///\brief konstruktor przyjmuj¹cy obiekt Path lub ew wstring i string lub const char* (wynika to z konwersji Path)
    */
    File(const Path& p);

    /**
      ///\brief konwersja do Path
    */
    operator Path() const;

    /**
      ///\brief metoda otwieraj¹ca plik na zewn¹trz w domyœlnym programie systemu, zwraca true jeœli sie powiedzie
    */
    bool execute() const;

    /**
      ///\brief zwraca w postaci const char* rozszerzenie pliku w przyk³adowym formacie ".txt"
    */
    const char* extension() const;

  private:
};




}///end of  namespace


#endif
