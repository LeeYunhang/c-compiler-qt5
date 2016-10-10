#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringList>
#include "ui_mainwindow.h"
#include "QFile"
#include "QMessageBox"
#include "QFileDialog"
#include "QString"
#include "QIODevice"
#include "QTextStream"
#include "QTextCursor"
#include "QTextBlockFormat"
#include "QScrollBar"


#include "lexical.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void readFile();
    void showToken();
private slots:
    void on_code_textChanged();
    void on_line_number_verticalScrollbar_changed(int);
    void on_code_blockCountChanged(int newBlockCount);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
