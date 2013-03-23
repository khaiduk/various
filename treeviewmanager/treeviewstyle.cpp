#include "treeviewstyle.h"

TreeViewStyle::TreeViewStyle(QFont f, QColor n, QColor a, QColor w , QColor z):
    font(f),nieaktywny(n), aktywny(a),wybrany(w), zaznaczony(z)
{
}

int TreeViewStyle::getPixelSize()
{
    return font.pixelSize();
}

std::wstring TreeViewStyle::toString()
{
    QString ss=font.toString()+'$'+nieaktywny.name()+'$'+aktywny.name()+'$'+wybrany.name()+'$'+zaznaczony.name();
    return ss.toStdWString();
}


TreeViewStyle TreeViewStyle::fromString(std::wstring s)
{

    TreeViewStyle styl;
    std::wstringstream ss;
    std::wstring ws;
    ss<<s;
    std::getline(ss,ws,L'$');
    QString qs;

    qs=QString::fromStdWString(ws);
    styl.font.fromString(qs);

    std::getline(ss,ws,L'$');
    qs=QString::fromStdWString(ws);
    styl.nieaktywny=QColor(qs);

    std::getline(ss,ws,L'$');
    qs=QString::fromStdWString(ws);
    styl.aktywny=QColor(qs);

    std::getline(ss,ws,L'$');
    qs=QString::fromStdWString(ws);
    styl.wybrany=QColor(qs);

    std::getline(ss,ws);
    qs=QString::fromStdWString(ws);
    styl.zaznaczony=QColor(qs);

    return styl;
}
