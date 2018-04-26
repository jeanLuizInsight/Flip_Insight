#include "peca_tabuleiro.h"

PecaTabuleiro::PecaTabuleiro(QFrame *parent, QColor color, int l, int c)
    : QFrame(parent), _cor(color), _linha(l), _coluna(c) {

}

PecaTabuleiro::~PecaTabuleiro() {

}

void PecaTabuleiro::drawPeca(QPainter &painter) {
    painter.setPen(Qt::lightGray);
    painter.setBrush(_cor);
    painter.drawRect(_x_rect, _y_rect, _w_rect, _h_rect);
}

QColor PecaTabuleiro::getCor() {
    return _cor;
}

float PecaTabuleiro::getAltura() {
    return _h_rect;
}

void PecaTabuleiro::setAltura(float h) {
    _h_rect = h;
}

float PecaTabuleiro::getLargura() {
    return _w_rect;
}

void PecaTabuleiro::setLargura(float w) {
    _w_rect = w;
}

float PecaTabuleiro::getX() {
    return _x_rect;
}

void PecaTabuleiro::setX(float x) {
    _x_rect = x;
}

float PecaTabuleiro::getY() {
    return _y_rect;
}

void PecaTabuleiro::setY(float y) {
    _y_rect = y;
}

int PecaTabuleiro::getLinha() {
    return _linha;
}

void PecaTabuleiro::setLinha(int l) {
    _linha = l;
}

int PecaTabuleiro::getColuna() {
    return _coluna;
}

void PecaTabuleiro::setColuna(int c) {
    _coluna = c;
}
