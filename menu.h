#ifndef MENU_H
#define MENU_H

#pragma once

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QColor>

class Menu : public QFrame {
    Q_OBJECT

public:
    float _w_1, _h_1, _w_2, _h_2, _w_3, _h_3, _w_4, _h_4, _w_5, _h_5, _w_back, _h_back;
    float _x_1, _y_1, _x_2, _y_2, _x_3, _y_3, _x_4, _y_4, _x_5, _y_5, _x_back, _y_back;
    Menu(QFrame *parent = NULL);
    ~Menu();
    void drawMenu(QPainter &painter);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    float getLargura();
    void setLargura(float w);
    float getAltura();
    void setAltura(float h);
    bool getVisualizaMenu();
    bool setVisualizaMenu(bool v);
    int getTipoTabuleiro();
    void setTipoTabuleiro(int t);
    void atualizaPosicoes();

private:
    int _x_menu, _y_menu;
    float _w_menu, _h_menu;
    bool _visualiza_menu;
    int _tipo_tabuleiro;
};

#endif // MENU_H
