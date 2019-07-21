/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[17];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 35), // "on_pushButton_configConfirm_c..."
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 28), // "on_pushButton_upload_clicked"
QT_MOC_LITERAL(4, 73, 34), // "on_pushButton_configCancel_cl..."
QT_MOC_LITERAL(5, 108, 6), // "upload"
QT_MOC_LITERAL(6, 115, 8), // "fileType"
QT_MOC_LITERAL(7, 124, 3), // "url"
QT_MOC_LITERAL(8, 128, 4), // "data"
QT_MOC_LITERAL(9, 133, 13), // "replyFinished"
QT_MOC_LITERAL(10, 147, 14), // "QNetworkReply*"
QT_MOC_LITERAL(11, 162, 5), // "reply"
QT_MOC_LITERAL(12, 168, 6), // "addLog"
QT_MOC_LITERAL(13, 175, 6), // "logStr"
QT_MOC_LITERAL(14, 182, 18), // "setNewFileNewInXml"
QT_MOC_LITERAL(15, 201, 8), // "FileType"
QT_MOC_LITERAL(16, 210, 10) // "updateTime"

    },
    "Widget\0on_pushButton_configConfirm_clicked\0"
    "\0on_pushButton_upload_clicked\0"
    "on_pushButton_configCancel_clicked\0"
    "upload\0fileType\0url\0data\0replyFinished\0"
    "QNetworkReply*\0reply\0addLog\0logStr\0"
    "setNewFileNewInXml\0FileType\0updateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    3,   52,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,
      12,    1,   62,    2, 0x08 /* Private */,
      14,    2,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::QUrl, QMetaType::QByteArray,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString,   15,   16,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_configConfirm_clicked(); break;
        case 1: _t->on_pushButton_upload_clicked(); break;
        case 2: _t->on_pushButton_configCancel_clicked(); break;
        case 3: _t->upload((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QUrl(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 4: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->addLog((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: _t->setNewFileNewInXml((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
struct qt_meta_stringdata_FTPUpload_t {
    QByteArrayData data[11];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FTPUpload_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FTPUpload_t qt_meta_stringdata_FTPUpload = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FTPUpload"
QT_MOC_LITERAL(1, 10, 6), // "upload"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "fileType"
QT_MOC_LITERAL(4, 27, 3), // "url"
QT_MOC_LITERAL(5, 31, 4), // "data"
QT_MOC_LITERAL(6, 36, 11), // "newFileTime"
QT_MOC_LITERAL(7, 48, 8), // "FileType"
QT_MOC_LITERAL(8, 57, 10), // "updateTime"
QT_MOC_LITERAL(9, 68, 6), // "addLog"
QT_MOC_LITERAL(10, 75, 6) // "logStr"

    },
    "FTPUpload\0upload\0\0fileType\0url\0data\0"
    "newFileTime\0FileType\0updateTime\0addLog\0"
    "logStr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FTPUpload[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       6,    2,   36,    2, 0x06 /* Public */,
       9,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::QUrl, QMetaType::QByteArray,    3,    4,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QStringList,   10,

       0        // eod
};

void FTPUpload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FTPUpload *_t = static_cast<FTPUpload *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upload((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QUrl(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 1: _t->newFileTime((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->addLog((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (FTPUpload::*_t)(quint8 , const QUrl & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FTPUpload::upload)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FTPUpload::*_t)(quint8 , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FTPUpload::newFileTime)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FTPUpload::*_t)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FTPUpload::addLog)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FTPUpload::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FTPUpload.data,
      qt_meta_data_FTPUpload,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FTPUpload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FTPUpload::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FTPUpload.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int FTPUpload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void FTPUpload::upload(quint8 _t1, const QUrl & _t2, const QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FTPUpload::newFileTime(quint8 _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FTPUpload::addLog(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
