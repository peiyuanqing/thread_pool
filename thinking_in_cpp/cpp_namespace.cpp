
//C++命名空间

//C++命名空间是一组逻辑分组机制


namespace Parse
{
    double expr(int);
    double func(int);
    //using namespace::std;//在定义一个命名空间，里面还可以再申请一个已经存在的命名空间
    std::String;
}

//将申明和实现分开，可以很好的看见命名空间的结构
double Parse::expr(int m)
{
    int x = m*m;
    return func(x);//这里调用和expr同一个命名空间的函数func不需要再指定命名空间了(即限定词)
}


//命名空间的别名

namespace MY_NAME_SPACE
{

    int func(std::string);
    double guc(int);
}

namespace MSP = MY_NAME_SPACE;

int MSP::func(std::string name)
{
    std::cout<<name<<std::endl;
    return 0;
}


/*命名空间的查找*/
//如果在使用一个函数的环境下找不到该函数，则去该函数的参数的命名空间去查找

/*命名空间的组合*/

namespace A
{
    class TEST
    {
        int i;
    };
    int func(int);
    int guc(int);
}
namespace B
{
    using namespace A;
    int huc(int);
}

namespace C
{
    using namespace B;
    int iuc();
}

//int C::func(int), 这里是不行的
//必须是
int A::func(int i)
{
    /**/
}
//规则是当在C里面去找显示的某个名字，如果找不到，编译器就会去查看指令提到的
//命名空间去找，但是要具体顶一个东西的时候，则必须和命名空间严格匹配

//命名空间是开放的，可以通过多个命名空间给它加入名字，下面这个例子是
//命名空间既有func，也有gunc
namespace D
{
    int func(int i);
}

namespace D
{
    int gunc(int i);
}


int main(int argc, char** argv)
{
    C::TEST test;//这里是ok的
    return;
}



 

 
 
 
