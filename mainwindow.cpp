#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new DrawFile();
    ui->label_2->setVisible(false);
    thr = false;
/*    QObject::connect(ui->drawPushButton, SIGNAL(clicked()), ui->widget, SLOT(draw()));
    QObject::connect(ui->drawPushButton, SIGNAL(clicked()), this, SLOT(updateString()));
*/
    QObject::connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(drawClicked()));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this->ui->widget, SLOT(set(int)));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changed(int)));
    QObject::connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(exec(double)));
    QObject::connect(ui->widget, SIGNAL(errorWas(QString)), this, SLOT(errorWrite(QString)));
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionDraw, SIGNAL(triggered()), this, SLOT(drawClicked()));
    QObject::connect(this->thread, SIGNAL(finished()), ui->widget, SLOT(update()));
    QObject::connect(ui->widget, SIGNAL(startThread()), this, SLOT(drawClicked()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveAsFile()));
    QObject::connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    QObject::connect(this->thread, SIGNAL(finished()), this, SLOT(pleaseWaitF()));
    QObject::connect(ui->widget, SIGNAL(startThread()), this, SLOT(pleaseWaitT()));
    QObject::connect(ui->lineEdit_3, SIGNAL(textChanged(QString)), this, SLOT(colorChanged(QString)));
//    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(drawClicked()));
    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->widget, SLOT(setAcc(int)));
    QObject::connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    QObject::connect(ui->actionCrossing, SIGNAL(triggered(bool)), this, SLOT(setCrossing(bool)));
    QObject::connect(ui->actionZoom, SIGNAL(triggered(bool)), ui->horizontalSlider, SLOT(setVisible(bool)));
    QObject::connect(ui->spinBox_2, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox_2, SLOT(setValue(int)));
    QObject::connect(ui->actionZoom, SIGNAL(triggered(bool)), ui->spinBox_2, SLOT(setVisible(bool)));
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->widget, SLOT(zoomChanged(int)));
    QObject::connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(setCoord(int)));
    QObject::connect(ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(setCoord(int)));
    QObject::connect(ui->widget, SIGNAL(setBackCoord(int,int)), this, SLOT(setBackCoord(int,int)));
    QObject::connect(ui->actionCenter, SIGNAL(triggered(bool)), ui->groupBox_5, SLOT(setVisible(bool)));
    QObject::connect(ui->actionCenter, SIGNAL(triggered(bool)), this, SLOT(setCenterMoving(bool)));
    QObject::connect(ui->actionStrageSteps, SIGNAL(triggered(bool)), ui->groupBox_6, SLOT(setVisible(bool)));
    QObject::connect(ui->actionStrageSteps, SIGNAL(triggered(bool)), this, SLOT(strange(bool)));
    QObject::connect(ui->actionIntegral, SIGNAL(triggered(bool)), ui->groupBox_7, SLOT(setVisible(bool)));

//    ui->horizontalSlider->setValue(50);
    //ui->widget->zoomChanged(50);
    ui->groupBox_5->setVisible(false);
    ui->groupBox_7->setVisible(false);
    ui->widget->integralLabel = ui->label_7;
    ui->widget->from = ui->doubleSpinBox_3;
    ui->widget->to = ui->doubleSpinBox_4;

    ui->clearButton->setVisible(false);
    bool thr;
    ui->horizontalSlider->setVisible(false);
    ui->spinBox_2->setVisible(false);
    thread->func = ui->widget;
    ui->label->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->widget->set(0);
    ui->groupBox_6->setVisible(false);
    ui->widget->SuperXStep = ui->spinBox_5;
    ui->widget->SuperYStep = ui->spinBox_6;
    ui->lineEdit->setText("Grapher");
    ui->actionDraw->trigger();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pleaseWaitF()
{
    ui->label_2->setVisible(false);
}

void MainWindow::pleaseWaitT()
{
    ui->label_2->setVisible(true);
}

void MainWindow::threadStart()
{
   qDebug() << "threadStart" << rand()%100;
    thr = false;
    if (thread->isRunning()) {
        thr = true;
        return;
    }
    thread->start();
    if (thr)
        threadStart();/*
    if (thread->isRunning())
        thread->terminate();
    thread->start();*/
//    falseThr();
    qDebug() << "threadStartend" << rand()%100;
}

void MainWindow::updateString()
{
    ui->widget->s = ui->lineEdit->text();
    ui->widget->s = "(" + clearSpaces(&ui->widget->s) + ")";
    ui->widget->s2 = ui->lineEdit_2->text();
    ui->widget->s2 = "(" + clearSpaces(&ui->widget->s2) + ")";
}

void MainWindow::exec(double i)
{
    ui->widget->x = i;
    ui->widget->k = 0;
    MainWindow::updateString();
    ui->doubleSpinBox_2->setValue(ui->widget->expr());
}

void MainWindow::drawClicked()
{
    MainWindow::updateString();
    ui->label->setVisible(false);
//    ui->widget->createFile("tmp.png", 1000, 1000, ui->widget->s);
    this->threadStart();
}

void MainWindow::errorWrite(QString string)
{
    ui->label->setText(string);
    ui->label->setVisible(true);
}

void MainWindow::changed(int n)
{
    if ((n == 0)||(n == 1)||(n == 3)) {
        ui->lineEdit_2->setVisible(false);
    } else {
        ui->lineEdit_2->setVisible(true);
    }

    if (n == 0) {
        ui->groupBox->setVisible(true);
    } else {
        ui->groupBox->setVisible(false);
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("GraphProgram"),
                       tr("This program is created by V.S.Tyulbashev"));
}

void MainWindow::showHelp()
{
    QMessageBox::about(this,
                       tr("GraphProgram"),
                       tr("no help"));
}
void MainWindow::saveAsFile()
{
    QSettings s;
    const QString searchPath = s.value("LastSaveDir", QDir::homePath()).toString();
    QString fileName = QFileDialog::getSaveFileName(this,
                                     tr("Save file..."),
                                     searchPath,
                                     tr("PNG files (*.png)"));
    s.setValue("LastSaveDir", QFileInfo(fileName).absoluteDir().absolutePath());

//    QFile file(fileName);
//    if (!file.open(QIODevice::WriteOnly)) {return;} else {
//        file.close();
   QFile::copy("tmp.png", fileName);
//    }
}

void MainWindow::colorChanged(QString s)
{
    *ui->widget->color = s;
}

void MainWindow::clearClicked()
{
    ui->widget->lastHeight = 0;
    MainWindow::drawClicked();
}

void MainWindow::setCrossing(bool b)
{
    ui->clearButton->setVisible(b);
    ui->widget->clearing = b;
}

QString MainWindow::clearSpaces(QString *s)
{
    QString c;
    c = *s;
    c.replace(' ', QString(""));
    for (int i = 0;i < c.length(); i++)
        c[i].toLower();
    return c;
}

void MainWindow::setCoord(int a)
{
    qDebug() << "set Coord";
    ui->widget->setCoord(ui->spinBox_3->value(), ui->spinBox_4->value());
    ui->widget->falseThr();
}

void MainWindow::setBackCoord(int x, int y)
{
    qDebug() << "setBackCoord";
    ui->spinBox_3->setValue(x);
    ui->spinBox_4->setValue(y);
}

void MainWindow::setCenterMoving(bool a)
{
    ui->widget->centerMoving = a;
    ui->widget->draw();
}

void MainWindow::strange(bool a)
{
    ui->widget->SuperStep = a;
}
