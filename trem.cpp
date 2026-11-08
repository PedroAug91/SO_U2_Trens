#include "trem.h"
#include <QtCore>

// Recursos compartilhados pela malha. Definidos uma única vez aqui; todas as
// threads Trem usam os mesmos nove mutexes.
QMutex Trem::mutex_trilho_3;
QMutex Trem::mutex_trilho_4;
QMutex Trem::mutex_trilho_8;
QMutex Trem::mutex_trilho_7_esq;
QMutex Trem::mutex_trilho_7_dir;
QMutex Trem::mutex_trilho_9_esq;
QMutex Trem::mutex_trilho_9_dir;
QMutex Trem::mutex_trilho_14;
QMutex Trem::mutex_trilho_16;

// Construtor
Trem::Trem(int ID, int x, int y) {
        this->ID = ID;
        this->x = x;
        this->y = y;
        this->velocidade = 100;
}

void Trem::updateSpeed(int vel) {
        if (vel < 0) {
                this->velocidade = 0;
                return;
        } else if (vel > 200) {
                this->velocidade = 200;
                return;
        }
        this->velocidade = vel;
}

// Função a ser executada após executar trem->START
void Trem::run() {
        while (true) {
                if (velocidade == 0) {
                        msleep(50);
                        continue;
                }

                switch (ID) {
                case 1: // Trem 1 (trem_label_a)
                        // Região 1 (trilho_3, com b), rank 4. Para 40 px antes
                        // do trilho: o rótulo tem 20 px e sobra folga visual.
                        if (x == 150 && y == 230)
                                mutex_trilho_3.lock();
                        // Região 2 (trilho_4, com c), rank 5.
                        if (x == 380 && y == 270)
                                mutex_trilho_4.lock();

                        if (y == 140 && x > 150)
                                x -= 10;
                        else if (x == 150 && y < 270)
                                y += 10;
                        else if (x < 690 && y == 270)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 1; só libera 6 células depois, para o
                        // trem que esperava não colidir com a "cauda".
                        if (x == 480 && y == 270)
                                mutex_trilho_3.unlock();
                        // Saiu da região 2; idem, 6 células de folga.
                        if (x == 690 && y == 210)
                                mutex_trilho_4.unlock();
                        break;
                case 2: // Trem 2 (trem_label_b)
                        // Região 4 (trilho_7_esq, com d), rank 0.
                        if (x == 150 && y == 360)
                                mutex_trilho_7_esq.lock();
                        // Região 5 (trilho_7_dir, com e), rank 2.
                        if (x == 250 && y == 400)
                                mutex_trilho_7_dir.lock();
                        // Região 3 (trilho_8, com c), rank 3.
                        if (x == 380 && y == 400)
                                mutex_trilho_8.lock();
                        // Região 1 (trilho_3, com a), rank 4. b já segura a
                        // região 3 e a adquire descendo a vertical, 40 px
                        // antes do cruzamento: é o menor adiantamento possível
                        // sem inverter a ordem global.
                        if (x == 420 && y == 310)
                                mutex_trilho_3.lock();

                        if (y == 270 && x > 150)
                                x -= 10;
                        else if (x == 150 && y < 400)
                                y += 10;
                        else if (x < 420 && y == 400)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 4; 6 células de folga.
                        if (x == 350 && y == 400)
                                mutex_trilho_7_esq.unlock();
                        // Saiu da região 5 (já subindo a vertical); 6 células.
                        if (x == 420 && y == 340)
                                mutex_trilho_7_dir.unlock();
                        // Saiu da região 3 e já está na horizontal; 6 células.
                        if (x == 360 && y == 270)
                                mutex_trilho_8.unlock();
                        // Saiu da região 1; idem, 6 células de folga.
                        // 330 é a posição inicial de b: no primeiro ciclo a
                        // condição só dispara depois de mover, então não há
                        // unlock de mutex não adquirido.
                        if (x == 150 && y == 330)
                                mutex_trilho_3.unlock();
                        break;
                case 3: // Trem 3 (trem_label_c)
                        // Regiões 3 e 2 no mesmo ponto, na ordem global
                        // 3 < 2: c pega trilho_8 antes de trilho_4 para não
                        // fechar o ciclo b -> c -> a.
                        if (x == 690 && y == 310) {
                                mutex_trilho_8.lock(); // região 3, rank 3
                                mutex_trilho_4.lock(); // região 2, rank 5
                        }
                        // Região 6 (trilho_9_esq, com e), rank 6.
                        if (x == 420 && y == 360)
                                mutex_trilho_9_esq.lock();
                        // Região 7 (trilho_9_dir, com f), rank 7.
                        if (x == 520 && y == 400)
                                mutex_trilho_9_dir.lock();

                        if (y == 270 && x > 420)
                                x -= 10;
                        else if (x == 420 && y < 400)
                                y += 10;
                        else if (x < 690 && y == 400)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 2 e continua descendo a região 3.
                        if (x == 420 && y == 330)
                                mutex_trilho_4.unlock();
                        // Saiu da região 3; 6 células de folga.
                        if (x == 480 && y == 400)
                                mutex_trilho_8.unlock();
                        // Saiu da região 6; 6 células de folga.
                        if (x == 620 && y == 400)
                                mutex_trilho_9_esq.unlock();
                        // Saiu da região 7 e já subiu a vertical; 6 células.
                        if (x == 690 && y == 340)
                                mutex_trilho_9_dir.unlock();
                        break;
                case 4: // Trem 4 (trem_label_d)
                        // Regiões 4 e 8 no mesmo ponto, na ordem global
                        // 4 < 8: d reserva trilho_7_esq antes de começar a
                        // subir a vertical, que é a região 8.
                        if (x == 250 && y == 530) {
                                mutex_trilho_7_esq.lock(); // região 4, rank 0
                                mutex_trilho_14.lock();    // região 8, rank 8
                        }

                        if (y == 400 && x > 20)
                                x -= 10;
                        else if (x == 20 && y < 530)
                                y += 10;
                        else if (x < 290 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 8; 6 células de folga.
                        if (x == 230 && y == 400)
                                mutex_trilho_14.unlock();
                        // Saiu da região 4; idem, 6 células de folga.
                        if (x == 90 && y == 400)
                                mutex_trilho_7_esq.unlock();
                        break;
                case 5: // Trem 5 (trem_label_e)
                        // Região 9 (trilho_16, com f), rank 1.
                        if (x == 520 && y == 530)
                                mutex_trilho_16.lock();
                        // Regiões 5 e 6 no mesmo ponto, na ordem global
                        // 5 < 6: e reserva trilho_7_dir antes de trilho_9_esq.
                        if (x == 560 && y == 440) {
                                mutex_trilho_7_dir.lock(); // região 5, rank 2
                                mutex_trilho_9_esq.lock(); // região 6, rank 6
                        }
                        // Região 8 (trilho_14, com d), rank 8.
                        if (x == 330 && y == 400)
                                mutex_trilho_14.lock();

                        if (y == 400 && x > 290)
                                x -= 10;
                        else if (x == 290 && y < 530)
                                y += 10;
                        else if (x < 560 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 9; 6 células de folga.
                        if (x == 500 && y == 400)
                                mutex_trilho_16.unlock();
                        // Saiu da região 6; 6 células de folga.
                        if (x == 360 && y == 400)
                                mutex_trilho_9_esq.unlock();
                        // Saiu da região 5 descendo a vertical; 6 células.
                        if (x == 290 && y == 460)
                                mutex_trilho_7_dir.unlock();
                        // Saiu da região 8; idem, 6 células de folga.
                        if (x == 350 && y == 530)
                                mutex_trilho_14.unlock();
                        break;
                case 6: // Trem 6 (trem_label_f)
                        // Regiões 9 e 7 no mesmo ponto, na ordem global
                        // 9 < 7: f reserva trilho_16 antes de trilho_9_dir.
                        if (x == 730 && y == 400) {
                                mutex_trilho_16.lock();    // região 9, rank 1
                                mutex_trilho_9_dir.lock(); // região 7, rank 7
                        }

                        if (y == 400 && x > 560)
                                x -= 10;
                        else if (x == 560 && y < 530)
                                y += 10;
                        else if (x < 830 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal

                        // Saiu da região 7 descendo a vertical; 6 células.
                        if (x == 560 && y == 460)
                                mutex_trilho_9_dir.unlock();
                        // Saiu da região 9; idem, 6 células de folga.
                        if (x == 620 && y == 530)
                                mutex_trilho_16.unlock();
                        break;
                default:
                        break;
                }

                int delay = qMax(1, 200 - velocidade);
                msleep(delay);
        }
}
