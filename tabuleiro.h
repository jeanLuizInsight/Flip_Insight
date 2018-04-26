#ifndef TABULEIRO_H
#define TABULEIRO_H

#pragma once

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QColor>
#include <QPainter>
#include <QList>
#include <QDateTime>
#include <QTimer>
#include <QPoint>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <stdlib.h> // para gerar numeros aleatorios
#include <time.h>   // para gerar a 'random seed' baseada no tempo
#include "peca_tabuleiro.h"
#include "player.h"
#include "municao.h"
#include "menu.h"

class Tabuleiro : public QFrame {
    Q_OBJECT

public:
    Tabuleiro(QFrame *parent = NULL);
    ~Tabuleiro();
    void montaMapaTabuleiro(int tipo);
    void drawTabuleiro();
    void setTipo(int tipo);
    float getAltura();
    void setAltura(float h);
    float getLargura();
    void setLargura(float w);
    void restart(int playerVencedor);
    void addMunicoes();
    void pintaPecaAoColitarMunicao(Projetil *p, int pos, int player);
    void paintEvent(QPaintEvent *evento);
    void keyPressEvent(QKeyEvent *evento);
    void keyReleaseEvent(QKeyEvent *evento);
    void resizeEvent(QResizeEvent *evento);
    void mouseMoveEvent(QMouseEvent *evento);
    void mousePressEvent(QMouseEvent *evento);

public slots:
    void disponibilizaMunicoes();
    //void resetObjetos();

private slots:
    void temporizador();

private:
    qint64 _time_final;
    qint64 _time_acumulado;
    int _max_fps;
    float _constant_dt;

    char _tabela[14][24];            // armazena mapa do tabuleiro
    int _tipo;                       // tipo do mapa do tabuleiro
    int _tipo_visualizacao;
    float _w_tab;                     // largura
    float _h_tab;                     // altura
    QList<PecaTabuleiro*> _pecas;    // peças do tabuleiro
    Player *_one;                    // jogador 1
    Player *_two;                    // jogador 2
    bool _c_one, _b_one, _e_one, _d_one, _t_one, _c_two, _b_two, _e_two, _d_two, _t_two;
    bool _colidiu_one, _colidiu_two;
    char _ultima_direcao_proj_one;
    char _ultima_direcao_proj_two;
    QTimer *_timer_dispoe_municoes;
    QList<Municao*> _municoes_especiais;
    int _pos_peca_mun_especial[4];
    bool _carrega_triplo_one;
    bool _carrega_triplo_two;
    bool _visualiza_menu;
    Menu *_menu;
    QMediaPlayer *_som_fundo;
    QMediaPlayer *_som_tiro_one1;
    QMediaPlayer *_som_tiro_one2;
    QMediaPlayer *_som_tiro_one3;
    QMediaPlayer *_som_tiro_one4;
    QMediaPlayer *_som_tiro_one5;
    QMediaPlayer *_som_tiro_two1;
    QMediaPlayer *_som_tiro_two2;
    QMediaPlayer *_som_tiro_two3;
    QMediaPlayer *_som_tiro_two4;
    QMediaPlayer *_som_tiro_two5;
    QMediaPlayer *_som_explosao1;
    QMediaPlayer *_som_explosao2;
    QMediaPlayer *_som_explosao3;
    QMediaPlayer *_som_explosao4;
    QMediaPlayer *_som_explosao5;
    QMediaPlayer *_som_click;
    QMediaPlayer *_som_move;
    bool m1, m2, m3, m4, m5;
};

#endif // TABULEIRO_H
