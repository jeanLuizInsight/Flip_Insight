#include "projetil.h"

Projetil::Projetil(QFrame *parent, QColor color, float x, float y, int w, int h)
    : QFrame(parent), _cor(color), _x_proj(x), _y_proj(y), _w_proj(w), _h_proj(h) {
    _dx = 2.f;
    _dy = 2.f;
}

Projetil::~Projetil() {

}

void Projetil::drawProjetil(QPainter &painter) {
    painter.setPen(_cor);
    painter.setBrush(_cor);
    painter.drawRect(_x_proj, _y_proj, _w_proj, _h_proj);
}

void Projetil::moveProjetil(float dt) {
    if (this->getDirecao() == 'c') {
        _y_proj -= ((_dy * dt * 120) / 1000) / 0.777;
    }
    if (this->getDirecao() == 'b') {
        _y_proj += ((_dy * dt * 120) / 1000) / 0.777;
    }
    if (this->getDirecao() == 'e') {
        _x_proj -= ((_dx * dt * 120) / 1000) / 0.777;
    }
    if (this->getDirecao() == 'd') {
        _x_proj += ((_dx * dt * 120) / 1000) / 0.777;
    }
}

QColor Projetil::getCor() {
    return _cor;
}

void Projetil::setCor(QColor cor) {
    _cor = cor;
}

float Projetil::getX() {
    return _x_proj;
}

void Projetil::setX(float x) {
    _x_proj = x;
}

float Projetil::getY() {
    return _y_proj;
}

void Projetil::setY(float y) {
    _y_proj = y;
}

int Projetil::getAltura() {
    return _h_proj;
}

void Projetil::setAltura(int h) {
    _h_proj = h;
}

int Projetil::getLargura() {
    return _w_proj;
}

void Projetil::setLargura(int w) {
    _w_proj = w;
}

bool Projetil::existeProjetil() {
    return _existe_proj;
}

void Projetil::setExisteProjetil(bool v) {
    _existe_proj = v;
}

void Projetil::setDirecao(char d) {
    _direcao = d;
}

char Projetil::getDirecao() {
    return _direcao;
}

bool Projetil::checkColisao(PecaTabuleiro *peca, int player) {
    float le1 = peca->getX();
    float ld1 = peca->getX() + (float) peca->getLargura();
    float lc1 = peca->getY();
    float lb1 = peca->getY() + (float) peca->getAltura();

    float le2 = _x_proj;
    float ld2 = _x_proj + (float) _w_proj;
    float lc2 = _y_proj;
    float lb2 = _y_proj + (float) _h_proj;

    if (((peca->_cor == Qt::black && player == 0) || (peca->_cor == Qt::white && player == 1)) && peca->_cor != Qt::lightGray) {
        return false;
    } else {
        if (le1 > ld2) {
            return false;
        }
        if (ld1 < le2) {
            return false;
        }
        if (lc1 > lb2) {
            return false;
        }
        if (lb1 < lc2) {
            return false;
        }
    }
    return true;
}

bool Projetil::checkColisao(Municao *m) {
    float le1 = m->getX();
    float ld1 = m->getX() + (float) m->getWH();
    float lc1 = m->getY();
    float lb1 = m->getY() + (float) m->getWH();

    float le2 = _x_proj;
    float ld2 = _x_proj + (float) _w_proj;
    float lc2 = _y_proj;
    float lb2 = _y_proj + (float) _h_proj;

    if (le1 > ld2) {
        return false;
    }
    if (ld1 < le2) {
        return false;
    }
    if (lc1 > lb2) {
        return false;
    }
    if (lb1 < lc2) {
        return false;
    }
    return true;
}

void Projetil::setDx(float dx) {
    _dx = dx;
}

void Projetil::setDy(float dy) {
    _dy = dy;
}





