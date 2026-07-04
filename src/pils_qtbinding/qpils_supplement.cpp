#include "qpils_supplement.h"

QList<int> QPilsPlainTextEdit::selection() const
{
    QTextCursor c = textCursor();
    return { c.anchor(), c.position() };
}

void QPilsPlainTextEdit::setSelection(int anchor, int position)
{
    QTextCursor c = textCursor();
    c.setPosition(anchor);
    c.setPosition(position, QTextCursor::KeepAnchor);
    setTextCursor(c);
}

QPilsTreeWidget::QPilsTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    setHeaderHidden(true);
}

QPilsTreeWidget::~QPilsTreeWidget()
{
}

void QPilsTreeWidget::clearTree()
{
    wrappers_.clear();
    clear();
}

QPilsTreeNode *QPilsTreeWidget::wrap(QTreeWidgetItem *item)
{
    if (!item)
        return nullptr;

    auto it = wrappers_.find(item);
    if (it != wrappers_.end())
        return it->second;

    auto *node = new QPilsTreeNode(this, item);
    wrappers_[item] = node;
    return node;
}

QPilsTreeNode *QPilsTreeWidget::addRootNode(const QString &text)
{
    auto *item = new QTreeWidgetItem;
    item->setText(0, text);
    addTopLevelItem(item);
    return wrap(item);
}

QPilsTreeNode *QPilsTreeWidget::currentNode() const
{
    auto *item = currentItem();
    if (!item)
        return nullptr;

    auto it = wrappers_.find(item);
    return it == wrappers_.end() ? nullptr : it->second;
}

//==========================================================

QPilsTreeNode::QPilsTreeNode(QPilsTreeWidget *tree,
                             QTreeWidgetItem *item)
    : QObject(tree),
    tree_(tree),
    item_(item)
{
}

QString QPilsTreeNode::text() const
{
    return item_->text(0);
}

void QPilsTreeNode::setText(const QString &text)
{
    item_->setText(0, text);
}

QPilsTreeNode *QPilsTreeNode::addChild(const QString &text)
{
    auto *child = new QTreeWidgetItem;
    child->setText(0, text);
    item_->addChild(child);
    return tree_->wrap(child);
}

QPilsTreeNode *QPilsTreeNode::parentNode() const
{
    return tree_->wrap(item_->parent());
}

int QPilsTreeNode::childCount() const
{
    return item_->childCount();
}

QPilsTreeNode *QPilsTreeNode::child(int i) const
{
    return tree_->wrap(item_->child(i));
}

void QPilsTreeNode::expand()
{
    tree_->expandItem(item_);
}

void QPilsTreeNode::collapse()
{
    tree_->collapseItem(item_);
}

const PILS::QtObjectClassName *QPilsTreeNode::getClassName()
{
    if (className == nullptr)
    {
        const PILS::PilsString* pilsName = PILS::PilsString::get("PilsTreeNode");
        PILS::Namespace_QtClass::singleton->retain();
        const PILS::ClicheShort *dumbClassName = PILS::Namespace_QtClass::singleton->clichefy(pilsName);
        className = static_cast<const PILS::QtObjectClassName*>(dumbClassName);
    }
    return className;
}

const PILS::QtObjectClassName *QPilsTreeNode::className = nullptr;
