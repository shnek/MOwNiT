/****************************************************************************
** Meta object code from reading C++ file 'svgview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../projekt3/svgview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svgview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SvgView_t {
    QByteArrayData data[7];
    char stringdata[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SvgView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SvgView_t qt_meta_stringdata_SvgView = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 26),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 23),
QT_MOC_LITERAL(4, 60, 17),
QT_MOC_LITERAL(5, 78, 6),
QT_MOC_LITERAL(6, 85, 14)
    },
    "SvgView\0setHighQualityAntialiasing\0\0"
    "highQualityAntialiasing\0setViewBackground\0"
    "enable\0setViewOutline\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SvgView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       4,    1,   32,    2, 0x0a,
       6,    1,   35,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,

       0        // eod
};

void SvgView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SvgView *_t = static_cast<SvgView *>(_o);
        switch (_id) {
        case 0: _t->setHighQualityAntialiasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setViewBackground((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setViewOutline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SvgView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_SvgView.data,
      qt_meta_data_SvgView,  qt_static_metacall, 0, 0}
};


const QMetaObject *SvgView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SvgView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SvgView.stringdata))
        return static_cast<void*>(const_cast< SvgView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int SvgView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
