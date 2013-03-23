/**
///\file File.h
///\brief deklaracja i definicja klasy File reprez�tujacej pliki
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////


#ifndef _FILE_H_
  #define _FILE_H_


//dolaczenie plikow nag��kowych
#include "Element.h"
#include <iostream>
#include <string>


using namespace std;


namespace FileSystem
{

/**
  ///\brief klasa reprezentuj�ca plik dziedziczy po og�lnej klasie Element
*/
class File : public Element
{
  public:

    /**
      ///\brief konstruktor domy�lny
    */
    File(){};

    /**
      ///\brief konstruktor przyjmuj�cy obiekt Path lub ew wstring i string lub const char* (wynika to z konwersji Path)
    */
    File(const Path& p);

    /**
      ///\brief konwersja do Path
    */
    operator Path() const;

    /**
      ///\brief metoda otwieraj�ca plik na zewn�trz w domy�lnym programie systemu, zwraca true je�li sie powiedzie
    */
    bool execute() const;

    /**
      ///\brief zwraca w postaci const char* rozszerzenie pliku w przyk�adowym formacie ".txt"
    */
    const char* extension() const;

  private:
};




}///end of  namespace


#endif
