#include <iostream>
#include "paddle.h"

Paddle::Paddle() {

  dx = 0;//инициализируем переменную dx
  image.load("paddle.png");//загружаем картинку

  rect = image.rect();//Получаем прямоугольник. Он ограничивает размеры загруженной картинки
  resetState();//устанавливаем ракетку в исходное положение
}

Paddle::~Paddle() {

 std::cout << ("Paddle deleted") << std::endl;
}

void Paddle::setDx(int x) {
  dx = x;
}

void Paddle::move() {//Метод для перемещения ракетки. Направление задается переменной dx

    int x = rect.x() + dx;//Возвращает координату x левого края прямоугольника.
    int y = rect.top();//Возвращает координату y верхнего края прямоугольника.

    rect.moveTo(x, y);//Перемещает прямоугольник, оставляя верхний левый угол в заданном положении (x, y).
}

void Paddle::resetState() {//устанавливает ракету в исходное положение

  rect.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Paddle::getRect() {

  return rect;
}

QImage & Paddle::getImage() {

  return image;
}
