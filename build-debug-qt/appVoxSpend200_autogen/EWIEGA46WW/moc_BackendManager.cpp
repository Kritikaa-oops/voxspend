/****************************************************************************
** Meta object code from reading C++ file 'BackendManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BackendManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BackendManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
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
struct qt_meta_tag_ZN14BackendManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto BackendManager::qt_create_metaobjectdata<qt_meta_tag_ZN14BackendManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BackendManager",
        "dataChanged",
        "",
        "login",
        "email",
        "password",
        "signup",
        "name",
        "confirmPassword",
        "getLastAuthError",
        "clearAuthError",
        "isDatabaseReady",
        "currentUserName",
        "currentUserEmail",
        "logout",
        "updateProfile",
        "addExpense",
        "title",
        "amount",
        "category",
        "date",
        "note",
        "getLastExpenseError",
        "clearExpenseError",
        "getExpenses",
        "QVariantList",
        "getCategoryTotals",
        "getMonthlyTotal",
        "getExpenseCount",
        "dataRevision"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'dataChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'login'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 4 }, { QMetaType::QString, 5 },
        }}),
        // Method 'signup'
        QtMocHelpers::MethodData<bool(const QString &, const QString &, const QString &, const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 4 }, { QMetaType::QString, 5 }, { QMetaType::QString, 8 },
        }}),
        // Method 'getLastAuthError'
        QtMocHelpers::MethodData<QString() const>(9, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'clearAuthError'
        QtMocHelpers::MethodData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'isDatabaseReady'
        QtMocHelpers::MethodData<bool() const>(11, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'currentUserName'
        QtMocHelpers::MethodData<QString() const>(12, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'currentUserEmail'
        QtMocHelpers::MethodData<QString() const>(13, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'updateProfile'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 4 },
        }}),
        // Method 'addExpense'
        QtMocHelpers::MethodData<bool(const QString &, double, const QString &, const QString &, const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 17 }, { QMetaType::Double, 18 }, { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
            { QMetaType::QString, 21 },
        }}),
        // Method 'getLastExpenseError'
        QtMocHelpers::MethodData<QString()>(22, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'clearExpenseError'
        QtMocHelpers::MethodData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getExpenses'
        QtMocHelpers::MethodData<QVariantList() const>(24, 2, QMC::AccessPublic, 0x80000000 | 25),
        // Method 'getCategoryTotals'
        QtMocHelpers::MethodData<QVariantList() const>(26, 2, QMC::AccessPublic, 0x80000000 | 25),
        // Method 'getMonthlyTotal'
        QtMocHelpers::MethodData<double() const>(27, 2, QMC::AccessPublic, QMetaType::Double),
        // Method 'getExpenseCount'
        QtMocHelpers::MethodData<int() const>(28, 2, QMC::AccessPublic, QMetaType::Int),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'dataRevision'
        QtMocHelpers::PropertyData<int>(29, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BackendManager, qt_meta_tag_ZN14BackendManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BackendManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BackendManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BackendManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14BackendManagerE_t>.metaTypes,
    nullptr
} };

void BackendManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BackendManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: { bool _r = _t->login((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->signup((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->getLastAuthError();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->clearAuthError(); break;
        case 5: { bool _r = _t->isDatabaseReady();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->currentUserName();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->currentUserEmail();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->logout(); break;
        case 9: { bool _r = _t->updateProfile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->addExpense((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getLastExpenseError();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->clearExpenseError(); break;
        case 13: { QVariantList _r = _t->getExpenses();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->getCategoryTotals();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 15: { double _r = _t->getMonthlyTotal();
            if (_a[0]) *reinterpret_cast<double*>(_a[0]) = std::move(_r); }  break;
        case 16: { int _r = _t->getExpenseCount();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BackendManager::*)()>(_a, &BackendManager::dataChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->dataRevision(); break;
        default: break;
        }
    }
}

const QMetaObject *BackendManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackendManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14BackendManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackendManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void BackendManager::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
