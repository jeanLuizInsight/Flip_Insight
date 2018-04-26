#include "player.h"
#include <QDebug>

Player::Player(QFrame *parent, QColor color, float x, float y, int sw_sh)
    : QFrame(parent), _cor(color), _x_rect(x), _y_rect(y), _sw_sh(sw_sh) {
    _tem_triplo = false;
    _carrega_triplo = false;
    _dx = 0;  // pixel a incrementar no eixo x
    _dy = 0;  // pixel a incrementar no eixo y
    _mov_mun = false;
    _angulo_rotacao_mun = 0;
    _rotaciona = 0;

//    _timer_animacao_mun = new QTimer(this);
//    _timer_animacao_mun->start(200);
//    QObject::connect(_timer_animacao_mun, SIGNAL (timeout()), this, SLOT (moveMunicao()));

    _timer_disponibiliza_municao = new QTimer(this);
    _timer_disponibiliza_municao->start(5000);
    QObject::connect(_timer_disponibiliza_municao, SIGNAL(timeout()), this, SLOT(disponibilizaMunicao()));
}

Player::~Player() {

}

/**
 * Atualizo a posição do objeto no tabuleiro com base na constante de tempo
 * @brief Player::movePlayer
 * @param dt
 */
void Player::movePlayer(float dt) {
    /* verifico o deslocamento se + ou - */
    if (_dx != 0) {
        _x_rect += ((_dx * dt * 120) / 1000) / 0.777;
    }
    if (_dy != 0) {
        _y_rect += ((_dy * dt * 120) / 1000) / 0.777;
    }
}

/**
 * Desenho o objeto na tela invocando o método de pintura
 * @brief Player::drawPlayer
 */
void Player::drawPlayer(QPainter &painter) {
    painter.setPen(_cor);
    painter.setBrush(_cor);
    painter.drawRoundedRect(_x_rect, _y_rect, _sw_sh, _sw_sh, 4, 4);
    /* pinto as munições do player
     * utilizo o mesmo laço pra pintar os projeteils tbm
     */
    for (int x = 0; x < 8; x++) {
        if (x < 5)
            _municoes[x]->drawMunicao(painter);
        _projeteis[x]->drawProjetil(painter);
    }
}

/**
 * Busco o valor de referência para rotacionar munições
 * @brief Player::getRaioPlayer
 * @return
 */
float Player::getCentroPlayer() {

}

float Player::getX() {
    return _x_rect;
}

void Player::setX(float x) {
    _x_rect = x;
}

float Player::getY() {
    return _y_rect;
}

void Player::setY(float y) {
    _y_rect = y;
}

int Player::getDimensao() {
    return _sw_sh;
}

void Player::setDimensao(int d) {
    _sw_sh = d;
}

float Player::getDx() {
    return _dx;
}

void Player::setDx(float dx) {
    _dx = dx;
}

float Player::getDy() {
    return _dy;
}

void Player::setDy(float dy) {
    _dy = dy;
}

void Player::addMunicoes() {
    /* posição central do player */
    _pos_x_centro = (_x_rect + ((_sw_sh - 7.5) / 2.f));
    _pos_y_centro = (_y_rect + ((_sw_sh - 7.5) / 2.f));
    /* dimensão da munição (sempre tamanho do player dividido por 4.5) */
    float dim = _sw_sh / 4.5;
    float x_mun = 0;
    float y_mun = 0;
    /* raio do circulo munições */
    _raio = _pos_y_centro - (_y_rect + (dim / 3));
    // inicia em 0 e incremente em 72 pra pintar as 5 munições
    int angulo = 0;

    /* 5 munições */
    if (_municoes.empty()) {
        if (_cor == Qt::white) {
            for (int x = 0; x < 5; x++) {
                float radians = angulo * (3.1416 / 180);
                x_mun = (cos(radians) * _raio) + _pos_x_centro;
                y_mun = (sin(radians) * _raio) + _pos_y_centro;
                angulo += 72;
                _municoes.append(new Municao((QFrame*)this, Qt::black, x_mun, y_mun, dim));
            }
        }
        if (_cor == Qt::black) {
            for (int x = 0; x < 5; x++) {
                float radians = angulo * (3.1416 / 180);
                x_mun = (cos(radians) * _raio) + _pos_x_centro;
                y_mun = (sin(radians) * _raio) + _pos_y_centro;
                angulo += 72;
                _municoes.append(new Municao((QFrame*)this, Qt::white, x_mun, y_mun, dim));
            }
        }
    }
    // inicialmente visíveis
    // cor dinamica (inicialmente white se player black, black se player white)
    // pode ficar red se pegar especial do tabuleiro
}

void Player::moveMunicoes() {
    _rotaciona++;
    /* posição central do player */
    _pos_x_centro = (_x_rect + ((_sw_sh - 7.5) / 2.f));
    _pos_y_centro = (_y_rect + ((_sw_sh - 7.5) / 2.f));
    /* dimensão da munição (sempre tamanho do player dividido por 5) */
    float dim = _sw_sh / 4.5;
    /* raio do circulo munições */
    _raio = _pos_y_centro - (_y_rect + (dim / 3));

    if (_rotaciona >= 30 && !_tem_triplo) {
        _rotaciona = 0;
        _angulo_rotacao_mun %= 432;
        _angulo_rotacao_mun += 20;
        _mov_mun = false;
    }

    for (int x = 0; x < _municoes.size(); x++) {
        _municoes[x]->setWH(dim);
        float radians = _angulo_rotacao_mun * (3.1416 / 180);
        _municoes[x]->setX(((cos(radians) * _raio) + _pos_x_centro));
        _municoes[x]->setY(((sin(radians) * _raio) + _pos_y_centro));
        _angulo_rotacao_mun += 72;
    }
}

void Player::addProjeteis() {
    _pos_x_centro = (_x_rect + ((_sw_sh - 7.5) / 2.f));
    _pos_y_centro = (_y_rect + ((_sw_sh - 7.5) / 2.f));
    if (_projeteis.empty()) {
        for (int x = 0; x < 8; x++) {
            _projeteis.append(new Projetil((QFrame*)this, Qt::transparent, _pos_x_centro, _pos_y_centro, (_sw_sh / 3), (_sw_sh / 8)));
        }
    }
}

void Player::moveMunicao() {
    for (int x = 0; x < 5; x++) {
        if (_municoes[x]->isTriplo()) {
            _mov_mun = false;
            break;
        }
        _mov_mun = true;
    }
}

void Player::disponibilizaMunicao() {
    bool temp = true;
    if (_tem_triplo) {
        _carrega_triplo = false;
    }
    /* verifico se o usuario solicitou tiro triplo */
    if (_carrega_triplo && !_tem_triplo) {
        /* não pode ter nenhuma munição especial */
        for (int x = _municoes.size() - 1; x >= 0 ; x--) {
            if (_municoes[x]->getCor() == Qt::red) {
                /* somente irá carregar tiro triplo se não existir especial*/
                _carrega_triplo = false;
                temp = false;
                break;
            }
        }
    }
    for (int x = _municoes.size() - 1; x >= 0 ; x--) {
        if (temp && _carrega_triplo && !_tem_triplo) {
            _carrega_triplo = false;
            _tem_triplo = true;
            _municoes[x]->setIsTriplo(true);
            if (_cor == Qt::white) {
                _municoes[x]->setCor(Qt::black);
                break;
            }
            if (_cor == Qt::black) {
                _municoes[x]->setCor(Qt::white);
                break;
            }
        }
        if (!_carrega_triplo && !_tem_triplo) {
            if (_cor == Qt::white) {
                if (_municoes[x]->getCor() == Qt::white || _municoes[x]->getCor() == Qt::lightGray) {
                    _municoes[x]->setCor(Qt::black);
                    break;
                }
            }
            if (_cor == Qt::black) {
                if (_municoes[x]->getCor() == Qt::black || _municoes[x]->getCor() == Qt::lightGray) {
                    _municoes[x]->setCor(Qt::white);
                    break;
                }
            }
        }
    }
}

/**
 * Delimita movimentação do player nas dimensões do tabuleiro e nas peças de cor oposta a sua no tabuleiro
 * @brief Player::checkColisao
 * @param peca
 * @param w
 * @param h
 * @return
 */
bool Player::checkColisao(PecaTabuleiro *peca, float w, float h, float dt) {

    float le1 = peca->getX();
    float ld1 = peca->getX() + peca->getLargura();
    float lc1 = peca->getY();
    float lb1 = peca->getY() + peca->getAltura();

    float le2 = _x_rect;
    float ld2 = _x_rect + (float) _sw_sh;
    float lc2 = _y_rect;
    float lb2 = _y_rect + (float) _sw_sh;

    if (le2 >= 0 && le2 <= (w - _sw_sh) && lc2 >= 0 && lc2 <= (h - _sw_sh)) {
        if (peca->_cor != _cor && peca->_cor != Qt::lightGray) {
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
    }
    _x_rect -= ((_dx * dt * 120) / 1000) / 0.777;
    _y_rect -= ((_dy * dt * 120) / 1000) / 0.777;
    return true;
}

bool Player::checkColisao(Projetil *projetil) {
    float le1 = projetil->getX();
    float ld1 = projetil->getX() + (float) projetil->getLargura();
    float lc1 = projetil->getY();
    float lb1 = projetil->getY() + (float) projetil->getAltura();

    float le2 = _x_rect;
    float ld2 = _x_rect + (float) _sw_sh;
    float lc2 = _y_rect;
    float lb2 = _y_rect + (float) _sw_sh;

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

bool Player::checkColisaoProjeteis(Projetil *p, int pos) {
    float le1 = p->getX();
    float ld1 = p->getX() + (float) p->getLargura();
    float lc1 = p->getY();
    float lb1 = p->getY() + (float) p->getAltura();

    float le2 = _projeteis[pos]->getX();
    float ld2 = _projeteis[pos]->getX() + (float) _projeteis[pos]->getLargura();
    float lc2 = _projeteis[pos]->getY();
    float lb2 = _projeteis[pos]->getY() + (float) _projeteis[pos]->getAltura();

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

bool Player::checkColisao(Municao *m) {
    if (m->getCor() == Qt::red) {
        float le1 = m->getX();
        float ld1 = m->getX() + (float) m->getWH();
        float lc1 = m->getY();
        float lb1 = m->getY() + (float) m->getWH();

        float le2 = _x_rect;
        float ld2 = _x_rect + (float) _sw_sh;
        float lc2 = _y_rect;
        float lb2 = _y_rect + (float) _sw_sh;

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
    } else {
        return false;
    }
    return true;
}

