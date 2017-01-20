#include "music.h"

Music::Music() {}

Music::~Music() {}

void Music::init() {}

void Music::play(int _index) {
    if(_index>=0 && _index<playlist->mediaCount()) {
        playlist->setCurrentIndex(_index);
        player->play();
    }
}

void Music::stop() {
    player->stop();
}
