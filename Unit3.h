#ifndef UNIT3_H_INCLUDED
#define UNIT3_H_INCLUDED


//# pragma warning(push)
//# pragma warning(disable:8057) //
// ===  �塢ʵ�� ======================================================
// ====================================================================
// --- ����26���������Ӻ��������ʽ�ĳ���ʱ�� ...
// ע�⣺
// 1    �������Ӻ��������ʽ�ĳ���ʱ�䣬�������������ӳ���������Ȳ����Ƴ����Ч��
// 2
namespace testItem26
{
    void encrypt(std::string& s) {} // ...
    #define MINPWDLEN 10
    string encrtptPassword(const string& pwd)
    {
        using namespace std ;
        if(pwd.size() < MINPWDLEN )
            throw logic_error("Password is too short") ;
        string encrypted(pwd) ;
        encrypt(encrypted) ;
        return encrypted ;
    }
    void exampleFunc()
    {
        using testItem10::Widget ;
        // 1    1�����캯��+1����������+n����ֵ�������ɱ���
        // ...
        Widget w ;
        for(int i=0 ;i<10 ;i++) // n = 10
        {
            w = Widget(i) ;
            // ....
        }
        // ...
        // 2    n�����캯��+n���������� ... ���ɱ���
        // ...
        for(int i=0 ;i<10 ;i++)
        {
            Widget w = Widget(i) ;
            // ....
        }
        // ...

    }
}//namespace testItem26
// ====================================================================
// --- ����27����������ת�Ͷ��� ...
// ע�⣺static_cast ,dynamic_cast ,const_cast ,reinterpret_cast ... XXX_cast<Type> (Expr)...
// 1    ������Ծ�������ת�ͣ����⣩���ر���ע��Ч�ʵĴ����У�����dynamic_cast S��
//      ����и������Ҫת�Ͷ��������ŷ�չ����ת�͵������� ....
// 2    ���ת�͵ı���ģ����Ž���������ĳ���������󡣿ͻ������Ե��øú�����
//      �����轫ת�ͷŽ����ǵ��Լ������ڡ�
// 3    ����ʹ�� C++ Style����ʽ��ת�ͣ���Ҫʵ���ʽת�͡�ǰ�ߺ����ױ�������
//      ����Ҳ�Ƚ����ŷ��ű����ְ�� ��
namespace testItem27
{
    // ����ʹ�� dynamic_cast ������һ�������� for void blink()���£� 11111 ��22222
    class Window
    {
    public:
        virtual void OnResize() { } // ....
        virtual void blink() {} // 22222
        // ...
    } ;
    class SpecialWindow : public Window
    {
    public:
        void OnResize()  // virtual ....
        {
            //static_cast<Window>(*this).OnResize() ;// error ,��ʱ����...!!!
            Window::OnResize() ; // okokok....
        }
        void blink()  //...virtual
        { cout << " virtual void SpecialWindow::blink()\n"; }
    } ;
    typedef std::vector<std::tr1::shared_ptr<Window> > VPW ;
    typedef std::vector<std::tr1::shared_ptr<SpecialWindow> > VSPW ;
    void exampleFunc()
    {
        //  1))))
        {
        VPW winPtrs ;
        // ...
        for(VPW::iterator iter = winPtrs.begin() ;//��ϣ��ʹ��dynamic_cast ...
            iter != winPtrs.end() ;iter++)
            if( SpecialWindow* psw = dynamic_cast<SpecialWindow*>(iter->get()) )
                psw->blink() ;
        }
        {
        //  2))))
        VSPW   winPtrs ; //��һ��11111
        // ...
        for(VSPW::iterator iter = winPtrs.begin() ;//�����ȽϺã���ʹ��dynamic_cast ...
            iter != winPtrs.end() ;iter++)
                (*iter)->blink() ;
        }
        {
        //  3))))
        VPW    winPtrs ; // ������22222
        // ...
        for(VPW::iterator iter = winPtrs.begin() ;//�����ȽϺã���ʹ��dynamic_cast ...
            iter != winPtrs.end() ;iter++)
                (*iter)->blink() ;
        }
    }
    //1)

}//namespace testItem27
// ====================================================================
// --- ����28�����ⷵ��handles ָ�������ڲ��ɷ� ...
// ע�⣺
// 1    ���ⷵ�� handles������references��ָ�롢��������ָ������ڲ��������������
//      �������ӳ���ķ�װ�ԣ�����const ��Ա��������Ϊ���const��������������������ơ�
//      (dangling handles) �Ŀ����Խ�������� ...
// 2
// 3
namespace testItem28
{
    class Point
    {
    private:
        int x ,y ;
    public:
        Point() : x(0) ,y(0) {} // ...
        Point(int x ,int y) : x(x) ,y(y) {}
        // ...
        void setX(int X) { x = X ;}
        void setY(int Y) { y = Y ;}
        int  getX() const {return x ; }
        int  getY() const {return y ; }
        void print() const ;
        // ...
    } ;
    void Point::print()const
    { cout << " X: "<< x << " ,Y: " << y << "\n" ; }
    struct RectData
    {
        Point ulhc ;
        Point lrhc ;
    } ;
    class Rectangle
    {
    private:
        std::tr1::shared_ptr<RectData> pData ;
    public:
        // ...
        Rectangle():pData(new RectData) { }
        // ...
        const Point& upperLeft() const// return non-const,warn !!!,but ,Point& ���ܳ���--���������
        { return pData->ulhc ; } //
        const Point& lowerRight() const//return non-const,warn !!!,but ,Point& ���ܳ���--���������
        { return pData->lrhc ; } //
        // or : ... if okokok...
        /*
        Point& upperLeft() //
        { return pData->ulhc ; } //
        Point& lowerRight() //
        { return pData->lrhc ; } //
        */
    } ;
    // ... for example :Point& ���ܳ���--���������
    class GUIObject {} ; // ...
    const Rectangle boundingBox(const GUIObject& obj)// ...
    {
        Rectangle rect ;
        // ...
        return rect ;
    }  // ...
    void exampleFunc()
    {
        GUIObject GUIObj ;
        // ...
        const Point* pUpperLeft = &(boundingBox(GUIObj).upperLeft()) ;
        //.pUpperLeft ,dangerous pUpperLeft from ��ʱ���� reference ( from boundingBox function ...)
        pUpperLeft->print() ;
        //  ...
    }
}//namespace testItem28
// ====================================================================
// --- ����29��Ϊ���쳣��ȫ����Ŭ��ʱֵ�õ�
// ע�⣺
// 1    �쳣��ȫ����( Exception-safe functions)��ʹ�����쳣Ҳ����й¶��Դ�������κκ���
//      �ṹ�ܻ��������ĺ�������Ϊ���ֿ��ܵı�֤������(��ŵ)�͡�ǿ���͡������쳣�͡�
// 2    ��ǿ�ұ��ա������ܹ���copy-and-swapʵ�ֳ���������ǿ�ұ�֤�����Ƕ����к���������ʵ��
//      ���Ǿ߱���ʵ���� ...
// 3    �����ṩ�ġ��쳣��ȫ��֤��ͨ�����ֻ�����������ú����еġ��쳣��ȫ��֤���е������� ��
namespace testItem29
{
    class Image
    {
    public:
        Image(std::istream& imgSrc) {} // ...
    } ; // ...
    using testItem14::Mutex ;
    using testItem14::Lock ;
    //for: 4     better ...
    struct PMImpl
    {
        std::tr1::shared_ptr<Image> pImage ;
        int     imageChanges ;
    } ;
    class PrettyMenu
    {/*
    public:
        using testItem14::Mutex ;
        using testItem14::Lock ;*/ //error
    private:
        //for:1 ,2       worse ,bad ...
        Mutex mutex ;
        Image*  pImage ;
        int     imageChanges ;
        //for: 3    good ...
        std::tr1::shared_ptr<Image> spImage ;
        //for: 4     better ...
        std::tr1::shared_ptr<PMImpl> pImpl ;
    public:
        // ...
        void changeBackground(std::istream& imgSrc) ;

    } ;
    void PrettyMenu::changeBackground(std::istream& imgSrc)
    {
        //4     better ...
        Lock m1(&mutex) ;
        std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl)) ; //��ø��� ...
        pNew->pImage.reset(new Image(imgSrc)) ;// �޸ĸ��� ...
        ++pNew->imageChanges ;
        using std::swap ;
        //swap(pImpl ,pNew) ;// ...�û�����...
        pNew.swap(pImpl) ;// ??? ...
        /*
        // 3    good ...
        Lock m1(&mutex) ;
        spImage.reset(new Image(imgSrc)) ;//...
        ++imageChanges ;
        /*==========================
        // 2    bad ....
        Lock m1(&mutex) ;
        delete pImage ;
        ++imageChanges ;
        pImage = new Image(imgSrc) ;
        /* ==========================
        // 1    worse ....
        using namespace testItem14 ;
        lock(&mutex) ;
        delete pImage ;
        ++imageChanges ;
        pImage = new Image(imgSrc) ;
        unlock(&mutex) ;
        //=========================*/
    }
}//namespace testItem29

namespace std
{   /* ....*/// for std::tr1::shared_ptr<T>::swap ...
    //for: 3    good ...
    typedef testItem29::Image* ImagePtr ;
    template<>
    void swap<ImagePtr>(ImagePtr& a ,ImagePtr& b)
    {
        ImagePtr temp = a ;
        a = b ;
        b = temp ;
    }
    //for:4     better ...
    typedef testItem29::PMImpl* PMImplPtr ;
    template<>
    void swap<PMImplPtr>(PMImplPtr& a ,PMImplPtr& b)
    {
        PMImplPtr temp = a ;
        a = b ;
        b = temp ;
    }
}
// ====================================================================
// --- ����30��͸���˽� inlining (inline) ���������� ...
// ע�⣺inline �Ǹ����룬���������Լ��Ժ���(�� inline �������ڸ���) ...
// 1    �������inlining������С�ͣ���Ƶ�����õĺ������ϡ����ʹ�պ�ĵ��Թ���
//      �Ͷ���������(binary upgradability)�����ף�Ҳ��ʹǱ�ڵĴ�������������С����
//      ʹ������ٶ������������ ...
// 2    ��Ҫֻ��Ϊ function templateS ������ͷ�ļ����ͽ��������� inline ��
// 3    ������ͨ�����ԡ�ͨ������ָ������еĵ��á�ʵʩinlining ...��ʱ�������캯��
//      ���������� ... ��ʱ����������Զ��������ߵ�outline ���� ...����(ʵ����)
//      ���������������inlining������ѡ����ס�����������Զ�Ϊ���죬�����������
namespace testItem30
{
    class Person
    {
    private:
        int     theAge ;
        //...
    public:
        int age() const { return theAge ; }
        // һ��������inline���룺age() ������class����ʽ��
        // ...
    } ;
    template <typename T>
    inline const T& Max(const T& a ,const T& b)//��ȷ����inline ...
    { return a < b ? b : a ; } //

    inline void inlineFunc()
    { cout << " inline void inlineFunc() ...\n" ; } // ...
    void exampleFunc()
    {
        void (*pFunc)() ;
        pFunc = inlineFunc ;
        inlineFunc() ; //������ý���inlined ����Ϊ����һ���������� ...
        pFunc() ;//������û���(ͨ��)����inlined����Ϊ��ͨ������ָ����� ...
    }

}//namespace testItem30
// ====================================================================
// --- ����31�����ļ���ı��������ϵ������� ...
// ע�⣺
// 1    ֧�֡�������������С������һ�㹹���ǣ�����������ʽ����Ҫ�����ڶ���ʽ��
//      ���ڴ˹���������ֶ��ǣ� Handle classes �� Interface clases ...
// 2    �����ͷ�ļ�Ӧ���ԡ���ȫ�ҽ�������ʽ��( full and delaration-only forms)
//      ����ʽ���ڡ��������������Ƿ��漰 templateS ������ ...
// 3
namespace testItem31
{
    // --- Handle classes ------------------------
    // As file Date.h ,Address.h
    using testItem18::Date ;
    // class   Address {} ;// ...
    typedef std::string Address ;
    // As file PersonImpl.h
    class   Date ;
    //class   Address ;
    class PersonImpl
    {
    private:
        std::string theName ;
        Date    theBirthday ;
        Address theAddress ;
    public:
        PersonImpl(const string& name ,const Date& birthday ,
                   const Address& addr)
        :theName(name) ,theBirthday(birthday) ,theAddress(addr) {}
        string name() const { return theName ; }
        Date birthday() const { return theBirthday ; }
        Address address() const { return theAddress ; }
        // ...
    } ;
    // As file Person.h
    // #include <...>
    class PersonImpl ;
    class   Date ;
    //class   Address ;
    class Person
    {
    private:
        std::tr1::shared_ptr<PersonImpl> pImpl ;
    public:
        Person(const string& name ,const Date& birthday ,
               const Address& addr) ;
        string  name() const ;
        Date    birthday() const ;
        Address address() const ;
        // ...
    } ;
    // As file Person.cpp
    //#include <...>
    //#include "Person.h"
    //#include "PersonImpl.h"
    Person::Person(const string& name ,const Date& birthday ,
                   const Address& addr)
    : pImpl(new PersonImpl(name ,birthday ,addr ) ) {}
    string Person::name() const { return pImpl->name() ; }
    Date Person::birthday() const { return pImpl->birthday() ; }
    Address Person::address() const { return pImpl->address() ; }
    void printPerson(const Person& p)
    {
        cout << " void printPerson(const Person& p) ... \n" ;
        cout << setfill(' ')<< left ; // ;
        cout << setw(19) << " p.name(): " << p.name()
             << setw(20) << "\n p.birthday() : " << p.birthday()
             << setw(20) << "\n p.address(): " <<  p.address() <<"\n" ;
    }
    // ..


    // --- Interface classes ------------------------
    class Person_
    {// ... none member data ...
    public:
        virtual ~Person_() {} ;
        virtual string name() const = 0 ;
        virtual Date    birthday() const = 0 ;
        virtual Address address() const = 0 ;

        static std::tr1::shared_ptr<Person_> create(
               const string& name ,const Date& birthday ,
               const Address& addr) ;
        // ...
    } ;
    void printPerson(const Person_& p)
    {
        cout << " void printPerson(const Person& p) ... \n" ;
        cout << setfill(' ')<< left ; // ;
        cout << setw(19) << " p.name(): " << p.name()
             << setw(20) << "\n p.birthday() : " << p.birthday()
             << setw(20) << "\n p.address(): " <<  p.address() <<"\n" ;
    }
    class RealPerson : public Person_
    {
    private:
        std::string theName ;
        Date    theBirthday ;
        Address theAddress ;
    public:
        RealPerson(const string& name ,const Date& birthday ,
                   const Address& addr)
        :theName(name) ,theBirthday(birthday) ,theAddress(addr) {}
        virtual ~RealPerson() {}
        string  name() const { return theName ; }
        Date    birthday() const { return theBirthday ; }
        Address address() const { return theAddress ; }
        // ...
    } ;
    std::tr1::shared_ptr<Person_> Person_::create(
           const string& name ,const Date& birthday ,
           const Address& addr)
    {
        return std::tr1::shared_ptr<Person_>(new RealPerson(name ,birthday ,addr) ) ;
    }

}//namespace testItem31


// ===  �����̳������������� ========================================
// ====================================================================
// --- ����32:ȷ�����public �̳���ģ��is-a ��ϵ
// ע�⣺
// 1    ��public�̳С���ζ�� is-��������base classes���ϵ�ÿһ����һ��Ҳ���� derived classes
//      ���ϣ���Ϊÿһ�� derived class����Ҳ����һ��base class ���� ...
// 2    is-a������Ψһ������classes֮��Ĺ�ϵ���������ֳ����Ĺ�ϵ��has-a��is-implementd-in-terms-of
// 3
namespace testItem32
{
    class Bird
    {
        // ...
        // virtual void fly() const = 0 ;
    } ;
    class FlyingBird : public Bird
    {
        virtual void fly() const = 0 ;
    } ;
    class Penguin : public Bird// ��� ... no fly
    {
        // ...
    } ;
    class Rectangle
    {
    public:
        Rectangle():height_(0) ,width_(0) {}
        Rectangle(int h ,int w) : height_(h) ,width_(w) {}
        virtual void setHeight(int h) ;
        virtual void setWidth(int w) ;
        virtual int  getHeight() const ;
        virtual int  getWidth() const ;
        // ...
    private:
        int height_ ,width_ ;
    } ;
    void Rectangle::setHeight(int h) { height_ = h ; }
    void Rectangle::setWidth(int w) { width_ = w ; }
    int  Rectangle::getHeight() const { return height_ ; }
    int  Rectangle::getWidth() const { return width_ ; }
    void makeBigger(Rectangle& r)
    {
        int oldHeight = r.getHeight() ;
        r.setWidth(r.getWidth()+10) ;
        assert(r.getHeight()==oldHeight) ;//�ж�r�ĸ߶��Ƿ�δ���ı� ...
    }
    //Warn: class Square : public Rectangle ,Square and Rectangle not is-a ...
    class Square : public Rectangle
    {
    public:
        Square() : Rectangle() {}
        Square(int x) : Rectangle(x ,x) {}
        //void Rectangle::setHeight(int h) { width_ = height_ = h ; }//should do ...
        //void Rectangle::setWidth(int w) { height_ = width_ = w ; }
        //
    } ; // ...
    void exampleFunc()
    {
        Square s ;
        assert(s.getWidth()==s.getHeight()) ;//�������������α���Ϊ��
        makeBigger(s) ;// ������� ...
        assert(s.getWidth()==s.getHeight()) ;//�������������α���Ϊ��
        // ...
    }


}//namespace testItem32
// ====================================================================
// --- ����33���������ڼ̳ж���������
// ע�⣺
// 1    derived classes �ڵ����ƻ�����base classes �ڵ����ơ���public�̳��´���û����ϣ�����
// 2    Ϊ���ñ����ڵ������ټ����գ�����ʹ��using����ʽ��ת��������forwarding function��
// 3
namespace testItem33
{
    class Base
    {
    private:
        int x ;
    public:
        virtual void mf1() = 0 ;
        virtual void mf1(int)
        { cout << " virtual void  Base::mf1(int)\n" ; }
        virtual void mf2() {} ;
        void mf3()
        { cout << " void Base::mf3()\n" ; }
        void mf3(double)
        { cout << " void Base::mf3(double)\n" ; }
        // ...
    } ;
    void Base::mf1()
    { cout << " virtual void  Base::mf1()\n" ; }
    class Derived_1 : public Base
    {
    public:
        using Base::mf1 ; // �� Base class ����Ϊ mf1��mf3�����ж�����
        using Base::mf3 ;//Derived �������ڶ��ɼ� ��okokok
        virtual void  mf1()
        { cout << " virtual void  Derived_1::mf1()\n" ; }
        // Warning W8022 : 'Derived_1::mf1()' hides virtual function 'Base::mf1(int)'|
        void mf3()
        { cout << " void Derived_1::mf3()\n" ; }
        void    mf4() ;//{ cout << " \n" ; }
        // ...
    } ;
    class Derived_2 : private Base
    {
    public:
        virtual void mf1()// ת���������Գ�Ϊinline
        { Base::mf1() ; cout << " virtual void  Derived_2::mf1()\n\n" ;}
        // Warning W8022 : 'Derived_2::mf1()' hides virtual function 'Base::mf1(int)'|
    } ;
}//namespace testItem33
// --- ����34�����ֽ�ڼ̳к�ʵ�ּ̳�
// ע�⣺
// 1    �ӿڼ̳к�ʵ�ּ̳в�ͬ����public�̳�֮�£�derived classes ���Ǽ̳�base class �Ľӿ�
// 2    pure virtual ����ֻ����ָ���ӿڼ̳У������Ե�����ʵ��--ת������ʵ�֣�
// 3    ���ӵģ��Ǵ���impure virtual �����ǻ�����ָ����ڼ̳м�ȱʡʵ�ּ̳�
// 4    non-virtual ��������ָ���ӿڼ̳��Լ�ǿ����ʵ�ּ̳�
namespace testItem34
{
    class Shape
    {
    private:
        unsigned int ID ;
        static   unsigned int objectNUM ;
    public:
        Shape() { ID = ++objectNUM ; }
        virtual ~Shape() {}
        virtual void draw() const =0  ;
        int objectID() const { return ID ; }
        void    testError()
        { error(std::string(typeid(*this).name())+",error!!!") ; }
        // ...
    protected:
        virtual void error(const std::string& msg) const ;
    } ;
    unsigned int Shape::objectNUM = 0 ;
    void Shape::draw() const
    {/*
        if(this==NULL)
            error("this==NULL,error!!!") ;
        else*/
        try
        {
            cout << " void Shape::draw() const \n" ;
        }
        catch(...)
        {
            error(std::string(typeid(*this).name())+",error!!!") ;
        }
    }
    void Shape::error(const std::string& msg)const
    {
        cout << " virtual void Shape::error(const std::string& msg) : \n" \
             << " msg: " << msg << "\n" ;
    }
    class Rectangle : public Shape {virtual void draw() const ; } ;// must declarate draw()....
    void Rectangle::draw() const
    { cout << " void Rectangle::draw() const\n" ; }
    class Ellipse : public Shape {virtual void draw() const ; } ;
    void Ellipse::draw() const
    { cout << " void Ellipse::draw() const\n" ; }
// ------------------------------------------- no better
    class Airport
    {
    private:
        const char* strID ;
    public:
        explicit Airport(const char* str):strID(str) {}
        const char* airportID() const { return strID ; }
    } ;
    class Airplane_1
    {
    public:
        virtual void fly(const Airport& destination) // = 0
        {
            cout << " virtual void Airplane_1::fly(const Airport& destination) \n"
                 << " destination.airportID(): " << destination.airportID()<< "\n" ;
        }
        // ...
    } ;
// -------------------------------------------better
    class Airplane_3
    {
    public:
        virtual void fly(const Airport& destination) = 0 ;
        // ...
    } ;
    void Airplane_3::fly(const Airport& destination) // = 0
    {
        cout << " void Airplane_3::fly(const Airport& destination) -- "
             << typeid(*this).name() << "\n"
             << " destination.airportID(): " << destination.airportID()<< "\n" ;
    }
    class ModelD : public Airplane_3
    {
    public:
        void fly(const Airport& destination) { Airplane_3::fly(destination) ; }
    } ;
    class ModelE : public Airplane_3
    {
    public:
        void fly(const Airport& destination) { Airplane_3::fly(destination) ; }
    } ;
    class ModelF : public Airplane_3
    {
    public:
        void fly(const Airport& destination)
        {
            cout << " void ModelF::fly(const Airport& destination)\n"
                 << " destination.airportID(): " << destination.airportID()<< "\n" ;
        }
    } ;
// -------------------------------------------better
    class Airplane_2
    {
    public:
        virtual void fly(const Airport& destination) = 0 ;
        // ...
    protected:
        virtual void defaultFly(const Airport& destination) // ...
        {
            cout << " void Airplane_2::defaultFly(const Airport& destination) -- "
                 << typeid(*this).name() << "\n"
             << " destination.airportID(): " << destination.airportID()<< "\n" ;
        }
    } ;
    class ModelA : public Airplane_2
    {
    public:
        void fly(const Airport& destination)
        { defaultFly(destination) ; }
    } ;
    class ModelB : public Airplane_2
    {
    public:
        void fly(const Airport& destination)
        { defaultFly(destination) ; }
    } ;
    class ModelC : public Airplane_2
    {
    public:
        void fly(const Airport& destination)
        {
            cout << " void ModelC::fly(const Airport& destination)\n"
                 << " destination.airportID(): " << destination.airportID()<< "\n" ;
        }
    } ;
}//namespace testItem34
// ====================================================================
// --- ����35������virtual ����֮�������ѡ�� ...
// ע�⣺
// 1    virtual�����������������NVI(Non-Virtual Interface)�ַ���Strategy���ģʽ�Ķ�����ʽ��
//      NVI�ַ�������һ��������ʽ�� Template Methodģʽ(��C++ templateS ���޹���)
// 2    �����ܴӳ�Ա�����Ƶ�class �ⲿ������������һ��ȱ����ǣ��ǳ�Ա�����޷�����non-public��Ա
// 3    tr1::function�������Ϊ����һ�㺯��ָ�롣�����Ķ���ɽ��ɡ������֮Ŀ��ǩ��ʽ���ݡ���
//      ���пɵ�����( callable entities ) ...
namespace testItem35
{
    class GameCharacter_
    {
    public:
        virtual int healthValue() const //non-pure virtual function and default implemenet ...
        {
            int retValue = 0 ;
            // ...
            return retValue ;
        } ;
    } ;
    // 1)   ����Non-Virtual Interface �ַ�ʵ�� Template Method ģʽ ...
    class GameCharacter_1
    {
    public:
        int healthValue() const
        {
            // ...
            int retValue = doHealthValue() ;
            // ...
            return retValue ;
        }
    private:
        virtual int doHealthValue() const
        {//
            int retValue ;
            // ...
            return retValue ;
        }
    } ;
    // 2)   ����Function Pointers ʵ�� Strategy ģʽ ...
    class GameCharacter_2 ;
    int defaultHealthCalc(const GameCharacter_2& gc) { return int(1) ;} // ...
    class GameCharacter_2
    {
    public:
        typedef int (*HealthCalcFunc)(const GameCharacter_2& gc) ;
        explicit GameCharacter_2(HealthCalcFunc hcf =defaultHealthCalc)
        : healthFunc(hcf) {}
        int healthValue() const
        { return healthFunc(*this) ; }
    private:
        HealthCalcFunc healthFunc ;
    } ;
    //1     ͬһ��������֮��ͬʵ������в�ͬ�Ľ������㺯��  ...
    class EvilBadGuy_2 : public GameCharacter_2
    {
    public:
        explicit EvilBadGuy_2(HealthCalcFunc hcf = defaultHealthCalc)
        : GameCharacter_2(hcf) {} // ...
        // ...
    } ;
    int loseHealthQuickly(const GameCharacter_2&) {return 2 ; }// ...
    int loseHealthSlowly(const GameCharacter_2&) {return 1 ; }// ...
    void exampleFunc_2()
    {
        EvilBadGuy_2 ebg1(loseHealthQuickly) ;
        EvilBadGuy_2 ebg2(loseHealthSlowly) ;
    }
    //2     ����ı��֪����Ľ���ָ�����㺯�������������ڱ�� ...
    // ....
    /**/
    // 3)   ���� tr1::function ���Stratagy ģʽ ...


    class GameCharacter_3 ;
    int defaultHealthCalc(const GameCharacter_3& gc) { return int(1) ;} // ...
    class GameCharacter_3
    {
    public:
        typedef boost::function<int (const GameCharacter_3&) > HealthCalcFunc ;
        // HealthCalcFunc �������κΡ��ɵ���������µ��ò�����
        // �κμ����� GameCharacter_3 ֮������κμ�����int �Ķ��� ....
        explicit GameCharacter_3(HealthCalcFunc hcf =defaultHealthCalc)
        : healthFunc(hcf) {}
        int healthValue() const
        { return healthFunc(*this) ; }
    private:
        HealthCalcFunc healthFunc ;
    } ;
    short calcHealth(const GameCharacter_3&) { return 1 ; }// ..
    struct HealthCalculator
    {
        int operator () (const GameCharacter_3&) const
        { // ...
            return int(1) ;
        }
    } ;
    class GameLevel
    {
    public:
        float health(const GameCharacter_3&) const
        { return 1.0 ; } // ...
        // ...
    } ;
    class EvilBadGuy_3 : public GameCharacter_3
    {// ....
    public:
        EvilBadGuy_3(HealthCalcFunc hcf)
        : GameCharacter_3(hcf) {} // ...
    } ;
    class EyeCandyCharacter_3 : public GameCharacter_3
    { // ...
    public:
        EyeCandyCharacter_3(HealthCalcFunc hcf)
        : GameCharacter_3(hcf) {} // ...
    } ;
    void exampleFunc_3()
    {
        EvilBadGuy_3 ebg1(calcHealth) ;
        EyeCandyCharacter_3 ecc1(HealthCalculator()) ;

        GameLevel currentLevel ;
        EvilBadGuy_3 ebg2(std::tr1::bind(&GameLevel::health ,currentLevel ,_1) ) ;
        // ...
    }

    // 4)   ���ɹŵ�� Stratagy ģʽ ...
    class GameCharacter_4 ;
    class HealthCalcFunc
    {
    public:
        virtual int calc(const GameCharacter_4& gc) const
        { return int(1) ; } // ...
        // ...
    } ;
    HealthCalcFunc defaultHealthCalcFunc ;
    class GameCharacter_4
    {
    private:
    HealthCalcFunc* pHealthCalc ;
    public:
        explicit GameCharacter_4(HealthCalcFunc* phcf = &defaultHealthCalcFunc)
        : pHealthCalc(phcf) {}
        int healthValue() const
        { return pHealthCalc->calc(*this) ; }
        // ...
    } ;
    // and ...
    class SlowHealthLoser : public HealthCalcFunc
    {
    public:
        int calc(const GameCharacter_4& gc) const
        { return int(1) ; }
    } ;
    class FastHealthLoser : public HealthCalcFunc
    {
    public:
        int calc(const GameCharacter_4& gc) const
        { return int(2) ; }
    } ;

}//namespace testItem35
// ====================================================================
// --- ����36���������¶���̳ж�����non-virtual���� ...
// ע�⣺
// 1    ���Բ�Ҫ���¶���̳ж�����non-virtual����
// 2
// 3
namespace testItem36
{
    class Base
    {
    public:
        void nonvirFunc() const ;
        // ...
    } ;
    void Base::nonvirFunc() const
    { cout << " void Base::nonvirFunc() const\n" ; }
    class Derived : public Base
    {
    public:
    //   Waring ....
        void nonvirFunc() const ;//����(hides) ��Base::nonvirFunc ..������33
        // ...
    } ;
    void Derived::nonvirFunc() const
    { cout << " void Derived::nonvirFunc() const\n" ; }
    void exampleFunc()
    {
        Derived d ;
        Derived* pD = &d;
        Base*    pB = &d ;
        pB->nonvirFunc() ;// ����Base::nonvirFunc
        pD->nonvirFunc() ;// ����Derived::nonvirFunc
    }
}//namespace testItem36
// ====================================================================
// --- ����37���������¶���̳ж�����ȱʡ����ֵ ...
// ע�⣺
// 1    ���Բ�Ҫ���¶���̳ж�����ȱʡ����ֵ����Ϊȱʡ����ֵ���Ǿ�̬��(������)��
//      �� virtual ����--��ΨһӦ�ø��ǵĶ���--ȴ�Ƕ�̬�� ...
// 2
// 3
namespace testItem37
{
    class Shape
    {
    public:
        enum ShapeColor { Red = 1 ,Green ,Blue } ;
        virtual void draw(ShapeColor color = Red) const = 0 ;
        // ...
    } ;
    class Rectangle : public Shape
    {
    public:
    //  ע�⣺���費ͬ��ȱʡ����ֵ�����Ǻ���� ...
        void draw(ShapeColor color = Green) const //Warn--���¶���̳ж�����ȱʡ����ֵ,but ...
        { cout << " virtual void Rectangle::draw(ShapeColor color)const ,color: "<< color << "\n" ; }
        // ...
    } ;
    class Circle : public Shape
    {
    public:
        void draw(ShapeColor color) const //OK--�̳�ȱʡ����ֵ ...
        { cout << " virtual void Circle::draw(ShapeColor color)const ,color: "<< color << "\n" ; }
        // ...
    } ;
    void exampleFunc()
    {
        Shape* pS ;
        Shape* pR = new Rectangle ;
        Shape* pC = new Circle ;
        cout << " pR->draw() ;...\n" ;  pR->draw() ;
        cout << " pC->draw() ;...\n" ;  pC->draw() ;
        pS = pR ;   cout << " pS = pR ;pS->draw() ;...\n" ;  pS->draw() ;
        pS = pC ;   cout << " pS = pC ;pS->draw() ;...\n" ;  pS->draw() ;
        delete pR ; delete pC ;

        Rectangle r ;
        Circle    c ;
        cout << " r.draw() ;...\n" ;  r.draw() ;
        //cout << "  c.draw() ;...\n" ;  c.draw() ;
        //Error E2193 : Too few parameters in call to 'Circle::draw(Shape::ShapeColor) const' in function exampleFunc()|
        pS = &r ;   cout << " pS = &r ;pS->draw() ;...\n" ;  pS->draw() ;
        pS = &c ;   cout << " pS = &c ;pS->draw() ;...\n" ;  pS->draw() ;
    }
    //  �����Ʒ����� NVI(non-virtual interface ) ...virtual to non-virtual ...
    class Shape_
    {
    public:
        enum ShapeColor { Red = 1 ,Green ,Blue } ;
        void draw(ShapeColor color = Red) const { doDraw() ; }
        // ...
    private:
        virtual void doDraw(ShapeColor color = Red) const = 0 ;
    } ;
    class Rectangle_ : public Shape_
    {
    public:
        // ...
    private:
        void doDraw(ShapeColor color) const
        { cout << " virtual void Rectangle_::doDraw(ShapeColor color)const ,color: "<< color << "\n" ; }
    } ;
    class Circle_ : public Shape_
    {
    public:
        // ...
    private:
        void doDraw(ShapeColor color) const
        { cout << " virtual void Circle_::doDraw(ShapeColor color)const ,color: "<< color << "\n" ; }
    } ;
    // ����non-virtual����Ӧ�þ��Բ���derived classes ��д(������36)��
    // �����ƺ������ʹ��draw������ color ȱʡ����ֵ���� Red ��
    // ...

}//namespace testItem37
// ====================================================================
// --- ����38��ͨ��������ģ��has-a��is-implemented-in-terms-of (������ĳ��ʵ�ֳ���)
// ע�⣺
// 1    ����(composition)�������public�̳���ȫ��ͬ ...
// 2    ��Ӧ����(application domain) ��������ζ has-a����ʵ����(implementation domain),������ζ
//      is-implementd-in-terms-of (����ĳ��ʵ�ֳ�) . ...
// 3
namespace testItem38
{
    // 1    has-a (��һ�� )��ϵ ....
    class Address {} ;// ...
    class PhoneNumber {} ;// ...
    class Person
    {
    public:
        // ...
        virtual void who() const // non-pure virtual function ...
        { std::cout << " virtual void Person::who() const ...a Person \n" ; }
        virtual ~Person() {}
    private:
        std::string name_ ;
        Address address_ ;
        PhoneNumber voiceNumber_ ;
        PhoneNumber faxNumber_ ;
        // ...
    } ;
    // for  testItem39 .....
    class Student : public Person //no public ...
    {
    public:
        // ...
        virtual void who() const
        { std::cout << " virtual void Student::who() const ...a Student \n" ; }
    } ; //
    // 2    is-implementd-in-terms-of (����ĳ��ʵ�ֳ�)
    /*
    template<typename T>
    class Set : public std::list<T>//��list Ӧ����Set�������÷� ...
    { // ...
    }// .. */
    //#include <list> // here ,error ...
    template <typename T>
    class Set
    {
    private:
        std::list<T> rep ;
    public:
        bool member(const T& item) const ;
        void insert(const T& item) ;
        void remove(const T& item) ;
        std::size_t size() const ;
        // ...
    } ;
    template <typename T>
    bool Set<T>::member(const T& item) const
    {
        return std::find(rep.begin() ,rep.end() ,item)!=rep.end() ;
    }
    template <typename T>
    void Set<T>::insert(const T& item)
    {
        if(!member(item)) rep.push_back(item) ;
    }
    template <typename T>
    void Set<T>::remove(const T& item)
    {
        typename std::list<T>::iterator it = \
        std::find(rep.begin() ,rep.end() ,item) ;
        if(it!=rep.end() ) rep.erase(it) ;
    }
    template <typename T>
    std::size_t Set<T>::size() const
    {
        return rep.size() ;
    }
    // ...
    //��Щ������˼򵥣���˶��ʺ�inlining��ѡ�� ...
}//namespace testItem38
// ====================================================================
// --- ����39�����Ƕ�������ʹ�� private �̳� ...
// ע�⣺
// 1    private�̳���ζ is-implementd-in-terms-of(����ĳ��ʵ�ֳ�)����ͨ���ȸ��ϳ�Ա(composition)
//      �ļ���͡����ǵ�derived classes ��Ҫ���� protected base class�ĳ�Ա������Ҫ���¶���̳�
//      ������ virtual ����ʱ����ô����Ǻ����
// 2    �͸���(composition)��ͬ��private�̳п������empty base class���Ż�����������ڡ�����ߴ�
//      ��С�����ĳ���⿪���߶��ԣ����ܺ���Ҫ ...
// 3
namespace testItem39
{
    using testItem38::Person ;
    class Student : private Person //no public ...
    {
    public:
        // ...
        virtual void who() const
        { std::cout << " virtual void Student::who() const ...a Student \n" ; }
    } ;
    void eat( const Person& p)
    { cout << " void eat( const Person& p) ...\n" ; p.who() ; }
    void study(const Student& s)
    { cout << " void study(const Student& s) ...\n" ; s.who() ; }
    // ---------------------------------
    class Timer
    {
    private:
        int tickFrequency_ ;
    public:
        explicit Timer(int tickFrequency = 1000)
        :tickFrequency_(tickFrequency) {}
        virtual void OnTick() const ;// ...
        //...
    } ;
    void Timer::OnTick() const { }// ...
    // 1) ************good*************
    class Widget_1 : private Timer //ע�⣬no public ...
    {
    private:
        void OnTick() const ;//�鿴Widget������ ...�ȵ�
    public:
        // ...
    } ;
    void Widget_1::OnTick() const // ...
    { cout << " void Widget_1::OnTick() const ...\n" ; }
    // 2) ************better*************���Ժܺõ����private �̳� ...
    class Widget_2
    {
    private:
        class WidgetTimer : public Timer
        {
        public:
            void OnTick() const ;
            // ...
        } ;
    WidgetTimer timer ;
    // ...
    public:
        // ...
    } ;
    void Widget_2::WidgetTimer::OnTick() const // ...
    { cout << " void Widget_2::WidgetTimer::OnTick() const ...\n" ; }
    // ������� --------------------------------
    class Empty{} ;// ...
    class HoldsAnInt_1
    {//����������HoldsAnInt_1�����С ...
    private:
        Empty e ;
        int   x ;
    } ;
    class HoldsAnInt_2 : private Empty
    {//�������Ż�HoldsAnInt_2�����С ...
    private:
        int x ;
    } ;

    void exampleFunc()
    {
        Person  p ;
        Student s ;
        testItem38::Student s_ ;
        eat(p) ;// û�����⣬p��Person  ...
        eat(s_) ;// ok ,class Student : public Person ...
        //eat(s) ;// error ,class Student : private Person ...
//Error E2064 : Cannot initialize 'const Person &' with 'Student' in function exampleFunc()|
        cout << " sizeof(int): " << sizeof(int) << "\n" ;
        cout << " sizeof(Empty): " << sizeof(Empty) << "\n" ;
        cout << " sizeof(HoldsAnInt_1): " << sizeof(HoldsAnInt_1) << "\n" ;
        cout << " sizeof(HoldsAnInt_2): " << sizeof(HoldsAnInt_2) << "\n" ;
    }
}//namespace testItem39
// ====================================================================
// --- ����40�����Ƕ�������ʹ�ö��ؼ̳� ...
// ע�⣺
// 1    ���ؼ̳б���һ�̳и��ӡ������ܵ����µ����壬�Լ���virtual�̳е���Ҫ��
// 2    virtual�̳л��������ʹ�С���ٶȡ���ʼ��(����ֵ)���Ӷȵȵȳɱ������virtual base classes
//      �����κ����ݣ��������ʹ�ü�ֵ����� ...
// 3    ���ؼ̳е�ȷ����������;������һ������漰��public�̳�ĳ��Interface class���͡�private�̳�
//      ĳ��Э��ʵ�� class ����������� ....
namespace testItem40
{
    // ���ܵ��µ����� ....
    class Base
    {
    private:
        int value_ ;
    public:
        Base() : value_(0) {}
        virtual ~Base() {} // ...
        explicit Base(int value) : value_(value) {} // ...
        int getValue() const { return value_ ; }
        void setValue(int newValue) { value_ = newValue ; }
        // ...
    } ;
    class Derived1 : public Base // non-virtual inherited...
    {
    public:
        Derived1() : Base(1) {}
        Derived1(int value ) : Base(value) {}
        // ....
    } ;
    class Derived2 : public Base// non-virtual inherited...
    {
    public:
        Derived2() : Base(2) {}
        Derived2(int value ) : Base(value) {}
        // ....
    } ;
    class Derived3 : public Derived1 ,public Derived2
    {
        // ...
    public:
    //  warning ...���� ...runtime error in GUN GCC ...
        int getValue() const { return getValue() ; }// Warn ...
        void setValue(int newValue) { setValue(newValue) ; }// Warn ...
        // should �ֿ���ƽӿ� ���� virtual �̳� ...
        int getValue1() const { return Derived1::getValue() ; }// ok ...
        void setValue1(int newValue) { Derived1::setValue(newValue) ; }
        int getValue2() const { return Derived2::getValue() ; }// ok ...
        void setValue2(int newValue) { Derived2::setValue(newValue) ; }
        void printDerived3()
        {
            cout << " Derived2::getValue(): " << Derived1::getValue()
                 << " ,Derived2::getValue(): " << Derived2::getValue() << "\n" ;
        }

    } ;// .... Derived1 : public Base // virtual ...
    //  ---- better ---------
    class Derived1_ : virtual public Base // virtual inherited...
    {
    public:
        Derived1_() : Base(1) {}
        Derived1_(int value ) : Base(value) {}
        // ....
    } ;
    class Derived2_ : virtual public Base// virtual inherited...
    {
    public:
        Derived2_() : Base(2) {}
        Derived2_(int value ) : Base(value) {}
        // ....
    } ;
    class Derived3_ : public Derived1_ ,public Derived2_
    { // and Derived3_(object) has only one Base object ...
    public:
        Derived3_() : Derived1_() ,Derived2_() {} // ...
        Derived3_(int value) : Derived1_(value) ,Derived2_(value) {} // ...
        Derived3_(int value1 ,int value2)
        : Derived1_(value1) ,Derived2_(value2) {} // ...
        int getValue() const { return getValue() ; }// okokok ...
        void setValue(int newValue)
        {
            // setValue(newValue) ;  //1 ���� ...runtime error in GUN GCC ...
            Derived1_::setValue(newValue) ; // 2
            // or :Derived2_::setValue(newValue) ;//3
        }
        void setValue1(int newValue) { Derived1_::setValue(newValue) ; }
        void setValue2(int newValue) { Derived2_::setValue(newValue) ; }
        void printDerived3_()
        {
            cout << " Derived2_::getValue(): " << Derived1_::getValue()
                 << " ,Derived2_::getValue(): " << Derived2_::getValue() << "\n" ;
        }
    } ;// ....
    // -----------------------------------------
    class BorrowableItem
    {
    public:
        void checkOut()const// ...
        { std::cout << " void BorrowableItem::checkOut()const ... \n" ;}
        // ...
    } ;
    class ElectronicGadget
    {
    private:
        void checkOut() const //...
        { std::cout << " void ElectronicGadget::checkOut()const ... \n" ;}
        // ...
    } ;
    class MP3Player : public BorrowableItem ,public ElectronicGadget
    { } ; // ...
    void exampleFunc()
    {
        MP3Player mp3 ;
//|error: request for member `checkOut' is ambiguous|
        //mp3.checkOut() ;
//���� ...�������ĸ�checkOut��BorrowableItem::checkOut ,ElectronicGadget::checkOut
        // should do that ....
        mp3.BorrowableItem::checkOut() ; // okokok ... public ...
        //mp3.ElectronicGadget::checkOut() ; // error ... private ...
//error: `void testItem40::ElectronicGadget::checkOut() const' is private|
        cout << " " << "\n" ;
        cout << " sizeof(Base): " << sizeof(Base) << "\n" ;
        cout << " sizeof(Derived1): " << sizeof(Derived1) << "\n" ;
        cout << " sizeof(Derived1_): " << sizeof(Derived1_) << "\n" ;
        cout << " sizeof(Derived3): " << sizeof(Derived3) << "\n" ;
        cout << " sizeof(Derived3_): " << sizeof(Derived3_) << "\n" ;
        cout << " sizeof(Derived2): " << sizeof(Derived2) << "\n" ;
        cout << " sizeof(Derived2_): " << sizeof(Derived2_) << "\n" ;
        cout << " sizeof(Derived3): " << sizeof(Derived3) << "\n" ;
        cout << " sizeof(Derived3_): " << sizeof(Derived3_) << "\n" ;
    }


// 3    ���ؼ̳е�ȷ����������;������һ������漰��public�̳�ĳ��Interface class���͡�private�̳�
//      ĳ��Э��ʵ�� class �����������
    using testItem18::Date ;
    class IPerson
    {
    public:
        virtual ~IPerson() {} ;
        virtual string name() const = 0;
        virtual Date birthDate() const = 0 ;
        // ...
    } ;
    class DatabaseID {} ;// ...
    class PersonInfo
    {
    private:
        DatabaseID dID_ ;
        Date    birthDate_ ;
        string  name_ ;
    public:
        explicit PersonInfo(const DatabaseID& pid)
        : dID_(pid) ,birthDate_(1 ,1 ,2010)  {} //...
        virtual ~PersonInfo() {}
        virtual const char* theName() const ;
        virtual const Date theBirthDate() const ;
    private: // ...
        virtual const char* valueDelimOpen() const ;
        virtual const char* valueDelimClose() const ;
        // ...
    } ;
    const char* PersonInfo::theName() const
    {
        #define MAX_LEN_NAME 100
        //����������������ֵʹ�ã����ڻ�������static����˻ᱻ�Զ���ʼ��Ϊ��ȫ��Ϊ0��
        static char value[MAX_LEN_NAME] ;
        //value[0] = '\0' ;
        std::strcpy(value ,valueDelimOpen() ) ;
        std::strcat(value ,name_.c_str() ) ;
        std::strcat(value ,valueDelimClose()) ;
        return value ;
    }
    const Date  PersonInfo::theBirthDate() const
    { return birthDate_ ;  }
    const char*  PersonInfo::valueDelimOpen() const
    { return "[" ;  }
    const char*  PersonInfo::valueDelimClose() const
    { return "]" ;  }
    // ...
    class CPerson : public IPerson ,private PersonInfo
    {
    private:
        explicit CPerson(const DatabaseID& pid)
        : PersonInfo(pid) {} //...
        ~CPerson() {}// ...
        virtual const char* theName() const
        { return PersonInfo::theName() ; }
        virtual const Date theBirthDate() const
        { return PersonInfo::theBirthDate() ;}
    private: // ...
        const char* valueDelimOpen() const { return "" ; }//virtual
        const char* valueDelimClose() const { return "" ; }//virtual
    } ;

}//namespace testItem40


// ====================================================================
//# pragma warning(pop)

#endif // UNIT3_H_INCLUDED
