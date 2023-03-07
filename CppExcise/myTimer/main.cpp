//
// Created by wenheng on 22-10-24.
//
#include "iostream"
#include "chrono"
#include "boost/format.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "functional"
#include "thread"

#include "myTimer.h"

void test_1()
{
    using namespace std::chrono;
    duration<int, std::ratio<1, 10>> t(9);

    milliseconds t2;
    t2 += t;
    std::cout << t.count() << std::endl;
    std::cout << t2.count() << std::endl;

    seconds seconds1 = duration_cast<seconds>(t);
    std::cout << seconds1.count() << std::endl;
    std::cout << (t % seconds(1)).count() << std::endl;
}

void test_ratio()
{
    std::ratio_add<std::ratio<1,2>, std::ratio<2,3>> a;
    std::cout << boost::format("num = %d and den = %d") % a.num % a.den << std::endl;
}

std::string fromTimePoint(const std::chrono::system_clock::time_point& tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    std::string str = ctime(&t);
    str.resize(str.size() - 1);
    return str;
}

void trans_timePoint()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration> t2;

    std::chrono::system_clock::time_point tp;
    std::string str = fromTimePoint(tp);
    std::cout << boost::format("epoch = %s") % str << std::endl;

    tp = std::chrono::system_clock::now();
    str = fromTimePoint(tp);
    std::cout << boost::format("now = %s") % str << std::endl;

    tp = std::chrono::system_clock::time_point::min();
    str = fromTimePoint(tp);
    std::cout << boost::format("min = %s") % str << std::endl;

    tp = std::chrono::system_clock::time_point::max();
    str = fromTimePoint(tp);
    std::cout << boost::format("max = %s") % str << std::endl;

}

void test_tp2()
{
    typedef std::chrono::duration<int, std::ratio<3600 * 24>> DAYS;
    std::chrono::system_clock::time_point tp;

    std::cout << boost::format("epoch = %s") % fromTimePoint(tp) << std::endl;

    DAYS day(1);
    tp += day + std::chrono::hours(23) + std::chrono::minutes(55);
    std::cout << boost::format("later = %s") % fromTimePoint(tp) << std::endl;

    auto diff = tp - std::chrono::system_clock::time_point();
    std::cout << boost::format("diff = %d\n") % std::chrono::duration_cast<std::chrono::minutes>(diff).count();

}

std::chrono::system_clock::time_point fromTimeT(int year, int month, int day,
                                                int hour, int min, int sec)
{
    std::tm t;
    t.tm_year = year - 1900;
    t.tm_mon = month;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;
    t.tm_isdst = -1;
    std::time_t tt = mktime(&t);

    if(tt == -1)
    {
        std::cout << "error" << std::endl;
        throw "error";
    }

    return std::chrono::system_clock::from_time_t(tt);



}

void printMyName(const std::string& str)
{
    std::cout << boost::format("hello, my name is %s") % str << std::endl;
}

void test_myTimer()
{
    std::function<void()> f = std::bind(&printMyName, "徐伟镇");
    myTimer timer(f);
    myTimer timer2(std::bind(&printMyName, "邝慧娴"));
    timer.start(std::chrono::seconds(5));
    timer2.start(std::chrono::seconds(3));
    std::cout << "timer go to start~" << std::endl;
    for(int i = 0; i < 10; i++)
    {
        std::cout << "main thread test!!!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "main thread done~" << std::endl;
}

void test_dateTime1()
{
    using namespace boost::gregorian;
    date d(2022, 1, 1);
    date d2(boost::gregorian::not_a_date_time);

}

void test_cppTime()
{
    auto tp = std::chrono::system_clock::now();
    std::time_t t1 = std::chrono::system_clock::to_time_t(tp);
    std::time_t t2 = time(nullptr);

    std::chrono::system_clock::time_point epcho;
    std::time_t t3 = std::chrono::system_clock::to_time_t(epcho);


    if(t1 == t2)
        std::cout << boost::format("t1 and t2 is equal~  %d") % t1 << std::endl;
    std::cout << boost::format("the one = %d") % t3 << std::endl;

    std::string str1 = ctime(&t1);
    std::cout << boost::format("str = %s") % str1 << std::endl;

    std::tm date1;
    memset(&date1, 0, sizeof date1);

    date1.tm_year = 2023 - 1900;
    date1.tm_mon = 1 - 1;
    date1.tm_mday = 22;
    date1.tm_isdst = -1;

    std::time_t nextYear = mktime(&date1);
    std::cout << boost::format("nextYearTime_t = %d str = %s") % nextYear % ctime(&nextYear) << std::endl;

    std::cout << boost::format("format date = %s") % std::put_time(localtime(&t2), "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main()
{
    test_myTimer();

    return 0;
}
