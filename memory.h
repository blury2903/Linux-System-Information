#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>


class Memory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap memory READ memory WRITE setMemory NOTIFY memoryChanged FINAL)
public:
    explicit Memory(QObject *parent = nullptr);

    QVariantMap memory() const;
    void setMemory(const QVariantMap &newMemory);

    Q_INVOKABLE QString dataFromCpp(QString key);


signals:
    void memoryChanged(QVariantMap map);
private:
    QVariantMap m_memory;
    QVariantMap m_tempMem;
    QTimer m_timer;
    bool getOK;
    void getMemory();

};

#endif // MEMORY_H
