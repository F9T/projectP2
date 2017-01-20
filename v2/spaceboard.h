#ifndef SPACEBOARD_H
#define SPACEBOARD_H

#include <QSet>
#include <QList>
#include <QGraphicsView>
#include <QSoundEffect>
#include "music/musicgame.h"
#include "player.h"
#include "enemies/enemyrow.h"
#include "levelinfos/levelinfo.h"

class SpaceBoard : public QGraphicsView {
    Q_OBJECT
public:
    SpaceBoard(QWidget *parent = 0);
    ~SpaceBoard();

private:
    LevelInfo *currentLevel;
    QGraphicsScene *scene;
    Player *player;
    QList<int> rowsFire;
    QTimer *timer, *timerFireEnemy;
    MusicGame *musicGame;
    QGraphicsTextItem *textLevel;
    QListIterator<LevelInfo*> *levelsIt;
    QList<LevelInfo*> levels;
    QList<EnemyRow*> listRowsEnemy;
    bool direction, enemyReadyToFire;
    QSoundEffect *effectGameover;

    void startCurrentLevel();
    void clearScene();
    void checkRemoveRow();
    void checkRemoveEnemy();
    void nextLevel();
    void gameover();
    void win();
    void resetEnemiesFire();
    int getMaxXEnemy() const;
    int getMinXEnemy() const;
    int getMinYEnemy() const;
    int getMaxYEnemy() const;

private slots:
    void autoEnemyMove();
    void readyToFire();
};

#endif // SPACEBOARD_H
