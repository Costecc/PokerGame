#include "game.h"
#include "ui_game.h"
#include "user_window.h"
#include "login_window.h"

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

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    //this->setStyleSheet("QDialog{background-image: url(':\img\img\24.png');}");
}

Game::~Game()
{
    delete ui;
}
