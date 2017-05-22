//C++中的智能指针，是面试的时候经常问到的一个问题，作为想惯例的每一个华为员工，都应该准备下啊
/*
1.对于编译器来说，只能指针是一个栈对象，并非指针类型，在栈对象生命周期即将结束的时候，
  智能指针通过析构函数释放它管理的堆内存。
2.所有只能指针都重载了operator ->，直接返回对象的引用
3.访问智能指针包含的裸指针则可以用 get() 函数。由于智能指针是一个对象，
  所以if (my_smart_object)永远为真，要判断智能指针的裸指针是否为空，需要这样判断：
  if (my_smart_object.get())。
*/
//std::auto_ptr

#include <iostream>
#include<memory>
using namespace std;

class A
{
    public:
        A(int i, const std::string& s)
        {
            this->number = i;
            this->info_extend = s;
            cout<<"constructor A"<<endl;
        }
        ~A()
        {
            cout<<"deconstructor"<<endl;
        }
        void func()
        {
            cout<<"A.number = "<<this->number<<endl;
            cout<<"A.info_extend = "<< this->info_extend <<endl;
        }

        void set(int i, const std::string s)
        {
            this->number = i;
            this->info_extend = s;
            cout<<"set A.number = "<<this->number<<endl;
            cout<<"Set A.info_extend = "<<this->info_extend<<endl;
        }
    private:
        int number;
        std::string info_extend;
};


int main(int argc, char** argv)
{
    //A a(10, "peixu");
    //a.func();
    std::auto_ptr<A> ptr1(new A(10, "peixu"));
    std::auto_ptr<A> ptr2;
    if(ptr1.get())
    {
        ptr1->func();
        ptr1->set(1, "maxin");
        ptr1->func();
        ptr2 = ptr1;
        ptr2->func();//这会导致程序崩溃，赋值操作会导致ptr1悬空
        //ptr1->func();
    }//看吧，再也没有恶心的delete了
    return 0;
}

/*
1.std::auto_ptr具体的使用方法还是要看auto_ptr类的声明。所在文件memmory
*/

/*
2.首先，只能指针是个对象，而不是指针。智能指针的思路是利用局部变量的声明周期是在某个
  scope里面，当离开这个scope的时候，这个智能指针的析构函数被自动调用，在智能指针的
  析构函数里面，显示的去调用智能指针所管理的那个对象的析构函数。
*/     

/*
3.auto_ptr的成员变量就是所要管理的对象的指针。这里需要注意下auto_ptr.release这个成员函数
  该函数在返回所管理的对象指针的同时，将自己的成员变量置为NULL
*/

/*
4.关于std::auto_ptr指针的更多信息，可以从它的类的声明里面看到。也可以实现自己的智能指针,
  概念上还是比较好理解的。
*/


