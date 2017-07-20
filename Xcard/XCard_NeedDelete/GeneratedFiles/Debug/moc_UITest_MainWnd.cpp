/****************************************************************************
** Meta object code from reading C++ file 'UITest_MainWnd.h'
**
** Created: Tue Jun 6 17:42:15 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "StdAfx.h"
#include "../../UITest_MainWnd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UITest_MainWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CUITest_MainWnd[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      30,   16,   16,   16, 0x0a,
      42,   16,   16,   16, 0x0a,
      54,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CUITest_MainWnd[] = {
    "CUITest_MainWnd\0\0Slot_Start()\0Slot_Stop()\0"
    "Slot_Next()\0Slot_Pre()\0"
};

void CUITest_MainWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CUITest_MainWnd *_t = static_cast<CUITest_MainWnd *>(_o);
        switch (_id) {
        case 0: _t->Slot_Start(); break;
        case 1: _t->Slot_Stop(); break;
        case 2: _t->Slot_Next(); break;
        case 3: _t->Slot_Pre(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CUITest_MainWnd::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CUITest_MainWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CUITest_MainWnd,
      qt_meta_data_CUITest_MainWnd, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CUITest_MainWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CUITest_MainWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CUITest_MainWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUITest_MainWnd))
        return static_cast<void*>(const_cast< CUITest_MainWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int CUITest_MainWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
