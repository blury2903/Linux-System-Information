#include "timestamp.h"

TimeStamp::TimeStamp(QObject *parent)
    : QObject{parent},
    m_timeStamp(""),
    m_tempTimeStamp(""),
    m_timer(new QTimer(this))
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this,  [=](){
        TimeStamp::getTimeStamp();
        TimeStamp::setTimeStamp(m_tempTimeStamp);

    });
    m_timer.start();
}

QString TimeStamp::timeStamp() const
{
    return m_timeStamp;
}

void TimeStamp::setTimeStamp(const QString &newTimeStamp)
{
    if (m_timeStamp == newTimeStamp)
        return;
    m_timeStamp = newTimeStamp;
    emit timeStampChanged(m_timeStamp);
}

void TimeStamp::getTimeStamp()
{
    std::time_t now = std::time(nullptr);
    struct tm *timeStruct = std::localtime(&now);

    if (timeStruct != nullptr) {
        QTime time(timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
        m_tempTimeStamp = time.toString("hh:mm:ss");
    } else {
        // Xử lý lỗi khi không thể lấy thời gian
        m_tempTimeStamp = "Error: Unable to get timestamp";
    }
}
