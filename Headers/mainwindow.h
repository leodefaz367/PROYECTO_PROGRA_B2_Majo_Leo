#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "jugador.h"
#include "jugadorrepository.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAgregar_clicked();

    void on_btnEditar_clicked();

    void on_btnCargar_clicked();

    void on_btnEliminar_clicked();

    void on_TableJugadores_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    QVector<Jugador> m_jugadores;
    JugadorRepository m_repo;

    void cargarJugadoresEnTabla();
    void agregarJugadorATabla(const Jugador &);

};
#endif // MAINWINDOW_H
