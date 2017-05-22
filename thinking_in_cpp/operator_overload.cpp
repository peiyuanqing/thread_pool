//���������
/*
��������غͺ�����������һ���ģ�������Ƶ�����Ҫ��һЩ���������Ĳ�����ʱ��,
operator overload��һ���ܺõ�ѡ������ == <  >�ȵ�
operator overload���Կ�����һ����ĳ�Ա���������Ѿ���һ��Ĭ�ϲ������Ǹ�ʵ��operator overload
����������Ķ���
*/
//������һЩС���ӡ�
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

