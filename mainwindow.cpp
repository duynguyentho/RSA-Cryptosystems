#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int p = 4, q = 3;
int n, phi_n;
int s;
int b;
int temp[100];
void MainWindow::on_createKey_clicked()
{
    getPair();
    n = p * q;
    phi_n = (p-1) * (q - 1);
    printf("\np va q: %d %d",p,q);
    printf("\nphi_n: %d",phi_n);
    printf("\n n: %d", n);
    QString n = getPublicKey();
    QString m = getPrivateKey();
    printf("\n b: %d",b);
    printf("\n s: %d\n",s);
    ui->Kpub->setText(n);
    ui->privateKey->setText(m);
}
QString eMsg, deMsg;
void MainWindow::on_encryptBtn_clicked()
{
    eMsg = ui->encryptText->text();
    QString res = encrypt(eMsg);
    ui->decryptText->setText(res);
}
void MainWindow::getPair(){
    do{
        p = random(2,20);
    }while(!isPrime(p));
    do{
        q = random(2,20);
    }while(!isPrime(q));
    if(p == q){
        getPair();
    }
}
int MainWindow::random(int begin, int end){
    return begin + rand() % (end + 1 - begin);
}
long int MainWindow::gcd(long int a,long  int b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

int MainWindow::getB(long int y){
    long int r;
    srand((int)time(0));
    while(true){
        r = random(2, y);
        if(gcd(r, y) == 1){
            printf("\nb: %d", r);
            return r;
        }
    }
    return 0;
}
int MainWindow::extendEuclide(int b, int a){
    for (long int l = 1; l < b; l++)
                {
                    if ((a * l) % b == 1)
                        return l;
                }
                return -1;
}
int MainWindow::modulo(int a, int b, int n){
    long result = 1L;
    for (long l = 0; l < b; l++)
    {
        result = (result * a) % n;
    }
    return result;
}
QString MainWindow::getPublicKey(){
    b = getB(phi_n);
    QString x = QString::number(b);
    QString y = QString::number(n);
    QString result = "";
    result.append(x);
    result.append(",");
    result.append(y);
    return result;
}
QString MainWindow::getPrivateKey(){
    s = extendEuclide(phi_n, b);
    QString privateKey = QString::number(s);
    return privateKey;
}
bool MainWindow::isPrime(int n){
    for(int i = 2; i <= (n / 2); i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
void MainWindow::convertStringToInt(char c[]){
    long length = strlen(c);
    for(int i = 0; i< length; i++){
        temp[i] = c[i] - char(65);
    }
}
char* MainWindow::vh(QString str){
    char* c = new char[str.size() + 1];
    QByteArray ba;
    ba = eMsg.toLatin1();
    strcpy(c,ba.data());
    c[str.size()] = '\0';
    return c;
}
char MainWindow::convertIntToChar(int i){
    return char(65 + i);
}
char* MainWindow::encrypt(QString str){
    char* x = new char(str.size() + 1);
    char* mau = vh(str);
    convertStringToInt(mau);
    int length = strlen(mau);
    char arr[eMsg.length()];
    for(int i = 0; i < length; i++ ){
        temp[i] = modulo(temp[i], b, n);
        printf("%d\n", temp[i]);
        x[i] = convertIntToChar(temp[i]);
    }
    for(int i = 0; i < length; i++ ){
        printf("%c\n", x[i]);
    }
     return x;
}
char* MainWindow::decrypt(QString str){
    char* x = new char(str.size() + 1);
    char* mau = vh(str);
    int length = strlen(mau);
    for(int i = 0; i < length; i++ ){
        temp[i] = modulo(temp[i], s, n);
        printf("%d\n", temp[i]);
        x[i] = convertIntToChar(temp[i]);
    }
    return x;
}
void MainWindow::on_decryptBtn_clicked()
{
    deMsg = ui->decryptText->text();
    QString res = decrypt(deMsg);
    ui->encryptText->setText(res);
}

void MainWindow::writeFile(){
    QString str = encrypt(eMsg);
    QFile file("/Users/wuyxz/Documents/RSAQtApplication/encrypt.txt");
    QTextStream textStream(&file);
    if(file.open(QIODevice::WriteOnly)){
        textStream << str;
        file.close();
    }
}
QString MainWindow::readFile(){
    QString str;
    QFile file("/Users/wuyxz/Documents/RSAQtApplication/key.txt");
    QTextStream textStream(&file);
    if(file.open(QIODevice::ReadOnly)){
        str = ui->encryptText->text();
        textStream << str;
        file.close();
    }
    return str;
}

