
//C++�����ռ�

//C++�����ռ���һ���߼��������


namespace Parse
{
    double expr(int);
    double func(int);
    //using namespace::std;//�ڶ���һ�������ռ䣬���滹����������һ���Ѿ����ڵ������ռ�
    std::String;
}

//��������ʵ�ַֿ������ԺܺõĿ��������ռ�Ľṹ
double Parse::expr(int m)
{
    int x = m*m;
    return func(x);//������ú�exprͬһ�������ռ�ĺ���func����Ҫ��ָ�������ռ���(���޶���)
}


//�����ռ�ı���

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


/*�����ռ�Ĳ���*/
//�����ʹ��һ�������Ļ������Ҳ����ú�������ȥ�ú����Ĳ����������ռ�ȥ����

/*�����ռ�����*/

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

//int C::func(int), �����ǲ��е�
//������
int A::func(int i)
{
    /**/
}
//�����ǵ���C����ȥ����ʾ��ĳ�����֣�����Ҳ������������ͻ�ȥ�鿴ָ���ᵽ��
//�����ռ�ȥ�ң�����Ҫ���嶥һ��������ʱ�������������ռ��ϸ�ƥ��

//�����ռ��ǿ��ŵģ�����ͨ����������ռ�����������֣��������������
//�����ռ����func��Ҳ��gunc
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
    C::TEST test;//������ok��
    return;
}



 

 
 
 
