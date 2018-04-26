#include "janela.h"

Janela::Janela(QWidget *parent)
    : QWidget(parent){
    /* propriedades iniciais da janela */

    this->resize(1016, 616);
    this->setMinimumSize(1016, 616);
    this->setWindowTitle("FLIP INSIGHT");

    /* A mágica toda dentro do tabuleiro acontece pelo objeto time_anim_improved */
    _tabuleiro = new Tabuleiro((QFrame*)this);

    /* layout da janela principal */
    _lay = new QVBoxLayout(this);
    _lay->addWidget(_tabuleiro);
    this->setLayout(_lay);
}

Janela::~Janela() {

}

void Janela::setTipoTabuleiro(int tipo) {
    _tipoTabuleiro = tipo;
}

int Janela::getLargura() {
    _w_jan = this->width();
    return _w_jan;
}

int Janela::getAltura() {
    _h_jan = this->height();
    return _h_jan;
}
