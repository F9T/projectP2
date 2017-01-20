#include "bulletplayer.h"
#include "enemies/enemypurple.h"
#include "enemies/enemyred.h"
#include "enemies/enemyyellow.h"
#include <typeinfo>
#include <QGraphicsScene>

/**
 * @brief BulletPlayer::BulletPlayer constructor
 * @param _parent
 */
BulletPlayer::BulletPlayer(QGraphicsItem *_parent) : Bullet(_parent) {
    setPixmap(QPixmap(":/images/bulletPlayer.png"));
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(automove()));
    timer->start(50);
}

/**
 * @brief BulletPlayer::~BulletPlayer destructor
 */
BulletPlayer::~BulletPlayer() {
    timer->stop();
    delete timer;
}

/**
 * @brief BulletPlayer::automove move bullet player with QTimer
 */
void BulletPlayer::automove() {
    QList<QGraphicsItem *> colliding = collidingItems();

    foreach(QGraphicsItem *item, colliding) {
        //If a enemy is colliding
        if (typeid(*item) == typeid(EnemyPurple) || typeid(*item)==typeid(EnemyYellow) || typeid(*item)==typeid(EnemyRed)){
            Enemy *enemy=dynamic_cast<Enemy*>(item);

            enemy->loseLife(1);
            if(enemy->getLife()<=0) {
               enemy->destroy();
            }
            scene()->removeItem(this);
            delete this;

            return;
        }
    }
    //If bullet is out of window
    setPos(x(),y()-this->boundingRect().height());
    if (pos().y() < 0){
       scene()->removeItem(this);
       delete this;
    }
}
