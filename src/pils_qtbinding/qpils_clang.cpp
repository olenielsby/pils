#include "qpils_clang.h"

using namespace PILS;

namespace
{

QString toQString(CXString string)
{
    QString result = QString::fromUtf8(clang_getCString(string));
    clang_disposeString(string);
    return result;
}

}

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

    return m_translationUnit != nullptr;
}

QClangCursor *QClangTranslationUnit::rootCursor() const
{
    if (!m_translationUnit)
        return nullptr;

    return new QClangCursor(
        const_cast<QClangTranslationUnit *>(this),
        clang_getTranslationUnitCursor(m_translationUnit));
}

///////////////////////////////////////////////////////////////////////////////

QClangCursor::QClangCursor(
    QClangTranslationUnit *translationUnit_,
    CXCursor cursor_,
    QObject *)
    : m_translationUnit(translationUnit_)
    , m_cursor(cursor_)
{
}

const PILS::QtObjectClassName *QClangCursor::className = nullptr;
const PILS::QtObjectClassName *QClangCursor::getClassName()
{
    if (className == nullptr)
    {
        const PILS::PilsString* pilsName = PILS::PilsString::get("ClangCursor");
        PILS::Namespace_QtClass::singleton->retain();
        const PILS::ClicheShort *dumbClassName = PILS::Namespace_QtClass::singleton->clichefy(pilsName);
        className = static_cast<const PILS::QtObjectClassName*>(dumbClassName);
    }
    return className;
}

bool QClangCursor::isNull() const
{
    return clang_Cursor_isNull(m_cursor);
}

QString QClangCursor::spelling() const
{
    return toQString(clang_getCursorSpelling(m_cursor));
}

QString QClangCursor::kind() const
{
    return toQString(
        clang_getCursorKindSpelling(
            clang_getCursorKind(m_cursor)));
}

QClangCursor *QClangCursor::semanticParent() const
{
    return new QClangCursor(
        m_translationUnit,
        clang_getCursorSemanticParent(m_cursor));
}

///////////////////////////////////////////////////////////////////////////////

struct FirstChildData
{
    CXCursor cursor;
    bool found = false;
};

CXChildVisitResult
QClangCursor::firstChildVisitor(
    CXCursor cursor,
    CXCursor,
    CXClientData clientData)
{
    auto *data = static_cast<FirstChildData *>(clientData);

    data->cursor = cursor;
    data->found = true;

    return CXChildVisit_Break;
}

QClangCursor *QClangCursor::firstChild() const
{
    FirstChildData data;

    clang_visitChildren(
        m_cursor,
        firstChildVisitor,
        &data);

    if (!data.found)
        return nullptr;

    return new QClangCursor(
        m_translationUnit,
        data.cursor);
}

///////////////////////////////////////////////////////////////////////////////

struct NextSiblingData
{
    CXCursor current;
    CXCursor next;
    bool foundCurrent = false;
    bool foundNext = false;
};

CXChildVisitResult
QClangCursor::nextSiblingVisitor(
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

QClangCursor *QClangCursor::nextSibling() const
{
    CXCursor parent = clang_getCursorSemanticParent(m_cursor);

    if (clang_Cursor_isNull(parent))
        return nullptr;

    NextSiblingData data;
    data.current = m_cursor;

    clang_visitChildren(
        parent,
        nextSiblingVisitor,
        &data);

    if (!data.foundNext)
        return nullptr;

    return new QClangCursor(
        m_translationUnit,
        data.next);
}