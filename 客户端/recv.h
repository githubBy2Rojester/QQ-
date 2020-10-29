#ifndef RECV_H
#define RECV_H

#include <QWidget>

namespace Ui {
class recv;
}

class recv : public QWidget
{
    Q_OBJECT

public:
    explicit recv(QWidget *parent = 0);
    ~recv();

    void getText(QString *text);
    void getName(QString &name);
    void getPhoto(QString &photo);
private:
    Ui::recv *ui;
    QString name;
    QString photo;
};

#endif // RECV_H
