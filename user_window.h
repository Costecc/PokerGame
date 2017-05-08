#ifndef USER_WINDOW_H
#define USER_WINDOW_H

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
class User_window;
}

class User_window : public QDialog
{
    Q_OBJECT

int money;

public:
    explicit User_window(QWidget *parent = 0);
    ~User_window();

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
    bool startPlay(int rate, int &money);
private slots:
    void on_logout_button_clicked();

    void showTime();

    void on_pushButton_clicked();

private:
    Ui::User_window *ui;
};

#endif // USER_WINDOW_H
