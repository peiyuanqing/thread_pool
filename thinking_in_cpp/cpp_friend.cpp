//C++友元，包括友元函数和友元类
//C++友元函数




//C++友元类
/*
当某个类A，声明另外一个类B为其友元类的时候，那么在B中可以访问A的private内容
*/


#include <iostream>
using namespace std;
class A
{
    private:
        friend class B;
        friend class C;
        friend void friend_func(A & a);
        friend void friend_func_pointer(A *a);
        int i;
    public:
        A(int ii):i(ii)
        {
            cout<<"constructor A"<<endl;
        }
        ~A()
        {
            cout<<"deconstructor A"<<endl;
        }
        void func()
        {
            cout<<"A.i == "<<this->i<<endl;
        }
        void set(int ii)
        {
            this->i = ii;
            cout<<"set A.i = "<<this->i<<endl;
        }
};

class B
{
    public:
        B()
        {
            cout<<"constructor B"<<endl;
        }
        ~B()
        {
            cout<<"deconstructor B"<<endl;
        }
        void func(A& a)
        {
            cout<<"friend of A is B, something is done in B, A.i = "<<a.i<<endl;
            return;
        }
};


//在这里我们准备搞一些邪恶的事情，假如C类即使A的派生类，又是A的friend class会怎么样呢?
//let's have a try
//我们知道即使C是A的派生类，在C里面也不能访问其基类的private成员，
//那么如果一个类既是它的派生类，又是它的friend class的话，会发生什么有意思的事情呢?
class C : public A
{
    private:
        int j;
    public:
        C(int ii, int jj):A(ii), j(jj)
        {
            cout<<"constructor C"<<endl;
        }
        ~C()
        {
            cout<<"deconstructor C"<<endl;
        }
        void func(A& a)
        {
            cout<<"do something with out telling A. A.i"<<a.i<<endl;
        }
};



//我们定义一个友元函数
void friend_func(A& a)
{
    cout<<"I am a friend func of A, A.i = "<<a.i<<endl;
    return;
}


void friend_func_pointer(A *a)
{
    cout<<"I am a friend func of A, which receives of pointer of A, A.i = "<<a->i<<endl;
}


int main(int argc, char** argv)
{
    B b;
    A a(1);
    cout<<"sizeof(B) = "<<sizeof(B)<<endl;//这里输出的B的大小是1个字节，是不是很奇怪?鬼知道C++想干什么
    cout<<"sizeof(A) = "<<sizeof(A)<<endl;//这里输出仍然是4个字节，即一个int的大小，说明在A里面申明一个友元并不会导致A的体积变大
    cout<<"sizoef(C) = "<<sizeof(C)<<endl;
    b.func(a);

    C c(1,2);
    c.func(a);
    //c.func();//这里将发生name hiding，我们之前讲过的，会导致编译失败

    friend_func(a);//我们在A里面申明friend_func是A的友元函数，那么这个函数就可以访问A中的private成员

    //让我们干点刺激的东西吧，当友元遇到up_cast会怎样? 让我们试一试 = =!
    friend_func(c);//完全没有问题，我们访问到了C里面的东西。实际上从概念上说，我们还是访问对的是A里面的东西

    //如果遇到指针的up_cast会发生什么呢?试一试便知道 + +
    friend_func_pointer(&a);

    friend_func_pointer((A*)&c);//也完全没有问题
    
    return 0;
}


/*
关于友元有一些需要注意的概念
(1) 友元关系不能被继承。 B是A的友元class，C是A的子类，但是B不是C的友元。
    这一点也很好理解。从封装性的角度考虑，友元class B可以访问A的private内容，但是不应该看到
    其子类的private东西。连A都看不到，更别说它的友元class B了。

(2) 友元关系是单向的，不具有交换性。若类B是类A的友元，类A不一定是类B的友元，要看在类中是否有相应的声明。
    这个更好理解了，A说:B，你是我的友元，我的所有东西都可以给你看，
    但是B说:好啊，你一厢情愿，我也没有办法。但是我的东西还是不能给你看。

(3) 友元关系不具有传递性。
    这一点也比较好理解，假如B是A的friend class， A又是D的友元。
    那么B可以看到A的private，A有可以看见D的private，但是B不应该直接看到D的private。
    简单的例子就是，我朋友的朋友不一定认识我嘛。

*/

//友元函数，是指定义在类的外部，但是可以直接访问类的private成员的函数
//我们还是来上面代码里面的例子吧


/*
总结:
1.一个字，乱
2.个人认为friend class和friend function破坏了oop语言的封装特性。
3.从上面的例子里面可以看到，当friend function遇到了up_cast的时候，friend function破坏了
  派生类的内容。
4.any way，我觉得还是不到万不得已的情况下，不要用friend class和friend function吧。
  毕竟在别人不感知的情况下擅自动别人的底裤是一种不文明的现象。

*/


