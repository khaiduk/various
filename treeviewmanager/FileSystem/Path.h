/**
///\file Path.h
///\brief definicja i deklaracja klasy Path - klasa reprezentuje sciezke
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _PATH_H_
  #define _PATH_H_

///nag��wki
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


namespace FileSystem
{

/**
  ///\brief klasa przechowuj�ca informacje o scie�ce do pliku lub katalogu
*/
class Path
{
  public:

    /**
      ///\brief konstruktor domy�lny
    */
    Path(){};

    /**
      ///\brief konstruktor przyjmuj�cy jako parametr �cie�k� do pliku/katalogu
    */
    Path(const string str);

    /**
      ///\brief konstruktor przyjmuj�cy ci�g znak�w. Mo�emy u�y� Zamiast Path("c:/") - "c:\"
    */
    Path(const char* c);

    /**
      ///\brief konstruktor przyjmuj�cy wstringa
    */
    Path(const wstring& wstr);

    /**
      ///\brief operator konwersji do const char*
    */
    operator const char*() const;

    /**
      ///\brief operator konwersji do wstring
    */
    operator wstring() const;

    /**
      ///\brief operator konwersji do string
    */
    operator string() const;

    /**
      ///\brief zwraca tekstow� reprezentacj� obiektu Path
      ///
      ///metoda zwraca string-owa reprezentacje obiektu Path czyli: cout<<Path.getPath("asdw") zwroci asdw
    */
    string getPath() const;

    /**
      ///\brief zmiana �cie�ki kt�r� reprezentuje ten obiekt Path
    */
    void setPath(const string str);

    /**
      ///\brief operator por�wnania - zwr�ci true je�li �cie�ki reprezentuj� ten sam element ( nie musz� by� tak samo zapisane)
    */
    bool operator==(const Path& p) const;

    /**
      ///\brief operator !=  zwraca zaprzeczenie opertora ==
    */
    bool operator!=(const Path& p) const;

  private:
    /**
      ///\brief obiekt tekstowy reprezentuj�cy �cie�k� do elementu
    */
    string path;
};

}///end namespace


#endif
