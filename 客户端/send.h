#ifndef SEND_H
#define SEND_H

#include <QWidget>

namespace Ui {
class send;
}

class send : public QWidget
{
    Q_OBJECT

public:
    explicit send(QWidget *parent = 0);
    ~send();

    void getText(QString &text);
    void getName(QString &name);
    void getPhoto(QString &photo);

private:
    Ui::send *ui;
    QString name;
    QString photo;
};

#endif // SEND_H
