//C++的public，private，protected，以及继承，多态，向上和向下造型，虚函数
//是时候做个了断了

//public关键字，表示成员变量和成员函数可以在任意作用域访问
//protected关键字，表示只有该类自己和它的子类可以访问
//private关键字，表示只有该类自己可以访问




//继承，A基类，B派生类
/*public继承
1.B获得A的所用的东西
2.A的private成员变量或者函数不能在B的作用域内--直接--访问，应该通过A的成员函数来使用
3.A中的public的东西可以在B中直接访问，在类的外部，也可以直接访问B从A继承过来
  的public的成员变量和成员函数
4.A的protected的成员变量和成员函数，继承到B中后仍然是protected的，可以在B类中直接访问，
  但是不能再B类的外部直接访问
5.A的private成员变量和成员函数，在B中仍然存在，但是不能在B中直接访问，应该通过A提供的成员
  函数去访问或者修改
*/

/*protected继承
1.A中的public成员变量和成员函数在B中将变成protected的
2.A中protected的成员变量和成员函数在B中仍然是protected的
3.A的private成员变量和成员函数，在B中仍然存在，但是不能在B中直接访问，应该通过A提供的成员
  函数去访问或者修改

*/
/*private继承
1.A中的public和protected均变成private的
2.A的private成员变量和成员函数，在B中仍然存在，但是不能在B中直接访问，应该通过A提供的成员
  函数去访问或者修改
*/




/*简而言之，如下
基类中 继承方式 子类中

public ＆ public继承 => public

public ＆ protected继承 => protected

public ＆ private继承 = > private



protected ＆ public继承 => protected

protected ＆ protected继承 => protected

protected ＆ private继承 = > private



private ＆ public继承 => 子类无权访问

private ＆ protected继承 => 子类无权访问

private ＆ private继承 = > 子类无权访问

*/
/*
由以上组合结果可以看出

1、public继承不改变基类成员的访问权限

2、private继承使得基类所有成员在子类中的访问权限变为private

3、protected继承将基类中public成员变为子类的protected成员，其它成员的访问 权限不变。

4、基类中的private成员不受继承方式的影响，子类永远无权访问。
*/


//public继承和protected继承的理解都是显而易见的
//这里重点研究下private继承

#ifdef __PRIVATE_INHERENT__
#include <iostream>
using namespace std;
class A
{
    public:
        A(int ii, int jj, int kk):i(ii),j(jj),k(kk)
        {
            cout<<"constructor A"<<endl;
        }
        ~A()
        {
            cout<<"deconstructor A"<<endl;
        }
        int i;
        void f1()
        {
            cout<<"this is f1"<<endl;
            f2();
            f3();
        }
        void aprintk()
        {
            cout<<"A.k = "<<this->k<<endl;
        }
    protected:
        int j;
        void f2()
        {
            cout<<"this is f2"<<endl;
            f3();
        }
    private:
        int k;
        void f3()
        {
            cout<<"this is f3"<<endl;
        }
};


class B : private A
{
    public:
    B(int ii, int jj, int kk):A(ii,jj,kk)
    {
        cout<<"constructor B"<<endl;
    }
    ~B()
    {
        cout<<"deconstructor B"<<endl;
    }
    void bprintk()
    {
        A::aprintk();//由于是private继承，A中所有东西在B中都变成private的了。
    }

};

int main(int argc, char** argv)
{
    B b(1,2,3);
    b.bprintk();
    //说明A中的private成员变量k在B中仍然存在,但是a的aprintk函数已经变成private的了，
    //不能在main里面直接调用了，但是仍然可以在B的内使用，且只能通过A提供的public或者protected函数来使用

    return 0;
}
#endif
//向上造型(up-cast)
//1.首先发现class的大小是和成员函数没有关系的
//2.派生类里面的成员函数函数如果和父类里面的成员函数名字相同且参数列表也相同的话，则发生name hiding，
//即B只能看到自己set(见代码)，但是在B中仍然可以显式的调用调用A的set函数
//3.派生类的成员变量的名字可以和父类的成员变量名字相同
//4.可以将派生类up cast成一个父类，而且是绝对安全的。换句话说，B isa A，up-cast只是将B当做A而已
//5.既然有向上造型，那么有没有向下造型呢，答案是没有。如果要这么写，则会发生编译错误
//像将A类向下造型为一个B或C，编译器会报错:no matching function for call to C::C(A&);
//根据这个报错信息，很显然，只要我们实现C::C(A&)，那么我们就可以完成向下造型了
#ifdef __up_cast
#include <iostream>
using namespace std;
class A
{
    public:
        A(int i):i(i)
        {
            cout<<"constructor A"<<endl;
        }
        //A():i(0)
        //{
        //}
        ~A()
        {
            cout<<"deconstructor A"<<endl;
        }

        void func()
        {
            cout<<"A.i = "<<this->i<<endl;
        }
        void set(int i)
        {
            this->i = i;
            cout<<"set A.i = "<<this->i<<endl;
        }
        int get()
        {
            return this->i;
        }
    private:
        int i;
};


class B : public A
{
    public:
        B(int i, int j): A(i), i(j)
        {
            cout<<"constructor B"<<endl;
        }
        ~B()
        {
            cout<<"deconstructor B"<<endl;
        }
        void func()
        {
            A::func();
            cout<<"B.i = "<<this->i<<endl;
        }
        void set(int i, int j)
        {
            A::set(i);
            this->i = j;
            cout<<"set B.i = "<<this->i<<endl;
        }
        void set(int i)
        {
            A::set(0);
            this->i = i;
            cout<<"Set B.i = "<<this->i<<endl;
        }
    private:
        int i;

};

class C : public A
{

};


class D : public A
{
    public:
        D(A& a):A(a.get())
        {
            cout<<"constructor D"<<endl;
        }
        ~D()
        {
            cout<<"deconstructor D"<<endl;
        }
};

class E : public A
{
    public:
        E(A& a):A(a.get()),j(0)
        {
            cout<<"constructor E"<<endl;
        }
        E(int i, int j):A(i), j(j)
        {
            cout<<"constructor E"<<endl;
        }
        ~E()
        {
            cout<<"deconstructor E"<<endl;
        }

        void func()
        {
            A::func();
            cout<<"E.j = "<<this->j<<endl;
        }

    private:
        int j;

};


int main(int argc, char**argv)
{
    A a(1);
    cout<<sizeof(A)<<endl;//输出结果是4，
    cout<<sizeof(a)<<endl;//输出结果是4
    a.func();
    a.set(10);
    a.func();
    //这说明每个类的成员函数并不会计算在这个类的大小里面


    B b(10,11);
    cout<<sizeof(B)<<endl;//输出结果是8，
    cout<<sizeof(b)<<endl;//输出结果是4
    b.func();
    b.set(5, 6);
    b.func();
    b.set(3);
    b.func();

    A a1 = (A)b;
    cout<<sizeof(a1)<<endl;//输出结果是4
    a1.func();
    a1.set(10);
    a1.func();
    /*
    B b2 = (B)a;
    cout<<sizeof(b2)<<endl;
    b2.func();
    b2.set(10, 11);
    b2.func();
    */
    /*
    C c = (C)a;
    cout<<sizeof(c)<<endl;
    c.func();
    c.set(10);
    c.func();
    */
    a.set(888);
    D d = (D)a;
    d.func();
    d.set(10);


    E *e = new E(1,2);

    e = (E*)&a;

    e->func();//会有一个随机值

    E e1 = a;
    e1.func();
    return 0;
}

#endif



//virtual关键字

/*1.虚函数，如果父类的一个函数申明为virtual，那么则告诉编译器，该父类的子类将拥有自己的virtual function。*/
/*2.之前在up-cast的范例里面看到，如果子类的一个函数和父类的一个函数的函数名和参数列表都一样的话
    将产生name hiding，但是在子类里面仍然可以显示的调用父类的函数。而且父类和子类的这两个函数是没有任何关系的
    只是所在的名字空间不一样而已*/
/*3.如果将父类的函数声明为virtual的，那么则告诉编译器，子类的该函数都是virtual的*/

//为什么要是用virtual函数呢? 答案是多态。多态是所有oop语言中最为重要的一个概念。

/*1.外界一个函数func使用父类的指针或者引用作为形参，在实际使用的时候，传入的实参是子类的指针或者引用,
    在func内调用virtual的函数的时候，则根据子类来分别调用各自的virtual函数。
  2.这个过程，只有在运行的时候才会实现，又叫做动态绑定。
  3.多态是指该指针或者引用是多态(polymorphism)的。
*/

//为什么要将析构函数申明为virtual呢?答案还是多态
/*1.如果在某个函数的参数是基类的指针或者引用，但是由于多态的原因，传进去的实参是子类的指针或者
    引用，那么在该函数里面delete p的时候，加入析构函数不是virtual的，那么调用的将是基类的析构函数
    进而可能引起内存泄露。
*/


//除C++外，其他oop语言都是动态绑定的。原因是C++追求效率。因为静态绑定实在编译时刻完成的。


//多态的实现
/*
1.类里面的virtual函数会占用内存。当一个类里面含有virtual函数的时候，
  该类的对象的内存的起始处会有一张表，对应着实现的virtual函数。实际上就是一个函数指针的table
  但是相同类的不同对象的virtual function table是一样的

2.假如子类中没有实现该父类virtual函数，则该子类里面的该函数和父类一样，即继承过来的。

3.每个类都有一个virtual function table，运行的时候，只要根据拿到的指针偏移到相对的位置
  就可以找到争取的函数调用。程序根本不关系这个指针是指向什么类的。
*/
//当多态遇到向上造型
/*
1.B是A的一个子类，将B类up cast到A，调用virtual func将仍然是A的virtual function。
  因为使用赋值操作符=，将调用拷贝构造函数，拷贝构造函数是按照成员拷贝的。virtual function table是不会被覆盖的。
2.对应的如果将B类的指针强转为A的指针，那么调用的将是B的virtual function
*/

//#ifdef __polymorphism
#include <iostream>
using namespace std;
class A
{
    public:
        int i;

        virtual void func() const
        {
            cout<<"A.i = "<<this->i<<endl;
            cout<<"A.j = "<<this->j<<endl;
        }
        A(int ii, int jj):i(ii),j(jj)
        {
            cout<<"constructor A"<<endl;
        }
        virtual ~A()
        {
            cout<<"deconstructor A"<<endl;
        }

        void set_j(int jj)
        {
            this->j = jj;
            cout<<"set A.j = "<<this->j<<endl;
        }
    private:
        int j;

};


class B : public A
{
    public:
        B():A(0,0)//只能通过初始化列表的方法调用父类的构造函数
        {
            cout<<"constructor B"<<endl;
        }
        virtual ~B()
        {
            cout<<"deconstructor B"<<endl;
        }
        virtual void func()
        {
            //A::set_j(888);
            this->i = 999;
            A::func();
        }
};

void out_func(A* const a)//这个函数声明说，我绝对不会改变入参值，但是调用a.func的时候，发现它并没有const修饰符的时候，会导致编译错误。
{
    a->func();
    return;
}


int main(int argc, char** argv)
{
    /*
    A a(10,10);
    cout<<sizeof(A)<<endl;//输出结果是8，因为virtual function table的存在，32位机器上则要多4个字节
    cout<<sizeof(a)<<endl;//输出结果是8
    a.func();
    B b;
    cout<<sizeof(B)<<endl;//输出结果是8
    cout<<sizeof(b)<<endl;//输出结果是8
    b.func();


    A a1(10,10), a2(11, 11);
    int *p = (int*)&a1;
    int *q = (int*)&a2;

    cout<<*p<<"  "<<*q<<endl;
    //*p和*q的值是一样的，可见相同类的不同对象，对应的那个virtaul function table是一样的

    int *x = (int*)*p;//这是为了查看virtual function在内存中的位置
    cout<<"pos = "<<x<<endl;

    B b1;

    B *b2 = new B();

    delete b2;
    //A a4 = b1;//这里不会调用A的构造函数。具体动作是先申请栈内存，大小为A，然后将B的内存拷贝到a4
              //因此在退出函数的时候，仍然会调用A的析构函数。

    //a4.func();//调用的仍然是a的func

    */
    B b1;
    A *a3 = &b1;
    b1.func();
    a3->func();//这里调用将是b的函数，因为拷贝构造函数式按照成员拷贝的。而这里是地址的直接转换

    //out_func(a);
    B b5;
    out_func(&b5);
    return 0;
}
//#endif


//虚基类和虚继承









