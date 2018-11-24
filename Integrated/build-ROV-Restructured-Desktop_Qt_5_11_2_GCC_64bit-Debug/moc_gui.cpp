/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ROV-Restructured/gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gui_t {
    QByteArrayData data[12];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gui_t qt_meta_stringdata_gui = {
    {
QT_MOC_LITERAL(0, 0, 3), // "gui"
QT_MOC_LITERAL(1, 4, 10), // "pause_play"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 13), // "buttonsConfig"
QT_MOC_LITERAL(4, 30, 13), // "Configuration"
QT_MOC_LITERAL(5, 44, 11), // "changeInGUI"
QT_MOC_LITERAL(6, 56, 6), // "button"
QT_MOC_LITERAL(7, 63, 26), // "changeButtonsConfiguration"
QT_MOC_LITERAL(8, 90, 9), // "newConfig"
QT_MOC_LITERAL(9, 100, 12), // "toggleCamera"
QT_MOC_LITERAL(10, 113, 5), // "print"
QT_MOC_LITERAL(11, 119, 17) // "prepButtonsConfig"

    },
    "gui\0pause_play\0\0buttonsConfig\0"
    "Configuration\0changeInGUI\0button\0"
    "changeButtonsConfiguration\0newConfig\0"
    "toggleCamera\0print\0prepButtonsConfig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,
      10,    0,   60,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gui *_t = static_cast<gui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pause_play(); break;
        case 1: _t->buttonsConfig((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->changeInGUI((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changeButtonsConfiguration((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->toggleCamera(); break;
        case 5: _t->print(); break;
        case 6: _t->prepButtonsConfig(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gui::pause_play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gui::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gui::buttonsConfig)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gui::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_gui.data,
      qt_meta_data_gui,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gui.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void gui::pause_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void gui::buttonsConfig(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
