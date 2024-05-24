#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

class CpuInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString modelName READ modelName WRITE setModelName NOTIFY modelNameChanged FINAL)
    Q_PROPERTY(QString serial READ serial WRITE setSerial NOTIFY serialChanged FINAL)
public:
    explicit CpuInfo(QObject *parent = nullptr);



    QString modelName() const;
    void setModelName(const QString &newModelName);

    QString serial() const;
    void setSerial(const QString &newSerial);

signals:
    void modelNameChanged();

    void serialChanged();

private:
    void getCpuInfo();
    QString m_modelName;
    QString m_serial;

    QString m_tmpModelName;
    QString m_tmpSerial;
};

#endif // CPUINFO_H
