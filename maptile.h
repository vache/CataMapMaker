#ifndef MAPTILE_H
#define MAPTILE_H

#include "mapfeatures.h"
#include <QColor>

class MapTile
{
public:
    MapTile();

    char GetDisplayChar();

    char expchar;

    QColor GetSymColor();
    QColor GetBgColor();

    ter_t terrain;
    furn_t furniture;

//    QStringList itemgroups;
//    QStringList monstergroups;
//    QStringList items;
    QString monstergroup;
    QString monster;
    QString itemgroup;
    QString item;

    bool operator ==(const MapTile) const;
};

#endif // MAPTILE_H
