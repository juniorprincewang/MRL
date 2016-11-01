#ifndef NEWSPAPER_H
#define NEWSPAPER_H
#include <QObject>

class Newspaper : public QObject
{
    Q_OBJECT
public:
    Newspaper(const QString &name, const QString &id):
        m_name(name), m_id(id)
    {

    }
    void sendName() const
    {
        emit newPaper(m_name);
    }
    void sendAll() const
    {
        emit newPaper(m_name, m_id);
    }
signals:
    void newPaper(const QString &name) const;
    void newPaper(const QString &name, const QString &id)const;
private:
    QString m_name;
    QString m_id;

};

#endif // NEWSPAPER_H
