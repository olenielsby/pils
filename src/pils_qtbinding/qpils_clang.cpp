#include "qpils_clang.h"

using namespace PILS;

namespace
{

struct FirstChildData
{
    CXCursor cursor;
    bool found = false;
};

CXChildVisitResult firstChildVisitor(
    CXCursor cursor,
    CXCursor,
    CXClientData clientData)
{
    auto *data = static_cast<FirstChildData *>(clientData);

    data->cursor = cursor;
    data->found = true;

    return CXChildVisit_Break;
}

struct NextSiblingData
{
    CXCursor current;
    CXCursor next;
    bool foundCurrent = false;
    bool foundNext = false;
};

CXChildVisitResult nextSiblingVisitor(
    CXCursor cursor,
    CXCursor,
    CXClientData clientData)
{
    auto *data = static_cast<NextSiblingData *>(clientData);

    if (data->foundCurrent)
    {
        data->next = cursor;
        data->foundNext = true;
        return CXChildVisit_Break;
    }

    if (clang_equalCursors(cursor, data->current))
        data->foundCurrent = true;

    return CXChildVisit_Continue;
}

} // anonymous namespace

///////////////////////////////////////////////////////////////////////////////

QClangTranslationUnit::QClangTranslationUnit(QObject *)
{
    m_index = clang_createIndex(0, 0);
}

QClangTranslationUnit::~QClangTranslationUnit()
{
    if (m_translationUnit)
        clang_disposeTranslationUnit(m_translationUnit);

    clang_disposeIndex(m_index);
}

bool QClangTranslationUnit::parse(const QString &filename)
{
    if (m_translationUnit)
    {
        clang_disposeTranslationUnit(m_translationUnit);
        m_translationUnit = nullptr;
    }

    m_translationUnit =
        clang_parseTranslationUnit(
            m_index,
            filename.toUtf8().constData(),
            nullptr,
            0,
            nullptr,
            0,
            CXTranslationUnit_None);

    if (!m_translationUnit)
        return false;

    m_cursor = clang_getTranslationUnitCursor(m_translationUnit);
    return true;
}

const CXCursor &QClangTranslationUnit::cursor() const
{
    static CXCursor nullCursor = clang_getNullCursor();
    if (!m_translationUnit)
        return nullCursor;
    return m_cursor;
}

bool QClangTranslationUnit::firstChild()
{
    FirstChildData data;

    clang_visitChildren(
        m_cursor,
        firstChildVisitor,
        &data);

    if (!data.found)
        return false;

    m_cursor = data.cursor;
    return true;
}

bool QClangTranslationUnit::semanticParent()
{
    CXCursor parent =
        clang_getCursorSemanticParent(m_cursor);

    if (clang_Cursor_isNull(parent))
        return false;

    m_cursor = parent;
    return true;
}

bool QClangTranslationUnit::nextSibling()
{
    CXCursor parent =
        clang_getCursorSemanticParent(m_cursor);

    if (clang_Cursor_isNull(parent))
        return false;

    NextSiblingData data;
    data.current = m_cursor;

    clang_visitChildren(
        parent,
        nextSiblingVisitor,
        &data);

    if (!data.foundNext)
        return false;

    m_cursor = data.next;
    return true;
}