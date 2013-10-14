#include "map.h"
#include <QDebug>
#include <QRect>

Map::Map(QString description, int x, int y)
{
    lastchar = '0';

    this->options.description = description;
    this->options.height = y;
    this->options.width = x;
    this->Resize();
}

void Map::Resize()
{
    this->height = 24 * options.height;
    this->width = 24 * options.width;

    tiles.resize(height * width);
}

int Map::Index(int row, int col)
{
    return ((row * width) + col);
}

void Map::SetTerrain(ter_t terrain, int row, int col)
{
    int index = Index(row, col);

    tiles[index].terrain = terrain;
}

void Map::SetFurniture(furn_t furniture, int row, int col)
{
    int index = Index(row, col);

    tiles[index].furniture = furniture;
}

void Map::SetMonster(QString monster, int row, int col)
{
    int index = Index(row, col);

    //tiles[index].monstergroups.append(group);
    tiles[index].monster = monster;
    qDebug() << "Tile at" << col << "," << row << "added monster:" << monster;
}

void Map::SetMonsterGroup(QString group, int row, int col)
{
    int index = Index(row, col);

    //tiles[index].monstergroups.append(group);
    tiles[index].monstergroup = group;
    qDebug() << "Tile at" << col << "," << row << "added monstergroup:" << group;
}

void Map::SetItemGroup(QString group, int row, int col)
{
    int index = Index(row, col);

    //tiles[index].itemgroups.append(group);
    tiles[index].itemgroup = group;
    qDebug() << "Tile at" << col << "," << row << "added itemgroup:" << group;
}

void Map::SetItem(QString item, int row, int col)
{
    int index = Index(row, col);

    //tiles[index].items.append(item);
    tiles[index].item = item;
    qDebug() << "Tile at" << col << "," << row << "added item:" << item;
}

QByteArray Map::Export()
{
    QByteArray data;
    data.append(this->options.description);

    // this is what the game view will look like.  gives whoever is reading the output file some idea of what it will look like
    data.append("\n\nGameplay View:\n");
    for(int i = 0; i < height; i++)
    {
        QString line;
        for(int j = 0; j < width; j++)
        {
            line.append(tiles[Index(i, j)].GetDisplayChar());
        }
        qDebug() << line;
        line.append("\n");
        data.append(line);
    }

    // this is what the game will interpret the building from.
    /* loops through every tile.  if a terrain/furniture combo is found that is not in the export character->tile mapping,
     * it assigns a letter to that particular combo.  any time this combo comes up, the code will output that letter
     * later, the code will write binding code so that the game knows to translate that letter to the right terrain/furniture
     *
     * it also searches through each tile for toilets to create the toilet water, and looks for monster/item spawns
     */
    QStringList toilets;
    QString toiletcode = "place_toilet(%1, %2);\n";

    QStringList monsters;
    QString monstercode = "add_spawn(\"%1\", 1, %2, %3);\n";

    QStringList itemgroups;
    QString itemgroupcode = "place_items(\"%1\", %2, %3, %4, %5, %6, %7, 0);\n";

    QStringList items;
    QString itemcode = "spawn_item(%1, %2, \"%3\", 0);\n";
    QString artifactcode = "spawn_artifact(%1, %2, g->new_artifact(), 0);\n";

    data.append("\nBuilding Code:\n");
    data.append("mapf::formatted_set_simple(this, 0, 0,\"");
    for(int i = 0; i < height; i++)
    {
        QString line = "\\\n";
        for(int j = 0; j < width; j++)
        {
            MapTile tile = tiles[Index(i, j)];

            // if charmap contains the tile, return that key, otherwise assign lastchar
            char key = charmap.key(tile, lastchar);
            // if the key is lastchar, it means tile was not found in map, so we insert it and set a new lastchar
            if(key == lastchar)
            {
                charmap.insert(key, tile);
                lastchar++;
                if(lastchar == '\\')
                {
                    lastchar++;
                }
            }

            line.append(key);

            if(tile.furniture.id == f_toilet)
            {
                toilets.append(toiletcode.arg(QString::number(j), QString::number(i)));
            }

            if(tile.item != "")
            {
                if(tile.item == "artifact")
                {
                    items.append(artifactcode.arg(QString::number(j), QString::number(i)));
                }
                else
                {
                    items.append(itemcode.arg(QString::number(j), QString::number(i), tile.item));
                }
            }

            if(tile.monster != "")
            {
                monsters.append(monstercode.arg(tile.monster, QString::number(j), QString::number(i)));
            }
        }
        line.append("\\n");
        qDebug() << line;
        data.append(line);
    }
    data.append("\",\n");

    QString bindterrainchars = "";
    QString bindterrainvalues = "";
    QString bindfurnchars = "";
    QString bindfurnvalues = "";
    for(QMap<char, MapTile>::const_iterator it = charmap.begin(); it != charmap.end(); it++)
    {
        bindterrainchars.append(' ').append(it.key());
        bindterrainvalues.append(", ").append(QString::number(it.value().terrain.id));

        bindfurnchars.append(' ').append(it.key());
        bindfurnvalues.append(", ").append(QString::number(it.value().furniture.id));
    }
    QString terrainbinding = QString("mapf::basic_bind(\"%1\"%2), \n").arg(bindterrainchars, bindterrainvalues);
    QString furnbinding = QString("mapf::basic_bind(\"%1\"%2), true);\n").arg(bindfurnchars, bindfurnvalues);

    data.append(terrainbinding);
    data.append(furnbinding);

    qDebug() << "Terrain Bind Command: " << terrainbinding;
    qDebug() << "Furniture Bind Command: " << furnbinding;

    foreach(QString toiletstring, toilets)
    {
        data.append(toiletstring);
        qDebug() << toiletstring;
    }

    foreach(QString itemstring, items)
    {
        data.append(itemstring);
        qDebug() << itemstring;
    }

    foreach(QString monsterstring, monsters)
    {
        data.append(monsterstring);
        qDebug() << monsterstring;
    }

    if(options.monstergroup != "Nothing")
    {
        QString monstergroupcode = QString("place_spawns(g, \"%1\", %2, %3, %4, %5, %6, %7);\n").arg(
                    options.monstergroup, QString::number(options.monsterchance),
                    "0", "0", QString::number((24 * options.height) - 1), QString::number((24 * options.width) - 1),
                    QString::number(options.monsterdensity));

        data.append(monstergroupcode);
        qDebug() << monstergroupcode;
    }

    if(options.itemgroup != "Nothing")
    {
        QString itemgroupoutput = itemgroupcode.arg(options.itemgroup, QString::number(options.itemchance),
                    "0", "0", QString::number((24 * options.height) - 1), QString::number((24 * options.width) - 1),
                    options.itemsongrass ? "true" : "false");

        data.append(itemgroupoutput);
        qDebug() << itemgroupoutput;
    }
    /*
     * To Add Toilet Water:
     * void place_toilet(const int x, const int y, const int charges = 6 * 4); // 6 liters at 250 ml per charge
     *
     * Monster Group Spawning:
     * place_spawns(g, "GROUP_ZOMBIE", 2, 0, 0, 23, 23, density);
     * void place_spawns(game *g, std::string group, const int chance,
                   const int x1, const int y1, const int x2, const int y2, const float density);
     *
     * Some notes on this: density is a parameter passed into the map generation function and is defined per
     * individual oter_t building struct.  Using "density" itself as the paremeter is fine for now.
     * The oter_t density defintion will have to be created as part of complete generation code however
     * Chance is the chance monsters will spawn, using the formula spawn_chance = one_in(chance / OPTION[Spawn_rate])
     * Standard value for "chance" seems to be 2.
     *
     * Single Monster Spawning:
     * add_spawn(mon_blank, rng(1,3), 0, 5);
     * void add_spawn(mon_id type, const int count, const int x, const int y, bool friendly = false,
                const int faction_id = -1, const int mission_id = -1,
                std::string name = "NONE");
     *
     * Item Group Spawning:
     * place_items("fridgesnacks", 65,  3, 10,  3, 15, false, 0);
     * int place_items(items_location loc, const int chance, const int x1, const int y1,
                  const int x2, const int y2, bool ongrass, const int turn);
     *
     * Single Item Spawning:
     * spawn_item(0, 3, "small_relic", 0);
     * void spawn_item(const int x, const int y, std::string itype_id, int birthday, int quantity = 0, int charges = 0, int damlevel = 0);
     *
     * Artifact Spawning:
     * spawn_artifact(rng(SEEX, SEEX + 1), rng(2, 3), g->new_artifact(), 0);
     * void spawn_artifact(int x, int y, itemtype, int birthday);
     */

    // this is to test the item group box making
    QStringList allthegroups;
    foreach(MapTile tile, tiles)
    {
        if(!allthegroups.contains(tile.itemgroup) && (tile.itemgroup != ""))
        {
            allthegroups.append(tile.itemgroup);
        }
    }

    QVector<bool> itemgroupvalid(height * width, true);
    QMap<QString, QRect> itemgroupmap;

    foreach(QString currentgroup, allthegroups)
    {
        qDebug() << "Looking for instances of" << currentgroup;
        itemgroupvalid.fill(true);

        // creates array of same size with true for indices that have the item group, false for ones that dont
        for(int i = 0; i < this->height; i++)
        {
            for(int j = 0; j < this->width; j++)
            {
                int index = Index(i, j);
                MapTile tile = tiles[index];
                if(tile.itemgroup != currentgroup)
                {
                    itemgroupvalid[index] = false;
                }

            }
        }

        // while there are still valid tiles...
        while(itemgroupvalid.contains(true))
        {
            /*
            qDebug() << "Map still contains instances of" << currentgroup;
            for(int i = 0; i < this->height; i++)
            {
                QString out = "";
                for(int j = 0; j < this->width; j++)
                {
                    int index = Index(i, j);
                    bool valid = itemgroupvalid[index];
                    if(valid)
                    {
                        out.append("1");
                    }
                    else
                    {
                        out.append("0");
                    }
                }
                qDebug() << out;
            }
            */

            QRect currentrect;
            // finds the index of the first valid tile;
            int index = itemgroupvalid.indexOf(true);
            // col = x = index % 24, row = y = index / 24
            int starty = (index - (index % 24)) / 24;
            int startx = index % 24;
            QPoint startpoint;
            startpoint.setX(startx);
            startpoint.setY(starty);
            currentrect.setTopLeft(startpoint);

            //qDebug() << QString("Top Left Corner @ (%1, %2)").arg(startx).arg(starty);

            // first row... find end x
            int x = startx;
            while((x < width) && itemgroupvalid[Index(starty, x+1)])
            {
                x++;
            }
            currentrect.setRight(x);

            //qDebug() << "Right Side @" << x;

            // first column find end y
            int y = starty;
            bool keepgoing = true;
            while((y < height) && keepgoing)
            {
                for(int i = startx; i <= x; i++)
                {
                    keepgoing = itemgroupvalid[Index(y+1, i)];
                    if(!keepgoing)
                    {
                        break;
                    }
                }
                if(!keepgoing)
                {
                    break;
                }
                y++;
            }
            currentrect.setBottom(y);

            //qDebug() << "Bottom Side @" << y;
            //qDebug() << QString("Final Rect: (%1, %2) to (%3, %4)").arg(startx).arg(starty).arg(x).arg(y);
            //qDebug() << currentrect.top() << "," << currentrect.bottom();
            //qDebug() << currentrect.left() << "," << currentrect.right();

            for(int row = currentrect.top(); row <= currentrect.bottom(); row++)
            {
                for(int col = currentrect.left(); col <= currentrect.right(); col++)
                {
                    itemgroupvalid[Index(row, col)] = false;
                }
            }

            itemgroupmap.insertMulti(currentgroup, currentrect);
        }
    }

    qDebug() << "Found Rectangles At:";
    foreach(QString key, itemgroupmap.uniqueKeys())
    {
        qDebug() << key;
        foreach(QRect rect, itemgroupmap.values(key))
        {
            qDebug() << QString("Start Point: %1, %2").arg(rect.topLeft().x()).arg(rect.topLeft().y());
            qDebug() << QString("End Point: %1, %2").arg(rect.bottomRight().x()).arg(rect.bottomRight().y());
            data.append(itemgroupcode.arg(key).arg(75).arg(rect.left()).arg(rect.top()).arg(rect.right()).arg(rect.bottom()).arg("true"));
            qDebug() << itemgroupcode.arg(key).arg(75).arg(rect.left()).arg(rect.top()).arg(rect.right()).arg(rect.bottom()).arg("true");
        }
    }

    lastchar = '0';
    return data;
}

void Map::debug()
{
    for(int i = 0; i < height; i++)
    {
        QString line = "";
        for(int j = 0; j < width; j++)
        {
            line.append(tiles[Index(i, j)].GetDisplayChar());
        }
        qDebug() << line;
    }
    qDebug() << "--------------------------";
}
