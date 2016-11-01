#ifndef READER_H
#define READER_H
#include <QObject>
#include <QDebug>

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader()    {}
    void receiveNewspaper(const QString &name ) const
    {
        qDebug() << "Receive newspaper" << name << endl;
    }
    void receiveNewspaper(const QString &name, const QString &id)
    {
        qDebug() << "receive newspaper, name:" << name << ", id:" << id << endl;
    }
};

#endif // READER_H
