//C++ģ�壬ģ����C++��һ����Ҫ����
//����ģ�庯���Լ�����ģ�������������Ǻ�������ģ����ǻ���ֱ����������
//ģ�庯��
#include <iostream>
using namespace std;

#ifdef __template_func
template<class T>
T func(T& a, T& b)
{
    T c;
    c = a > b ? a:b;
    return c;
}
int main(int argc, char**argv)
{
    int max_num = 0;
    int a = 2;
    int b = 3;
    max_num = func(a, b);
    cout<<"max number is "<<max_num<<endl;
    return 0;
}
#endif
//ģ����
template<typename T>
class A
{
  public:
    A(const T& ii):i(ii)
    {
        cout<<"constructor A"<<endl;
    }
    ~A()
    {
        cout<<"deconstructor A"<<endl;
    }
  private:
    T i;
};


class B
{
    public:
        B(const B& b)
        {
            this->buff = new char[b.length];
            this->length = b.length;
            //����û���������B���ڲ�����ֱ�ӷ��ʸ�������������private��Ա����
            cout<<"constructor B"<<endl;
        }
        B(int i):length(i)
        {
            this->buff = new char[this->length];
            cout<<"constructor B"<<endl;
        }
        ~B()
        {
            delete this->buff;
            cout<<"deconstructor B"<<endl;
        }
    private:
        int length;
        char* buff;

};

int main(int argc, char** argv)
{
    B b(10);
    //A<int> a1(3);
    A<B> a2(b);
    return 0;
}


