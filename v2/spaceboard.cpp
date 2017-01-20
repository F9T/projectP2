#include "spaceboard.h"
#include "xml/xmlreader.h"
#include <QTimer>
#include <QTime>
#include <typeinfo>
#include <QMessageBox>
#include <stdlib.h>
#include <cstdlib>
#include <QDebug>
#include <QApplication>

SpaceBoard::SpaceBoard(QWidget *_parent) : QGraphicsView(_parent) {
    musicGame=new MusicGame();

    effectGameover=new QSoundEffect(this);
    effectGameover->setSource(QUrl("qrc:/sound/gameover.wav"));
    effectGameover->setVolume(0.4);

    scene = new QGraphicsScene(this);
    setScene(scene);
    this->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("SPACE INVADER V2");

    setBackgroundBrush(QImage(":/images/space_new.png"));
    setCacheMode(QGraphicsView::CacheBackground);

    //Graphics quality
    setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

    qsrand(QTime::currentTime().msec());

    timer=new QTimer(this);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoEnemyMove()));

    timerFireEnemy=new QTimer(this);
    connect(timerFireEnemy, SIGNAL(timeout()), this, SLOT(readyToFire()));

    //Read Levels
    XmlReader *reader=new XmlReader();
    QList<LevelInfo*> levels=reader->readLevels(new QFile("levels.xml"));
    if(!levels.empty()){
        levelsIt=new QListIterator<LevelInfo*>(levels);

        delete reader;
        //Select first level
        this->nextLevel();
        this->startCurrentLevel();
        show();
    } else delete this;
}

SpaceBoard::~SpaceBoard() {
    timerFireEnemy->stop();
    timer->stop();
    effectGameover->stop();
    delete effectGameover;
    delete timer;
    delete timerFireEnemy;
    delete musicGame;
    if(currentLevel!=NULL) delete currentLevel;
    if(player!=NULL) delete player;
    clearScene();
}

void SpaceBoard::startCurrentLevel() {
    musicGame->play(0);
    if(timer->isActive()) timer->stop();
    if(timerFireEnemy->isActive()) timerFireEnemy->stop();
    clearScene();
    resetEnemiesFire();
    direction=true;
    if(currentLevel!=NULL) {
        //Initialisation text current level
        textLevel=new QGraphicsTextItem(QString::number(currentLevel->getNumber()));
        textLevel->setPos(775,3);
        textLevel->setFont(QFont("Consolas", 14));
        textLevel->setDefaultTextColor(Qt::red);
        scene->addItem(textLevel);
        player=new Player();
        scene->addItem(player);
        player->init();
        player->setReloadTime(currentLevel->getReloadTime());
        int min=currentLevel->getMinInterval();
        int max=currentLevel->getMaxInterval();
        //Random interval of timer fire enemy
        int interval=(rand()%(max-min+1))+min;
        timerFireEnemy->setInterval(interval);
        listRowsEnemy=currentLevel->generateLevel();

        //Add enemy to scene
        foreach(EnemyRow *row , listRowsEnemy) {
            foreach(Enemy* enemy , row->getEnemies()) {
                scene->addItem(enemy);
            }
        }
    }
    timer->start();
    timerFireEnemy->start();
}


void SpaceBoard::nextLevel() {
    if(timer->isActive()) timer->stop();
    if(levelsIt->hasNext())
        currentLevel=levelsIt->next();
}

void SpaceBoard::clearScene() {
    scene->clear();
    listRowsEnemy.clear();
}

/**
 * @brief SpaceBoard::getMaxXEnemy get the positon x of the rightmost enemy
 * @return max position
 */
int SpaceBoard::getMaxXEnemy() const {
    int max=-1;
    foreach(EnemyRow* row, listRowsEnemy) {
        max=qMax(max, row->getMaxXEnemy());
    }
    return max;
}

/**
 * @brief SpaceBoard::getMinXEnemy get the positon x of the least right enemy
 * @return min position
 */
int SpaceBoard::getMinXEnemy() const {
    int min=-1;
    if(!listRowsEnemy.isEmpty()) min=listRowsEnemy.at(0)->getMinXEnemy();
    foreach(EnemyRow* row, listRowsEnemy) {
        min=qMin(min, row->getMinXEnemy());
    }
    return min;
}

/**
 * @brief SpaceBoard::getMinYEnemy get the positon y of the highest enemy
 * @return min position
 */
int SpaceBoard::getMinYEnemy() const {
    int min=-1;
    if(!listRowsEnemy.isEmpty()) min=listRowsEnemy.at(0)->getCurrentYLine();
    foreach(EnemyRow* row, listRowsEnemy) {
        min=qMin(min, row->getCurrentYLine());
    }
    return min;
}

/**
 * @brief SpaceBoard::getMaxYEnemy get the positon y of the lowest enemy
 * @return max position
 */
int SpaceBoard::getMaxYEnemy() const {
    int max=-1;
    if(!listRowsEnemy.isEmpty()) {
        max=listRowsEnemy.at(listRowsEnemy.size()-1)->getCurrentYLine();
    }
    return max;
}

/**
 * @brief SpaceBoard::checkRemoveRow remove instance of EnemyRow if empty
 */
void SpaceBoard::checkRemoveRow() {
    for(int i=0;i<listRowsEnemy.size();) {
        EnemyRow *row=listRowsEnemy.at(i);
        if(row->isEmpty()) {
            listRowsEnemy.removeAt(i);
            delete row;
        } else i++;
    }
}

/**
 * @brief SpaceBoard::checkRemoveEnemy remove instance of Enemy is destroyed
 */
void SpaceBoard::checkRemoveEnemy() {
    foreach(EnemyRow* row, listRowsEnemy) {
        row->destroyEnemy();
        getMaxXEnemy();
    }
}

/**
 * @brief SpaceBoard::gameover end of party
 */
void SpaceBoard::gameover() {
    player->stop();
    timer->stop();
    timerFireEnemy->stop();
    musicGame->stop();
    effectGameover->play();
    int rep = QMessageBox::question(this, "Space Invaders", "GAME OVER !\n Recommencer ?", QMessageBox::Yes | QMessageBox::No);
    if (rep == QMessageBox::Yes) {
        //Restart of firt level
        while(levelsIt->hasPrevious()) {
            currentLevel=levelsIt->previous();
        }
        this->startCurrentLevel();
    } else if(rep == QMessageBox::No) {
        close();
        delete this;
    }
}

void SpaceBoard::win() {
    player->stop();
    timer->stop();
    timerFireEnemy->stop();
    if(levelsIt->hasNext()) {
        QMessageBox::information(this, "Space Invaders", "Niveau reussi", QMessageBox::Ok);
        this->nextLevel();
        this->startCurrentLevel();
    } else QMessageBox::information(this, "Space Invaders", "Félicitations vous avez terminé le jeu!", QMessageBox::Ok);
}

void SpaceBoard::readyToFire() {

    int min=1;
    int max=currentLevel->getMaxSimultFire();
    int nbFire=(rand()%(max-min+1))+min;

    min=0;
    max=listRowsEnemy.size()-1;
    for(int i=0;i<nbFire;i++) {
        rowsFire.append((rand()%(max-min+1))+min);
    }
    enemyReadyToFire=true;
    //Random interval of timer fire enemy
    min=currentLevel->getMinInterval();
    max=currentLevel->getMaxInterval();
    int interval=(rand()%(max-min+1))+min;
    timerFireEnemy->setInterval(interval);
}

void SpaceBoard::resetEnemiesFire() {
    rowsFire.clear();
    enemyReadyToFire=false;
    foreach(EnemyRow *row, listRowsEnemy) {
        row->resetEnemiesFire();
    }
}

void SpaceBoard::autoEnemyMove() {
    //If the player is destroyed -> gameover
    if(player->isDestroyed()) {
        gameover();
        return;
    }
    checkRemoveEnemy();
    checkRemoveRow();

    //Check win, if there are no enemy
    if(listRowsEnemy.empty()) {
        win();
        return;
    }

    //Check row if enemies arrive limit left or right window
    bool updateRow=false;
    if(direction) {
        //get enemy rightmost of window
        int maxX=getMaxXEnemy();
        if(maxX!=-1 && maxX+32 > scene->width()) {
            direction=false;
            updateRow=true;
        }
    } else {
        //get enemy leftmost of window
        int minX=getMinXEnemy();
        if(minX!=-1 && minX-32 < 0) {
            direction=true;
            updateRow=true;
        }
    }

    //Check if enemy arrive too low -> gameover
    if(getMaxYEnemy()>(scene->height()-65)) {
        gameover();
        return;
    }

    //Move all enemies
    foreach(EnemyRow* row, listRowsEnemy){
        row->automove(direction, updateRow);
    }

    //Enemies fire
    if(enemyReadyToFire && !rowsFire.empty()){
        foreach(int row , rowsFire) {
            if(row<listRowsEnemy.size()) listRowsEnemy.at(row)->enemyReadyToFire();
        }
        resetEnemiesFire();
    }

}
