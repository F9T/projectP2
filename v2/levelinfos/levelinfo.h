#ifndef LEVELINFO_H
#define LEVELINFO_H

#include "enemies/enemyrow.h"
#include "levelinfos/rowinfo.h"

class LevelInfo {
public:
    LevelInfo();

    void setNumber(int _number);
    void setXStart(int _x);
    void setYStart(int _y);
    void setXSpacing(int _spacing);
    void setYSpacing(int _spacing);
    void setSpeed(int _speed);
    void setInterval(QString _interval);
    void setReloadTime(int _reloadTime);
    void setMaxSimultFire(int _max);

    int getReloadTime() const;
    int getNumber() const;
    int getMinInterval() const;
    int getMaxInterval() const;
    int getMaxSimultFire() const;

    void addEnemyRow(int _nbPurle, int _nbYellow, int _nbRed);
    QList<EnemyRow*> generateLevel();

private:
    int number, xStart, yStart, spacingX, spacingY, speedEnemy, currentYRow, minInterval, maxInterval, reloadTime, maxSimultFire;
    QList<RowInfo*> listRowInfos;
};

#endif // LEVELINFO_H
