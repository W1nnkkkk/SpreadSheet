#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPropertyAnimation>

class QAction;
class QLabel;
class findd;
class Spreadsheet;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();


private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBar();
    void createConextMenu();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    void createTable();


    Spreadsheet *spr;
    findd *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFile;
    QString curFile;
    // processing temporary file

    enum {MaxRecentFiles = 5};
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    //file menu
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    QAction *closeAction;
    QAction *exitAction;

    // edit menu
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;

    //select actions
    QAction *selectAction;
    QAction *rowAction;
    QAction *columnAction;
    QAction *allAction;

    //find actions
    QAction *findAction;
    QAction *goToCellAction;
    //tool menu actions
    QAction *recalculateAction;
    QAction *sortAction;
    //options menu
    QAction *showGridAction;
    QAction *autoRecalculateAction;
    //help menu
    QAction *aboutAction;
    QAction *aboutQtAction;
};
#endif // MAINWINDOW_H
