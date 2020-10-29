#ifndef MYBOARD_H
#define MYBOARD_H

#include <QWidget>
#include <QPushButton>

class myboard : public QPushButton
{
    Q_OBJECT
public:
    explicit myboard(QWidget *parent = 0);


private slots:
    void onClickKeyBoard();


};

#endif // MYBOARD_H
