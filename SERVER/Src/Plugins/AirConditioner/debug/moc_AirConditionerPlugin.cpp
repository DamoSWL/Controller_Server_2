/****************************************************************************
** Meta object code from reading C++ file 'AirConditionerPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AirConditionerPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AirConditionerPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AirConditonerPlugin_t {
    QByteArrayData data[4];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AirConditonerPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AirConditonerPlugin_t qt_meta_stringdata_AirConditonerPlugin = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AirConditonerPlugin"
QT_MOC_LITERAL(1, 20, 20), // "readPendingDatagrams"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17) // "onResponseTimeout"

    },
    "AirConditonerPlugin\0readPendingDatagrams\0"
    "\0onResponseTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AirConditonerPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AirConditonerPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AirConditonerPlugin *_t = static_cast<AirConditonerPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readPendingDatagrams(); break;
        case 1: _t->onResponseTimeout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AirConditonerPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AirConditonerPlugin.data,
      qt_meta_data_AirConditonerPlugin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AirConditonerPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AirConditonerPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AirConditonerPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IAirConditioner"))
        return static_cast< IAirConditioner*>(this);
    if (!strcmp(_clname, "DD2184E4-1C78-4ADC-A7AD-274146762C4C"))
        return static_cast< IAirConditioner*>(this);
    return QObject::qt_metacast(_clname);
}

int AirConditonerPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xd0, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xbc, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, 'D',  'D',  '2',  '1',  '8',  '4', 
    'E',  '4',  '-',  '1',  'C',  '7',  '8',  '-', 
    '4',  'A',  'D',  'C',  '-',  'A',  '7',  'A', 
    'D',  '-',  '2',  '7',  '4',  '1',  '4',  '6', 
    '7',  '6',  '2',  'C',  '4',  'C',  0x00, 0x00,
    0x1b, 0x0a, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x13, 0x00, 'A',  'i',  'r',  'C',  'o',  'n', 
    'd',  'i',  't',  'o',  'n',  'e',  'r',  'P', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    ':',  '@',  0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x12, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, '$',  0x00, 0x00, 0x00,
    0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 'K',  'e', 
    'y',  's',  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x84, 0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    'x',  0x00, 0x00, 0x00, 'h',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xd0, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xbc, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, 'D',  'D',  '2',  '1',  '8',  '4', 
    'E',  '4',  '-',  '1',  'C',  '7',  '8',  '-', 
    '4',  'A',  'D',  'C',  '-',  'A',  '7',  'A', 
    'D',  '-',  '2',  '7',  '4',  '1',  '4',  '6', 
    '7',  '6',  '2',  'C',  '4',  'C',  0x00, 0x00,
    0x15, 0x0a, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    '$',  0x00, 0x00, 0x00, 0x14, 0x03, 0x00, 0x00,
    0x04, 0x00, 'K',  'e',  'y',  's',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x1b, 0x11, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x13, 0x00, 'A',  'i',  'r',  'C',  'o',  'n', 
    'd',  'i',  't',  'o',  'n',  'e',  'r',  'P', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, ':',  '@',  0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, 'x',  0x00, 0x00, 0x00,
    0xa0, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(AirConditonerPlugin, AirConditonerPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
