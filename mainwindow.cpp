#include "mainwindow.h"
#include "ui_mainwindow.h"

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
int b;
int temp[100];
void MainWindow::on_createKey_clicked()
{
    getPair();
    n = p * q;
    phi_n = (p-1) * (q - 1);
    QString n = getPublicKey();
    QString m = getPrivateKey();
    ui->Kpub->setText(n);
    ui->privateKey->setText(m);
}
QString eMsg, deMsg;
void MainWindow::on_encryptBtn_clicked()
{
    eMsg = ui->encryptText->toPlainText();
    QString res = encrypt();
    ui->decryptText->setPlainText(res);
}
void MainWindow::getPair(){
    do{
        p = random(2,50);
    }while(!isPrime(p));
    do{
        q = random(2,50);
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
            return r;
        }
    }
    return 0;
}
int MainWindow::extendEuclide(int b, int a){
    int result, y0=0, y1=1, r, q;
    while(a>0)
        {
            r=b%a;
            if(r==0) break;
            else
            {
            q=b/a;
            result=y0-y1*q;
            b=a;
            a=r;
            y0=y1;
            y1=result;
            }
        }
    if(result < 0){
        return result + phi_n;
    }
    return result;
}
int MainWindow::modulo(int a, int b, int n){
    long long x = 1, y = a;
    while(b > 0){
        if(b % 2 == 1){
            x = (x * y) % n;
        }
        y = (y * y) % n;
        b /= 2;
    }
    return x % n;
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
    QString privateKey = QString::number(extendEuclide(phi_n, b));
    return privateKey;
}
bool MainWindow::isPrime(int n){
    for(int i = 2; i <= (n / 2); i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}
void MainWindow::convertStringToInt(char c[]){
    long length = strlen(c);
    for(int i = 0; i< length; i++){
        temp[i] = c[i] - 'A';
    }
    for(int i=0; i<length; i++){
        printf("%d\n", temp[i]);
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
QString MainWindow::encrypt(){
    convertStringToInt(vh(eMsg));
    char arr[eMsg.length()];
    for(int i = 0; i < eMsg.length(); i++ ){
        temp[i] = modulo(temp[i], b, n);
        arr[i] = convertIntToChar(temp[i]);
    }
    QString enc(arr);
    return enc;
}
QString MainWindow::decrypt(){
    convertStringToInt(vh(eMsg));
    char arr[eMsg.length()];
    for(int i = 0; i < eMsg.length(); i++ ){
        temp[i] = modulo(temp[i], b, n);
        arr[i] = convertIntToChar(temp[i]);
    }
    QString enc(arr);
    return enc;
}
void MainWindow::on_decryptBtn_clicked()
{
    deMsg = ui->decryptText->toPlainText();
    QString res = decrypt();
    ui->encryptText->setPlainText(res);
}

