#ifndef MAPOPTIONS_H
#define MAPOPTIONS_H

#include <QString>

class MapOptions
{
public:
    MapOptions();

    QString description;
    int width;
    int height;

    QString monstergroup;
    int monsterchance;
    double monsterdensity;

    QString itemgroup;
    int itemchance;
    bool itemsongrass;
};

#endif // MAPOPTIONS_H
