#pragma once
#include "qpils_plumming.h"
#include "qpils_converter.h"
namespace PILS{

class QtObjectWrapper
    : public ReallySpecial
{
public:
    QtObjectWrapper(const Constant *&link, const QtObjectClassName *className, QObject *object)
        : ReallySpecial (link), className(className), object(object), state(State::Deleted), mind(nullptr)
    {
        StateChangeFilter *filter = new StateChangeFilter(*this);
        filter->setParent(object);
        object->installEventFilter(filter);
        QObject::connect(object, &QObject::destroyed, object, [this]() { checkState(); });
        if (QWindow *win = qobject_cast<QWindow*>(object))
            QObject::connect(win, &QWindow::visibleChanged, object, [this]() { checkState(); });
        checkState();
    }
    const QtObjectClassName *className;
    QPointer<QObject> object;
    void write(Writing &writing) const override;
    void unlink() override;
    bool specialComparing(const QtObjectLookup &lookup) const override;
    const Any *specialCalling(Runner &run, const QtMethodName &method, const Any &arg) const override;
    const Any *specialCalling(Runner &run, const QtMethodName &method) const override;
    const Any *getWhen() const override {if (when) {when->retain(); return when;} else return Empty::get();}
    const Any *specialCalling(Runner &run, const Strap &call) const override;
    const Step *calling(Runner &run, const Constant &call) const override;
    const Any *specialWhen(Runner &run, const Any &argument) const override;
    mutable const Any *when = nullptr;
    void pilsCallback(const QtSignalCliche *cliche, const Constant *argv[], size_t argc);
private:
    const Any *invokeMethod(const QtMethodName &name, const Any *const *args, size_t argct) const;
    enum class State : uint8_t {
        DetachedHidden,     // !visible, !parent
        DetachedVisible,    // visible, !parent   (top-level window)
        Attached,           // parent
        Deleted             // special terminal
    };
    class StateChangeFilter : public QObject
    {
    public:
        StateChangeFilter(QtObjectWrapper &wrapper): wrapper(wrapper) {}
        QtObjectWrapper &wrapper;
        bool eventFilter(QObject *watched, QEvent *event) override
        {
            switch (event->type())
            {
            case QEvent::ParentChange:
            case QEvent::Show:
            case QEvent::Hide:
                wrapper.checkState();
                break;
            default:
                break;
            }
            return QObject::eventFilter(watched, event);
        }
    };
    mutable State state;
    mutable PassingMind *mind;
    State computeCurrentState() const;
    bool isTopLevelVisible(QObject *obj) const;
    void checkState() const;
    void enableMind() const;
    void disableMind() const;
    static int retainCount(State s);
};
}
