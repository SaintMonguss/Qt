#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include <QObject>

class DataElement : public QObject
{
    Q_OBJECT
public:
    explicit DataElement(QObject *parent = 0);
    DataElement(const QString &path, const QString &name, QObject *parent=0);

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    QString path() const;
    void setPath(const QString &path);

    QString name() const;
    void setName(const QString &name);

signals:
    void pathChanged();
    void nameChanged();

private:
    QString m_path;
    QString m_name;
};

#endif // DATAELEMENT_H
