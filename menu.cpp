#include "menu.h"

Menu::Menu(QFrame *parent)
    : QFrame(parent) {
    _x_menu = 0;
    _x_1 = 0;
    _x_2 = 0;
    _x_3 = 0;
    _x_4 = 0;
    _x_5 = 0;
    _x_back = 0;
    _y_menu = 100;
    _w_menu = 946;
    _h_menu = 416;
}

Menu::~Menu() {

}

void Menu::drawMenu(QPainter &painter) {
    painter.setFont(QFont("arial", 30, 50, false));

    painter.setPen(Qt::lightGray);
    painter.setBrush(Qt::lightGray);
    /* fundo branco */
    painter.fillRect(_x_menu, _y_menu, _w_menu, _h_menu, Qt::white);
    painter.setPen(Qt::lightGray);
    painter.drawText(_x_menu + (_w_menu / 2) - 120, _y_menu + 80, "SELECT MAP");

    painter.setFont(QFont("arial", 15, 50, false));
    /* 5 mapas */
    painter.drawRect(_x_menu, _y_1, _w_1, _h_1);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_menu / 2) - 20, _y_1 + 25, "Wrap");

    painter.setPen(Qt::lightGray);
    painter.drawRect(_x_menu, _y_2, _w_2, _h_2);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_menu / 2) - 27, _y_2 + 25, "Closed");

    painter.setPen(Qt::lightGray);
    painter.drawRect(_x_menu, _y_3, _w_3, _h_3);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_menu / 2) - 30, _y_3 + 25, "Corners");

    painter.setPen(Qt::lightGray);
    painter.drawRect(_x_menu, _y_4, _w_4, _h_4);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_menu / 2) - 27, _y_4 + 25, "Bomber");

    painter.setPen(Qt::lightGray);
    painter.drawRect(_x_menu, _y_5, _w_5, _h_5);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_menu / 2) - 16, _y_5 + 25, "Plus");

    painter.setPen(Qt::lightGray);
    painter.drawRoundedRect(_x_menu, _y_back, _w_back, _h_back, 4, 4);
    painter.setPen(Qt::white);
    painter.drawText(_x_menu + (_w_back / 2) - 24, _y_back + 25, "Back");
}

int Menu::getX() {
    return _x_menu;
}

void Menu::setX(int x) {
    _x_menu = x;
}

int Menu::getY() {
    return _y_menu;
}

void Menu::setY(int y) {
    _y_menu = y;
}

float Menu::getLargura() {
    return _w_menu;
}

void Menu::setLargura(float w) {
    _w_menu = w;
}

float Menu::getAltura() {
    return _h_menu;
}

void Menu::setAltura(float h) {
    _h_menu = h;
}

bool Menu::getVisualizaMenu() {
    return _visualiza_menu;
}

bool Menu::setVisualizaMenu(bool v) {
    _visualiza_menu = v;
}

int Menu::getTipoTabuleiro() {
    return _tipo_tabuleiro;
}

void Menu::setTipoTabuleiro(int t) {
    _tipo_tabuleiro = t;
}

void Menu::atualizaPosicoes() {
    _w_1 = _w_menu;
    _h_1 = _h_menu / 12;
    _w_2 = _w_menu;
    _h_2 = _h_menu / 12;
    _w_3 = _w_menu;
    _h_3 = _h_menu / 12;
    _w_4 = _w_menu;
    _h_4 = _h_menu / 12;
    _w_5 = _w_menu;
    _h_5 = _h_menu / 12;
    _w_back = _w_menu / 10;
    _h_back = _h_menu / 12;

    _y_1 = ((_y_menu + 100) + _h_1);
    _y_2 = ((_y_menu + 140) + _h_2);
    _y_3 = ((_y_menu + 180) + _h_3);
    _y_4 = (_y_menu + 220 + _h_4);
    _y_5 = (_y_menu + 260 + _h_5);
    _y_back = (_y_menu + 310 + _h_back);
}
