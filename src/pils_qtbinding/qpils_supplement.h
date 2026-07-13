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

class QPilsTreeNode;
class QPilsTreeWidget : public QTreeWidget
{
public:
    explicit QPilsTreeWidget(QWidget *parent);
    QPilsTreeWidget() : QPilsTreeWidget(nullptr) {}
    ~QPilsTreeWidget();
    void clearTree();
    QPilsTreeNode *addRootNode(const QString &text);
    QPilsTreeNode *currentNode() const;
private:
    friend class QPilsTreeNode;
    QPilsTreeNode *wrap(QTreeWidgetItem *);
    // void forget(QTreeWidgetItem *);
    std::unordered_map<QTreeWidgetItem *, QPilsTreeNode *> wrappers_;
};

class QPilsTreeNode : public QObject
{
public:
    QString text() const;
    void setText(const QString &);
    QPilsTreeNode *addChild(const QString &text);
    QPilsTreeNode *parentNode() const;
    int childCount() const;
    QPilsTreeNode *child(int i) const;
    void expand();
    void collapse();
    static const PILS::QtObjectClassName *getClassName();
private:
    friend class QPilsTreeWidget;
    QPilsTreeNode(QPilsTreeWidget *,
                  QTreeWidgetItem *);
    QPilsTreeWidget *tree_;
    QTreeWidgetItem *item_;
    static const PILS::QtObjectClassName *className;
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
