//
// Created by нд╨Ц on 2022/5/13.
//

#include "thread"
#include "iostream"

#include "cv_task.h"

int main()
{
    cv_task task;

//    std::thread pro1(&cv_task::provider, &task, 1);
//    std::thread con1(&cv_task::consumer, &task, 10);
//    std::thread con2(&cv_task::consumer, &task, 11);
//    std::thread con3(&cv_task::consumer, &task, 12);
//
//    pro1.join();
//    con1.join();
//    con2.join();
//    con3.join();

    std::thread t1(&cv_task::atomic_pro, &task);
    std::thread t2(&cv_task::atomic_con, &task);

    t1.join();
    t2.join();

    return 0;
}
