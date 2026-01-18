#ifndef JUGADORREPOSITORY_H
#define JUGADORREPOSITORY_H

#include "jugador.h"
#include <QVector>
#include <QString>

class JugadorRepository
{
private:
    QString filePath;

public:
    JugadorRepository(const QString& path);

    QVector<Jugador> loadAll() const;
    void saveAll(const QVector<Jugador>& jugadores) const;
};

#endif // JUGADORREPOSITORY_H
