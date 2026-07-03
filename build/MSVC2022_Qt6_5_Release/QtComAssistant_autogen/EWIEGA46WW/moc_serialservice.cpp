/****************************************************************************
** Meta object code from reading C++ file 'serialservice.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../serialservice.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSerialServiceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSerialServiceENDCLASS = QtMocHelpers::stringData(
    "SerialService",
    "dataReceived",
    "",
    "data",
    "dataSent",
    "portOpened",
    "name",
    "portClosed",
    "errorOccurred",
    "message",
    "open",
    "SerialConfig",
    "config",
    "close",
    "sendBytes",
    "setDtr",
    "on",
    "setRts",
    "setAutoReplyRules",
    "QList<std::pair<QByteArray,QByteArray>>",
    "rules",
    "autoReplyEnabled",
    "setAutoReplyEnabled",
    "enabled",
    "onReadyRead",
    "onErrorOccurred",
    "QSerialPort::SerialPortError",
    "error"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSerialServiceENDCLASS_t {
    uint offsetsAndSizes[56];
    char stringdata0[14];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[9];
    char stringdata5[11];
    char stringdata6[5];
    char stringdata7[11];
    char stringdata8[14];
    char stringdata9[8];
    char stringdata10[5];
    char stringdata11[13];
    char stringdata12[7];
    char stringdata13[6];
    char stringdata14[10];
    char stringdata15[7];
    char stringdata16[3];
    char stringdata17[7];
    char stringdata18[18];
    char stringdata19[40];
    char stringdata20[6];
    char stringdata21[17];
    char stringdata22[20];
    char stringdata23[8];
    char stringdata24[12];
    char stringdata25[16];
    char stringdata26[29];
    char stringdata27[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSerialServiceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSerialServiceENDCLASS_t qt_meta_stringdata_CLASSSerialServiceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "SerialService"
        QT_MOC_LITERAL(14, 12),  // "dataReceived"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 4),  // "data"
        QT_MOC_LITERAL(33, 8),  // "dataSent"
        QT_MOC_LITERAL(42, 10),  // "portOpened"
        QT_MOC_LITERAL(53, 4),  // "name"
        QT_MOC_LITERAL(58, 10),  // "portClosed"
        QT_MOC_LITERAL(69, 13),  // "errorOccurred"
        QT_MOC_LITERAL(83, 7),  // "message"
        QT_MOC_LITERAL(91, 4),  // "open"
        QT_MOC_LITERAL(96, 12),  // "SerialConfig"
        QT_MOC_LITERAL(109, 6),  // "config"
        QT_MOC_LITERAL(116, 5),  // "close"
        QT_MOC_LITERAL(122, 9),  // "sendBytes"
        QT_MOC_LITERAL(132, 6),  // "setDtr"
        QT_MOC_LITERAL(139, 2),  // "on"
        QT_MOC_LITERAL(142, 6),  // "setRts"
        QT_MOC_LITERAL(149, 17),  // "setAutoReplyRules"
        QT_MOC_LITERAL(167, 39),  // "QList<std::pair<QByteArray,QB..."
        QT_MOC_LITERAL(207, 5),  // "rules"
        QT_MOC_LITERAL(213, 16),  // "autoReplyEnabled"
        QT_MOC_LITERAL(230, 19),  // "setAutoReplyEnabled"
        QT_MOC_LITERAL(250, 7),  // "enabled"
        QT_MOC_LITERAL(258, 11),  // "onReadyRead"
        QT_MOC_LITERAL(270, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(286, 28),  // "QSerialPort::SerialPortError"
        QT_MOC_LITERAL(315, 5)   // "error"
    },
    "SerialService",
    "dataReceived",
    "",
    "data",
    "dataSent",
    "portOpened",
    "name",
    "portClosed",
    "errorOccurred",
    "message",
    "open",
    "SerialConfig",
    "config",
    "close",
    "sendBytes",
    "setDtr",
    "on",
    "setRts",
    "setAutoReplyRules",
    "QList<std::pair<QByteArray,QByteArray>>",
    "rules",
    "autoReplyEnabled",
    "setAutoReplyEnabled",
    "enabled",
    "onReadyRead",
    "onErrorOccurred",
    "QSerialPort::SerialPortError",
    "error"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSerialServiceENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  104,    2, 0x06,    1 /* Public */,
       4,    1,  107,    2, 0x06,    3 /* Public */,
       5,    1,  110,    2, 0x06,    5 /* Public */,
       7,    0,  113,    2, 0x06,    7 /* Public */,
       8,    1,  114,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  117,    2, 0x0a,   10 /* Public */,
      13,    0,  120,    2, 0x0a,   12 /* Public */,
      14,    1,  121,    2, 0x0a,   13 /* Public */,
      15,    1,  124,    2, 0x0a,   15 /* Public */,
      17,    1,  127,    2, 0x0a,   17 /* Public */,
      18,    1,  130,    2, 0x0a,   19 /* Public */,
      21,    0,  133,    2, 0x10a,   21 /* Public | MethodIsConst  */,
      22,    1,  134,    2, 0x0a,   22 /* Public */,
      24,    0,  137,    2, 0x08,   24 /* Private */,
      25,    1,  138,    2, 0x08,   25 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,

       0        // eod
};

Q_CONSTINIT const QMetaObject SerialService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSerialServiceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSerialServiceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSerialServiceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SerialService, std::true_type>,
        // method 'dataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'dataSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'portOpened'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'portClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'open'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const SerialConfig &, std::false_type>,
        // method 'close'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendBytes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'setDtr'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setRts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setAutoReplyRules'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<QPair<QByteArray,QByteArray>> &, std::false_type>,
        // method 'autoReplyEnabled'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setAutoReplyEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>
    >,
    nullptr
} };

void SerialService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->dataSent((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->portOpened((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->portClosed(); break;
        case 4: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->open((*reinterpret_cast< std::add_pointer_t<SerialConfig>>(_a[1]))); break;
        case 6: _t->close(); break;
        case 7: _t->sendBytes((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 8: _t->setDtr((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->setRts((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->setAutoReplyRules((*reinterpret_cast< std::add_pointer_t<QList<std::pair<QByteArray,QByteArray>>>>(_a[1]))); break;
        case 11: { bool _r = _t->autoReplyEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setAutoReplyEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->onReadyRead(); break;
        case 14: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialService::*)(const QByteArray & );
            if (_t _q_method = &SerialService::dataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialService::*)(const QByteArray & );
            if (_t _q_method = &SerialService::dataSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SerialService::*)(const QString & );
            if (_t _q_method = &SerialService::portOpened; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SerialService::*)();
            if (_t _q_method = &SerialService::portClosed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SerialService::*)(const QString & );
            if (_t _q_method = &SerialService::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *SerialService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSerialServiceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SerialService::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialService::dataSent(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SerialService::portOpened(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SerialService::portClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SerialService::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
