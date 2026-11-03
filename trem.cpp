#include "trem.h"
#include <QtCore>

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
                        if (y == 140 && x > 150)
                                x -= 10;
                        else if (x == 150 && y < 270)
                                y += 10;
                        else if (x < 690 && y == 270)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                case 2: // Trem 2 (trem_label_b)
                        if (y == 270 && x > 150)
                                x -= 10;
                        else if (x == 150 && y < 400)
                                y += 10;
                        else if (x < 420 && y == 400)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                case 3: // Trem 3 (trem_label_c)
                        if (y == 270 && x > 420)
                                x -= 10;
                        else if (x == 420 && y < 400)
                                y += 10;
                        else if (x < 690 && y == 400)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                case 4: // Trem 4 (trem_label_d)
                        if (y == 400 && x > 20)
                                x -= 10;
                        else if (x == 20 && y < 530)
                                y += 10;
                        else if (x < 290 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                case 5: // Trem 5 (trem_label_e)
                        if (y == 400 && x > 290)
                                x -= 10;
                        else if (x == 290 && y < 530)
                                y += 10;
                        else if (x < 560 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                case 6: // Trem 5 (trem_label_e)
                        if (y == 400 && x > 560)
                                x -= 10;
                        else if (x == 560 && y < 530)
                                y += 10;
                        else if (x < 830 && y == 530)
                                x += 10;
                        else
                                y -= 10;
                        emit updateGUI(ID, x, y); // Emite um sinal
                        break;
                default:
                        break;
                }

                int delay = qMax(1, 200 - velocidade);
                msleep(delay);
        }
}
