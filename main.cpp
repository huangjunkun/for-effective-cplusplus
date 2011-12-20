
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
//#include <exception>
#include <stdexcept> // logic_error
using namespace std;

#include <function.hpp>
//using namespace boost ;
/**/
// ===  �š���������  ===========================================
// --- ����53����Ҫ���׺��ӱ������ľ��� ...
// ע�⣺
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem
// --- ����54�����Լ���Ϥ����TR1(Technical Report 1)���ڵı�׼����� ...
//              boost -> tr1  ....
// ע�⣺
// 1    C++ ��׼�����Ҫ������ STL��iostream��locales��ɡ�������C99��׼�����
// 2    TR1 ����������ָ��(���� tr1::shared_ptr)��һ�㻯����ָ��(tr1::function)��
//      hash-based������������ʽ(regular rxpressions)�Լ�����10�������֧�� ...
// 3    TR1����ֻ��һ�ݹ淶��Ϊ���TR1 �ṩ�ĺô�������Ҫһ��ʵ�һ���õ�ʵ��
//      ��Դ���� Boost ...
#include <shared_ptr.hpp> //D:\Program Files\Borland\CBuilder6\Include\Boost ...
#include <function.hpp>// std::tr1::function<int (const GameCharacter_3&)  ...
#include <bind.hpp> // std::tr1::bind(...)
#include <scoped_array.hpp> // std::tr1::scoped_array<T> ..
//#include <function_equal.hpp>
namespace std
{
    namespace tr1 = ::boost ;//namespace std::tr1��namespace boost��һ������ ...
} ;
// --- ����55�����Լ���Ϥ Boost ...
// ע�⣺
// 1    Boost��һ����Ⱥ��Ҳ��һ����վ����������ѡ�Դ�뿪�š�ͬ�Ÿ����C++ ����⿪����
//      Boost ��C++ ��׼�������а��������Ӱ�����Ľ�ɫ ...
// 2    Boost �ṩ���TR1���ʵ��Ʒ���Լ�����������⡣
// 3
#include "Unit1.h"
//#include "Unit2.h"
//#include "Unit3.h"
#include "Unit4.h"
// for test boost::function<...> ...
void print()
{
    cout << " void print() ...\n" ;
}
//# pragma warning(push)
//# pragma warning(disable)
int main()
{/*
    {// test --- sonmething ....
        int     i = 10 ,j = 20 ;
        int&    iRef = i ;
        //cout << " i ,j ,iRef: " << " \n" ;
        printf(" i ,j ,iRef: %d ,%d ,%d\n" ,i ,j ,iRef) ;
        iRef = j ;
        printf(" i ,j ,iRef: %d ,%d ,%d\n" ,i ,j ,iRef) ;
        boost::function<void ()> func(print) ; // for BCB error ....
        func() ;
    }
    {//
    cout << " test using namespace testItem ;\n" ;
    using namespace testItem ;
    } */
    {
    cout << " test using namespace testItem02 ;\n" ;
    using namespace testItem02 ;
    exampleFunc() ;
    }
/*
    {
    cout << " test using namespace testItem46 ;\n" ;
    using namespace testItem46 ;
    exampleFunc() ;
    }
/*
    {//
    cout << " test using namespace testItem45 ;\n" ;
    using namespace testItem45 ;
    exampleFunc() ;
    }
    /*=================================*/
    cout << " Hello world!" << endl;
    //cin.get() ;
    return 0;
}
//# pragma warning(pop)
