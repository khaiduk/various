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
    /// Sygna³ - zmiana bie¿¹cego katalogu
    void directoryChanged(FileSystem::Path dir);
    /// Sygna³ - próba otwarcia pliku
    void openFile(FileSystem::Path dir);
    /// Sygna³ - zaznaczenie elementów
    void selectedElements(std::vector<FileSystem::Path> dir);
    
public slots:
    /// ustawia katalog
    void setDirectory(FileSystem::Path dir);
    /// ustawia sposób wyœwietlania
    void setStyle(const TreeViewStyle& style);

protected:
    /// Zdarzenie - rysowanie obiektu
    void paintEvent(QPaintEvent *event);
    /// Zdarzenie - u¿ycie kó³ka myszy
    void wheelEvent(QWheelEvent *event);
    /// Zdarzenie - przesuniêcie myszy
    void mouseMoveEvent(QMouseEvent *event);
    /// Zdarzenie - wciœniêcie przycisku myszy
    void mousePressEvent(QMouseEvent *event);
    /// Zdarzenie - pusczenie przycisku myszy
    void mouseReleaseEvent(QMouseEvent *event);
    /// Zdarzenie - dwukrotne klikniecie mysz¹
    void mouseDoubleClickEvent(QMouseEvent *event);
    /// Ustawia bie¿¹cy element ze wzglêdu na po³o¿enie widoku
    void updateCurrentElement();

    /// Prostok¹t reprezentuj¹cy korzeñ drzewa wzglêdem widoku
    QRectF _rootRect;

    /// Czy jesteœmy w trakcie zaznaczania
    bool _currentlySelecting;
    /// Obszar zaznaczania
    QPainterPath _selectionPath;

    /// Aktualnie aktywny element drzewa
    TreeViewElement* _active;

    /// Korzeñ drzewa
    TreeViewElement* _root;

    /// Element bie¿¹cy
    TreeViewElement* _current;

    /// Elementy zaznaczone
    std::set<TreeViewElement*> _selected;

    /// Ostatnie znane po³o¿enie kursora
    QPoint prevpos;

    TreeViewStyle _style;
    
};

#endif // TREEVIEW_H
