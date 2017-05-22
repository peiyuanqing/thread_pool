//C++的引用

/*
1.引用的概念还是比较好理解的，申明一个引用，并将其和某个变量捆绑在一起，
  在用这个引用的时候，相当于使用这个变量本身。引用的一个重要的特性就是申明的时候必须将其初始化。

2.当一个类的成员变量是引用的时候，则只能采取初始化列表的方法将其和某个变量绑定

3.为什么要这么干呢?还是C++的对象构造机制的问题。C++在构造一个对象的时候是先申请内存，然后
  调用构造函数去初始化各个成员变量。限于引用必须在申明的时候就初始化，必须采用初始化列表的方法。

4.reference可以作为左值

5.函数的形参建议使用reference，为了防止函数对外部传入的变量进行修改，使用const关键字
*/
class A
{
    public:
        A(int& b):a(b)
        {
            cout<<"constructor A"<<endl;
        }
        ~A();
        void func()
        {
            cout<<"A.a = "<<this->a<<endl;
        }
        void set(int i)
        {
            this->a = i;
            cout<<"set A.a = "<<this->a<<endl;
        }
    private:        
        int& a;
}


int main()
{
    int i = 3;
    A *a = new a(i);

    a.func();
    a.set(0);
    cout<<"value of i is "<<i<<endl;

    return 0;
}





