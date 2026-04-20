#include "qpils_plumming.h"
#include "qpils_qobject_wrapper.h"
#include "qpils_converter.h"
#include "qpils_signal.h"
namespace PILS{

const Any *Plumcake::specialCalling(Runner &run, const QtObjectClassName &className, const Any &arg) const
{
    const Any *singleArg = &arg;
    const Any *const *args = &singleArg;
    size_t argc = 1;
    arg.isList(args, argc);
    QObject *object = className.createQObject(args, argc);
    if (object == nullptr)
        return nullptr;
    // No existing wrapper, but search anyway, for consistency with pils constant hashing
    QtObjectLookup lookup(object, &className);
    return lookup.lookup();
}

const Any *Plumcake::specialCalling(Runner &run, const QtObjectClassName &className) const
{
    return specialCalling(run, className, Empty::singleton);
}

const Any *QtObjectWrapper::specialCalling(Runner &run, const QtMethodName &method, const Any &arg) const
{
    const Any *singleArg = &arg;
    const Any *const *args = &singleArg;
    size_t argc = 1;
    arg.isList(args, argc);
    return invokeMethod(method, args, argc);
}

const Any *QtObjectWrapper::specialCalling(Runner &run, const QtMethodName &method) const
{
    return invokeMethod(method, nullptr, 0);
}

const Any *QtObjectWrapper::invokeMethod(const QtMethodName &name, const Any *const *args, size_t argc) const
{
    QObject* obj = object.data();
    if (!obj)
        return nullptr;
    const QMetaObject* meta = obj->metaObject();

    for (auto impl = name.implementationChain; impl; impl = impl->next)
    {
        if (!meta->inherits(impl->meta))
            continue;

        const Any* result = nullptr;

        if (!impl->invoker(obj, args, argc, result))
            continue;

        if (result)
            return result;

        retain();
        return this;
    }

    // const PilsString &nameString = *name.attributes[0]->as_String();
    // QByteArrayView methodName(nameString.value, nameString.count->value);
    // if (!obj)
    //     return nullptr;
    // int methodCount = meta->methodCount();
    // for (int i = 0; i < methodCount; ++i)
    // {
    //     QMetaMethod method = meta->method(i);
    //     auto tryMethod = method.name();
    //     if (method.methodType() != QMetaMethod::Method &&
    //         method.methodType() != QMetaMethod::Slot)
    //         continue;
    //     if (tryMethod != methodName)
    //         continue;
    //     QtMethodCallFrame callFrame(method);
    //     if (!callFrame.convertArguments(args, argc))
    //         continue;
    //     if (!callFrame.invoke(obj))
    //         continue;
    //     if (const Any *returnValue = callFrame.convertReturnValue())
    //         return returnValue;
    //     retain();
    //     return this;
    // }
    return nullptr;
}

// bool QtMethodCallFrame::convertArgument(
//     const Any* arg,
//     QMetaType target,
//     QtGenericArgumentWithStorage &ga)
// {
    // switch (target.id())
    // {
    // case QMetaType::Int:
    //     {
    //         if (const Integer *v = arg->as_Integer())
    //         {
    //             ga.int_ = v->value;
    //             ga.genericArgument = QGenericArgument("int", &ga.int_);
    //             return true;
    //         }
    //     }
    // case QMetaType::Double:
    //     {
    //         if (arg->isNumber(ga.double_))
    //         {
    //             ga.genericArgument = QGenericArgument("double", &ga.double_);
    //             return true;
    //         }
    //     }
    // case QMetaType::QString:
    //     {
    //         if (const PilsString *v = arg->as_String())
    //         {
    //             if (const PlatformDependentString *twin = v->getPlatformTwin())
    //             {
    //                 ga.genericArgument = QGenericArgument("QString", &twin->qString);
    //                 return true;
    //             }
    //         }
    //     }
    // case QMetaType::QObjectStar:
    //     {
    //         QtObjectArgumentConverter converter(ga);
    //         return arg->convert(converter);
    //     }
    // default:
    // return false;
    // }
// }

// bool QtMethodCallFrame::convertArguments(const Any* const* args, size_t argc)
// {
//     if (argc != size_t(method.parameterCount()))
//         return false;

//     for (int i = 0; i < int(argc); ++i)
//     {
//         QtArgumentConverter converter(gas[i], method.parameterMetaType(i));
//         if (!args[i]->convert(converter))
//             return false;
//     }
//     return true;
// }

// bool QtArgumentConverter::converting(const QtObjectWrapper &argument)
// {
//     if (type.id() != QMetaType::QObjectStar)
//         return false;
//     ga.obj = argument.object.data();
//     if (ga.obj == nullptr) return false;
//     ga.genericArgument = QGenericArgument("QObject*", &ga.obj);
//     return true;
// }

// bool QtMethodCallFrame::invoke(QObject* obj)
// {
//     return method.invoke(
//         obj,
//         Qt::DirectConnection,
//         returnArgument,
//         gas[0].genericArgument,
//         gas[1].genericArgument,
//         gas[2].genericArgument,
//         gas[3].genericArgument,
//         gas[4].genericArgument,
//         gas[5].genericArgument,
//         gas[6].genericArgument,
//         gas[7].genericArgument,
//         gas[8].genericArgument,
//         gas[9].genericArgument
//         );
// }

// const Any* QtMethodCallFrame::convertReturnValue() const
// {
//     if (returnType.id() == QMetaType::Void)
//         return nullptr;

//     switch (returnType.id())
//     {
//     case QMetaType::Int:
//         return Integer::get(*reinterpret_cast<const int*>(returnData));
//     case QMetaType::Double:
//         return Number::get(*reinterpret_cast<const double*>(returnData));
//     case QMetaType::Bool:
//         return Integer::get(*reinterpret_cast<const bool*>(returnData));

//     case QMetaType::QString:
//     {
//         const QString& s = *reinterpret_cast<const QString*>(returnData);
//         // kopi til PILS string (UTF-8)
//         QByteArray utf8 = s.toUtf8();
//         return PilsString::get(utf8.constData(), utf8.size());
//     }

//     case QMetaType::QByteArray:
//     {
//         const QByteArray& b =
//             *reinterpret_cast<const QByteArray*>(returnData);

//         return PilsString::get(b.constData(), b.size());
//     }

//     case QMetaType::QObjectStar:
//     {
//         QObject* obj = *reinterpret_cast<QObject* const*>(returnData);
//         return QtWrap::wrap(obj);
//     }

//     default:
//         break;
//     }

//     // --- fallback: prøv QObject* via QVariant-less tilgang ---
//     if (returnType.flags() & QMetaType::PointerToQObject)
//     {
//         QObject* obj =
//             *reinterpret_cast<QObject* const*>(returnData);

//         return QtWrap::wrap(obj);
//     }

//     // --- ukendt type ---
//     return nullptr;
// }

const ReallySpecial *QtObjectLookup::newSpecial(const Constant *&link)
{
    if (className)
        className->retain();
    else className = getClassNameFromQObject(object);
    return new const QtObjectWrapper(link, className, object);
}

const QtObjectClassName *QtObjectLookup::getClassNameFromQObject(QObject* object)
{
    const QMetaObject* meta = object->metaObject();
    QByteArray qtName(meta->className());
    const char* name = qtName.constData();
    const PilsString* pilsName = PilsString::get(name+(name[0] == 'Q'));
    Namespace_QtClass::singleton->retain();
    const ClicheShort *className = Namespace_QtClass::singleton->clichefy(pilsName);
    const QtObjectClassName* typedClassName = static_cast<const QtObjectClassName*>(className);
    typedClassName->meta = meta;
    return typedClassName;
}

bool QtObjectLookup::compare(const ReallySpecial &special) const
{
    return special.specialComparing(*this);
}

size_t QtObjectLookup::hash() const
{
    return std::hash<QObject*>{}(object);
}

const Step *QtObjectWrapper::calling(Runner &run, const Constant &call) const
{
    if (&call == &Builtin::name.mind)
    {
        if (run.isMainThread() && object.get() && mind)
        {
            const Express *what = run.calling.what;
            what->retain();
            return run.sink->pass(run, mind, what);
        }
    }
    return ReallySpecial::calling(run, call);
}

QtObjectWrapper::State QtObjectWrapper::computeCurrentState() const
{
    if (!object)
        return State::Deleted;
    if (object->parent())
        return State::Attached;
    return isTopLevelVisible(object) ? State::DetachedVisible
                                     : State::DetachedHidden;
}

bool QtObjectWrapper::isTopLevelVisible(QObject *obj) const
{
    if (auto w = qobject_cast<QWidget*>(obj))
        return w->isWindow() && w->isVisible();

    if (auto win = qobject_cast<QWindow*>(obj))
        return win->isVisible();
    return false;
}

void QtObjectWrapper::checkState() const
{
    State oldState = state;
    state = computeCurrentState();
    if (state == oldState) return;
    if (state == State::DetachedVisible) enableMind();
    else if (oldState == State::DetachedVisible) disableMind();
    switch (retainCount(state) - retainCount(oldState))
    {
    case 1: retain();
        break;
    case -1: release();
        break;
    default:
        break;
    }
}

int QtObjectWrapper::retainCount(State s)
{
    if (s == State::DetachedVisible || s == State::Attached)
        return 1;
    else return 0;
}

void QtObjectWrapper::enableMind() const
{
    assert(mind == nullptr);
    mind = new PassingMind(*this);
}

void QtObjectWrapper::disableMind() const
{
    assert(mind != nullptr);
    delete mind;
    mind = nullptr;
}

const Any *QtObjectWrapper::specialCalling(Runner &run, const Strap &strap) const
{
    if (mind)
        mind->stick(strap);
    retain();
    return this;
}

const Any *QtObjectWrapper::specialWhen(Runner &run, const Any &argument) const
{
    if (when)
    {
        retain();
        return this;
    }

    if (refcount.isMultipleReferenced(retainCount(state)))
        return nullptr;

    argument.retain();
    when = &argument;

    QtSignalClicheExtractor extractor;
    argument.convert(extractor);

    for (const QtSignalCliche* cliche : extractor.cliches)
    {
        for (auto implement = cliche->implementations; implement != nullptr; implement = implement->next)
            implement->connectIfCompatible(object.data(), const_cast<QtObjectWrapper*>(this), cliche);
    }

    retain();
    return this;
}

}
