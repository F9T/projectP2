#include "enemypurple.h"

EnemyPurple::EnemyPurple(QGraphicsItem *parent) : Enemy(parent) {
    this->init();
}

EnemyPurple::~EnemyPurple() {}

void EnemyPurple::init() {
    setPixmap(QPixmap(":/images/enemyPurple.png"));
    setLife(1);
}
