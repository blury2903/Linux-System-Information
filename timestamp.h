#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class TimeStamp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeStamp READ timeStamp WRITE setTimeStamp NOTIFY timeStampChanged FINAL)
public:
    explicit TimeStamp(QObject *parent = nullptr);

    QString timeStamp() const;
    void setTimeStamp(const QString &newTimeStamp);

signals:
    void timeStampChanged(QString time);
private:
    QString m_timeStamp;
    QString m_tempTimeStamp;
    QTimer m_timer;
    void getTimeStamp();
};

#endif // TIMESTAMP_H
