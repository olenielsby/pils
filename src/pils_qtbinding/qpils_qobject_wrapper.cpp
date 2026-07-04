#include "qpils_plumming.h"
#include "qpils_qobject_wrapper.h"
#include "qpils_converter.h"
#include "qpils_signal.h"
#include "qpils_event.h"
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
    return nullptr;
}

const ReallySpecial *QtObjectLookup::newSpecial(const Constant *&link)
{
    if (className)
        className->retain();
    else className = getClassNameFromQObjectInsideLock(object);
    return new const QtObjectWrapper(link, className, object);
}

const QtObjectClassName *QtObjectLookup::getClassNameFromQObjectInsideLock(QObject* object)
{
    const QMetaObject* meta = object->metaObject();
    QByteArray qtName(meta->className());
    const char* name = qtName.constData();
    const PilsString* pilsName = PilsString::getInsideLock(name+(name[0] == 'Q'));
    Namespace_QtClass::singleton->retain();
    const ClicheShort *className = Namespace_QtClass::singleton->clichefyInsideLock(pilsName);
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

bool QtObjectWrapper::converting(PlatformSpecificConverter &converter) const
{
    return converter.converting(*this);
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

// #ifndef NDEBUG
//     switch (oldState)
//     {
//     case State::Attached: std::fputc('a', stderr); break;
//     case State::Deleted: std::fputc('d', stderr); break;
//     case State::DetachedHidden: std::fputc('h', stderr); break;
//     case State::DetachedVisible: std::fputc('v', stderr); break;
//     }
//     std::fputc('-', stderr);
//     switch (state)
//     {
//     case State::Attached: std::fputc('a', stderr); break;
//     case State::Deleted: std::fputc('d', stderr); break;
//     case State::DetachedHidden: std::fputc('h', stderr); break;
//     case State::DetachedVisible: std::fputc('v', stderr); break;
//     }
//     className->writeToDebugOutput(10);
// #endif

    if (state == oldState) return;
    if (state == State::Deleted) removeWhen();
    else if (state == State::DetachedVisible) enableMind();
    else if (oldState == State::DetachedVisible) disableMind();

    switch (retainCount(state) - retainCount(oldState))
    {
    case 1: retain();
        break;
    case -1: release();
    case 0:
        break;
    default:
        assert(false && state == State::Deleted);
    }
}

void QtObjectWrapper::checkDeletedState() const
{
    retain();
    if (state != State::Deleted)
    {
        State oldState = state;
        state = State::Deleted;
        removeWhen();
        if (oldState == State::DetachedVisible) disableMind();
        if (retainCount(oldState) == 1) release();
    }
    release();
}

int QtObjectWrapper::retainCount(State s)
{
    if (
        // s == State::DetachedVisible ||
        s == State::Attached)
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
    auto gone = mind;
    mind = nullptr;
    delete gone;
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
    if (object.get() == nullptr || when != nullptr || refcount.isMultipleReferenced(retainCount(state)))
        return nullptr;
    assert(eventFilterProxy == nullptr);
    argument.retain();
    when = &argument;
    QtSignalEventClicheExtractor extractor;
    argument.convert(extractor);
    for (const QtSignalCliche* cliche : extractor.signalCliches)
    {
        for (auto implement = cliche->implementations; implement != nullptr; implement = implement->next)
            implement->connectIfCompatible(object.data(), const_cast<QtObjectWrapper*>(this), cliche);
    }
    if (extractor.eventMask != 0)
    {
        eventMask = extractor.eventMask;
        eventFilterProxy = new QtEventFilterProxy(this, object);
        object->installEventFilter(eventFilterProxy);
    }
    retain();
    return this;
}

void QtObjectWrapper::removeWhen() const
{
    assert(state == State::Deleted);
    if (!when) return;
    auto w = when;
    when = nullptr;
    w->release();
}

void QtObjectWrapper::write(Writing &writing) const
{
    writing.write('Q');
    if (const PilsString *name = className->attributes[0]->as_String())
    {
        writing.write(name->value);
    }
    else writing.write('?');
    if (object.isNull())
        writing.write('?');
}

void QtObjectWrapper::unlink()
{
    unhash();
    className->releaseFrom(*this);
    if (when)
    {
        auto w = when;
        when = nullptr;
        w->releaseFrom(*this);
    }
    assert(mind == nullptr);
    QObject* o = object.data();
    object = nullptr;
    if (o && o->parent() == nullptr)
        o->deleteLater();
}

QtObjectWrapper::QtObjectWrapper(const Constant *&link, const QtObjectClassName *className, QObject *object)
    : ReallySpecial (link), className(className), object(object), state(State::Deleted), mind(nullptr)
{
    StateChangeFilter *filter = new StateChangeFilter(*this);
    filter->setParent(object);
    object->installEventFilter(filter);
    QObject::connect(object, &QObject::destroyed, object, [this]() { checkDeletedState(); });
    if (QWindow *win = qobject_cast<QWindow*>(object))
        QObject::connect(win, &QWindow::visibleChanged, object, [this]() { checkState(); });
    checkState();
// #ifndef NDEBUG
//     std::fputc('+', stderr);
//     className->writeToDebugOutput(10);
// #endif
}

QtObjectWrapper::~QtObjectWrapper()
{
// #ifndef NDEBUG
//     std::fputc('~', stderr);
//     className->writeToDebugOutput(10);
// #endif
    if (eventFilterProxy)
    {
        eventFilterProxy->wrapper = nullptr;
        eventFilterProxy = nullptr;
    }
}
}
