#include "registerform.h"
#include "ui_registerform.h"


QTextCodec *codec;

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);

    //�ַ�����
    codec = QTextCodec::codecForName("GBK");

    //���ñ���
    setWindowTitle(codec->toUnicode("ע��"));

    //����ģ̬
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);

    //���ñ���
    QPixmap pixmap = QPixmap("background.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(palette);

    //���ÿ�ʼ��꼯�����˺ſ�
    ui->lineEditID->setFocus();
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

//�˺�
void RegisterForm::on_lineEditID_textChanged(const QString &arg1)
{
    //��һ���˺ŵ������淶������ʽ
    QRegExp re1("[1-9][0-9]{10}");
    QRegExp re2("[^0a-zA-z][0-9]{0,10}");

    //��׼ƥ��
    if(re1.exactMatch(arg1)||!re2.exactMatch(arg1))
        ui->lineEditID->setText(arg1.left(arg1.length()-1));
}

//����
void RegisterForm::on_lineEditPW_returnPressed()
{
}

//ȷ������
void RegisterForm::on_lineEditRPW_returnPressed()
{
}

//ע��
void RegisterForm::on_btnSure_clicked()
{
    if(ui->lineEditID->text().isEmpty())
        return;

    if(ui->lineEditPW->text() != ui->lineEditRPW->text())
    {
        QMessageBox::information(this,codec->toUnicode("��Ϣ"),codec->toUnicode("���벻һ��"));
        return;
    }


    //��ȡ�˺�����
    QString ID = ui->lineEditID->text();
    QString PW = ui->lineEditPW->text();

    //ƴ���˺�����
    QString Rusult = QString("%1#%2\r\n").arg(ID).arg(PW);

    //���ļ�
    QFile file("C:/code/day03/build-5-17-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ClientInfo.txt");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        cout<<codec->toUnicode("��ʧ��");
        return;
    }

    //����ȡ�ļ���Ϣ
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
            QMessageBox::warning(this,codec->toUnicode("��Ϣ"),codec->toUnicode("�û��Ѵ���!!ע��ʧ��!!!"));
            file.close();
            //this->hide();
            //parentWidget()->show();
            return;
        }
    }

    //�ر��ļ�
    file.close();


    //���ļ�
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    if(!file.isOpen())
    {
        cout<<codec->toUnicode("��ʧ��");
        return;
    }

    //����Ϣд���ļ�
    file.write(Rusult.toStdString().c_str());

    //�ر��ļ�
    file.close();
    QMessageBox::information(this,codec->toUnicode("��Ϣ"),codec->toUnicode("ע��ɹ�"));
    this->hide();
    parentWidget()->show();
}

//����
void RegisterForm::on_btnReturn_clicked()
{
    //Ӱ��ע�����
    hide();
    //��ʾ��¼����
    parentWidget()->show();
}
