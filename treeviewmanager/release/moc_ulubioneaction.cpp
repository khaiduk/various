/****************************************************************************
** Meta object code from reading C++ file 'ulubioneaction.h'
**
** Created: Sun 16. Sep 23:31:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ulubioneaction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ulubioneaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UlubioneAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UlubioneAction[] = {
    "UlubioneAction\0\0sygnalUlubione(std::wstring)\0"
    "przeslijDalej()\0"
};

void UlubioneAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UlubioneAction *_t = static_cast<UlubioneAction *>(_o);
        switch (_id) {
        case 0: _t->sygnalUlubione((*reinterpret_cast< std::wstring(*)>(_a[1]))); break;
        case 1: _t->przeslijDalej(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UlubioneAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UlubioneAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_UlubioneAction,
      qt_meta_data_UlubioneAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UlubioneAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UlubioneAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UlubioneAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UlubioneAction))
        return static_cast<void*>(const_cast< UlubioneAction*>(this));
    return QAction::qt_metacast(_clname);
}

int UlubioneAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void UlubioneAction::sygnalUlubione(std::wstring _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
