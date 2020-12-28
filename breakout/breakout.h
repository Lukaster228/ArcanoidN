#pragma once

#include <QWidget>
#include <QKeyEvent>
#include "ball.h"
#include "brick.h"
#include "paddle.h"

class Breakout : public QWidget {

  public:
    Breakout(QWidget *parent = 0);
    ~Breakout();

  protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);//Ракетка управляется с помощью клавиш-стрелок на клавиатуре. В игре мы следим за событиями нажатия клавиш клавиатуры с помощью этих методов
    void keyReleaseEvent(QKeyEvent *);//Ракетка управляется с помощью клавиш-стрелок на клавиатуре. В игре мы следим за событиями нажатия клавиш клавиатуры с помощью этих методов
    void drawObjects(QPainter *);//Для отрисовки объектов
    void finishGame(QPainter *, QString);//Ждя того, чтобы закончить игру
    void moveObjects();//Для передвижения объектов

    void startGame();//Начало игры
    void pauseGame();//Пауза во время игры
    void stopGame();//Остановка игры
    void victory();//Победа
    void checkCollision();//Проверка то, коснулся ли шарик чего либо.

  private:
    int x;//В переменной x хранится текущее положение Ракетки по оси X. Переменная timerId используется для идентификации объекта timer. Это необходимо в тех моментах, когда мы приостанавливаем игру
    int timerId;//В переменной x хранится текущее положение Ракетки по оси X. Переменная timerId используется для идентификации объекта timer. Это необходимо в тех моментах, когда мы приостанавливаем игру
    static const int N_OF_BRICKS = 30;//Константа N_OF_BRICKS задает количество Кирпичей в игре
    static const int DELAY = 10;//Константа DELAY управляет скоростью игры
    static const int BOTTOM_EDGE = 400;//Когда Мяч пересекает нижний край окна, то игра заканчивается
    Ball *ball;//Переменные-указатели на объекты Мяча, Ракетки и массива Кирпичей
    Paddle *paddle;//Переменные-указатели на объекты Мяча, Ракетки и массива Кирпичей
    Brick *bricks[N_OF_BRICKS];//Переменные-указатели на объекты Мяча, Ракетки и массива Кирпичей
    bool gameOver;//Следующие 4 переменные отвечают за различные состояния игры
    bool gameWon;//Следующие 4 переменные отвечают за различные состояния игры
    bool gameStarted;//Следующие 4 переменные отвечают за различные состояния игры
    bool paused;//Следующие 4 переменные отвечают за различные состояния игры
};
