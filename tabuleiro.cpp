#include "tabuleiro.h"

Tabuleiro::Tabuleiro(QFrame *parent)
    : QFrame(parent) {
    this->setMouseTracking(true);

    _c_one = false;
    _b_one = false;
    _e_one = false;
    _d_one = false;
    _t_one = false;
    _c_two = false;
    _b_two = false;
    _e_two = false;
    _d_two = false;
    _t_two = false;
    m1 = true;
    m2 = true;
    m3 = true;
    m4 = true;
    m5 = true;
    _ultima_direcao_proj_one = ' ';
    _ultima_direcao_proj_two = ' ';
    _carrega_triplo_one = false;
    _carrega_triplo_two = false;

    _tipo = -1;
    _tipo_visualizacao = -1;
    _visualiza_menu = true;
    _menu = new Menu((QFrame*)this);
    /* 2 players *
     * e suas posições iniciais no tabuleiro
     */
    _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
    _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));

    _som_fundo = new QMediaPlayer();
    _som_fundo->setMedia(QUrl::fromLocalFile("qrc:/audio/fundo.mp3"));
    _som_tiro_one1 = new QMediaPlayer();
    _som_tiro_one2 = new QMediaPlayer();
    _som_tiro_one3 = new QMediaPlayer();
    _som_tiro_one4 = new QMediaPlayer();
    _som_tiro_one5 = new QMediaPlayer();
    _som_tiro_two1 = new QMediaPlayer();
    _som_tiro_two2 = new QMediaPlayer();
    _som_tiro_two3 = new QMediaPlayer();
    _som_tiro_two4 = new QMediaPlayer();
    _som_tiro_two5 = new QMediaPlayer();
    _som_tiro_one1->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_one2->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_one3->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_one4->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_one5->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_two1->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_two2->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_two3->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_two4->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_tiro_two5->setMedia(QUrl::fromLocalFile("qrc:/audio/tiro.wav"));
    _som_explosao1 = new QMediaPlayer();
    _som_explosao2 = new QMediaPlayer();
    _som_explosao3 = new QMediaPlayer();
    _som_explosao4 = new QMediaPlayer();
    _som_explosao5 = new QMediaPlayer();
    _som_explosao1->setMedia(QUrl::fromLocalFile("qrc:/audio/explosion.wav"));
    _som_explosao2->setMedia(QUrl::fromLocalFile("qrc:/audio/explosion.wav"));
    _som_explosao3->setMedia(QUrl::fromLocalFile("qrc:/audio/explosion.wav"));
    _som_explosao4->setMedia(QUrl::fromLocalFile("qrc:/audio/explosion.wav"));
    _som_explosao5->setMedia(QUrl::fromLocalFile("qrc:/audio/explosion.wav"));
    _som_click = new QMediaPlayer();
    _som_click->setMedia(QUrl::fromLocalFile("qrc:/audio/click.mp3"));
    _som_move = new QMediaPlayer();
    _som_move->setMedia(QUrl::fromLocalFile("qrc:/audio/move.wav"));

    _time_acumulado = 0;
    _max_fps = 120;
    /* constante padrão 8 ms */
    _constant_dt = 1000 / _max_fps;
    _time_final = QDateTime::currentMSecsSinceEpoch();

    /* start timer */
    QTimer::singleShot(1000 / _max_fps, this, SLOT(temporizador())); // a 8 ms invoca temporizador()

    _timer_dispoe_municoes = new QTimer(this);
    _timer_dispoe_municoes->start(15000);
    QObject::connect(_timer_dispoe_municoes, SIGNAL (timeout()), this, SLOT (disponibilizaMunicoes()));

    this->setFocus();
}

Tabuleiro::~Tabuleiro() {

}

void Tabuleiro::montaMapaTabuleiro(int tipo) {
    // crio meu tabuleiro a partir do mapa selecionado no menu inicial
    if (tipo == 0) {
        char tabelaTemp[14][24] = { { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
                                  };
        memcpy(_tabela, tabelaTemp, 14*24*sizeof(char));
    } else if (tipo == 1) {
        char tabelaTemp[14][24] = { { -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    { -1, -1,  0,  0,  1,  1,  1,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                                    {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1, -1 },
                                    { -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
                                  };
        memcpy(_tabela, tabelaTemp, 14*24*sizeof(char));
    } else if (tipo == 2) {
        char tabelaTemp[14][24] = { {  1,  1,  1,  1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,  1,  1,  1,  1 },
                                    {  1,  1,  1,  1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,  1,  1,  1,  1 },
                                    {  1,  1,  1,  1, 1,  1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1, 1,  1,  1,  1,  1 },
                                    {  1,  1,  1,  1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1,  1,  1,  1,  1 },
                                    {  1, -1, -1,  1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1,  1, -1, -1,  1 },
                                    {  1, -1, -1,  1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1,  1, -1, -1,  1 },
                                    { -1, -1, -1, -1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, -1, -1, -1, -1 },
                                    {  0, -1, -1,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0, -1, -1,  0 },
                                    {  0, -1, -1,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0, -1, -1,  0 },
                                    {  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0 },
                                    {  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0, -1, -1,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0 },
                                    {  0,  0,  0,  0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  0,  0,  0,  0 },
                                    {  0,  0,  0,  0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  0,  0,  0,  0 }
                                  };
        memcpy(_tabela, tabelaTemp, 14*24*sizeof(char));
    } else if (tipo == 3) {
        char tabelaTemp[14][24] = { { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    {  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  0 },
                                    {  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0 },
                                    {  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0 },
                                    {  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1, -1,  0 },
                                    {  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  0 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
                                  };
        memcpy(_tabela, tabelaTemp, 14*24*sizeof(char));
    } else if (tipo == 4) {
        char tabelaTemp[14][24] = { {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    {  0, -1, -1, -1,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1 },
                                    {  0, -1, -1, -1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1 },
                                    {  0, -1, -1, -1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1 },
                                    {  0, -1, -1, -1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    {  0,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0, -1, -1, -1,  1 },
                                    {  0,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0, -1, -1, -1,  1 },
                                    {  0,  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0, -1, -1, -1,  1 },
                                    {  0,  0,  0,  0, -1, -1, -1,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 },
                                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 }
                                  };
        memcpy(_tabela, tabelaTemp, 14*24*sizeof(char));
    }
    /*
     * a partir do mapa selecionado pelos jogadores
     */
    if (_pecas.empty()) {
        for (int l = 0; l < 14; l++) {
            for (int c = 0; c < 24; c++) {
                // peça preta
                if(_tabela[l][c] == 1) {
                    _pecas.append(new PecaTabuleiro((QFrame*)this, Qt::black, l, c));
                }
                // peça branca
                if (_tabela[l][c] == 0) {
                    _pecas.append(new PecaTabuleiro((QFrame*)this, Qt::white, l, c));
                }
                if (_tabela[l][c] == -1) {
                    _pecas.append(new PecaTabuleiro((QFrame*)this, Qt::lightGray, l, c));
                }
            }
        }
    }
}

void Tabuleiro::drawTabuleiro() {
    repaint();
}

void Tabuleiro::paintEvent(QPaintEvent *evento) {
    QFrame::paintEvent(evento);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    /* pinto o fundo do tabuleiro */
    painter.fillRect(0, 0, _w_tab, _h_tab, Qt::lightGray);
    painter.setPen(Qt::lightGray);

    if ((_tipo != -1 || _tipo_visualizacao != -1) && !_pecas.empty()) {
        for (int x = 0; x < _pecas.size(); x++) {
            /* pinto as peças */
            _pecas[x]->drawPeca(painter);
        }
    }
    if (_visualiza_menu) {
        _menu->drawMenu(painter);
    }
    if (!_visualiza_menu) {
        for (int x = 0; x < _municoes_especiais.size(); x++) {
            _municoes_especiais[x]->drawMunicao(painter);
        }
        /* pinto os players */
        _one->drawPlayer(painter);
        _two->drawPlayer(painter);
    }
}

/**
 * Invocado ao pressionar algum botão
 * @brief Tabuleiro::keyPressEvent
 * @param evento
 */
void Tabuleiro::keyPressEvent(QKeyEvent *evento) {
    QFrame::keyPressEvent(evento);
    switch (evento->key()) {
    /* botões player 1 */
    case Qt::Key_Up:
        _c_one = true;
        break;
    case Qt::Key_Down:
        _b_one = true;
        break;
    case Qt::Key_Left:
        _e_one = true;
        break;
    case Qt::Key_Right:
        _d_one = true;
        break;
    case Qt::Key_Space:  //tiro
        _t_one = true;
        break;
    case Qt::Key_B:  // carrega munição especial p/ tiro triplo do player 1
        _one->_carrega_triplo = true;
        break;

    /* botões player 2 */
    case Qt::Key_W:
        _c_two = true;
        break;
    case Qt::Key_S:
        _b_two = true;
        break;
    case Qt::Key_D:
        _d_two = true;
        break;
    case Qt::Key_A:
        _e_two = true;
        break;
    case Qt::Key_1:  //tiro
        _t_two = true;
        break;
    case Qt::Key_2:  // carrega munição especial p/ tiro triplo do player 2
        _two->_carrega_triplo = true;
        break;

    case Qt::Key_M:
        _som_fundo->stop();
        _visualiza_menu = true;
        break;
    default:
        break;
    }
}

/**
 * Invocado ao soltar algum botão (a principio utilizado p/ movimentar )
 * @brief Tabuleiro::keyReleaseEvent
 * @param evento
 */
void Tabuleiro::keyReleaseEvent(QKeyEvent *evento) {
    QFrame::keyReleaseEvent(evento);
    switch (evento->key()) {

    /* botões player 1 */
    case Qt::Key_Up:
        _c_one = false;
        break;
    case Qt::Key_Down:
        _b_one = false;
        break;
    case Qt::Key_Left:
        _e_one = false;
        break;
    case Qt::Key_Right:
        _d_one = false;
        break;
//    case Qt::Key_AltGr:  //tiro
//        _t_one = false;
//        break;

    /* botões player 2 */
    case Qt::Key_W:
        _c_two = false;
        break;
    case Qt::Key_S:
        _b_two = false;
        break;
    case Qt::Key_D:
        _d_two = false;
        break;
    case Qt::Key_A:
        _e_two = false;
        break;
//    case Qt::Key_1:  //tiro
//        _t_two = false;
//        break;
    default:
        break;
    }
}

void Tabuleiro::resizeEvent(QResizeEvent *evento) {
    QFrame::resizeEvent(evento);

    float w_tab_anterior = _w_tab;
    float h_tab_anterior = _h_tab;
    _w_tab = this->width();
    _h_tab = this->height();
    if (_w_tab != w_tab_anterior || _h_tab != h_tab_anterior) {
        if (!_pecas.empty()) {
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }

            /* armazeno qual a porcentagem de redimensionamento */
            float w_per_red = _w_tab - w_tab_anterior;
            float h_per_red = _h_tab - h_tab_anterior;
            float x_player = 0.f;
            float y_player = 0.f;
            x_player = (_one->getX() + (w_per_red / 4.5));
            y_player = (_one->getY() + (h_per_red / 3.7));
            _one->setX(x_player);
            _one->setY(y_player);

            x_player = (_two->getX() + (w_per_red / 1.3));
            y_player = (_two->getY() + (h_per_red / 1.5));
            _two->setX(x_player);
            _two->setY(y_player);

            this->addMunicoes();
        }
        if (_one != NULL && _two != NULL) {
            /* atualizo dimensões dos players */
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
        }
        /* atualizo dimensões do menu */
        _menu->setX(0);
        float centro = (_h_tab / 2);
        float y_ini = centro - 210;
        _menu->setY(y_ini);
        //_menu->setAltura(_h_tab - 200);
        _menu->setLargura(_w_tab);
        _menu->atualizaPosicoes();
    }
}

void Tabuleiro::mouseMoveEvent(QMouseEvent *evento) {
    QFrame::mouseMoveEvent(evento);
    if (_visualiza_menu) {
        QPoint pos = evento->pos();
        /* verifico qual a posição x e y em que o mause foi clicado */
        if ((pos.x() >= _menu->_x_1 && pos.x() <= (_menu->_x_1 + _menu->_w_1)) && (pos.y() >= _menu->_y_1 && pos.y() <= (_menu->_y_1 + _menu->_h_1))) {
            _tipo_visualizacao = 0;
            if (m1) {
                _som_move->play();
                m1 = false;
                m2 = true;
                m3 = true;
                m4 = true;
                m5 = true;
            }
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo_visualizacao);
        }
        if ((pos.x() >= _menu->_x_2 && pos.x() <= (_menu->_x_2 + _menu->_w_2)) && (pos.y() >= _menu->_y_2 && pos.y() <= (_menu->_y_2 + _menu->_h_2))) {
            _tipo_visualizacao = 1;
            if (m2) {
                _som_move->play();
                m1 = true;
                m2 = false;
                m3 = true;
                m4 = true;
                m5 = true;
            }
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo_visualizacao);
        }
        if ((pos.x() >= _menu->_x_3 && pos.x() <= (_menu->_x_3 + _menu->_w_3)) && (pos.y() >= _menu->_y_3 && pos.y() <= (_menu->_y_3 + _menu->_h_3))) {
            _tipo_visualizacao = 2;
            if (m3) {
                _som_move->play();
                m1 = true;
                m2 = true;
                m3 = false;
                m4 = true;
                m5 = true;
            }
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo_visualizacao);
        }
        if ((pos.x() >= _menu->_x_4 && pos.x() <= (_menu->_x_4 + _menu->_w_4)) && (pos.y() >= _menu->_y_4 && pos.y() <= (_menu->_y_4 + _menu->_h_4))) {
            _tipo_visualizacao = 3;
            if (m4) {
                _som_move->play();
                m1 = true;
                m2 = true;
                m3 = true;
                m4 = false;
                m5 = true;
            }
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo_visualizacao);
        }
        if ((pos.x() >= _menu->_x_5 && pos.x() <= (_menu->_x_5 + _menu->_w_5)) && (pos.y() >= _menu->_y_5 && pos.y() <= (_menu->_y_5 + _menu->_h_5))) {
            _tipo_visualizacao = 4;
            if (m5) {
                _som_move->play();
                m1 = true;
                m2 = true;
                m3 = true;
                m4 = true;
                m5 = false;
            }
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo_visualizacao);
        }
    }
}

void Tabuleiro::mousePressEvent(QMouseEvent *evento) {
    QFrame::mousePressEvent(evento);
    if (evento->button() == Qt::LeftButton) {
        QPoint pos = evento->pos();
        /* verifico qual a posição x e y em que o mause foi clicado */
        if ((pos.x() >= _menu->_x_1 && pos.x() <= (_menu->_x_1 + _menu->_w_1)) && (pos.y() >= _menu->_y_1 && pos.y() <= (_menu->_y_1 + _menu->_h_1))) {
            _visualiza_menu = false;
            _tipo = 0;
            _som_click->play();
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo);
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }
            this->addMunicoes();
            _one->~Player();
            _two->~Player();
            _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
            _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
            _som_fundo->play();
        }
        if ((pos.x() >= _menu->_x_2 && pos.x() <= (_menu->_x_2 + _menu->_w_2)) && (pos.y() >= _menu->_y_2 && pos.y() <= (_menu->_y_2 + _menu->_h_2))) {
            _visualiza_menu = false;
            _tipo = 1;
            _som_click->play();
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo);
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }
            this->addMunicoes();
            _one->~Player();
            _two->~Player();
            _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
            _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
            _som_fundo->play();
        }
        if ((pos.x() >= _menu->_x_3 && pos.x() <= (_menu->_x_3 + _menu->_w_3)) && (pos.y() >= _menu->_y_3 && pos.y() <= (_menu->_y_3 + _menu->_h_3))) {
            _visualiza_menu = false;
            _tipo = 2;
            _som_click->play();
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo);
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }
            this->addMunicoes();
            _one->~Player();
            _two->~Player();
            _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
            _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
            _som_fundo->play();
        }
        if ((pos.x() >= _menu->_x_4 && pos.x() <= (_menu->_x_4 + _menu->_w_4)) && (pos.y() >= _menu->_y_4 && pos.y() <= (_menu->_y_4 + _menu->_h_4))) {
            _visualiza_menu = false;
            _tipo = 3;
            _som_click->play();
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo);
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }
            this->addMunicoes();
            _one->~Player();
            _two->~Player();
            _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
            _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
            _som_fundo->play();
        }
        if ((pos.x() >= _menu->_x_5 && pos.x() <= (_menu->_x_5 + _menu->_w_5)) && (pos.y() >= _menu->_y_5 && pos.y() <= (_menu->_y_5 + _menu->_h_5))) {
            _visualiza_menu = false;
            _tipo = 4;
            _som_click->play();
            if (!_pecas.empty())
                _pecas.clear();
            this->montaMapaTabuleiro(_tipo);
            for (int x = 0; x < _pecas.size(); x++) {
                _pecas[x]->setAltura(_h_tab / 14);
                _pecas[x]->setLargura(_w_tab / 24);
                _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
            }
            this->addMunicoes();
            _one->~Player();
            _two->~Player();
            _one = new Player((QFrame*)this, Qt::white, (41.9 * 5), (43 * 4), ((_h_tab / 14) - 10));
            _two = new Player((QFrame*)this, Qt::black, (41.5 * 18), (42.7 * 9), ((_h_tab / 14) - 10));
            _one->setDimensao((_h_tab / 14) - 10);
            _one->addMunicoes();
            _one->addProjeteis();
            _two->setDimensao((_h_tab / 14) - 10);
            _two->addMunicoes();
            _two->addProjeteis();
            _som_fundo->play();
        }
        if ((pos.x() >= _menu->_x_back && pos.x() <= (_menu->_x_back + _menu->_w_back)) && (pos.y() >= _menu->_y_back && pos.y() <= (_menu->_y_back + _menu->_h_back))) {
            if (_tipo != -1 && !_pecas.empty()) {
                _visualiza_menu = false;
                _som_click->play();
                if (!_pecas.empty())
                    _pecas.clear();
                this->montaMapaTabuleiro(_tipo);
                for (int x = 0; x < _pecas.size(); x++) {
                    _pecas[x]->setAltura(_h_tab / 14);
                    _pecas[x]->setLargura(_w_tab / 24);
                    _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                    _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
                }
                _som_fundo->play();
            }
        }
    }
}

/**
 * Responsável por atualizar as munições especiais no tabuleiro (trabalhado na cor)
 * @brief Tabuleiro::disponibilizaMunicoes
 */
void Tabuleiro::disponibilizaMunicoes() {
    float dim = _one->getDimensao() / 4.5;
    if (!_municoes_especiais.empty() && !_visualiza_menu) {
        for (int x = 0; x < _municoes_especiais.size(); x++) {
            int peca = (int) rand() % 336;
            if (((peca % 2) == 0) && _municoes_especiais[x]->getCor() != Qt::red && _pecas[peca]->getCor() != Qt::lightGray) {
                _pos_peca_mun_especial[x] = peca;
                /* seto as posições das munições baseadas nas peças (fixas) */
                float pos_x = ((_pecas[peca]->getX() + (_pecas[peca]->getLargura() / 2)) - (dim / 2));
                float pos_y = ((_pecas[peca]->getY() + (_pecas[peca]->getAltura() / 2)) - (dim / 2));
                /* se as munições ja existem apenas atualizo suas posições */
                _municoes_especiais[x]->setWH(dim);
                _municoes_especiais[x]->setX(pos_x);
                _municoes_especiais[x]->setY(pos_y);
                /* disponibilizo todas ao mesmo tempo */
                _municoes_especiais[x]->setCor(Qt::red);
                _municoes_especiais[x]->setvarAnima(0);
            }
        }
    }
}

/**
 * Responsável pela animação do jogo (baseada em tempo)
 * OBS: Invocado a cada instante de tempo implementado no temporizador
 * @brief Tabuleiro::temporizador
 */
void Tabuleiro::temporizador() {
    /* armazeno o tempo em que o método foi invocado */
    qint64 time_inicial = QDateTime::currentMSecsSinceEpoch();

    /* armazeno o tempo que passou (atual subtraido da ultima atualização) */
    qint64 time_gasto = time_inicial - _time_final;

    /* acumulo o tempo que passou */
    _time_acumulado += time_gasto;

    if (_visualiza_menu) {
        while (_time_acumulado >= _constant_dt) {
            if (!_pecas.empty()) {
                for (int x = 0; x < _pecas.size(); x++) {
                    _pecas[x]->setAltura(_h_tab / 14);
                    _pecas[x]->setLargura(_w_tab / 24);
                    _pecas[x]->setX(_pecas[x]->getLargura() * _pecas[x]->getColuna());
                    _pecas[x]->setY(_pecas[x]->getAltura() * _pecas[x]->getLinha());
                }
            }
            _time_acumulado -= _constant_dt;
        }

    } else {
        if (_som_fundo->state() != QMediaPlayer::PlayingState) {
            _som_fundo->play();
        }
        /* teclas mov player 1 */
        if (_c_one && _e_one) {
            _one->setDx(-2);
            _one->setDy(-1);
        } else if (_c_one && _d_one) {
            _one->setDx(2);
            _one->setDy(-1);
        } else if (_b_one && _e_one) {
            _one->setDx(-2);
            _one->setDy(1);
        } else if (_b_one && _d_one) {
            _one->setDx(2);
            _one->setDy(1);
        } else if (_c_one) {
            _one->setDx(0);
            _one->setDy(-2);
            _ultima_direcao_proj_one = 'c';
        } else if (_b_one) {
            _one->setDx(0);
            _one->setDy(2);
            _ultima_direcao_proj_one = 'b';
        } else if (_e_one) {
            _one->setDx(-2);
            _one->setDy(0);
            _ultima_direcao_proj_one = 'e';
        } else if (_d_one) {
            _one->setDx(2);
            _one->setDy(0);
            _ultima_direcao_proj_one = 'd';
        } else {
            _one->setDx(0);
            _one->setDy(0);
        }
        /* tecla tiro player 1 */
        if (_t_one) {
            _t_one = false;
            bool especial = false;
            bool especial_triplo = false;
            for (int x = 0; x < 5; x++) {
                /* verifico se existe munição especial p/ tiro triplo */
                if (_one->_municoes[x]->isTriplo()) {
                    especial_triplo = true;
                    _one->_tem_triplo = false;
                    _one->_municoes[x]->setIsTriplo(false);
                    if (x == 4) {
                        _one->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                    } else {
                        _one->_municoes[x]->setCor(Qt::white);        // some munição
                    }
                    for (int pr = 0; pr < 3; pr++) {
                        _one->_projeteis[pr]->setDx(5.f);
                        _one->_projeteis[pr]->setDy(5.f);
                        _one->_projeteis[pr]->setCor(Qt::red);
                        _one->_projeteis[pr]->setExisteProjetil(true);
                        _one->_projeteis[pr]->setDirecao(_ultima_direcao_proj_one); // direita
                        if (_ultima_direcao_proj_one == 'c' || _ultima_direcao_proj_one == 'b') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[pr]->setAltura((_one->getDimensao() / 3));
                            _one->_projeteis[pr]->setLargura((_one->getDimensao() / 8));
                            float pos_x = (_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[pr]->getLargura() / 2));
                            float pos_y = (_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[pr]->getLargura() / 2));
                            if (pr == 0) {
                                pos_x -= (_one->getDimensao() + 5);
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 1) {
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 2) {
                                pos_x += (_one->getDimensao() + 5);
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }

                        }
                        if (_ultima_direcao_proj_one == 'e' || _ultima_direcao_proj_one == 'd') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[pr]->setAltura((_one->getDimensao() / 8));
                            _one->_projeteis[pr]->setLargura((_one->getDimensao() / 3));
                            float pos_x = (_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[pr]->getLargura() / 2));
                            float pos_y = (_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[pr]->getLargura() / 2));
                            if (pr == 0) {
                                pos_y -= (_one->getDimensao() + 5);
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 1) {
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 2) {
                                pos_y += (_one->getDimensao() + 5);
                                _one->_projeteis[pr]->setX(pos_x);
                                _one->_projeteis[pr]->setY(pos_y);
                            }
                        }
                    }
                    if (_som_tiro_one1->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_one1->play();
                    } else if (_som_tiro_one2->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_one2->play();
                    } else if (_som_tiro_one3->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_one3->play();
                    } else if (_som_tiro_one4->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_one4->play();
                    } else {
                        _som_tiro_one5->play();
                    }
                    break;
                }
            }
            if (!especial_triplo) {
                /* verifico se existe munições especiais */
                for (int x = 0; x < 5; x++) {
                    /* especial laser */
                    if (_one->_municoes[x]->getCor() == Qt::red) {
                        especial = true;
                        if (x == 4) {
                            _one->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                        } else {
                            _one->_municoes[x]->setCor(Qt::white);        // some munição
                        }
                        _one->_projeteis[x]->setDx(5.f);
                        _one->_projeteis[x]->setDy(5.f);
                        _one->_projeteis[x]->setCor(Qt::red);
                        _one->_projeteis[x]->setExisteProjetil(true); // o mesmo projetil passa a existir

                        _one->_projeteis[x]->setDirecao(_ultima_direcao_proj_one); // direita
                        if (_ultima_direcao_proj_one == 'c' || _ultima_direcao_proj_one == 'b') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[x]->setAltura((_one->getDimensao() / 3));
                            _one->_projeteis[x]->setLargura((_one->getDimensao() / 8));
                            _one->_projeteis[x]->setX((_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getLargura() / 2)));
                            _one->_projeteis[x]->setY((_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getLargura() / 2)));
                        }
                        if (_ultima_direcao_proj_one == 'e' || _ultima_direcao_proj_one == 'd') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[x]->setAltura((_one->getDimensao() / 8));
                            _one->_projeteis[x]->setLargura((_one->getDimensao() / 3));
                            _one->_projeteis[x]->setX((_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getAltura() / 2)));
                            _one->_projeteis[x]->setY((_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getAltura() / 2)));
                        }
                        if (_som_tiro_one1->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one1->play();
                        } else if (_som_tiro_one2->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one2->play();
                        } else if (_som_tiro_one3->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one3->play();
                        } else if (_som_tiro_one4->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one4->play();
                        } else {
                            _som_tiro_one5->play();
                        }
                        break;
                    }
                }
            }
            if (!especial && !especial_triplo) {
                for (int x = 0; x < 5; x++) {
                    /* normal */
                    if (_one->_municoes[x]->getCor() == Qt::black) {  // existe
                        if (x == 4) {
                            _one->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                        } else {
                            _one->_municoes[x]->setCor(Qt::white);        // some munição
                        }
                        _one->_projeteis[x]->setCor(Qt::white);
                        _one->_projeteis[x]->setExisteProjetil(true); // o mesmo projetil passa a existir

                        _one->_projeteis[x]->setDirecao(_ultima_direcao_proj_one); // direita
                        if (_ultima_direcao_proj_one == 'c' || _ultima_direcao_proj_one == 'b') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[x]->setAltura((_one->getDimensao() / 3));
                            _one->_projeteis[x]->setLargura((_one->getDimensao() / 8));
                            _one->_projeteis[x]->setX((_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getLargura() / 2)));
                            _one->_projeteis[x]->setY((_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getLargura() / 2)));
                        }
                        if (_ultima_direcao_proj_one == 'e' || _ultima_direcao_proj_one == 'd') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _one->_projeteis[x]->setAltura((_one->getDimensao() / 8));
                            _one->_projeteis[x]->setLargura((_one->getDimensao() / 3));
                            _one->_projeteis[x]->setX((_one->getX() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getAltura() / 2)));
                            _one->_projeteis[x]->setY((_one->getY() + (_one->getDimensao() / 2) - (_one->_projeteis[x]->getAltura() / 2)));
                        }
                        if (_som_tiro_one1->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one1->play();
                        } else if (_som_tiro_one2->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one2->play();
                        } else if (_som_tiro_one3->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one3->play();
                        } else if (_som_tiro_one4->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_one4->play();
                        } else {
                            _som_tiro_one5->play();
                        }
                        break;
                    }
                }
            }
        }


        /* teclas mov player 2 */
        if (_c_two && _e_two) {
            _two->setDx(-2);
            _two->setDy(-1);
        } else if (_c_two && _d_two) {
            _two->setDx(2);
            _two->setDy(-1);
        } else if (_b_two && _e_two) {
            _two->setDx(-2);
            _two->setDy(1);
        } else if (_b_two && _d_two) {
            _two->setDx(2);
            _two->setDy(1);
        } else if (_c_two) {
            _two->setDx(0);
            _two->setDy(-2);
            _ultima_direcao_proj_two = 'c';
        } else if (_b_two) {
            _two->setDx(0);
            _two->setDy(2);
            _ultima_direcao_proj_two = 'b';
        } else if (_e_two) {
            _two->setDx(-2);
            _two->setDy(0);
            _ultima_direcao_proj_two = 'e';
        } else if (_d_two) {
            _two->setDx(2);
            _two->setDy(0);
            _ultima_direcao_proj_two = 'd';
        } else {
            _two->setDx(0);
            _two->setDy(0);
        }
        /* tecla tiro player 2 */
        if (_t_two) {
            _t_two = false;
            bool especial = false;
            bool especial_triplo = false;
            for (int x = 0; x < 5; x++) {
                /* verifico se existe munição especial p/ tiro triplo */
                if (_two->_municoes[x]->isTriplo()) {
                    especial_triplo = true;
                    _two->_tem_triplo = false;
                    _two->_municoes[x]->setIsTriplo(false);
                    if (x == 4) {
                        _two->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                    } else {
                        _two->_municoes[x]->setCor(Qt::black);        // some munição
                    }
                    for (int pr = 0; pr < 3; pr++) {
                        _two->_projeteis[pr]->setDx(5.f);
                        _two->_projeteis[pr]->setDy(5.f);
                        _two->_projeteis[pr]->setCor(Qt::red);
                        _two->_projeteis[pr]->setExisteProjetil(true);
                        _two->_projeteis[pr]->setDirecao(_ultima_direcao_proj_two); // direita
                        if (_ultima_direcao_proj_two == 'c' || _ultima_direcao_proj_two == 'b') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _two->_projeteis[pr]->setAltura((_two->getDimensao() / 3));
                            _two->_projeteis[pr]->setLargura((_two->getDimensao() / 8));
                            float pos_x = (_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[pr]->getLargura() / 2));
                            float pos_y = (_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[pr]->getLargura() / 2));
                            if (pr == 0) {
                                pos_x -= (_two->getDimensao() + 5);
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 1) {
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 2) {
                                pos_x += (_one->getDimensao() + 5);
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }

                        }
                        if (_ultima_direcao_proj_two == 'e' || _ultima_direcao_proj_two == 'd') {
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _two->_projeteis[pr]->setAltura((_two->getDimensao() / 8));
                            _two->_projeteis[pr]->setLargura((_two->getDimensao() / 3));
                            float pos_x = (_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[pr]->getLargura() / 2));
                            float pos_y = (_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[pr]->getLargura() / 2));
                            if (pr == 0) {
                                pos_y -= (_two->getDimensao() + 5);
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 1) {
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }
                            if (pr == 2) {
                                pos_y += (_two->getDimensao() + 5);
                                _two->_projeteis[pr]->setX(pos_x);
                                _two->_projeteis[pr]->setY(pos_y);
                            }
                        }
                    }
                    if (_som_tiro_two1->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_two1->play();
                    } else if (_som_tiro_two2->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_two2->play();
                    } else if (_som_tiro_two3->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_two3->play();
                    } else if (_som_tiro_two4->state() != QMediaPlayer::PlayingState) {
                        _som_tiro_two4->play();
                    } else {
                        _som_tiro_two5->play();
                    }
                    break;
                }
            }
            if (!especial_triplo) {
                /* verifico se existe munições especiais */
                for (int x = 0; x < 5; x++) {
                    /* especial laser */
                    if (_two->_municoes[x]->getCor() == Qt::red) {
                        especial = true;
                        if (x == 4) {
                            _two->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                        } else {
                            _two->_municoes[x]->setCor(Qt::black);        // some munição
                        }
                        _two->_projeteis[x]->setDx(5.f);
                        _two->_projeteis[x]->setDy(5.f);
                        _two->_projeteis[x]->setCor(Qt::red);
                        _two->_projeteis[x]->setExisteProjetil(true); // o mesmo projetil passa a existir

                        _two->_projeteis[x]->setDirecao(_ultima_direcao_proj_two); // direita
                        if (_ultima_direcao_proj_two == 'c' || _ultima_direcao_proj_two == 'b') {
                            _two->_projeteis[x]->setAltura((_two->getDimensao() / 3));
                            _two->_projeteis[x]->setLargura((_two->getDimensao() / 8));
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _two->_projeteis[x]->setX((_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getLargura() / 2)));
                            _two->_projeteis[x]->setY((_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getLargura() / 2)));
                        }
                        if (_ultima_direcao_proj_two == 'e' || _ultima_direcao_proj_two == 'd') {
                            _two->_projeteis[x]->setAltura((_two->getDimensao() / 8));
                            _two->_projeteis[x]->setLargura((_two->getDimensao() / 3));
                            /* atualizo posição inicial do projetil e direcao a ser pintado */
                            _two->_projeteis[x]->setX((_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getAltura() / 2)));
                            _two->_projeteis[x]->setY((_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getAltura() / 2)));
                        }
                        if (_som_tiro_two1->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two1->play();
                        } else if (_som_tiro_two2->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two2->play();
                        } else if (_som_tiro_two3->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two3->play();
                        } else if (_som_tiro_two4->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two4->play();
                        } else {
                            _som_tiro_two5->play();
                        }
                        break;
                    }
                }
            }
            if (!especial && !especial_triplo) {
                /* verifico se existe munições */
                for (int x = 0; x < 5; x++) {
                    if (_two->_municoes[x]->getCor() == Qt::white) {  // existe
                        if (x == 4) {
                            _two->_municoes[x]->setCor(Qt::lightGray);    // a altima fica cinza
                        } else {
                            _two->_municoes[x]->setCor(Qt::black);        // some munição
                        }
                        _two->_projeteis[x]->setCor(Qt::black);
                        _two->_projeteis[x]->setExisteProjetil(true); // o mesmo projetil passa a existir
                        _two->_projeteis[x]->setDirecao(_ultima_direcao_proj_two); // direita
                        if (_ultima_direcao_proj_two == 'c' || _ultima_direcao_proj_two == 'b') {
                            _two->_projeteis[x]->setAltura((_one->getDimensao() / 3));
                            _two->_projeteis[x]->setLargura((_one->getDimensao() / 8));
                            _two->_projeteis[x]->setX((_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getLargura() / 2)));
                            _two->_projeteis[x]->setY((_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getLargura() / 2)));
                        }
                        if (_ultima_direcao_proj_two == 'e' || _ultima_direcao_proj_two == 'd') {
                            _two->_projeteis[x]->setAltura((_two->getDimensao() / 8));
                            _two->_projeteis[x]->setLargura((_two->getDimensao() / 3));
                            _two->_projeteis[x]->setX((_two->getX() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getAltura() / 2)));
                            _two->_projeteis[x]->setY((_two->getY() + (_two->getDimensao() / 2) - (_two->_projeteis[x]->getAltura() / 2)));
                        }
                        if (_som_tiro_two1->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two1->play();
                        } else if (_som_tiro_two2->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two2->play();
                        } else if (_som_tiro_two3->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two3->play();
                        } else if (_som_tiro_two4->state() != QMediaPlayer::PlayingState) {
                            _som_tiro_two4->play();
                        } else {
                            _som_tiro_two5->play();
                        }
                        break;
                    }
                }
            }
        }

        /* aguardo o tempo de atualização necessário para atualizar as variáveis */
        while (_time_acumulado >= _constant_dt) {
             /* movo os objetos sempre depois de fazer as verificações nos eventos do teclado */
             _one->movePlayer(_constant_dt);
             _two->movePlayer(_constant_dt);

             /* posso utilizar o mesmo laço p/ verificar pros dois players */
             for (int x = 0; x < 8; x++) {
                 if (_one->_projeteis[x]->existeProjetil()) {
                     _one->_projeteis[x]->moveProjetil(_constant_dt);
                 }
                 if (_two->_projeteis[x]->existeProjetil()) {
                     _two->_projeteis[x]->moveProjetil(_constant_dt);
                 }
             }
             /* atualizo munições do player */
             _one->moveMunicoes();
             _two->moveMunicoes();
             /* após atualizar sempre diminuo do acumulado */
             _time_acumulado -= _constant_dt;

             /* colisões */
             for (int x = 0; x < _pecas.size(); x++) {
                 /* player 1 <> peças */
                 _one->checkColisao(_pecas[x], _w_tab, _h_tab, _constant_dt);
                 /* player 2 <> peças */
                 _two->checkColisao(_pecas[x], _w_tab, _h_tab, _constant_dt);

                 /* players com munições especiais */
                 for (int z = 0; z < 4; z++) {
                     if (_one->checkColisao(_municoes_especiais[z])) {
                         /* pinto de red (tras p/ frente) */
                         for (int mu = 4; mu >= 0; mu--) {
                             if (_one->_municoes[mu]->getCor() != Qt::red && _one->_municoes[mu]->getCor() != Qt::black
                                     && !_one->_municoes[mu]->isTriplo()) {
                                 _one->_municoes[mu]->setCor(Qt::red);
                                 _municoes_especiais[z]->setCor(Qt::transparent);
                                 break;
                             }
                             if (mu == 0 && !_one->_municoes[mu]->isTriplo()) {
                                 if (_one->_municoes[mu]->getCor() == Qt::black) {
                                     _one->_municoes[mu]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_one->_municoes[mu + 1]->getCor() == Qt::black) {
                                     _one->_municoes[mu + 1]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_one->_municoes[mu + 2]->getCor() == Qt::black) {
                                     _one->_municoes[mu + 2]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_one->_municoes[mu + 3]->getCor() == Qt::black) {
                                     _one->_municoes[mu + 3]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 }
                             }
                         }
                     }
                     if (_two->checkColisao(_municoes_especiais[z])) {
                         /* pinto de red (tras p/ frente) */
                         for (int mu = 4; mu >= 0; mu--) {
                             if (_two->_municoes[mu]->getCor() != Qt::red && _two->_municoes[mu]->getCor() != Qt::white
                                     && !_two->_municoes[mu]->isTriplo()) {
                                 _two->_municoes[mu]->setCor(Qt::red);
                                 _municoes_especiais[z]->setCor(Qt::transparent);
                                 break;
                             }
                             if (mu == 0 && !_two->_municoes[mu]->isTriplo()) {
                                 if (_two->_municoes[mu]->getCor() == Qt::white) {
                                     _two->_municoes[mu]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_two->_municoes[mu + 1]->getCor() == Qt::white) {
                                     _two->_municoes[mu + 1]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_two->_municoes[mu + 2]->getCor() == Qt::white) {
                                     _two->_municoes[mu + 2]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 } else if (_two->_municoes[mu + 3]->getCor() == Qt::white) {
                                     _two->_municoes[mu + 3]->setCor(Qt::red);
                                     _municoes_especiais[z]->setCor(Qt::transparent);
                                 }
                             }
                         }
                     }
                 }
                 /* projetil <> peças
                  * projetil <> players
                  * projetil <> projetil
                  * projetil <> munições tab */
                 for (int y = 0; y < 8; y++) {
                     if (_one->_projeteis[y]->existeProjetil()) {
                         /* primeira coisa verifico se ele ainda esta dentro do tabuleiro*/
                         if (_one->_projeteis[y]->getX() >= 0 && _one->_projeteis[y]->getX() <= (_w_tab + _one->_projeteis[y]->getLargura()) && _one->_projeteis[y]->getY() >= 0 && _one->_projeteis[y]->getY() <= (_h_tab + _one->_projeteis[y]->getAltura())) {
                             /* com peça */
                             if (_one->_projeteis[y]->checkColisao(_pecas[x], 0)) {
                                 if (_pecas[x]->_cor == Qt::lightGray) {
                                     _one->_projeteis[y]->setCor(Qt::transparent);
                                     _one->_projeteis[y]->setExisteProjetil(false);
                                     _one->_projeteis[y]->setDx(2.f);
                                     _one->_projeteis[y]->setDy(2.f);
                                 } else {
                                    _pecas[x]->_cor = Qt::black;
                                 }
                             }
                             /* com player */
                             if (_two->checkColisao(_one->_projeteis[y])) {
                                 if (_som_explosao1->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao1->play();
                                 } else if (_som_explosao2->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao2->play();
                                 } else if (_som_explosao3->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao3->play();
                                 } else if (_som_explosao4->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao4->play();
                                 } else {
                                     _som_explosao5->play();
                                 }
                                 _one->_projeteis[y]->setCor(Qt::transparent);
                                 _one->_projeteis[y]->setExisteProjetil(false);
                                 _one->_projeteis[y]->setDx(2.f);
                                 _one->_projeteis[y]->setDy(2.f);
                                 this->restart(0); // player 1 definido como 0
                             }
                             /* projetil com munição especial e player */
                             for (int z = 0; z < 4; z++) {
                                 if (_municoes_especiais[z]->getCor() == Qt::red) {
                                     if (_one->_projeteis[y]->checkColisao(_municoes_especiais[z])) {
                                         /* pinto peças ao redor da munição (da cor oposta a do projetil) */
                                         this->pintaPecaAoColitarMunicao(_one->_projeteis[y], z, 0);
                                         _one->_projeteis[y]->setCor(Qt::transparent);
                                         _one->_projeteis[y]->setExisteProjetil(false);
                                         _one->_projeteis[y]->setDx(2.f);
                                         _one->_projeteis[y]->setDy(2.f);
                                         _municoes_especiais[z]->setCor(Qt::transparent);
                                         if (_som_explosao1->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao1->play();
                                         } else if (_som_explosao2->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao2->play();
                                         } else if (_som_explosao3->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao3->play();
                                         } else if (_som_explosao4->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao4->play();
                                         } else {
                                             _som_explosao5->play();
                                         }
                                     }
                                 }
                             }

                             /* com projetil do adversário aqui ja mato pros dois players */
                             for (int z = 0; z < 8; z++) {
                                if (_two->_projeteis[z]->existeProjetil()) {
                                    if (_one->checkColisaoProjeteis(_two->_projeteis[z], y)) {
                                        _one->_projeteis[y]->setCor(Qt::transparent);
                                        _one->_projeteis[y]->setExisteProjetil(false);
                                        _one->_projeteis[y]->setDx(2.f);
                                        _one->_projeteis[y]->setDy(2.f);
                                        _two->_projeteis[z]->setCor(Qt::transparent);
                                        _two->_projeteis[z]->setExisteProjetil(false);
                                        _two->_projeteis[y]->setDx(2.f);
                                        _two->_projeteis[y]->setDy(2.f);
                                        if (_som_explosao1->state() != QMediaPlayer::PlayingState) {
                                            _som_explosao1->play();
                                        } else if (_som_explosao2->state() != QMediaPlayer::PlayingState) {
                                            _som_explosao2->play();
                                        } else if (_som_explosao3->state() != QMediaPlayer::PlayingState) {
                                            _som_explosao3->play();
                                        } else if (_som_explosao4->state() != QMediaPlayer::PlayingState) {
                                            _som_explosao4->play();
                                        } else {
                                            _som_explosao5->play();
                                        }
                                    }
                                }
                             }
                         } else {
                             _one->_projeteis[y]->setCor(Qt::transparent);
                             _one->_projeteis[y]->setExisteProjetil(false);
                             _one->_projeteis[y]->setDx(2.f);
                             _one->_projeteis[y]->setDy(2.f);
                         }
                     }
                     if (_two->_projeteis[y]->existeProjetil()) {
                          if (_two->_projeteis[y]->getX() >= 0 && _two->_projeteis[y]->getX() <= (_w_tab + _two->_projeteis[y]->getLargura()) && _two->_projeteis[y]->getY() >= 0 && _two->_projeteis[y]->getY() <= (_h_tab + _two->_projeteis[y]->getAltura())) {
                             if (_two->_projeteis[y]->checkColisao(_pecas[x], 1)) {
                                 if (_pecas[x]->_cor == Qt::lightGray) {
                                     _two->_projeteis[y]->setCor(Qt::transparent);
                                     _two->_projeteis[y]->setExisteProjetil(false);
                                     _two->_projeteis[y]->setDx(2.f);
                                     _two->_projeteis[y]->setDy(2.f);
                                 } else {
                                    _pecas[x]->_cor = Qt::white;
                                 }
                             }
                             if (_one->checkColisao(_two->_projeteis[y])) {
                                 if (_som_explosao1->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao1->play();
                                 } else if (_som_explosao2->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao2->play();
                                 } else if (_som_explosao3->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao3->play();
                                 } else if (_som_explosao4->state() != QMediaPlayer::PlayingState) {
                                     _som_explosao4->play();
                                 } else {
                                     _som_explosao5->play();
                                 }
                                 _two->_projeteis[y]->setCor(Qt::transparent);
                                 _two->_projeteis[y]->setExisteProjetil(false);
                                 _two->_projeteis[y]->setDx(2.f);
                                 _two->_projeteis[y]->setDy(2.f);
                                 this->restart(1); // player 2 definido como 1
                             }
                             /* projetil com munição especial */
                             for (int z = 0; z < 4; z++) {
                                 if (_municoes_especiais[z]->getCor() == Qt::red) {
                                     if (_two->_projeteis[y]->checkColisao(_municoes_especiais[z])) {
                                         /* pinto peças ao redor da munição (da cor oposta a do projetil) */
                                         this->pintaPecaAoColitarMunicao(_two->_projeteis[y], z, 1);
                                         _two->_projeteis[y]->setCor(Qt::transparent);
                                         _two->_projeteis[y]->setExisteProjetil(false);
                                         _two->_projeteis[y]->setDx(2.f);
                                         _two->_projeteis[y]->setDy(2.f);
                                         _municoes_especiais[z]->setCor(Qt::transparent);
                                         if (_som_explosao1->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao1->play();
                                         } else if (_som_explosao2->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao2->play();
                                         } else if (_som_explosao3->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao3->play();
                                         } else if (_som_explosao4->state() != QMediaPlayer::PlayingState) {
                                             _som_explosao4->play();
                                         } else {
                                             _som_explosao5->play();
                                         }
                                     }
                                 }
                             }
                         } else {
                             _two->_projeteis[y]->setCor(Qt::transparent);
                             _two->_projeteis[y]->setExisteProjetil(false);
                             _two->_projeteis[y]->setDx(2.f);
                             _two->_projeteis[y]->setDy(2.f);
                         }
                     }
                 }
             }
        }
    }
    /* desenho os objetos */
    this->drawTabuleiro();
    /* atualizo variavel que armazena tempo da ultima invocação do método */
    _time_final = time_inicial;

    /* reseto temporizador */
    QTimer::singleShot(1000 / _max_fps, this, SLOT(temporizador()));
}

void Tabuleiro::setTipo(int tipo) {
    _tipo = tipo;
}

void Tabuleiro::setAltura(float h) {
    _h_tab = h;
}

void Tabuleiro::setLargura(float w) {
    _w_tab = w;
}

/**
 * Reestarta jogo no mesmo mapa quando um player acerta o outro
 * @brief Tabuleiro::restart
 * @param player
 */
void Tabuleiro::restart(int playerVencedor) {
    if (playerVencedor == 0) {
        /* pinto todas as peças de preto einicio o jogo no mesmo mapa */
        for (int x = 0; x < _pecas.size(); x++) {
            _pecas[x]->_cor = Qt::black;

        }
        //_two->~Player();
        _som_fundo->stop();
        _visualiza_menu = true;
        _tipo = -1;
    }
    if (playerVencedor == 1) {
        /* pinto todas as peças de branco e inicio o jogo no mesmo mapa */
        for (int x = 0; x < _pecas.size(); x++) {
            _pecas[x]->_cor = Qt::white;
        }
        //_two->~Player();
        _som_fundo->stop();
        _visualiza_menu = true;
        _tipo = -1;
    }
}

/**
 * Adiciona os objetos munições para serem pintados posteriormente no tabuleiro (inicialmente invisíveis)
 * Invocado dentro do resize p/ atualizar redimensionamento proporcional a peça do tabuleiro
 * @brief Tabuleiro::addMunicoes
 */
void Tabuleiro::addMunicoes() {
    float dim = _one->getDimensao() / 4.5;
    /* pode no máximo 4 munições ao mesmo tempo, adiciono na lista apenas 4 */
    if (_municoes_especiais.empty()) {
        for (int x = 0; x < 4; x++) {
            int peca;
            if (x == 0)
                peca = 53;
            if (x == 1)
                peca = 69;
            if (x == 2)
                peca = 267;
            if (x == 3)
                peca = 252;
            /* seto as posições das munições baseadas nas peças (fixas) */
            float pos_x = ((_pecas[peca]->getX() + (_pecas[peca]->getLargura() / 2)) - (dim / 2));
            float pos_y = ((_pecas[peca]->getY() + (_pecas[peca]->getAltura() / 2)) - (dim / 2));
            if (_municoes_especiais.empty() || _municoes_especiais.size() <= 4) {
                _municoes_especiais.append(new Municao((QFrame*)this, Qt::transparent, pos_x, pos_y, dim));
                continue;
            }
        }
        _municoes_especiais[0]->setIsEspecialTabuleiro(true);
        _municoes_especiais[1]->setIsEspecialTabuleiro(true);
        _municoes_especiais[2]->setIsEspecialTabuleiro(true);
        _municoes_especiais[3]->setIsEspecialTabuleiro(true);
    } else {
        for (int x = 0; x < 4; x++) {
            int peca;
            if (x == 0)
                peca = 53;
            if (x == 1)
                peca = 69;
            if (x == 2)
                peca = 267;
            if (x == 3)
                peca = 252;
            /* seto as posições das munições baseadas nas peças (fixas) */
            float pos_x = ((_pecas[peca]->getX() + (_pecas[peca]->getLargura() / 2)) - (dim / 2));
            float pos_y = ((_pecas[peca]->getY() + (_pecas[peca]->getAltura() / 2)) - (dim / 2));
            /* se as munições ja existem apenas atualizo suas posições */
            _municoes_especiais[x]->setWH(dim);
            _municoes_especiais[x]->setX(pos_x);
            _municoes_especiais[x]->setY(pos_y);
        }
    }
}

void Tabuleiro::pintaPecaAoColitarMunicao(Projetil *p, int pos, int player) {
    int peca = _pos_peca_mun_especial[pos];
    if (peca != NULL) {
        if (player == 0) {
            _pecas[peca]->_cor = Qt::black;
            if (_pecas[peca - 1]->getCor() != Qt::lightGray) {
                _pecas[peca - 1]->_cor = Qt::black;
            }
            if (_pecas[peca + 1]->getCor() != Qt::lightGray) {
                _pecas[peca + 1]->_cor = Qt::black;
            }
            if (_pecas[peca - 25]->getCor() != Qt::lightGray) {
                _pecas[peca - 25]->_cor = Qt::black;
            }
            if (_pecas[peca - 24]->getCor() != Qt::lightGray) {
                _pecas[peca - 24]->_cor = Qt::black;
            }
            if (_pecas[peca - 23]->getCor() != Qt::lightGray) {
                _pecas[peca - 23]->_cor = Qt::black;
            }
            if (_pecas[peca + 25]->getCor() != Qt::lightGray) {
                _pecas[peca + 25]->_cor = Qt::black;
            }
            if (_pecas[peca + 24]->getCor() != Qt::lightGray) {
                _pecas[peca + 24]->_cor = Qt::black;
            }
            if (_pecas[peca + 23]->getCor() != Qt::lightGray) {
                _pecas[peca + 23]->_cor = Qt::black;
            }
        }
        if (player == 1) {
            _pecas[peca]->_cor = Qt::white;
            if (_pecas[peca - 1]->getCor() != Qt::lightGray) {
                _pecas[peca - 1]->_cor = Qt::white;
            }
            if (_pecas[peca + 1]->getCor() != Qt::lightGray) {
                _pecas[peca + 1]->_cor = Qt::white;
            }
            if (_pecas[peca - 25]->getCor() != Qt::lightGray) {
                _pecas[peca - 25]->_cor = Qt::white;
            }
            if (_pecas[peca - 24]->getCor() != Qt::lightGray) {
                _pecas[peca - 24]->_cor = Qt::white;
            }
            if (_pecas[peca - 23]->getCor() != Qt::lightGray) {
                _pecas[peca - 23]->_cor = Qt::white;
            }
            if (_pecas[peca + 25]->getCor() != Qt::lightGray) {
                _pecas[peca + 25]->_cor = Qt::white;
            }
            if (_pecas[peca + 24]->getCor() != Qt::lightGray) {
                _pecas[peca + 24]->_cor = Qt::white;
            }
            if (_pecas[peca + 23]->getCor() != Qt::lightGray) {
                _pecas[peca + 23]->_cor = Qt::white;
            }
        }
    }

}



