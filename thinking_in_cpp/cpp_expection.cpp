#include <iostream>
#include <string>
using namespace std;

//�쳣�����ǿ��Դ���ģ����Ҳ�Ӧ���Ǵ�����Ե��ֶ�
//�󲿷ֹ�˾�ǽ�ֹʹ���쳣�ģ�ԭ����C++����Ա�����ʲβ��.....

//�쳣�Ĳ���ʽ
try
{

}catch(...)//��׽�����쳣�����ǵò����쳣����

//�쳣�Ļ�ȡ˳��,������д��˳��
//��ÿһ��catch���水����������������catch�쳣
/*
1.�����Ƿ�����ȫƥ����쳣
2.�����Ƿ������ת�����쳣ƥ��
3.�Ƿ���ellipse����...ƥ��
*/

//��������ת����������Ҫ��
/*
1.    ����ӷǳ���ת��������������ת����
2.    ����������ൽ�����ת����
3.    �������鱻ת����Ϊָ�����飨Ԫ�أ����͵�ָ�룬������ת����ָ��ú������͵�ָ�롣
4.    ��׼�������͵�ת�������磺��bool�ͺ�char��ת����int�ͣ�
      ��������ת��(ʹ���������ת���������ת�����캯��)��
*/

//�����׳��쳣�ĺ���д��
//��ʾ��������������׳�һ�¼����쳣�����������func�����ģ������Ǻ����ĵ�����
#ifdef __CPP_EXCEPION
int func(int a) : throw(exception1, exception2, exception3)
{
    
}
//��ʾfunc�����׳��κ��쳣
int func(int a)
{

}
//��ʾ���׳��κ��쳣
int func(int a) : throw()
{

}

//���캯���е��쳣
//C++��new�������һ��NULL,�����׳�һ���쳣
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
    //C++�Ļ������������ڴ棬Ȼ��ȥ���ù��캯������ʱA���ڴ��Ѿ����䡣��������׳��쳣��ϵͳ�Ὣ�ⲿ���ڴ����
    //����A�Ĺ��캯���׳��쳣֮ǰnew��������һƬ�ڴ潫���ᱻ�ͷ�
    //����û����ɣ������������ᱻ����
    delete a;

    return 0;
}


//��ȷ�Ĵ�����
int func()
{
    try
    {
        A *a = new A();
        //�׳����쳣�ڴ�λ��ջ�������ᱻ���١�
        //����׳����쳣ʱnew�����ģ���ôcatch��Ӧ����ʾ��delete���쳣
    }
    catch(exceptionxx &)
    //����ǵ�һ�����������catch��ʱ�������һ������
    //ֱ���õ��Ǹ��쳣���������������ᷢ����������
    //����ǵڶ��������throwһ���쳣�����ָ�룬
    //������catch�쳣�����ָ�룬�������쳣���ֶ�����delete��
    {
        do something;
    }
    delete a;

    return 0;
}
//�����๹�캯���е��쳣
int func()
{
    try
    {
        B *b = new B();
        //1.����B���ڴ�
        //2.����B�Ĺ��캯��
        //3.����A�Ĺ��캯��,��ʼ��A
        //4.����ִ��B�Ĺ��캯�����������쳣�׳�����ֹ���캯��
        //5.����A����������������class A;
    }
    catch(exceptionxxx)
    {
        do something;
        //����B�����Ѿ�new��һƬ�ڴ棬��������Ҫ���ֶν����ͷ�
        //Ψһ�Ľ���취�ǣ����׳��쳣֮ǰ��������������ڴ��ֶ��ͷŵ�
        //�������ڹ��캯���ڲ�����try catch��Ȼ���ֶ��ͷ��ڴ�
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



//��׼�쳣

/*
�����׳�
bad_alloc, throw: new
bad_cast, throw: dynamic_cast

bad_typed, throw: typeid

bad_exception, throw: �쳣����



��׼���׳�
out_of_range    throw: at()
invalid_argument throw: ��λ���ù��캯��
overflow_error throw: throw: bitset<>::to_ulong



*/



