#pragma once
#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include <QGroupBox>
#include "qpils_plumming.h"
#include <QPointer>
#include <QCloseEvent>
#include <QCoreApplication>

class QPilsPlainTextEdit : public QPlainTextEdit
{
public:
    using QPlainTextEdit::QPlainTextEdit;

    QList<int> selection() const;
    QList<int> selection_utf16() const;
    void setSelection(int anchor, int position);
    void setSelection_utf16(int anchor, int position);

private:
    class PositionConverter
    {
    public:
        explicit PositionConverter(const QPilsPlainTextEdit &editor);
        int utf8ToUtf16(int utf8Pos) const;
        int utf16ToUtf8(int utf16Pos) const;
    private:
        QString text;
    };
};

class QPilsTreeWidgetItem;
class QPilsTreeWidget : public QTreeWidget
{
public:
    explicit QPilsTreeWidget(QWidget *parent);
    QPilsTreeWidget() : QPilsTreeWidget(nullptr) {}
    ~QPilsTreeWidget();
    void clearTree();
    QPilsTreeWidgetItem *addTopLevelItem(const QString &text);
    QPilsTreeWidgetItem *currentItem() const;
    void setCurrentItem(QPilsTreeWidgetItem *item);
private:
    friend class QPilsTreeWidgetItem;
    QPilsTreeWidgetItem *wrap(QTreeWidgetItem *);
    // void forget(QTreeWidgetItem *);
    std::unordered_map<QTreeWidgetItem *, QPilsTreeWidgetItem *> wrappers_;
};

class QPilsTreeWidgetItem : public QObject
{
public:
    QString text() const;
    void setText(const QString &);
    QPilsTreeWidgetItem *addChild(const QString &text);
    QPilsTreeWidgetItem *parentNode() const;
    int childCount() const;
    QPilsTreeWidgetItem *child(int i) const;
    void expand();
    void collapse();
    static const PILS::QtObjectClassName *getClassName();
private:
    friend class QPilsTreeWidget;
    QPilsTreeWidgetItem(QPilsTreeWidget *,
                  QTreeWidgetItem *);
    QPilsTreeWidget *tree_;
    QTreeWidgetItem *item_;
    static const PILS::QtObjectClassName *className;
};

class QPilsLocale : public QObject
{
public:
    explicit QPilsLocale(QObject *parent = nullptr)
        : QObject(parent), locale(QLocale::system()) {}
    QString name() const
    { return locale.name(); } // da_DK
    QString bcp47Name() const
    { return locale.bcp47Name(); }     // da-DK
    QString language() const
    { return QLocale::languageToString(locale.language()); }
    QString territory() const
    { return QLocale::territoryToString(locale.territory()); }
private:
    QLocale locale;
};


class QPilsDelayedDestroy : public QObject
{
public:
    QPilsDelayedDestroy();
};

#include <QObject>
#include <QPointer>
#include <QCloseEvent>
#include <QCoreApplication>

class QPilsCloseChildren : public QObject
{
public:
    using QObject::QObject;
    ~QPilsCloseChildren() override;
};

class QPilsGroupBox : public QGroupBox
{
public:
    using QGroupBox::QGroupBox;
protected:
    void paintEvent(QPaintEvent *event) override;
};
