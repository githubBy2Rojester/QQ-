#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),timerflag(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //字符编码
    codec = QTextCodec::codecForName("GBK");

    //标题,背景
    setWindowTitle(codec->toUnicode("服务器"));
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    //加载已经创建的客户端
    loadingExistClient();

    //创建服务器
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);

    //捕捉客户端的连接
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(ClientLink()));
    //将线上用户信息 发送给当前客户端
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendClientName()));
}

Widget::~Widget()
{
    delete ui;
}

//加载存在的客户信息
void Widget::loadingExistClient()
{
    QFile file("ClientInfo.txt");
    bool isOk  = file.open(QIODevice::ReadOnly);
    if(!isOk)
    {
        QMessageBox::about(this,codec->toUnicode("关于"),codec->toUnicode("加载客户信息失败"));
        return;
    }

    //加载信息
    QString usrInfo = file.readAll();
    QStringList mylist = usrInfo.split("\r\n");

    QString R_Text;
    QStringList R_IDPW;
    for(int i=0;i<mylist.size()-1;i++)
    {
        R_Text = mylist[i];
        R_IDPW = R_Text.split("#");
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(R_IDPW[0]);
        ui->listWGRegister->addItem(item);
    }

    //关闭文件
    file.close();
}


//客户端连接服务器
void Widget::ClientLink()
{
    //客户端的套接字
    tcpSocket = tcpServer->nextPendingConnection();
    //接收客户端的消息
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveFromClient()));

}

//接收客户端的消息
void Widget::receiveFromClient()
{
    //获取发送者的套接字
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    //获取客户端发来的信息
    clientName= socket->readAll();

    if(clientName.startsWith("userName:"))
    {
        clientName.remove(0,9);
        //把信息保存到键值对内部
        clientContents.insert(socket,clientName);
        //将所有名字保存到链表
        allClientName.push_back(clientName);

        //把连接的客户端信息显示到登录列表
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(clientContents.value(socket));
        ui->listWGLoginUsr->addItem(item);

        //同时把登录的用户发送给客户端

        //发给当前客户端
        //调用定时器
        timer.start(100);

        //发给其他客户端
        for(QMap<QTcpSocket*,QString>::iterator it=clientContents.begin();it!=clientContents.end();it++)
        {
            //跳过本客户端
            if(it.value()==clientName)
                continue;

            //告诉除了本客户端外的所有客户 新上线的客户端用户名
            it.key()->write(clientContents.value(socket).toUtf8());
        }
        return;

    }
    else if(clientName=="#EmptySender#")
    {
        sendr = NULL;
        return;
    }
    else if(clientName.startsWith("text:"))
    {	//text:photoPath$#jack$:xxxx
        //将文本内容发送
        QString lastText = clientName.remove(0,5);//photoPath$#jack$:xxxx
        QString photo = lastText.section("$#",0,0);//photoPath
        lastText.remove(0,photo.size()+2);//jack$:xxxx
        QString cli = lastText.section("$:",0,0);//获取要发送的客户端名
        lastText = "text:" + photo+"$#"+ lastText.remove(0,cli.size()+2);
        sendr = clientContents.key(cli);
        sendr->write(lastText.toUtf8());//text:photoPath$#xxxxx
        return;
    }
    else if(clientName.startsWith("delete:"))
    {
        //取名字
        QString temp = clientName.mid(7);
        //发送给其他客户端这个用户已经离开
        for(QMap<QTcpSocket*,QString>::iterator it=clientContents.begin();it!=clientContents.end();it++)
        {
            //跳过本客户端
            if(it.value()==temp)
                continue;

            //告诉除了本客户端外的所有客户 刚下线的客户端用户名
            it.key()->write(clientName.toUtf8());
        }

        //获取删除的客户端名字
        clientName.remove(0,7);
        deleteName = clientName;

        //从容器和链表中 把这个用户取走
        clientContents.take(clientContents.key(deleteName));
        allClientName.removeOne(deleteName);

        //从登录列表上去除
        QList<QListWidgetItem*> list = ui->listWGLoginUsr->findItems(deleteName,Qt::MatchExactly);
        int row = ui->listWGLoginUsr->row(list.at(0));
        ui->listWGLoginUsr->takeItem(row);
        return;

    }//File:chatform@@fileName##fileSize
    else if(clientName.startsWith("File:"))
    {
        clientName.remove(0,5);//chatform@@fileName##fileSize
        QString str =  clientName.section("@@",0,0);
        sendr = clientContents.key(str);
        clientName.remove(0,str.size());//@@fileName##fileSize
        QString text = "File:"+clientName;//File:@@fileName##fileSize
        sendr->write(text.toUtf8());
        return;
    }
    if(sendr!=NULL)
    {
        sendr->write(clientName.toUtf8());
    }

}

//发送客户端的名字
void Widget::sendClientName()
{
   //定时器运行的次数
    timerflag++;//1 //2

    //如果运行次数和用户+1相同  停止
    if(allClientName.size()+1==timerflag) //2==1 2==2
    {
        timer.stop();
        timerflag=0;
        return;
    }
    //如果是当前客户端就不发
    if(allClientName.at(timerflag-1)== clientName)//0==0
    {
        return;
    }
    //发送当前的用户名
    tcpSocket->write(allClientName.at(timerflag-1).toUtf8());

}
