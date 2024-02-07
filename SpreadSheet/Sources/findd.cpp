#include "findd.h"
#include <QtWidgets>
#include <QDialog>

findd::findd(QWidget *parent)
    : QDialog{parent}
{
    label = new QLabel(tr("Find &what:")); // tr - translate, Match &case - учитывать регистр
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit); // при нажатии горячей клавиши будет перескакивать на указанный в параметре объект

    caseCheckBox = new QCheckBox(tr("Match &case")); // ампермант указыает на горячую клавишу?
    backwardCheckBox  = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true); // при нажатии на ENTER по умолчанию или нет
    findButton->setEnabled(false); // по умолчании выключена

    closeButton = new QPushButton(tr("&Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString&)),
            this, SLOT(enableFindButton(const QString&))); // из-за макроса QObject в классе не используем расширение видимости, но можно испозовать

    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close())); // quit - все закрывает, close - закрывает текущее окно

    QHBoxLayout* topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch(); // добавляет какое-то растяжение

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle("Finder");
    setFixedHeight(sizeHint().height());
}

void findd::findClicked(){
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive: Qt::CaseInsensitive;

    if(backwardCheckBox->isChecked()) {
        emit findPrevios(text, cs); // emit - генерирует сигнал
    }
    else {
        emit findNext(text,cs);
    }
}


void findd::enableFindButton(const QString& text){
    findButton->setEnabled(!text.isEmpty());
}
