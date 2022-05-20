#include "clientStuff.h"
//QString MainWindow::strbuff;
extern QString strbuff;
ClientStuff::ClientStuff(   //构造函数
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    //host和port是服务器端绑定（bind）的IP和PORT
    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);
}

void ClientStuff::connect2host()    //与服务器的槽函数中的连接函数
{
    timeoutTimer->start(3000);      //如果3秒内未连接，timeout
    tcpSocket->connectToHost(host, port);       //连接服务器，根据绑定的端口和地址
    //connectedToHost函数建立成功之后，发出connect信号，status变成connected
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    //如果tcpSocket对象发出readyRead信号，说明对端发送的数据到达，之后可以调用read函数读取数据
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

void ClientStuff::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void ClientStuff::connected()
{
    status = true;
    emit statusChanged(status);
}

bool ClientStuff::getStatus() {return status;}

void ClientStuff::readyRead()       //tcpSocket发出的信号readyRead，所对应的ClientStuff类的槽函数readyRead().
{
    //readAll---将当前可用操作数据全部读出，通过返回值返回读出的字符串,所以str里是读出的内容
    QByteArray str = tcpSocket->readAll();
    //strbuff里的内容是读取的内容
    strbuff = str;
    //在qt输出客户端接收的内容
    qDebug()<<"strbuff origin:"<<strbuff;
    //对客户端接收的内容解析
    //如果发送的内容为字符串格式的0，将被替换为connection closed
    if (str == "0")
    {
        str = "Connection closed";
        closeConnection();
    }

    //readyRead这个槽函数发送信号hasReadSome，又会触发它对应的槽函数
    emit hasReadSome(str);
    m_nNextBlockSize = 0;
}


void ClientStuff::closeConnection()     //客户端接受到服务器发送的字符串"0",客户端也会主动断开与服务器的连接closeConnection()
{
    timeoutTimer->stop();       //关闭定时器
    //断开与服务器端连接
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);
    //
    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
