//
// Created by 文恒 on 2022/1/3.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <direct.h>

using namespace std;

void printBoolIO();
void printValueIO();
void printIO_format();
void getInput();
void unformat_IO();
void fileIO();

void getfile();

int main(void)
{
//    char buff[100];
//    getcwd(buff,100);
//    cout << "current path: " << buff;
    fileIO();
//    unformat_IO();
}

void printBoolIO(){
    cout << "default bool: " << true << " " << false << endl;
    cout << "boolalpha bool: " << boolalpha << true << " " << false << ends;

    cout << "-------------------------------------------------" << endl;

    cout << noboolalpha << "change...." << true << " " << false << endl;
}

void printValueIO(){
    int val1,val2;
    val1 = 20;
    val2 = 1024;

    cout << showbase;
    cout << "default: " << val1 << " " << val2 << endl;
    cout << "oct: " << oct << val1 << " " << val2 << endl;
    cout << "hex: " << hex << uppercase << val1 << " " << val2 << endl;
    cout << "to default: " << dec << val1 << " " << val2 << endl;

    cout << noshowbase << nouppercase;

    cout << "precision: " << cout.precision() << " values: " << sqrt(2.0) << endl;
    cout.precision(12);
    cout << "precision: " << cout.precision() << " values: " << sqrt(2.0) << endl;

    cout << setprecision(6);
    cout << "precision: " << cout.precision() << " values: " << sqrt(2.0) << endl;


    cout << "default format: " << 100 * sqrt(2.0) << '\n';
    cout << "scientific: " << scientific << 100 * sqrt(2.0) << '\n';
    cout << "fixed: " << fixed << 100 * sqrt(2.0) << '\n';
    cout << "hexfloat: " << hexfloat << 100 * sqrt(2.0) << '\n';
    cout << "to default: " << defaultfloat << 100 * sqrt(2.0) << '\n';

    cout << "--------------------------------------------------------------" << endl;

    cout << 10.0 << endl;
    cout << showpoint << 10.0 << noshowpoint << endl;
}

void printIO_format(){
    int i = -16;
    double d = 3.14159;

    cout << "i: " << setw(12) << i << "next col" << '\n';
    cout << "d: " << setw(12) << d << "next col" << '\n';

    cout << left;
    cout << "2-i: " << setw(12) << i << "next col" << '\n';
    cout << "2-d: " << setw(12) << d << "next col" << '\n';
    cout << right;

    cout << right
        << "3-i: " << setw(12) << i << "next col" << '\n'
        << "3-d: " << setw(12) << d << "next col" << '\n';

    cout << internal << setfill('$')
        << "4-i: " << setw(12) << i << "next col" << '\n'
        << "4-d: " << setw(12) << d << "next col" << '\n';

    cout << setfill('#')
        << "5-i: " << setw(12) << i << "next col" << '\n'
        << "5-d: " << setw(12) << d << "next col" << '\n'
        << setfill(' ');


}

void getInput(){
    cin >> noskipws;

    cout << "please input:" << ends;
    char c;
    while(cin >> c)
        cout << c;

    cin >> skipws;
}

void unformat_IO(){
    char ch;

    while(cin.get(ch))
        cout.put(ch);
}

//使用IO读取文件内容
void getfile()
{
    ifstream in("test.txt",ios::in);

    if(!in.is_open()){
        cout << "the file is not exist..";
        return;
    }

    char buffer[100];

    int index{};
//    cout << "bytes: " << in.gcount();
    while(in)
    {
        in.getline(buffer,10);
        cout << "index" << ++index << ": " << buffer << endl;
        cout << "bytes: " << in.gcount() << endl;

        in.rdstate();
    }

    cout << "buffer: " << strlen(buffer) << endl;

    in.close();

}

void fileIO()
{
    fstream myfile("test.txt",fstream::ate | fstream::in | fstream::out);

    if(!myfile.is_open()){
        cerr << "the file can't open~~";
        exit(0);
    }

    auto endMark = myfile.tellp();

    string line;

    myfile.seekp(0,fstream::beg);

    auto curMark = myfile.tellp();

    while(myfile && curMark != endMark && getline(myfile,line)){
        size_t cnt = line.size();
        curMark = myfile.tellp();

        myfile.seekp(0,fstream::end);

        myfile << cnt+1;

        if(curMark != endMark) myfile << " ";

        myfile.seekp(curMark);
    }
    myfile << '\n';

    myfile.close();
}
