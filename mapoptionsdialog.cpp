#include "mapoptionsdialog.h"
#include "ui_mapoptionsdialog.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

MapOptionsDialog::MapOptionsDialog(MapOptions options, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapOptionsDialog)
{
    ui->setupUi(this);

    FillItemGroupBox();
    FillMonsterGroupBox();

    ui->DescriptionLE->setText(options.description);

    ui->HeightBox->setValue(options.height);
    ui->WidthBox->setValue(options.width);

    ui->MonsterGroupBox->setCurrentText(options.monstergroup);
    ui->MonsterChanceBox->setValue(options.monsterchance);
    ui->MonsterDensityBox->setValue(options.monsterdensity);

    ui->ItemGroupBox->setCurrentText(options.itemgroup);
    ui->ItemChanceBox->setValue(options.itemchance);
    ui->ItemsOnGrassBox->setChecked(options.itemsongrass);
}

MapOptionsDialog::~MapOptionsDialog()
{
    delete ui;
}

void MapOptionsDialog::FillItemGroupBox()
{
    QFile itemjson("./item_groups.json");
    itemjson.open(QIODevice::ReadOnly);

    QByteArray itemdata = itemjson.readAll();

    QJsonDocument jsondata = QJsonDocument::fromJson(itemdata);

    QJsonArray jsonarray = jsondata.array();

    ui->ItemGroupBox->addItem("Nothing");
    for(int i = 0; i < jsonarray.size(); i++)
    {
        if(jsonarray[i].isObject())
        {
            ui->ItemGroupBox->addItem(jsonarray[i].toObject()["id"].toString());
        }
    }
    itemjson.close();
}

void MapOptionsDialog::FillMonsterGroupBox()
{
    QFile monsterjson("./monstergroups.json");
    monsterjson.open(QIODevice::ReadOnly);

    QByteArray monsterdata = monsterjson.readAll();

    QJsonDocument jsondata = QJsonDocument::fromJson(monsterdata);

    QJsonArray jsonarray = jsondata.array();

    ui->MonsterGroupBox->addItem("Nothing");
    for(int i = 0; i < jsonarray.size(); i++)
    {
        if(jsonarray[i].isObject())
        {
            ui->MonsterGroupBox->addItem(jsonarray[i].toObject()["name"].toString());
        }
    }
    monsterjson.close();
}

QString MapOptionsDialog::GetDescription()
{
    return ui->DescriptionLE->text();
}

int MapOptionsDialog::GetHeight()
{
    return ui->HeightBox->value();
}

int MapOptionsDialog::GetWidth()
{
    return ui->WidthBox->value();
}

QString MapOptionsDialog::GetMonsterGroup()
{
    return ui->MonsterGroupBox->currentText();
}

int MapOptionsDialog::GetMonsterChance()
{
    return ui->MonsterChanceBox->value();
}

double MapOptionsDialog::GetMonsterDensity()
{
    return ui->MonsterDensityBox->value();
}

QString MapOptionsDialog::GetItemGroup()
{
    return ui->ItemGroupBox->currentText();
}

int MapOptionsDialog::GetItemChance()
{
    return ui->ItemChanceBox->value();
}

bool MapOptionsDialog::GetItemOnGrass()
{
    return ui->ItemsOnGrassBox->isChecked();
}
