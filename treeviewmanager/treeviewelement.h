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
    /// sposób podœwietlania elementu
    enum HighlightStyle { inactive, active, current, selected };
public:
    /// Tworzy element do korzenia - wszystkich dysków
    TreeViewElement();
    /// Tworzy element do obiektu o œcie¿ce path
    TreeViewElement(const FileSystem::Path& path, int depth = 0);
    ~TreeViewElement();
    /// Rysuje element
    /// painter - obiekt QPainter za pomoc¹ którego bêdzie rysowany element
    /// style - styl wyœwietlania elementu
    /// rect - pozycja obiektu bezpoœrednio nadrzêdnego
    /// view - pozycja widoku
    /// depth - g³êbokoœæ wyœwietlania
    void draw(QPainter& painter, TreeViewStyle &style, const QRect &rect, const QRect& view, const int depth);
    /// Ustawia sposób podœwietlania
    void setHighlight(HighlightStyle hightlight);
    /// Kasuje podœwietlanie
    void resetHighlight();
    /// Zwraca wskaŸnik do elementu pod punktem p, jeœli takiego nie ma - zwaca NULL
    /// p - punkt w uk³adzie widoku
    /// depth - maksymalna glêbokoœæ wzglêdna
    TreeViewElement* getUnder(QPoint p, int depth);
    /// Zwraca wskaŸnik do podelementu o danej scie¿ca
    /// Jeœli taki element nie istnieje - zwraca null
    TreeViewElement* getSub(FileSystem::Path path);
    /// Zwraca œcie¿kê do skoja¿onego elementu systemu plików
    FileSystem::Path getPath();
    /// Zwraca bie¿¹ce po³o¿enie wzglêdem widoku
    QRect getCurrentRect();
    /// Zwraca element nadrzêdny
    TreeViewElement* getParent();
    /// Wype³nia dany element do okna
    /// root - pozycja korzenia - ulega zmianie
    /// view - pozycja widoku
    void fillToRect(QRectF& root, const QRect& view) const;
    /// £aduje zawartoœæ folderu
    void loadContents();

protected:
    /// Rozmieszcza zawartoœæ elementu
    void placeContents();
    /// G³êbokoœæ wzglêdem korzenia
    int _depth;
    /// Sposób wyœwietlania
    HighlightStyle _highlight;
    /// Po³o¿enie wzglêdem widoku
    QRect _currentRect;
    /// Wzglêdne po³o¿enie w stosunku do obiektu bezpoœrednio nadrzêdnego
    QRectF _rect;
    /// WskaŸnik do skojarzonego elementu systemu plików
    FileSystem::Element* _element;
    /// Podelementy
    /// je¿eli element nie reprezentuje folderu - pozostaje puste
    vector<TreeViewElement*> _contents;
    /// Element rodzica
    TreeViewElement* _parent;
    /// true gdy ca³a zawartoœæ jest za³adowana
    bool _loaded;

    friend class TreeViewContentLoader;
};

#endif // TREEVIEWELEMENT_H
