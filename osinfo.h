#ifndef OSINFO_H
#define OSINFO_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class OSInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString osVersion READ osVersion WRITE setOsVersion NOTIFY osVersionChanged FINAL)
    Q_PROPERTY(QString osName READ osName WRITE setOsName NOTIFY osNameChanged FINAL)
public:
    explicit OSInfo(QObject *parent = nullptr);

    QString osVersion() const;
    void setOsVersion(const QString &newOsVersion);

    QString osName() const;
    void setOsName(const QString &newOsName);

signals:
    void osVersionChanged(QString version);
    void osNameChanged(QString name);

private:
    QString m_osVersion;
    QString m_tempOsVersion;

    QString m_osName;
    QString m_tempOsName;

    void getOsInfo();
};

#endif // OSINFO_H
