#ifndef TREM_H
#define TREM_H

#include <QMutex>
#include <QThread>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar
 * a função RUN. Para parar a execução da função RUN da thread, basta executar a
 * função TERMINATE.
 *
 */
class Trem : public QThread {
        Q_OBJECT
      public:
        Trem(int, int, int); // construtor
        void run();          // função a ser executada pela thread

        // Cria um sinal
      signals:
        void updateGUI(int, int, int);
      public slots:
        void updateSpeed(int);

      private:
        int x;          // posição X do trem na tela
        int y;          // posição Y do trem na tela
        int ID;         // ID do trem
        int velocidade; // Velocidade. É o tempo de dormir em milisegundos entre
                        // a mudança de posição do trem

        // Nove regiões críticas, uma para cada par de trens que divide um
        // trecho de trilho (Figura 2 do enunciado). static: o recurso é da
        // malha, não de um trem; as seis instâncias compartilham o objeto.
        //
        // Ordem global de aquisição (rank crescente), idêntica em todas as
        // threads:
        //     região 4 < 9 < 5 < 3 < 1 < 2 < 6 < 7 < 8
        // Cada trem só adquire um mutex de rank maior do que todos os que já
        // segura e só espera, portanto, por um rank maior. Como a espera é
        // sempre "para cima", não existe ciclo de espera: é o argumento de
        // hierarquia de recursos (OSTEP, cap. 32).
        //
        // Mapa região -> trilho da interface:
        //   1: a,b  trilho_3       6: c,e  trilho_9_esq
        //   2: a,c  trilho_4       7: c,f  trilho_9_dir
        //   3: b,c  trilho_8       8: d,e  trilho_14
        //   4: b,d  trilho_7_esq   9: e,f  trilho_16
        //   5: b,e  trilho_7_dir
        static QMutex mutex_trilho_3;     // região 1: a/b
        static QMutex mutex_trilho_4;     // região 2: a/c
        static QMutex mutex_trilho_8;     // região 3: b/c
        static QMutex mutex_trilho_7_esq; // região 4: b/d
        static QMutex mutex_trilho_7_dir; // região 5: b/e
        static QMutex mutex_trilho_9_esq; // região 6: c/e
        static QMutex mutex_trilho_9_dir; // região 7: c/f
        static QMutex mutex_trilho_14;    // região 8: d/e
        static QMutex mutex_trilho_16;    // região 9: e/f
};

#endif // TREM_H
