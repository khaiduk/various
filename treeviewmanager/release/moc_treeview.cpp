/****************************************************************************
** Meta object code from reading C++ file 'treeview.h'
**
** Created: Sun 16. Sep 23:31:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../treeview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,
      49,   10,    9,    9, 0x05,
      76,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     124,   10,    9,    9, 0x0a,
     161,  155,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TreeView[] = {
    "TreeView\0\0dir\0directoryChanged(FileSystem::Path)\0"
    "openFile(FileSystem::Path)\0"
    "selectedElements(std::vector<FileSystem::Path>)\0"
    "setDirectory(FileSystem::Path)\0style\0"
    "setStyle(TreeViewStyle)\0"
};

void TreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TreeView *_t = static_cast<TreeView *>(_o);
        switch (_id) {
        case 0: _t->directoryChanged((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 1: _t->openFile((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 2: _t->selectedElements((*reinterpret_cast< std::vector<FileSystem::Path>(*)>(_a[1]))); break;
        case 3: _t->setDirectory((*reinterpret_cast< FileSystem::Path(*)>(_a[1]))); break;
        case 4: _t->setStyle((*reinterpret_cast< const TreeViewStyle(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TreeView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TreeView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TreeView,
      qt_meta_data_TreeView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeView))
        return static_cast<void*>(const_cast< TreeView*>(this));
    return QWidget::qt_metacast(_clname);
}

int TreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TreeView::directoryChanged(FileSystem::Path _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TreeView::openFile(FileSystem::Path _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TreeView::selectedElements(std::vector<FileSystem::Path> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
