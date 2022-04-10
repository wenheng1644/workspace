//
// Created by 文恒 on 2022/1/31.
//

#include "mylog.h"

#include "iostream"
#include "fstream"
#include "ctime"
#include "direct.h"

#include "QDir"

using namespace std;

mylog* mylog::s_ptr = nullptr;

void mylog::write(const string &content) {

    string filename = getLogFile();

    ofstream ofile(filename,ios::app);
    if(!ofile.is_open())
    {
        cerr << "file can't open";
        exit(0);
    }

    ofile << content << '\n';

    ofile.close();
}

std::string mylog::getTimeFile() {
    const auto times = time(nullptr);
    auto stime = gmtime(&times);

    string filename = to_string(stime->tm_year) + to_string(stime->tm_mon) + to_string(stime->tm_mday);

    return filename;
}

std::string mylog::getLogFile()
{
    std::string baseFileName = getTimeFile();

    std::string logPath = "./log";

    QString thedir = QDir::currentPath();

    if(access(logPath.c_str(),0) == -1)
    {
        mkdir(logPath.c_str());
    }

    return logPath + "/" + baseFileName + ".log";
}

std::string mylog::getDrawDateInfo(int times)
{
    const auto t = time(nullptr);
    auto s_time = localtime(&t);

    auto year = to_string(s_time->tm_year + 1900);
    auto month = to_string(s_time->tm_mon + 1);
    auto day = to_string(s_time->tm_mday);
    auto hour = to_string((s_time->tm_hour) % 24);
    auto min = to_string(s_time->tm_min);
    auto sec = to_string(s_time->tm_sec);

    std::string info = "[" + year + "." + month + "." + day + "\t" + hour + ":" + min + ":" + sec + "]" + "\t";

    info += "( " + to_string(times) + " )";
    return info;
}

void mylog::write(const vector<std::string> &contents) {

    string filename = getLogFile();
    ofstream ofile(filename,ios::app);
    if(!ofile.is_open())
    {
        cerr << "file can't open";
        exit(0);
    }

    for(const auto& content : contents)
    {
        ofile << content << "\n";
    }

    ofile.close();
}

void mylog::write(const vector<drawcard_data> &contents) {

    string filename = getLogFile();
    ofstream ofile(filename,ios::app);

    if(!ofile.is_open())
    {
        cerr << "error!! file can't open";
        exit(0);
    }

    std::string dateInfo = getDrawDateInfo(contents.size());
    ofile << dateInfo << "\n";
    for(const auto& content : contents)
    {
        string res = "cardId: " + to_string(content.m_id) + "\tname: " + content.m_name + "\tquality"
                + to_string(content.m_quality);

        ofile << res << "\n";
    }

    ofile << "--------------------------------------------------------------" << "\n";
    ofile.close();
}

