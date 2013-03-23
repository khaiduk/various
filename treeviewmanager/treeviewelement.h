#ifndef TREEVIEWELEMENT_H
#define TREEVIEWELEMENT_H

#include <QPainter>
//#include <dirent.h>
#include <QtConcurrentRun>
#include "FileSystem/FileSystem.h"
#include "treeviewstyle.h"

/// Pojedynczy element widoku drzewa
class TreeViewElement
{
public:
    /// spos�b pod�wietlania elementu
    enum HighlightStyle { inactive, active, current, selected };
public:
    /// Tworzy element do korzenia - wszystkich dysk�w
    TreeViewElement();
    /// Tworzy element do obiektu o �cie�ce path
    TreeViewElement(const FileSystem::Path& path, int depth = 0);
    ~TreeViewElement();
    /// Rysuje element
    /// painter - obiekt QPainter za pomoc� kt�rego b�dzie rysowany element
    /// style - styl wy�wietlania elementu
    /// rect - pozycja obiektu bezpo�rednio nadrz�dnego
    /// view - pozycja widoku
    /// depth - g��boko�� wy�wietlania
    void draw(QPainter& painter, TreeViewStyle &style, const QRect &rect, const QRect& view, const int depth);
    /// Ustawia spos�b pod�wietlania
    void setHighlight(HighlightStyle hightlight);
    /// Kasuje pod�wietlanie
    void resetHighlight();
    /// Zwraca wska�nik do elementu pod punktem p, je�li takiego nie ma - zwaca NULL
    /// p - punkt w uk�adzie widoku
    /// depth - maksymalna gl�boko�� wzgl�dna
    TreeViewElement* getUnder(QPoint p, int depth);
    /// Zwraca wska�nik do podelementu o danej scie�ca
    /// Je�li taki element nie istnieje - zwraca null
    TreeViewElement* getSub(FileSystem::Path path);
    /// Zwraca �cie�k� do skoja�onego elementu systemu plik�w
    FileSystem::Path getPath();
    /// Zwraca bie��ce po�o�enie wzgl�dem widoku
    QRect getCurrentRect();
    /// Zwraca element nadrz�dny
    TreeViewElement* getParent();
    /// Wype�nia dany element do okna
    /// root - pozycja korzenia - ulega zmianie
    /// view - pozycja widoku
    void fillToRect(QRectF& root, const QRect& view) const;
    /// �aduje zawarto�� folderu
    void loadContents();

protected:
    /// Rozmieszcza zawarto�� elementu
    void placeContents();
    /// G��boko�� wzgl�dem korzenia
    int _depth;
    /// Spos�b wy�wietlania
    HighlightStyle _highlight;
    /// Po�o�enie wzgl�dem widoku
    QRect _currentRect;
    /// Wzgl�dne po�o�enie w stosunku do obiektu bezpo�rednio nadrz�dnego
    QRectF _rect;
    /// Wska�nik do skojarzonego elementu systemu plik�w
    FileSystem::Element* _element;
    /// Podelementy
    /// je�eli element nie reprezentuje folderu - pozostaje puste
    vector<TreeViewElement*> _contents;
    /// Element rodzica
    TreeViewElement* _parent;
    /// true gdy ca�a zawarto�� jest za�adowana
    bool _loaded;

    friend class TreeViewContentLoader;
};

#endif // TREEVIEWELEMENT_H
