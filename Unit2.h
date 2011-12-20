#ifndef UNIT2_H_INCLUDED
#define UNIT2_H_INCLUDED

// === ������Դ���� =================================================
// --- ����13���Զ��������Դ ...
// ע�⣺
// 1    Ϊ��ֹ��Դй¶����ʹ��RAII���������ڹ��캯���л����Դ���������������ͷ���Դ
// 2    ��������ʹ����RAII classed �ֱ���tr1::shareed_ptr �� auto_ptr ��ǰ��ͨ���ǽϼѵ�
//      ѡ��,��Ϊ��copy��Ϊ�Ƚ�ֱ�ۡ���ѡ��auto_ptr �����ƶ�����ʹ�����������ָ��null ...
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

// --- ����14������Դ����������С��copying ��Ϊ ...
// ע�⣺RAII��Resource Acquisition Is Initialization����Դȡ��ʱ�����ǳ�ʼ��ʱ��....
// 1    ����RAII�������һ�����������������Դ��������Դ��coping��Ϊ����RAII�����copying��Ϊ
// 2    �ձ��������RAII class copying��Ϊʱ������copying��ʩ�����ü�������reference counting����
//      ����������ΪҲ���ܱ�ʵ�� ...
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

// --- ����15������Դ���������ṩ��ԭʼ��Դ�ķ��� ...
// ע�⣺
// 1    APIs����Ҫ�����ԭʼ��Դ��raw resouces������˶���ÿһ��RAII class Ӧ���ṩһ����ȡ��
//      ��������֮��Դ���İ취 ...
// 2    ��ԭʼ��Դ�ķ��ʿ��ܾ�����ʽת��������ʽת����һ�������ʽת���Ƚϰ�ȫ������ʽת�������û��ȽϷ��� ...
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
        // ��ʽת��
        FontHandle get() const { return fh_ ; }// safely ,better ...
        // ��ʽת�� ...
        //operator FontHandle() const { return fh_ ; } // no safe ...
    } ;
}//namespace testItem15
// --- ����16���ɶ�ʹ��new �� delete ʱ������ͬ��ʽ ...new-delete ,new[]-delete[]
// ע�⣺
// 1    ������ڱ��ʽ��ʹ��[] ����������Ӧ��delete���ʽ��ʹ��[]����֮��Ȼ ....
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
        // delete pStr ;// ��Ϊ�ж��� ....WARN !!!
        delete[] pStr ;//  �ܺ� ....
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
// --- ����17
// ע�⣺�Զ�����佫new��newed��������������ָ�� ...
// 1    �Զ�����佫new��newed��������������ָ���ڣ��������������һ���쳣���׳���
//      �п��ܵ������Բ������Դй¶ ....������ָ�����Ӧ���쳣����Դ���� ... ��
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
        Widget* pW = new Widget ; // �����ڴ�й¶ ...
        pW->print() ;
        throw MyExpcetion() ;
    }
}//namespace testItem17

// === �ġ���������� =================================================

// --- ����18���ýӿ����ױ�ʹ�ã����ױ����� ...
// ע�⣺
// 1    �õĽӿں����ױ���ȷʹ�ã������ױ����á���Ӧ����������нӿ�����������Щ���ʡ�
// 2    ���ٽ���ȷʹ�ã��İ취�����ӿڵ�һ���ԣ��Լ����������͵���Ϊ����
// 3    ��ֹ���õİ취�������������͡����������ϵĲ�������������ֵ���Լ������ͻ�����Դ��������
// 4    tr1����shared_ptr ֧�ֶ�����ɾ������custom deleter������ɷ���DLL���⣬�ɱ������Զ����
//      �������ȵ� ...
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
// --- ����19�����class �������type ...
// ע�⣺
// 1    class ����ƾ͵�type ����� ���ڶ���һ����type֮ǰ����ȷ�����Ѿ����ǹ��������⣺
//  1)  �µĶ���Ӧ�ñ���εĴ��������� ...��
//  2)  ����ĳ�ʼ���Ͷ���ĸ�ֵӦ����ʲô���Ĳ��
//  3)  �µ�type���������passed by value����ֵ���ݣ�����ζ��ʲô ��
//  4)  ʲô����type �ĺϷ�ֵ ��
//  5)  �����type��Ҫ���ĳ���̳�ͼϵ�𣿣�inheritance graph��
//  6)  �����type��Ҫʲô����ת����
//  7)  ʲô���Ĳ������ͺ����Դ�type�����Ǻ���� ��
//  8)  ʲô���ı�׼����Ӧ�ò��� ��
//  9)  ˭��ȡ���µ�type �ĳ�Ա��
//  10)  ʲô����type�ġ�Ϊ�����Ľӿڡ���
//  11)  �����type�ж�ôһ�㻯��
//  12)  �������Ҫһ���� type��
// 2
// 3
namespace testItem19
{
}//namespace testItem19
// --- ����20������pass-by-reference-to-const�滻pass-by-value ....
// ע�⣺
// 1    ������pass-by-reference-to-const�滻pass-by-value��ǰ��ͨ���Ƚϸ�Ч�������Ա��⣨����ģ��и�����
// 2    ���Ϲ��򲢲��������������ͣ��Լ�STL�ĵ������ͺ������󡣶����Ƕ��ԣ�pass-by-value�����Ƚ��ʵ� ...
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
// --- ����21�����뷵�ض���ʱ�������뷵���� reference ...
// ע�⣺
// 1    ����Ҫ����pointer��reference ָ��һ�� local stack ���󣬻򷵻�reference ָ��һ��heap-allocated
//      ���󣬻򷵻�pointer����referenceָ��һ��local static ������п���ͬʱ��Ҫ��������Ķ���
//      ����4 �Ѿ�Ϊ���ڵ��̻߳����к����� reference ָ��һ�� local static ���� �ṩһ�����ʵ�� ...
// 2
// 3
namespace testItem21
{
    class Rational
    {
    private:
        int n_ ,d_ ;
    public:
        Rational(int numerator = 0 ,int denominator = 1 )//����24˵��Ϊʲô������캯��
        : n_(numerator) ,d_(denominator)
        {}// ... ������Ϊ explicit ...
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
        return Rational(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ; //���棬���Ĵ��� ��error ...
    }
    // Warning 2:
    const Rational& operator * (const Rational& lhs ,const Rational& rhs)
    {
        return *(new Rational(lhs.n_*rhs.n_ ,lhs.d_*rhs.d_) ) ;// and then who delete that ...�����ڴ�й¶
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
// --- ����22������Ա��������Ϊ private ...
// ע�⣺
// 1    �мǽ���Ա��������Ϊprivate ����ɸ���ͻ��������ݵ�һ���ԣ���ϸ΢���ַ��ʿ��ƣ�
//      ����Լ��������ñ�֤�����ṩclass �����Գ�ֵ�ʵ�ֵ��� ...
// 2    ��ʵ��protected ������ public ���߷�װ�� ....
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
// --- ����23������non-member��non-friend �滻 member ����...
// ע�⣺
// 1    ����non-member��non-friend �滻 member ����.�������������ڼҷ�װ�ԡ���������
//      (packaging flexibility ) �ͻ��������� ...

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
// --- ����24�������в�����������ת��(��ʽ)����Ϊ�˲���non-member���� ...
// ע�⣺
// 1    �������ҪΪĳ�����������в�����������thisָ����ָ���Ǹ�������������������ת�ͣ�
//      ��ô������������Ǹ� non-member ...
// 2
// 3
namespace testItem24
{
    using testItem21::Rational ;
    // operator *  -- ֧����ʽ����ת������ʽ��������  ....
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
// --- ����25������д��һ�����׳��쳣�� swap ���� ...
// ע�⣺
// 1    �� std::swap ���������Ч�ʲ���ʱ���ṩһ��swap��Ա��������ȷ������������׳��쳣
// 2    ������ṩһ��member swap ��Ҳ�ṩһ��non-member swap ��������ǰ�ߡ�����classes
//      ������templates����Ҳ���ػ� std::swap ��
// 3    ���� swap ʱӲ���std::swap ʹ�� using ����ʽ���պ����swap���Ҳ����κΡ������ռ��ʸ����Ρ�
// 4    Ϊ���û��Զ������͡�����ȫ�ػ��ĺõģ���ǧ��Ҫ������std �ڼ���ĳЩ�� std����ȫ�µĶ��� ....
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
        using std::swap ;//���������Ҫ ...
        swap(pImpl ,other.pImpl) ;//ֻ���û� pImpl ָ��...
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
// --- ����
// ע�⣺
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem

#endif // UNIT2_H_INCLUDED
