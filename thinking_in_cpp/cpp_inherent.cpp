//C++��public��private��protected���Լ��̳У���̬�����Ϻ��������ͣ��麯��
//��ʱ�������˶���

//public�ؼ��֣���ʾ��Ա�����ͳ�Ա�����������������������
//protected�ؼ��֣���ʾֻ�и����Լ�������������Է���
//private�ؼ��֣���ʾֻ�и����Լ����Է���




//�̳У�A���࣬B������
/*public�̳�
1.B���A�����õĶ���
2.A��private��Ա�������ߺ���������B����������--ֱ��--���ʣ�Ӧ��ͨ��A�ĳ�Ա������ʹ��
3.A�е�public�Ķ���������B��ֱ�ӷ��ʣ�������ⲿ��Ҳ����ֱ�ӷ���B��A�̳й���
  ��public�ĳ�Ա�����ͳ�Ա����
4.A��protected�ĳ�Ա�����ͳ�Ա�������̳е�B�к���Ȼ��protected�ģ�������B����ֱ�ӷ��ʣ�
  ���ǲ�����B����ⲿֱ�ӷ���
5.A��private��Ա�����ͳ�Ա��������B����Ȼ���ڣ����ǲ�����B��ֱ�ӷ��ʣ�Ӧ��ͨ��A�ṩ�ĳ�Ա
  ����ȥ���ʻ����޸�
*/

/*protected�̳�
1.A�е�public��Ա�����ͳ�Ա������B�н����protected��
2.A��protected�ĳ�Ա�����ͳ�Ա������B����Ȼ��protected��
3.A��private��Ա�����ͳ�Ա��������B����Ȼ���ڣ����ǲ�����B��ֱ�ӷ��ʣ�Ӧ��ͨ��A�ṩ�ĳ�Ա
  ����ȥ���ʻ����޸�

*/
/*private�̳�
1.A�е�public��protected�����private��
2.A��private��Ա�����ͳ�Ա��������B����Ȼ���ڣ����ǲ�����B��ֱ�ӷ��ʣ�Ӧ��ͨ��A�ṩ�ĳ�Ա
  ����ȥ���ʻ����޸�
*/




/*�����֮������
������ �̳з�ʽ ������

public �� public�̳� => public

public �� protected�̳� => protected

public �� private�̳� = > private



protected �� public�̳� => protected

protected �� protected�̳� => protected

protected �� private�̳� = > private



private �� public�̳� => ������Ȩ����

private �� protected�̳� => ������Ȩ����

private �� private�̳� = > ������Ȩ����

*/
/*
��������Ͻ�����Կ���

1��public�̳в��ı�����Ա�ķ���Ȩ��

2��private�̳�ʹ�û������г�Ա�������еķ���Ȩ�ޱ�Ϊprivate

3��protected�̳н�������public��Ա��Ϊ�����protected��Ա��������Ա�ķ��� Ȩ�޲��䡣

4�������е�private��Ա���ܼ̳з�ʽ��Ӱ�죬������Զ��Ȩ���ʡ�
*/


//public�̳к�protected�̳е���ⶼ���Զ��׼���
//�����ص��о���private�̳�

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
        A::aprintk();//������private�̳У�A�����ж�����B�ж����private���ˡ�
    }

};

int main(int argc, char** argv)
{
    B b(1,2,3);
    b.bprintk();
    //˵��A�е�private��Ա����k��B����Ȼ����,����a��aprintk�����Ѿ����private���ˣ�
    //������main����ֱ�ӵ����ˣ�������Ȼ������B����ʹ�ã���ֻ��ͨ��A�ṩ��public����protected������ʹ��

    return 0;
}
#endif
//��������(up-cast)
//1.���ȷ���class�Ĵ�С�Ǻͳ�Ա����û�й�ϵ��
//2.����������ĳ�Ա������������͸�������ĳ�Ա����������ͬ�Ҳ����б�Ҳ��ͬ�Ļ�������name hiding��
//��Bֻ�ܿ����Լ�set(������)��������B����Ȼ������ʽ�ĵ��õ���A��set����
//3.������ĳ�Ա���������ֿ��Ժ͸���ĳ�Ա����������ͬ
//4.���Խ�������up cast��һ�����࣬�����Ǿ��԰�ȫ�ġ����仰˵��B isa A��up-castֻ�ǽ�B����A����
//5.��Ȼ���������ͣ���ô��û�����������أ�����û�С����Ҫ��ôд����ᷢ���������
//��A����������Ϊһ��B��C���������ᱨ��:no matching function for call to C::C(A&);
//�������������Ϣ������Ȼ��ֻҪ����ʵ��C::C(A&)����ô���ǾͿ����������������
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
    cout<<sizeof(A)<<endl;//��������4��
    cout<<sizeof(a)<<endl;//��������4
    a.func();
    a.set(10);
    a.func();
    //��˵��ÿ����ĳ�Ա��������������������Ĵ�С����


    B b(10,11);
    cout<<sizeof(B)<<endl;//��������8��
    cout<<sizeof(b)<<endl;//��������4
    b.func();
    b.set(5, 6);
    b.func();
    b.set(3);
    b.func();

    A a1 = (A)b;
    cout<<sizeof(a1)<<endl;//��������4
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

    e->func();//����һ�����ֵ

    E e1 = a;
    e1.func();
    return 0;
}

#endif



//virtual�ؼ���

/*1.�麯������������һ����������Ϊvirtual����ô����߱��������ø�������ཫӵ���Լ���virtual function��*/
/*2.֮ǰ��up-cast�ķ������濴������������һ�������͸����һ�������ĺ������Ͳ����б�һ���Ļ�
    ������name hiding������������������Ȼ������ʾ�ĵ��ø���ĺ��������Ҹ���������������������û���κι�ϵ��
    ֻ�����ڵ����ֿռ䲻һ������*/
/*3.���������ĺ�������Ϊvirtual�ģ���ô����߱�����������ĸú�������virtual��*/

//ΪʲôҪ����virtual������? ���Ƕ�̬����̬������oop��������Ϊ��Ҫ��һ�����

/*1.���һ������funcʹ�ø����ָ�����������Ϊ�βΣ���ʵ��ʹ�õ�ʱ�򣬴����ʵ���������ָ���������,
    ��func�ڵ���virtual�ĺ�����ʱ��������������ֱ���ø��Ե�virtual������
  2.������̣�ֻ�������е�ʱ��Ż�ʵ�֣��ֽ�����̬�󶨡�
  3.��̬��ָ��ָ����������Ƕ�̬(polymorphism)�ġ�
*/

//ΪʲôҪ��������������Ϊvirtual��?�𰸻��Ƕ�̬
/*1.�����ĳ�������Ĳ����ǻ����ָ��������ã��������ڶ�̬��ԭ�򣬴���ȥ��ʵ���������ָ�����
    ���ã���ô�ڸú�������delete p��ʱ�򣬼���������������virtual�ģ���ô���õĽ��ǻ������������
    �������������ڴ�й¶��
*/


//��C++�⣬����oop���Զ��Ƕ�̬�󶨵ġ�ԭ����C++׷��Ч�ʡ���Ϊ��̬��ʵ�ڱ���ʱ����ɵġ�


//��̬��ʵ��
/*
1.�������virtual������ռ���ڴ档��һ�������溬��virtual������ʱ��
  ����Ķ�����ڴ����ʼ������һ�ű���Ӧ��ʵ�ֵ�virtual������ʵ���Ͼ���һ������ָ���table
  ������ͬ��Ĳ�ͬ�����virtual function table��һ����

2.����������û��ʵ�ָø���virtual�����������������ĸú����͸���һ�������̳й����ġ�

3.ÿ���඼��һ��virtual function table�����е�ʱ��ֻҪ�����õ���ָ��ƫ�Ƶ���Ե�λ��
  �Ϳ����ҵ���ȡ�ĺ������á������������ϵ���ָ����ָ��ʲô��ġ�
*/
//����̬������������
/*
1.B��A��һ�����࣬��B��up cast��A������virtual func����Ȼ��A��virtual function��
  ��Ϊʹ�ø�ֵ������=�������ÿ������캯�����������캯���ǰ��ճ�Ա�����ġ�virtual function table�ǲ��ᱻ���ǵġ�
2.��Ӧ�������B���ָ��ǿתΪA��ָ�룬��ô���õĽ���B��virtual function
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
        B():A(0,0)//ֻ��ͨ����ʼ���б�ķ������ø���Ĺ��캯��
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

void out_func(A* const a)//�����������˵���Ҿ��Բ���ı����ֵ�����ǵ���a.func��ʱ�򣬷�������û��const���η���ʱ�򣬻ᵼ�±������
{
    a->func();
    return;
}


int main(int argc, char** argv)
{
    /*
    A a(10,10);
    cout<<sizeof(A)<<endl;//��������8����Ϊvirtual function table�Ĵ��ڣ�32λ��������Ҫ��4���ֽ�
    cout<<sizeof(a)<<endl;//��������8
    a.func();
    B b;
    cout<<sizeof(B)<<endl;//��������8
    cout<<sizeof(b)<<endl;//��������8
    b.func();


    A a1(10,10), a2(11, 11);
    int *p = (int*)&a1;
    int *q = (int*)&a2;

    cout<<*p<<"  "<<*q<<endl;
    //*p��*q��ֵ��һ���ģ��ɼ���ͬ��Ĳ�ͬ���󣬶�Ӧ���Ǹ�virtaul function table��һ����

    int *x = (int*)*p;//����Ϊ�˲鿴virtual function���ڴ��е�λ��
    cout<<"pos = "<<x<<endl;

    B b1;

    B *b2 = new B();

    delete b2;
    //A a4 = b1;//���ﲻ�����A�Ĺ��캯�������嶯����������ջ�ڴ棬��СΪA��Ȼ��B���ڴ濽����a4
              //������˳�������ʱ����Ȼ�����A������������

    //a4.func();//���õ���Ȼ��a��func

    */
    B b1;
    A *a3 = &b1;
    b1.func();
    a3->func();//������ý���b�ĺ�������Ϊ�������캯��ʽ���ճ�Ա�����ġ��������ǵ�ַ��ֱ��ת��

    //out_func(a);
    B b5;
    out_func(&b5);
    return 0;
}
//#endif


//��������̳�









