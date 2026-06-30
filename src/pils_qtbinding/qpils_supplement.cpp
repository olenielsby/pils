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