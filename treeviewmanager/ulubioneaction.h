/**
  *@author S³awomir Gefert
  *@date 2012-06-13
  */
#ifndef ULUBIONEACTION_H
#define ULUBIONEACTION_H
#include <QAction>
#include <string>

/**
  @class UlubioneAction
  @brief Klasa akcji menu Ulubionych.

  Klasa dziedziczy po klasie QAction. U¿ywana w celu przechowywania
  dodatkowej informacji identyfikuj¹cej wybran¹ akcjê. Sygna³
  trigerred() (klikniêci¹ na ni¹) jest przkazywany do jej slotu przeslijDalej(),
  który to pobiera jej "identyfikator" i wysy³a sygna³ z paramatrem, dziêki
  temu mo¿liwa jest ³atwa indetyfikacja, która to akcja zosta³a wybrana z menu.

  */
class UlubioneAction: public QAction
{
    Q_OBJECT
public:
    /**
      @brief Konstruktor
      @param s nazwa wyœwietlana oraz identyfikator
      @param p rodzic
      */
    explicit UlubioneAction(const QString& s, QObject* p=0);

    /**
      @brief Zwraca identyfikator.
      */
    std::wstring getVal();
signals:

    /**
      @brief Sygna³ wciœniêcia przycisku wraz z indetyfikatorem.
      */
    void sygnalUlubione(std::wstring);

public slots:
    /**
      @brief Slot odbieraj¹cy informacjê o wciœniêtej akcji emituj¹cy sygna³ wraz z indetyfikatorem.
      */
    void przeslijDalej();

private:
    /**
      Identyfikator.
      */
    std::wstring val;
};

#endif // ULUBIONEACTION_H
