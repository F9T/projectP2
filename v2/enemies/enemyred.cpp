#include "enemyred.h"

EnemyRed::EnemyRed(QGraphicsItem *parent) : Enemy(parent) {
    this->init();
}

EnemyRed::~EnemyRed() {}

void EnemyRed::init() {
    setPixmap(QPixmap(":/images/enemyRed.png"));
    setLife(3);
}
