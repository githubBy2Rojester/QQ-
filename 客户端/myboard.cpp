#include "myboard.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QApplication>
#define cout qDebug()

//��־λ���ó�ȫ�ֱ���  ��Ҫ���ó�˽��
//����һ����ť��  ÿ����ť����һ�������  ����flag����ͬһ��
int flag=0;

myboard::myboard(QWidget *parent) : QPushButton(parent)
{
    //��������ź���ۺ���
    connect(this,SIGNAL(clicked(bool)),this,SLOT(onClickKeyBoard()));
}

void myboard::onClickKeyBoard()
{
    //��ȡ�ĸ���ť����
    myboard* key = qobject_cast<myboard *>(sender());
    //��ť������ı�
    QString text = key->text();
    //��ť���ı���Delete ����һ���˸�����¼���focusWidget
    //�����focusWidget�������ı���
    if(text == QString("Delete"))
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier,text);
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
        return;
    }
    if(text == QString("space"))//�ո�
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Space,Qt::NoModifier," ");
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
        return;
    }
    if(text == QString("Cap"))//��Сд����
    {
        flag++;
        if(flag%2==1)
        {
            key->setStyleSheet("background-color:rgb(50,210,0);");
        }
        else
        {
            key->setStyleSheet("background-color:lightGray");
        }

        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,Qt::Key_CapsLock,Qt::NoModifier,"");
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
        return;
    }
    //���ֺ���ĸ
    std::string keyValue = text.toStdString();
    int value = keyValue.at(0);

    if(flag%2==0)
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,value,Qt::NoModifier,text.at(0).toLower());
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
    }
    else
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,value,Qt::NoModifier,text);
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
    }


}
