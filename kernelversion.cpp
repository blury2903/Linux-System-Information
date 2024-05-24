#include "kernelversion.h"

KernelVersion::KernelVersion(QObject *parent)
    : QObject{parent},
    m_tempVersion{""}
{
    KernelVersion::getKernelVersion();
    KernelVersion::setKernelVersion(m_tempVersion);


}

QString KernelVersion::kernelVersion() const
{
    return m_kernelVersion;
}

void KernelVersion::setKernelVersion(const QString &newKernelVersion)
{
    if (m_kernelVersion == newKernelVersion)
        return;
    m_kernelVersion = newKernelVersion;
    emit kernelVersionChanged(m_kernelVersion);
}

void KernelVersion::getKernelVersion()
{
    QFile kernelVerFile("/proc/sys/kernel/osrelease");
    if (!kernelVerFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open upTimeFile";
        m_tempVersion = "";
        return;
    }
    QTextStream in(&kernelVerFile);
    QString line = in.readLine();
    kernelVerFile.close();
    m_tempVersion = line.trimmed();

}
