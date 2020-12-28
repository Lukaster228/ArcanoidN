#include <QPainter>
#include <QApplication>
#include "breakout.h"

Breakout::Breakout(QWidget *parent)
    : QWidget(parent) {

  x = 0;
  gameOver = false;
  gameWon = false;
  paused = false;
  gameStarted = false;
  ball = new Ball();
  paddle = new Paddle();

  int k = 0;

  for (int i=0; i<5; i++) {//В конструкторе класса Breakout мы создаем экземпляр тридцати Кирпичей
    for (int j=0; j<6; j++) {
      bricks[k] = new Brick(j*40+30, i*10+50);
      k++;
    }
  }
}

Breakout::~Breakout() {

 delete ball;
 delete paddle;

}

void Breakout::paintEvent(QPaintEvent *e) {//В зависимости от переменных gameOver и gameWon мы либо заканчиваем игру, выдавая соответствующие сообщения, либо продолжаем отрисовывать в окне игровые объекты

  Q_UNUSED(e);//Указывает компилятору, что параметр с указанным именем не используется в теле функции. Это может быть использовано для подавления предупреждений компилятора, позволяя при этом определять функции со значимыми именами параметров в их сигнатурах.

  QPainter painter(this);

  if (gameOver) {

    finishGame(&painter, "Game lost");

  } else if(gameWon) {

    finishGame(&painter, "Victory");
  }
  else {

    drawObjects(&painter);
  }
}

void Breakout::finishGame(QPainter *painter, QString message) {//Метод finishGame() отображает завершающее сообщение в центре окна. Это либо "Game lost" ("Игра проиграна"), либо "Victory" ("Победа").

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);//Метод QFontMetrics::width() используется для вычисления ширины строки соответствующего сообщения
  int textWidth = fm.width(message);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));//Переводит систему координат на заданное смещение, то есть заданное смещение добавляется к точкам.
  painter->drawText(-textWidth/2, 0, message);//Рисует заданный текст внутри предоставленного прямоугольника.
}

void Breakout::drawObjects(QPainter *painter) {//Метод drawObjects() отрисовывает в окне все объекты игры: Мяч, Ракетку и Кирпичи. А так как данные объекты представлены изображениями, то при помощи метода drawImage() мы отображаем и их изображения

  painter->drawImage(ball->getRect(), ball->getImage());
  painter->drawImage(paddle->getRect(), paddle->getImage());

  for (int i=0; i<N_OF_BRICKS; i++) {
    if (!bricks[i]->isDestroyed()) {//Нужно для того, чтобы при столкновении мяча с плиткой, пилтка исчезала. Если убрать !, то плиток на экране видно не будет, но технически они будут существовать и при сталкновении они будут отрисововаться
      painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *e) {//В теле метода timerEvent() мы сначала перемещаем объекты, а затем проверяем, не столкнулся ли Мяч с Ракеткой или Кирпичом. В конце генерируем событие отрисовки

  Q_UNUSED(e);

  moveObjects();
  checkCollision();
  repaint();
}

void Breakout::moveObjects() {//Метод moveObjects() отвечает за перемещения объектов Мяч и Ракетка. В нем вызываются их собственные методы перемещения

  ball->autoMove();
  paddle->move();
}

void Breakout::keyReleaseEvent(QKeyEvent *e) {//Передвижение ракетки.

    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = 0;
            paddle->setDx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            paddle->setDx(dx);
            break;
    }
}

void Breakout::keyPressEvent(QKeyEvent *e) {//Когда игрок отпускает кнопку ← или →, то мы присваиваем переменной dx Ракетки значение 0. В результате Ракетка перестает двигаться

    int dx = 0;

    switch (e->key()) {//Когда игрок отпускает кнопку ← или →, то мы присваиваем переменной dx Ракетки значение 0. В результате Ракетка перестает двигаться
    case Qt::Key_Left:

        dx = -1;
        paddle->setDx(dx);

        break;

    case Qt::Key_Right:

        dx = 1;
        paddle->setDx(dx);
        break;

    case Qt::Key_P://Ставит игру на паузу

        pauseGame();
        break;

    case Qt::Key_Space://Запускает игру на пробел

        startGame();
        break;

    case Qt::Key_Escape://Выходит из игры на кнопку escape

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::startGame() {//Метод startGame() сбрасывает состояния объектов ball и paddle; они перемещаются в исходное положение.

  if (!gameStarted) {
    ball->resetState();
    paddle->resetState();

    for (int i=0; i<N_OF_BRICKS; i++) {//В цикле for мы устанавливаем флаг destroyed на false для каждого Кирпича, таким образом отображая их в окне.
      bricks[i]->setDestroyed(false);
    }

    gameOver = false;//Переменные gameOver, gameWon и gameStarted получают свои начальные логические значения.
    gameWon = false;//Переменные gameOver, gameWon и gameStarted получают свои начальные логические значения.
    gameStarted = true;//Переменные gameOver, gameWon и gameStarted получают свои начальные логические значения.
    timerId = startTimer(DELAY);//с помощью метода startTimer() мы запускаем таймер
  }
}

void Breakout::pauseGame() {//Функция pauseGame() используется для приостановки и запуска уже остановленной игры. Данное состояние игры управляется с помощью переменной paused.

  if (paused) {

    timerId = startTimer(DELAY);//Чтобы перезапустить его, мы вызываем метод startTimer()
    paused = false;
  } else {

    paused = true;
    killTimer(timerId);//Также мы храним и идентификатор таймера. Чтобы приостановить игру, мы «убиваем» таймер с помощью метода killTimer().
  }
}

void Breakout::stopGame() {//В методе stopGame() мы «убиваем» таймер и устанавливаем соответствующие флаги

  killTimer(timerId);
  gameOver = true;
  gameStarted = false;
}

void Breakout::victory() {

  killTimer(timerId);
  gameWon = true;
  gameStarted = false;
}

void Breakout::checkCollision() {//В методе checkCollision() мы делаем проверку столкновения Мяча с игровыми объектами. Игра заканчивается, если Мяч попадает в нижний край окна

  if (ball->getRect().bottom() > BOTTOM_EDGE) {//Возвращает координату y нижнего края прямоугольника. Если он больше BOTTOM_EDGE, который равен 400, то игра останавливается
    stopGame();
  }

  for (int i=0, j=0; i<N_OF_BRICKS; i++) {//Проверяем количество разрушенных Кирпичей. Если все Кирпичи уничтожены, то мы выиграли

    if (bricks[i]->isDestroyed()) {
      j++;
    }

    if (j == N_OF_BRICKS) {
      victory();
    }
  }

  if ((ball->getRect()).intersects(paddle->getRect())) {//Возвращает true, если этот прямоугольник пересекается с заданным прямоугольником

    int paddleLPos = paddle->getRect().left();
    int ballLPos = ball->getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {//Если Мяч попадает в верхнюю часть Ракетки, то меняем направление Мяча на влево-вверх
      ball->setXDir(-1);
      ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      ball->setXDir(-1);
      ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       ball->setXDir(0);
       ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       ball->setXDir(1);
       ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos > fourth) {
      ball->setXDir(1);
      ball->setYDir(-1);
    }
  }

  for (int i=0; i<N_OF_BRICKS; i++) {

    if ((ball->getRect()).intersects(bricks[i]->getRect())) {

      int ballLeft = ball->getRect().left();
      int ballHeight = ball->getRect().height();
      int ballWidth = ball->getRect().width();
      int ballTop = ball->getRect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!bricks[i]->isDestroyed()) {
        if(bricks[i]->getRect().contains(pointRight)) {//Если Мяч ударяется о нижнюю часть Кирпича, то мы меняем направление y Мяча — он идет вниз
           ball->setXDir(-1);
        }

        else if(bricks[i]->getRect().contains(pointLeft)) {
           ball->setXDir(1);
        }

        if(bricks[i]->getRect().contains(pointTop)) {
           ball->setYDir(1);
        }

        else if(bricks[i]->getRect().contains(pointBottom)) {
           ball->setYDir(-1);
        }

        bricks[i]->setDestroyed(true);
      }
    }
  }
}
