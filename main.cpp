/**
 * Trabalho implementado para a disciplina de PG1 do curso de Engenharia de Computação - UNOESC
 * Jean Luiz Zanatta
 *
 */

#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "janela.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Janela jan;
    jan.show();
    return app.exec();
}
