//
// Created by 文恒 on 2022/4/15.
//

#ifndef SERVER_DATETIMEMGR_H
#define SERVER_DATETIMEMGR_H

#include "string"
#include "cstring"
#include "ctime"

#include "boost/date_time/gregorian/greg_date.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

//using namespace std;
class dateTimeMgr {
public:
    static std::string getDateTime()
    {
        using namespace boost::posix_time;
        ptime curtime = boost::posix_time::second_clock::local_time();
        std::string dateTime_str = to_iso_string(curtime);

        size_t idx = dateTime_str.find('T');

        dateTime_str.replace(idx, 1, std::string(" "));
        dateTime_str.replace(idx - 2, 0, std::string("-"));
        dateTime_str.replace(idx - 4, 0, std::string("-"));
        idx = dateTime_str.find(' ');
        dateTime_str.replace(idx + 3,0,std::string(":"));
        dateTime_str.replace(idx + 6,0,std::string(":"));


        return dateTime_str;
    }


private:
    static dateTimeMgr* m_dataTimeMgr;

    dateTimeMgr() {}
};


#endif //SERVER_DATETIMEMGR_H
