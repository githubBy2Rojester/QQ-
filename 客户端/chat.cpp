#include "chat.h"
#include "ui_chat.h"

CHAT::CHAT(QWidget *parent) :
    QWidget(parent),talkflag(0),
    y_off(0),emjoyflag(0),keyflag(0),
    ui(new Ui::CHAT)
{
    ui->setupUi(this);

    //�ַ�����
    codec = QTextCodec::codecForName("GBK");

    //����,����
    setWindowTitle(codec->toUnicode("�ͻ���"));
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    //����ScrollArea����
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(260,50,411,251);
    scrollArea->setBackgroundRole(QPalette::Dark);

    //���û���������
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //����widget���� �������ô�С
    scrollAreaCentralContents = new QWidget();
    scrollAreaCentralContents->resize(411,251);

    //����ģ̬
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    //�����ͻ����׽���
    tcpSocket = new QTcpSocket(this);
    //���ӷ�����
    tcpSocket->connectToHost(QHostAddress("192.168.29.188"),8888);
    //�����ź�
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(NameToServer()));
}

CHAT::~CHAT()
{
    delete ui;
}

//��ȡ�˺�
void CHAT::getAccount(QString account)
{
    this->Account = account;
}

//��ȡͷ��
void CHAT::getPhoto(QString &photo)
{
    this->photo = photo;
}

void CHAT::emjoyFlagAdd()
{
    emjoyflag++;
}

//�رմ����¼�
void CHAT::closeEvent(QCloseEvent *event)
{
    //���͵���Ϣ
    QString text = "delete:"+Account;
    //���߿ͻ�������û��˳�
    tcpSocket->write(text.toUtf8());
}
//��ȡ�����·��
void CHAT::emjoyPath(QString &path)
{
    this->path = path;
    cout << this->path;
    QString lastPath = QString("<img src = \"%1\">").arg(this->path);
    ui->textEdit->insertHtml(lastPath);
}

//���û������͸�������
void CHAT::NameToServer()
{
    cout << "^.^"<<Account;

    QString text = "userName:"+Account;
    tcpSocket->write(text.toUtf8());
    //�������ź�
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receverFromServer()));
}

//���ܷ��������͹������û���Ϣ
void CHAT::receverFromServer()
{    
    QString text = tcpSocket->readAll();
//    cout << text;

    if(text.startsWith("text:"))
    {	//text:photoPath$#xxxxx
        text.remove(0,5);//photoPath$#xxxx
        QString recvrPhoto = text.section("$#",0,0);
        text.remove(0,recvrPhoto.size()+2);//xxxx

        //�����������ڵ�Widget����
        scrollArea->takeWidget();

        //�½�������ҳ��
        recvr = new recv(scrollAreaCentralContents);
        QString *str = new QString(text);
        recvr->getName(chatForm);
        recvr->getText(str);
        recvr->getPhoto(recvrPhoto);
        recvr->setGeometry(0,y_off*50,411,50);

        //�����ǰ�ı���Ĵ�С������ʼ��С
        if((y_off+1)*50>=251)
        {
            //�������õ�ǰ�Ĵ�С
            scrollAreaCentralContents->resize(411,(y_off+1)*50);
        }

        y_off++;//ƫ��������

        scrollArea->setWidget(scrollAreaCentralContents);//��widget��ӵ�scrollArea
        scrollArea->verticalScrollBar()->setValue(y_off*50);//����������ײ�
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

        //������ߵĺ����Ǹո�����ĺ��Ѿ���������״̬
        if(!chatForm.isEmpty())
        {
            if(deleteName==chatForm)
            {
                talkflag=0;
                //˳�㷢һ����Ϣ��������,������ˢ�·�����
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
    //����������
    talkflag++;
    //��ȡ����ĺ�����
    QListWidgetItem *item = ui->listWidgetFriend->currentItem();
    chatForm = item->text();
    ui->labelUserName->setText(chatForm);
    //chatForm = "charForm:"+item->text();
    //�ѵ�����û��� ���͸�������
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

//������Ϣ
void CHAT::on_btnSend_clicked()
{
    if(!talkflag)
        return;

    //��ȡ�ı��������
    QString text = ui->textEdit->toHtml();
    if(text.isEmpty())
        return;

    //�����������ڵ�Widget����
    scrollArea->takeWidget();

    //�½�������ҳ��
    snder = new send(scrollAreaCentralContents);
    snder->getName(Account);
    snder->getText(text);
    snder->getPhoto(photo);
    snder->setGeometry(0,y_off*50,411,50);

    //�����ǰ�ı���Ĵ�С������ʼ��С
    if((y_off+1)*50>=251)
    {
        //�������õ�ǰ�Ĵ�С
        scrollAreaCentralContents->resize(411,(y_off+1)*50);
    }

    y_off++;//ƫ��������

    scrollArea->setWidget(scrollAreaCentralContents);//��widget��ӵ�scrollArea

    //ƴ�ӷ��͸�����
    //text = "text:"+chatForm+"$:"+text;//text:jack$:xxxxx
    text = "text:" +photo+"$#"+chatForm+"$:"+text;//text:photoPath$#jack$:xxxx
    tcpSocket->write(text.toUtf8());
    scrollArea->verticalScrollBar()->setValue(y_off*50);//����������ײ�


//    QString text = ui->textEdit->toPlainText();
//    ui->textBrowser->insertPlainText(text);
//    ui->textEdit->clear();

//    text = "text:"+chatForm+"$:"+text;//text:jack$:xxxxx
//    tcpSocket->write(text.toUtf8());

}

//�����
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

//����
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
