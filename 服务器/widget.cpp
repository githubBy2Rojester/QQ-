#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),timerflag(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //�ַ�����
    codec = QTextCodec::codecForName("GBK");

    //����,����
    setWindowTitle(codec->toUnicode("������"));
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    //�����Ѿ������Ŀͻ���
    loadingExistClient();

    //����������
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);

    //��׽�ͻ��˵�����
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(ClientLink()));
    //�������û���Ϣ ���͸���ǰ�ͻ���
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendClientName()));
}

Widget::~Widget()
{
    delete ui;
}

//���ش��ڵĿͻ���Ϣ
void Widget::loadingExistClient()
{
    QFile file("ClientInfo.txt");
    bool isOk  = file.open(QIODevice::ReadOnly);
    if(!isOk)
    {
        QMessageBox::about(this,codec->toUnicode("����"),codec->toUnicode("���ؿͻ���Ϣʧ��"));
        return;
    }

    //������Ϣ
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

    //�ر��ļ�
    file.close();
}


//�ͻ������ӷ�����
void Widget::ClientLink()
{
    //�ͻ��˵��׽���
    tcpSocket = tcpServer->nextPendingConnection();
    //���տͻ��˵���Ϣ
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveFromClient()));

}

//���տͻ��˵���Ϣ
void Widget::receiveFromClient()
{
    //��ȡ�����ߵ��׽���
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    //��ȡ�ͻ��˷�������Ϣ
    clientName= socket->readAll();

    if(clientName.startsWith("userName:"))
    {
        clientName.remove(0,9);
        //����Ϣ���浽��ֵ���ڲ�
        clientContents.insert(socket,clientName);
        //���������ֱ��浽����
        allClientName.push_back(clientName);

        //�����ӵĿͻ�����Ϣ��ʾ����¼�б�
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(clientContents.value(socket));
        ui->listWGLoginUsr->addItem(item);

        //ͬʱ�ѵ�¼���û����͸��ͻ���

        //������ǰ�ͻ���
        //���ö�ʱ��
        timer.start(100);

        //���������ͻ���
        for(QMap<QTcpSocket*,QString>::iterator it=clientContents.begin();it!=clientContents.end();it++)
        {
            //�������ͻ���
            if(it.value()==clientName)
                continue;

            //���߳��˱��ͻ���������пͻ� �����ߵĿͻ����û���
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
        //���ı����ݷ���
        QString lastText = clientName.remove(0,5);//photoPath$#jack$:xxxx
        QString photo = lastText.section("$#",0,0);//photoPath
        lastText.remove(0,photo.size()+2);//jack$:xxxx
        QString cli = lastText.section("$:",0,0);//��ȡҪ���͵Ŀͻ�����
        lastText = "text:" + photo+"$#"+ lastText.remove(0,cli.size()+2);
        sendr = clientContents.key(cli);
        sendr->write(lastText.toUtf8());//text:photoPath$#xxxxx
        return;
    }
    else if(clientName.startsWith("delete:"))
    {
        //ȡ����
        QString temp = clientName.mid(7);
        //���͸������ͻ�������û��Ѿ��뿪
        for(QMap<QTcpSocket*,QString>::iterator it=clientContents.begin();it!=clientContents.end();it++)
        {
            //�������ͻ���
            if(it.value()==temp)
                continue;

            //���߳��˱��ͻ���������пͻ� �����ߵĿͻ����û���
            it.key()->write(clientName.toUtf8());
        }

        //��ȡɾ���Ŀͻ�������
        clientName.remove(0,7);
        deleteName = clientName;

        //�������������� ������û�ȡ��
        clientContents.take(clientContents.key(deleteName));
        allClientName.removeOne(deleteName);

        //�ӵ�¼�б���ȥ��
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

//���Ϳͻ��˵�����
void Widget::sendClientName()
{
   //��ʱ�����еĴ���
    timerflag++;//1 //2

    //������д������û�+1��ͬ  ֹͣ
    if(allClientName.size()+1==timerflag) //2==1 2==2
    {
        timer.stop();
        timerflag=0;
        return;
    }
    //����ǵ�ǰ�ͻ��˾Ͳ���
    if(allClientName.at(timerflag-1)== clientName)//0==0
    {
        return;
    }
    //���͵�ǰ���û���
    tcpSocket->write(allClientName.at(timerflag-1).toUtf8());

}
