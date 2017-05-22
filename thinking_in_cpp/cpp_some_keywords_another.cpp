#include "some_keywords.h"
using namespace std;
/*
int static_func_test_another(void)
{
    static_var_test++;
    return static_func_test();

}*/


int static_func_test_another(void)
{
    A a(10, 20);
    A::test1();
    A::test3(a);
    cout<<"use the static var A.x in another file A.x = "<<A::x<<endl;
    return 0;
}



