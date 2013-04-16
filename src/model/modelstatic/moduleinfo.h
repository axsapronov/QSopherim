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

    const QString getPublisher() const;
    void setPublisher(QString t_var);

    const QString getContributors() const;
    void setContributors(QString t_var);

    const QString getDate() const;
    void setDate(QString t_var);

    const QString getType() const;
    void setType(QString t_var);

    const QString getFormat() const;
    void setFormat(QString t_var);

    const QString getIdentifier() const;
    void setIdentifier(QString t_var);

    const QString getSource() const;
    void setSource(QString t_var);

    const QString getLanguage() const;
    void setLanguage(QString t_var);

    const QString getCoverage() const;
    void setCoverage(QString t_var);

    const QString getRights() const;
    void setRights(QString t_var);

    const QString getSubject() const;
    void setSubject(QString t_var);

    const QString getDescription() const;
    void setDescription(QString t_var);

    const QString getCreator() const;
    void setCreator(QString t_var);

private:
    QString m_fullName;
    QString m_shortName;
    QString m_path;
    QString m_type;


    QString m_publisher;
    QString m_contributors;
    QString m_date;
    QString m_type;
    QString m_format;
    QString m_identifier;
    QString m_source;
    QString m_language;
    QString m_coverage;
    QString m_rights;
    QString m_subject;
    QString m_description;
    QString m_creator;


    int m_id;
};

#endif // MODULEINFO_H

