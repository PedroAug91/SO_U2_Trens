#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);

        // Cria o trem com seu (ID, posição X, posição Y)
        trem_a = new Trem(1, 420, 140);
        trem_b = new Trem(2, 150, 330);
        trem_c = new Trem(3, 690, 330);
        trem_d = new Trem(4, 20, 460);
        trem_e = new Trem(5, 420, 530);
        trem_f = new Trem(6, 830, 460);
        Trem *trens[6] = {trem_a, trem_b, trem_c, trem_d, trem_e, trem_f};

        this->ui->slider_a->connect(this->ui->slider_a,
                                    SIGNAL(valueChanged(int)), this->trem_a,
                                    SLOT(updateSpeed(int)));
        this->ui->slider_b->connect(this->ui->slider_b,
                                    SIGNAL(valueChanged(int)), this->trem_b,
                                    SLOT(updateSpeed(int)));
        this->ui->slider_c->connect(this->ui->slider_c,
                                    SIGNAL(valueChanged(int)), this->trem_c,
                                    SLOT(updateSpeed(int)));
        this->ui->slider_d->connect(this->ui->slider_d,
                                    SIGNAL(valueChanged(int)), this->trem_d,
                                    SLOT(updateSpeed(int)));
        this->ui->slider_e->connect(this->ui->slider_e,
                                    SIGNAL(valueChanged(int)), this->trem_e,
                                    SLOT(updateSpeed(int)));
        this->ui->slider_f->connect(this->ui->slider_f,
                                    SIGNAL(valueChanged(int)), this->trem_f,
                                    SLOT(updateSpeed(int)));


        /*
         * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
         * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a
         * função UPDATEINTERFACE. Os 3 parâmetros INT do sinal serão utilizados
         * na função. Trem1 e Trem2 são os objetos que podem chamar o sinal. Se
         * um outro objeto chamar o sinal UPDATEGUI, não haverá execução da
         * função UPDATEINTERFACE
         */
        this->connect(this->trem_a, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));
        this->connect(this->trem_b, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));
        this->connect(this->trem_c, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));
        this->connect(this->trem_d, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));
        this->connect(this->trem_e, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));
        this->connect(this->trem_f, SIGNAL(updateGUI(int, int, int)),
                      SLOT(updateInterface(int, int, int)));

        for (auto trem : trens) {
                trem->start();
        }
}

// Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y) {
        switch (id) {
        case 1:
                ui->label_trem_a->setGeometry(x, y, 20, 20);
                break;
        case 2:
                ui->label_trem_b->setGeometry(x, y, 20, 20);
                break;
        case 3:
                ui->label_trem_c->setGeometry(x, y, 20, 20);
                break;
        case 4:
                ui->label_trem_d->setGeometry(x, y, 20, 20);
                break;
        case 5:
                ui->label_trem_e->setGeometry(x, y, 20, 20);
                break;
        case 6:
                ui->label_trem_f->setGeometry(x, y, 20, 20);
                break;
        default:
                break;
        }
}

MainWindow::~MainWindow() { delete ui; }
