//运算符重载
/*
运算符重载和函数的重载是一样的，当你设计的类需要做一些运算符级别的操作的时候,
operator overload是一个很好的选择。例如 == <  >等等
operator overload可以看做是一个类的成员函数，它已经有一个默认参数是那个实现operator overload
操作符的类的对象。
*/
//下面是一些小例子。
#include <iostream>
using namespace std;
class A
{
    public:
        A(int ii):i(ii)
        {
            cout<<"constructor A"<<endl;
        }
        ~A()
        {
            cout<<"deconstructor A"<<endl;
        }

        const A& operator=(const A& b)
        {
            this->i = b.i;
            cout<<"my operator = is called"<<endl;
            return b;
        }

        bool operator==(const A& y)
        {
            cout<<"my operator = is called"<<endl;
            if(this->i == y.i)
            {
                return true;
            }
            else
                return false;
        }
        bool operator < (const A& x)
        {
            cout<<"my operator < is called"<<endl;
            return this->i < x.i;
        }
        bool operator > (const A& x)
        {
            cout<<"my operator > is called"<<endl;
            return this->i > x.i;
        }
        void func()
        {
            cout<<"A.i = "<<this->i<<endl;
        }
    private:
        int i;
};



int main()
{
    A a1(1);
    A a2(0);
    A a3 = a2 = a1;

    a2.func();
    a3.func();
    if(a1==a2)
    {
        cout<<"equal"<<endl;
    }
    if(a1 < a2)
    {
        cout<<"less than"<<endl;
    }
    if(a1 > a2)
    {
        cout<<"larger than"<<endl;
    }
    return 0;
}

