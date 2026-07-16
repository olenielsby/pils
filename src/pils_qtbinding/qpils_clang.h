#pragma once

#include <QObject>
#include <QString>

#include <clang-c/Index.h>
#include "qpils_plumming.h"

using namespace PILS;

class QClangTranslationUnit : public QObject
{
public:
    explicit QClangTranslationUnit(QObject *parent = nullptr);

    ~QClangTranslationUnit() override;

    bool firstChild();
    bool nextSibling();
    bool semanticParent();
    bool parse(const QString &filename);
    const CXCursor &cursor() const;
private:
    CXIndex m_index = nullptr;
    CXCursor m_cursor;
    CXTranslationUnit m_translationUnit = nullptr;
};
