#ifndef ENEMYYELLOW_H
#define ENEMYYELLOW_H

#include "enemy.h"

class EnemyYellow : public Enemy {
    Q_OBJECT

public:
    EnemyYellow(QGraphicsItem *_parent=0);
    ~EnemyYellow();

protected:
    void init();
};

#endif // ENEMYYELLOW_H
