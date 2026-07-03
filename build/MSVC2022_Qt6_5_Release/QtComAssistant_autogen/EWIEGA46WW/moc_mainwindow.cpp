/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onOpenCloseClicked",
    "",
    "onSend",
    "onDataReceived",
    "data",
    "onDataSent",
    "onPortOpened",
    "name",
    "onPortClosed",
    "onError",
    "message",
    "onTimedSendTick",
    "onKeywordHighlight",
    "onSaveClicked",
    "onFileSendClicked",
    "onCommandMenu",
    "onClearScreen",
    "refreshPortList"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[38];
    char stringdata0[11];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[15];
    char stringdata5[5];
    char stringdata6[11];
    char stringdata7[13];
    char stringdata8[5];
    char stringdata9[13];
    char stringdata10[8];
    char stringdata11[8];
    char stringdata12[16];
    char stringdata13[19];
    char stringdata14[14];
    char stringdata15[18];
    char stringdata16[14];
    char stringdata17[14];
    char stringdata18[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 18),  // "onOpenCloseClicked"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 6),  // "onSend"
        QT_MOC_LITERAL(38, 14),  // "onDataReceived"
        QT_MOC_LITERAL(53, 4),  // "data"
        QT_MOC_LITERAL(58, 10),  // "onDataSent"
        QT_MOC_LITERAL(69, 12),  // "onPortOpened"
        QT_MOC_LITERAL(82, 4),  // "name"
        QT_MOC_LITERAL(87, 12),  // "onPortClosed"
        QT_MOC_LITERAL(100, 7),  // "onError"
        QT_MOC_LITERAL(108, 7),  // "message"
        QT_MOC_LITERAL(116, 15),  // "onTimedSendTick"
        QT_MOC_LITERAL(132, 18),  // "onKeywordHighlight"
        QT_MOC_LITERAL(151, 13),  // "onSaveClicked"
        QT_MOC_LITERAL(165, 17),  // "onFileSendClicked"
        QT_MOC_LITERAL(183, 13),  // "onCommandMenu"
        QT_MOC_LITERAL(197, 13),  // "onClearScreen"
        QT_MOC_LITERAL(211, 15)   // "refreshPortList"
    },
    "MainWindow",
    "onOpenCloseClicked",
    "",
    "onSend",
    "onDataReceived",
    "data",
    "onDataSent",
    "onPortOpened",
    "name",
    "onPortClosed",
    "onError",
    "message",
    "onTimedSendTick",
    "onKeywordHighlight",
    "onSaveClicked",
    "onFileSendClicked",
    "onCommandMenu",
    "onClearScreen",
    "refreshPortList"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    1,  100,    2, 0x08,    3 /* Private */,
       6,    1,  103,    2, 0x08,    5 /* Private */,
       7,    1,  106,    2, 0x08,    7 /* Private */,
       9,    0,  109,    2, 0x08,    9 /* Private */,
      10,    1,  110,    2, 0x08,   10 /* Private */,
      12,    0,  113,    2, 0x08,   12 /* Private */,
      13,    0,  114,    2, 0x08,   13 /* Private */,
      14,    0,  115,    2, 0x08,   14 /* Private */,
      15,    0,  116,    2, 0x08,   15 /* Private */,
      16,    0,  117,    2, 0x08,   16 /* Private */,
      17,    0,  118,    2, 0x08,   17 /* Private */,
      18,    0,  119,    2, 0x08,   18 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onOpenCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'onDataSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'onPortOpened'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onPortClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onTimedSendTick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onKeywordHighlight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFileSendClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCommandMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearScreen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshPortList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onOpenCloseClicked(); break;
        case 1: _t->onSend(); break;
        case 2: _t->onDataReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->onDataSent((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 4: _t->onPortOpened((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onPortClosed(); break;
        case 6: _t->onError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onTimedSendTick(); break;
        case 8: _t->onKeywordHighlight(); break;
        case 9: _t->onSaveClicked(); break;
        case 10: _t->onFileSendClicked(); break;
        case 11: _t->onCommandMenu(); break;
        case 12: _t->onClearScreen(); break;
        case 13: _t->refreshPortList(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
