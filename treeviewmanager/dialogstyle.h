/**
  *@author S³awomir Gefert
  *@date 2012-06-13
  */

#ifndef DIALOGSTYLE_H
#define DIALOGSTYLE_H

#include <QDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QPixmap>
#include "treeviewstyle.h"

namespace Ui {
class DialogStyle;
}

class DialogStyle : public QDialog
{
    Q_OBJECT

public:
    /**
      @brief konstruktor
      @param s obecny styl
      @param parent rodzic
      */
    explicit DialogStyle(const TreeViewStyle& s,QWidget *parent=0);
    ~DialogStyle();
signals:
    /**
      @brief sygnal do klasy FileSystemController informujacy o nowym stylu widoku
      @param nowy styl
      */
    void styleChanged(TreeViewStyle);
public slots:
    /**
      @brief wybieranie nowej czcionki
     */
    void setCzcionka();
    /**
      @brief wybieranie koloru elementu nieaktywnego
     */
    void setNieaktywny();
    /**
      @brief wybieranie koloru elementu aktywnego
  */
    void setAktywny();
    /**
      @brief wybieranie koloru elementu wybranego
  */
    void setWybrany();
    /**
      @brief wybieranie koloru elementu zaznaczonego
   */
    void setZaznaczony();

    /**
      @brief akceptacja nowego stylu i wyemitowanie sygnalu ze zmiana
      */
    void zaakceptuj();

    /**
      @brief odrzucenie zmian
      */
    void odrzuc();
private:
    Ui::DialogStyle *ui;

    /**
      @brief nowy styl
      */
    TreeViewStyle styl;
    /**
      @brief stary styl
      */
    const TreeViewStyle& orygStyl;

};

#endif // DIALOGSTYLE_H
