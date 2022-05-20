#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QUrl>


extern QString strbuff;
extern int Popup_function;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)   //构造函数
{
    //启动UI
    ui->setupUi(this);

    /*初始化界面*/
    //地址和端口自动补全以及默认提示
    QStringList hostWordList, portWordList;
    hostWordList << tr("192.168.1.2");
    portWordList << tr("5000");
    QCompleter* completerHost = new QCompleter(hostWordList, this);
    QCompleter* completerPort = new QCompleter(portWordList, this);
    ui->hostLineEdit_2->setCompleter(completerHost);
    ui->portLineEdit_2->setCompleter(completerPort);
    ui->hostLineEdit_2->setPlaceholderText(tr("192.168.1.2"));
    ui->portLineEdit_2->setPlaceholderText(tr("5000"));
    //定义一个client对象，ClientStuff类（继承自QObject）,来自clientStuff
    client = new ClientStuff(host,port);
    //client的status初始值为false,getStatus作用为返回status,setStatus为根据连接状态设置连接情况红绿,开始为红色
    setStatus(client->getStatus());


    //client对象发出信号读到了东西或者状态改变，则执行槽函数receivedSomething和setStatus
    connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);
    connect(client, &ClientStuff::statusChanged, this, &MainWindow::setStatus);
    //如果client类的tcpSocket对象报告了连接错误，则执行对应槽函数gotError,执行对应错误处理 ---运行期间该槽函数一直在检测此信号。
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));

    //定义QByteArray类对象text,并根据对象绘制二维码
    QByteArray text;
    ui->widget->setQrCodeContent(text,QSize(200,200));
}

MainWindow::~MainWindow()       //析构函数，删除client和ui,防止内存泄漏
{
    delete client;
    delete ui;
}

void MainWindow::setStatus(bool newStatus)
{
    //如果传入的status为true，则让连接情况状态框变绿，代表连接成功
    if(newStatus)
    {
        ui->label_status->setText(
                    tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connect->setVisible(false);
        ui->pushButton_disconnect->setVisible(true);
    }
    //如果传入的status为false,则让连接情况状态框变红，代表没有连接或连接失败
    else
    {
        ui->label_status->setText(
                tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->pushButton_connect->setVisible(true);
        ui->pushButton_disconnect->setVisible(false);
    }
}

void MainWindow::receivedSomething(QString msg)
{
    //定义正则网页匹配对象re与正则音乐匹配对象re_music，分别表示两种正则表达规则
    QRegularExpression re("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");//网页正则
    QRegularExpression re_music(".*\\.(?i)wav");//音乐正则
    //定义时间currentTime并给时间赋值，在客户端接收端上以时分秒的形式附加在信息前面
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->textEdit_log->append("[" + currentTime.toString("hh:mm:ss") + "] "+msg);
    //在日志里打印传输过来的内容 strubff tran, 原内容为strbuff origin
    qDebug()<<"strbuff tran:"<<strbuff;
    //text是对象，text的内容从strbuff里来的
    QByteArray text(strbuff.toUtf8());
    //使需生成的二维码对内容大小写敏感
    ui->widget->setQrCodeCaseSensitive(true);
    //二维码的内容从text里面得出，大小设置为200x200
    ui->widget->setQrCodeContent(text,QSize(200,200));
    //正则匹配的条件设置为strbuff长度大于10且Popup_function==1
    if(strbuff.length()>10&&Popup_function==1)
    {
        //把re正则是否适用于strbuff的结果传给match
        QRegularExpressionMatch match=re.match(strbuff);
        //如果match成功，弹窗,根据是否按钮，如果按了是，由默认浏览器打开网址；如果按了否，什么都不执行
        if( match.hasMatch() )
        {
                if(QMessageBox::Yes == QMessageBox::information(this,tr("是否打开此网页"),strbuff,QMessageBox::Yes|QMessageBox::No))
                {
                    QDesktopServices::openUrl(QUrl(strbuff));
                }
        }

        //把re.music规则是否适用于strbuff的结果传给match_music
        QRegularExpressionMatch match_music=re_music.match(strbuff);
        //如果match成功，弹窗,根据是否按钮，如果按了是，给服务器发送play；如果按了否，什么都不执行
        if( match_music.hasMatch() )
        {
                if(QMessageBox::Yes == QMessageBox::information(this,tr("是否播放此音乐"),strbuff,QMessageBox::Yes|QMessageBox::No))
                {
                    QString sendMsg = "play";
                    client->tcpSocket->write(sendMsg.toUtf8());
                }
        }
    }
}


void MainWindow::gotError(QAbstractSocket::SocketError err)     //连接中发生错误的槽函数处理,err为传出参数
{
    qDebug() << "got error";

    QString strError = "unknown error";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        //如果err为1，则连接错误类型是服务器断开连接
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }
    //在文本框显示连接错误错误信息
    ui->textEdit_log->append(strError);
}

void MainWindow::on_pushButton_connect_clicked()    //按下connect按钮
{

    //调试查看输入的服务器ip与端口号
    qDebug()<<"server's ip:"<<ui->hostLineEdit_2->text();
    qDebug()<<"port"<<ui->portLineEdit_2->text().toInt();

    //定义QString类的host,port变量并赋值给client类中元素
    host = ui->hostLineEdit_2->text();
    port = ui->portLineEdit_2->text().toInt();
    client->host=host;
    client->port=port;
    //与服务器建议socket-TCP通信
    client->connect2host();
}

void MainWindow::on_pushButton_send_clicked()   //按下send按钮后的槽函数
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    //定义对象in,把发送框内容给in
    QString in;
    in = ui->lineEdit_message->text();
    qDebug()<<in;
    //把in的类型变为字符串送入str变量
    std::string str = in.toStdString();
    //如果模式为1，拍照模式；否则为视频模式
    if (str == "1")
    {
        Popup_function = 1;
    }else //只有1才需要弹窗
    {
        Popup_function = 0;
    }
    //将1通过tcpSocket发送至服务器
    const char* ch = str.c_str();
    out.writeRawData(ch,in.length());
    client->tcpSocket->write(arrBlock);
}
void MainWindow::on_Update_clicked()  //按下update(更新二维码)后的槽函数
{
    //把strbuff里的内容送入info
    QString info = strbuff;
    //debug输出strbuff里的内容，看看传过来的内容是否正确
    qDebug()<<"strbuff tran:"<<strbuff;
    //把内容改成适合setQrCodeContent的格式送入text
    QByteArray text(info.toUtf8());
    //设置大小写敏感，根据200x200的大小和text内容绘制二维码
    ui->widget->setQrCodeCaseSensitive(true);
    ui->widget->setQrCodeContent(text,QSize(200,200));
}

void MainWindow::on_pushButton_disconnect_clicked() //按下disconnect按钮，关闭与服务器的连接
{
    client->closeConnection();
}
