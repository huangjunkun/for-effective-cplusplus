#ifndef UNIT4_H_INCLUDED
#define UNIT4_H_INCLUDED

// ===  七、模板与泛型编程  ===========================================
// ====================================================================
// --- 条款41
// 注意：了解隐式接口和编译期多态 ...
// 1    classes 和 templates 都支持接口(interfaces)和多态(polymorphism) 。
// 2    对classes而言接口是显示的(explicit)，以函数签名为中心。多态则是通过virtual函数
//      发生于程序运行期。
// 3    对templates 而言，接口的隐式的(implicit)，奠基于有效表达式。多提啊则是通过template
//      具现化和函数重载解析(function overloading resolution)发生于编译期 ...
namespace testItem41
{
    class Widget
    {
    private:
        int value_ ;
    public:
        Widget() {} ;
        Widget(int i) : value_(i) {} ;
        virtual ~Widget() {}
        virtual std::size_t size() const { return  value_ ; }
        virtual void normalize() { value_ = 1 ; }
        void swap(Widget& other)
        {
            int temp = value_ ;
            value_ = other.value_ ;
            other.value_  = temp ;
        }
        bool operator != (const Widget& rhs)
        { return (value_ != rhs.value_) ; }
        // ...
    } ;
    // 函数签名显示接口 ... classes
    static Widget someNastyWidget(0) ;// ...
    void doProcessing(Widget& w)
    {
        if(w.size()>10 && w!=someNastyWidget)
        {
            Widget temp(w) ;
            temp.normalize() ;
            temp.swap(w) ;
        }
    }
    // 有效表达式隐式接口 ... templates
    template <typename T>
    void doProcessing_(T& w)
    {
        if(w.size()>10 && w!=someNastyWidget)
        {
            Widget temp(w) ;
            temp.normalize() ;
            temp.swap(w) ;
        }
    }
    void exampleFunc()
    {
        Widget w1(11) ;
        doProcessing(w1) ;
        Widget w2(11) ;
        doProcessing_(w2) ;
    }
}//namespace testItem41

// ====================================================================
// --- 条款42：了解typename 的双重意义
// 注意：
// 1    声明template 参数时，前缀关键字class 和typename可互换。
// 2    请使用关键字typename 标识嵌套从属类型名称；但不得在base calss lists
//      （基类列表）或member initialization list（成员初始值列表）内以它作为base class 修饰符
namespace testItem42
{
    template <class T> class Widget_1{ } ;//okokok
    template <typename T> class Widget_2{ } ;//typename same as class
    template <typename C>
    void print2nd(const C& container)
    {
        if(container.size()>=2)
        {
            typename C::const_iterator it(container.begin()) ;// ... should has typename
            it++ ;
            std::cout << " print2nd(const C& container): " << *it << "\n" ;
        }
    }
    template <typename C>
    typename C::const_iterator
    find(const C& container ,typename C::const_iterator dest)//const ...
    {
        typename C::const_iterator it(container.begin()) ;
        for( ;it!=container.end() ;it++)
            if(*dest==*it)
                return it ;
        return it ;
    }
    template <typename C>
    typename C::iterator
    find(C& container ,typename C::iterator dest)//const ...
    {
        typename C::iterator it(container.begin()) ;
        for( ;it!=container.end() ;it++)
            if(*dest==*it)
                return it ;
        return it ;
    }
    // -----------------------------------
    // -----------------------------------
    template <typename T>
    class Base
    {
    public:
        class Nested
        {
        private:
            T value_ ;
        public:
            Nested(int v): value_(v) {}
            //// ...
            //template <typename U>
            //friend ostream& operator <<  (ostream& os ,const Nested& n) ;/**/
            friend ostream& operator <<  (ostream& os ,const Nested& n)//okokok MinGW ...
            {
                os << " calss Base<T>::Nested: ostream& operator << (ostream& os ,const Nested& n)\n"
                   << " value_: " << n.value_ << "\n" ;
                return os ;
            }
        } ;
    } ;/* */
    /*  =================??????????????????*
    template <typename U>
    ostream&  operator << (ostream& os ,const Base<U>::Nested& n)
    {
        os << " calss Base<T>::Nested: ostream& operator << (ostream& os ,const Nested& n)\n"
           << " value_: " << n.value_ << "\n" ;
        return os ;
    }*/

    template <typename T>
    class Derived : public Base<T>::Nested
    {
    private:
        T dValue_ ;
    public:
        explicit Derived(int x):Base<T>::Nested(x),dValue_(x)
        { }
        //typedef Base<T>::Nested BaseType ;//...
        //template <typename U>
        friend ostream& operator << <> (ostream& os ,const Derived& d) ;/*
        friend ostream& operator <<  (ostream& os ,const Derived& n) //okokok
        {
            os << " calss Base<T>::Nested: ostream& operator << (ostream& os ,const Nested& n)\n"
               << " dValue_: " << n.dValue_ << "\n" ;
            return os ;
        } */
    } ;        /*  ???????????*/
    template <typename T>
    ostream& operator <<  (ostream& os ,const Derived<T>& d)
    {
        os << " calss Base<T>::Nested: ostream& operator << (ostream& os ,const Nested& n)\n"
           << " dValue_: " << d.dValue_ << "\n" ;
        return os ;
    }
} //namespace testItem42
// ====================================================================
// --- 条款43：学习处理模板化基类内的名称
// 注意：
// 1    课在derived class templates 内通过"this->" 指涉base class templates 内的成员名称
//      或藉由一个明白写出的"base class 资格修饰符"完成。
// 2
namespace testItem43
{
    class MsgInfo{ } ;
    class CompanyA
    {
    public:
        // ....
        void sendCleartext(const std::string& msg) { cout << " CompanyA::sendCleartext\n" ;}
        void sendEncrypted(const std::string& msg) { cout << " CompanyA::sendEncrypted\n" ;}
        // ....
    } ;
    class CompanyB
    {
    public:
        // ....
        void sendCleartext(const std::string& msg) { cout << " CompanyB::sendCleartext\n" ;}
        void sendEncrypted(const std::string& msg) { cout << " CompanyB::sendEncrypted\n" ;}
        // ....
    } ;
    class CompanyC
    {
    public:
        // ....
        //void sendCleartext(const std::string& msg) { cout << " CompanyA::sendCleartext\n" ;}
        void sendEncrypted(const std::string& msg) { cout << " CompanyC::sendEncrypted\n" ;}
        // ....
    } ;
    template <typename Company>
    class MsgSender
    {
    public:
        //...
        void sendClear(const MsgInfo& info)
        {
            std::string msg ;
            //在这里根据info产生信息 ；
            Company c ;
            c.sendCleartext(msg) ;
        }
        void sendSecret(const MsgInfo& info)
        {
            std::string msg ;
            //在这里根据info产生信息 ；
            Company c ;
            c.sendEncrypted(msg) ;
        }//...
    } ;
    template <>
    class MsgSender<CompanyC>
    {
    public:
        // ...
        void sendSecret(const MsgInfo& info)
        {
            std::string msg ;
            //在这里根据info产生信息 ；
            CompanyC c ;
            c.sendEncrypted(msg) ;
        }
    protected:
            void sendClear(const MsgInfo& info) {}// nothing ...lock the function ...
    } ;
    template <typename Company>
    class LoggingMsgSender : public MsgSender<Company>
    {
    public:
        // ...
        using MsgSender<Company>::sendClear ; //typename 2: non-virtual member (function) ...
        void sendClearMsg(const MsgInfo& info)
        {
            // 将“传送前”的信息写至log
            // 1:
            this->sendClear(info) ;// okok ---sendClear(info) ;//error???nonono
            // or: .... 2: non-virtual member (function)
            sendClear(info) ; // okokok ...
            // or: .... 3: non-virtual member (function)
            //MsgSender<Company>::sendClear(info) ;

            // 将“传送后”的信息写至log
        }
    } ;
}//namespace testItem43
// ====================================================================
// --- 条款44：将与参数无关的代码抽离 templates
// 注意：
// 1    Templates 生成多个classes 和 多个函数 ，所以任何template 代码都不该与某个造成膨胀
//      的tempalte参数产生相依关系 ...
// 2    因非类型模板参数(non-type tempalte parameters)而造成的代码膨胀，往往可以消除，做法
//      是以函数参数或classes 成员变量替换 template 参数 ...
// 3    因类型参数(type parameters) 而造成的代码膨胀，往往可以降低，做法是让到右完全相同
//      二进制表述(binary representations)的具体类型(instantiation types)共享实现码 ....
namespace testItem44
{
    //1  --- 没有将与参数无关的代码抽离 templateS ...
    template <typename T ,std::size_t N>
    class SquareMatrix_
    {
    public:
        // ...
        void invert() ;// 求逆矩阵 ...
    } ;
    template <typename T ,std::size_t N>
    void SquareMatrix_<T ,N>::invert() {} // ...
    // 若因为 SquareMatrix 的N 不同具现出很多类型，则导致代码膨胀 ...
    void exampleFunc()
    {
        SquareMatrix_<double ,5> sm1 ;
        // ...
        sm1.invert() ;
        SquareMatrix_<double ,10> sm2 ;// sm1 和 sm2 不同类型 ...
        // ...
        sm2.invert() ;
    }
    //2  --- 将与参数无关的代码抽离 templateS ...
    template <typename T>
    class SquareMatrixBase
    {
    protected:
        SquareMatrixBase(std::size_t n ,T* pMem)
        : size_(n) ,pData(pMem) {} // ...
        void setDataPtr(T* ptr) { pData = ptr ; }
        // ...
    private:
        size_t size_ ;
        T*      pData ;
    } ;

    template <typename T ,std::size_t N>
    class SquareMatrix : SquareMatrixBase<T>
    {
    public:
        SquareMatrix() : SquareMatrixBase<T>(N ,pData_) {}// ..
        // ...
    private:
        //T   pData_[N*N] ;// 可能导致class SquareMatrix 对象大小很大 ...数据存储于程序栈 ...
        std::tr1::scoped_array<T> pData_ ; // or: std::tr1::scoped_array<T>，数据存储于堆 ...
    } ;
    // 不论数据存储于何处，从膨胀的角度讨论之，关键是现在许多SquareMatrix成员函数可以单纯地以
    // inline 方式调用base class 版本，后者由"持有同型元素“（不论矩阵大小）之所有矩阵共享 ..

}//namespace testItem44
// ====================================================================
// --- 条款45：运用成员函数模板接受所有兼容类型 ...
// 注意：
// 1    请使用成员函数模板(member function templates) 生成”可接受所有兼容类型“的函数 ...
// 2    如果你声明了 member templates 用于 ”泛化copy 构造“或”泛化 assignment操作“，你还是需要
//      声明正常的copy 构造函数和copy assignment 操作符 ...
// 3
namespace testItem45
{
    class Top
    {
    public:
        Top() { cout << " Top::Top()\n" ; }
        virtual ~Top() { cout << " virtual Top::~Top()\n" ; }
    } ;// ...
    class Middle : public Top
    {
    public:
        Middle() { cout << " Middle::Middle()\n" ; }
        virtual ~Middle() { cout << " virtual Middle::~Middle()\n" ; }
    } ;// ...
    class Bottom : public Middle
    {
    public:
        Bottom() { cout << " Bottom::Bottom()\n" ; }
        virtual ~Bottom() { cout << " virtual Bottom::~Bottom()\n" ; }
    } ;// ...

    template <typename T>
    class SmartPtr
    {
    public:
        SmartPtr() : heldPtr(NULL) {} //..
        explicit SmartPtr(T* realPtr) : heldPtr(realPtr) {} // ...
        ~SmartPtr()
        { if(heldPtr) { delete heldPtr ; heldPtr=NULL ; } }
        /*1 ***************************************/
        template <typename U>
        SmartPtr(const SmartPtr<U>& other)//
        : heldPtr(other.get())
        {
            other.reset() ;
            cout << " template <typename U> SmartPtr(const SmartPtr<U>& other) ...\n" ;
        }// ...
        /*2 ***************************************/
        SmartPtr(const SmartPtr& rhs) : heldPtr(rhs.get())
        {
            rhs.reset() ;
            cout << " SmartPtr(const SmartPtr& rhs)  ...\n" ;
        }
        SmartPtr& operator = (const SmartPtr& rhs)
        {
            heldPtr = rhs.get() ;
            rhs.reset() ;
            cout << " SmartPtr& operator = (const SmartPtr& rhs) ...\n" ;
            return *this ;
        }
        /****************************************/
        /****************************************/
        T*  get() const { return heldPtr ; }
        void reset() const { heldPtr = NULL ; }
        // ...
    private:
        mutable T*  heldPtr ; // ...
    } ;
    // ... 参照，boost::shared_ptr<T>的详细实现 ...
    void exampleFunc()
    {
        /*
        Top* pt1 = new Middle ;// 将Middle* 转化为 Top* ---自动
        Top* pt2 = new Bottom ;// 将Bottom* 转化为 Top* ---自动
        const Top pct1 = pt1 ; // 将Top* 转化为 const Top* ---自动
        */
        SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle) ;
        SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom) ;
        SmartPtr<const Top> pct1 = pt1 ;
        SmartPtr<Top> pt3(pt1) ,pt4 ;
        pt4 = pt2 ;
    }
}//namespace testItem45
// ====================================================================
// --- 条款46：需要类型转换时请为模板定义非成员函数 ...参照条款24 ...
// 注意：
// 1    当我们编写一个 class template ，而它所提供之”与此template相关的”函数支持“所有参数
//      之隐式类型转换”时，请将那些函数定义为“class template内部的friend函数 “ ...
// 2
// 3
namespace testItem46
{
    // 先声明 template class Rational ....
    template <typename T>
    class Rational ;
    // 先声明 函数 doMutilply ....
    template <typename T>
    const Rational<T>  doMutilply(const Rational<T>& lhs ,const Rational<T>& rhs) ;
    //
    template <typename T>
    class Rational
    {
    private:
        T n_ ,d_ ;
    public:
        Rational(T numerator = T(0) ,T denominator = T(1) )//条款24说明为什么这个构造函数
        : n_(numerator) ,d_(denominator)
        {}// ... 不声明为 explicit ...
        T numerator() const { return n_ ; }
        T denominator() const { return d_ ; }
        /*
// --------- non-inline -------------
////////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! /////////////
        //template <typename U> //not for MinGW GUN GCC ...
        //friend const Rational<U>  operator* (const Rational<U>& lhs ,const Rational<U>& rhs) ;
        friend const Rational  operator* <> (const Rational& lhs ,const Rational& rhs) ;//for BCB okokok,but MinGW GUN GCC ...
//warning: friend declaration `const testItem46::Rational<T> testItem46::operator*(const testItem46::Rational<T>&, const testItem46::Rational<T>&)' declares a non-template function|
        //friend const Rational<T>  operator* (const Rational<T>& lhs ,const Rational<T>& rhs) ; //Also,okokok
//warning: (if this is not what you intended, make sure the function template has already been declared and add <> after the function name here) -Wno-non-template-friend disables this warning|
        // -------------------------
        // friend ostream& operator << (ostream& os ,const Rational& rhs) ;// for BCB okokok,but MinGW GUN GCC ...
        template <typename U> // for MinGW GUN GCC ...
        friend ostream& operator << (ostream& os ,const Rational<U>& rhs) ; // non-inline
        */
// --------- inline -------------
        /* // inlining*/
        friend const Rational  operator* (const Rational& lhs ,const Rational& rhs)
        {
            return Rational<T>(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator()) ;
            //doMutilply(lhs ,rhs) ; // or :调用外部辅助函数 ... 很好的点子 ！！！
        }
        // inlining
        friend ostream& operator << (ostream& os ,const Rational& rhs)
        {
            os << " n_: " << rhs.numerator() << " ,d_: " << rhs.denominator() << "\n" ;
            return os ;
        }
    } ;/*
    template <typename T>
    const Rational<T>  operator*  (const Rational<T>& lhs ,const Rational<T>& rhs)
    {
        return Rational<T>(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator()) ;
    }
    template <typename T>
    ostream& operator << (ostream& os ,const Rational<T>& rhs)
    {
        os << " n_: " << rhs.numerator() << " ,d_: " << rhs.denominator() << "\n" ;
        return os ;
    }*/
    template <typename T>
    const Rational<T>  doMutilply(const Rational<T>& lhs ,const Rational<T>& rhs)
    {
        return Rational<T>(lhs.numerator()*rhs.numerator(),lhs.denominator()*rhs.denominator()) ;
    }

    void exampleFunc()
    {
        Rational<int>   r1(1 ,1) ,r2(2 ,2) ;
        cout << " r1(1 ,1) ,r2(2 ,2) ; ...\n" ;
        cout << r1 << r2 ;
        cout << " cout << r1*r2 ; ...\n" ;
        cout << r1*r2 ;
        cout << " cout << r1*3 ; ...\n" ;
        cout << r1*3 ;
        cout << " cout << 3*r2 ; ...\n" ;
        cout << 3*r2 ;
        cout << " cout << 3*r1*r2*2 ; ...\n" ;
        cout << 3*r1*r2*2 ;
    }
}//namespace testItem46
// ====================================================================
// --- 条款47：请使用traits classes表现类型类型
// 注意：
// 1：Traits classes 使得“类型相关信息”在编译期可用。它们templates和“templates特化”完成实现。
// 2：整合重载技术（overloading）后，traits classes有可能在编译期对类型执行if ... else测试。
// 3
namespace testItem47
{
}//namespace testItem47
// ====================================================================
// --- 条款48：认识template 元编程
// 注意：
// 1：Template metaprogramming(TMP ，模板元编程)可将工作由运行期移往编译期，
//    因而得以实现早期错误侦测和更高的执行效率
// 2：TMP 可被用来生成"基于策略选择组合" 的客户定制代码，也可以用来避免生成
//    对某些特殊类型并不合适的代码
// 3
namespace testItem48
{
    template <int I>
    int Func()
    {
        return I*Func<I-1>() ;
    }
    template <>
    int Func<1>()
    {
        return 1 ;
    }
    template <>
    int Func<0>()
    {
        return 1 ;
    }
    // ...
    template <int I>
    struct Factorial
    {
        enum { result = I*Factorial<I-1>::result } ;
    } ;
    template <>
    struct Factorial<0>
    { enum { result = 1  } ;} ;
}//namespace testItem48
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
// --- 条款49
// 注意：
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem

// ================================================================
#endif // UNIT4_H_INCLUDED
