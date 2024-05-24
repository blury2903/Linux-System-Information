#ifndef UPTIME_H
#define UPTIME_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class UpTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString upTime READ upTime WRITE setUpTime NOTIFY upTimeChanged FINAL)
public:
    explicit UpTime(QObject *parent = nullptr);

    QString upTime() const;
    void setUpTime(const QString &newUpTime);

signals:
    void upTimeChanged(QString time);
private:
    QString m_upTime;
    QString m_time;
    QTimer m_timer;
    bool getOK;
    void getUpTime();
};

#endif // UPTIME_H
