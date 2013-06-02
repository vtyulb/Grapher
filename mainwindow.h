#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <drawfile.h>
#include <QFile>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    DrawFile *thread;
public slots:
    void updateString();
    void exec(double);
    void drawClicked();
    void errorWrite(QString);
    void changed(int);
    void threadStart();
    void saveAsFile();
    void showHelp();
    void showAbout();
    void pleaseWaitF();
    void pleaseWaitT();
    void colorChanged(QString);
    void clearClicked();
    void setCrossing(bool);
    void setCoord(int);
    void setBackCoord(int, int);
    void setCenterMoving(bool);
    void strange(bool);
    QString clearSpaces(QString *s);
 private:
    Ui::MainWindow *ui;
    bool thr;

};

#endif // MAINWINDOW_H
