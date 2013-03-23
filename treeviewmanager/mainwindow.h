/**
  *@author S³awomir Gefert
  *@date 2012-06-13
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QWebView>

#include "ulubioneaction.h"

#include "filesystemcontroller.h"
namespace Ui
{
class MainWindow;
}

/**
  @class MainWindow
  @brief G³ówne okno programu.

  Klasa bêd¹ca g³ównym oknem programu. Zawiera równie¿ instancje klas pomocniczych
  takich jak FileSystemController, przetrzymywane pomocniczo menuUlubione celem
  ³atwiejszej aktualizcji tego menu.
  Dziedziczy po klasie QMainWindow.

  */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
      @brief Konstruktor klasy. Dodatkowo tworzy wiêkszoœæ po³¹czeñ miêdzy sygna³ami, a slotami.
      @param rodzic tego obiektu
      */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
      @brief Uruchamia metodê z klasy bazowej wyswietlaj¹c¹ okno oraz uruchamia metodê tworz¹c¹ menu i otwieraj¹c¹ folder startowy
      */
    void show();
signals:
    /**
      @brief sygnal informujacy o zmianie dzialania programu z przegladarki www na manager plikow
      @param true-przegladarka www uruchomiona, false - manager plikow uruchomiony
      */
    bool wwwChanged(bool);
public slots:

    /**
      @brief Slot, który dodaje now¹ akcje do Ulubionych.
      @param nazwa tworzonego ulubionego

      Dodaje akcjê do menuUlubione o nazwie przekazanej w parametrze i ustawia to
      menu jako wyœwietlane dla przycisku BUlubione. Ponadto tworzy po³¹czenie
      sygna³u triggered utworzonej akcji menu ze slotem w niej siê znajduj¹cym,
      aby ten slot móg³ nadaæ sygna³ z dodatkowym parametrem go identyfikuj¹cym.
      Nastêpnie tworzy po³¹czenie w.w. sygna³u z parametrem ze slotem
      znajduj¹cym siê w fsystem, celem wykonania odpowiedniej funkcji
      (np. dodanie nowego ulubionego, wybranie ulubionego, usuniecie itd.).
      */
    void dodajUlubiony(std::wstring s);

    /**
      @brief Slot, usuwaj¹cy ulubiony.
      @param nazwa usuwanego ulubionego

      Usuwa akcjê z menuUlubione.
      */
    void usunUlubione(std::wstring szukany);

    /**
      @brief Slot, usuwaj¹cy ulubiony.
      @param nazwa usuwanego ulubionego

      Usuwa akcjê z menuUlubione.
      */
    void przejdzNaAdres();

    /**
      @brief przelacza tryb dzialania z przegladarki www na manager plikow lub odwrotnie - pokazuje lub ukrywa odpowiedni widget
      @param true-przegladarka www; false-manager plikow
      */
    void changeWWW(bool wlacz);



private:
    Ui::MainWindow *ui;

    /**
      WskaŸnik na instancje g³ównej klasy steruj¹cej.
      */
    FileSystemController* fsystem;

    /**
      Pomocniczo przetrzymywany wskaŸnik na menuUlubione celem
      ³atwiejszej aktualizcji tego menu.
      */
    QMenu* menuUlubione;



    /**
    * @brief aktualny status dzialania (czy przegladarka czy manager plikow): true-przegladarka www, false-manager plikow
    */
    bool ifWwwOn;


};

#endif // MAINWINDOW_H
