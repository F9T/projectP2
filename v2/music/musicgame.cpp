#include "musicgame.h"

MusicGame::MusicGame() : Music() {
    this->init();
}

MusicGame::~MusicGame() {
    playlist->clear();
    player->stop();
    delete player;
    delete playlist;
}

void MusicGame::init() {
    playlist=new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/sound/grandioso.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player=new QMediaPlayer(this);
    player->setVolume(100);
    player->setPlaylist(playlist);
}
