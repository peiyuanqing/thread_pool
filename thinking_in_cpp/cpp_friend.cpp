//C++��Ԫ��������Ԫ��������Ԫ��
//C++��Ԫ����




//C++��Ԫ��
/*
��ĳ����A����������һ����BΪ����Ԫ���ʱ����ô��B�п��Է���A��private����
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


//����������׼����һЩа������飬����C�༴ʹA�������࣬����A��friend class����ô����?
//let's have a try
//����֪����ʹC��A�������࣬��C����Ҳ���ܷ���������private��Ա��
//��ô���һ����������������࣬��������friend class�Ļ����ᷢ��ʲô����˼��������?
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



//���Ƕ���һ����Ԫ����
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
    cout<<"sizeof(B) = "<<sizeof(B)<<endl;//���������B�Ĵ�С��1���ֽڣ��ǲ��Ǻ����?��֪��C++���ʲô
    cout<<"sizeof(A) = "<<sizeof(A)<<endl;//���������Ȼ��4���ֽڣ���һ��int�Ĵ�С��˵����A��������һ����Ԫ�����ᵼ��A��������
    cout<<"sizoef(C) = "<<sizeof(C)<<endl;
    b.func(a);

    C c(1,2);
    c.func(a);
    //c.func();//���ｫ����name hiding������֮ǰ�����ģ��ᵼ�±���ʧ��

    friend_func(a);//������A��������friend_func��A����Ԫ��������ô��������Ϳ��Է���A�е�private��Ա

    //�����Ǹɵ�̼��Ķ����ɣ�����Ԫ����up_cast������? ��������һ�� = =!
    friend_func(c);//��ȫû�����⣬���Ƿ��ʵ���C����Ķ�����ʵ���ϴӸ�����˵�����ǻ��Ƿ��ʶԵ���A����Ķ���

    //�������ָ���up_cast�ᷢ��ʲô��?��һ�Ա�֪�� + +
    friend_func_pointer(&a);

    friend_func_pointer((A*)&c);//Ҳ��ȫû������
    
    return 0;
}


/*
������Ԫ��һЩ��Ҫע��ĸ���
(1) ��Ԫ��ϵ���ܱ��̳С� B��A����Ԫclass��C��A�����࣬����B����C����Ԫ��
    ��һ��Ҳ�ܺ���⡣�ӷ�װ�ԵĽǶȿ��ǣ���Ԫclass B���Է���A��private���ݣ����ǲ�Ӧ�ÿ���
    �������private��������A��������������˵������Ԫclass B�ˡ�

(2) ��Ԫ��ϵ�ǵ���ģ������н����ԡ�����B����A����Ԫ����A��һ������B����Ԫ��Ҫ���������Ƿ�����Ӧ��������
    �����������ˣ�A˵:B�������ҵ���Ԫ���ҵ����ж��������Ը��㿴��
    ����B˵:�ð�����һ����Ը����Ҳû�а취�������ҵĶ������ǲ��ܸ��㿴��

(3) ��Ԫ��ϵ�����д����ԡ�
    ��һ��Ҳ�ȽϺ���⣬����B��A��friend class�� A����D����Ԫ��
    ��ôB���Կ���A��private��A�п��Կ���D��private������B��Ӧ��ֱ�ӿ���D��private��
    �򵥵����Ӿ��ǣ������ѵ����Ѳ�һ����ʶ���

*/

//��Ԫ��������ָ����������ⲿ�����ǿ���ֱ�ӷ������private��Ա�ĺ���
//���ǻ��������������������Ӱ�


/*
�ܽ�:
1.һ���֣���
2.������Ϊfriend class��friend function�ƻ���oop���Եķ�װ���ԡ�
3.�����������������Կ�������friend function������up_cast��ʱ��friend function�ƻ���
  ����������ݡ�
4.any way���Ҿ��û��ǲ����򲻵��ѵ�����£���Ҫ��friend class��friend function�ɡ�
  �Ͼ��ڱ��˲���֪����������Զ����˵ĵ׿���һ�ֲ�����������

*/


