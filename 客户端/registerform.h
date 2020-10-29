#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <QTextCodec>	//�ַ�����
#include <QFile>		//�ļ�
#include <QMessageBox>	//��Ϣ����
#include <QDebug>		//�������
#define cout qDebug()
#include <QPixmap>		//����
#include <QPalette>		//��ɫ��
#include <QBrush>		//��ˢ

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
