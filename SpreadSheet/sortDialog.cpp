#include <QtGui>
#include "sortDialog.h"

SortDialog::SortDialog(QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();

    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    tertiaryColumnCombo->addItem(tr("None"));
    secondaryColumnCombo->addItem(tr("None"));

    primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while (ch <= last)
    {
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));
        ++ch.unicode();
    }
}
