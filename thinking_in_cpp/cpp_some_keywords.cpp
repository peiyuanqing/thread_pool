//C++��һЩ�ؼ���
//extern
//explicit
//static

//��Լ����.....
/*
explicit�ؼ���
1.��Ĭ�Ϲ涨��ֻ�ô�һ�������Ĺ��캯��Ҳ������һ����ʽת��
2.�˹ؼ���ֻ�ܶ��û��Լ�����Ķ��������ã�����Ĭ�Ϲ��캯��������
3.�˹ؼ���ֻ�ܹ����ι��캯�������ҹ��캯���Ĳ���ֻ����һ������

static�ؼ���
1.������̵�static�ؼ���C������һ���ģ���������static��������static���������������Ǹ��ļ���

2.����ֻ������������static�ؼ���
//���е�static����
3.�������static�����������Ǿ�̬���Ա������ͨ���������ͣ�����Ҫ�ڸ���Ķ��Ժ��棬��ʾ�Ľ���̬��Ա��ʼ��
  ���ʽ����������������:  type class::member��ǰ�������ټ���static�ؼ��֡�//�������Թ��ˣ��ᵼ�±������
4.��ķ�public��̬��Ա��������������Ȼ��ֻ���ڸ�����ڲ�ʹ�á���һ����Ҫע����ǣ�static��Ա��������
  �������������������ļ��ˡ����仰˵���ǣ�static��Ա�������еĸ���Ķ���
5.��������Щ���۵����ӿ��Եõ�һЩ���۵Ľ���
   a.������ͷ�ļ����涨��һ��static�����������ļ�include���ͷ�ļ���ʱ�򣬿��Զ��������޸�
   b.������ͷ�ļ�������������ʵ��һ��static function�������ļ�include���ͷ�ļ���ʱ����Ե��øú���
   c.���������ͷ�ļ���������һ��static function����������һ���ļ�����ȥʵ��������ô�������
     ������ʵ�ָú������ļ����Ե��á����������ļ�include���ͷ�ļ���Ҳ���ܵ������static function��
     ��Ϊ��ʵ���������ļ�������static�ģ��������ɼ������������Ӵ���
     

//���е�static����
1.һ�����а���static member function�����Խ������������һ��ͷ�ļ�����
  static member function��ʵ�ַ��������ļ����档�����Ǿ仰��static member function��������ࡣ
2.��������ͨ��static function����ͨstatic function����������Ͷ���ֿ��Ļ��������ڸ�
  static functionʵ�ֵ��ļ�����ſ��Ե��øú������������ļ�������ã�������include��ͷ�ļ�
  Ҳ��������Ӵ���


extern�ؼ���
��Ҷ�֪����....
����һ����Ҫ���ô����ǣ���C++�������C������������֪��C++֧�ֺ������أ���C�����ǲ�֧�ֺ���
���صġ����غ�����������ĺ����������˺��������⻹�����Ĳ����б��йء�
���������º���

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
    //A a=1;//�������ڹ��캯��ǰ�����explicit�ؼ��ֵ�ʱ���Ǹ������ʽת���Ͳ���ͨ��������
    A a(1,2);//��ʱֻ����ʽ�ĵ��ø���Ĺ��캯��������һ���ࡣ
    A a1;
    a.func();
    A::test1();
    //A::test2();//test����A��private��Ա����������������������A���ڲ�
    cout<<"static var in A, A::x = "<<A::x<<endl;
    A::test3(a);
    static_var_test++;
    cout<<"static var which is define in a header file: "<<static_var_test<<endl;
    static_func_test();
    //static_func_test_another();
    static_func_test_another();

    return 0;
}


