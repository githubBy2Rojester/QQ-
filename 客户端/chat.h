#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTextCodec>

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
#include <QCloseEvent>
#include <QList>
#include <QScrollArea>//»¬¶¯ÈÝÆ÷
#include <QScrollBar>
#include "recv.h"
#include "send.h"
#include "emjoy.h"
#include "mykeyboard.h"

namespace Ui {
class CHAT;
}

class CHAT : public QWidget
{
    Q_OBJECT

public:
    explicit CHAT(QWidget *parent = 0);
    ~CHAT();

    void getAccount(QString account);
    void getPhoto(QString &photo);
    void emjoyFlagAdd();
    void closeEvent(QCloseEvent *event);
    void emjoyPath(QString &path);

private slots:
    void NameToServer();
    void receverFromServer();
    void on_listWidgetFriend_doubleClicked(const QModelIndex &index);
    void on_btnSend_clicked();

    void on_btnEmjoy_clicked();

    void on_btnKey_clicked();

private:
    Ui::CHAT *ui;

    QTcpSocket *tcpSocket;
    QTextCodec *codec;

    QScrollArea *scrollArea;//¹ö¶¯ÈÝÆ÷
    QWidget *scrollAreaCentralContents;
    send *snder;
    recv *recvr;
    Emjoy *emjoy;
    mykeyboard *keyboard;

    QString Account;
    QString photo;
    QString chatForm;
    QString path;

    QMap<quint16,QString> clientContents;

    int talkflag;
    int y_off;
    int emjoyflag;
    int keyflag;
};

#endif // CHAT_H
