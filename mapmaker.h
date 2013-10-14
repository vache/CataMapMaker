#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QMainWindow>
#include <QModelIndex>
#include <QString>
#include <QActionGroup>
#include <QSettings>

#include "map.h"
#include "mapfeatures.h"

namespace Ui {
class MapMaker;
}

enum layer_t { GAME = 0, TERRAIN, FURNITURE };
enum tool_t { SELECT = 0, DRAW, FILLEDBOX, HOLLOWBOX };
enum tab_t { TERRAIN_TAB = 0, FURNITURE_TAB, MONSTER_TAB, ITEM_GROUP_TAB, ITEMS_TAB };

Q_DECLARE_METATYPE(tool_t)

class MapMaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapMaker(QWidget *parent = 0);
    ~MapMaker();

private:
    Ui::MapMaker *ui;

    void FillFeatureList();
    void FillFurnitureList();
    void FillMonsterList();
    void FillItemGroupList();
    void FillItemList();
    void FillToolbar();

    QActionGroup* actiongroup;

    ter_t ter;
    furn_t furn;

    Map* newmap;

    tool_t tool;
    layer_t layer;

    bool boxclick;
    QModelIndex firstcorner;

    QSettings* settings;
    void ReadSettings();
    void WriteSettings();

    void SetTile(int row, int col);

private slots:
    void NewTerrainSelection(int row);
    void NewFurnitureSelection(int row);
    void MapClicked(QModelIndex index);
    void MapClicked(int row, int col);
    void FillMap();
    void BuildNewMap(QString description, int x, int y);
    void Resize();

    void ToggleGrid(bool);
    void ToolChanged();
    void LayerChanged();

    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionQuit_triggered();
    void on_actionNew_triggered();
    void on_actionOptions_triggered();
    void on_actionSettings_triggered();

    void closeEvent(QCloseEvent *);
};

#endif // MAPMAKER_H
