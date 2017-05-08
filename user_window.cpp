#include "user_window.h"
#include "ui_user_window.h"
#include "login_window.h"
#include "game.h"
#include "register_window.h"

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

User_window::User_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User_window)
{
    ui->setupUi(this);
    //Getting login
    QFile file("C:\\Users\\Konstanty\\Desktop\\POKER2\\login.txt"); //double slashes
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "Info", file.errorString());
    }

    QTextStream in(&file);
    ui->welcome_user->setText(in.readAll());

    QString login = ui->welcome_user->text();

    if(!openConnect()){
        qDebug() << "Failed to open db";
        return;
    }

   //openConnect(); //opening connection with db
    QSqlQuery qry;
    qry.prepare("SELECT * FROM players_data WHERE login =\'"+login+"\'");

    if(qry.exec()){
        if(qry.next()){
            //ui->result->setText("[+]Valid Login");
            QString info_money = qry.value(3).toString();
            ui->money_ammount->setText(info_money);
            //QMessageBox::warning(this, "Login was successful", info_money);
            //Opening new window and hiding login window
            // save_to_file(login, "C:\\Users\\Konstanty\\Desktop\\POKER2\\login.txt");
            closeConnect();
          //  User_window user_window;
           // user_window.setModal(true);
//            user_window.exec();
        }else{
           // ui->result->setText("Niepoprawny login lub hasło!");
        }
    }


    // Setting timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
}

void User_window::showTime(){
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->digital_clock->setText(time_text);
}

User_window::~User_window()
{
    delete ui;
}

void User_window::on_logout_button_clicked()
{
    this->close();
}

void save_to_file(QString what, QString name_of_file){
    QFile plik(name_of_file);
    plik.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QTextStream stream(&plik);
    stream << what;

    plik.close();
}

QSqlDatabase db;
bool openConnect(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Path_to_DB);
    QFileInfo checkFile(Path_to_DB);

    if(checkFile.isFile()){
        if(db.open()){
            qDebug()<<"[+]Connected to Database";
            return true;
        }

    }else {
        qDebug()<<"[!]Database file doesn't exist";
        return false;
    }
}
void closeConnect(){
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

/*
void save_money_to_base(QString what, QString login){
    openConnect(); //opening connection with db
    QSqlQuery qry;
    qry.prepare("UPDATE players_data SET money = '"+what+"' where login= \'"+login+"\'");
    closeConnect();
}*/

bool User_window::startPlay(int rate, int &money){
    if(rate > money){
        QMessageBox::critical(this, "Brak środków", "Uzupełnij stan konta!");
    }
    else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Wpisowe 1000$", "Czy na pewno chcesz wejść do gry?<br> Nie ma możliwości wyrejestrowania się.",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            money-=rate;
            save_to_file(QString::number(rate), "C:\\Users\\Konstanty\\Desktop\\POKER2\\rate.txt");
            QString s = QString::number(money);
            ui->money_ammount->setText(s);
            return true;
        }
    }
    return false;
}

void User_window::on_pushButton_clicked()
{
    int money;
    QString moneys = ui->money_ammount->text();
    money = moneys.split(" ")[0].toInt();
    QMessageBox::information(this, "Login was successful", QString::number(money));

    if(ui->rate1->isChecked() && startPlay(1000, money)){
      // QString login = ui->welcome_user->text();
      // QString s = QString::number(money);
       Game new_game;
       new_game.setModal(true);
       new_game.exec();
    }


QString s = QString::number(money);
    QString login = ui->welcome_user->text();
    QMessageBox::warning(this, "ee", s);
    //save_money_to_base(s, login);
    openConnect(); //opening connection with db
    QSqlQuery qry1;
    qry1.prepare("UPDATE players_data SET money = "+s+" WHERE login =\'"+login+"\'");
    if(qry1.exec()){
         QMessageBox::warning(this, "ee", "elo");
    }
    closeConnect();

    //Poker_login conn;

/*
    if(!conn.openConnect()){
        qDebug() << "Failed to open db";
        return;
    }

    conn.openConnect(); //opening connection with db
    QSqlQuery qry;
    qry.prepare("UPDATE players_data SET login = '"+login+"', password = '"+password+"', email = '"+email+"', money = '"+money+"' WHERE login = '"+login+"' AND email = '"+email+"'");

    if(qry.exec()){
        QMessageBox::critical(this, tr("Update"), tr("Updated"));
    }
    else {
        QMessageBox::critical(this, tr("Error::"), qry.lastError().text());
    }
    conn.closeConnect();*/
}
