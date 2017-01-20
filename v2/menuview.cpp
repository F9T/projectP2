#include "menuview.h"
#include "spaceboard.h"
#include <QMessageBox>
#include <QPalette>
#include <QLabel>
#include <QFontDatabase>
#include <QVBoxLayout>

MenuView::MenuView(QWidget *_parent) : QWidget(_parent) {
    QPalette* pBtnColor = new QPalette();
    pBtnColor->setColor(QPalette::ButtonText, Qt::white);
    QPalette p = palette();
    p.setBrush(QPalette::Window, QBrush(QPixmap(":/images/menuBackground.png")));
    this->setPalette(p);
    this->setWindowTitle("Space Invaders");

    this->setFixedSize(500, 500);

    QFontDatabase::addApplicationFont("qrc:/font/Pixeled.ttf");
    QFont title = QFont("Pixeled", 27);
    QFont btn = QFont("Pixeled", 10);
    QLabel *lblTitre = new QLabel();
    lblTitre->setFont(title);
    lblTitre->setText("<font color='white'>SPACE INVADERS</font>");
    //lblTitre->setPalette(*pBtnColor);
    QPushButton *btnNew = new QPushButton("NOUVELLE PARTIE");
    QPushButton *btnQuit = new QPushButton("QUITTER");
    QPushButton *btnAbout = new QPushButton ("A PROPOS");
    btnNew->setFont(btn);
    btnQuit->setFont(QFont(btn));
    btnAbout->setFont(QFont(btn));
    btnNew->setStyleSheet("background-color: black;");
    btnQuit->setStyleSheet("background-color: black;");
    btnAbout->setStyleSheet("background-color: black;");
    btnNew->setPalette(*pBtnColor);
    btnQuit->setPalette(*pBtnColor);
    btnAbout->setPalette(*pBtnColor);

    btnNew->setFixedHeight(160);
    btnNew->setFixedWidth(210);
    btnQuit->setFixedHeight(160);
    btnQuit->setFixedWidth(210);
    btnAbout->setFixedHeight(160);
    btnAbout->setFixedWidth(210);

    QObject::connect(btnNew, SIGNAL(clicked()), this, SLOT(newGame()));
    QObject::connect(btnQuit, SIGNAL(clicked()), this, SLOT(quitGame()));
    QObject::connect(btnAbout, SIGNAL(clicked()), this, SLOT(aboutGame()));

    musicMenu=new MusicMenu();
    musicMenu->play(0);
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(lblTitre, 0, Qt::AlignCenter);
    vLayout->addWidget(btnNew, 0, Qt::AlignCenter);
    vLayout->addWidget(btnAbout, 0, Qt::AlignCenter);
    vLayout->addWidget(btnQuit, 0, Qt::AlignCenter);

    this->setLayout(vLayout);
}

MenuView::~MenuView() {
    delete musicMenu;
}

void MenuView::quitGame() {
    this->close();
}

void MenuView::newGame() {
    musicMenu->stop();
    spaceboard=new SpaceBoard();
    this->close();
}

void MenuView::aboutGame() {
    QMessageBox::information(this, "À propos", "SPACE INVADERS V1.0\nHE-ARC\n2016-2017\nLovis Thomas, Griesser Gabriel, Gignon Luc\n ");
}
