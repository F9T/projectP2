#include "player.h"
#include "bullets/bulletplayer.h"
#include <QGraphicsScene>

Player::Player(QGraphicsItem *_parent, int _reloadTime) : Item(_parent) {
    effectFire=new QSoundEffect(this);
    effectFire->setSource(QUrl("qrc:/sound/shoot.wav"));
    effectFire->setVolume(0.1);

    effectTouch=new QSoundEffect(this);
    effectTouch->setSource(QUrl("qrc:/sound/boum.wav"));
    effectTouch->setVolume(0.1);

    this->reloadTimer=new QTimer(this);
    this->setReloadTime(_reloadTime);
    connect(reloadTimer, SIGNAL(timeout()), this, SLOT(reload()));
}

Player::~Player() {
    reloadTimer->stop();
    repeatKeyTimer->stop();
    delete reloadTimer;
    delete repeatKeyTimer;
    effectFire->stop();
    delete effectFire;
    effectTouch->stop();
    delete effectTouch;
}

void Player::init() {
    setPixmap(QPixmap(":/images/player.png"));
    setLife(3);
    this->isDestroy=false;
    this->moveX=5;
    this->isReload=false;
    this->repeatKeyTimer=new QTimer(this);
    this->repeatKeyTimer->setInterval(0);
    setPos(400, 565);
    setFlag(QGraphicsItem::ItemIsFocusable);
    connect(repeatKeyTimer, SIGNAL(timeout()), this, SLOT(repeatKey()));

    setFocus();
}

void Player::setReloadTime(int _reloadTime) {
    this->reloadTimer->setInterval(_reloadTime);
}

void Player::stop() {
    reloadTimer->stop();
    repeatKeyTimer->stop();
}

void Player::keyPressEvent(QKeyEvent *_evt) {
    if(isDestroy) {
        repeatKeyTimer->stop();
        return;
    }
    keysPressed+=_evt->key();
    if(keysPressed.contains(Qt::Key_Right)) {
        action(Player::RIGHT);
    }
    if(keysPressed.contains(Qt::Key_Left)) {
        action(Player::LEFT);
    }
    if(keysPressed.contains(Qt::Key_Space)) {
        action(Player::FIRE);
        //Key enfonced
        if(!keysPressed.empty()) repeatKeyTimer->start();
    }
}

void Player::keyReleaseEvent(QKeyEvent *_evt) {
    if(isDestroy) {
        repeatKeyTimer->stop();
        return;
    }
    keysPressed-=_evt->key();
    if(keysPressed.contains(Qt::Key_Space)) {
        action(Player::FIRE);
    }
    if(keysPressed.empty()) repeatKeyTimer->stop();
}

void Player::repeatKey() {
    if(keysPressed.contains(Qt::Key_Space)) {
        action(Player::FIRE);
    }
}

void Player::action(Action _act) {
    switch(_act) {
        case Player::RIGHT:
            this->right();
        break;
        case Player::LEFT:
            this->left();
        break;
        case Player::FIRE:
            this->fire();
        break;
    }
}

void Player::left() {
    int newX=x()-moveX;
    //Limit  0 of windows
    if(newX>0)
        setPos(newX, y());
}

void Player::right() {
    int newX=x()+moveX;
    //Limit width of windows
    if(newX<(scene()->width()-this->boundingRect().width()))
        setPos(newX, y());
}

void Player::reload() {
    this->isReload=false;
    this->reloadTimer->stop();
}

void Player::fire() {
    if(!isReload) {
        effectFire->play();
        BulletPlayer *bullet = new BulletPlayer();
        bullet->setPos((x()+(this->boundingRect().width()/2))-(bullet->boundingRect().width()/2), y()-bullet->boundingRect().height());
        scene()->addItem(bullet);
        isReload=true;
        reloadTimer->start();
    }
}

void Player::setLife(int _life) {
    this->life=_life;
    //Initialisation of hearts
    for(int i=0;i<this->life;i++) {
        QGraphicsPixmapItem *heart=new QGraphicsPixmapItem();
        heart->setPixmap(QPixmap(":/images/heart.png"));
        listHearth.append(heart);
    }

    for(int y=0;y<this->life;y++) {
        listHearth[y]->setPos(5+(y*30), 3);
        scene()->addItem(listHearth[y]);
    }
}

void Player::loseLife(int _loseLife) {
    //Remove heart
    effectTouch->play();
    for(int i = life-1 ; i >= 0;i--){
        scene()->removeItem(listHearth[i]);
        listHearth.removeAt(i);

    }
    int newLife=life-_loseLife;
    this->setLife(newLife);
}
