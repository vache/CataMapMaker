#include "mapmaker.h"
#include "ui_mapmaker.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "newmapdialog.h"
#include "mapoptionsdialog.h"
#include "optionsdialog.h"
#include "mapfeatures.h"

MapMaker::MapMaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapMaker)
{
    ui->setupUi(this);
    actiongroup = new QActionGroup(ui->mainToolBar);

    settings = new QSettings("Cataclysm Building Designer", "Cataclysm Building Designer");
    ReadSettings();

    FillFeatureList();
    FillFurnitureList();
    FillMonsterList();
    FillItemGroupList();
    FillItemList();
    FillToolbar();

    connect(ui->GridBox, SIGNAL(clicked(bool)), this, SLOT(ToggleGrid(bool)));
    connect(ui->GameplayViewRadio, SIGNAL(clicked()), this, SLOT(LayerChanged()));
    connect(ui->TerrainViewRadio, SIGNAL(clicked()), this, SLOT(LayerChanged()));
    connect(ui->FurnitureViewRadio, SIGNAL(clicked()), this, SLOT(LayerChanged()));
    connect(ui->TerrainList, SIGNAL(currentRowChanged(int)), this, SLOT(NewTerrainSelection(int)));
    connect(ui->FurnList, SIGNAL(currentRowChanged(int)), this, SLOT(NewFurnitureSelection(int)));
    connect(ui->GameViewWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(MapClicked(QModelIndex)));
    connect(ui->GameViewWidget, SIGNAL(cellEntered(int,int)), this, SLOT(MapClicked(int, int)));
    connect(ui->FillButton, SIGNAL(clicked()), this, SLOT(FillMap()));

    ui->GameViewWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->GameViewWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->GameViewWidget->setStyleSheet("gridline-color: gray;");

    ui->TerrainList->setCurrentRow(0);
    ter = terlist[0];

    ui->FurnList->setCurrentRow(0);
    furn = furnlist[0];

    tool = DRAW;
    layer = GAME;

    boxclick = false;

    newmap = NULL;
    BuildNewMap(QString("New"), 1, 1);
}

MapMaker::~MapMaker()
{
    delete ui;
}

void MapMaker::FillFeatureList()
{
    for(int i = 0; i < num_terrain_types; i++)
    {
        ui->TerrainList->addItem(QString(terlist[i].sym) + " : " + terlist[i].name);
    }
}

void MapMaker::FillFurnitureList()
{
    for(int i = 0; i < num_furniture_types; i++)
    {
        ui->FurnList->addItem(QString(furnlist[i].sym) + " : " + furnlist[i].name);
    }
}

void MapMaker::FillMonsterList()
{
    qDebug() << "Filling Monster List";
    QString path = settings->value("cata-path").toString().append("/data/raw/monsters.json");
    QFile monsterjson(path);
    monsterjson.open(QIODevice::ReadOnly);

    QByteArray monsterdata = monsterjson.readAll();

    QJsonDocument jsondata = QJsonDocument::fromJson(monsterdata);

    QJsonArray jsonarray = jsondata.array();

    ui->MonsterList->addItem("Nothing");
    for(int i = 0; i < jsonarray.size(); i++)
    {
        if(jsonarray[i].isObject())
        {
            if(jsonarray[i].toObject()["type"].toString() == "MONSTER")
            {
                ui->MonsterList->addItem(jsonarray[i].toObject()["id"].toString());
            }
        }
    }
    monsterjson.close();

    ui->MonsterList->setCurrentRow(0);
}

void MapMaker::FillItemGroupList()
{
    qDebug() << "Filling Item Group List";
    QString path = settings->value("cata-path").toString().append("/data/raw/item_groups.json");
    QFile itemjson(path);
    itemjson.open(QIODevice::ReadOnly);

    QByteArray itemdata = itemjson.readAll();

    QJsonDocument jsondata = QJsonDocument::fromJson(itemdata);

    QJsonArray jsonarray = jsondata.array();

    ui->ItemGroupList->addItem("Nothing");
    for(int i = 0; i < jsonarray.size(); i++)
    {
        if(jsonarray[i].isObject())
        {
            ui->ItemGroupList->addItem(jsonarray[i].toObject()["id"].toString());
        }
    }
    itemjson.close();

    ui->ItemGroupList->setCurrentRow(0);
}

void MapMaker::FillItemList()
{
    qDebug() << "Filling Item List";

    ui->ItemList->setHeaderLabel("Item");

    QTreeWidgetItem* nothing = new QTreeWidgetItem(QStringList("Nothing"), QTreeWidgetItem::UserType);
    nothing->setData(0, QTreeWidgetItem::UserType, QString(""));
    ui->ItemList->addTopLevelItem(nothing);

    QTreeWidgetItem* artifact = new QTreeWidgetItem(QStringList("Random Artifact"), QTreeWidgetItem::UserType);
    artifact->setData(0, QTreeWidgetItem::UserType, QString("artifact"));
    ui->ItemList->addTopLevelItem(artifact);

    QString path = settings->value("cata-path").toString().append("/data/raw/items/");

    QDir itemdir(path, "*.json");
    foreach(QString filename, itemdir.entryList())
    {
        QFile itemfile(itemdir.filePath(filename));
        itemfile.open(QIODevice::ReadOnly);
        QString itemtype = filename.split('.')[0];

        QByteArray itemdata = itemfile.readAll();

        QJsonDocument jsondata = QJsonDocument::fromJson(itemdata);

        QJsonArray jsonarray = jsondata.array();

        QTreeWidgetItem* topItem = new QTreeWidgetItem(QStringList(itemtype));
        QTreeWidgetItem* item;

        ui->ItemList->addTopLevelItem(topItem);

        for(int i = 0; i < jsonarray.size(); i++)
        {
            if(jsonarray[i].isObject())
            {
                item = new QTreeWidgetItem(topItem, QTreeWidgetItem::UserType);//, QStringList(jsonarray[i].toObject()["name"].toString()));
                item->setText(0, jsonarray[i].toObject()["name"].toString());
                item->setData(0, QTreeWidgetItem::UserType, jsonarray[i].toObject()["id"].toString());
                ui->ItemList->addTopLevelItem(item);
                //ui->ItemList->addItem(jsonarray[i].toObject()["name"].toString());
            }
        }
        itemfile.close();
    }

    ui->ItemList->setCurrentItem(nothing);
}

void MapMaker::FillToolbar()
{
    ui->mainToolBar->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->mainToolBar->addAction(ui->actionNew);
    ui->mainToolBar->addAction(ui->actionOpen);
    ui->mainToolBar->addAction(ui->actionSave);

    ui->mainToolBar->addSeparator();

    QAction* select = new QAction("Select", actiongroup);
    select->setData(SELECT);
    select->setCheckable(true);
    connect(select, SIGNAL(triggered()), this, SLOT(ToolChanged()));

    QAction* draw = new QAction("Draw", actiongroup);
    draw->setData(DRAW);
    draw->setCheckable(true);
    draw->setChecked(true);
    connect(draw, SIGNAL(triggered()), this, SLOT(ToolChanged()));

    QAction* filledbox = new QAction("Filled Box", actiongroup);
    filledbox->setData(FILLEDBOX);
    filledbox->setCheckable(true);
    connect(filledbox, SIGNAL(triggered()), this, SLOT(ToolChanged()));

    QAction* hollowbox = new QAction("Hollow Box", actiongroup);
    hollowbox->setData(HOLLOWBOX);
    hollowbox->setCheckable(true);
    connect(hollowbox, SIGNAL(triggered()), this, SLOT(ToolChanged()));

    ui->mainToolBar->addActions(actiongroup->actions());
}

void MapMaker::ReadSettings()
{
    resize(settings->value("size", QSize(960, 640)).toSize());
    move(settings->value("pos", QPoint(100,100)).toPoint());

    if(settings->value("cata-path").toString() == "")
    {
        OptionsDialog dlg;
        if(!dlg.exec() || dlg.GetPath() == "")
        {
            QMessageBox::warning(this, "Must Select Cataclysm Directory",
                                 "In order to have access to the cataclysm json files, a path to a cataclysm install directory must be set in the options.");
        }
        else
        {
            settings->setValue("cata-path", dlg.GetPath());
        }
    }
}

void MapMaker::WriteSettings()
{
    settings->setValue("size", size());
    settings->setValue("pos", pos());
}

void MapMaker::NewTerrainSelection(int row)
{
    ter = terlist[row];
}

void MapMaker::NewFurnitureSelection(int row)
{
    furn = furnlist[row];
}

// actually used for a "click" action
void MapMaker::MapClicked(QModelIndex index)
{
    switch(tool)
    {
    case SELECT:
    {
        QString message = "(%1, %2) Terrain: %3; Furniture: %4; Monster Group: %5; Item Group: %6; Indiv. Item: %7";
        MapTile tile = newmap->tiles[newmap->Index(index.row(), index.column())];
        ui->statusBar->showMessage(message.arg(QString::number(index.column()), QString::number(index.row()), tile.terrain.name, tile.furniture.name, tile.monstergroup, tile.itemgroup, tile.item));
        break;
    }
    case DRAW:
    {
        SetTile(index.row(), index.column());
        break;
    }
    case FILLEDBOX:
    {
        if (!boxclick)
        {
            firstcorner = index;
            boxclick = true;
        }
        else
        {
            QModelIndex secondcorner = index;
            int startcol, startrow, endcol, endrow;

            if(firstcorner.column() > secondcorner.column())
            {
                startcol = secondcorner.column();
                endcol = firstcorner.column();
            }
            else
            {
                startcol = firstcorner.column();
                endcol = secondcorner.column();
            }

            if(firstcorner.row() > secondcorner.row())
            {
                startrow = secondcorner.row();
                endrow = firstcorner.row();
            }
            else
            {
                startrow = firstcorner.row();
                endrow = secondcorner.row();
            }

            for(int i = startcol; i <= endcol; i++)
            {
                for(int j = startrow; j <= endrow; j++)
                {
                    SetTile(j, i);
                }
            }
            boxclick = false;
        }
        break;
    }
    case HOLLOWBOX:
    {
        if (!boxclick)
        {
            firstcorner = index;
            boxclick = true;
        }
        else
        {
            QModelIndex secondcorner = index;
            int startcol, startrow, endcol, endrow;

            if(firstcorner.column() > secondcorner.column())
            {
                startcol = secondcorner.column();
                endcol = firstcorner.column();
            }
            else
            {
                startcol = firstcorner.column();
                endcol = secondcorner.column();
            }

            if(firstcorner.row() > secondcorner.row())
            {
                startrow = secondcorner.row();
                endrow = firstcorner.row();
            }
            else
            {
                startrow = firstcorner.row();
                endrow = secondcorner.row();
            }

            for(int i = startcol; i <= endcol; i++)
            {
                SetTile(firstcorner.row(), i);
                SetTile(secondcorner.row(), i);
            }
            for(int j = startrow; j <= endrow; j++)
            {
                SetTile(j, firstcorner.column());
                SetTile(j, secondcorner.column());
            }
            boxclick = false;
        }
        break;
    }
    default:
        break;
    }
}

// used for "cell entered", the "painting" action
void MapMaker::MapClicked(int row, int col)
{
    if(tool == DRAW)
    {
        if(QApplication::mouseButtons() & Qt::LeftButton)
        {
            SetTile(row, col);
        }
    }
}

void MapMaker::FillMap()
{
    for(int i = 0; i < newmap->height; i++)
    {
        for(int j = 0; j < newmap->width; j++)
        {
            SetTile(i, j);
        }
    }
}

void MapMaker::SetTile(int row, int col)
{
    QString message;
    switch(ui->FeatureTabs->currentIndex())
    {
    // Terrain Tab
    case TERRAIN_TAB:
    {
        newmap->SetTerrain(ter, row, col);

        message = "Set terrain at %1, %2 to %3";
        ui->statusBar->showMessage(message.arg(QString::number(col), QString::number(row), QString(ter.sym)));
        break;
    }
    // Furniture Tab
    case FURNITURE_TAB:
    {
        newmap->SetFurniture(furn, row, col);

        message = "Set furniture at %1, %2 to %3";
        ui->statusBar->showMessage(message.arg(QString::number(col), QString::number(row), QString(furn.sym)));
        break;
    }
    case MONSTER_TAB:
    {
        QString monster = ui->MonsterList->selectedItems()[0]->text();
        if(monster == "Nothing")
        {
            monster = "";
        }
        newmap->SetMonster(monster, row, col);

        message = "Set monster at %1, %2 to %3";
        ui->statusBar->showMessage(message.arg(QString::number(col), QString::number(row), monster));
        break;
    }
    case ITEM_GROUP_TAB:
    {
        QString itemgroup = ui->ItemGroupList->selectedItems()[0]->text();
        if(itemgroup == "Nothing")
        {
            itemgroup = "";
        }
        newmap->SetItemGroup(itemgroup, row, col);

        message = "Set item group at %1, %2 to %3";
        ui->statusBar->showMessage(message.arg(QString::number(col), QString::number(row), itemgroup));
        break;
    }
    case ITEMS_TAB:
    {
        if(ui->ItemList->selectedItems()[0]->type() == QTreeWidgetItem::UserType)
        {
            newmap->SetItem(ui->ItemList->selectedItems()[0]->data(0, QTreeWidgetItem::UserType).toString(), row, col);

            message = "Set item at %1, %2 to %3";
            ui->statusBar->showMessage(message.arg(QString::number(col), QString::number(row), QString(furn.sym)));
        }
        break;
    }
    default:
        break;
    }

    MapTile tile = newmap->tiles[newmap->Index(row, col)];
    QString tooltip = "(%1, %2) Terrain: %3; Furniture: %4; Monster Group: %5; Item Group: %6; Indiv. Item: %7";
    ui->GameViewWidget->item(row, col)->setToolTip(tooltip.arg(QString::number(row), QString::number(col), tile.terrain.name, tile.furniture.name, tile.monstergroup, tile.itemgroup, tile.item));

    switch(layer)
    {
    case GAME:
        ui->GameViewWidget->item(row, col)->setText(QString(tile.GetDisplayChar()));
        ui->GameViewWidget->item(row, col)->setBackgroundColor(tile.GetBgColor());
        ui->GameViewWidget->item(row, col)->setTextColor(tile.GetSymColor());
        break;
    case TERRAIN:
        ui->GameViewWidget->item(row, col)->setText(QString(tile.terrain.sym));
        ui->GameViewWidget->item(row, col)->setBackgroundColor(tile.terrain.color.bg);
        ui->GameViewWidget->item(row, col)->setTextColor(tile.terrain.color.fg);
        break;
    case FURNITURE:
        ui->GameViewWidget->item(row, col)->setText(QString(tile.furniture.sym));
        ui->GameViewWidget->item(row, col)->setBackgroundColor(tile.furniture.color.bg);
        ui->GameViewWidget->item(row, col)->setTextColor(tile.furniture.color.fg);
        break;
    default:
        break;
    }
}

void MapMaker::BuildNewMap(QString description, int x, int y)
{
    if(newmap != NULL)
    {
        // prompt to save before deletion
        delete newmap;
    }

    newmap = new Map(description, x, y);

    Resize();
}

void MapMaker::Resize()
{
    ui->GameViewWidget->setColumnCount(newmap->width);
    ui->GameViewWidget->setRowCount(newmap->height);

    QTableWidgetItem* item;
    for(int i = 0; i < newmap->height; i++)
    {
        for(int j = 0; j < newmap->width; j++)
        {
            if(ui->GameViewWidget->item(i, j) == 0)
            {
                item = new QTableWidgetItem(" ");
                ui->GameViewWidget->setItem(i, j, item);
            }
            ui->GameViewWidget->item(i, j)->setBackgroundColor(QColor(Qt::black));
        }
    }
}

void MapMaker::ToggleGrid(bool checked)
{
    ui->GameViewWidget->setShowGrid(checked);
}

void MapMaker::ToolChanged()
{
    tool = static_cast<tool_t>(((QAction*)QObject::sender())->data().toInt());

    boxclick = false;
}

void MapMaker::LayerChanged()
{
    if(QObject::sender()->objectName() == "GameplayViewRadio")
    {
        layer = GAME;
    }
    else if(QObject::sender()->objectName() == "TerrainViewRadio")
    {
        layer = TERRAIN;
    }
    else if(QObject::sender()->objectName() == "FurnitureViewRadio")
    {
        layer = FURNITURE;
    }

    for(int i = 0; i < newmap->height; i++)
    {
        for(int j = 0; j < newmap->width; j++)
        {
            MapTile tile = newmap->tiles[newmap->Index(i, j)];
            switch(layer)
            {
            case GAME:
                ui->GameViewWidget->item(i, j)->setText(QString(tile.GetDisplayChar()));
                ui->GameViewWidget->item(i, j)->setBackgroundColor(tile.GetBgColor());
                ui->GameViewWidget->item(i, j)->setTextColor(tile.GetSymColor());
                break;
            case TERRAIN:
                ui->GameViewWidget->item(i, j)->setText(QString(tile.terrain.sym));
                ui->GameViewWidget->item(i, j)->setBackgroundColor(tile.terrain.color.bg);
                ui->GameViewWidget->item(i, j)->setTextColor(tile.terrain.color.fg);
                break;
            case FURNITURE:
                ui->GameViewWidget->item(i, j)->setText(QString(tile.furniture.sym));
                ui->GameViewWidget->item(i, j)->setBackgroundColor(tile.furniture.color.bg);
                ui->GameViewWidget->item(i, j)->setTextColor(tile.furniture.color.fg);
                break;
            default:
                break;
            }
        }
    }
}

void MapMaker::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Map", ".");

    QFile openfile;
    openfile.setFileName(filename);

    openfile.open(QIODevice::ReadOnly);

    QTextStream read(&openfile);

    int row = 0;
    while(!read.atEnd())
    {
        QString line = read.readLine();
        for(int i = 0; i < line.length(); i++)
        {

        }
    }
}

void MapMaker::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Map", ".");

    QFile savefile;
    savefile.setFileName(filename);

    savefile.open(QIODevice::Truncate | QIODevice::WriteOnly);

    QTextStream write(&savefile);

    write << newmap->Export();

    write.flush();
    savefile.close();
}

void MapMaker::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MapMaker::on_actionNew_triggered()
{
    NewMapDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        QString description = dlg.GetDescription();
        int height = dlg.GetHeight();
        int width = dlg.GetWidth();

        BuildNewMap(description, width, height);
    }
}

void MapMaker::on_actionOptions_triggered()
{
    MapOptionsDialog dlg(newmap->options);
    if(dlg.exec())
    {
        newmap->options.description = dlg.GetDescription();

        bool resize = ((newmap->options.height != dlg.GetHeight()) ||
                       (newmap->options.width != dlg.GetWidth()));

        newmap->options.height = dlg.GetHeight();
        newmap->options.width = dlg.GetWidth();

        newmap->options.monstergroup = dlg.GetMonsterGroup();
        newmap->options.monsterchance = dlg.GetMonsterChance();
        newmap->options.monsterdensity = dlg.GetMonsterDensity();

        newmap->options.itemgroup = dlg.GetItemGroup();
        newmap->options.itemchance = dlg.GetItemChance();
        newmap->options.itemsongrass = dlg.GetItemOnGrass();

        if(resize)
        {
            newmap->Resize();
            this->Resize();
        }
    }
}

void MapMaker::on_actionSettings_triggered()
{
    OptionsDialog dlg;
    if(dlg.exec())
    {
        settings->setValue("cata-path", dlg.GetPath());
    }
}

void MapMaker::closeEvent(QCloseEvent *event)
{
    WriteSettings();
}
