#include "account_window.h"
#include "ui_account_window.h"
#include "login_window.h"
#include "login_window.cpp"

#include <QDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>

account_window::account_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account_window)
{

    //Getting login
    QFile file("C:\\Users\\Konstanty\\Desktop\\POKER2\\login.txt"); //double slashes
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "Info", file.errorString());
    }

    QTextStream in(&file);
    ui->welcome_user->setText("Witaj " + in.readAll());
    // Setting timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
    //Getting money
    account_window conn1;
    conn1.openConnect(); //opening connection with db
    QString login = ui->welcome_user->text();
    QSqlQuery qry1;
    qry1.prepare("SELECT money FROM players_data WHERE login =\'"+login+"\'");
    conn1.closeConnect();

}

void account_window::showTime(){
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->digital_clock->setText(time_text);
}

account_window::~account_window()
{
    delete ui;
}

void account_window::on_logout_button_clicked()
{
    this->close();
}
