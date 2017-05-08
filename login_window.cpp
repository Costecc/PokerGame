#include "login_window.h"
#include "ui_login_window.h"
#include "register_window.h"
#include "user_window.h"
#include "player.h"

login_window::login_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_window)
{
    ui->setupUi(this);

    QFileInfo checkFile(Path_to_DB);
    if(checkFile.isFile()){
        if(openConnect()){
            ui->result->setText("[+]Connected to Database");
        }

    }else {
        ui->result->setText("[!]Database file doesn't exist");
    }
}

login_window::~login_window()
{
    delete ui;
}


void login_window::on_login_button_clicked()
{
    QString login, password;
    login = ui->txtLogin->text();
    password = ui->txtPassword->text();

    if(!openConnect()){
        qDebug() << "Failed to open db";
        return;
    }

    openConnect(); //opening connection with db
    QSqlQuery qry;
    qry.prepare("SELECT * FROM players_data WHERE login =\'"+login+"\' AND password=\'"+password+"\'");

    if(qry.exec()){
        if(qry.next()){
            ui->result->setText("[+]Valid Login and Password");
            //QString info_login = qry.value(0).toString();
            //QString info_money = qry.value(3).toString();

           // QMessageBox::warning(this, "Login was successful", info_money);
            //Opening new window and hiding login window
            save_to_file(login, "C:\\Users\\Konstanty\\Desktop\\POKER2\\login.txt");
            closeConnect();
            this->close();
            User_window user_window;
            user_window.setModal(true);
            user_window.exec();
        }else{
            ui->result->setText("Niepoprawny login lub hasło!");
        }
    }
}

void login_window::on_register_button_clicked()
{
    register_window registration;
    registration.setModal(true);
    registration.exec();
}
