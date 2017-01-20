#include "xmlreader.h"
#include "levelinfos/levelinfo.h"
#include "enemies/enemyrow.h"
#include <QMessageBox>
#include <QtXml>

XmlReader::XmlReader() {}

QList<LevelInfo*> XmlReader::readLevels(QFile *_file) {

    QList<LevelInfo*> levels;
    if(!_file->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, "Erreur lecture xml", "Impossible d'ouvrir le fichier : "+_file->fileName(), QMessageBox::Ok);
        return levels;
    }

    QDomDocument doc;
    if(!doc.setContent(_file)) {
        _file->close();
        QMessageBox::warning(NULL, "Erreur lecture xml", "Erreur du contenu du document xml", QMessageBox::Ok);
        return levels;
    }
    _file->close();

    if(doc.isDocument()) {
        QDomElement root=doc.documentElement();
        QDomNode node=root.firstChild();
        while(!node.isNull()) {
            QDomElement levelElement=node.toElement();
            if(!levelElement.isNull()) {
                if(levelElement.tagName()=="Level") {
                    QDomNamedNodeMap attrs=levelElement.attributes();
                    //read attributes
                    LevelInfo* level=new LevelInfo();
                    for(int j=0;j<attrs.size();j++) {
                        QString name=attrs.item(j).nodeName();
                        QString value=attrs.item(j).toAttr().value();
                        if(name=="no") level->setNumber(value.toInt());
                        else if(name=="speed") level->setSpeed(value.toInt());
                        else if(name=="xStart") level->setXStart(value.toInt());
                        else if(name=="yStart") level->setYStart(value.toInt());
                        else if(name=="spacingX") level->setXSpacing(value.toInt());
                        else if(name=="spacingY") level->setYSpacing(value.toInt());
                        else if(name=="intervalFire") level->setInterval(value);
                        else if(name=="reloadTime") level->setReloadTime(value.toInt());
                        else if(name=="maxSimultFire")level->setMaxSimultFire(value.toInt());
                    }
                    QDomElement rowsEnemyElement=levelElement.firstChild().toElement();
                    if(!rowsEnemyElement.isNull()) {
                        if(rowsEnemyElement.tagName()=="RowsEnemy") {
                            QDomNode rowNode=rowsEnemyElement.firstChild();
                            while(!rowNode.isNull()) {
                                QString rowElementName=rowNode.nodeName();
                                if(rowElementName=="RowEnemy") {
                                    QDomNamedNodeMap attrs=rowNode.attributes();
                                    //read attributes
                                    int nbPurple=0, nbYellow=0, nbRed=0;
                                    for(int j=0;j<attrs.size();j++) {
                                        QString name=attrs.item(j).nodeName();
                                        QString value=attrs.item(j).toAttr().value();
                                        if(name=="purpleenemy") nbPurple=value.toInt();
                                        else if(name=="yellowenemy") nbYellow=value.toInt();
                                        else if(name=="redenemy") nbRed=value.toInt();
                                    }
                                    level->addEnemyRow(nbPurple, nbYellow, nbRed);
                                }
                                rowNode=rowNode.nextSibling();
                            }
                        }
                    }
                    levels.append(level);
                }
            }
            node=node.nextSibling();
        }
    }
    return levels;
}
