#include <random>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

void testRandomEngine();
void testDistri_Engine();
void print_normalDistri(); //正态分布
void bonuli(); //伯努利测试

int main(void)
{
//    testRandomEngine();
//    testDistri_Engine();
//    print_normalDistri();
    bonuli();
    return 0;
}

void testRandomEngine()
{
    default_random_engine e;

    for(int i = 0;i < 10;i++)
    {
        cout << i+1 << ": " << e() << endl;
    }

    cout << "engine max: " << e.max() << " sizeof(e.max()): " << sizeof(e.max()) << endl;
    cout << "engine min: " << e.min() << endl;


}

void testDistri_Engine()
{
    static uniform_real_distribution<double> u(0,1);
    static default_random_engine e(time(nullptr));

    int i = 0;
    int totalCount = 100;

    int goodCount = 0;
    int badCount = 0;
    while(i < totalCount) {
        double res= u(e);

        if (res >= 0.8){
            cout << "good: " << res << endl;
            goodCount++;
        }
        else{
            cout << "bad: " << res << endl;
            badCount++;
        }
        i++;
    }

    cout << "goodCount: " << goodCount << " precise: " << (float)goodCount/totalCount << endl;
    cout << "badCount: " << badCount << " precise: " << (float)badCount/totalCount << endl;
}

void print_normalDistri(){
    default_random_engine e(time(nullptr));
    normal_distribution<> u(4,1.5);

    vector<unsigned> vec(9);

    for(int i = 0;i < 200;i++)
    {
        unsigned int v = lround(u(e));
        if(v < vec.size())
        {
            vec[v]++;
        }

    }

    for(int i = 0;i < vec.size();i++)
    {
        cout << i << ": " << string(vec[i],'*') << endl;
    }

}

void bonuli(){
    default_random_engine e(time(nullptr));
    bernoulli_distribution u(.1);

    int goodCount{};
    int badCount{};
    for(int i = 0;i < 100;i++)
    {
        bool res = u(e);

        if(res)
            goodCount++;
        else
            badCount++;
    }

    cout << "goodCount: " << goodCount << endl;
    cout << "badCount: " << badCount << endl;
}