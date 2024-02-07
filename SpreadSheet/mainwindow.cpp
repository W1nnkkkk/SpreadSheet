#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spreadsheet.h"
#include "findd.h"
#include "gotocell.h"
#include "sortDialog.h"
#include <QtGui>
#include <QFileDialog>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable();
    createActions();
    createMenus();
    createContextMenu();
    createToolBar();
    createStatusBar();

    readSettings();
    findDialog = 0;

    setAttribute(Qt::WA_DeleteOnClose);

    foreach (QWidget *win, QApplication::topLevelWidgets())
    {
        if(MainWindow *mainWin = qobject_cast<MainWindow *>(win))
        {
            mainWin->updateRecentFileActions();
        }
    }

    setWindowIcon(QIcon(":/icons/icons/spreadSheet.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    spr = new Spreadsheet;
    spr->setColumnCount(26);
    spr->setRowCount(999);

    QStringList lst;
    QChar simbl = 'A';
    for (int i = 0; i < 26; ++i)
    {
        lst.push_back(simbl);
        ++simbl.unicode();
    }
    spr->setHorizontalHeaderLabels(lst);
    setCentralWidget(spr);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    /*if(okToContinue())
    {
        spr->clear();
        setCurrentFile("");
    }*/

    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void MainWindow::open()
{
    if(okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
    {
        return saveAs();
    }
    else
        return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Spreadsheet", ".", tr("Spreadsheet files (*.sp)"));
    if(fileName.isEmpty())
    {
        return false;
    }

    return saveFile(fileName);
}

void MainWindow::find()
{
    // Не модальное окно (не блокирует дейсвия основного окна)
    if(!findDialog)
    {
        findDialog = new findd(this);
        connect(findDialog, SIGNAL(findNext(QString,Qt::CaseSensitivity)), spr, SLOT(findNext(QString,Qt::CaseSensitivity)));
        connect(findDialog, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)), spr, SLOT(findPrevious(QString,Qt::CaseSensitivity)));
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCell *dialog = new GoToCell(this);
    if(dialog->exec())
    {
        QString str = dialog->lineEdit->text().toUpper();
        spr->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
    delete dialog;
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spr->selectRange();
    dialog.setColumnRange(QChar('A' + range.leftColumn()), QChar('A' + range.rightColumn()));
    if(dialog.exec())
    {
        SpreadsheetCompare compare;
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;

        compare.ascending[0] = (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] = (dialog.secondaryOrederCombo->currentIndex() == 0);
        compare.ascending[2] = (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spr->sort(compare);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"), tr("<h2>Spreadsheet</h2>"
                                                         "<p>Copyright &copy; 2024 Software Inc."
                                                         "Spreadsheet is a small aplication that "
                                                         "demonstrated QAction, QMainWindow, QMenuBar,"
                                                         "QStatusBar, QTableWidget, QToolBar and many other "
                                                         "Qt classers<br><br>"
                                                         "Игорь верни деньги!"));
}

void MainWindow::openRecentFile()
{
    if(okToContinue())
    {
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
        {
            loadFile(action->data().toString());
        }
    }
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spr->currentLocation());
    formulaLabel->setText(spr->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/icons/icons/newFile.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip("Create a new spreadsheet file");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/icons/icons/openFile.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Create a open spreadsheet file");
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/icons/icons/saveFile.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Create a save spreadsheet file");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setIcon(QIcon(":/icons/icons/saveFile.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Create a saveAs spreadsheet file");
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    closeAction = new QAction(tr("Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close this window - %1").arg(tr("Закрыть текущее окно")));
    connect(closeAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon(":/icons/icons/exitIcon.jpg"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    cutAction = new QAction(tr("&Cut"), this);
    cutAction->setIcon(QIcon(":/icons/icons/cutIcon.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip("Cut");
    connect(cutAction, SIGNAL(triggered()), spr, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/icons/icons/copyIcon.jpg"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip("Copy");
    connect(copyAction, SIGNAL(triggered()), spr, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/icons/icons/pasteIcon.jpg"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip("Paste");
    connect(pasteAction, SIGNAL(triggered()), spr, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/icons/icons/deleteIcon.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip("Delete");
    connect(deleteAction, SIGNAL(triggered()), spr, SLOT(del()));

    selectAction = new QAction(tr("Select"), this);
    selectAction->setStatusTip("Выбирать");

    rowAction = new QAction(tr("&Row"), this);
    connect(rowAction, SIGNAL(triggered()), spr, SLOT(selectCurrentRow()));

    columnAction = new QAction(tr("&Column"), this);
    connect(columnAction, SIGNAL(triggered()), spr, SLOT(selectCurrentColumn()));

    allAction = new QAction(tr("&All"), this);
    allAction->setShortcut(QKeySequence::SelectAll);
    allAction->setStatusTip(tr("Select All the cells int the QTableWidget"));
    connect(allAction, SIGNAL(triggered()), spr, SLOT(selectAll()));

    findAction = new QAction(tr("&Find"), this);
    findAction->setIcon(QIcon(":/icons/icons/findIcon.jpg"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip("Find");
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    goToCellAction = new QAction(tr("&Go to cell"), this);
    goToCellAction->setIcon(QIcon(":/icons/icons/gotocellIcon.jpg"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip("Go to cell...");
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

    recalculateAction = new QAction(tr("&Recalculate"), this);
    recalculateAction->setShortcut(tr("F9"));
    connect(recalculateAction, SIGNAL(triggered()), spr, SLOT(recalculate()));

    sortAction = new QAction(tr("&Sort"), this);
    sortAction->setStatusTip("Sort window");
    connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spr->showGrid());
    showGridAction->setStatusTip("Show or hide the QTableWidet grid");
    connect(showGridAction, SIGNAL(toggled(bool)), spr, SLOT(setShowGrid(bool)));

    autoRecalculateAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalculateAction->setCheckable(true);
    autoRecalculateAction->setStatusTip("Auto recalculate");
    autoRecalculateAction->setChecked(spr->autoRecalculate());
    connect(autoRecalculateAction, SIGNAL(toggled(bool)), spr, SLOT(setAutoRecalculate(bool)));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("&About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt lobrary's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();

    for(int i = 0; i < MaxRecentFiles; ++i)
    {
        fileMenu->addAction(recentFileActions[i]);
    }

    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(rowAction);
    selectSubMenu->addAction(columnAction);
    selectSubMenu->addAction(allAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalculateAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
    spr->addAction(cutAction);
    spr->addAction(copyAction);
    spr->addAction(pasteAction);
    spr->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" Programm working ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spr, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(updateStatusBar()));

    connect(spr, SIGNAL(modified()), this, SLOT(spreadsheetModified()));

    updateStatusBar();
}

void MainWindow::readSettings()
{
    QSettings settings("SpreadSheet", "Spreadsheet");

    restoreGeometry(settings.value("geometry").toByteArray());
    recentFile = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);
    bool autoRecalc = settings.value("AutoRecalc/autoRecalc", true).toBool();
    autoRecalculateAction->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
    QSettings settings("SpreadSheet", "Spreadsheet");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFile);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalculateAction->isChecked());
    settings.beginGroup("AutoRecalc");
    settings.setValue("autoRecalc", autoRecalculateAction->isChecked());
    settings.endGroup();
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadsheet"), tr("The document has benn modified.\n Do you want to save your changes"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if( r == QMessageBox::Yes)
        {
            return save();
        }
        else if( r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!spr->readFile(fileName))
    {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!spr->writeFile(fileName))
    {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString showName = "Untiled";
    if(!curFile.isEmpty())
    {
        showName = strippedName(curFile);
        recentFile.removeAll(curFile);
        recentFile.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Spreadsheet")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFile);
    while(i.hasNext())
    {
        if(!QFile::exists(i.next()))
        {
            i.remove();
        }
    }

    for(int j = 0; j < MaxRecentFiles; ++j)
    {
        if( j < recentFile.count())
        {
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFile[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFile[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFile.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}
