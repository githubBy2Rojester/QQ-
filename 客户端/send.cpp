#include "send.h"
#include "ui_send.h"

send::send(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::send)
{
    ui->setupUi(this);
}

send::~send()
{
    delete ui;
}

void send::getText(QString &text)
{   
    ui->textBrowser->setText(text);
    ui->textBrowser->setAlignment(Qt::AlignRight);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->textBrowser->setEnabled(false);
}

//��ȡ��¼�ͻ��˵�����
void send::getName(QString &name)
{
    this->name = name;
    ui->label->setText(this->name);
    ui->label->setAlignment(Qt::AlignRight);
}

//��ȡ�Լ���ͷ��
void send::getPhoto(QString &photo)
{
    this->photo = photo;
    ui->pushButton->setStyleSheet(QString("border-image:url(%1)").arg(photo));
}
