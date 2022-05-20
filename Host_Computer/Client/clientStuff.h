#ifndef CLIENTSTUFF_H
#define CLIENTSTUFF_H

#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>

class ClientStuff : public QObject      //继承QObject类，子类ClientStuff类。包含客户端需要的一系列对象及槽信号与槽函数
{
    Q_OBJECT

public:
    ClientStuff(const QString hostAddress, int portVal, QObject *parent = 0);   //ClientStuff对象，由两个参数组成，IP地址和端口号
    QTcpSocket *tcpSocket;
    bool getStatus();
    QString host;
    int port;

public slots:
    void closeConnection();
    void connect2host();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

private:
    bool status;
    quint16 m_nNextBlockSize;
    QTimer *timeoutTimer;
};

#endif // CLIENTSTUFF_H
