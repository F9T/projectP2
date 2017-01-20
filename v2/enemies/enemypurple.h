#ifndef ENEMYPURPLE_H
#define ENEMYPURPLE_H

#include "enemy.h"

class EnemyPurple : public Enemy {
     Q_OBJECT
public:
    EnemyPurple(QGraphicsItem *_parent=0);
    ~EnemyPurple();

protected:
    void init();
};

#endif // ENEMYPURPLE_H
