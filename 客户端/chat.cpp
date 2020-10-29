#include "chat.h"
#include "ui_chat.h"

CHAT::CHAT(QWidget *parent) :
    QWidget(parent),talkflag(0),
    y_off(0),emjoyflag(0),keyflag(0),
    ui(new Ui::CHAT)
{
    ui->setupUi(this);

    //字符编码
    codec = QTextCodec::codecForName("GBK");

    //标题,背景
    setWindowTitle(codec->toUnicode("客户端"));
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    //设置ScrollArea容器
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(260,50,411,251);
    scrollArea->setBackgroundRole(QPalette::Dark);

    //设置滑动条隐藏
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //创建widget对象 并且设置大小
    scrollAreaCentralContents = new QWidget();
    scrollAreaCentralContents->resize(411,251);

    //设置模态
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    //创建客户端套接字
    tcpSocket = new QTcpSocket(this);
    //连接服务器
    tcpSocket->connectToHost(QHostAddress("192.168.29.188"),8888);
    //关联信号
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(NameToServer()));
}

CHAT::~CHAT()
{
    delete ui;
}

//获取账号
void CHAT::getAccount(QString account)
{
    this->Account = account;
}

//获取头像
void CHAT::getPhoto(QString &photo)
{
    this->photo = photo;
}

void CHAT::emjoyFlagAdd()
{
    emjoyflag++;
}

//关闭窗口事件
void CHAT::closeEvent(QCloseEvent *event)
{
    //发送的信息
    QString text = "delete:"+Account;
    //告诉客户端这个用户退出
    tcpSocket->write(text.toUtf8());
}
//获取表情包路径
void CHAT::emjoyPath(QString &path)
{
    this->path = path;
    cout << this->path;
    QString lastPath = QString("<img src = \"%1\">").arg(this->path);
    ui->textEdit->insertHtml(lastPath);
}

//将用户名发送给服务器
void CHAT::NameToServer()
{
    cout << "^.^"<<Account;

    QString text = "userName:"+Account;
    tcpSocket->write(text.toUtf8());
    //关联读信号
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receverFromServer()));
}

//接受服务器发送过来的用户信息
void CHAT::receverFromServer()
{    
    QString text = tcpSocket->readAll();
//    cout << text;

    if(text.startsWith("text:"))
    {	//text:photoPath$#xxxxx
        text.remove(0,5);//photoPath$#xxxx
        QString recvrPhoto = text.section("$#",0,0);
        text.remove(0,recvrPhoto.size()+2);//xxxx

        //将滑动容器内的Widget拿走
        scrollArea->takeWidget();

        //新建接受者页面
        recvr = new recv(scrollAreaCentralContents);
        QString *str = new QString(text);
        recvr->getName(chatForm);
        recvr->getText(str);
        recvr->getPhoto(recvrPhoto);
        recvr->setGeometry(0,y_off*50,411,50);

        //如果当前文本框的大小大于起始大小
        if((y_off+1)*50>=251)
        {
            //重新设置当前的大小
            scrollAreaCentralContents->resize(411,(y_off+1)*50);
        }

        y_off++;//偏移量自增

        scrollArea->setWidget(scrollAreaCentralContents);//将widget添加到scrollArea
        scrollArea->verticalScrollBar()->setValue(y_off*50);//设置浏览到底部
        //ui->textBrowser->append(text);
        return;
    }

    if(text.startsWith("delete:"))
    {
        text.remove(0,7);
        QString deleteName = text;
        QList<QListWidgetItem*> list = ui->listWidgetFriend->findItems(deleteName,Qt::MatchExactly);
        int row = ui->listWidgetFriend->row(list.at(0));
        ui->listWidgetFriend->takeItem(row);

        //如果下线的好友是刚刚聊天的好友就重置聊天状态
        if(!chatForm.isEmpty())
        {
            if(deleteName==chatForm)
            {
                talkflag=0;
                //顺便发一条信息给服务器,告诉他刷新发送者
                tcpSocket->write("#EmptySender#");
            }
        }
        return;
    }

    QListWidgetItem *item = new QListWidgetItem;
    item->setText(text);
    ui->listWidgetFriend->addItem(item);
}


void CHAT::on_listWidgetFriend_doubleClicked(const QModelIndex &index)
{
    //可以聊天了
    talkflag++;
    //获取点击的好友名
    QListWidgetItem *item = ui->listWidgetFriend->currentItem();
    chatForm = item->text();
    ui->labelUserName->setText(chatForm);
    //chatForm = "charForm:"+item->text();
    //把点击的用户名 发送给服务器
    //tcpSocket->write(chatForm.toUtf8());

    scrollArea->takeWidget();
    QList<send *> mylist;
    mylist = scrollAreaCentralContents->findChildren<send *>();
    for(auto k : mylist)
    {
        delete k;
    }
    y_off=0;
}

//发送消息
void CHAT::on_btnSend_clicked()
{
    if(!talkflag)
        return;

    //读取文本框的内容
    QString text = ui->textEdit->toHtml();
    if(text.isEmpty())
        return;

    //将滑动容器内的Widget拿走
    scrollArea->takeWidget();

    //新建发送者页面
    snder = new send(scrollAreaCentralContents);
    snder->getName(Account);
    snder->getText(text);
    snder->getPhoto(photo);
    snder->setGeometry(0,y_off*50,411,50);

    //如果当前文本框的大小大于起始大小
    if((y_off+1)*50>=251)
    {
        //重新设置当前的大小
        scrollAreaCentralContents->resize(411,(y_off+1)*50);
    }

    y_off++;//偏移量自增

    scrollArea->setWidget(scrollAreaCentralContents);//将widget添加到scrollArea

    //拼接发送给好友
    //text = "text:"+chatForm+"$:"+text;//text:jack$:xxxxx
    text = "text:" +photo+"$#"+chatForm+"$:"+text;//text:photoPath$#jack$:xxxx
    tcpSocket->write(text.toUtf8());
    scrollArea->verticalScrollBar()->setValue(y_off*50);//设置浏览到底部


//    QString text = ui->textEdit->toPlainText();
//    ui->textBrowser->insertPlainText(text);
//    ui->textEdit->clear();

//    text = "text:"+chatForm+"$:"+text;//text:jack$:xxxxx
//    tcpSocket->write(text.toUtf8());

}

//表情包
void CHAT::on_btnEmjoy_clicked()
{

    if(emjoyflag%2==0)
    {
        emjoy = new Emjoy(this);
        emjoy->setGeometry(280,134,300,156);
        emjoy->show();
    }
    else
    {
        emjoy->close();
    }

     emjoyflag++;
}

//键盘
void CHAT::on_btnKey_clicked()
{
    if(keyflag%2==0)
    {
        keyboard = new mykeyboard(this);
        keyboard->setGeometry(240,80,500,209);
        keyboard->show();
    }
    else
    {
        keyboard->close();
    }

    keyflag++;
}
