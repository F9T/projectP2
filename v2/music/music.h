#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Music : public QObject {
public:
    Music();
    virtual ~Music();
    virtual void init();

    void play(int _index);
    void stop();

protected:
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
};

#endif // MUSIC_H
