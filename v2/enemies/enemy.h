#ifndef ENEMY_H
#define ENEMY_H

#include "item.h"

class Enemy : public Item {
    Q_OBJECT
public:
    Enemy(QGraphicsItem *_parent=0);
    virtual ~Enemy();

    bool isAlreadyFire();
    void resetFire();

    void init();
    void fire();
    void automove(bool _dir, bool _updateRow);
    void setLife(int _life);
    void loseLife(int _loseLife);

private:
    bool alreadyFire;
};

#endif // ENEMY_H
