//C++�е�����ָ�룬�����Ե�ʱ�򾭳��ʵ���һ�����⣬��Ϊ�������ÿһ����ΪԱ������Ӧ��׼���°�
/*
1.���ڱ�������˵��ֻ��ָ����һ��ջ���󣬲���ָ�����ͣ���ջ�����������ڼ���������ʱ��
  ����ָ��ͨ�����������ͷ�������Ķ��ڴ档
2.����ֻ��ָ�붼������operator ->��ֱ�ӷ��ض��������
3.��������ָ���������ָ��������� get() ��������������ָ����һ������
  ����if (my_smart_object)��ԶΪ�棬Ҫ�ж�����ָ�����ָ���Ƿ�Ϊ�գ���Ҫ�����жϣ�
  if (my_smart_object.get())��
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
        ptr2->func();//��ᵼ�³����������ֵ�����ᵼ��ptr1����
        //ptr1->func();
    }//���ɣ���Ҳû�ж��ĵ�delete��
    return 0;
}

/*
1.std::auto_ptr�����ʹ�÷�������Ҫ��auto_ptr��������������ļ�memmory
*/

/*
2.���ȣ�ֻ��ָ���Ǹ����󣬶�����ָ�롣����ָ���˼·�����þֲ�������������������ĳ��
  scope���棬���뿪���scope��ʱ���������ָ��������������Զ����ã�������ָ���
  �����������棬��ʾ��ȥ��������ָ����������Ǹ����������������
*/     

/*
3.auto_ptr�ĳ�Ա����������Ҫ����Ķ����ָ�롣������Ҫע����auto_ptr.release�����Ա����
  �ú����ڷ���������Ķ���ָ���ͬʱ�����Լ��ĳ�Ա������ΪNULL
*/

/*
4.����std::auto_ptrָ��ĸ�����Ϣ�����Դ���������������濴����Ҳ����ʵ���Լ�������ָ��,
  �����ϻ��ǱȽϺ����ġ�
*/


