#ifndef UNIT1_H_INCLUDED
#define UNIT1_H_INCLUDED

// === 一、让自己习惯 C++ =============================================
// ====================================================================
// --- 条款
// 注意：
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem
// ====================================================================
// --- 条款01：视C++ 为语言联邦 ...
// 注意：
// 1    C++ 高效编程守则视状况（C++ 相关次语言）而变化，取决于你使用C++的哪一部分
// 2    C++ 次语言主要包括四个：///////////////
//      C
//      Object_Orirnted C++
//      Template C++
//      STL
// 3
namespace testItem01
{
}//namespace testItem01
// ====================================================================
// --- 条款02：尽量以const，enum，inline替换 #define
// 注意：
// 1    对于单纯变量，最好以const 对象或是 enumS 替换 #defineS 。。。
// 2    对于形似函数的 宏（mactos），最好改用inline(结合 template) 函数替换 #defineS ...
// 3
namespace testItem02
{
    template <typename T>
    inline T   MAX_TEMP(const T& a ,const T& b)
    { return (a>b ? a : b) ; }
    void exampleFunc()
    {
        cout << " define constant ,using #define ,enum , const Type ... \n" ;
        #define DEFINE_NUM  10
        enum { ENUM_NUM = 10  } ; // ..
        const int CONST_NUM = 10 ;
        cout << " DEFINE_NUM  ENUM_NUM  CONST_NUM :"
             << DEFINE_NUM << setw(5) << ENUM_NUM << setw(5) << CONST_NUM << "\n" ;
        /*
        char    str1[DEFINE_NUM] ; // okokok ...
        char    str2[ENUM_NUM] ;// okokok ...
        char    str3[CONST_NUM] ;// okokok ...
        */
        // #define 导致的错误  .....
        cout << " Error , use #define  ...\n" ;
        #define MAX_DEFINE(a,b) ((a) > (b) ? (a) : (b))
        int a = 5, b = 0;
        cout << " a = 5, b = 0; MAX_DEFINE(++a, b): " ;
        cout << MAX_DEFINE(++a, b) << "\n" ;// a 的值增加了2次
        cout << " a: " << a << " ，MAX_DEFINE(++a, b+10) : " ;
        cout << MAX_DEFINE(++a, b+10) << "\n" ; // a 的值只增加了1次
        cout << " a: " << a << "\n" ;
        cout << " OKOKOK , use inline template  ...\n" ;
        a = 5, b = 0;
        cout << " a = 5, b = 0; MAX_TEMP(++a, b): " ;
        cout << MAX_TEMP(++a, b) << "\n" ;// a 的值增加了2次
        cout << " a: " << a << " MAX_TEMP(++a, b+10) : " ;
        cout << MAX_TEMP(++a, b+10) << "\n" ; // a 的值只增加了1次
        cout << " a: " << a << "\n" ;
    }
}//namespace testItem02
// ====================================================================
// --- 条款03：尽量使用 const ...
// 注意：
// 1
// 2
// 3
namespace testItem03
{
}//namespace testItem03
// ====================================================================
// --- 条款04：确定对象被使用前先被初始化 ...
// 注意：
// 1
// 2
// 3
namespace testItem04
{
}//namespace testItem04
// === 二、构造/析构/赋值运算 ============================================
// ====================================================================
// --- 条款05：了解C++ 默默编写并调用的哪些函数：
//     （默认）构造函数，析构函数，赋值函数，复制构造函数
// 注意：
// 1    编译期可以暗自为class 创建 default 构造函数，copy构造函数，copy assignment
//      操作符，以及析构函数 ...
namespace testItem05
{// .....
}
// ====================================================================
// --- 条款06：若不想实验编译器自动生成的函数，就该明确拒绝
// 注意：
// 1    为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private or protected
//      并且不予实现。使用像Uncopyable这样的base class 也是一种做法
namespace testItem06
{
    class Uncopyable
    {
    protected:
        Uncopyable() {}
        ~Uncopyable() {}
    private:
        Uncopyable(const Uncopyable&) ;
        Uncopyable& operator = (const Uncopyable&) ;
    } ;
    class HomeForSale : private Uncopyable
    { // ...
    } ;
}//namespace testItem06
// ====================================================================
// --- 条款07：为多态基类声明virtual 析构函数 ...
// 注意：
// 1    polymorphic（多态的）base class 应该声明一个virtual 析构函数。
//      如果class带有任何virtual函数，她应该拥有一个virtual析构函数
// 2    class 的设计目的如果不是作为base class使用，或不是为了具备多态性
//      就不应该声明一个virtual 析构函数 ...
// 3
namespace testItem07
{
    class TimeKeeper
    {
    public:
        TimeKeeper() {};
        virtual ~TimeKeeper() {};
        // should virtual for delete pBase ;//destroy exactly
        // ...
    } ;
    class AtomicClock : public TimeKeeper{ } ;// ...
    class WaterClock : public TimeKeeper{ } ;// ...
    class WristClock : public TimeKeeper{ } ;// ...
    class AWOV
    {
    public:
        virtual ~AWOV() = 0 ;
    } ;
    AWOV::~AWOV() {} //must has a defalut definition
}
// ====================================================================
// --- 条款08：别让异常逃离析构函数 ...
// 注意：
// 1    析构函数绝对不要吐出异常。如果一个呗析构函数调用的函数可能抛出异常，
//      那么在析构函数内应该捕捉任何异常，然后吞下它们（不传播）或是结束程序...
// 2    如果客户需要对某个操作函数运行期抛出的异常做出反应，那么class 应该提供
//      一个普通的函数（而非在系后函数中）执行该操作 ...
// 3
namespace testItem08
{
    class DBConnection
    {
        // ....
    public:
        void start() {}
        void close() {}
        // ....
    } ;
    class DBConn
    {
    private:
        bool   bClose_ ;
        DBConnection db ;
    public:
        void start() //
        {
            db.start() ;
            bClose_ = false ;
        }
        void close() // better ....note 2
        {
            db.close() ;
            bClose_ = true ;
        }
        ~DBConn()// better ....
        {
            if(!bClose_)
            {
                try
                {
                	db.close() ;
                }
                catch(...)
                {// better ....note 1
                    handleError() ;// or: db.close() again ...
                    bClose_ = false ;
                }
            }
        }
    protected:
        void handleError() {} // ...
    } ;
}//namespace testItem08
// ====================================================================
// --- 条款09：绝不vuz构造和析构过程中调用virtual 函数 ...
// 注意：
// 1    在构造和析构过程中不要调用virtual函数，因为这类调用从不下降只derived class
//      （比起当前执行构造和析构函数的那一次 class）
// 2
// 3
namespace testItem09
{
    class Transaction_Bad
    {
    private:
        int     value_ ;
    public:
        Transaction_Bad() ;
        virtual void logTransaction_Bad() const = 0 ;
    } ;
    Transaction_Bad::Transaction_Bad()
    {   // ...
        //logTransaction_Bad() ; // warn !!! or error
    }
    void Transaction_Bad::logTransaction_Bad() const
    { std::cout << "  virtual void Transaction_Bad::logTransaction_Bad() const\n" ; }
    class BuyTransaction_Bad : public Transaction_Bad
    {
    public:
        //BuyTransaction_Bad():Transaction_Bad() {}
        virtual void logTransaction_Bad() const
        { std::cout << "  virtual void BuyTransaction_Bad::logTransaction_Bad() const\n" ; }
    } ;
    class SellTransaction_Bad : public Transaction_Bad
    {
    public:
        //BuyTransaction_Bad():Transaction_Bad() {}
        virtual void logTransaction_Bad() const
        { std::cout << " virtual void SellTransaction_Bad::logTransaction_Bad() const\n" ; }
    } ;
    // --------------
    class Transaction_Good
    {
    public:
        explicit Transaction_Good(const std::string& logInfo)  ;
        void logTransaction_Good(const std::string& logInfo) const  ;//non-virtual
    } ;
    Transaction_Good::Transaction_Good(const std::string& logInfo)
    {
        // ...
        logTransaction_Good(logInfo) ; // warn !!!
    }
    void Transaction_Good::logTransaction_Good(const std::string& logInfo) const
    {
        std::cout << " void Transaction_Good::logTransaction_Good(const std::string& logInfo) const\n"
                  << " logInfo: " << logInfo << "\n" ;
    }
    class BuyTransaction_Good : public Transaction_Good
    {
    private:
        static string createLogStr(int index)
        { return " static string BuyTransaction_Good::createLogStr(int index)" ; }
    public:
        BuyTransaction_Good(int index):Transaction_Good(createLogStr(index))
        {} // ...
        virtual void logTransaction_Good() const
        { std::cout << " virtual void BuyTransaction_Good::logTransaction_Good() const\n" ; }
    } ;
    class SellTransaction_Good : public Transaction_Good
    {
    private:
        static string createLogStr(int index)
        { return " static string SellTransaction_Good::createLogStr(int index)" ; }
    public:
        SellTransaction_Good(int index):Transaction_Good(createLogStr(index))
        {} // ...
        virtual void logTransaction_Good() const
        { std::cout << " virtual void SellTransaction_Good::logTransaction_Good() const\n" ; }
    } ;
}//namespace testItem09
// ====================================================================
// --- 条款10：令operator= 返回一个 referance to *this
// 注意：
// 1    令赋值（assignment）操作符返回一个 reference tio *this ...
namespace testItem10
{
    class Widget
    {
    private:
        int value_ ;
    public:
        //Widget():value_(0) {} // ... or remove
        Widget(int v=0):value_(v) {}
        Widget& operator = (const Widget& rhs) ;
        Widget& operator += (const Widget& rhs) ;
        void printW()
        { std::cout << " Widget::value_: " << value_ << "\n" ; }
        // ...
    } ;
    Widget& Widget::operator = (const Widget& rhs)
    {
        value_ = rhs.value_ ;
        return *this ;
    }
    Widget& Widget::operator += (const Widget& rhs)
    {
        value_ += rhs.value_ ;
        return *this ;
    }
}
// ====================================================================
// --- 条款11：在operator= 中处理“自我赋值” ...安全处理 ...
// 注意：
// 1
// 2
// 3
namespace testItem11
{
    class Bitmap
    {
    private:
        int     value_ ;
    public:
        Bitmap():value_(11111) {}
        void print()
        {
            std::cout << " void Bitmap::print()\n"
                      << " Bitmap::value_: "<< value_ << "\n" ;
        }
    } ;
    class Widget
    {
    private:
        Bitmap* pb ;
        void swap(Widget& rhs) ;
    public:
        Widget() { pb = new Bitmap() ; }
        Widget(const Widget& rhs) { pb = new Bitmap(*rhs.pb) ; }
        Widget operator = (const Widget& rhs) ;
        void print()
        { std::cout << " void Widget::print()\n" ; pb->print() ; }
    } ;   /*
    // 1111111111111111111111
    Widget Widget::operator = (const Widget& rhs)
    {
        if(this==&rhs) return *this ;
        delete pb ;
        pb = new Bitmap(*rhs.pb) ;
        return *this ;
    }
    // 2222222222222222222222
    Widget Widget::operator = (const Widget& rhs)
    {
        Bitmap* pOrig = pb ;
        pb = new Bitmap(*rhs.pb) ;
        delete pOrig ;
        return *this ;
    }  */
    // 3333333333333333333333
    void Widget::swap(Widget& rhs)
    {
        Bitmap* temp = pb ;
        pb = rhs.pb ;
        rhs.pb = temp ;
    }
    Widget Widget::operator = (const Widget& rhs)
    {
        Widget temp(rhs) ;
        swap(temp) ;
        return *this ;
    }
    /* or : ....
    Widget Widget::operator = (Widget rhs)
    {
        swap(temp) ;
        return *this ;
    }

    */
}//namespace testItem11
// ====================================================================
// --- 条款12：赋值对象时勿忘其每一成分
// 注意：
// 1    copying函数一个确保复制”对象内的所有成员变量“及”所有base class 成员(成分)“
// 2    不要尝试以某个copying函数实现另一个copying函数。一个将共同机能（操作）
//      封装在第三个函(private or protected)中，并由copying函数共同调用...
// 3
namespace testItem12
{
    class PureVirClassAble
    {
    public:
        virtual ~PureVirClassAble() = 0 ;
    } ;
    PureVirClassAble::~PureVirClassAble() {}
    class Human : public PureVirClassAble // ... good
    {
    private:
        string name ;
        short  age ;
        Human* assoHumans ;
        // ...
    public: //默认复制构造函数，默认赋值operator = 函数
        Human(const string& name ,short age ,Human* s=NULL)
        :name(name) ,age(age) ,assoHumans(s) {} // two names same okokok ...
        virtual ~Human() {} // ...
        friend ostream& operator << (ostream& os ,const Human& rhs) ;
        // ...
    protected:
        Human() {}
    } ;
    ostream& operator << (ostream& os ,const Human& rhs)
    {
        os << " print Human::name ,age ,assoHumans ... \n" \
           << " name: " << rhs.name << ",age: "<< rhs.age << (rhs.assoHumans!=NULL ? " ,assoHumans..." : " ,NULL") << "\n" ;
        return os ;
    }
    class Customer : public Human
    {
    private:
        std::string nickname_ ;
        int         userID_ ;
        string      email_ ;
        // ...
        void copyNewVariable(const Customer& rhs)
        {
            nickname_ = rhs.nickname() ;
            userID_ = rhs.userID() ;
            email_ = rhs.email() ;
            // ...
        }
    public:
        string nickname()const { return nickname_ ; }
        int userID()const { return userID_ ; }
        string email()const { return email_ ; }
    protected:
        Customer():Human() {} // ...
    public:
        Customer(const string& nname ,int ID ,const string& email ,\
                 const string& name ,short age ,Human* assoHumans=NULL)
        :Human(name ,age ,assoHumans) , \
         nickname_(nname) , userID_(ID),email_(email)
        { } // ...
        Customer(const Customer& rhs):Human(rhs)// ...
        {  copyNewVariable(rhs) ; }
        Customer& operator = (const Customer& rhs)
        {
            Human::operator=(rhs) ;
            copyNewVariable(rhs) ;
            return *this ;
        }
        static Customer* ctreateEmptyCustomer() ;
        friend ostream& operator << (ostream& os ,const Customer& rhs) ;
    } ;
    Customer* Customer::ctreateEmptyCustomer()
    {
        return (new Customer) ;
    }
    ostream& operator << (ostream& os ,const Customer& rhs)
    {
        os << static_cast<Human>(rhs) ; //or:(Human)rhs  ....
        os << " print Customer::nickname_ ,userID_ ,email_ ... \n" \
           << " nickname_: " << rhs.nickname_<< " ,userID_: " <<rhs.userID_
           << " ,email_: " << rhs.email_<< "\n" ;
        return os ;
    }
}//namespace testItem12
// ====================================================================
#endif // UNIT1_H_INCLUDED
