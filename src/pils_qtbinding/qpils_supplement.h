#pragma once
#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTreeWidget>
#include "qpils_plumming.h"

class QPilsPlainTextEdit : public QPlainTextEdit
{
public:
    using QPlainTextEdit::QPlainTextEdit;

    QList<int> selection() const;
    void setSelection(int anchor, int position);
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
