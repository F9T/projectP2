#ifndef XMLREADER_H
#define XMLREADER_H

#include <QFile>
#include "levelinfos/levelinfo.h"

class XmlReader {
public:
    XmlReader();
    QList<LevelInfo*> readLevels(QFile *_file);
};

#endif // XMLREADER_H
