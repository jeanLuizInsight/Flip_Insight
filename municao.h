#ifndef MUNICAO_H
#define MUNICAO_H

#pragma once
#include <QObject>
#include <QFrame>
#include <QColor>
#include <QPainter>

class Municao : public QFrame {
    Q_OBJECT

public:
    Municao(QFrame *parent = NULL, QColor color = Qt::red, float x = 0, float y = 0, float wh = 0);
    ~Municao();
    void drawMunicao(QPainter &painter);
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    float getWH();
    void setWH(float wh);
    void setCor(QColor cor);
    QColor getCor();
    bool isTriplo();
    void setIsTriplo(bool v);
    bool isEspecialTabuleiro();
    void setIsEspecialTabuleiro(bool v);
    void setvarAnima(int var);

private:
    QColor _cor;
    float _x_circle, _y_circle;
    float _w_h_circle;
    bool _is_triplo;
    bool _is_especial_tabuleiro;
    int _var_anima_mun;
};

#endif // MUNICAO_H
