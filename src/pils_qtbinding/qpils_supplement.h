#pragma once
#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>

class QPilsPlainTextEdit : public QPlainTextEdit
{
public:
    using QPlainTextEdit::QPlainTextEdit;

    QList<int> selection() const;
    void setSelection(int anchor, int position);
};
