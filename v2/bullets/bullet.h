#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Bullet(QGraphicsItem *_parent=0);
    virtual ~Bullet();

protected:
    QTimer *timer;

protected slots:
    virtual void automove();
};

#endif // BULLET_H
