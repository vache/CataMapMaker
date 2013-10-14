#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

    QString GetPath();

private slots:
    void on_BrowseButton_clicked();

private:
    Ui::OptionsDialog *ui;

    QString path;
};

#endif // OPTIONSDIALOG_H
