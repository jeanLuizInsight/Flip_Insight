#include "municao.h"

Municao::Municao(QFrame *parent, QColor color, float x, float y, float wh)
    : QFrame(parent), _cor(color), _x_circle(x), _y_circle(y), _w_h_circle(wh) {
    _is_triplo = false;
    _var_anima_mun = 0;
    _is_especial_tabuleiro = false;
}

Municao::~Municao() {
}

void Municao::drawMunicao(QPainter &painter) {
    if (_is_triplo) {
        painter.setPen(Qt::red);
    } else {
        painter.setPen(_cor);
    }
    painter.setBrush(_cor);
    if (_is_especial_tabuleiro) {
        if (_var_anima_mun < 50)
            _var_anima_mun++;
        if (_var_anima_mun < 20) {
            painter.setBrush(Qt::transparent);
            painter.drawEllipse(_x_circle - 10, _y_circle - 10, _w_h_circle + 20, _w_h_circle + 20);
            painter.setBrush(_cor);
            painter.drawEllipse(_x_circle - 3, _y_circle - 3, _w_h_circle + 6, _w_h_circle + 6);
        } else if (_var_anima_mun < 30) {
            painter.drawEllipse(_x_circle + 2, _y_circle + 2, _w_h_circle - 4, _w_h_circle - 4);
        } else {
            if (_var_anima_mun < 40) {
                painter.drawEllipse(_x_circle, _y_circle, _w_h_circle, _w_h_circle);
            } else {
                if (_var_anima_mun == 50)
                    _var_anima_mun = 30;
                painter.drawEllipse(_x_circle + 1, _y_circle + 1, _w_h_circle - 2, _w_h_circle - 2);
            }
        }
    } else {
        painter.setBrush(_cor);
        painter.drawEllipse(_x_circle, _y_circle, _w_h_circle, _w_h_circle);
    }
}

float Municao::getX() {
    return _x_circle;
}

void Municao::setX(float x) {
    _x_circle = x;
}

float Municao::getY() {
    return _y_circle;
}

void Municao::setY(float y) {
    _y_circle = y;
}

float Municao::getWH() {
    return _w_h_circle;
}

void Municao::setWH(float wh) {
    _w_h_circle = wh;
}

void Municao::setCor(QColor cor) {
    _cor = cor;
}

QColor Municao::getCor() {
    return _cor;
}

bool Municao::isTriplo() {
    return _is_triplo;
}

void Municao::setIsTriplo(bool v) {
    _is_triplo = v;
}

bool Municao::isEspecialTabuleiro() {
    return _is_especial_tabuleiro;
}

void Municao::setIsEspecialTabuleiro(bool v) {
    _is_especial_tabuleiro = v;
}

void Municao::setvarAnima(int var) {
    _var_anima_mun = var;
}
