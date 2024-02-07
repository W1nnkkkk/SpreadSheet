#ifndef FINDD_H
#define FINDD_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class findd : public QDialog
{
    Q_OBJECT
public:
    explicit findd(QWidget *parent = nullptr);

signals:
    void findNext(const QString& str, Qt::CaseSensitivity cs);
    void findPrevios(const QString& str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString& text);
private:
    QLabel* label;
    QLineEdit* lineEdit;
    QCheckBox* caseCheckBox;
    QCheckBox* backwardCheckBox;
    QPushButton* findButton;
    QPushButton* closeButton;
};

#endif // FINDD_H
