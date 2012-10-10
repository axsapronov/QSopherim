#include "biblemodule.h"
#include "debughelper.h"


BibleModule::BibleModule()
{

}
//------------------------------------------------------------------------------
BibleModule::~BibleModule()
{
//    DEBUG_FUNC_NAME;
//    m_versification.clear();
}
//------------------------------------------------------------------------------
int BibleModule::loadBibleData(const int /*bibleID*/, const QString &/*path*/)
{
    myWarning() << "calling BibleModule";
    return -1;
}
//------------------------------------------------------------------------------
MetaInfo BibleModule::readInfo(QFile &/*file*/)
{
    myWarning() << "calling BibleModule";
    return MetaInfo();
}
//------------------------------------------------------------------------------
bool BibleModule::hasIndex() const
{
    myWarning() << "calling BibleModule";
    return false;
}
//------------------------------------------------------------------------------
void BibleModule::buildIndex()
{
    myWarning() << "calling BibleModule";
}
//------------------------------------------------------------------------------
int BibleModule::moduleID() const
{
    myWarning() << "calling BibleModule";
    return 0;
}
//------------------------------------------------------------------------------
QString BibleModule::modulePath() const
{
    myWarning() << "calling BibleModule";
    return "";
}
//------------------------------------------------------------------------------
QString BibleModule::moduleName(bool /*preferShortName*/) const
{
    myWarning() << "calling BibleModule";
    return "";
}
//------------------------------------------------------------------------------
QString BibleModule::uid() const
{
    return QString();
}
//------------------------------------------------------------------------------
std::pair<int, int> BibleModule::minMaxVerse(int /*bookID*/, int /*chapterID*/)
{
    myWarning() << "calling BibleModule";
    return std::pair<int, int>();
}
//------------------------------------------------------------------------------
void BibleModule::clear()
{
    myWarning() << "calling BibleModule";
}
//------------------------------------------------------------------------------
void BibleModule::clearData()
{
    myWarning() << "calling BibleModule";
}
//------------------------------------------------------------------------------
void BibleModule::parseModule(QString pathToModule)
{
    myWarning() << "calling BibleModule";
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
