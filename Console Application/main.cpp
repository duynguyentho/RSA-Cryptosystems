//  Xcode
//  main.cpp
//  RSA Demo
//
//  Created by wuyxz on 17/05/2021.
//

#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>
#include <stdio.h>
//use boost library
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/algorithm/string/std/list_traits.hpp>
void convertToBase64(std::string a){
    using namespace boost::archive::iterators;
    std::string test = a;
    std::stringstream os;
        typedef
            insert_linebreaks<
                base64_from_binary<
                    transform_width<
                        const char *,
                        6,
                        8
                    >
                >
                ,72
            >
            base64_text;

        std::copy(
            base64_text(test.c_str()),
            base64_text(test.c_str() + test.size()),
            ostream_iterator<char>(os)
        );

        std::cout << os.str();
}
using namespace std;
long int p, q, n, phi_n, e, d, b, s;
string inputMsg; // chuoi ki tu nhap vao
char* eMsg; // encrypt Message
int temp[100];
char* dMsg; // decrypt Message
long int extendEuclide(long int, long int);
void convertStringToInt(char c[]);
bool isPrime(long int n);
long int getB(long int y); // lay so b
char convertIntToChar(int i);
long int extendEuclide(long int b, long int a); // nghich dao modulo
bool isPrime(long int n){
    for(int i = 2; i <= (n / 2); i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
long int gcd(long int a,long  int b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}
long random(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}
// 1 < b < phi_n(n) && gcd(b, phi_n(n)) == 1
long int getB(long int y){
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
long int extendEuclide(long int b, long int a){
    for (long int l = 1; l < b; l++)
                {
                    if ((a * l) % b == 1)
                        return l;
                }
                return -1;
}
long int modulo(long int a, long int b, long int n){
    long result = 1L;
    for (long l = 0; l < b; l++)
    {
        result = (result * a) % n;
    }
    return result;
    
}
char* vh(string str){
    char* c = new char[str.size() + 1];
    copy(str.begin(), str.end(), c);
    c[str.size()] = '\0';
    return c;
}
void convertStringToInt(char c[]){
    long length = strlen(c);
    for(int i = 0; i< length; i++){
        temp[i] = c[i] - char(65);
    }
//    for(int i = 0;  i < length ; i++){
//        cout << temp[i]<<endl;
//    }
}
char* encrypt(string s){
    char* x = new char(s.size() + 1);
    char* mau = vh(s);
    convertStringToInt(mau);
    int length = strlen(mau);
    for(int i = 0; i< length; i++){
        temp[i] = modulo(temp[i], b, n);
        x[i] = convertIntToChar(temp[i]);
    }
//    for(int i = 0;  i < length ; i++){
//        cout << temp[i]<<endl;
//    }
    return x;
}
char* decrypt(string str){
    char* x = new char(str.size() + 1);
    char* mau = vh(str);
    int length = strlen(mau);
    cout <<"\n------------------------------\n";
    for(int i = 0; i< length; i++){
        temp[i] = modulo(temp[i], s, n);
        x[i] = convertIntToChar(temp[i]);
    }
//        for(int i = 0;  i < length ; i++){
//            cout << temp[i]<<endl;
//        }
    return x;
}
void getPair(){
    srand((int)time(0));
    do{
        p = random(3, 3000);
    }while(!isPrime(p));
    do{
        q = random(3, 3000);
    }while(!isPrime(q) && p != q);
}
void Running(){
    long int x1, y1;
//    cout << "Input p: \n";
//    cin >> p;
//    cout <<"Input q: \n";
//    cin >> q;
//    if(!isPrime(p) || !isPrime(q)){
//        cout <<"\nInput a pair of prime number !";
//        return ;
//    }
//    if(p == q){
//        cout << "p can't equal q";
//        return;
//    }
    getPair();
    n = p * q;
    phi_n = (p - 1)*(q - 1);
    b = getB(phi_n);
    cout<<"-----------------\n";
    cout << "p: "<<p;
    cout <<"\nq: "<<q;
    cout << "\nn: "<< n;
    cout <<"\ny: "<<phi_n;
    cout <<"\nb: "<<b;
    cout <<"\nKpublic(n, b): ("<<n<<", "<<b<<")"<<endl;
    std::ostringstream kpub;
    kpub << n << b;
    const std::string kpu(kpub.str());
    convertToBase64(kpu);
    s = extendEuclide(phi_n, b);
    cout <<"\nKprivate: "<< s <<endl;
    std::ostringstream kpriv;
    kpriv << s << n;
    const std::string kpr(kpriv.str());
    convertToBase64(kpr);
    cout << "\nInput message: \n";
    cin >>inputMsg;
    std::string input(inputMsg);
    convertToBase64(input);
    cout <<"\nEncrypt: \n---------------------------------\n" <<encrypt(inputMsg)<< endl;
    dMsg = encrypt(inputMsg);
    cout <<"\nDecrypt: " <<decrypt(dMsg)<<endl;
//    std::string str(decrypt(dMsg));
//    convertToBase64(str);
    return;
}
char convertIntToChar(int i){
    return char(65+i);
}
int main(int argc, const char * argv[]) {
   Running();
    //cout << char(65);
    //getPair();
    return 0;
}
