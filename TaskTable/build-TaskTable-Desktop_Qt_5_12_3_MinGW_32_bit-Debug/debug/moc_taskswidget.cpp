/****************************************************************************
** Meta object code from reading C++ file 'taskswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TaskTable/taskswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taskswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TasksWidget_t {
    QByteArrayData data[27];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TasksWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TasksWidget_t qt_meta_stringdata_TasksWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TasksWidget"
QT_MOC_LITERAL(1, 12, 16), // "selectionChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "QItemSelection"
QT_MOC_LITERAL(4, 45, 8), // "selected"
QT_MOC_LITERAL(5, 54, 10), // "finishTask"
QT_MOC_LITERAL(6, 65, 12), // "nSelectedRow"
QT_MOC_LITERAL(7, 78, 9), // "resetTask"
QT_MOC_LITERAL(8, 88, 9), // "startTask"
QT_MOC_LITERAL(9, 98, 18), // "start_or_pauseTask"
QT_MOC_LITERAL(10, 117, 11), // "rowSelected"
QT_MOC_LITERAL(11, 129, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 141, 5), // "index"
QT_MOC_LITERAL(13, 147, 18), // "showAddEntryDialog"
QT_MOC_LITERAL(14, 166, 8), // "addEntry"
QT_MOC_LITERAL(15, 175, 5), // "sName"
QT_MOC_LITERAL(16, 181, 8), // "uint32_t"
QT_MOC_LITERAL(17, 190, 8), // "priority"
QT_MOC_LITERAL(18, 199, 12), // "deadTimeDate"
QT_MOC_LITERAL(19, 212, 9), // "editEntry"
QT_MOC_LITERAL(20, 222, 11), // "removeEntry"
QT_MOC_LITERAL(21, 234, 13), // "selectionProc"
QT_MOC_LITERAL(22, 248, 17), // "disconnectButtons"
QT_MOC_LITERAL(23, 266, 13), // "enableButtons"
QT_MOC_LITERAL(24, 280, 14), // "disableButtons"
QT_MOC_LITERAL(25, 295, 23), // "setStartPauseButtonText"
QT_MOC_LITERAL(26, 319, 4) // "text"

    },
    "TasksWidget\0selectionChanged\0\0"
    "QItemSelection\0selected\0finishTask\0"
    "nSelectedRow\0resetTask\0startTask\0"
    "start_or_pauseTask\0rowSelected\0"
    "QModelIndex\0index\0showAddEntryDialog\0"
    "addEntry\0sName\0uint32_t\0priority\0"
    "deadTimeDate\0editEntry\0removeEntry\0"
    "selectionProc\0disconnectButtons\0"
    "enableButtons\0disableButtons\0"
    "setStartPauseButtonText\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TasksWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       7,    1,  100,    2, 0x06 /* Public */,
       8,    1,  103,    2, 0x06 /* Public */,
       9,    1,  106,    2, 0x06 /* Public */,
      10,    1,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  112,    2, 0x0a /* Public */,
      14,    3,  113,    2, 0x0a /* Public */,
      14,    2,  120,    2, 0x2a /* Public | MethodCloned */,
      19,    0,  125,    2, 0x0a /* Public */,
      20,    0,  126,    2, 0x0a /* Public */,
      21,    1,  127,    2, 0x0a /* Public */,
      22,    0,  130,    2, 0x0a /* Public */,
      23,    0,  131,    2, 0x0a /* Public */,
      24,    0,  132,    2, 0x0a /* Public */,
      25,    1,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16, QMetaType::QDateTime,   15,   17,   18,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16,   15,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,

       0        // eod
};

void TasksWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TasksWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1]))); break;
        case 1: _t->finishTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->resetTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->startTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->start_or_pauseTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->rowSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 6: _t->showAddEntryDialog(); break;
        case 7: _t->addEntry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< QDateTime(*)>(_a[3]))); break;
        case 8: _t->addEntry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2]))); break;
        case 9: _t->editEntry(); break;
        case 10: _t->removeEntry(); break;
        case 11: _t->selectionProc((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 12: _t->disconnectButtons(); break;
        case 13: _t->enableButtons(); break;
        case 14: _t->disableButtons(); break;
        case 15: _t->setStartPauseButtonText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TasksWidget::*)(const QItemSelection & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::selectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TasksWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::finishTask)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TasksWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::resetTask)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TasksWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::startTask)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TasksWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::start_or_pauseTask)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TasksWidget::*)(QModelIndex );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TasksWidget::rowSelected)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TasksWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TasksWidget.data,
    qt_meta_data_TasksWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TasksWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TasksWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TasksWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TasksWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void TasksWidget::selectionChanged(const QItemSelection & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TasksWidget::finishTask(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TasksWidget::resetTask(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TasksWidget::startTask(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TasksWidget::start_or_pauseTask(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TasksWidget::rowSelected(QModelIndex _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
