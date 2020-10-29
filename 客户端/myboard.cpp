#include "myboard.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QApplication>
#define cout qDebug()

//标志位设置成全局变量  不要设置成私有
//这是一个按钮类  每个按钮都是一个类对象  所以flag不是同一个
int flag=0;

myboard::myboard(QWidget *parent) : QPushButton(parent)
{
    //关联点击信号与槽函数
    connect(this,SIGNAL(clicked(bool)),this,SLOT(onClickKeyBoard()));
}

void myboard::onClickKeyBoard()
{
    //获取哪个按钮对象
    myboard* key = qobject_cast<myboard *>(sender());
    //按钮对象的文本
    QString text = key->text();
    //按钮的文本是Delete 发送一个退格键盘事件给focusWidget
    //这里的focusWidget可以是文本框
    if(text == QString("Delete"))
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier,text);
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
        return;
    }
    if(text == QString("space"))//空格
    {
        QKeyEvent *keyevent = new  QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Space,Qt::NoModifier," ");
        QCoreApplication::postEvent(QApplication::focusWidget(),keyevent);
        return;
    }
    if(text == QString("Cap"))//大小写锁键
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
    //数字和字母
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
