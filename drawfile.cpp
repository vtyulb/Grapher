#include <drawfile.h>

DrawFile::DrawFile(QThread *parent) :
    QThread(parent)
{

}

void DrawFile::run()
{
    //usleep(1000);
    func->thr = true;
    func->createFile("tmp.png", func->height() - 1, func->width() - 1, func->s);
    usleep(100);
    func->update();
}
