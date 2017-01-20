#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QPushButton>
#include <QWidget>
#include "spaceboard.h"
#include "music/musicmenu.h"

class MenuView : public QWidget {
    Q_OBJECT
public:
    explicit MenuView(QWidget *_parent = 0);
    ~MenuView();

protected:
    QPushButton *btnNew, *btnQuit, *btnAbout;
    MusicMenu *musicMenu;
    SpaceBoard *spaceboard;

public slots:
    void newGame();
    void quitGame();
    void aboutGame();
};

#endif // MENUVIEW_H
