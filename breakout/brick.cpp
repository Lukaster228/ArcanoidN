#include <iostream>
#include "brick.h"

Brick::Brick(int x, int y) {//Конструктор класса Brick загружает изображение Кирпича, инициирует переменную-флаг destroyed и устанавливает изображение в исходную позицию

  image.load("brickie.png");
  destroyed = false;
  rect = image.rect();//Получаем прямоугольник. Он ограничивает размеры загруженной картинки
  rect.translate(x, y);
}

Brick::~Brick() {

  std::cout << ("Brick deleted") << std::endl;
}

QRect Brick::getRect() {

  return rect;
}

void Brick::setRect(QRect rct) {

  rect = rct;
}

QImage & Brick::getImage() {

  return image;
}

bool Brick::isDestroyed() {// У объектов класса Brick есть переменная-флаг destroyed. Если её значение установлено как true, то кирпич считается разрушенным, и не отображается в окне

  return destroyed;
}

void Brick::setDestroyed(bool destr) {

  destroyed = destr;
}
