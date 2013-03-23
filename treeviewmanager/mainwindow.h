/**
  *@author S�awomir Gefert
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
  @brief G��wne okno programu.

  Klasa b�d�ca g��wnym oknem programu. Zawiera r�wnie� instancje klas pomocniczych
  takich jak FileSystemController, przetrzymywane pomocniczo menuUlubione celem
  �atwiejszej aktualizcji tego menu.
  Dziedziczy po klasie QMainWindow.

  */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
      @brief Konstruktor klasy. Dodatkowo tworzy wi�kszo�� po��cze� mi�dzy sygna�ami, a slotami.
      @param rodzic tego obiektu
      */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
      @brief Uruchamia metod� z klasy bazowej wyswietlaj�c� okno oraz uruchamia metod� tworz�c� menu i otwieraj�c� folder startowy
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
      @brief Slot, kt�ry dodaje now� akcje do Ulubionych.
      @param nazwa tworzonego ulubionego

      Dodaje akcj� do menuUlubione o nazwie przekazanej w parametrze i ustawia to
      menu jako wy�wietlane dla przycisku BUlubione. Ponadto tworzy po��czenie
      sygna�u triggered utworzonej akcji menu ze slotem w niej si� znajduj�cym,
      aby ten slot m�g� nada� sygna� z dodatkowym parametrem go identyfikuj�cym.
      Nast�pnie tworzy po��czenie w.w. sygna�u z parametrem ze slotem
      znajduj�cym si� w fsystem, celem wykonania odpowiedniej funkcji
      (np. dodanie nowego ulubionego, wybranie ulubionego, usuniecie itd.).
      */
    void dodajUlubiony(std::wstring s);

    /**
      @brief Slot, usuwaj�cy ulubiony.
      @param nazwa usuwanego ulubionego

      Usuwa akcj� z menuUlubione.
      */
    void usunUlubione(std::wstring szukany);

    /**
      @brief Slot, usuwaj�cy ulubiony.
      @param nazwa usuwanego ulubionego

      Usuwa akcj� z menuUlubione.
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
      Wska�nik na instancje g��wnej klasy steruj�cej.
      */
    FileSystemController* fsystem;

    /**
      Pomocniczo przetrzymywany wska�nik na menuUlubione celem
      �atwiejszej aktualizcji tego menu.
      */
    QMenu* menuUlubione;



    /**
    * @brief aktualny status dzialania (czy przegladarka czy manager plikow): true-przegladarka www, false-manager plikow
    */
    bool ifWwwOn;


};

#endif // MAINWINDOW_H
