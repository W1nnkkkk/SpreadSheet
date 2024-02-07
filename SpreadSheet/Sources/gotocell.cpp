#include <QtGui>
#include <QRegularExpression>
#include "gotocell.h"

GoToCell::GoToCell(QWidget* parent) : QDialog(parent){
    setupUi(this);
    QRegularExpressionValidator* regExp = new QRegularExpressionValidator;
    QRegularExpression exp("[a-zA-Z][1-9][0-9]{0,3}");
    regExp->setRegularExpression(exp);
    lineEdit->setValidator((QValidator*)regExp);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCell::on_lineEdit_textChanged(){
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}
// в конструкторе можно использовать регулярные выражения так же есть классы для проверки значений
// QIntValidator. QDoubleValidatoe. QRegExpValidator
// [] - один символ
// {} - кол-во вхождений символов
