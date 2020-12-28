#include <iostream>
#include "ball.h"

Ball::Ball() {//В начале игры мячик будет двигаться вправо-вверх

  xdir = 1;
  ydir = -1;

  image.load("ball.png");

  rect = image.rect();//Получаем прямоугольник. Он ограничивает размеры загруженной картинки
  resetState();
}

Ball::~Ball() {//Уничтожения шарика

  std::cout << ("Ball deleted") << std::endl;
}

void Ball::autoMove() {//Этот метод будет вызываться каждый игровой цикл для перемещения мяча по экрану. Если мяч доходит до конца экрана, то мяч меняет направление. Если касается низа экрана, то игра кончается.

  rect.translate(xdir, ydir);//Перемещает прямоугольник dx вдоль оси x и dy вдоль оси y относительно текущего положения.

  if (rect.left() == 0) {//Возвращает координату x левого края прямоугольника.
    xdir = 1;
  }

  if (rect.right() == RIGHT_EDGE) {//Возвращает координату x правого края прямоугольника.
    xdir = -1;
  }

  if (rect.top() == 0) {//Возвращает координату y верхнего края прямоугольника.
    ydir = 1;
  }
}

void Ball::resetState() {//При начале новой игры, ракетка будет становиться на стандартную позицию

  rect.moveTo(INITIAL_X, INITIAL_Y);
}

void Ball::setXDir(int x) {

  xdir = x;
}

void Ball::setYDir(int y) {

  ydir = y;
}

int Ball::getXDir() {

  return xdir;
}

int Ball::getYDir() {

  return ydir;
}

QRect Ball::getRect() {//Извлекает положение верхнего левого угла прямоугольника в *x и * y, а его размеры-в *ширину и *высоту.

  return rect;
}

QImage & Ball::getImage() {//Получает изображение ракетки

  return image;
}
