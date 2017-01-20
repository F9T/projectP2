#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include <QSet>
#include <QKeyEvent>
#include <QTimer>

class Player : public Item {
    Q_OBJECT
    Q_ENUMS(Actions)
public:
    Player(QGraphicsItem *_parent=0, int _reloadTime=750);
    ~Player();

    void stop();
    void setReloadTime(int _reloadTime);
    void setLife(int _life);
    void init();
    void loseLife(int _loseLife);

protected:
    void keyPressEvent(QKeyEvent *_evt);
    void keyReleaseEvent(QKeyEvent *_evt);

private:
   enum Action { LEFT, RIGHT, FIRE };
   QSet<int> keysPressed;
   bool isReload;
   QTimer *reloadTimer, *repeatKeyTimer;
   QList<QGraphicsItem*> listHearth;
   QSoundEffect *effectTouch;

   void action(Action _act);
   void left();
   void right();
   void fire();

private slots:
   void reload();
   void repeatKey();
};

#endif // PLAYER_H
