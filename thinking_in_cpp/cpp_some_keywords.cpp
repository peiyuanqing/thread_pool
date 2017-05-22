//C++的一些关键字
//extern
//explicit
//static

//面对疾风吧.....
/*
explicit关键字
1.按默认规定，只用传一个参数的构造函数也定义了一个隐式转换
2.此关键字只能对用户自己定义的对象起作用，不对默认构造函数起作用
3.此关键字只能够修饰构造函数。而且构造函数的参数只能有一个。。

static关键字
1.面向过程的static关键和C语言是一样的，即无论是static变量还是static函数，其作用域都是该文件内

2.这里只考虑面向对象的static关键字
//类中的static变量
3.类里面的static变量，无论是静态类成员还是普通的数据类型，都需要在该类的定以后面，显示的将静态成员初始化
  其格式就像例子里面那样:  type class::member。前面无需再加上static关键字。//加上我试过了，会导致编译错误
4.类的非public静态成员变量的作用域仍然是只能在该类的内部使用。有一点需要注意的是，static成员的作用域将
  不局限于声明这个类的文件了。换句话说就是，static成员属于所有的该类的对象。
5.从下面这些蛋疼的例子可以得到一些蛋疼的结论
   a.可以在头文件里面定义一个static变量，其他文件include这个头文件的时候，可以对他进行修改
   b.可以在头文件下里面申明并实现一个static function，其他文件include这个头文件的时候可以调用该函数
   c.假如仅仅在头文件里面申明一个static function，而在另外一个文件里面去实现它，那么这个函数
     仅仅在实现该函数的文件可以调用。尽管其他文件include这个头文件，也不能调用这个static function，
     因为它实现在其他文件，且是static的，对它不可见。将产生链接错误。
     

//类中的static方法
1.一个类中包含static member function，可以将类的声明放在一个头文件里面
  static member function的实现放在其他文件里面。还是那句话，static member function属于这个类。
2.区别于普通的static function。普通static function如果将申明和定义分开的话，仅仅在该
  static function实现的文件里面才可以调用该函数。在其他文件里面调用，哪怕是include了头文件
  也会产生链接错误。


extern关键字
大家都知道的....
另外一个重要的用处就是，在C++里面编译C函数。众所周知，C++支持函数重载，而C语言是不支持函数
重载的。重载函数编译出来的函数名，除了函数名以外还和它的参数列表有关。
假如有以下函数

*/





#include <iostream>
#include "some_keywords.h"
#include "some_keywords_another.h"
using namespace std;


int A::x = 0;
int A::y = 0;
B A::b(0);

void A::test1(void)
{
    cout<<"static var in A, A::x = "<<A::x<<endl;
    return;
}

void A::test2(void)
{
    cout<<"static var in A, A::y = "<<A::y<<endl;
}


void A::test3(const A& a)
{
    a.test2();
    return;
}

static int static_func_test(void)
{
    cout<<"hello world"<<endl;
    return 0;
}



int main(int arc, char **argv)
{
    //A a=1;//当我们在构造函数前面加上explicit关键字的时候，那个这个隐式转换就不能通过编译了
    A a(1,2);//此时只能显式的调用该类的构造函数来生成一个类。
    A a1;
    a.func();
    A::test1();
    //A::test2();//test的是A的private成员函数，因此作用域仅仅限于A的内部
    cout<<"static var in A, A::x = "<<A::x<<endl;
    A::test3(a);
    static_var_test++;
    cout<<"static var which is define in a header file: "<<static_var_test<<endl;
    static_func_test();
    //static_func_test_another();
    static_func_test_another();

    return 0;
}


