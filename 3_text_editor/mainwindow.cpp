#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    //Shortcuts
    saveShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    saveAsShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), this);
    newShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this);
    openShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this);
    exitShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_G), this);
    copyShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_C), this);
    pasteShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_V), this);
    undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_K), this);
    cutShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_X), this);

    connect(saveShortcut, &QShortcut::activated, this, &MainWindow::on_actionSave_triggered);
    connect(saveAsShortcut, &QShortcut::activated, this, &MainWindow::on_actionSave_As_triggered);
    connect(newShortcut, &QShortcut::activated, this, &MainWindow::on_actionNew_triggered);
    connect(openShortcut, &QShortcut::activated, this, &MainWindow::on_actionOpen_triggered);
    connect(exitShortcut, &QShortcut::activated, this, &MainWindow::on_actionExit_triggered);
    connect(copyShortcut, &QShortcut::activated, this, &MainWindow::on_actionCopy_triggered);
    connect(pasteShortcut, &QShortcut::activated, this, &MainWindow::on_actionPaste_triggered);
    connect(undoShortcut, &QShortcut::activated, this, &MainWindow::on_actionUndo_triggered);
    connect(redoShortcut, &QShortcut::activated, this, &MainWindow::on_actionRedo_triggered);
    connect(cutShortcut, &QShortcut::activated, this, &MainWindow::on_actionCut_triggered);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui -> textEdit -> setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file (fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot Open File : " +file.errorString());
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui -> textEdit -> setText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered() {
    qDebug() << "Save Shortcut Triggered! yey";
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot Save File : " + file.errorString());
    }
    currentFile = fileName;
    setWindowTitle(fileName);

    QTextStream out(&file);
    QString text = ui -> textEdit -> toPlainText();
    out << text;
    file.close();

}

void MainWindow::on_actionSave_triggered() {
    QString fileName = currentFile;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot Save File : " + file.errorString());
    }

    QTextStream out(&file);
    QString text = ui -> textEdit -> toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered() {
    ui -> textEdit -> copy();
}

void MainWindow::on_actionPaste_triggered() {
    ui -> textEdit -> paste();
}

void MainWindow::on_actionUndo_triggered() {
    ui -> textEdit -> undo();
}

void MainWindow::on_actionRedo_triggered() {
    ui -> textEdit -> redo();
}

void MainWindow::on_actionCut_triggered() {
    ui -> textEdit -> cut();
}



