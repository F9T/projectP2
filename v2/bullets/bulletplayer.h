#ifndef BULLETPLAYER_H
#define BULLETPLAYER_H

#include "bullet.h"

class BulletPlayer : public Bullet {
    Q_OBJECT
public:
    BulletPlayer(QGraphicsItem *_parent=0);
    ~BulletPlayer();

protected slots:
    void automove();
};

#endif // BULLETPLAYER_H
