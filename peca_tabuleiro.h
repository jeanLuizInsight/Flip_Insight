#ifndef PECA_TABULEIRO_H
#define PECA_TABULEIRO_H

#pragma once

#include <QObject>
#include <QFrame>
#include <QColor>
#include <QPainter>

class PecaTabuleiro : public QFrame {
    Q_OBJECT

public:
    QColor _cor;           // cor da peça
    PecaTabuleiro(QFrame *parent = NULL, const QColor color = Qt::black, int l = 0, int c = 0);
    ~PecaTabuleiro();
    void drawPeca(QPainter &painter);
    float getAltura();
    void setAltura(float h);
    float getLargura();
    void setLargura(float w);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    int getLinha();
    void setLinha(int l);
    int getColuna();
    void setColuna(int c);
    QColor getCor();

signals:

public slots:

private:
    float _x_rect, _y_rect;  // posição da peça no eixo x e y
    float _h_rect, _w_rect;  // dimensão da peça
    int _linha, _coluna;
};

#endif // PECA_TABULEIRO_H
