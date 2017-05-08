#ifndef ACCOUNT_WINDOW_H
#define ACCOUNT_WINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

#define Path_to_DB "C:/SQLite/players.sqlite"

namespace Ui {
class account_window;
}

class account_window : public QDialog
{
    Q_OBJECT

public:
    explicit account_window(QWidget *parent = 0);
    ~account_window();

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

private slots:
    void on_logout_button_clicked();
    void showTime();

private:
    Ui::account_window *ui;
};

#endif // ACCOUNT_WINDOW_H
