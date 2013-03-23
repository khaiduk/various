/****************************************************************************
** Meta object code from reading C++ file 'filesystemcontroller.h'
**
** Created: Mon 17. Sep 00:02:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filesystemcontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filesystemcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileSystemController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x05,
      51,   22,   21,   21, 0x05,
      83,   21,   21,   21, 0x05,
     117,   21,   21,   21, 0x05,
     154,  152,   21,   21, 0x05,
     183,   21,   21,   21, 0x05,
     211,   21,   21,   21, 0x05,
     227,   22,   21,   21, 0x05,
     245,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     258,   21,   21,   21, 0x0a,
     273,   21,   21,   21, 0x0a,
     286,   21,   21,   21, 0x0a,
     298,   21,   21,   21, 0x0a,
     310,   21,   21,   21, 0x0a,
     323,   21,   21,   21, 0x0a,
     336,   21,   21,   21, 0x0a,
     350,   21,   21,   21, 0x0a,
     366,  360,   21,   21, 0x0a,
     416,  410,   21,   21, 0x0a,
     449,   21,   21,   21, 0x0a,
     476,   21,   21,   21, 0x0a,
     499,   22,   21,   21, 0x0a,
     522,   21,   21,   21, 0x0a,
     540,   21,   21,   21, 0x0a,
     558,  554,   21,   21, 0x0a,
     588,  586,   21,   21, 0x0a,
     635,  624,   21,   21, 0x0a,
     662,   21,   21,   21, 0x0a,
     688,   21,   21,   21, 0x0a,
     712,   21,   21,   21, 0x0a,
     730,   21,   21,   21, 0x0a,
     745,   22,   21,   21, 0x0a,
     766,   22,   21,   21, 0x0a,
     788,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FileSystemController[] = {
    "FileSystemController\0\0s\0"
    "setStatusBarWMain(QString)\0"
    "dodanieUlubionego(std::wstring)\0"
    "usuniecieUlubionego(std::wstring)\0"
    "otwarcieKatalogu(FileSystem::Path)\0,\0"
    "zakomunikuj(QString,QString)\0"
    "styleChanged(TreeViewStyle)\0changeWWW(bool)\0"
    "setAdres(QString)\0odswiezWWW()\0"
    "otworzFolder()\0kopiujPlik()\0kasujPlik()\0"
    "wklejPlik()\0wytnijPlik()\0zmienNazwe()\0"
    "nowyKatalog()\0odswiez()\0nazwy\0"
    "zaznaczPliki(std::vector<FileSystem::Path>)\0"
    "nazwa\0aktywujKatalog(FileSystem::Path)\0"
    "poUtworzeniuGlownegoOkna()\0"
    "ustawKatalogStartowy()\0ulubione(std::wstring)\0"
    "wczytajUlubione()\0ustawKolory()\0kat\0"
    "otworzKatalog(std::wstring)\0p\0"
    "otworzZewnetrznie(FileSystem::Path)\0"
    "title,opis\0komunikat(QString,QString)\0"
    "wyslijStyl(TreeViewStyle)\0"
    "otworzKatalogStartowy()\0onWwwChange(bool)\0"
    "changeStatus()\0addToStatus(QString)\0"
    "rmFromStatus(QString)\0toWindows()\0"
};

void FileSystemController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileSystemController *_t = static_cast<FileSystemController *>(_o);
        switch (_id) {
        case 0: _t->setStatusBarWMain((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->dodanieUlubionego((*reinterpret_cast< std::wstring(*)>(_a[1]))); break;
        case 2: _t->usuniecieUlubionego((*reinterpret_cast< std::wstring(*)>(_a[1]))); break;
        case 3: _t->otwarcieKatalogu((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 4: _t->zakomunikuj((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->styleChanged((*reinterpret_cast< TreeViewStyle(*)>(_a[1]))); break;
        case 6: _t->changeWWW((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setAdres((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->odswiezWWW(); break;
        case 9: _t->otworzFolder(); break;
        case 10: _t->kopiujPlik(); break;
        case 11: _t->kasujPlik(); break;
        case 12: _t->wklejPlik(); break;
        case 13: _t->wytnijPlik(); break;
        case 14: _t->zmienNazwe(); break;
        case 15: _t->nowyKatalog(); break;
        case 16: _t->odswiez(); break;
        case 17: _t->zaznaczPliki((*reinterpret_cast< std::vector<FileSystem::Path>(*)>(_a[1]))); break;
        case 18: _t->aktywujKatalog((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 19: _t->poUtworzeniuGlownegoOkna(); break;
        case 20: _t->ustawKatalogStartowy(); break;
        case 21: _t->ulubione((*reinterpret_cast< std::wstring(*)>(_a[1]))); break;
        case 22: _t->wczytajUlubione(); break;
        case 23: _t->ustawKolory(); break;
        case 24: _t->otworzKatalog((*reinterpret_cast< std::wstring(*)>(_a[1]))); break;
        case 25: _t->otworzZewnetrznie((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 26: _t->komunikat((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 27: _t->wyslijStyl((*reinterpret_cast< TreeViewStyle(*)>(_a[1]))); break;
        case 28: _t->otworzKatalogStartowy(); break;
        case 29: _t->onWwwChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->changeStatus(); break;
        case 31: _t->addToStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: _t->rmFromStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->toWindows(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileSystemController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileSystemController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FileSystemController,
      qt_meta_data_FileSystemController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileSystemController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileSystemController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileSystemController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileSystemController))
        return static_cast<void*>(const_cast< FileSystemController*>(this));
    return QObject::qt_metacast(_clname);
}

int FileSystemController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void FileSystemController::setStatusBarWMain(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileSystemController::dodanieUlubionego(std::wstring _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileSystemController::usuniecieUlubionego(std::wstring _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileSystemController::otwarcieKatalogu(FileSystem::Path _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FileSystemController::zakomunikuj(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FileSystemController::styleChanged(TreeViewStyle _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FileSystemController::changeWWW(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FileSystemController::setAdres(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void FileSystemController::odswiezWWW()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
