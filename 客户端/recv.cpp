#include "recv.h"
#include "ui_recv.h"

recv::recv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recv)
{
    ui->setupUi(this);
}

recv::~recv()
{
    delete ui;
}

void recv::getText(QString *text)
{   
    ui->textBrowser->setText(*text);
    ui->textBrowser->setAlignment(Qt::AlignLeft);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//»ñÈ¡Ãû×Ö
void recv::getName(QString &name)
{
    this->name = name;
    ui->label->setText(name);
    ui->label->setAlignment(Qt::AlignLeft);
}

void recv::getPhoto(QString &photo)
{
    this->photo = photo;
    ui->pushButton->setStyleSheet(QString("border-image:url(%1)").arg(photo));
}
