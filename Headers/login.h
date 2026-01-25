#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btnLogin_clicked();
    void on_btnRegistrar_clicked();

private:
    Ui::login *ui;
    void usuarioExiste(QString usuario, bool &existe, QString &contraseniaGuardada);
    int intentosFallidos = 0;
};

#endif
