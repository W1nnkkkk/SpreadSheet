#ifndef GOTOCELL_H
#define GOTOCELL_H

#include <QDialog>
#include "ui_gotocell.h"

class GoToCell : public QDialog, public Ui::GoToCellDialog {
    Q_OBJECT
public:
    GoToCell(QWidget* parent = nullptr);
private slots:
    void on_lineEdit_textChanged();
};



#endif // GOTOCELL_H
