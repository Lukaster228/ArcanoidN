#pragma once

#include <QImage>
#include <QRect>

class Ball {

  public:
    Ball();
    ~Ball();

  public:
    void resetState();//Шарик в начальной позиции
    void autoMove();//Передвижение мяча по экрану
    void setXDir(int);//В переменных xdir и ydir хранится направление движения Мяча.
    void setYDir(int);//В переменных xdir и ydir хранится направление движения Мяча.
    int getXDir();
    int getYDir();
    QRect getRect();//Извлекает положение верхнего левого угла прямоугольника в *x и * y, а его размеры-в *ширину и *высоту.
    QImage & getImage();//Для текстуры шарика

  private:
    int xdir;
    int ydir;
    QImage image;
    QRect rect;
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 355;
    static const int RIGHT_EDGE = 300;
};
