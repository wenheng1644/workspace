//
// Created by 文恒 on 2022/1/31.
//

#ifndef DRAWCARDAPP_MYLOG_H
#define DRAWCARDAPP_MYLOG_H

#include "string"
#include "fstream"
#include "vector"

#include "../drawCard/drawcard_Data.h"

class mylog {
public:
    static mylog* getSingleton()
    {
        if(!s_ptr)
            s_ptr = new mylog;

        return s_ptr;
    }

    void write(const std::string& content);
    void write(const std::vector<std::string>& contents);
    void write(const std::vector<drawcard_data>& contents);

private:
    static mylog* s_ptr;

    mylog() {}
    std::string getTimeFile();
    std::string getLogFile(); //确保生成日志文件路径正确

    std::string getDrawDateInfo(int times = 1); //获取抽卡日期等信息

};


#endif //DRAWCARDAPP_MYLOG_H
