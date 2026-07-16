#pragma once

#include <QObject>
#include <QString>

#include <clang-c/Index.h>
#include "qpils_plumming.h"

namespace PILS
{

class QClangCursor;

class QClangTranslationUnit : public QObject
{
public:
    explicit QClangTranslationUnit(QObject *parent = nullptr);

    ~QClangTranslationUnit() override;

    bool parse(const QString &filename);

    QClangCursor *cursor() const;

private:
    CXIndex m_index = nullptr;
    CXTranslationUnit m_translationUnit = nullptr;

    friend class QClangCursor;
};

class QClangCursor : public QObject
{

public:
    static const PILS::QtObjectClassName *getClassName();
    QClangCursor(
        QClangTranslationUnit *translationUnit,
        CXCursor cursor,
        QObject *parent = nullptr);

    QString spelling() const;
    QString kind() const;

    bool isNull() const;

    QClangCursor *firstChild() const;
    QClangCursor *nextSibling() const;
    QClangCursor *semanticParent() const;


private:
    static const PILS::QtObjectClassName *className;
    static CXChildVisitResult firstChildVisitor(
        CXCursor cursor,
        CXCursor parent,
        CXClientData clientData);

    static CXChildVisitResult nextSiblingVisitor(
        CXCursor cursor,
        CXCursor parent,
        CXClientData clientData);

    QClangTranslationUnit *m_translationUnit;
    CXCursor m_cursor;
};

}