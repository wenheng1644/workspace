//
// Created by 文恒 on 2022/1/31.
//

#ifndef DRAWCARDAPP_MYLOG_H
#define DRAWCARDAPP_MYLOG_H

#include "string"
#include "fstream"
#include "vector"

#include "drawcard_Data.h"

class mylog {
public:
    mylog* getSingleton()
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
    std::string m_filename;


    mylog();
    std::string getTimeFile();

};


#endif //DRAWCARDAPP_MYLOG_H
