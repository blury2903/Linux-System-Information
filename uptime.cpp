#include "uptime.h"

UpTime::UpTime(QObject *parent): QObject{parent},
    m_upTime(""),
    m_time(""),
    m_timer(new QTimer(this)),
    getOK(0)
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this,  [=](){
        UpTime::getUpTime();
        if(getOK) {
            UpTime::setUpTime(m_time);
        }
        else {
            emit upTimeChanged(m_upTime);
        }

    });
    m_timer.start();

}

QString UpTime::upTime() const
{
    return m_upTime;
}

void UpTime::setUpTime(const QString &newUpTime)
{
    if (m_upTime == newUpTime)
        return;
    m_upTime = newUpTime;
    emit upTimeChanged(m_upTime);
}

void UpTime::getUpTime()
{
    QFile upTimeFile("/proc/uptime");
    if (!upTimeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open upTimeFile";
        getOK = 0;
        return;
    }
    QTextStream in(&upTimeFile);
    QString line = in.readLine();
    upTimeFile.close();

    QStringList parts = line.split(" ");
    bool ok;
    QTime time(0, 0, 0);
    double secs = parts[0].toDouble(&ok);
    if(!ok) {
        qDebug() << "Failed to toInt";
        getOK = 0;
        return;
    }
    time = time.addSecs(secs);
    m_time = time.toString("hh:mm:ss");
    getOK = 1;

}
