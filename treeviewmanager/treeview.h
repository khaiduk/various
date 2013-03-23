#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QWheelEvent>
#include "treeviewelement.h"
#include "treeviewstyle.h"
#include <set>

/// Klasa widoku drzewa
class TreeView : public QWidget
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = 0);
    ~TreeView();
    
signals:
    /// Sygna� - zmiana bie��cego katalogu
    void directoryChanged(FileSystem::Path dir);
    /// Sygna� - pr�ba otwarcia pliku
    void openFile(FileSystem::Path dir);
    /// Sygna� - zaznaczenie element�w
    void selectedElements(std::vector<FileSystem::Path> dir);
    
public slots:
    /// ustawia katalog
    void setDirectory(FileSystem::Path dir);
    /// ustawia spos�b wy�wietlania
    void setStyle(const TreeViewStyle& style);

protected:
    /// Zdarzenie - rysowanie obiektu
    void paintEvent(QPaintEvent *event);
    /// Zdarzenie - u�ycie k�ka myszy
    void wheelEvent(QWheelEvent *event);
    /// Zdarzenie - przesuni�cie myszy
    void mouseMoveEvent(QMouseEvent *event);
    /// Zdarzenie - wci�ni�cie przycisku myszy
    void mousePressEvent(QMouseEvent *event);
    /// Zdarzenie - pusczenie przycisku myszy
    void mouseReleaseEvent(QMouseEvent *event);
    /// Zdarzenie - dwukrotne klikniecie mysz�
    void mouseDoubleClickEvent(QMouseEvent *event);
    /// Ustawia bie��cy element ze wzgl�du na po�o�enie widoku
    void updateCurrentElement();

    /// Prostok�t reprezentuj�cy korze� drzewa wzgl�dem widoku
    QRectF _rootRect;

    /// Czy jeste�my w trakcie zaznaczania
    bool _currentlySelecting;
    /// Obszar zaznaczania
    QPainterPath _selectionPath;

    /// Aktualnie aktywny element drzewa
    TreeViewElement* _active;

    /// Korze� drzewa
    TreeViewElement* _root;

    /// Element bie��cy
    TreeViewElement* _current;

    /// Elementy zaznaczone
    std::set<TreeViewElement*> _selected;

    /// Ostatnie znane po�o�enie kursora
    QPoint prevpos;

    TreeViewStyle _style;
    
};

#endif // TREEVIEW_H
