#include <iostream>
#include <string>
using namespace std;

//异常必须是可以处理的，而且不应该是代码调试的手段
//大部分公司是禁止使用异常的，原因是C++程序员的素质参差不齐.....

//异常的捕获方式
try
{

}catch(...)//捕捉所有异常，但是得不到异常对象

//异常的获取顺序,按照书写的顺序。
//在每一个catch里面按照如下三条规则来catch异常
/*
1.查找是否有完全匹配的异常
2.查找是否可以有转换的异常匹配
3.是否是ellipse，即...匹配
*/

//关于类型转换，有以下要求
/*
1.    允许从非常量转换到常量的类型转换。
2.    允许从派生类到基类的转换。
3.    允许数组被转换成为指向数组（元素）类型的指针，函数被转换成指向该函数类型的指针。
4.    标准算术类型的转换（比如：把bool型和char型转换成int型）
      和类类型转换(使用类的类型转换运算符和转换构造函数)。
*/

//可能抛出异常的函数写法
//表示运行最多最多可能抛出一下几种异常，这个是限制func函数的，而不是函数的调用者
#ifdef __CPP_EXCEPION
int func(int a) : throw(exception1, exception2, exception3)
{
    
}
//表示func可能抛出任何异常
int func(int a)
{

}
//表示不抛出任何异常
int func(int a) : throw()
{

}

//构造函数中的异常
//C++的new不会给你一个NULL,而是抛出一个异常
class
{
    public:
        A()
        {
            this->amem = new char[10];
        }
        ~A()
        {
            delete this->amem;
            this->amem = NULL;
        }
    private:
        char *amem;
}A;

class B:public A
{
    public:
        B()
        {
            this->bmem = new char[10]
            throw exception;
        }
        ~B()
        {
            delete this->bmem;
            this->bmem = NULL;
        }
    private:
        char *bmem;
}


int func()
{
    A *a = new A();
    //C++的机制是先申请内存，然后去调用构造函数。此时A的内存已经分配。但是如果抛出异常，系统会将这部分内存回收
    //至于A的构造函数抛出异常之前new出来的那一片内存将不会被释放
    //构造没有完成，析构函数不会被调用
    delete a;

    return 0;
}


//正确的处理方法
int func()
{
    try
    {
        A *a = new A();
        //抛出的异常内存位于栈，后来会被销毁。
        //如果抛出的异常时new出来的，那么catch后应该显示的delete掉异常
    }
    catch(exceptionxx &)
    //如果是第一种情况，这里catch的时候最好用一个引用
    //直接拿到那个异常对象做处理，而不会发生拷贝构造
    //如果是第二种情况，throw一个异常对象的指针，
    //在这里catch异常对象的指针，处理完异常后，手动将其delete掉
    {
        do something;
    }
    delete a;

    return 0;
}
//派生类构造函数中的异常
int func()
{
    try
    {
        B *b = new B();
        //1.申请B的内存
        //2.调用B的构造函数
        //3.调用A的构造函数,初始化A
        //4.继续执行B的构造函数，发现有异常抛出，终止构造函数
        //5.调用A的析构函数，销毁class A;
    }
    catch(exceptionxxx)
    {
        do something;
        //由于B里面已经new了一片内存，在这里需要有手段将其释放
        //唯一的解决办法是，在抛出异常之前，将该类申请的内存手动释放掉
        //或者是在构造函数内部尝试try catch，然后手动释放内存
    }
    
    delete a;

    return 0;
}

#endif


#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int32_t result;
    int i = 0;
    cin>>i;
    try
    {
        result = 100/i;
    }catch()
    {

    }
}



//标准异常

/*
语言抛出
bad_alloc, throw: new
bad_cast, throw: dynamic_cast

bad_typed, throw: typeid

bad_exception, throw: 异常描述



标准库抛出
out_of_range    throw: at()
invalid_argument throw: 按位设置构造函数
overflow_error throw: throw: bitset<>::to_ulong



*/



