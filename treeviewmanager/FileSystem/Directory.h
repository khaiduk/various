/**
///\file Directory.h
///\brief definicja i deklaracja klasy Directory - klasa reprezentuje katalogi
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _DIR_H_
  #define _DIR_H_

///pliki nagłówkowe

#include "Element.h"
#include <iostream>
#include <string>
#include <vector>
#include "File.h"


using namespace std;

/**
  ///\brief Biblioteka umożliwiająca zarządzanie systemem plików Windows
*/
namespace FileSystem
{

/**
  ///\brief klasa reprezentująca katalogi, dziedziczy po Element
*/
class Directory : public Element
{
  public:
    /**
      ///\brief konstruktor domyślny
    */
    Directory(){};

    /**
      ///\brief konstruktor przyjmujący obiekt Path& ewentualnie string lub const char* (wynika to z konwersji Path)
    */
    Directory(const Path& p);

    /**
      ///\brief konwersja do Path
    */
    operator Path() const;

    /**
      ///\brief zwraca wektor referencji Element pod ktorymi kryją sie obiekty File lub Directory. Jest to lista elementów zawartości tego katalogu
    */
    vector<Element> content() const;


  private:
};




}///end of namespace


#endif
