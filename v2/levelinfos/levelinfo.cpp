#include "levelinfo.h"

LevelInfo::LevelInfo() {}

/**
 * @brief LevelInfo::addEnemyRow add all enemies in the row
 * @param nbPurple number of purple enemy (type=0)
 * @param nbYellow number of yellow enemy (type=1)
 * @param nbRed number of red enemy (type=2)
 */
void LevelInfo::addEnemyRow(int nbPurple, int nbYellow, int nbRed) {
    listRowInfos.append(new RowInfo(nbPurple, nbYellow, nbRed));
}

/**
 * @brief LevelInfo::generateLevel geenrate level
 * @return QList of all rows enemies
 */
QList<EnemyRow*> LevelInfo::generateLevel() {
    currentYRow=yStart;
    QList<EnemyRow*> rowsEnemies;
    foreach(RowInfo *rowInfo, listRowInfos) {
        EnemyRow *rowEnemy=new EnemyRow(xStart, currentYRow, spacingX);
        rowEnemy->createEnemy(rowInfo->getNumberPurple(), 0);
        rowEnemy->createEnemy(rowInfo->getNumberYellow(), 1);
        rowEnemy->createEnemy(rowInfo->getNumberRed(), 2);
        rowsEnemies.append(rowEnemy);
        currentYRow+=spacingY;
    }
    return rowsEnemies;
}

void LevelInfo::setNumber(int _number) {
    this->number=_number;
}

void LevelInfo::setSpeed(int _speed) {
    this->speedEnemy=_speed;
}

void LevelInfo::setXSpacing(int _spacing) {
    this->spacingX=_spacing;
}

void LevelInfo::setYSpacing(int _spacing) {
    this->spacingY=_spacing;
}

void LevelInfo::setXStart(int _x) {
    this->xStart=_x;
}

void LevelInfo::setYStart(int _y) {
    this->yStart=_y;
    this->currentYRow=_y;
}

void LevelInfo::setReloadTime(int _reloadTime) {
    this->reloadTime=_reloadTime;
}

/**
 * @brief LevelInfo::setInterval set interval of two fire enemy, default interval [1500;3000]
 * @param _interval
 */
void LevelInfo::setInterval(QString _interval) {
    QList<QString> intervals=_interval.split(";");
    if(intervals.size()==2) {
        minInterval=intervals.at(0).toInt();
        maxInterval=intervals.at(1).toInt();
        if(minInterval>maxInterval) {
            int temp=minInterval;
            minInterval=maxInterval;
            maxInterval=temp;
        }
    } else {
        minInterval=1500;
        maxInterval=3000;
    }
}

void LevelInfo::setMaxSimultFire(int _max) {
    this->maxSimultFire=_max;
}

int LevelInfo::getNumber() const {
    return number;
}

int LevelInfo::getMaxInterval() const {
    return maxInterval;
}

int LevelInfo::getMinInterval() const {
    return minInterval;
}

int LevelInfo::getReloadTime() const {
    return reloadTime;
}

int LevelInfo::getMaxSimultFire() const {
    return maxSimultFire;
}
