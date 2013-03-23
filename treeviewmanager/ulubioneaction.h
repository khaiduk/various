/**
  *@author S�awomir Gefert
  *@date 2012-06-13
  */
#ifndef ULUBIONEACTION_H
#define ULUBIONEACTION_H
#include <QAction>
#include <string>

/**
  @class UlubioneAction
  @brief Klasa akcji menu Ulubionych.

  Klasa dziedziczy po klasie QAction. U�ywana w celu przechowywania
  dodatkowej informacji identyfikuj�cej wybran� akcj�. Sygna�
  trigerred() (klikni�ci� na ni�) jest przkazywany do jej slotu przeslijDalej(),
  kt�ry to pobiera jej "identyfikator" i wysy�a sygna� z paramatrem, dzi�ki
  temu mo�liwa jest �atwa indetyfikacja, kt�ra to akcja zosta�a wybrana z menu.

  */
class UlubioneAction: public QAction
{
    Q_OBJECT
public:
    /**
      @brief Konstruktor
      @param s nazwa wy�wietlana oraz identyfikator
      @param p rodzic
      */
    explicit UlubioneAction(const QString& s, QObject* p=0);

    /**
      @brief Zwraca identyfikator.
      */
    std::wstring getVal();
signals:

    /**
      @brief Sygna� wci�ni�cia przycisku wraz z indetyfikatorem.
      */
    void sygnalUlubione(std::wstring);

public slots:
    /**
      @brief Slot odbieraj�cy informacj� o wci�ni�tej akcji emituj�cy sygna� wraz z indetyfikatorem.
      */
    void przeslijDalej();

private:
    /**
      Identyfikator.
      */
    std::wstring val;
};

#endif // ULUBIONEACTION_H
