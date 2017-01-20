#include "musicmenu.h"

MusicMenu::MusicMenu() : Music() {
    this->init();
}

MusicMenu::~MusicMenu() {
    playlist->clear();
    player->stop();
    delete player;
    delete playlist;
}

void MusicMenu::init() {
    playlist=new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/sound/majaise.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player=new QMediaPlayer(this);
    player->setVolume(60);
    player->setPlaylist(playlist);
}
