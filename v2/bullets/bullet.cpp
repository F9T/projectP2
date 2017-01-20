#include "bullet.h"

Bullet::Bullet(QGraphicsItem *_parent) : QGraphicsPixmapItem(_parent) {
    setFlag(QGraphicsItem::ItemIsMovable);
}

Bullet::~Bullet() {}

void Bullet::automove() {}
