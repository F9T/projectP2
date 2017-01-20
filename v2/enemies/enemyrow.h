#ifndef ENEMYROW_H
#define ENEMYROW_H

#include <QList>
#include "enemies/enemy.h"

class EnemyRow {
public:
    EnemyRow(int _x, int _y, int _spacing);

    //0->purple, 1->yellow, 2->red
    void createEnemy(int _number, int _type);
    void addEnemy(Enemy *_enemy);
    void automove(bool _dir, bool _updateRow);
    void destroyEnemy();
    int getMaxXEnemy();
    int getMinXEnemy();
    QList<Enemy*> getEnemies();
    int getCurrentYLine();
    bool isEmpty();
    void setStartX(int _xStart);
    void setStartY(int _yStart);
    void restart();
    void enemyReadyToFire();
    void resetEnemiesFire();

private:
    int currentX, currentY, spacing, nbPurple, nbYellow, nbRed;
    QList<Enemy*> enemies;
};

#endif // ENEMYROW_H
