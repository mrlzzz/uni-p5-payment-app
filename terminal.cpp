#include "terminal.h"
#include "ui_terminal.h"
#include "transblock.h"
#include <QDebug>
#include <QPushButton>
#include <QDate>
#include <QTime>


Terminal::Terminal(QWidget *parent) : QMainWindow(parent), ui(new Ui::Terminal) {

    ui->setupUi(this);

    //Transportation Block created
    tBlock.setTerminalID("TERXXAA0001");

    //CREATE AND ASSIGN NUM BUTTONS

    QPushButton *numButtons[10];

    for(int i=0 ; i < 10 ; i++){
        QString butName = "Button" + QString::number(i);

        //Finding specific children of Widget by providing a name
        //Casting because of casting
        numButtons[i] = Terminal::findChild<QPushButton *>(butName);

        //Whenever button is released, call NumPressed();
        //connect usign SIGNAL, whevener button is released
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    //CREATE AND ASSIGN THE REST OF BUTTONS

    QPushButton *buttonClear = Terminal::findChild<QPushButton *>("ButtonClear");
    QPushButton *buttonConfirm = Terminal::findChild<QPushButton *>("ButtonConfirm");
    QPushButton *buttonInit = Terminal::findChild<QPushButton *>("ButtonInit");

    connect(buttonClear, SIGNAL(released()), this, SLOT(ClearPressed()));
    connect(buttonConfirm, SIGNAL(released()), this, SLOT(ConfirmPressed()));
    connect(buttonInit, SIGNAL(released()), this, SLOT(InitPressed()));
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

void Terminal::ClearPressed() {
    ui->Display->setText("");
    ui->DisplayLog->appendPlainText("Clear button has been pressed.");
}

void Terminal::ConfirmPressed() {

    QDate date = date.currentDate();
    QTime time = time.currentTime();

    tBlock.setTimestamp(date.toString() + " " + time.toString());
    tBlock.setPIN(ui->Display->text());

    ui->DisplayLog->appendPlainText("Timestamp: " + tBlock.getTimestamp());
    ui->DisplayLog->appendPlainText("Amount: " + QString::number(tBlock.getAmount()));
    ui->DisplayLog->appendPlainText("Currency: " + tBlock.getCurrency());
    ui->DisplayLog->appendPlainText("TerminalID: " + tBlock.getTerminalID());
    ui->DisplayLog->appendPlainText("PAN: " + tBlock.getPAN());
    ui->DisplayLog->appendPlainText("Encrypted :) PIN: " + tBlock.getPIN());

}

void Terminal::InitPressed() {
    /*
        ### Hardcoded should be not. ###

        Later:

            Get amount and currency from merchant
            Currency should be represented by code
            Figure out terminal ID - rand number? any scheme to create?
            Get enc PIN from enc method

     */

    tBlock.setAmount(100);
    tBlock.setCurrency("DKK");
    tBlock.setPAN("1234-****-****-4231");

    ui->DisplayAmount->setText(QString::number(tBlock.getAmount()) + " " + tBlock.getCurrency());
    ui->DisplayLog->appendPlainText("Transaction initialized.");
}

//void Terminal::createTransBlock() {



//    QDate timestamp = timestamp.currentDate();


//    transBlock tBlock = new transBlock();
//}

/*
    Transportation Block (TB)

    1. Timestamp       - QDATE Type
    2. Amount          - INT
    3. Amount exponent - ???
    4. Currency code   - INT
    5. Terminal ID     - STRING OR some QTYPE
    6. PAN             - QByteArray
    7. Encrypted PIN   - QByteArray
    8. Retail MAC      - ???

    ### Use terminalWrapper for Terminal logic - seperate GUI handling from logic ###
    ### When is it created? - After Confirm button click ###
    ### Before Confirm button click, check fields are correct ###
  */

Terminal::~Terminal() {
    delete ui;
}
















