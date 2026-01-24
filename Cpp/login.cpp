#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::usuarioExiste(QString usuario, bool &existe, QString &contraseniaGuardada)
{
    existe = false;

    QFile archivo("usuarios.txt");

    if (!archivo.exists()) {
        archivo.open(QIODevice::WriteOnly | QIODevice::Text);
        archivo.close();
        return;
    }

    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&archivo);
    QString user, contra;

    while (!in.atEnd()) {
        in >> user >> contra;
        if (user == usuario) {
            existe = true;
            contraseniaGuardada = contra;
            break;
        }
    }

    archivo.close();
}

void login::on_btnRegistrar_clicked()
{
    QString usuario = ui->txtUsuario->text().trimmed();
    QString contrasenia = ui->txtContrasenia->text().trimmed();

    if (usuario.length() == 0 || contrasenia.length() == 0) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Registro");
        msg.setText("Es obligatorio llenar todos los campos");
        msg.setStyleSheet(
            "QLabel { color: white; }"
            "QPushButton { color: white; }"
            );
        msg.exec();
        return;
    }

    bool existe;
    QString temporal;
    usuarioExiste(usuario, existe, temporal);

    if (existe) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Registro");
        msg.setText("El usuario ya existe");
        msg.setStyleSheet(
            "QLabel { color: white; }"
            "QPushButton { color: white; }"
            );
        msg.exec();
        return;
    }

    QFile archivo("usuarios.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Error");
        msg.setText("No se pudo abrir el archivo");
        msg.setStyleSheet(
            "QMessageBox { background-color: #0b1d3a; }"
            "QLabel { color: white; font-size: 14px; }"
            "QPushButton { color: white; background-color: #1e88e5; padding: 6px 14px; }"
            "QPushButton:hover { background-color: #42a5f5; }"
            );
        msg.exec();
        return;
    }

    QTextStream out(&archivo);
    out << usuario << " " << contrasenia << "\n";
    archivo.close();

    QMessageBox msg(this);
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("Registro");
    msg.setText("Usuario registrado correctamente");
    msg.setStyleSheet(
        "QLabel { color: white; }"
        "QPushButton { color: white; }"
        );
    msg.exec();

    ui->txtUsuario->clear();
    ui->txtContrasenia->clear();
}

void login::on_btnLogin_clicked()
{
    QString usuario = ui->txtUsuario->text().trimmed();
    QString contrasenia = ui->txtContrasenia->text().trimmed();

    if (usuario.length() == 0 || contrasenia.length() == 0) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Login");
        msg.setText("Es obligatorio llenar todos los campos");
        msg.setStyleSheet(
            "QLabel { color: white; }"
            "QPushButton { color: white; }"
            );
        msg.exec();
        return;
    }

    bool existe;
    QString contraseniaGuardada;
    usuarioExiste(usuario, existe, contraseniaGuardada);

    if (!existe) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Login");
        msg.setText("El usuario no existe, por favor regístrese");
        msg.setStyleSheet(
            "QLabel { color: white; }"
            "QPushButton { color: white; }"
            );
        msg.exec();

        ui->txtUsuario->clear();
        ui->txtContrasenia->clear();
        ui->txtUsuario->setFocus();
        return;
    }

    if (contrasenia != contraseniaGuardada) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Login");
        msg.setText("Contraseña incorrecta");
        msg.setStyleSheet(
            "QLabel { color: white; }"
            "QPushButton { color: white; }"
            );
        msg.exec();
        return;
    }

    QMessageBox msg(this);
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("Login");
    msg.setText("Bienvenido " + usuario);
    msg.setStyleSheet(
        "QLabel { color: white; }"
        "QPushButton { color: white; }"
        );
    msg.exec();

    accept();

    ui->txtUsuario->clear();
    ui->txtContrasenia->clear();
}

