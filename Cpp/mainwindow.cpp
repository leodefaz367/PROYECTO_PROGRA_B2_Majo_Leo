#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QAbstractItemView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_repo("jugadores.txt")

{
    ui->setupUi(this);

    ui ->TableJugadores->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableJugadores->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TableJugadores->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_jugadores = m_repo.loadAll();
    cargarJugadoresEnTabla();

}

void MainWindow::cargarJugadoresEnTabla()
{
    ui->TableJugadores->setRowCount(0);

    for (const Jugador &j : m_jugadores){
        agregarJugadorATabla(j);
    }
}

void MainWindow::agregarJugadorATabla(const Jugador &j)
{
    int fila = ui->TableJugadores->rowCount();

    ui->TableJugadores->insertRow(fila);

    ui->TableJugadores->setItem(fila, 0, new QTableWidgetItem(j.nombre));

    ui->TableJugadores->setItem(fila, 1, new QTableWidgetItem(QString::number(j.edad)));

    ui->TableJugadores->setItem(fila, 2, new QTableWidgetItem(j.posicion));

    ui->TableJugadores->setItem(fila, 3, new QTableWidgetItem(QString::number(j.numeroCamiseta)));

    ui->TableJugadores->setItem(fila, 4, new QTableWidgetItem(QString::number(j.goles)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAgregar_clicked()
{
    QString nombre = ui->txtNombre->text().trimmed();
    QString edadStr = ui->txtEdad->text().trimmed();
    QString pos = ui->txtPosicion->text().trimmed();
    QString numStr = ui->txtCamiseta->text().trimmed();
    QString golesStr = ui->txtGoles->text().trimmed();

    if (nombre.isEmpty()){
        QMessageBox::warning(this, "Dato faltante", "Por favor ingrese el nombre del Jugador");
        return;
    }

    bool okEdad = false, okNum = false, okGoles = false; //Booleano para verificar las conversiones a enteros
    int edad = edadStr.toInt(&okEdad);
    int num = numStr.toInt(&okNum);
    int goles = golesStr.toInt(&okGoles);

    if(!okEdad||!okNum||!okGoles){
        QMessageBox::warning(this, "Datos Invalidos", "Por favor ingrese números enteros (edad,goles,numero)");
        return;
    }

    Jugador j(nombre, edad, pos, num, goles);
    m_jugadores.append(j); //Guarda en la memoria
    m_repo.saveAll(m_jugadores); //Guarda en el txt
    agregarJugadorATabla(j);
    ui->txtNombre->clear();
    ui->txtEdad->clear();
    ui->txtPosicion->clear();
    ui->txtCamiseta->clear();
    ui->txtGoles->clear();
    ui->txtNombre->setFocus();

}

