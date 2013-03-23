#include "ulubioneaction.h"

UlubioneAction::UlubioneAction(const QString& s, QObject *p):QAction(s, p),val(s.toStdWString())
{
    QObject::connect(this,SIGNAL(triggered()),this, SLOT(przeslijDalej()));

}

 std::wstring UlubioneAction::getVal()
 {
     return val;
 }

 void UlubioneAction::przeslijDalej()
 {
     emit sygnalUlubione(val);
 }
