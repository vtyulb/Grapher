#ifndef FUNCWRITE_H
#define FUNCWRITE_H

#include <QWidget>
#include <QFile>
#include <QSpinBox>
#include <QMessageBox>
#include <QLabel>
#include <math.h>

class FuncWrite : public QWidget
{
    Q_OBJECT
public:
    explicit FuncWrite(QWidget *parent = 0);
    QString s, s2;
    double x;
    double y;
    QSpinBox *SuperXStep;
    QSpinBox *SuperYStep;
    bool SuperStep;
    double expr();
    int k;
    int XStart, YStart;
    void createFile(QString str, int height, int width, QString vir);
    QColor *color;
    bool clearing;
    bool showing;
    int lastHeight, lastWidth;
    bool thr;
    bool centerMoving;
    void falseThr();
    double integral(double, double);
    double express(double);

    QLabel *integralLabel;
    QDoubleSpinBox *from, *to;


protected:
    enum ET {a, b, c};
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void showEvent(QShowEvent *);

    const bool equal(double a, double b);

    void nextLexem();
    void nextLex();
    void errorRun(QString);

    const double mult();
    const double ones();
    const double abs(double a);

    const double step();
    void drawGori(QPainter *p, int x, int y);
    void drawVert(QPainter *p, int x, int y);
    double power(double n, double st);
    double sqrtN(double n, double st);
    QPoint RLToRadian(double r, double l, double XStep, double YStep, double XStart, double YStart);


    double currentNumber;
//    QString lexem;
    int curlex, prlex;
    QImage *tmpq;
    int eded;
    int numK;
    double ax[1000], ay[1000];

    QString lex[100];
    bool error;
    double kExpr;
    int vir;
    double l;
    double eps;

    int clickX, clickY;

    bool inCircle(double x, double y);
    bool inFirstP(double x, double y);
    bool inSecondP(double x, double y);
    bool inRomb(double x, double y);
    bool inRect(double x, double y);
    bool underFirstLine(double x, double y);
    bool underSecondLine(double x, double y);

    bool firstRegion(double x, double y);
    bool secondRegion(double x, double y);
    bool thirdRegion(double x, double y);

signals:
    void errorWas(QString);
    void startThread();
    void setBackCoord(int, int);

public slots:
    void draw();
    void set(int b);
    void zoomChanged(int);
    void setAcc(int);
    void setCoord(int, int);

};

#endif // FUNCWRITE_H
