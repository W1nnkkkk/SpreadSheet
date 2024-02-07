/********************************************************************************
** Form generated from reading UI file 'sort.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORT_H
#define UI_SORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_sortDialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout;
    QComboBox *primaryOrderCombo;
    QComboBox *primaryColumnCombo;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *secondaryGroupBox;
    QGridLayout *gridLayout_2;
    QComboBox *secondaryOrederCombo;
    QComboBox *secondaryColumnCombo;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *tertiaryGroupBox;
    QGridLayout *gridLayout_3;
    QComboBox *tertiaryOrderCombo;
    QComboBox *tertiaryColumnCombo;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;
    QPushButton *moreButton;

    void setupUi(QDialog *sortDialog)
    {
        if (sortDialog->objectName().isEmpty())
            sortDialog->setObjectName("sortDialog");
        sortDialog->resize(344, 385);
        gridLayout_4 = new QGridLayout(sortDialog);
        gridLayout_4->setObjectName("gridLayout_4");
        primaryGroupBox = new QGroupBox(sortDialog);
        primaryGroupBox->setObjectName("primaryGroupBox");
        gridLayout = new QGridLayout(primaryGroupBox);
        gridLayout->setObjectName("gridLayout");
        primaryOrderCombo = new QComboBox(primaryGroupBox);
        primaryOrderCombo->addItem(QString());
        primaryOrderCombo->addItem(QString());
        primaryOrderCombo->setObjectName("primaryOrderCombo");

        gridLayout->addWidget(primaryOrderCombo, 1, 1, 1, 2);

        primaryColumnCombo = new QComboBox(primaryGroupBox);
        primaryColumnCombo->addItem(QString());
        primaryColumnCombo->setObjectName("primaryColumnCombo");

        gridLayout->addWidget(primaryColumnCombo, 0, 1, 1, 1);

        label = new QLabel(primaryGroupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(primaryGroupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        gridLayout_4->addWidget(primaryGroupBox, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_2, 1, 0, 1, 1);

        secondaryGroupBox = new QGroupBox(sortDialog);
        secondaryGroupBox->setObjectName("secondaryGroupBox");
        gridLayout_2 = new QGridLayout(secondaryGroupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        secondaryOrederCombo = new QComboBox(secondaryGroupBox);
        secondaryOrederCombo->addItem(QString());
        secondaryOrederCombo->addItem(QString());
        secondaryOrederCombo->setObjectName("secondaryOrederCombo");

        gridLayout_2->addWidget(secondaryOrederCombo, 1, 1, 1, 2);

        secondaryColumnCombo = new QComboBox(secondaryGroupBox);
        secondaryColumnCombo->addItem(QString());
        secondaryColumnCombo->setObjectName("secondaryColumnCombo");

        gridLayout_2->addWidget(secondaryColumnCombo, 0, 1, 1, 1);

        label_3 = new QLabel(secondaryGroupBox);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(secondaryGroupBox);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout_4->addWidget(secondaryGroupBox, 2, 0, 1, 1);

        tertiaryGroupBox = new QGroupBox(sortDialog);
        tertiaryGroupBox->setObjectName("tertiaryGroupBox");
        gridLayout_3 = new QGridLayout(tertiaryGroupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        tertiaryOrderCombo = new QComboBox(tertiaryGroupBox);
        tertiaryOrderCombo->addItem(QString());
        tertiaryOrderCombo->addItem(QString());
        tertiaryOrderCombo->setObjectName("tertiaryOrderCombo");

        gridLayout_3->addWidget(tertiaryOrderCombo, 1, 1, 1, 2);

        tertiaryColumnCombo = new QComboBox(tertiaryGroupBox);
        tertiaryColumnCombo->addItem(QString());
        tertiaryColumnCombo->setObjectName("tertiaryColumnCombo");

        gridLayout_3->addWidget(tertiaryColumnCombo, 0, 1, 1, 1);

        label_5 = new QLabel(tertiaryGroupBox);
        label_5->setObjectName("label_5");

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(tertiaryGroupBox);
        label_6->setObjectName("label_6");

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        gridLayout_4->addWidget(tertiaryGroupBox, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        okButton = new QPushButton(sortDialog);
        okButton->setObjectName("okButton");

        verticalLayout->addWidget(okButton);

        cancelButton = new QPushButton(sortDialog);
        cancelButton->setObjectName("cancelButton");

        verticalLayout->addWidget(cancelButton);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        moreButton = new QPushButton(sortDialog);
        moreButton->setObjectName("moreButton");
        moreButton->setCheckable(true);
        moreButton->setChecked(false);

        verticalLayout->addWidget(moreButton);


        gridLayout_4->addLayout(verticalLayout, 0, 1, 3, 1);


        retranslateUi(sortDialog);
        QObject::connect(okButton, &QPushButton::clicked, sortDialog, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, sortDialog, qOverload<>(&QDialog::reject));
        QObject::connect(moreButton, &QPushButton::toggled, secondaryGroupBox, &QGroupBox::setVisible);
        QObject::connect(moreButton, &QPushButton::toggled, tertiaryGroupBox, &QGroupBox::setVisible);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(sortDialog);
    } // setupUi

    void retranslateUi(QDialog *sortDialog)
    {
        sortDialog->setWindowTitle(QCoreApplication::translate("sortDialog", "Sort", nullptr));
        primaryGroupBox->setTitle(QCoreApplication::translate("sortDialog", "&Primary Key", nullptr));
        primaryOrderCombo->setItemText(0, QCoreApplication::translate("sortDialog", "Ascending", nullptr));
        primaryOrderCombo->setItemText(1, QCoreApplication::translate("sortDialog", "Deskanding", nullptr));

        primaryColumnCombo->setItemText(0, QCoreApplication::translate("sortDialog", "None", nullptr));

        label->setText(QCoreApplication::translate("sortDialog", "Column:", nullptr));
        label_2->setText(QCoreApplication::translate("sortDialog", "Order:", nullptr));
        secondaryGroupBox->setTitle(QCoreApplication::translate("sortDialog", "&Secondary Key", nullptr));
        secondaryOrederCombo->setItemText(0, QCoreApplication::translate("sortDialog", "Ascending", nullptr));
        secondaryOrederCombo->setItemText(1, QCoreApplication::translate("sortDialog", "Deskending", nullptr));

        secondaryColumnCombo->setItemText(0, QCoreApplication::translate("sortDialog", "None", nullptr));

        label_3->setText(QCoreApplication::translate("sortDialog", "Column:", nullptr));
        label_4->setText(QCoreApplication::translate("sortDialog", "Order:", nullptr));
        tertiaryGroupBox->setTitle(QCoreApplication::translate("sortDialog", "&Tertiary Key", nullptr));
        tertiaryOrderCombo->setItemText(0, QCoreApplication::translate("sortDialog", "Ascending", nullptr));
        tertiaryOrderCombo->setItemText(1, QCoreApplication::translate("sortDialog", "Deskending", nullptr));

        tertiaryColumnCombo->setItemText(0, QCoreApplication::translate("sortDialog", "None", nullptr));

        label_5->setText(QCoreApplication::translate("sortDialog", "Column:", nullptr));
        label_6->setText(QCoreApplication::translate("sortDialog", "Order:", nullptr));
        okButton->setText(QCoreApplication::translate("sortDialog", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("sortDialog", "Cancel", nullptr));
        moreButton->setText(QCoreApplication::translate("sortDialog", "&More", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sortDialog: public Ui_sortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORT_H
