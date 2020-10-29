#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),echoFlag(0),
    keyFlag(0),
    ui(new Ui::Login)
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

    //设置快捷键
    ui->btnLogin->setShortcut(Qt::Key_Return);

    //设置初始头像
    photoPath = QString("C:/code/day03/build-5-18-Desktop_Qt_5_7_0_MinGW_32bit-Debug/xiongmao.jpg");

    //开始密码设置回显
    ui->lineEditPW->setEchoMode(QLineEdit::Password);

    //关联时钟
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

//登录
void Login::on_btnLogin_clicked()
{
    //获取账号密码
    QString account = ui->lineEditAccount->text();
    QString pw = ui->lineEditPW->text();

    //打开注册信息
    QFile file("C:/code/day03/build-5-17-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ClientInfo.txt");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        QMessageBox::about(this,codec->toUnicode("关于"),codec->toUnicode("打开用户信息失败"));
        return;
    }

    //将文件的信息读取出来
    QString usrInfo = file.readAll();

    //将所有用户的信息存放到字符串数组中
    QStringList mylist = usrInfo.split("\r\n");

    //用户账号密码获取
    QString R_Text;
    QStringList R_IDPW;
    for(int i=0;i<mylist.size()-1;i++)
    {
        R_Text = mylist[i];//账号密码
        R_IDPW = R_Text.split("#");//0账号,1密码

        if(R_IDPW[0] == account)
        {
            if(R_IDPW[1] == pw)
            {
                //创建聊天界面,指定父控件
                chat = new CHAT(this);
                //显示
                chat->show();
                chat->getAccount(R_IDPW[0]);
                chat->getPhoto(photoPath);
                //清空登录界面的信息
                ui->lineEditAccount->clear();
                ui->lineEditPW->clear();
                //隐藏主界面
                hide();
                return;
            }
            else
            {
                QMessageBox::warning(this,codec->toUnicode("错误"),codec->toUnicode("密码错误"));
                cout << R_IDPW[1];
                ui->lineEditPW->clear();
                return;
            }
        }

    }

    QMessageBox::warning(this,codec->toUnicode("错误"),codec->toUnicode("用户名不存在"));

    ui->lineEditAccount->clear();
    ui->lineEditPW->clear();
    return;
}

//密码回显
void Login::on_btnPWEcho_clicked()
{
    if(echoFlag%2==0)
        ui->lineEditPW->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEditPW->setEchoMode(QLineEdit::Password);

    echoFlag++;
}

//键盘
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

//注册用户
void Login::on_btnRegister_clicked()
{
    //创建第二个窗口对象
    registerForm =  new RegisterForm(this);
    //并且显示
    registerForm->show();
    //影藏主界面
    hide();
}

//更换头像
void Login::on_btnImage_clicked()
{
    QString filter = codec->toUnicode("图片(*.bmp *jpg)");
    photoPath = QFileDialog::getOpenFileName(this,codec->toUnicode("选择头像"),".",filter);
    if(photoPath.isEmpty())
    {
        QMessageBox::about(this,codec->toUnicode("错误"),"请选择合适的头像");
        return;
    }

    ui->btnImage->setStyleSheet(QString("border-image:url(%1)").arg(photoPath));
}
