
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
// ===  九、杂项讨论  ===========================================
// --- 条款53：不要轻易忽视编译器的警告 ...
// 注意：
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem
// --- 条款54：让自己熟悉包括TR1(Technical Report 1)在内的标准程序库 ...
//              boost -> tr1  ....
// 注意：
// 1    C++ 标准库的主要机能由 STL、iostream、locales组成。并包含C99标准程序库
// 2    TR1 增加了智能指针(例如 tr1::shared_ptr)、一般化函数指针(tr1::function)、
//      hash-based容器、正则表达式(regular rxpressions)以及另外10个组件的支持 ...
// 3    TR1自身只是一份规范。为获得TR1 提供的好处，你需要一份实物。一个好的实物
//      来源就是 Boost ...
#include <shared_ptr.hpp> //D:\Program Files\Borland\CBuilder6\Include\Boost ...
#include <function.hpp>// std::tr1::function<int (const GameCharacter_3&)  ...
#include <bind.hpp> // std::tr1::bind(...)
#include <scoped_array.hpp> // std::tr1::scoped_array<T> ..
//#include <function_equal.hpp>
namespace std
{
    namespace tr1 = ::boost ;//namespace std::tr1是namespace boost的一个别名 ...
} ;
// --- 条款55：让自己熟悉 Boost ...
// 注意：
// 1    Boost是一个社群，也是一个网站。致力于免费、源码开放、同僚复查的C++ 程序库开发。
//      Boost 在C++ 标准化过程中扮演着深具影响力的角色 ...
// 2    Boost 提供许多TR1组件实现品，以及其他许多程序库。
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
