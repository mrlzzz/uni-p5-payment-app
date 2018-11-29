#ifndef TERMINAL_H
#define TERMINAL_H

#include <QMainWindow>

namespace Ui {
class Terminal;
}

class Terminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Terminal(QWidget *parent = nullptr);
    ~Terminal();

private:
    Ui::Terminal *ui;
private slots:
    void NumPressed();
    void ClearPressed();

};

#endif // TERMINAL_H
