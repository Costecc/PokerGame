#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include "login_window.h"

#define Path_to_DB "C:/SQLite/players.sqlite"

namespace Ui {
class register_window;
}

class register_window : public QDialog
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

public:
    explicit register_window(QWidget *parent = 0);
    ~register_window();

private slots:
    void on_login_button_r_clicked();

    void on_register_button_r_clicked();

private:
    Ui::register_window *ui;
};

#endif // REGISTER_WINDOW_H
