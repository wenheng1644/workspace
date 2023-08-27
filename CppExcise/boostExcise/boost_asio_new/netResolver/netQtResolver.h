//
// Created by wenheng on 23年8月19日.
//

#ifndef BOOST_ASIO_NEW_NETQTRESOLVER_H
#define BOOST_ASIO_NEW_NETQTRESOLVER_H

#include "string"
#include "iostream"
#include "utility"

#include "QtCore/QDataStream"
#include "QtCore/QByteArray"
#include "QtCore/QString"
#include "QtCore/QIODevice"

typedef std::pair<std::string, size_t> netStrData;

namespace netQtResolver {
    template<typename T>
    netStrData getSerialStrByCmdData(T& data);

    template<typename T>
    T getCmdDataBySerStr(const netStrData& serData);
};

template<typename T>
netStrData netQtResolver::getSerialStrByCmdData(T &data)
{
    QByteArray byteArray;
    QDataStream os(&byteArray, QIODevice::ReadWrite);

    os << data;

    std::string serStr = byteArray.toStdString();

    netStrData ret;
    ret.first = serStr;
    ret.second = byteArray.size();

    return ret;
}

template<typename T>
T netQtResolver::getCmdDataBySerStr(const netStrData& serData)
{
    QByteArray byteArray(serData.first.c_str(), serData.second);
    QDataStream os(byteArray);

    T cmd;

    os >> cmd;

    return cmd;
}


#endif //BOOST_ASIO_NEW_NETQTRESOLVER_H
