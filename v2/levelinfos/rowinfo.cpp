#include "rowinfo.h"

RowInfo::RowInfo(int _nbPurple, int _nbYellow, int _nbRed) {
    this->nbPurple=_nbPurple;
    this->nbYellow=_nbYellow;
    this->nbRed=_nbRed;
}

int RowInfo::getNumberPurple() const  {
    return nbPurple;
}

int RowInfo::getNumberYellow() const {
    return nbYellow;
}

int RowInfo::getNumberRed() const {
    return nbRed;
}
