#ifndef ROWINFO_H
#define ROWINFO_H

class RowInfo {
public:
    RowInfo(int _nbPurple, int _nbYellow, int _nbRed);

    int getNumberPurple() const;
    int getNumberYellow() const ;
    int getNumberRed() const;

private:
    int nbPurple, nbYellow, nbRed;
};

#endif // ROWINFO_H
