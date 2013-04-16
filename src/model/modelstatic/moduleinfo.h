#ifndef MODULEINFO_H
#define MODULEINFO_H

#include <QString>

class ModuleInfo
{
public:
    ModuleInfo();

    void setFullName(QString t_fullName);
    void setShortName(QString t_shortName);
    void setPath(QString t_path);
    void setType(QString t_type);

    const QString getFullName() const;
    const QString getShortName() const;
    const QString getPath() const;
    const QString getType() const;

private:
    QString m_fullName;
    QString m_shortName;
    QString m_path;
    QString m_type;
    int m_id;
};

#endif // MODULEINFO_H

