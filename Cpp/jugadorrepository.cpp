#include "jugadorrepository.h"
#include <QFile>
#include <QTextStream>

JugadorRepository::JugadorRepository(const QString& path)
    : filePath(path) {}

QVector<Jugador> JugadorRepository::loadAll() const {
    QVector<Jugador> result;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return result;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split("|");
        if (parts.size() < 5) continue;

        Jugador j;
        j.nombre         = parts[0];
        j.edad           = parts[1].toInt();
        j.posicion       = parts[2];
        j.numeroCamiseta = parts[3].toInt();
        j.goles          = parts[4].toInt();

        result.append(j);
    }

    return result;
}

void JugadorRepository::saveAll(const QVector<Jugador>& jugadores) const {
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const Jugador& j : jugadores) {
        out << j.nombre << "|"
            << j.edad << "|"
            << j.posicion << "|"
            << j.numeroCamiseta << "|"
            << j.goles << "\n";
    }
}

