#include "enemyyellow.h"

EnemyYellow::EnemyYellow(QGraphicsItem *parent) : Enemy(parent) {
    this->init();
}

EnemyYellow::~EnemyYellow() {}

void EnemyYellow::init() {
    setPixmap(QPixmap(":/images/enemyYellow.png"));
    setLife(2);
}
