#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QTimer>
#include "kerbyanimation.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer timer;
    int action = 0;

    char rightPixelData[17][18] = {
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
            {'_', '_', '_', '_', '_', '_', '_', 'B', 'B', 'B', 'B', 'B', '_', 'B', 'B', '_', '_', '_'},
            {'_', '_', '_', '_', '_', 'B', 'B', 'H', 'P', 'P', 'P', 'H', 'B', 'H', 'P', 'B', '_', '_'},
            {'_', '_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'B', '_'},
            {'_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'H', 'P', 'B', '_'},
            {'_', '_', '_', 'B', 'P', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'H', 'H', 'B', '_'},
            {'_', '_', 'B', 'P', 'P', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'P', 'H', 'B', '_'},
            {'_', 'B', 'H', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'B', '_'},
            {'_', 'B', 'P', 'P', 'H', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_'},
            {'_', 'B', 'P', 'P', 'H', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'P', 'B', '_', '_'},
            {'_', '_', 'B', 'B', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_'},
            {'_', 'B', 'H', 'H', 'H', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_'},
            {'_', 'B', 'H', 'H', 'H', 'H', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_', '_'},
            {'_', 'B', 'H', 'H', 'H', 'H', 'B', 'P', 'P', 'P', 'P', 'P', 'H', 'B', 'B', '_', '_', '_'},
            {'_', '_', 'B', 'H', 'H', 'H', 'H', 'B', 'H', 'H', 'H', 'B', 'B', 'H', 'H', 'B', '_', '_'},
            {'_', '_', '_', 'B', 'H', 'H', 'B', 'B', 'B', 'B', 'B', 'H', 'H', 'H', 'H', 'H', 'B', '_'},
            {'_', '_', '_', '_', 'B', 'B', '_', '_', '_', '_', '_', 'B', 'B', 'B', 'B', 'B', 'B', '_'}};

    char standPixelData[17][18] = {
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
            {'_', '_', '_', '_', '_', '_', '_', 'B', 'B', 'B', 'B', 'B', '_', '_', '_', '_', '_', '_'},
            {'_', '_', '_', '_', '_', 'B', 'B', 'H', 'P', 'P', 'P', 'H', 'B', 'B', '_', '_', '_', '_'},
            {'_', '_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_', '_'},
            {'_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'H', 'B', '_', '_'},
            {'_', '_', '_', 'B', 'P', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'P', 'B', '_', '_'},
            {'_', '_', 'B', 'P', 'P', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'P', 'P', 'B', '_'},
            {'_', 'B', 'H', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'H', 'B'},
            {'_', 'B', 'P', 'P', 'H', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'H', 'P', 'P', 'B'},
            {'_', 'B', 'P', 'P', 'H', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'H', 'P', 'P', 'B'},
            {'_', '_', 'B', 'B', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'B', 'B', '_'},
            {'_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_'},
            {'_', '_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_', '_'},
            {'_', '_', '_', '_', 'B', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'H', 'B', 'B', '_', '_', '_'},
            {'_', '_', '_', 'B', 'H', 'H', 'B', 'B', 'H', 'H', 'H', 'B', 'B', 'H', 'H', 'B', '_', '_'},
            {'_', '_', 'B', 'H', 'H', 'H', 'H', 'H', 'B', 'B', 'B', 'H', 'H', 'H', 'H', 'H', 'B', '_'},
            {'_', '_', 'B', 'B', 'B', 'B', 'B', 'B', '_', '_', '_', 'B', 'B', 'B', 'B', 'B', 'B', '_'}};

    char leftPixelData[17][18] = {
            {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
            {'_', '_', '_', 'B', 'B', '_', 'B', 'B', 'B', 'B', 'B', '_', '_', '_', '_', '_', '_', '_'},
            {'_', '_', 'B', 'P', 'H', 'B', 'H', 'P', 'P', 'P', 'H', 'B', 'B', '_', '_', '_', '_', '_'},
            {'_', 'B', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'B', '_', '_', '_', '_'},
            {'_', 'B', 'P', 'H', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'H', 'B', '_', '_', '_'},
            {'_', 'B', 'H', 'H', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'P', 'B', '_', '_', '_'},
            {'_', 'B', 'H', 'P', 'P', 'P', 'P', 'B', 'P', 'B', 'P', 'P', 'P', 'P', 'P', 'B', '_', '_'},
            {'_', 'B', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'H', 'H', 'P', 'P', 'P', 'H', 'B', '_'},
            {'_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'H', 'P', 'P', 'B', '_'},
            {'_', '_', 'B', 'P', 'P', 'P', 'P', 'P', 'B', 'P', 'P', 'P', 'P', 'H', 'P', 'P', 'B', '_'},
            {'_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'B', 'B', '_', '_'},
            {'_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'H', 'H', 'H', 'B', '_'},
            {'_', '_', '_', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'B', 'H', 'H', 'H', 'H', 'B', '_'},
            {'_', '_', '_', 'B', 'B', 'H', 'P', 'P', 'P', 'P', 'P', 'B', 'H', 'H', 'H', 'H', 'B', '_'},
            {'_', '_', 'B', 'H', 'H', 'B', 'B', 'H', 'H', 'H', 'B', 'H', 'H', 'H', 'H', 'B', '_', '_'},
            {'_', 'B', 'H', 'H', 'H', 'H', 'H', 'B', 'B', 'B', 'B', 'B', 'H', 'H', 'B', '_', '_', '_'},
            {'_', 'B', 'B', 'B', 'B', 'B', 'B', '_', '_', '_', '_', '_', 'B', 'B', '_', '_', '_', '_'}};

    const char *B = "0, 0, 0";
    const char *P = "255, 192, 203 ";
    const char *H = "255, 51, 153";
    const char *A = "255, 255, 255";

    QFile file("kerbyRight.ppm");
    file.open(QFile::WriteOnly);
    file.write("P3\n");
    file.write("18 17\n");
    file.write("255\n");

    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 18; j++) {
            if(rightPixelData[i][j] == 'B') {
                file.write(B);
                file.write(" ");
            } else if(rightPixelData[i][j] == 'P') {
                file.write(P);
                file.write(" ");
            } else if(rightPixelData[i][j] == 'H') {
                file.write(H);
                file.write(" ");
            }
            else if(rightPixelData[i][j] == '_') {
                            file.write(A);
                            file.write(" ");
                        }
        }
        file.write("\n");
    }
    file.close();


    QFile file2("kerbyStand.ppm");
    file2.open(QFile::WriteOnly);
    file2.write("P3\n");
    file2.write("18 17\n");
    file2.write("255\n");

    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 18; j++) {
            if(standPixelData[i][j] == 'B') {
                file2.write(B);
                file2.write(" ");
            } else if(standPixelData[i][j] == 'P') {
                file2.write(P);
                file2.write(" ");
            } else if(standPixelData[i][j] == 'H') {
                file2.write(H);
                file2.write(" ");
            }
            else if(standPixelData[i][j] == '_') {
                            file2.write(A);
                            file2.write(" ");
                        }
        }
        file2.write("\n");
    }
    file2.close();

    QFile file3("kerbyLeft.ppm");
    file3.open(QFile::WriteOnly);
    file3.write("P3\n");
    file3.write("18 17\n");
    file3.write("255\n");

    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 18; j++) {
            if(leftPixelData[i][j] == 'B') {
                file3.write(B);
                file3.write(" ");
            } else if(leftPixelData[i][j] == 'P') {
                file3.write(P);
                file3.write(" ");
            } else if(leftPixelData[i][j] == 'H') {
                file3.write(H);
                file3.write(" ");
            }
            else if(leftPixelData[i][j] == '_') {
                            file3.write(A);
                            file3.write(" ");
                        }
        }
        file3.write("\n");
    }
    file3.close();

    QLabel label;
    label.show();

    QObject::connect(&timer, &QTimer::timeout, [&](){
        int control = action % 4;
        switch (control) {
        case 0: label.setPixmap(QPixmap("kerbyRight.ppm").scaled(500, 500));
            break;
        case 1: label.setPixmap(QPixmap("kerbyStand.ppm").scaled(500, 500));
            break;
        case 2: label.setPixmap(QPixmap("kerbyLeft.ppm").scaled(500, 500));
            break;
        case 3: label.setPixmap(QPixmap("kerbyStand.ppm").scaled(500, 500));
            break;
        }
        action++;
     });

    timer.start(300);

    return a.exec();
}
