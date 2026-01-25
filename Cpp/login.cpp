
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
        QMessageBox::warning(this, "Registro", "Es obligatorio llenar todos los campos");
        return;
    }
    bool existe;
    QString temporal;
    usuarioExiste(usuario, existe, temporal);

    if (existe) {
        QMessageBox::warning(this, "Registro", "El usuario ya existe");
        return;
    }

    QFile archivo("usuarios.txt");
    if (!archivo.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream out(&archivo);
    out << usuario << " " << contrasenia << "\n";
    archivo.close();

    QMessageBox::information(this, "Registro", "Usuario registrado correctamente");

    ui->txtUsuario->clear();
    ui->txtContrasenia->clear();
}

void login::on_btnLogin_clicked()
{
    QString usuario = ui->txtUsuario->text().trimmed();
    QString contrasenia = ui->txtContrasenia->text().trimmed();
    if (usuario.length() == 0 || contrasenia.length() == 0) {
        QMessageBox::warning(this, "Login", "Es obligatorio llenar todos los campos");
        return;
    }
    bool existe;
    QString contraseniaGuardada;
    usuarioExiste(usuario, existe, contraseniaGuardada);

    if (!existe) {
        QMessageBox::warning(this, "Login", "El usuario no existe, por favor regístrese");
        ui->txtUsuario->clear();
        ui->txtContrasenia->clear();
        ui->txtUsuario->setFocus();

        return;

    }


    if (contrasenia != contraseniaGuardada) {

            intentosFallidos++;

            QMessageBox::warning(
                this,
                "Login",
                "Usuario y/o Contraseña incorrecta\nIntentos restantes: "
                    + QString::number(3 - intentosFallidos)
                );

            if (intentosFallidos >= 3) {
                QMessageBox::critical(
                    this,
                    "Login",
                    "Has superado el número máximo de intentos.\nLa aplicación se cerrará."
                    );
                reject();
                return;
            }

            ui->txtContrasenia->clear();
            ui->txtContrasenia->setFocus();
            return;
        }

        QMessageBox::information(this, "Login", "Bienvenido " + usuario);
        intentosFallidos = 0;
    accept();

    ui->txtUsuario->clear();
    ui->txtContrasenia->clear();
}
