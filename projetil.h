#ifndef PROJETIL_H
#define PROJETIL_H

#pragma once
#include <QObject>
#include <QFrame>
#include <QColor>
#include <QPainter>
#include "peca_tabuleiro.h"
#include "municao.h"

class Projetil : public QFrame {
    Q_OBJECT

public:
    Projetil(QFrame *parent = NULL, QColor color = Qt::red, float x = 0, float y = 0, int w = 0, int h = 0);
    ~Projetil();
    void drawProjetil(QPainter &painter);
    void moveProjetil(float dt);
    QColor getCor();
    void setCor(QColor cor);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    int getAltura();
    void setAltura(int h);
    int getLargura();
    void setLargura(int w);
    bool existeProjetil();
    void setExisteProjetil(bool v);
    void setDirecao(char d);
    char getDirecao();
    bool checkColisao(PecaTabuleiro *peca, int player);
    bool checkColisao(Municao *m);
    void setDx(float dx);
    void setDy(float dy);


private:
    QColor _cor;
    float _x_proj, _y_proj;
    int _w_proj, _h_proj;
    float _dx, _dy;
    bool _existe_proj;
    char _direcao;

};

#endif // PROJETIL_H
