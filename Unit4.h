#ifndef UNIT4_H_INCLUDED
#define UNIT4_H_INCLUDED

// ===  �ߡ�ģ���뷺�ͱ��  ===========================================
// ====================================================================
// --- ����41
// ע�⣺�˽���ʽ�ӿںͱ����ڶ�̬ ...
// 1    classes �� templates ��֧�ֽӿ�(interfaces)�Ͷ�̬(polymorphism) ��
// 2    ��classes���Խӿ�����ʾ��(explicit)���Ժ���ǩ��Ϊ���ġ���̬����ͨ��virtual����
//      �����ڳ��������ڡ�
// 3    ��templates ���ԣ��ӿڵ���ʽ��(implicit)���������Ч���ʽ�����ᰡ����ͨ��template
//      ���ֻ��ͺ������ؽ���(function overloading resolution)�����ڱ����� ...
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
    // ����ǩ����ʾ�ӿ� ... classes
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
    // ��Ч���ʽ��ʽ�ӿ� ... templates
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
// --- ����42���˽�typename ��˫������
// ע�⣺
// 1    ����template ����ʱ��ǰ׺�ؼ���class ��typename�ɻ�����
// 2    ��ʹ�ùؼ���typename ��ʶǶ�״����������ƣ���������base calss lists
//      �������б���member initialization list����Ա��ʼֵ�б���������Ϊbase class ���η�
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
// --- ����43��ѧϰ����ģ�廯�����ڵ�����
// ע�⣺
// 1    ����derived class templates ��ͨ��"this->" ָ��base class templates �ڵĳ�Ա����
//      �����һ������д����"base class �ʸ����η�"��ɡ�
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
            //���������info������Ϣ ��
            Company c ;
            c.sendCleartext(msg) ;
        }
        void sendSecret(const MsgInfo& info)
        {
            std::string msg ;
            //���������info������Ϣ ��
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
            //���������info������Ϣ ��
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
            // ��������ǰ������Ϣд��log
            // 1:
            this->sendClear(info) ;// okok ---sendClear(info) ;//error???nonono
            // or: .... 2: non-virtual member (function)
            sendClear(info) ; // okokok ...
            // or: .... 3: non-virtual member (function)
            //MsgSender<Company>::sendClear(info) ;

            // �������ͺ󡱵���Ϣд��log
        }
    } ;
}//namespace testItem43
// ====================================================================
// --- ����44����������޹صĴ������ templates
// ע�⣺
// 1    Templates ���ɶ��classes �� ������� �������κ�template ���붼������ĳ���������
//      ��tempalte��������������ϵ ...
// 2    �������ģ�����(non-type tempalte parameters)����ɵĴ������ͣ�������������������
//      ���Ժ���������classes ��Ա�����滻 template ���� ...
// 3    �����Ͳ���(type parameters) ����ɵĴ������ͣ��������Խ��ͣ��������õ�����ȫ��ͬ
//      �����Ʊ���(binary representations)�ľ�������(instantiation types)����ʵ���� ....
namespace testItem44
{
    //1  --- û�н�������޹صĴ������ templateS ...
    template <typename T ,std::size_t N>
    class SquareMatrix_
    {
    public:
        // ...
        void invert() ;// ������� ...
    } ;
    template <typename T ,std::size_t N>
    void SquareMatrix_<T ,N>::invert() {} // ...
    // ����Ϊ SquareMatrix ��N ��ͬ���ֳ��ܶ����ͣ����´������� ...
    void exampleFunc()
    {
        SquareMatrix_<double ,5> sm1 ;
        // ...
        sm1.invert() ;
        SquareMatrix_<double ,10> sm2 ;// sm1 �� sm2 ��ͬ���� ...
        // ...
        sm2.invert() ;
    }
    //2  --- ��������޹صĴ������ templateS ...
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
        //T   pData_[N*N] ;// ���ܵ���class SquareMatrix �����С�ܴ� ...���ݴ洢�ڳ���ջ ...
        std::tr1::scoped_array<T> pData_ ; // or: std::tr1::scoped_array<T>�����ݴ洢�ڶ� ...
    } ;
    // �������ݴ洢�ںδ��������͵ĽǶ�����֮���ؼ����������SquareMatrix��Ա�������Ե�������
    // inline ��ʽ����base class �汾��������"����ͬ��Ԫ�ء������۾����С��֮���о����� ..

}//namespace testItem44
// ====================================================================
// --- ����45�����ó�Ա����ģ��������м������� ...
// ע�⣺
// 1    ��ʹ�ó�Ա����ģ��(member function templates) ���ɡ��ɽ������м������͡��ĺ��� ...
// 2    ����������� member templates ���� ������copy ���조�򡱷��� assignment���������㻹����Ҫ
//      ����������copy ���캯����copy assignment ������ ...
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
    // ... ���գ�boost::shared_ptr<T>����ϸʵ�� ...
    void exampleFunc()
    {
        /*
        Top* pt1 = new Middle ;// ��Middle* ת��Ϊ Top* ---�Զ�
        Top* pt2 = new Bottom ;// ��Bottom* ת��Ϊ Top* ---�Զ�
        const Top pct1 = pt1 ; // ��Top* ת��Ϊ const Top* ---�Զ�
        */
        SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle) ;
        SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom) ;
        SmartPtr<const Top> pct1 = pt1 ;
        SmartPtr<Top> pt3(pt1) ,pt4 ;
        pt4 = pt2 ;
    }
}//namespace testItem45
// ====================================================================
// --- ����46����Ҫ����ת��ʱ��Ϊģ�嶨��ǳ�Ա���� ...��������24 ...
// ע�⣺
// 1    �����Ǳ�дһ�� class template ���������ṩ֮�����template��صġ�����֧�֡����в���
//      ֮��ʽ����ת����ʱ���뽫��Щ��������Ϊ��class template�ڲ���friend���� �� ...
// 2
// 3
namespace testItem46
{
    // ������ template class Rational ....
    template <typename T>
    class Rational ;
    // ������ ���� doMutilply ....
    template <typename T>
    const Rational<T>  doMutilply(const Rational<T>& lhs ,const Rational<T>& rhs) ;
    //
    template <typename T>
    class Rational
    {
    private:
        T n_ ,d_ ;
    public:
        Rational(T numerator = T(0) ,T denominator = T(1) )//����24˵��Ϊʲô������캯��
        : n_(numerator) ,d_(denominator)
        {}// ... ������Ϊ explicit ...
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
            //doMutilply(lhs ,rhs) ; // or :�����ⲿ�������� ... �ܺõĵ��� ������
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
// --- ����47
// ע�⣺
// 1
// 2
// 3
namespace testItem47
{
}//namespace testItem47
// ====================================================================
// --- ����48����ʶtemplate Ԫ���
// ע�⣺
// 1��Template metaprogramming(TMP ��ģ��Ԫ���)�ɽ����������������������ڣ�
//    �������ʵ�����ڴ������͸��ߵ�ִ��Ч��
// 2��TMP �ɱ���������"���ڲ���ѡ�����" �Ŀͻ����ƴ��룬Ҳ����������������
//    ��ĳЩ�������Ͳ������ʵĴ���
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
// --- ����
// ע�⣺
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem
// ====================================================================
// --- ����49
// ע�⣺
// 1
// 2
// 3
namespace testItem
{
}//namespace testItem

// ================================================================
#endif // UNIT4_H_INCLUDED
