/****************************************************************************
** Meta object code from reading C++ file 'mysqlplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mysqlplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mysqlplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MysqlDBPlugin_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MysqlDBPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MysqlDBPlugin_t qt_meta_stringdata_MysqlDBPlugin = {
    {
QT_MOC_LITERAL(0, 0, 13) // "MysqlDBPlugin"

    },
    "MysqlDBPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MysqlDBPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MysqlDBPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MysqlDBPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MysqlDBPlugin.data,
      qt_meta_data_MysqlDBPlugin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MysqlDBPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MysqlDBPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MysqlDBPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IMysqlDB"))
        return static_cast< IMysqlDB*>(this);
    if (!strcmp(_clname, "28654FD1-36F1-468E-8CC8-5BDCF9A2D3F2"))
        return static_cast< IMysqlDB*>(this);
    return QObject::qt_metacast(_clname);
}

int MysqlDBPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xc8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xb4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, '2',  '8',  '6',  '5',  '4',  'F', 
    'D',  '1',  '-',  '3',  '6',  'F',  '1',  '-', 
    '4',  '6',  '8',  'E',  '-',  '8',  'C',  'C', 
    '8',  '-',  '5',  'B',  'D',  'C',  'F',  '9', 
    'A',  '2',  'D',  '3',  'F',  '2',  0x00, 0x00,
    0x1b, 0x0a, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0d, 0x00, 'M',  'y',  's',  'q',  'l',  'D', 
    'B',  'P',  'l',  'u',  'g',  'i',  'n',  0x00,
    ':',  '@',  0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x11, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, '$',  0x00, 0x00, 0x00,
    0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 'K',  'e', 
    'y',  's',  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '|',  0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, '`',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xc8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xb4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '$',  0x00, '2',  '8',  '6',  '5',  '4',  'F', 
    'D',  '1',  '-',  '3',  '6',  'F',  '1',  '-', 
    '4',  '6',  '8',  'E',  '-',  '8',  'C',  'C', 
    '8',  '-',  '5',  'B',  'D',  'C',  'F',  '9', 
    'A',  '2',  'D',  '3',  'F',  '2',  0x00, 0x00,
    0x15, 0x0a, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    '(',  0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    '$',  0x00, 0x00, 0x00, 0x14, 0x03, 0x00, 0x00,
    0x04, 0x00, 'K',  'e',  'y',  's',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x1b, 0x11, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0d, 0x00, 'M',  'y',  's',  'q',  'l',  'D', 
    'B',  'P',  'l',  'u',  'g',  'i',  'n',  0x00,
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, ':',  '@',  0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, 'x',  0x00, 0x00, 0x00,
    0x98, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(MysqlDBPlugin, MysqlDBPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
