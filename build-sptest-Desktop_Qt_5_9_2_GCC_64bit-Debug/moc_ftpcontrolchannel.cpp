/****************************************************************************
** Meta object code from reading C++ file 'ftpcontrolchannel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sptest/ftpcontrolchannel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ftpcontrolchannel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FtpControlChannel_t {
    QByteArrayData data[12];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FtpControlChannel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FtpControlChannel_t qt_meta_stringdata_FtpControlChannel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FtpControlChannel"
QT_MOC_LITERAL(1, 18, 6), // "opened"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "QHostAddress"
QT_MOC_LITERAL(4, 39, 12), // "localAddress"
QT_MOC_LITERAL(5, 52, 9), // "localPort"
QT_MOC_LITERAL(6, 62, 6), // "closed"
QT_MOC_LITERAL(7, 69, 4), // "info"
QT_MOC_LITERAL(8, 74, 5), // "reply"
QT_MOC_LITERAL(9, 80, 4), // "code"
QT_MOC_LITERAL(10, 85, 10), // "parameters"
QT_MOC_LITERAL(11, 96, 12) // "invalidReply"

    },
    "FtpControlChannel\0opened\0\0QHostAddress\0"
    "localAddress\0localPort\0closed\0info\0"
    "reply\0code\0parameters\0invalidReply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FtpControlChannel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       6,    0,   44,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,
       8,    2,   48,    2, 0x06 /* Public */,
      11,    1,   53,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    9,   10,
    QMetaType::Void, QMetaType::QByteArray,    8,

       0        // eod
};

void FtpControlChannel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FtpControlChannel *_t = static_cast<FtpControlChannel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->opened((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->closed(); break;
        case 2: _t->info((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->reply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 4: _t->invalidReply((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FtpControlChannel::*_t)(const QHostAddress & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FtpControlChannel::opened)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FtpControlChannel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FtpControlChannel::closed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FtpControlChannel::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FtpControlChannel::info)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (FtpControlChannel::*_t)(int , const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FtpControlChannel::reply)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (FtpControlChannel::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FtpControlChannel::invalidReply)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject FtpControlChannel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FtpControlChannel.data,
      qt_meta_data_FtpControlChannel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FtpControlChannel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FtpControlChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FtpControlChannel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FtpControlChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FtpControlChannel::opened(const QHostAddress & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FtpControlChannel::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FtpControlChannel::info(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FtpControlChannel::reply(int _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FtpControlChannel::invalidReply(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
