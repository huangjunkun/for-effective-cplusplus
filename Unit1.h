#ifndef UNIT1_H_INCLUDED
#define UNIT1_H_INCLUDED

// === һ�����Լ�ϰ�� C++ =============================================
// ====================================================================
// --- ����
// ע�⣺
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem
// ====================================================================
// --- ����01����C++ Ϊ�������� ...
// ע�⣺
// 1    C++ ��Ч���������״����C++ ��ش����ԣ����仯��ȡ������ʹ��C++����һ����
// 2    C++ ��������Ҫ�����ĸ���///////////////
//      C
//      Object_Orirnted C++
//      Template C++
//      STL
// 3
namespace testItem01
{
}//namespace testItem01
// ====================================================================
// --- ����02��������const��enum��inline�滻 #define
// ע�⣺
// 1    ���ڵ��������������const ������� enumS �滻 #defineS ������
// 2    �������ƺ����� �꣨mactos������ø���inline(��� template) �����滻 #defineS ...
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
        // #define ���µĴ���  .....
        cout << " Error , use #define  ...\n" ;
        #define MAX_DEFINE(a,b) ((a) > (b) ? (a) : (b))
        int a = 5, b = 0;
        cout << " a = 5, b = 0; MAX_DEFINE(++a, b): " ;
        cout << MAX_DEFINE(++a, b) << "\n" ;// a ��ֵ������2��
        cout << " a: " << a << " ��MAX_DEFINE(++a, b+10) : " ;
        cout << MAX_DEFINE(++a, b+10) << "\n" ; // a ��ֵֻ������1��
        cout << " a: " << a << "\n" ;
        cout << " OKOKOK , use inline template  ...\n" ;
        a = 5, b = 0;
        cout << " a = 5, b = 0; MAX_TEMP(++a, b): " ;
        cout << MAX_TEMP(++a, b) << "\n" ;// a ��ֵ������2��
        cout << " a: " << a << " MAX_TEMP(++a, b+10) : " ;
        cout << MAX_TEMP(++a, b+10) << "\n" ; // a ��ֵֻ������1��
        cout << " a: " << a << "\n" ;
    }
}//namespace testItem02
// ====================================================================
// --- ����03������ʹ�� const ...
// ע�⣺
// 1
// 2
// 3
namespace testItem03
{
}//namespace testItem03
// ====================================================================
// --- ����04��ȷ������ʹ��ǰ�ȱ���ʼ�� ...
// ע�⣺
// 1
// 2
// 3
namespace testItem04
{
}//namespace testItem04
// === ��������/����/��ֵ���� ============================================
// ====================================================================
// --- ����05���˽�C++ ĬĬ��д�����õ���Щ������
//     ��Ĭ�ϣ����캯����������������ֵ���������ƹ��캯��
// ע�⣺
// 1    �����ڿ��԰���Ϊclass ���� default ���캯����copy���캯����copy assignment
//      ���������Լ��������� ...
namespace testItem05
{// .....
}
// ====================================================================
// --- ����06��������ʵ��������Զ����ɵĺ������͸���ȷ�ܾ�
// ע�⣺
// 1    Ϊ���ر������Զ������ԣ��ṩ�Ļ��ܣ��ɽ���Ӧ�ĳ�Ա��������Ϊprivate or protected
//      ���Ҳ���ʵ�֡�ʹ����Uncopyable������base class Ҳ��һ������
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
// --- ����07��Ϊ��̬��������virtual �������� ...
// ע�⣺
// 1    polymorphic����̬�ģ�base class Ӧ������һ��virtual ����������
//      ���class�����κ�virtual��������Ӧ��ӵ��һ��virtual��������
// 2    class �����Ŀ�����������Ϊbase classʹ�ã�����Ϊ�˾߱���̬��
//      �Ͳ�Ӧ������һ��virtual �������� ...
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
// --- ����08�������쳣������������ ...
// ע�⣺
// 1    �����������Բ�Ҫ�³��쳣�����һ���������������õĺ��������׳��쳣��
//      ��ô������������Ӧ�ò�׽�κ��쳣��Ȼ���������ǣ������������ǽ�������...
// 2    ����ͻ���Ҫ��ĳ�����������������׳����쳣������Ӧ����ôclass Ӧ���ṩ
//      һ����ͨ�ĺ�����������ϵ�����У�ִ�иò��� ...
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
// --- ����09������vuz��������������е���virtual ���� ...
// ע�⣺
// 1    �ڹ�������������в�Ҫ����virtual��������Ϊ������ôӲ��½�ֻderived class
//      ������ǰִ�й����������������һ�� class��
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
// --- ����10����operator= ����һ�� referance to *this
// ע�⣺
// 1    �ֵ��assignment������������һ�� reference tio *this ...
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
// --- ����11����operator= �д������Ҹ�ֵ�� ...��ȫ���� ...
// ע�⣺
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
// --- ����12����ֵ����ʱ������ÿһ�ɷ�
// ע�⣺
// 1    copying����һ��ȷ�����ơ������ڵ����г�Ա��������������base class ��Ա(�ɷ�)��
// 2    ��Ҫ������ĳ��copying����ʵ����һ��copying������һ������ͬ���ܣ�������
//      ��װ�ڵ�������(private or protected)�У�����copying������ͬ����...
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
    public: //Ĭ�ϸ��ƹ��캯����Ĭ�ϸ�ֵoperator = ����
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
