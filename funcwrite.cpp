#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <funcwrite.h>
#include <math.h>
#include <stdio.h>

FuncWrite::FuncWrite(QWidget *parent) :
    QWidget(parent)
{
    eps = 0.1;
    color = new QColor("Black");
    eded = this->width()/10;
    numK = 5000;
    showing = false;
    clearing = false;
    thr = false;
    centerMoving = false;
    SuperStep = false;
}

void FuncWrite::paintEvent(QPaintEvent *event)
{
    //QWidget::paintEvent(event);
    QPainter p(this);
    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap("tmp.png"));
    /*QPoint pxStart, pyStart, pyFinish, pxFinish, activePoint, lastPoint;
    int XEnd = this->width() - 1;
    int YEnd = this->height() - 1;
    int XStart = (XEnd + 1)/2;
    int YStart = (YEnd + 1)/2;

    int XStep = XEnd / 10;
    int YStep = YEnd / 10;


    pxStart.setX(1);pxStart.setY(YStart);
    pxFinish.setX(XEnd);pxFinish.setY(YStart);
    pyStart.setX(XStart);pyStart.setY(1);
    pyFinish.setY(YEnd);pyFinish.setX(XStart);

    p.setPen(QPen(QColor("black"), 1, Qt::SolidLine));
    p.setBrush(QColor("white"));
    p.drawRect(1, 1, XEnd - 1, YEnd - 1);

    p.setBrush(QColor("blue"));
    p.drawRect(XStart - XStep, YStart - YStep, XStep * 2 + 1, YStep * 2 + 1);


    p.setPen(QPen(QColor("green"), 1, Qt::SolidLine));
    p.drawLine(pxStart, pxFinish);
    p.drawLine(pyStart, pyFinish);

    p.setPen(QPen(QColor("red"), 1, Qt::SolidLine));

    if (s==QString("")) {
        p.end();
        return;
    }

    if (vir == 0) {
        for (int i = 1; i <= XEnd; i++) {
            lastPoint = activePoint;
            bool tmp = error;
            error = false;
            x = double(i - XStart) / XStep;
            k = 0;
            activePoint.setX(i);
            activePoint.setY(YStart-FuncWrite::expr()*YStep);
            if (tmp) lastPoint = activePoint;
            if ((i != 1) && !error)
                p.drawLine(lastPoint, activePoint);
        }
    } else if (vir == 1) {
        p.setPen(QPen(QColor(100, 100, 30), 1, Qt::SolidLine));
        FuncWrite::errorRun(QString(""));
        for (int i = 1; i <= YEnd; i++) {
            for (int j = 1; j <= XEnd; j++) {
                x = double(j - XStart) / XStep;
                y = double(i - YStart) / YStep;
                k = 0;
                double tmp = FuncWrite::abs(FuncWrite::expr());
                QPoint p1;
                p1.setX(j);
                p1.setY(i);
                if ((tmp <= 2)&&(error)) {
                    lastPoint = p1;
                    error = false;
                    continue;
                }
                if (tmp < eps)
                    p.drawPoint(p1);
            }
        }
    } else if (vir == 2) {
        p.setPen(QPen(QColor(100, 100, 30), 1, Qt::SolidLine));\
        double ax[100000];
        double ay[100000];
        for (int i = kExpr = 0; i < 100000; kExpr += 0.1, i++) {
            ax[i] = FuncWrite::expr();
            k = 0;
        }
        QString tmp = s;
        s = s2;
        for (int i = kExpr = 0; i < 100000; kExpr += 0.1, i++) {
            ay[i] = FuncWrite::expr();
            k = 0;
        }
        s = tmp;
        QPoint pr, cur;
        pr.setX(double(ax[0] * double(XStep)) + XStart);
        pr.setY(double(-ay[0] * double(YStep)) + YStart);
        for (int i = 1; i < 10000; i++) {
            cur.setX(double(ax[i] * double(XStep)) + XStart);
            cur.setY(double(-ay[i] * double(YStep)) + YStart);
            p.drawLine(pr, cur);
            pr = cur;
        }
    } else if (vir == 4) {
        QPoint pr, cur;
        QString tmp = s;
        cur.setX(x);
        cur.setY(y);
        for (int i = 0; i<10000; i++) {
            pr = cur;
            k = 0;
            cur.setX(FuncWrite::expr());
            s = s2;
            k = 0;
            cur.setY(FuncWrite::expr());
            x = cur.x();
            y = cur.y();
            s = tmp;
            p.drawLine(pr, cur);
        }
    }
*/
    p.end();
//    tmpq.save("/home/vlad/image.png");
    event->accept();
}

void FuncWrite::draw()
{
    qDebug() << "FuncWrite::draw called...";
//    FuncWrite::createFile("tmp.png", this->height()-2, this->width()-2, s);
    emit startThread();
//    FuncWrite::update();
}

double FuncWrite::expr()
{
    FuncWrite::nextLexem();
    double res = FuncWrite::mult();
    while ((curlex == 2)||(curlex == 3)) {
        if (curlex == 2) {
            FuncWrite::nextLexem();
            res = res - FuncWrite::mult();
        } else {
            FuncWrite::nextLexem();
            res = res + FuncWrite::mult();
        }
    }
    return res;
}

const double FuncWrite::mult()
{
    double res = FuncWrite::step();
    while ((curlex == 1)||(curlex == 4)) {
        if (curlex == 1) {
            FuncWrite::nextLexem();
            res = res * FuncWrite::step();
        } else {
            FuncWrite::nextLexem();
            double tmp = FuncWrite::step();
            if (FuncWrite::equal(tmp, 0)) {
                FuncWrite::errorRun("division by zero");
            } else {
                res = res / tmp;
            }
        }
    }
    return res;
}

const double FuncWrite::step()
{
    double res = FuncWrite::ones();
    if (curlex == 12) {
        FuncWrite::nextLexem();
        double tmp = FuncWrite::step();
        return power(res, tmp);
    } else {
//        FuncWrite::nextLexem();
    }
    return res;
}
const double FuncWrite::ones()
{
    if (curlex == 0) {
        FuncWrite::nextLexem();
        return currentNumber;
    } else if (curlex == 2) {
        if ((prlex == 5) || (prlex == 12) || (prlex == 13)) {
            FuncWrite::nextLexem();
            return -FuncWrite::ones();
        } else {
            FuncWrite::errorRun("error expression::'-'");
            return 0;
        }
    } else if (curlex == 5) {
        double res = FuncWrite::expr();
        if (curlex != 6) {
            FuncWrite::errorRun("\")\" expected");
        }
        FuncWrite::nextLexem();
        return res;
    } else if (curlex == 10) {
        double tmp = FuncWrite::abs(FuncWrite::expr());
        if (curlex != 6) {
            FuncWrite::errorRun("\")\" expected");
        }
        FuncWrite::nextLexem();
        return tmp;
    } else if (curlex == 11) {
        double tmp = FuncWrite::expr();
        if (curlex != 6) {
            if (curlex != 13) {
                FuncWrite::errorRun("\")\" expected");
            } else {
                double t = FuncWrite::expr();
                if (curlex != 6) {
                    FuncWrite::errorRun("\")\" expected");
                }
                FuncWrite::nextLexem();
                return FuncWrite::sqrtN(tmp, t);
            }
        }
        FuncWrite::nextLexem();
        if (tmp < 0) {
            FuncWrite::errorRun("wrong sqrt");
        } else {
            return sqrt(tmp);
        }
    } else if (curlex == 8) {
        double tmp = sin(FuncWrite::expr());
        if (curlex != 6) {
            FuncWrite::errorRun("\")\" expected");
        }
        FuncWrite::nextLexem();
        return tmp;
    } else if (curlex == 9) {
        double tmp = cos(FuncWrite::expr());
        if (curlex != 6) {
            FuncWrite::errorRun("\")\" expected");
        }
        FuncWrite::nextLexem();
        return tmp;
    } else if (curlex == 7) {
        double tmp = FuncWrite::expr();
        tmp = sin(tmp)/cos(tmp);
        if (curlex != 6) {
            FuncWrite::errorRun("\")\" expected");
        }
        FuncWrite::nextLexem();
        return tmp;
    } else if (curlex == 14) {
        double tmp = FuncWrite::expr();
        if (curlex != 6)
            if (curlex != 13) {
                FuncWrite::errorRun("\")\" expected");
            } else {
                double t = FuncWrite::expr();
                if (curlex != 6) {
                    FuncWrite::errorRun("\")\" expected");
                }
                FuncWrite::nextLexem();
                return log(tmp) / log(t);
            }
        FuncWrite::nextLexem();
        return log(tmp);
    }
}

void FuncWrite::nextLex()
{
//    lexem = lex[k++];
}

void FuncWrite::nextLexem()
{
    prlex = curlex;
    if ((s[k] == 'x') || (s[k] == 'X')) {
//        lexem = "number";
        curlex = 0;
        currentNumber = x;
    } else if ((s[k] == 'k') || (s[k] == 'K')) {
        curlex = 0;
        currentNumber = kExpr;
    } else if ((s[k] == 'y') || (s[k] == 'Y')) {
//        lexem = "number";
        curlex = 0;
        currentNumber = y;
    } else if (((s[k] == 'l') || (s[k] == 'L'))&&(s[k + 1] != 'o')) {
        curlex = 0;
        currentNumber = l;
    } else if (s[k] == '*') {
//        lexem = "*";
        curlex = 1;
    } else if (s[k] == '-') {
//        lexem = "-";
        curlex = 2;
    } else if (s[k] == '+') {
//        lexem = "+";
        curlex = 3;
    } else if (s[k] == '/') {
//        lexem = "/";
        curlex = 4;
    } else if (s[k] == '(') {
//        lexem = "(";aliasing);

        curlex = 5;
    } else if (s[k] == ')') {
//        lexem = ")";
        curlex = 6;
    } else if (s[k] == '\0'){
//        lexem = "end";
        curlex = -1;
        return;
    } else if ((s[k] == 't')&&(s[k + 1] == 'g')) {
//        lexem = "tg";
        curlex = 7;
        k += 2;
    } else if ((s[k] == 's')&&(s[k + 1] == 'i')&&(s[k + 2] == 'n')) {
//        lexem = "sin";
        curlex = 8;
        k += 3;
    } else if ((s[k] == 'c')&&(s[k + 1] == 'o')&&(s[k + 2] == 's')) {
//        lexem = "cos";
        curlex = 9;
        k += 3;
    } else if ((s[k] == 'a')&&(s[k + 1] == 'b')&&(s[k + 2] == 's')) {
        k += 3;
//        lexem = "abs";
        curlex = 10;
    } else if ((s[k] == 's')&&(s[k + 1] == 'q')&&(s[k + 2] == 'r')&&(s[k + 3] == 't')) {
        k += 4;
//        lexem = "sqrt";
        curlex = 11;
    } else if (s[k] == '^') {
        curlex = 12;
    } else if (s[k] == '|') {
        curlex = 13;
    } else if ((s[k] == 'l') && (s[k + 1] == 'o') && (s[k + 2] == 'g')) {
        k += 3;
        //lexem = log
        curlex = 14;
    } else if (s[k].isDigit()){
//        lexem = "number";
        curlex = 0;
        currentNumber = 0;
        while (s[k].isDigit()) {
            currentNumber = currentNumber * 10 + QString(s[k]).toInt();
            k++;
        }
        if ((s[k] == '.')||(s[k] == ',')) {
            int z = 10;
            k++;
            while (s[k].isDigit()) {
                currentNumber = currentNumber + double(QString(s[k]).toInt())/z;
                z = z * 10;
                k++;
            }
        }
        k--;
    } else {
        errorRun(QString("Unknown symbol ")+QString(s[k]));
//        lexem = "end";
        curlex = -1;
    }
    k++;
}

const bool FuncWrite::equal(double a, double b)
{
    return (abs(a-b)<eps);
}

const double FuncWrite::abs(double a)
{
    if (a<0) return -a; else
             return a;
}

void FuncWrite::errorRun(QString s)
{
    if (s!="wrong sqrt")
        if (s!="division by zero")
            emit errorWas(s);
    error = true;
}



inline bool FuncWrite::inCircle(double x, double y)
{
    return x*x + (y - 5) * (y - 5) < 1.5*1.5;
}

inline bool FuncWrite::inFirstP(double x, double y)
{
    return y < -0.5 * x * x - 3 * x  - 2.5;
}

inline bool FuncWrite::inRomb(double x, double y)
{
    return abs(y + 1.5) / 2 + abs(x - 2.5) < 2.5;
}

inline bool FuncWrite::inSecondP(double x, double y)
{
    return x < -1.5 * (y - 3) * (y - 3) + 2;
}

inline bool FuncWrite::inRect(double x, double y)
{
    return (x > -4) && (x < -3) && (y < 2) && (y > -0.5);
}

inline bool FuncWrite::underFirstLine(double x, double y)
{
    return y < -3.0 / 2 * x;
}

inline bool FuncWrite::underSecondLine(double x, double y)
{
    return y < 2;
}

inline bool FuncWrite::firstRegion(double x, double y)
{
    return inFirstP(x, y) && inSecondP(x, y) && inRect(x, y);
}

inline bool FuncWrite::secondRegion(double x, double y)
{
    return inSecondP(x, y) && !underFirstLine(x, y) && !inCircle(x, y);
}

inline bool FuncWrite::thirdRegion(double x, double y)
{
    return underFirstLine(x, y) && !inFirstP(x, y) && !inSecondP(x, y) && !inRomb(x, y) && underSecondLine(x, y);
}

void FuncWrite::createFile(QString str, int width, int height, QString function)
{
    s = function;
    if (function == "Grapher") {
        QFile::remove("tmp.png");
        QFile::copy("icon.png", "tmp.png");
        return;
    }
    bool b =(lastHeight == height)&&(lastWidth == width)&&clearing;
    if (!b) {
        tmpq = new QImage(height + 1, width + 1, QImage::Format_RGB32);
        lastHeight = height;
        lastWidth = width;
    }
    QPainter p(tmpq);
//    p.setRenderHint(QPainter::Antialiasing);
    int XEnd = height - 1;
    int YEnd = width - 1;

    if (!centerMoving) {
        XStart = (XEnd + 1)/2;
        YStart = (YEnd + 1)/2;
    }


//    XStart = 10;
//    YStart = 10;

    double XStep = XEnd / 10;
    double YStep = YEnd / 10;
    XStep = YStep;
    if (eded != 0) {
        XStep = YStep = eded;
    }

    if (SuperStep) {
        XStep = SuperXStep->value();
        YStep = SuperYStep->value();
    }

//    XStep = width/(3-1);
//    YStep = height/(9-1);
//    XStart = /-1/XStep;
//    YStart = 1/YStep;


    QPoint pxStart, pyStart, pyFinish, pxFinish, activePoint, lastPoint;


    pxStart.setX(1);pxStart.setY(YStart);
    pxFinish.setX(XEnd);pxFinish.setY(YStart);
    pyStart.setX(XStart);pyStart.setY(1);
    pyFinish.setY(YEnd);pyFinish.setX(XStart);

//!!!!!!!!!!*/
    if (!b) {
        p.setPen(QPen(QColor("black"), 2, Qt::SolidLine));
        p.setBrush(QColor("white"));
        p.drawRect(1, 1, XEnd, YEnd);



        //  p.setBrush(QColor("blue"));
//        p.drawRect(XStart - XStep, YStart - YStep, XStep * 2 + 1, YStep * 2 + 1);

        p.setPen(QPen(QColor("green"), 1, Qt::SolidLine));
        p.drawLine(pxStart, pxFinish);
        p.drawLine(pyStart, pyFinish);


        for (int i = XStart + XStep; i < XEnd; i += XStep) {
            drawGori(&p, i, pxStart.y());
        }

        for (int i = XStart - XStep; i > 2; i -=XStep) {
            drawGori(&p, i, pxStart.y());
        }

        for (int i = YStart + YStep; i < YEnd - 2; i += YStep) {
            drawVert(&p, pyStart.x(), i);
        }

        for (int i = YStart - YStep; i > 2; i -= YStep) {
            drawVert(&p, pyStart.x(), i);
        }
    }
    if (s==QString("")) {
        p.end();
        tmpq->save(str);
        return;
    }




    p.setPen(QPen(*color, 2, Qt::SolidLine));
    if (vir == 0) {
        for (int i = 1; i <= numK; i++) {
            lastPoint = activePoint;
            bool tmp = error;
            error = false;
            x = double(i - XStart) / XStep;
            k = 0;
            activePoint.setX(i);
            activePoint.setY(YStart-FuncWrite::expr()*YStep);
            if (tmp) lastPoint = activePoint;
            if ((i != 1) && !error)
                p.drawLine(lastPoint, activePoint);
        }
    } else if (vir == 1) {
//        p.setPen(QPen(/*QColor(100, 100, 30)*/*color, 1, Qt::SolidLine));
        FuncWrite::errorRun(QString(""));
        for (int i = 1; i <= YEnd; i++) {
            for (int j = 1; j <= XEnd; j++) {
                x = double(j - XStart) / XStep;
                y = double(YStart - i) / YStep;
                k = 0;
                double tmp = FuncWrite::abs(FuncWrite::expr());
                QPoint p1;
                p1.setX(j);
                p1.setY(i);
                if ((tmp <= 2)&&(error)) {
                    lastPoint = p1;
                    error = false;
                    continue;
                }
                if (tmp < eps)
                    p.drawPoint(p1);

            }
        }
    } else if (vir == 2) {
//        p.setPen(QPen(/*QColor(100, 100, 30)*/*color, 1, Qt::SolidLine));

        for (int i = kExpr = 0; i < numK; kExpr += 0.1, i++) {
            ax[i] = FuncWrite::expr();
            k = 0;
        }
        QString tmp = s;
        s = s2;
        for (int i = kExpr = 0; i < numK; kExpr += 0.1, i++) {
            ay[i] = FuncWrite::expr();
            k = 0;
        }
        s = tmp;
        QPoint pr, cur;
        pr.setX(double(ax[0] * double(XStep)) + XStart);
        pr.setY(double(-ay[0] * double(YStep)) + YStart);
        for (int i = 1; i < numK; i++) {
            cur.setX(double(ax[i] * double(XStep)) + XStart);
            cur.setY(double(-ay[i] * double(YStep)) + YStart);
            p.drawLine(pr, cur);
            pr = cur;
        }
    } else if (vir == 3) {
        QPoint pr, cur;
        l = k = 0;
        cur = RLToRadian(FuncWrite::expr(), l, XStep, YStep, XStart, YStart);
        for (l = 0; l < numK; l += 0.1) {
            k = 0;
            pr = cur;
            cur = RLToRadian(FuncWrite::expr(), l, XStep, YStep, XStart, YStart);
            p.drawLine(pr, cur);
        }
    } else if (vir == 4) {
        QPoint pr, cur;
        QString tmp = s;
        cur.setX(x);
        cur.setY(y);
        for (int i = 0; ((i < 1000) && (cur.x() > 0) && (cur.y() > 0)); i++) {
            pr = cur;
            k = 0;
            cur.setX(FuncWrite::expr());
            s = s2;
            k = 0;
            cur.setY(FuncWrite::expr());
            x = cur.x();
            y = cur.y();
            s = tmp;
            p.drawLine(pr, cur);
        }
    } else if (vir == 5) {
        for (int i = 1; i <= YEnd; i++) {
            for (int j = 1; j <= XEnd; j++) {
                x = double(j - XStart) / XStep;
                y = double(YStart - i) / YStep;
                //double tmp = FuncWrite::abs(FuncWrite::expr());
                QPoint p1;
                p1.setX(j);
                p1.setY(i);
                p.setPen(QColor("grey"));

                if (firstRegion(x, y) || secondRegion(x, y) || thirdRegion(x, y))
                    p.drawPoint(p1);

                bool er;
                er = false;
                int u;
                int c = 0;
                p1.setX(p1.x() - c);
                for (u = -100; u < 100; u++)
                    if (abs(x - u) < eps) {
                        er = true;
                        break;
                    }
                if (er)
                    if (-100 + 100/trunc(y) * y < eps) {
                        p.setPen(QColor("black"));
                        p.drawPoint(p1);
                    }

                er = false;
                for (u = -100; u < 100; u++)
                    if (abs(y - u) < eps) {
                        er = true;
                        break;
                    }

                p1.setX(p1.x() + c);
                p1.setY(p1.y() - c);
                if (er)
                    if (-100 + 100/trunc(x) * x < eps ) {
                        p.setPen(QColor("black"));
                        p.drawPoint(p1);
                    }

                /*if ((tmp <= 2)&&(error)) {
                    lastPoint = p1;
                    error = false;
                    continue;
                }
                if (tmp < eps)
                    p.drawPoint(p1);*/
            }
        }

        p.setPen(QColor("green"));
        for (int x = -100; x < 100; x++) {
            if (x == 0)
                p.setPen(QColor("magenta"));
            else
                p.setPen(QColor("black"));
            p.drawLine(x * XStep + XStart, -10000, x * XStep + XStart, 10000);
            p.drawLine(-10000, -(x * YStep - YStart), 10000, -(x * YStep - YStart));
        }
    }

    if (integralLabel->isVisible())
        integralLabel->setText(QString::number(integral(from->value(), to->value())));

    p.end();
    tmpq->save(str);
}

void FuncWrite::set(int b)
{
    FuncWrite::vir = b;
}

void FuncWrite::mousePressEvent (QMouseEvent *event)
{lastWidth;
    bool thr;
    clickX = event->x();
    clickY = event->y();

    if (vir == 4) {
       x = event->x();
       y = event->y();
//       event->accept();
       FuncWrite::draw();
    }
}

void FuncWrite::drawGori(QPainter *p, int x, int y)
{
    QPoint p1, p2;
    p1.setX(x);
    p2.setX(x);
    p1.setY(y - 3);
    p2.setY(y + 3);
    p->drawLine(p1, p2);
}

void FuncWrite::drawVert(QPainter *p, int x, int y)
{
    QPoint p1, p2;
    p1.setY(y);
    p2.setY(y);lastWidth;
    bool thr;
    p1.setX(x - 3);
    p2.setX(x + 3);
    p->drawLine(p1, p2);
}

double FuncWrite::power(double n, double st)
{
//    double res = 1;
//    for (int i = 0; i < st; i++)
//        res *= n;
    double res = pow(n, st);
    if (res != res) FuncWrite::errorRun("error power");
    return res;
}

double FuncWrite::sqrtN(double n, double st)
{
    double res = pow(n, 1.0 / st);
    if (res != res) FuncWrite::errorRun("wrong sqrt");
    return res;
}

QPoint FuncWrite::RLToRadian(double r, double l, double XStep, double YStep, double XStart, double YStart)
{
    QPoint res;
    res.setX(double(r * cos(l) * XStep) + XStart);
    res.setY(double(-r * sin(l) * YStep) + YStart);
    return res;
}

void FuncWrite::zoomChanged(int a)
{
    eded = a;
    lastWidth = 0;
    falseThr();
}

void FuncWrite::setAcc(int a)
{
    numK = a;
    draw();
}

void FuncWrite::mouseMoveEvent(QMouseEvent *event)
{
    if (!centerMoving)
        return;
    qDebug() << event->x() << rand()%100;
    qDebug() << event->y() << rand()%100;
    qDebug() << "---------------";


    XStart += event->x() - clickX;
    YStart += event->y() - clickY;

    clickX = event->x();
    clickY = event->y();

    emit setBackCoord(XStart, YStart);

//    this->createFile("tmp.png", height() - 1, width() - 1, s);
//    this->repaint();
//    this->draw();
    //update();
}

void FuncWrite::showEvent(QShowEvent *event)
{
    if (showing)
        return;
    qDebug() << "showEvent";
//    sleep(1);
    showing = true;
    XStart = width() / 2;
    YStart = height() / 2;
    this->draw();
    emit setCoord(XStart, YStart);
    event->accept();
}

void FuncWrite::setCoord(int x, int y)
{
    XStart = x;
    YStart = y;
//    this->draw();
}

void FuncWrite::falseThr()
{
    createFile("tmp.png", height() - 1, width() - 1, s);
    repaint();
}

double FuncWrite::integral(double start, double finish) {
    double curres = 0;
    double eps = 1e-7;
    int already = 5;
    double step = (finish - start);
    curres = express(start) / 2 + express(finish) / 2;
    int i = 1;
    while (already != 0) {
        double tmpres = curres;
        step /= 2;
        double curp = start + step;

        for (int j = 0; j < i; j++) {
            tmpres += express(curp);
            curp += step * 2;
        }

        if (abs(curres * step - tmpres * step / 2) > eps)
            already = 5;
        else
            already--;

        i *= 2;
        curres = tmpres;
    }

    qDebug() << curres * step;
    return curres * step;
}

double FuncWrite::express(double a) {
    x = a;
    k = 0;
    return expr();
}
