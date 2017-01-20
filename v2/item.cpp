#include "item.h"
#include <QGraphicsScene>

Item::Item(QGraphicsItem *_parent) : QGraphicsPixmapItem(_parent) {}

Item::~Item() {}

void Item::fire() {}

void Item::init() {}

void Item::setLife(int) {}

void Item::destroy() {
    scene()->removeItem(this);
    this->isDestroy=true;
}

bool Item::isDestroyed() {
    return this->isDestroy;
}

int Item::getLife() {
    return life;
}

void Item::loseLife(int _loseLife) {
    int newLife=life-_loseLife;
    this->setLife(newLife);
}
