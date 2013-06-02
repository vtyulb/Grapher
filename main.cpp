#include <QApplication>
#include "mainwindow.h"
#include <stdio.h>
#include <funcwrite.h>
void help()
{
    printf("Program created by Tyulbashev...\n");
    printf("use program --help|-h|-of=OutputFile -f=FUNCTION|-if=InputFile [-c=COLOR]\n");
    printf("Parametrs:\n");
    printf("\t--help|-h      -> to print help\n");
    printf("\t-f=FUNCTION    -> to define function\n");
    printf("\t-of=OutputFile -> to define output file\n");
    printf("\t-if=InputFile  -> to define input file\n");
    printf("\t-c=COLOR       -> to define color of function default=red\n");
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    } else {
        /*printf("I detect parametrs %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("%d parametr: %s\n", i, argv[i]);
        }*/
        QString OutFile, InFile;
        QString color;
        QString function;
        for (int i = 1; i < argc; i++)
            if ((QString(argv[i]) == QString("--help"))||(QString(argv[i]) == QString("-h"))) {
                help();
                return 0;
            } else if ((QChar(argv[i][0]) == QChar('-'))&&(QChar(argv[i][1]) == QChar('o'))&&(QChar(argv[i][2]) == QChar('f'))&&(QChar(argv[i][3]) == QChar('='))) {
                OutFile = argv[i];
                OutFile.remove(0, 4);
            } else if ((QChar(argv[i][0]) == QChar('-'))&&(QChar(argv[i][1]) == QChar('i'))&&(QChar(argv[i][2]) == QChar('f'))&&(QChar(argv[i][3]) == QChar('='))) {
                InFile = argv[i];
                InFile.remove(0, 4);
            } else if ((QChar(argv[i][0]) == QChar('-'))&&(QChar(argv[i][1]) == QChar('c'))&&(QChar(argv[i][2]) == QChar('='))) {
                color = argv[i];
                color.remove(0, 3);
            } else if ((QChar(argv[i][0]) == QChar('-'))&&(QChar(argv[i][1]) == QChar('f'))&&(QChar(argv[i][2]) == QChar('='))) {
                function = argv[i];
                function.remove(0, 3);
            } else {
                printf("Error argument: %s\n", argv[i]);
            }
        FuncWrite().createFile(OutFile, 1000, 1000, function);
        return 0;
    }
}
