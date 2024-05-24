#include "memory.h"

Memory::Memory(QObject *parent) : QObject{parent},
    m_timer(new QTimer(this)),
    getOK(0)
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this,  [=](){
        Memory::getMemory();
        if(getOK) {
            setMemory(m_tempMem);
        }


    });
    m_timer.start();

}

QVariantMap Memory::memory() const
{
    return m_memory;
}






void Memory::setMemory(const QVariantMap &newMemory)
{
    if (m_memory != newMemory) {
        m_memory = newMemory;
        emit memoryChanged(m_memory);
    }


}

QString Memory::dataFromCpp(QString key)
{

    return QString::number(m_memory.value(key).toDouble(), 'f', 2);
}



void Memory::getMemory()
{
    QFile memFile("/proc/meminfo");
    if (!memFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open memFile";
        getOK = 0;
        return;
    }

    QTextStream in(&memFile);
    static QRegularExpression re("\\s+");
    int count = 3;

    while (count--) {
        QString line = in.readLine();
        QStringList parts = line.split(re, Qt::SkipEmptyParts);

        if (parts.size() >= 2) {
            QString key = parts[0].remove(":");
            QString value = parts[1];

            if (key == "MemTotal" || key == "MemFree") {
                m_tempMem[key] = value.toDouble() / (1024 * 1024);
            }
        }
    }
    getOK = 1;
    memFile.close();

    m_tempMem["MemUsage"] = 100 - (100 * m_tempMem["MemFree"].toDouble() / m_tempMem["MemTotal"].toDouble());
}

