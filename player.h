#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
private:
    //Basic user data
    QString login;
    QString password;
    int money;
    //Time to update ammount of money
    QString time_to_update;
    //Needed to rank
    int games_ammount;
    int money_won;
public:
    void showRank(QString login);
    void getData();
};

#endif // PLAYER_H
