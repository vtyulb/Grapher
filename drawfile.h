#ifndef DRAWFILE_H
#define DRAWFILE_H

#include <funcwrite.h>
#include <QThread>

class DrawFile : public QThread
{
    Q_OBJECT
public:
    explicit DrawFile(QThread *parent = 0);
    FuncWrite *func;
protected:
    void run();
signals:

public slots:

};

#endif // DRAWFILE_H
