#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sort.h"

class SortDialog : public QDialog, public Ui::sortDialog {
    Q_OBJECT
public:
    SortDialog(QWidget* parent = nullptr);
    void setColumnRange(QChar first, QChar last);
};


#endif // SORTDIALOG_H
