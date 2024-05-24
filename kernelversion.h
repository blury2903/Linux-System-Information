#ifndef KERNELVERSION_H
#define KERNELVERSION_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>

class KernelVersion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kernelVersion READ kernelVersion WRITE setKernelVersion NOTIFY kernelVersionChanged FINAL)
public:
    explicit KernelVersion(QObject *parent = nullptr);

    QString kernelVersion() const;
    void setKernelVersion(const QString &newKernelVersion);

signals:
    void kernelVersionChanged(QString version);
private:
    QString m_kernelVersion;
    QString m_tempVersion;
    void getKernelVersion();
};

#endif // KERNELVERSION_H
