#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),echoFlag(0),
    keyFlag(0),
    ui(new Ui::Login)
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

    //���ÿ�ݼ�
    ui->btnLogin->setShortcut(Qt::Key_Return);

    //���ó�ʼͷ��
    photoPath = QString("C:/code/day03/build-5-18-Desktop_Qt_5_7_0_MinGW_32bit-Debug/xiongmao.jpg");

    //��ʼ�������û���
    ui->lineEditPW->setEchoMode(QLineEdit::Password);

    //����ʱ��
    timer.start(1000);
    connect(&timer,&QTimer::timeout,
            [=]()
            {
                QString time = QTime::currentTime().toString("hh:mm:ss");
                ui->labelTime->setText(time);
            }
            );
}

Login::~Login()
{
    delete ui;
}

//��¼
void Login::on_btnLogin_clicked()
{
    //��ȡ�˺�����
    QString account = ui->lineEditAccount->text();
    QString pw = ui->lineEditPW->text();

    //��ע����Ϣ
    QFile file("C:/code/day03/build-5-17-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ClientInfo.txt");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        QMessageBox::about(this,codec->toUnicode("����"),codec->toUnicode("���û���Ϣʧ��"));
        return;
    }

    //���ļ�����Ϣ��ȡ����
    QString usrInfo = file.readAll();

    //�������û�����Ϣ��ŵ��ַ���������
    QStringList mylist = usrInfo.split("\r\n");

    //�û��˺������ȡ
    QString R_Text;
    QStringList R_IDPW;
    for(int i=0;i<mylist.size()-1;i++)
    {
        R_Text = mylist[i];//�˺�����
        R_IDPW = R_Text.split("#");//0�˺�,1����

        if(R_IDPW[0] == account)
        {
            if(R_IDPW[1] == pw)
            {
                //�����������,ָ�����ؼ�
                chat = new CHAT(this);
                //��ʾ
                chat->show();
                chat->getAccount(R_IDPW[0]);
                chat->getPhoto(photoPath);
                //��յ�¼�������Ϣ
                ui->lineEditAccount->clear();
                ui->lineEditPW->clear();
                //����������
                hide();
                return;
            }
            else
            {
                QMessageBox::warning(this,codec->toUnicode("����"),codec->toUnicode("�������"));
                cout << R_IDPW[1];
                ui->lineEditPW->clear();
                return;
            }
        }

    }

    QMessageBox::warning(this,codec->toUnicode("����"),codec->toUnicode("�û���������"));

    ui->lineEditAccount->clear();
    ui->lineEditPW->clear();
    return;
}

//�������
void Login::on_btnPWEcho_clicked()
{
    if(echoFlag%2==0)
        ui->lineEditPW->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEditPW->setEchoMode(QLineEdit::Password);

    echoFlag++;
}

//����
void Login::on_btnKey_clicked()
{
    if(keyFlag%2==0)
    {
        keyboard = new mykeyboard(this);
        keyboard->setGeometry(180,270,441,201);
        keyboard->show();
    }
    else
    {
        keyboard->close();
        delete keyboard;
    }

    keyFlag++;
}

//ע���û�
void Login::on_btnRegister_clicked()
{
    //�����ڶ������ڶ���
    registerForm =  new RegisterForm(this);
    //������ʾ
    registerForm->show();
    //Ӱ��������
    hide();
}

//����ͷ��
void Login::on_btnImage_clicked()
{
    QString filter = codec->toUnicode("ͼƬ(*.bmp *jpg)");
    photoPath = QFileDialog::getOpenFileName(this,codec->toUnicode("ѡ��ͷ��"),".",filter);
    if(photoPath.isEmpty())
    {
        QMessageBox::about(this,codec->toUnicode("����"),"��ѡ����ʵ�ͷ��");
        return;
    }

    ui->btnImage->setStyleSheet(QString("border-image:url(%1)").arg(photoPath));
}
