#include "terminal.h"
#include "ui_terminal.h"
#include <QDebug>
#include <QPushButton>


Terminal::Terminal(QWidget *parent) : QMainWindow(parent), ui(new Ui::Terminal) {
    ui->setupUi(this);
//    ui->Display->setMaxLength(4);

    QPushButton *numButtons[10];

    for(int i=0 ; i < 10 ; i++){
        QString butName = "Button" + QString::number(i);

        //Finding specific children of Widget by providing a name
        //Casting beacause of casting
        numButtons[i] = Terminal::findChild<QPushButton *>(butName);

        //Whenever button is released, call NumPressed();
        //connect usign SIGNAL, whevener button is released
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    QPushButton *buttonClear = Terminal::findChild<QPushButton *>("ButtonClear");

    connect(buttonClear, SIGNAL(released()), this, SLOT(ClearPressed()));

//    ui->Display->setText("Insert card");
}

Terminal::~Terminal() {
    delete ui;
}

void Terminal::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();


    if((displayVal + butVal).size() <= 4){
        ui->Display->setText(displayVal + butVal);
    }

    ui->DisplayLog->appendPlainText("Button " + butVal + " has been pressed.");

}

void Terminal::ClearPressed(){
    ui->Display->setText("");
    ui->DisplayLog->appendPlainText("Clear button has been pressed.");
}
