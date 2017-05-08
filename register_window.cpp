#include "register_window.h"
#include "ui_register_window.h"

register_window::register_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_window)
{
    ui->setupUi(this);

    QFileInfo checkFile(Path_to_DB);
    if(checkFile.isFile()){
        if(openConnect()){
            ui->result_r->setText("[+]Connected to Database");
        }

    }else {
        ui->result_r->setText("[!]Database file doesn't exist");
    }
}

register_window::~register_window()
{
    delete ui;
}
//
void register_window::on_login_button_r_clicked()
{
    this->hide();
}

void register_window::on_register_button_r_clicked()
{
   register_window conn;

    QString login, password, email;
    login = ui->add_login_r->text();
    password = ui->add_password_r->text();
    email = ui->add_email_r->text();

    if(!conn.openConnect()){
        qDebug() << "Failed to open db";
        return;
    }

    conn.openConnect(); //opening connection with db
    QSqlQuery qry;
    qry.prepare("INSERT INTO players_data (login, password, email) VALUES ('"+login+"', '"+password+"', '"+email+"')");

    if(qry.exec()){
        QMessageBox::critical(this, tr("Rejestracja"), tr("Pomyślnie zarejestrowano. Dziękujemy!"));
    }
    else {
        QMessageBox::critical(this, tr("Błąd rejestracji"), tr("Ten login lub email został już wykorzystany!"));
    }
    conn.closeConnect();
}
