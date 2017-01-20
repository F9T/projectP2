#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "bullet.h"

class BulletEnemy : public Bullet {
    Q_OBJECT

public:
    BulletEnemy(QGraphicsItem *_parent=0);
    ~BulletEnemy();

protected slots:
    void automove();
};

#endif // BULLETENEMY_H
