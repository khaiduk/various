/**
  *@author S³awomir Gefert
  *@date 2012-06-13
  */

#ifndef TREEVIEWSTYLE_H
#define TREEVIEWSTYLE_H
#include <QFont>
#include <QColor>
#include <QString>
#include <string>
#include <sstream>

class TreeViewStyle
{
public:
    /**
      @brief konstruktor
      @param f styl czcionki
      @param n kolor nieaktywnego elementu
      @param a kolor aktywnego elementu
      @param w kolor wybranego elementu
      @param z kolor zaznaczonego elementu
      */
    TreeViewStyle(QFont f, QColor n, QColor a, QColor w, QColor z);
    TreeViewStyle(){}

    /**

      */
    QFont font;

    /**
      @brief zwraca rozmiar czcionki w pixelach
      */
    int getPixelSize();

    /**
      @brief kolor nieaktywnego elementu
      */
    QColor nieaktywny;

    /**
      @brief kolor aktywnego elementu
      */
    QColor aktywny;

    /**
      @brief kolor wybranego elementu
      */
    QColor wybrany;

    /**
      @brief kolor zaznaczonego elementu
      */
    QColor zaznaczony;

    /**
      @brief zamienia klase TreeViewStyle w string
      */
    std::wstring toString();

    /**
      @brief tworzy klase TreeViewStyle ze stringu
      */
    static  TreeViewStyle fromString(std::wstring s);

};

#endif // TREEVIEWSTYLE_H
