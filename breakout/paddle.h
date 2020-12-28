#pragma once

#include <QImage>
#include <QRect>

class Paddle {

  public:
    Paddle();
    ~Paddle();

  public:
    void resetState();//Для начальной позиции ракетки
    void move();//Передвижение ракетки
    void setDx(int);//Ракетка может двинаться только по оси x
    QRect getRect();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int dx;
    static const int INITIAL_X = 200;//это константы, которые представляют начальные координаты объекта
    static const int INITIAL_Y = 360;//это константы, которые представляют начальные координаты объекта
};
