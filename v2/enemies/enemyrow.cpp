#include "enemyrow.h"
#include "enemies/enemypurple.h"
#include "enemies/enemyyellow.h"
#include "enemies/enemyred.h"
#include <QTime>
#include <stdlib.h>
#include <cstdlib>

EnemyRow::EnemyRow(int _x, int _y, int _spacing) {
    this->setStartX(_x);
    this->setStartY(_y);
    this->spacing=_spacing;
}

/**
 * @brief EnemyRow::createEnemy create enemy in relation to the type
 * @param _number number of enemy
 * @param _type type 0=purple enemy, 1=yellow enemy, 2=red enemy
 */
void EnemyRow::createEnemy(int _number, int _type) {

    for(int i=0;i<_number;i++) {
        Enemy *enemy;
        if(_type==0) {
            enemy=new EnemyPurple();
            nbPurple=_number;
        }
        else if(_type==1) {
            enemy=new EnemyYellow();
            nbYellow=_number;
        }
        else if(_type==2) {
            enemy=new EnemyRed();
            nbRed=_number;
        }
        enemy->setPos(currentX, currentY);
        this->enemies.append(enemy);
        currentX+=spacing;
    }
}

/**
 * @brief EnemyRow::restart restart level
 */
void EnemyRow::restart() {
    enemies.clear();
    createEnemy(nbPurple, 0);
    createEnemy(nbYellow, 1);
    createEnemy(nbRed, 2);
}

/**
 * @brief EnemyRow::automove start automove enemies
 * @param _dir current direction
 * @param _updateRow if enemies arrives limit of windows, change direction
 */
void EnemyRow::automove(bool _dir, bool _updateRow) {
    if(_updateRow && !enemies.isEmpty()) currentY=enemies.at(0)->y();
    foreach(Enemy *enemy, enemies) {
        enemy->automove(_dir, _updateRow);
    }
}

/**
 * @brief EnemyRow::destroyEnemy destroy enemy
 */
void EnemyRow::destroyEnemy() {
    for(int i=0;i<enemies.size();) {
        Enemy *enemy=enemies.at(i);
        if(enemy->isDestroyed()) {
            enemies.removeAt(i);
            delete enemy;
        } else i++;
    }
}

/**
 * @brief EnemyRow::getMaxXEnemy the last enemy of QList will always be the one to the right of the line
 * @return last index of QList
 */
int EnemyRow::getMaxXEnemy() {
    int size=enemies.size();
    if(size>0) return enemies.at(size-1)->x();
    return -1;
}

//Le premier ennemi du tableau sera toujours celui le plus à gauche de la ligne (première case de la liste)
/**
 * @brief EnemyRow::getMinXEnemy the first enemy of QList will always be the one to the left of the line
 * @return first index of QList
 */
int EnemyRow::getMinXEnemy() {
    int size=enemies.size();
    if(size>0) return enemies.at(0)->x();
    return -1;
}

/**
 * @brief EnemyRow::getEnemies
 * @return QList of enemies
 */
QList<Enemy*> EnemyRow::getEnemies() {
    return enemies;
}

/**
 * @brief EnemyRow::getCurrentYLine
 * @return current line in Y
 */
int EnemyRow::getCurrentYLine() {
    return this->currentY;
}

/**
 * @brief EnemyRow::isEmpty
 * @return if all enemies are dead
 */
bool EnemyRow::isEmpty() {
    return enemies.isEmpty();
}

/**
 * @brief EnemyRow::setStartX the start horizontal position of row
 * @param _xStart position x (horizontal)
 */
void EnemyRow::setStartX(int _xStart) {
    this->currentX=_xStart;
}

/**
 * @brief EnemyRow::setStartY the start vertical position of row
 * @param _yStart position y (vertical)
 */
void EnemyRow::setStartY(int _yStart) {
    this->currentY=_yStart;
}

/**
 * @brief EnemyRow::enemyReadyToFire enemy fire
 */
void EnemyRow::enemyReadyToFire() {
    int min=0;
    int max=enemies.size()-1;
    int enemyFire=(rand()%(max-min+1))+min;
    Enemy *selectedEnemy=enemies.at(enemyFire);
    if(!selectedEnemy->isDestroyed() && !selectedEnemy->isAlreadyFire())
        enemies.at(enemyFire)->fire();
}

/**
 * @brief EnemyRow::resetEnemiesFire reset all enemy fire
 */
void EnemyRow::resetEnemiesFire() {
    foreach(Enemy *enemy, enemies) {
        enemy->resetFire();
    }
}
