#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class NewMapDialog;
}

class NewMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMapDialog(QWidget *parent = 0);
    ~NewMapDialog();

    QString GetDescription();
    int GetHeight();
    int GetWidth();

private:
    Ui::NewMapDialog *ui;
};

#endif // NEWMAPDIALOG_H
