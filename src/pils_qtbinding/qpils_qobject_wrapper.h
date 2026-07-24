#pragma once
#include "qpils_plumming.h"
#include "qpils_converter.h"
namespace PILS{

class QtObjectWrapper
    : public ReallySpecial, public QObject
{
public:
    QtObjectWrapper(Runner &run, const Constant *&link, const QtObjectClassName *className, QObject *object);
    ~QtObjectWrapper();
    const QtObjectClassName *className;
    QPointer<QObject> object;
    void write(Writing &writing) const override;
    bool specialComparing(const QtObjectLookup &lookup) const override;
    const Any *specialCalling(Runner &run, const QtMethodName &method, const Any &arg) const override;
    const Any *specialCalling(Runner &run, const QtMethodName &method) const override;
    bool converting(PlatformSpecificConverter &converter) const override;
protected:
    Runner &run;
private:
    const Any *invokeMethod(const QtMethodName &name, const Any *const *args, size_t argct) const;
};

class QtNewObjectWrapper : public QtObjectWrapper
{
public:
    QtNewObjectWrapper(Runner &run, const Constant *&link, const QtObjectClassName *className, QObject *object);
    ~QtNewObjectWrapper();
    const Step *calling(Runner &run, const Constant &call) const override;
    const Any *specialCalling(Runner &run, const Strap &call) const override;
    const Any *specialWhen(Runner &run, const Any &argument) const override;
    const Any *getWhen() const override {if (when) {when->retain(); return when;} else return Empty::get();}
    void removeWhen() const;
    mutable const Any *when = nullptr;
    mutable uint64_t eventMask = 0;
    void pilsSignalCallback(const QtSignalCliche *cliche, const Constant *argv[], size_t argc) const;
    bool pilsEventCallback(const QtEventCliche *cliche, const Constant *arg) const;
    class QtPassingMind : public QObject, public PassingMind
    {
    public:
        QtPassingMind(Runner &run, const Any &owner) : PassingMind(run, owner)
        {}
    };
    enum class State : uint8_t {
        DetachedHidden,         // !visible, !parent
        DetachedVisible,        // visible, !parent   (top-level window)
        AttachedVisibleDialog,  // visible, parent   (window-modal dialog)
        Attached,               // parent (buttons etc.)
        Deleted                 // wrapper survives dead object
    };
    bool eventFilter(QObject *watched, QEvent *event) override;
    mutable State state;
    mutable QtPassingMind *mind;
    State computeCurrentState() const;
    bool isTopLevelVisible(QObject *obj) const;
    void checkState() const;
    // void checkDeletedState() const;
    void enableMind() const;
    void disableMind() const;
    static int mindful(State s);
private:
    template<typename Obj, typename Signal, Signal signal, bool Blind>
    friend struct QtSignalImpl;
    static int retainCount(State s);
};
}
