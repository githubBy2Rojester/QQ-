#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <QTextCodec>	//字符编码
#include <QFile>		//文件
#include <QMessageBox>	//消息盒子
#include <QDebug>		//测试语句
#define cout qDebug()
#include <QPixmap>		//画布
#include <QPalette>		//调色板
#include <QBrush>		//画刷

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = 0);
    ~RegisterForm();

private slots:
    void on_lineEditID_textChanged(const QString &arg1);

    void on_lineEditPW_returnPressed();

    void on_lineEditRPW_returnPressed();

    void on_btnSure_clicked();

    void on_btnReturn_clicked();

private:
    Ui::RegisterForm *ui;
};

#endif // REGISTERFORM_H
