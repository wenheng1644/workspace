//
// Created by 文恒 on 2022/1/31.
//

#include "mylog.h"

#include "iostream"
#include "fstream"
#include "ctime"

using namespace std;
void mylog::write(const string &content) {

    string filename = getTimeFile();

    ofstream ofile(filename,ios::app);
    if(!ofile.is_open())
    {
        cerr << "file can't open";
        exit(0);
    }

    ofile << "\n" << content;

    ofile.close();
}

std::string mylog::getTimeFile() {
    const auto times = time(nullptr);
    auto stime = gmtime(&times);

    string filename = to_string(stime->tm_year) + to_string(stime->tm_mon) + to_string(stime->tm_mday);

    return filename;
}

void mylog::write(const vector<std::string> &contents) {

    string filename = getTimeFile();

    ofstream ofile(filename,ios::app);
    if(!ofile.is_open())
    {
        cerr << "file can't open";
        exit(0);
    }

    for(const auto& content : contents)
    {
        ofile << "\n" << content;
    }

    ofile.close();
}

void mylog::write(const vector<drawcard_data> &contents) {

    string filename = getTimeFile();
    ofstream ofile(filename);

    if(!ofile.is_open())
    {
        cerr << "error!! file can't open";
        exit(0);
    }

    for(const auto& content : contents)
    {
        string res = "cardId: " + to_string(content.m_id) + "\tname: " + content.m_name + "\tquality"
                + to_string(content.m_quality);

        ofile << "\n" << res;
    }

    ofile.close();
}

