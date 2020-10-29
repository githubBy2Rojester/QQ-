#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QMessageBox>

#include <QTextCodec>

#include <QDebug>
#define cout qDebug()
#include "chat.h"

#include <QTime>
#include <QTimer>
#include "mykeyboard.h"
#include "registerform.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_btnLogin_clicked();

    void on_btnPWEcho_clicked();

    void on_btnKey_clicked();

    void on_btnRegister_clicked();

    void on_btnImage_clicked();

private:
    Ui::Login *ui;
    QTextCodec *codec;
    CHAT *chat;
    QTimer timer;
    mykeyboard *keyboard;
    RegisterForm *registerForm;
    QString photoPath;
    int keyFlag;
    int echoFlag;
};

#endif // LOGIN_H
