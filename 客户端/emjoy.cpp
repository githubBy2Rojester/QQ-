#include "emjoy.h"
#include "ui_emjoy.h"
#include <QDebug>
#include "chat.h"



Emjoy::Emjoy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Emjoy)
{
    ui->setupUi(this);


    //Ŀ¼
    QDir dir("biaoqing");
    QStringList stringList= dir.entryList();

    for(int i=0;i<32;i++)
    {
        //���ַ
        list.append(stringList.at(i+2));
    }


    //�����ź�
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_8,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_9,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_10,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_11,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_12,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_13,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_14,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_15,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_16,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_17,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_18,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_19,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_20,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_21,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_22,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_23,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_24,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_25,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_26,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_27,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_28,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_29,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_30,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_31,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
    connect(ui->pushButton_32,SIGNAL(clicked(bool)),this,SLOT(onClickEmjoy()));
}

Emjoy::~Emjoy()
{
    delete ui;
}



//����˱���
void Emjoy::onClickEmjoy()
{
    //��ȡ�ĸ���ť����
    QPushButton* key = qobject_cast<QPushButton*>(sender());

    //��ť������ı�
    QString text = key->text();

    //��ȡͼƬ��
    QString iconName = list.at(text.toInt()-1);

    //ͼƬ·��
    path = QString("C:/code/day03/build-5-18-Desktop_Qt_5_7_0_MinGW_32bit-Debug/biaoqing/%1").arg(iconName);

    //���ø��������ı���ť
    //�ѻ�ȡ���ĵ�ַ��������
    qobject_cast<CHAT*> (this->parentWidget())->emjoyPath(path);
    qobject_cast<CHAT*> (this->parentWidget())->emjoyFlagAdd();

    //�ر�
    this->close();

}
