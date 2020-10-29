#ifndef EMJOY_H
#define EMJOY_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QDir>
#include <QFileInfo>

namespace Ui {
class Emjoy;
}

class Emjoy : public QWidget
{
    Q_OBJECT

public:
    explicit Emjoy(QWidget *parent = 0);
    ~Emjoy();

private slots:
    void onClickEmjoy();

private:
    Ui::Emjoy *ui;
    QList<QString> list;
    QString path;
};

#endif // EMJOY_H
