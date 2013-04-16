#include "moduleinfo.h"

ModuleInfo::ModuleInfo()
{

}
//------------------------------------------------------------------------------
const QString ModuleInfo::getFullName() const
{
    return m_fullName;
}
//------------------------------------------------------------------------------
const QString ModuleInfo::getShortName() const
{
    return m_shortName;
}
//------------------------------------------------------------------------------
const QString ModuleInfo::getPath() const
{
    return m_path;
}
//------------------------------------------------------------------------------
const QString ModuleInfo::getType() const
{
    return m_type;
}
//------------------------------------------------------------------------------
void ModuleInfo::setFullName(QString t_fullName)
{
    m_fullName = t_fullName;
}
//------------------------------------------------------------------------------
void ModuleInfo::setShortName(QString t_shortName)
{
    m_shortName = t_shortName;
}
//------------------------------------------------------------------------------
void ModuleInfo::setType(QString t_type)
{
    m_type = t_type;
}
//------------------------------------------------------------------------------
void ModuleInfo::setPath(QString t_path)
{
    m_path = t_path;
}
//------------------------------------------------------------------------------

