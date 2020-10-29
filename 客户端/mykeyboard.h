#ifndef MYKEYBOARD_H
#define MYKEYBOARD_H

#include <QWidget>

namespace Ui {
class mykeyboard;
}

class mykeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit mykeyboard(QWidget *parent = 0);
    ~mykeyboard();


private:
    Ui::mykeyboard *ui;
};

#endif // MYKEYBOARD_H
