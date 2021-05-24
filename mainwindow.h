#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createKey_clicked();
    void on_encryptBtn_clicked();

    void on_decryptBtn_clicked();

private:
    int random(int , int );
private:
    long int gcd(long int, long int);
private:
    int getB(long int);
private:
    bool isPrime(int);
private:
    QString getPublicKey();
private:
    void getPair();
private:
    int modulo(int, int, int);
private:
    int extendEuclide(int, int);
private:
    QString getPrivateKey();
private:
    void convertStringToInt(char c[]);
private:
    char* vh(QString s);
private:
    char convertIntToChar(int a);
private:
    char* encrypt(QString);
private:
    char* decrypt(QString);
private:
    QString readFile();
private:
    void writeFile();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
