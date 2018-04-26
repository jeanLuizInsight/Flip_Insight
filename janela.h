#ifndef JANELA_H
#define JANELA_H

#pragma once

#include <QtGui>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "menu.h"
#include "tabuleiro.h"

class Janela : public QWidget {
    Q_OBJECT

public:
    Janela(QWidget *parent = NULL);
    ~Janela();
    int getLargura();
    int getAltura();

public slots:
    void setTipoTabuleiro(int tipo);

private:
    Menu *_menu;
    int _w_jan, _h_jan;
    int _tipoTabuleiro;     // tipo do mapa do tabuleiro
    Tabuleiro *_tabuleiro;  // Qtimer temporizador
    QVBoxLayout *_lay;      // layout
};

#endif // JANELA_H
