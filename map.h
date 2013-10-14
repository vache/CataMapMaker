#ifndef MAP_H
#define MAP_H

#include "mapfeatures.h"
#include "maptile.h"
#include "mapoptions.h"

#include <QString>
#include <QVector>
#include <QPair>
#include <QByteArray>
#include <QMap>

class Map
{
public:
    Map(QString description, int x, int y);

    int height;
    int width;

    QVector<MapTile> tiles;

    QMap<char, MapTile > charmap;

    MapOptions options;

    void Resize();
    int Index(int row, int col);

    void SetTerrain(ter_t terrain, int row, int col);
    void SetFurniture(furn_t furniture, int row, int col);
    void SetMonster(QString monster, int row, int col);
    void SetMonsterGroup(QString group, int row, int col);
    void SetItemGroup(QString group, int row, int col);
    void SetItem(QString item, int row, int col);

    QByteArray Export();

    void debug();

private:
    char lastchar;
};

#endif // MAP_H
