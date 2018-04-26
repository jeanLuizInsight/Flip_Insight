#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include <QObject>
#include <QFrame>
#include <QColor>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <math.h>
#include <peca_tabuleiro.h>
//#include <municao.h>
#include "projetil.h"

class Player : public QFrame {
    Q_OBJECT

public:
    QList<Municao*> _municoes;
    QList<Projetil*> _projeteis;
    QList<Projetil*> _projeteis_triplo; // lista com 3
    bool _carrega_triplo;
    bool _tem_triplo;
    Player(QFrame *parent = NULL, const QColor color = Qt::black, float x = 0, float y = 0, int sw_sh = 0);
    ~Player();
    void movePlayer(float dt);
    void drawPlayer(QPainter &painter);
    float getCentroPlayer();
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    int getDimensao();
    void setDimensao(int d);
    float getDx();
    void setDx(float dx);
    float getDy();
    void setDy(float dy);
    void addMunicoes();
    void moveMunicoes();
    void addProjeteis();
    bool checkColisao(PecaTabuleiro *peca, float w, float h, float dt);
    bool checkColisao(Projetil *projetil);
    bool checkColisaoProjeteis(Projetil *p, int pos);
    bool checkColisao(Municao *m);

public slots:
    void moveMunicao();
    void disponibilizaMunicao();

private:
    QColor _cor;            // cor do player
    int _sw_sh;             // dimensão (tamanho) do player
    float _x_rect, _y_rect; // posição no eixo x e y
    float _dx, _dy;         // distancia percorrida no eixo x e y
    float _pos_x_centro, _pos_y_centro;    // armazena o centro do player (referencia rotação munições)
    float _raio;
    QTimer *_timer_animacao_mun;
    QTimer *_timer_disponibiliza_municao;
    bool _mov_mun;
    int _angulo_rotacao_mun;
    int _rotaciona;
};

#endif // PLAYER_H
