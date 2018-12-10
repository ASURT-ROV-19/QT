/****************************************************************************
** Meta object code from reading C++ file 'joystickbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ROV-Restructured/joystickbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joystickbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_joystickButton_t {
    QByteArrayData data[9];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_joystickButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_joystickButton_t qt_meta_stringdata_joystickButton = {
    {
QT_MOC_LITERAL(0, 0, 14), // "joystickButton"
QT_MOC_LITERAL(1, 15, 18), // "initialDisplaySign"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "thisClicked"
QT_MOC_LITERAL(4, 47, 16), // "joystickButton**"
QT_MOC_LITERAL(5, 64, 10), // "joyButtons"
QT_MOC_LITERAL(6, 75, 12), // "adminButtons"
QT_MOC_LITERAL(7, 88, 14), // "QRadioButton**"
QT_MOC_LITERAL(8, 103, 16) // "selectionButtons"

    },
    "joystickButton\0initialDisplaySign\0\0"
    "thisClicked\0joystickButton**\0joyButtons\0"
    "adminButtons\0QRadioButton**\0"
    "selectionButtons"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_joystickButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 7,    5,    6,    8,

       0        // eod
};

void joystickButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        joystickButton *_t = static_cast<joystickButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initialDisplaySign(); break;
        case 1: _t->thisClicked((*reinterpret_cast< joystickButton**(*)>(_a[1])),(*reinterpret_cast< joystickButton**(*)>(_a[2])),(*reinterpret_cast< QRadioButton**(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (joystickButton::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&joystickButton::initialDisplaySign)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject joystickButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_joystickButton.data,
      qt_meta_data_joystickButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *joystickButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *joystickButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_joystickButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int joystickButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void joystickButton::initialDisplaySign()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
