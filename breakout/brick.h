#pragma once

#include <QImage>
#include <QRect>

class Brick {

  public:
    Brick(int, int);
    ~Brick();

  public:
    bool isDestroyed();//Проверка на то, разрушена ли плитка
    void setDestroyed(bool);// Если плитка разрушена, то значение булет True
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    bool destroyed;
};
