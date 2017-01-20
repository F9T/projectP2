#ifndef ENEMYRED_H
#define ENEMYRED_H

#include "enemy.h"

class EnemyRed : public Enemy {
    Q_OBJECT

public:
    EnemyRed(QGraphicsItem *_parent=0);
    ~EnemyRed();

protected:
    void init();
};

#endif // ENEMYRED_H
