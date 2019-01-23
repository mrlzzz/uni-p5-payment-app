#ifndef TERMINAL_H
#define TERMINAL_H

#include <QMainWindow>
#include "transblock.h"


namespace Ui {
class Terminal;
}

class Terminal : public QMainWindow
{
    Q_OBJECT
    TransBlock tBlock;

public:
    explicit Terminal(QWidget *parent = nullptr);
    ~Terminal();
    void createTransBlock();
    QString pinEncode(QString);
    QString testAES(QByteArray);

private:
    Ui::Terminal *ui;
private slots:
    void NumPressed();
    void ClearPressed();
    void ConfirmPressed();
    void InitPressed();
    void CardPressed();

};

#endif // TERMINAL_H
