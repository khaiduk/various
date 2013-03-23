/**
///\file Directory.h
///\brief definicja i deklaracja klasy Directory - klasa reprezentuje katalogi
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _DIR_H_
  #define _DIR_H_

///pliki nag��wkowe

#include "Element.h"
#include <iostream>
#include <string>
#include <vector>
#include "File.h"


using namespace std;

/**
  ///\brief Biblioteka umo�liwiaj�ca zarz�dzanie systemem plik�w Windows
*/
namespace FileSystem
{

/**
  ///\brief klasa reprezentuj�ca katalogi, dziedziczy po Element
*/
class Directory : public Element
{
  public:
    /**
      ///\brief konstruktor domy�lny
    */
    Directory(){};

    /**
      ///\brief konstruktor przyjmuj�cy obiekt Path& ewentualnie string lub const char* (wynika to z konwersji Path)
    */
    Directory(const Path& p);

    /**
      ///\brief konwersja do Path
    */
    operator Path() const;

    /**
      ///\brief zwraca wektor referencji Element pod ktorymi kryj� sie obiekty File lub Directory. Jest to lista element�w zawarto�ci tego katalogu
    */
    vector<Element> content() const;


  private:
};




}///end of namespace


#endif
