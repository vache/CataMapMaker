#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QFileDialog>
#include <QSettings>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    QSettings settings("Cataclysm Building Designer", "Cataclysm Building Designer");
    ui->PathLE->setText(settings.value("cata-path", QString("")).toString());
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::on_BrowseButton_clicked()
{
    QFileDialog fd(this);
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly);
    if(fd.exec())
    {
        path = fd.selectedFiles()[0];
        ui->PathLE->setText(path);
    }
}

QString OptionsDialog::GetPath()
{
    return path;
}
