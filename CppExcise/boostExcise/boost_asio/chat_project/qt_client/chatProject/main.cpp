#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <thread>

#include "boost/asio.hpp"

using namespace boost::asio;

void printio(io_service* ioserver)
{
    std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;
    io_service::work mywork(*ioserver);
    ioserver->run();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    io_service ioserver;
    ip::tcp::resolver myresolver_(ioserver);
    ip::tcp::resolver::query query("121.37.233.74", "8888");
    ip::tcp::resolver::iterator iter = myresolver_.resolve(query);

//    ioserver.poll();


    std::thread t(boost::bind(&printio, &ioserver));
//    std::thread t(boost::bind(&io_service::run, &ioserver));
//    t.join();

    MainWindow w(ioserver, iter);



    QApplication::desktop()->screen()->rect().center() - w.rect().center();
    w.show();
    w.raise();

    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;


    a.exec();
//    ioserver.run();
    t.join();

    return 0;
}
