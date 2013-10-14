#ifndef MAPOPTIONSDIALOG_H
#define MAPOPTIONSDIALOG_H

#include <QDialog>
#include "mapoptions.h"

namespace Ui {
class MapOptionsDialog;
}

class MapOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapOptionsDialog(MapOptions options, QWidget *parent = 0);
    ~MapOptionsDialog();

    QString GetDescription();
    int GetHeight();
    int GetWidth();

    QString GetMonsterGroup();
    int GetMonsterChance();
    double GetMonsterDensity();

    QString GetItemGroup();
    int GetItemChance();
    bool GetItemOnGrass();

private:
    Ui::MapOptionsDialog *ui;

    void FillItemGroupBox();
    void FillMonsterGroupBox();

};

#endif // MAPOPTIONSDIALOG_H
