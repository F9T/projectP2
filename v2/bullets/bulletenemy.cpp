#include "bulletenemy.h"
#include "player.h"
#include <typeinfo>
#include <QGraphicsScene>

/**
 * @brief BulletEnemy::BulletEnemy constructor
 * @param _parent
 */
BulletEnemy::BulletEnemy(QGraphicsItem *_parent) : Bullet(_parent) {
    setPixmap(QPixmap(":/images/bulletEnemy.png"));
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(automove()));
    timer->start(50);
}

/**
 * @brief BulletEnemy::~BulletEnemy destructor
 */
BulletEnemy::~BulletEnemy() {
    timer->stop();
    delete timer;
}

/**
 * @brief BulletEnemy::automove move bullet enemy with QTimer
 */
void BulletEnemy::automove() {
    QList<QGraphicsItem *> colliding = collidingItems();

    foreach(QGraphicsItem *item, colliding) {
        //If a enemy is colliding
        if (typeid(*item) == typeid(Player)){
            Player *player=dynamic_cast<Player*>(item);

            player->loseLife(1);
            if(player->getLife()<=0) {
               player->destroy();
            }
            scene()->removeItem(this);
            delete this;

            return;
        }
    }
    //If bullet is out of window
    setPos(x(),y()+this->boundingRect().height());
    if (pos().y() > scene()->height()){
       scene()->removeItem(this);
       delete this;
    }
}
