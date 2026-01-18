#ifndef JUGADOR_H
#define JUGADOR_H
#pragma once
#include <QString>
class Jugador {
public:
    QString nombre;
    int edad;
    QString posicion;
    int numeroCamiseta;
    int goles;

    Jugador()
        : edad(0), numeroCamiseta(0), goles(0) {}

    Jugador(const QString& n, int e, const QString& p, int num, int g)
        : nombre(n), edad(e), posicion(p), numeroCamiseta(num), goles(g) {}
};

#endif // JUGADOR_H
