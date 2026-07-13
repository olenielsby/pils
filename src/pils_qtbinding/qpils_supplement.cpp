#include "qpils_supplement.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QStylePainter>

QList<int> QPilsPlainTextEdit::selection_utf16() const
{
    QTextCursor c = textCursor();
    return { c.anchor(), c.position() };
}

void QPilsPlainTextEdit::setSelection_utf16(int anchor, int position)
{
    QTextCursor c = textCursor();
    c.setPosition(anchor);
    c.setPosition(position, QTextCursor::KeepAnchor);
    setTextCursor(c);
}

QList<int> QPilsPlainTextEdit::selection() const
{
    PositionConverter conv(*this);
    QTextCursor c = textCursor();
    return { conv.utf16ToUtf8(c.anchor()), conv.utf16ToUtf8(c.position()) };
}

void QPilsPlainTextEdit::setSelection(int anchor, int position)
{
    PositionConverter conv(*this);
    QTextCursor c = textCursor();
    c.setPosition(conv.utf8ToUtf16(anchor));
    c.setPosition(conv.utf8ToUtf16(position), QTextCursor::KeepAnchor);
    setTextCursor(c);
}

QPilsPlainTextEdit::PositionConverter::PositionConverter(
    const QPilsPlainTextEdit &editor)
    : text(editor.toPlainText())
{
}

int QPilsPlainTextEdit::PositionConverter::utf16ToUtf8(int utf16Pos) const
{
    return text.left(utf16Pos).toUtf8().length();
}

int QPilsPlainTextEdit::PositionConverter::utf8ToUtf16(int utf8Pos) const
{
    return QString::fromUtf8(text.toUtf8().left(utf8Pos)).length();
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

void QPilsGroupBox::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    QStyleOptionGroupBox opt;

    initStyleOption(&opt);

    // eksperimentér med opt her

    p.drawComplexControl(QStyle::CC_GroupBox, opt);
}

QPilsDelayedDestroy::QPilsDelayedDestroy()
{
    auto *dummy = new QObject;
    setParent(dummy);
    dummy->deleteLater();
}

QPilsCloseChildren::~QPilsCloseChildren()
{
    while (!children().isEmpty()) {
        QPointer<QObject> child = children().first();
        QCloseEvent event;
        QCoreApplication::sendEvent(child.data(), &event);
        // Eventet kan have destrueret eller reparenteret child.
        if (child && child->parent() == this)
            delete child;
    }
}

