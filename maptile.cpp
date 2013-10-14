#include "maptile.h"

MapTile::MapTile()
{
    terrain = terlist[0];
    furniture = furnlist[0];

    monstergroup = "";
    itemgroup = "";
    item = "";
}

char MapTile::GetDisplayChar()
{
    // display character is topmost char
    // if furniture = nothing->display furniture, if loot->display loot, else->display terrain
    if(furniture.id == f_null)
    {
        return terrain.sym;
    }
    else
    {
        return furniture.sym;
    }
}

QColor MapTile::GetSymColor()
{
    if((monstergroup != "") || (itemgroup != "") || (item != ""))
    {
        return QColor(Qt::black);
    }
    else if(furniture.id == f_null)
    {
        return terrain.color.fg;
    }
    else
    {
        return furniture.color.fg;
    }
}

QColor MapTile::GetBgColor()
{
    if(monster != "")
    {
        return QColor(Qt::yellow);
    }
    else if((item != "") || (itemgroup != ""))
    {
        return QColor(Qt::blue);
    }
    else if(furniture.id == f_null)
    {
        return terrain.color.bg;
    }
    else
    {
        return furniture.color.bg;
    }
}

bool MapTile::operator ==(const MapTile m) const
{
    return (this->furniture.id == m.furniture.id &&
            this->terrain.id == m.terrain.id);
}
