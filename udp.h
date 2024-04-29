#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

class Udp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged FINAL)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged FINAL)

private:
    QUdpSocket* socket;
public:
    explicit Udp(QObject *parent = nullptr);

    QString status() const;
    void setStatus(const QString &newStatus);

    bool connected() const;
    void setConnected(bool newConnected);

public slots:
    void bind(int port);
    void unbind();
    void send(QString _ip, int _port, QString _msg);

private slots:
    void receive();

signals:
    void statusChanged();
    void connectedChanged();
    void msg(QString _msg);

private:
    QString m_status;
    bool m_connected;
};

#endif // UDP_H
