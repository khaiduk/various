/**
///\file Path.h
///\brief definicja i deklaracja klasy Path - klasa reprezentuje sciezke
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#ifndef _PATH_H_
  #define _PATH_H_

///nag³ówki
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


namespace FileSystem
{

/**
  ///\brief klasa przechowuj¹ca informacje o scie¿ce do pliku lub katalogu
*/
class Path
{
  public:

    /**
      ///\brief konstruktor domyœlny
    */
    Path(){};

    /**
      ///\brief konstruktor przyjmuj¹cy jako parametr œcie¿kê do pliku/katalogu
    */
    Path(const string str);

    /**
      ///\brief konstruktor przyjmuj¹cy ci¹g znaków. Mo¿emy u¿yæ Zamiast Path("c:/") - "c:\"
    */
    Path(const char* c);

    /**
      ///\brief konstruktor przyjmuj¹cy wstringa
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
      ///\brief zwraca tekstow¹ reprezentacjê obiektu Path
      ///
      ///metoda zwraca string-owa reprezentacje obiektu Path czyli: cout<<Path.getPath("asdw") zwroci asdw
    */
    string getPath() const;

    /**
      ///\brief zmiana œcie¿ki któr¹ reprezentuje ten obiekt Path
    */
    void setPath(const string str);

    /**
      ///\brief operator porównania - zwróci true jeœli œcie¿ki reprezentuj¹ ten sam element ( nie musz¹ byæ tak samo zapisane)
    */
    bool operator==(const Path& p) const;

    /**
      ///\brief operator !=  zwraca zaprzeczenie opertora ==
    */
    bool operator!=(const Path& p) const;

  private:
    /**
      ///\brief obiekt tekstowy reprezentuj¹cy œcie¿kê do elementu
    */
    string path;
};

}///end namespace


#endif
