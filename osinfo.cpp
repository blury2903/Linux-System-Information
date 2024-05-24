#include "osinfo.h"

OSInfo::OSInfo(QObject *parent)
    : QObject{parent},

    m_osVersion{""},
    m_osName{""}
{
    OSInfo::getOsInfo();
    OSInfo::setOsVersion(m_tempOsVersion);
    OSInfo::setOsName(m_tempOsName);

}

QString OSInfo::osVersion() const
{
    return m_osVersion;
}

void OSInfo::setOsVersion(const QString &newOsVersion)
{
    if (m_osVersion == newOsVersion)
        return;
    m_osVersion = newOsVersion;
    emit osVersionChanged(m_osVersion);
}



QString OSInfo::osName() const
{
    return m_osName;
}

void OSInfo::setOsName(const QString &newOsName)
{
    if (m_osName == newOsName)
        return;
    m_osName = newOsName;
    emit osNameChanged(m_osName);
}


void OSInfo::getOsInfo()
{
    QFile osVerFile("/etc/os-release");
    if (!osVerFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open upTimeFile";
        m_tempOsVersion = "";
        return;
    }
    QTextStream in(&osVerFile);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        if(line.startsWith("NAME=")) {
            m_tempOsName = line.section('=', 1, 1).remove('"').trimmed();
        } else if (line.startsWith("VERSION=")) {
            m_tempOsVersion = line.section('=', 1, 1).remove('"').trimmed();
        }
    }
    osVerFile.close();
}
