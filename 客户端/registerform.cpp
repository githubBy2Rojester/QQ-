#include "registerform.h"
#include "ui_registerform.h"


QTextCodec *codec;

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);

    //字符编码
    codec = QTextCodec::codecForName("GBK");

    //设置标题
    setWindowTitle(codec->toUnicode("注册"));

    //设置模态
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    //设置背景
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(palette);

    //设置开始光标集中在账号框
    ui->lineEditID->setFocus();
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

//账号
void RegisterForm::on_lineEditID_textChanged(const QString &arg1)
{
    //搞一个账号的命名规范正则表达式
    QRegExp re1("[1-9][0-9]{10}");
    QRegExp re2("[^0a-zA-z][0-9]{0,10}");

    //精准匹配
    if(re1.exactMatch(arg1)||!re2.exactMatch(arg1))
        ui->lineEditID->setText(arg1.left(arg1.length()-1));
}

//密码
void RegisterForm::on_lineEditPW_returnPressed()
{
}

//确认密码
void RegisterForm::on_lineEditRPW_returnPressed()
{
}

//注册
void RegisterForm::on_btnSure_clicked()
{
    if(ui->lineEditID->text().isEmpty())
        return;

    if(ui->lineEditPW->text() != ui->lineEditRPW->text())
    {
        QMessageBox::information(this,codec->toUnicode("消息"),codec->toUnicode("密码不一致"));
        return;
    }


    //获取账号密码
    QString ID = ui->lineEditID->text();
    QString PW = ui->lineEditPW->text();

    //拼接账号密码
    QString Rusult = QString("%1#%2\r\n").arg(ID).arg(PW);

    //打开文件
    QFile file("C:/code/day03/build-5-17-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ClientInfo.txt");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        cout<<codec->toUnicode("打开失败");
        return;
    }

    //将读取文件信息
    QByteArray a;
    a = file.readAll();
    QString text = a;
    QStringList mylist = text.split("\r\n");

    QString R_Text;
    QStringList R_IDPW;
    for(int i=0;i<mylist.size()-1;i++)
    {
        R_Text = mylist[i];
        R_IDPW = R_Text.split("#");
        if(R_IDPW[0] == ID)
        {
            QMessageBox::warning(this,codec->toUnicode("信息"),codec->toUnicode("用户已存在!!注册失败!!!"));
            file.close();
            //this->hide();
            //parentWidget()->show();
            return;
        }
    }

    //关闭文件
    file.close();


    //打开文件
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    if(!file.isOpen())
    {
        cout<<codec->toUnicode("打开失败");
        return;
    }

    //将信息写入文件
    file.write(Rusult.toStdString().c_str());

    //关闭文件
    file.close();
    QMessageBox::information(this,codec->toUnicode("消息"),codec->toUnicode("注册成功"));
    this->hide();
    parentWidget()->show();
}

//返回
void RegisterForm::on_btnReturn_clicked()
{
    //影藏注册界面
    hide();
    //显示登录界面
    parentWidget()->show();
}
