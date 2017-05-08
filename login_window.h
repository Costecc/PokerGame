#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
//#include "register_window.h"
//#include "account_window.h"
#include <QFileDialog>

#define Path_to_DB "C:/SQLite/players.sqlite"

namespace Ui {
class login_window;
}

class login_window : public QMainWindow
{
    Q_OBJECT

public:
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

    void save_to_file(QString what, QString name_of_file){
        QFile plik(name_of_file);
        plik.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        QTextStream stream(&plik);
        stream << what;

        plik.close();
    }

public:
    explicit login_window(QWidget *parent = 0);
    ~login_window();

private slots:


    void on_login_button_clicked();

    void on_register_button_clicked();

private:
    Ui::login_window *ui;
};

#endif // LOGIN_WINDOW_H
