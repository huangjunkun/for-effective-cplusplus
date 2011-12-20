#ifndef UNIT2_H_INCLUDED
#define UNIT2_H_INCLUDED

// === 三、资源管理 =================================================
// --- 条款13：对对象管理资源 ...
// 注意：
// 1    为防止资源泄露，请使用RAII对象，它们在构造函数中获得资源并在析构函数中释放资源
// 2    两个常被使用是RAII classed 分别是tr1::shareed_ptr 和 auto_ptr 。前者通常是较佳的
//      选择,因为其copy行为比较直观。若选择auto_ptr ，复制动作会使它（被复制物）指向null ...
// 3
namespace testItem13
{
    class Investment
    {
    private:
        int value_ ;
        int objectID_ ;
        static int objectNUM_ ; // or ...
    public:
        Investment() : value_(999) ,objectID_(++objectNUM_)
        { cout << " Investment::Investment() ,objectID_: "<< objectID_<<"\n" ; }
        ~Investment()
        { cout << " Investment::~Investment() ,objectID_: "<< objectID_<<"\n" ; }
        void showInv()
        { cout << " void showInv() ... value_: " << value_ << "\n" ; }
    } ;
    int Investment::objectNUM_ = 0 ;
    Investment* createInvestment() { return new Investment ; }
    void Foo()
    {
        std::auto_ptr<Investment> pInv1(createInvestment()) ;
        // ... no need delete pInv ;
        cout << " pInv2 = pInv1 ;and " ;
        auto_ptr<Investment>    pInv2 = pInv1 ;
        if(pInv1.get()==NULL)
            cout << " pInv1 == NULL \n" ;
        else
            cout << " pInv1 != NULL \n" ;
        pInv2->showInv() ;
        cout << " pInv2.reset(createInvestment()) ;and then ... \n" ;
        pInv2.reset(createInvestment()) ;

    }
}//namespace testItem13

// --- 条款14：在资源管理类中心小心copying 行为 ...
// 注意：RAII（Resource Acquisition Is Initialization）资源取得时机即是初始化时机....
// 1    复制RAII对象必须一并复制它所管理的资源，所以资源的coping行为决定RAII对象的copying行为
// 2    普遍而常见的RAII class copying行为时：御制copying、施行引用计数法（reference counting）。
//      不过其他行为也可能被实现 ...
// 3
namespace testItem14
{
  class Mutex
  { /*...*/ } ;
  void lock(Mutex* m) {} ;// ...
  void unlock(Mutex* m) {} ;// ...
  class Lock
  {
  private:
      Mutex* MutexPtr ;
  public:
      explicit Lock(Mutex* pm)
      : MutexPtr(pm)
      { lock(MutexPtr) ; }
      ~Lock() { unlock(MutexPtr) ; }
  } ;
}//namespace testItem14

// --- 条款15：在资源管理类中提供对原始资源的访问 ...
// 注意：
// 1    APIs往往要求访问原始资源（raw resouces），因此对于每一个RAII class 应该提供一个“取得
//      其所管理之资源”的办法 ...
// 2    对原始资源的访问可能经由显式转换或是隐式转换，一般而言显式转化比较安全，但隐式转化对于用户比较方便 ...
// 3
namespace testItem15
{
    class FontHandle
    {
    public:
        FontHandle(int i = 0) {}
    } ;// ...
    FontHandle getFont()
    { return FontHandle(0) ; }
    void releaseFont(FontHandle& f)
    { f = FontHandle(0) ; } //...
    class Font
    {
    private:
        FontHandle fh_ ;
    public:
        explicit Font(FontHandle fh) : fh_(fh)
        { } // ...
        ~Font() { releaseFont(fh_) ; }
        // 显式转化
        FontHandle get() const { return fh_ ; }// safely ,better ...
        // 隐式转换 ...
        //operator FontHandle() const { return fh_ ; } // no safe ...
    } ;
}//namespace testItem15
// --- 条款16：成对使用new 和 delete 时采用相同形式 ...new-delete ,new[]-delete[]
// 注意：
// 1    如果你在表达式中使用[] ，必须在相应的delete表达式中使用[]。反之亦然 ....
// 2
namespace testItem16
{
    class Widget
    {
    public:
        Widget() { cout << " Widget::Widget() ... new Widget ... \n" ; }
        ~Widget() { cout << " ~Widget::Widget() ... delete pWidget ...\n" ; }
        void print() { cout << " void Widget::print() ... \n" ; }
    } ;
    void warnFuncDemo()
    {
        typedef std::string AddressLines[4] ;
        std::string* pStr = new AddressLines ;
        // delete pStr ;// 行为有定义 ....WARN !!!
        delete[] pStr ;//  很好 ....
        cout << " Widget* pWidget = new Widget ;,and then ... \n" ;
        Widget* pWidget = new Widget ;
        cout << " delete pWidget ;,and then ... \n" ;
        delete pWidget ;
        // delete[] pWidget ; // error ...
        cout << " pWidget = new Widget[4] ;,and then ... \n" ;
        pWidget = new Widget[4] ;
        cout << " delete[] pWidget ;,and then ... \n" ;
        delete[] pWidget ;
        // delete pWidget ; // error ...
    }
}//namespace testItem16
// --- 条款17
// 注意：以独立语句将new（newed）对象置入智能指针 ...
// 1    以独立语句将new（newed）对象置入智能指针内，如果不这样做，一旦异常被抛出，
//      有可能导致难以察觉的资源泄露 ....（智能指针可以应对异常的资源析构 ... ）
// 2
// 3
namespace testItem17
{
    class MyExpcetion : public std::exception
    {
        const char* what()  const  throw()//
        { return " MyExpcetion::what() ,exception ... " ; }
    } ;
    void    testFunc()
    {
        using testItem16::Widget ;
        std::auto_ptr<Widget> pWidget(new Widget) ;
        Widget* pW = new Widget ; // 导致内存泄露 ...
        pW->print() ;
        throw MyExpcetion() ;
    }
}//namespace testItem17

// === 四、设计与声明 =================================================

// --- 条款18：让接口容易被使用，不易被误用 ...
// 注意：
// 1    好的接口很容易被正确使用，不容易被误用。你应该在你的所有接口中哪里达成这些性质。
// 2    “促进正确使用：的办法包括接口的一致性，以及与内置类型的行为兼容
// 3    阻止误用的办法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任
// 4    tr1：：shared_ptr 支持定制型删除器（custom deleter）。这可防范DLL问题，可被用来自动解除
//      互斥锁等等 ...
namespace testItem18
{
    class Month
    {
    public:
        static Month Jan() { return Month(1) ; }
        static Month Feb() { return Month(2) ; }
        // ... ...
        static Month Dec() { return Month(12) ; }
        short get() const { return month_ ; }
        // ...
        Month(short m):month_(m) //explicit
        { if(!(month_>0&&month_<13)) throw std::logic_error("month_ ,error") ; }
    private:
        short   month_ ;
    } ;
    class Day
    {// ...
    public:
        Day(short d):day_(d) //explicit
        { if(!(day_>0&&day_<32)) throw std::logic_error("day_ ,error") ; }
        short get() const { return day_ ; }
    private:
        short day_ ;
    } ;
    class Year
    {// ...
    public:
        Year(int y):year_(y)//explicit
        { if(!(year_>0)) throw std::logic_error("year_ ,error") ; }
        int get() const { return year_ ; }
    private:
        int year_ ;
    } ;
    class Date
    {
    public:
        explicit Date(Month m ,Day d ,Year y)
        : month_(m) ,day_(d) ,year_(y) {}
        //...
        friend ostream& operator << (ostream& os ,const Date& date) ;

    private:
        Month month_ ;
        Day   day_ ;
        Year  year_ ;
    } ;
    ostream& operator << (ostream& os ,const Date& date)
    {
        os << "Date(Month ,Day ,Year): "
           << "(" << date.month_.get() << " ," << date.day_.get() <<" ,"
           << date.year_.get() << ")" ;
        return os ;
    }
}//namespace testItem18
// --- 条款19：设计class 犹如设计type ...
// 注意：
// 1    class 的设计就得type 的设计 。在定义一个新type之前，请确定你已经考虑过以下主题：
//  1)  新的对象应该被如何的创建和销毁 ...？
//  2)  对象的初始化和对象的赋值应该有什么样的差别？
//  3)  新的type对象如果被passed by value（以值传递），意味着什么 ？
//  4)  什么是新type 的合法值 ？
//  5)  你的新type需要配合某个继承图系吗？（inheritance graph）
//  6)  你的新type需要什么样的转化？
//  7)  什么样的操作符和函数对此type而言是合理的 ？
//  8)  什么样的标准函数应该驳回 ？
//  9)  谁该取用新的type 的成员？
//  10)  什么是新type的”为声明的接口“？
//  11)  你的新type有多么一般化？
//  12)  你真的需要一个新 type吗？
// 2
// 3
namespace testItem19
{
}//namespace testItem19
// --- 条款20：宁以pass-by-reference-to-const替换pass-by-value ....
// 注意：
// 1    尽量以pass-by-reference-to-const替换pass-by-value。前者通常比较高效，并可以避免（对象的）切割问题
// 2    以上规则并不适用于内置类型，以及STL的迭代器和函数对象。对它们而言，pass-by-value往往比较适当 ...
// 3
namespace testItem20
{
    class Window
    {
    public:
        // ...
        Window() { cout << " Window::Window() ... \n" ; }
        string name() const { return "A object of class Window or its derived class " ; }
        virtual void display() const { cout << " virtual void Window::display() ... \n" ; }
        // ...
    } ;
    class WindowWithScrollBars : public Window
    {
    public:
        WindowWithScrollBars() { cout << " WindowWithScrollBars::WindowWithScrollBars() ... \n" ; }
        void display() const { cout << " void WindowWithScrollBars::display() ... \n" ; }
        // ...
    } ;
    void printNameAndDisplay_(Window w)
    {
        std::cout << "  void printNameAndDisplay_(Window w) ... \n" ;
        std::cout << " name(): " << w.name() << "\n" ;
        w.display() ;
    }
    void printNameAndDisplay(const Window& w)
    {
        std::cout << " void printNameAndDisplay(const Window& w) ... \n" ;
        std::cout << " name(): " << w.name() << "\n" ;
        w.display() ;
    }
}//namespace testItem20
// --- 条款21：必须返回对象时，别妄想返回其 reference ...
// 注意：
// 1    绝不要返回pointer或reference 指向一个 local stack 对象，或返回reference 指向一个heap-allocated
//      对象，或返回pointer或是reference指向一个local static 对象而有可能同时需要多个这样的对象。
//      条款4 已经为”在单线程环境中合理返回 reference 指向一个 local static 对象“ 提供一份设计实例 ...
// 2
// 3
namespace testItem21
{
    class Rational
    {
    private:
        int n_ ,d_ ;
    public:
        Rational(int numerator = 0 ,int denominator = 1 )//条款24说明为什么这个构造函数
        : n_(numerator) ,d_(denominator)
        {}// ... 不声明为 explicit ...
        int numerator() const { return n_ ; }
        int denominator() const { return d_ ; }
        friend const Rational operator * (const Rational& lhs ,const Rational& rhs) ;// better ...or non-friend
    //friend  const Rational& operator * (const Rational& lhs ,const Rational& rhs) ;// worse ...
    } ;
    inline const Rational operator * (const Rational& lhs ,const Rational& rhs) // better ...
    {
        return Rational(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ;
    }
    /* or: ===non-friend===
    inline const Rational operator * (const Rational& lhs ,const Rational& rhs) // better ...
    {
        return Rational(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator()) ;
    }*/

    // Warning ..................
    /*
    // Warning 1:
    const Rational& operator * (const Rational& lhs ,const Rational& rhs)
    {
        return Rational(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ; //警告，糟糕的代码 ，error ...
    }
    // Warning 2:
    const Rational& operator * (const Rational& lhs ,const Rational& rhs)
    {
        return *(new Rational(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ) ;// and then who delete that ...可能内存泄露
    }
    // Warning 3:
    const Rational& operator * (const Rational& lhs ,const Rational& rhs)
    {
        static Rational result(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ;
        return result ;
    }*/
    /* // for exmaple: ... error ...
        Rational a , b ,c ,d ;
        // ....
        if((a*b) == (c*d) ) // always true ...result==result //static Rational result
            .... //
        else
            ....
    */

}//namespace testItem21
// --- 条款22：将成员函数声明为 private ...
// 注意：
// 1    切记将成员变量声明为private 。这可赋予客户访问数据的一致性，可细微区分访问控制，
//      允许约束条件获得保证，并提供class 作者以充分的实现弹性 ...
// 2    其实，protected 并不比 public 更具封装性 ....
// 3
namespace testItem22
{
    class AccessLevels
    {
    private:
        int noAccess ;
        int readOnly ;
        int readWrite ;
        int writeOnly ;
        // ...
    public:
        int getReadOnly() const { return readOnly ; }
        void    setReadWrite(int value) { readWrite = value ; }
        int     getReadWrite() const { return readWrite ; }
        void    setWriteOnly(int value) { writeOnly = value ; }
        // ...
    } ;
}//namespace testItem22
// --- 条款23：宁以non-member、non-friend 替换 member 函数...
// 注意：
// 1    宁以non-member、non-friend 替换 member 函数.。这样做可以在家封装性、包裹弹性
//      (packaging flexibility ) 和机能扩充性 ...

// 2
// 3
namespace testItem23
{
    class WebBrowse
    {
    private:
        bool    bRun_ ;
        // ...
    public:
        // ...
        void    clearCache() {}
        void    clearHistory() {}
        void    removeCookies() {}
        // ...
        void clearEverything() // ... bag ...to clearWebBrowser
        {
            clearCache() ;
            clearHistory() ;
            removeCookies() ;
        }
        void clearWebBrowser(WebBrowse& wb) // ... good ... to WebBrowse::clearEverything
        {
            wb.clearCache() ;
            wb.clearHistory() ;
            wb.removeCookies() ;
        }
    } ;//

}//namespace testItem23
// --- 条款24：若所有参数皆需类型转换(隐式)，请为此采用non-member函数 ...
// 注意：
// 1    如果你需要为某个函数的所有参数（包括呗this指针所指的那个隐喻参数）进行类型转型，
//      那么这个函数必须是个 non-member ...
// 2
// 3
namespace testItem24
{
    using testItem21::Rational ;
    // operator *  -- 支持隐式类型转换与混合式算术运算  ....
    ostream& operator << (ostream& os ,const Rational& rhs)
    {
        os << " ostream& operator << (ostream& os ,const Rational& rhs) ... \n" ;
        os << " rhs.numerator(): " << rhs.numerator()
           << " rhs.denominator(): " << rhs.denominator() << "\n" ;
        return os ;
    }
    void testFunc()
    {
        Rational obj_1and8(1 ,8) ,obj_1and2(1 ,2) ;
        cout << " print obj_1and8 ,obj_1and2 :\n" ;
        cout << obj_1and8 << obj_1and2  ;

        cout << " result = obj_1and8*obj_1and2 ; and print result :\n" ;
        Rational result = obj_1and8*obj_1and2 ; //okokok
        cout << result ;
        //result = result*obj_1and2 ; //okokok
        cout << " result = obj_1and2 * 2 ; and print result :\n" ;
        result = obj_1and2 * 2 ;//okokok
        cout << result ;
        cout << " result = 2 * obj_1and2 ; and print result :\n" ;
        result = 2 * obj_1and2 ;//okokok
        cout << result ;

    }

}//namespace testItem24
// --- 条款25：考虑写出一个不抛出异常的 swap 函数 ...
// 注意：
// 1    当 std::swap 对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常
// 2    如果你提供一个member swap ，也提供一个non-member swap 用来调用前者。对于classes
//      （而非templates），也请特化 std::swap 。
// 3    调用 swap 时硬针对std::swap 使用 using 声明式，日后调用swap并且不带任何”命名空间资格修饰“
// 4    为”用户自定义类型“进行全特化的好的，但千万不要尝试在std 内加入某些对 std而言全新的东西 ....
/*
namespace std
{
    template <typename T>
    void swap(T& a ,T& b)
    {
        T temp(a) ;
        a = b ;
        b = temp ;
    }
}*/
namespace testItem25
{
    class WidgetImpl
    {
    private:
        int a ,b ,c ;
        std::vector<double> dVec ;
        // ...
    public:
        WidgetImpl() {}
        /* // default copy and perator = constructor for copy a ,b ,c and dVec ( okokok ) ..
        WidgetImpl(const WidgetImpl& rhs)
        : a(rhs.a) ,b(rhs.b) ,c(rhs.c) // ,dVec(w.dVec)
        {
            dVec.assign(rhs.dVec.begin() ,rhs.dVec.end() ) ;
            cout << " WidgetImpl::WidgetImpl(const WidgetImpl& rhs) ... \n" ;
        }
        WidgetImpl& operator = (const WidgetImpl& rhs)
        {
            a = rhs.a ;
            b = rhs.b ;
            c = rhs.c ;
            dVec.assign(rhs.dVec.begin() ,rhs.dVec.end() ) ;
        }*/
        // ----- member function ----
        vector<double>* getPtrdVec() { return &dVec ; }
        // ...
    } ;
    class Widget  // : public WidgetImpl
    {
    private:
        WidgetImpl* pImpl ;
    public:
        Widget() { pImpl = new WidgetImpl ; }
        Widget(const Widget& w) ;
        Widget& operator = (const Widget& rhs) ;
        vector<double>* getPtrdVec() ;
        WidgetImpl*& getImpl() { return pImpl ; }
        void    swap(Widget& other) ;
    } ;
    Widget::Widget(const Widget& rhs)
    {
        cout << " Widget::Widget(const Widget& rhs) ... \n" ;
        pImpl = new WidgetImpl(*rhs.pImpl) ;
    }
    Widget& Widget::operator = (const Widget& rhs)
    {
        cout << " Widget& Widget::operator = (const Widget& rhs) ... \n" ;
        pImpl = new WidgetImpl(*rhs.pImpl) ;
        return *this ;
    }
    vector<double>* Widget::getPtrdVec() { return pImpl->getPtrdVec() ; }// for test ...
    void    Widget::swap(Widget& other)
    {
        using std::swap ;//这个声明必要 ...
        swap(pImpl ,other.pImpl) ;//只需置换 pImpl 指针...
    }
    // -------------------------------------
    template <typename T>
    class WidgetImpl_T
    {
    private:
        T   value_ ;
    public:
        explicit WidgetImpl_T(T v) : value_(v) {}
        T&  getValue() { return value_ ; }
    } ;

    template <typename T>
    class Widget_T
    {
    private:
        WidgetImpl_T<T>*    pImpl ;
    public:
        explicit Widget_T(T v) : pImpl(new WidgetImpl_T<T>(v)) {}// ...
        void swap(Widget_T<T>& other)
        {
            //using std::swap ;
            std::swap(pImpl ,other.pImpl) ;//@@@@@@@@@@@@@@@@, error ...
            //std::swap(pImpl ,other.pImpl) ;//@@@@@@@@@@@@@@@@, error ...
        //Error: Could not find a match for 'swap<>(WidgetImpl_T<int> *,WidgetImpl_T<int> *)' in function Widget_T<int>::swap(Widget_T<int> &)|
        }
        void printWidget_T()
        { cout << " void Widget_T<T>::printWidget_T() ,pImpl->getValue(): " << pImpl->getValue() << "\n" ; }
    } ; /*
    template<typename T>
    void swap<Widget_T<T> >(Widget_T<T>& a ,Widget_T<T>& b)
    {//Error : Explicit specialization of 'std::swap<>(Widget &,Widget &)' requires 'template<>' declaration|
        a.swap(b) ;
    } */
    template<typename T>
    void swap(Widget_T<T>& a ,Widget_T<T>& b)//
    {
        cout << " template<typename T> void testItem25::swap(Widget_T<T>& a ,Widget_T<T>& b)\n" ;
        a.swap(b) ;
    }
}//namespace testItem25
namespace std
{
    using testItem25::Widget ;
    template<>
    void swap<Widget>(Widget& a ,Widget& b)
    {
        cout << " template<> void std::swap<Widget>(Widget& a ,Widget& b)\n" ;
        a.swap(b) ;
        //or : swap(a.getImpl() ,b.getImpl()) ;// okokok
    }
    /* //////////////////////// Error //////////////////////////////////
    using testItem25::Widget_T ;
    template<typename T>
    void swap<Widget_T<T> >(Widget_T<T>& a ,Widget_T<T>& b)
    {//Error : Explicit specialization of 'std::swap<>(Widget &,Widget &)' requires 'template<>' declaration|
        a.swap(b) ;
    } */
    /* //////////////////////// Error //////////////////////////////////
    using testItem25::Widget_T ;
    template<typename T>
    void swap(Widget_T<T>& a ,Widget_T<T>& b)// Compile okokok ,but .... @@@@@@@@@@@@@@@@
    {//Error : Explicit specialization of 'std::swap<>(Widget &,Widget &)' requires 'template<>' declaration|
        cout << " template<typename T> void std::swap(Widget_T<T>& a ,Widget_T<T>& b)\n" ;
        a.swap(b) ;
    }*/ /*
    using testItem25::WidgetImpl_T ;
    template<typename T>
    void swap(WidgetImpl_T<T>* pa ,WidgetImpl_T<T>* pb)//
    {
        cout << " template<typename T> void std::swap(WidgetImpl_T<T>* a ,WidgetImpl_T<T>* b)\n" ;
        _STL::swap(pa ,pb) ;
    } */
}
//Unit2.h|560|Error E2015 : Ambiguity between 'std::void swap<int>(testItem25::WidgetImpl_T<int> *,testItem25::WidgetImpl_T<int> *)' and '_STL::void swap<testItem25::WidgetImpl_T<int> *>(testItem25::WidgetImpl_T<int> * &,testItem25::WidgetImpl_T<int> * &)' in function std::void swap<int>(testItem25::WidgetImpl_T<int> *,testItem25::WidgetImpl_T<int> *)|
// ====================================================================
// --- 条款
// 注意：
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem

#endif // UNIT2_H_INCLUDED
