#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCodec>

#include <QTcpServer>
#include <QTcpSocket>

#include <QPixmap>
#include <QBrush>
#include <QPalette>
#include <QMap>

#include <QHostAddress>
#include <QListWidgetItem>
#include <QIcon>

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QDebug>
#define cout qDebug()

#include <QMessageBox>
#include <QStringList>
#include <QList>
#include <QTest>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void loadingExistClient();
private slots:
    void ClientLink();
    void receiveFromClient();
    void sendClientName();

private:
    Ui::Widget *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QTcpSocket *sendr;

    QTextCodec *codec;
    QMap<QTcpSocket*,QString> clientContents;
    QList<QString> allClientName;
    QTimer timer;
    //QString currentName;
    QString clientName;
    QString deleteName;
    int timerflag;
};

#endif // WIDGET_H
