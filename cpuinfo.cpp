#include "cpuinfo.h"

CpuInfo::CpuInfo(QObject *parent)
    : QObject{parent},
    m_modelName{""},
    m_serial{""}
{
    CpuInfo::getCpuInfo();
    CpuInfo::setModelName(m_tmpModelName);
    CpuInfo::setSerial(m_tmpSerial);

}



void CpuInfo::getCpuInfo()
{
    QFile cpuInfoFile("/proc/cpuinfo");
    if (!cpuInfoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open memFile";
        return;
    }

    QTextStream in(&cpuInfoFile);
    QString line = in.readLine();

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList parts = line.split(":");

        if (parts.size() >= 2) {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            if (key == "model name") {
                m_tmpModelName = value;
            }

            if (key == "Serial") {
                m_tmpSerial = value;
            }
        }
    }
    cpuInfoFile.close();

}

QString CpuInfo::modelName() const
{
    return m_modelName;
}

void CpuInfo::setModelName(const QString &newModelName)
{
    if (m_modelName == newModelName)
        return;
    m_modelName = newModelName;
    emit modelNameChanged();
}

QString CpuInfo::serial() const
{
    return m_serial;
}

void CpuInfo::setSerial(const QString &newSerial)
{
    if (m_serial == newSerial)
        return;
    m_serial = newSerial;
    emit serialChanged();
}
