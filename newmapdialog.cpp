#include "newmapdialog.h"
#include "ui_newmapdialog.h"

NewMapDialog::NewMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMapDialog)
{
    ui->setupUi(this);
}

NewMapDialog::~NewMapDialog()
{
    delete ui;
}

QString NewMapDialog::GetDescription()
{
    return ui->DescriptionLE->text();
}

int NewMapDialog::GetHeight()
{
    return ui->HeightBox->text().toInt();
}

int NewMapDialog::GetWidth()
{
    return ui->WidthBox->text().toInt();
}
