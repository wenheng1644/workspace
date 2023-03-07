//
// Created by wenheng on 22-10-20.
//

#ifndef COMMAND_COMMAND_H
#define COMMAND_COMMAND_H

class worker;

class command {
public:
    command(worker* w) : m_worker(w) {}
    virtual ~command() =default;

    virtual void excute() = 0;

protected:
    worker* m_worker;
};


class TeaCommand : public command
{
public:
    TeaCommand(worker* m) : command(m) {}
    ~TeaCommand() = default;

    void excute() override;
};

class MeatCommand : public command
{
public:
    MeatCommand(worker* w) : command(w) {}
    ~MeatCommand() = default;

    void excute() override;
};

class waiter
{
public:
    waiter() = default;
    ~waiter() = default;
    void setCommand(command* order)
    {
        m_command = order;
    }

    void noifty()
    {
        if(!m_command) return;

        m_command->excute();
    }
private:
    command* m_command;
};

class worker
{
public:
    worker() = default;
    ~worker() = default;

    void makeTea();
    void makeMeat();
};

#endif //COMMAND_COMMAND_H
