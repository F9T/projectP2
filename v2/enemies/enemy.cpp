#include "enemy.h"
#include "bullets/bulletenemy.h"
#include <QGraphicsScene>

Enemy::Enemy(QGraphicsItem *_parent) : Item(_parent) {
    this->init();
}

Enemy::~Enemy() {}

/**
 * @brief Enemy::automove auto move enemy right to left or left to right
 * @param _dir acutel direction (left-right=true or right-left=false)
 * @param _updateRow enemies arrives limit of windows, they go down
 */
void Enemy::automove(bool _dir, bool _updateRow) {
    int newX=x();
    int newY=y();
    if(_updateRow) newY+=40;
    if(_dir) newX+=moveX;
    else newX-=moveX;
    setPos(newX, newY);
}

/**
 * @brief Enemy::init initialisation
 */
void Enemy::init() {
    this->isDestroy=false;
    this->alreadyFire=false;
    this->moveX=5;
}

/**
 * @brief Enemy::fire enemy fire
 */
void Enemy::fire() {
    if(!alreadyFire) {
        BulletEnemy *bullet = new BulletEnemy();
        //Bullet's positon is center position of enemy
        bullet->setPos((x()+(this->boundingRect().width()/2))-(bullet->boundingRect().width()/2), y()-bullet->boundingRect().height());
        scene()->addItem(bullet);
        this->alreadyFire=true;
    }
}

/**
 * @brief Enemy::setLife life of enemy
 * @param _life life of enemy
 */
void Enemy::setLife(int _life) {
    this->life=_life;
}

/**
 * @brief Enemy::loseLife number of live lose
 * @param _loseLife
 */
void Enemy::loseLife(int _loseLife) {
    int newLife=life-_loseLife;
    this->setLife(newLife);
}

/**
 * @brief Enemy::isAlreadyFire if the enemy has already fire
 * @return
 */
bool Enemy::isAlreadyFire() {
    return alreadyFire;
}

/**
 * @brief Enemy::resetFire reset enemy alreadyFire
 */
void Enemy::resetFire() {
    this->alreadyFire=false;
}
