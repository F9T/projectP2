#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>

class Item : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Item(QGraphicsItem *_parent=0);
    virtual ~Item();

    bool isDestroyed();
    void destroy();
    int getLife();
    virtual void setLife(int _life);
    virtual void loseLife(int _loseLife);

    virtual void fire();
    virtual void init();

protected:
    bool isDestroy;
    int life, moveX;
    QSoundEffect *effectFire;
};

#endif // ITEM_H
