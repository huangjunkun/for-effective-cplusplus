#ifndef UNIT3_H_INCLUDED
#define UNIT3_H_INCLUDED


//# pragma warning(push)
//# pragma warning(disable:8057) //
// ===  五、实现 ======================================================
// ====================================================================
// --- 条款26：尽可能延后变量定义式的出现时间 ...
// 注意：
// 1    尽可能延后变量定义式的出现时间，这样做可以增加程序的清晰度并改善程序的效率
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
        // 1    1个构造函数+1个析构函数+n个赋值操作（成本）
        // ...
        Widget w ;
        for(int i=0 ;i<10 ;i++) // n = 10
        {
            w = Widget(i) ;
            // ....
        }
        // ...
        // 2    n个构造函数+n个析构函数 ... （成本）
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
// --- 条款27：尽量少做转型动作 ...
// 注意：static_cast ,dynamic_cast ,const_cast ,reinterpret_cast ... XXX_cast<Type> (Expr)...
// 1    如果可以尽量少做转型（避免），特别是注重效率的代码中，避免dynamic_cast S。
//      如果有个设计需要转型动作，试着发展无需转型的替代设计 ....
// 2    如果转型的必须的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，
//      而不需将转型放进他们的自己代码内。
// 3    宁可使用 C++ Style（新式）转型，不要实验旧式转型。前者很容易辨别出来，
//      而且也比较有着分门别类的职掌 。
namespace testItem27
{
    // 避免使用 dynamic_cast ，两个一般性做法 for void blink()如下： 11111 ，22222
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
            //static_cast<Window>(*this).OnResize() ;// error ,临时对象...!!!
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
        for(VPW::iterator iter = winPtrs.begin() ;//不希望使用dynamic_cast ...
            iter != winPtrs.end() ;iter++)
            if( SpecialWindow* psw = dynamic_cast<SpecialWindow*>(iter->get()) )
                psw->blink() ;
        }
        {
        //  2))))
        VSPW   winPtrs ; //法一：11111
        // ...
        for(VSPW::iterator iter = winPtrs.begin() ;//这样比较好，不使用dynamic_cast ...
            iter != winPtrs.end() ;iter++)
                (*iter)->blink() ;
        }
        {
        //  3))))
        VPW    winPtrs ; // 法二：22222
        // ...
        for(VPW::iterator iter = winPtrs.begin() ;//这样比较好，不使用dynamic_cast ...
            iter != winPtrs.end() ;iter++)
                (*iter)->blink() ;
        }
    }
    //1)

}//namespace testItem27
// ====================================================================
// --- 条款28：避免返回handles 指向对象的内部成分 ...
// 注意：
// 1    避免返回 handles（包括references、指针、迭代器）指向对象内部。遵守这个条款
//      可以增加程序的封装性，帮助const 成员函数的行为像个const，并将发生“需吊号码牌”
//      (dangling handles) 的可能性降低至最低 ...
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
        const Point& upperLeft() const// return non-const,warn !!!,but ,Point& 可能出错--需吊号码牌
        { return pData->ulhc ; } //
        const Point& lowerRight() const//return non-const,warn !!!,but ,Point& 可能出错--需吊号码牌
        { return pData->lrhc ; } //
        // or : ... if okokok...
        /*
        Point& upperLeft() //
        { return pData->ulhc ; } //
        Point& lowerRight() //
        { return pData->lrhc ; } //
        */
    } ;
    // ... for example :Point& 可能出错--需吊号码牌
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
        //.pUpperLeft ,dangerous pUpperLeft from 临时对象 reference ( from boundingBox function ...)
        pUpperLeft->print() ;
        //  ...
    }
}//namespace testItem28
// ====================================================================
// --- 条款29：为“异常安全”而努力时值得的
// 注意：
// 1    异常安全函数( Exception-safe functions)即使发生异常也不会泄露资源或允许任何函数
//      结构败坏。这样的函数区分为三种可能的保证：基本(承诺)型、强烈型、不抛异常型。
// 2    “强烈保险”往往能够以copy-and-swap实现出来，但“强烈保证”并非对所有函数都可以实现
//      或是具备现实意义 ...
// 3    函数提供的“异常安全保证”通常最高只等于其所调用函数中的“异常安全保证”中的最弱者 。
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
        std::tr1::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl)) ; //获得副本 ...
        pNew->pImage.reset(new Image(imgSrc)) ;// 修改副本 ...
        ++pNew->imageChanges ;
        using std::swap ;
        //swap(pImpl ,pNew) ;// ...置换数据...
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
// --- 条款30：透彻了解 inlining (inline) 的里里外外 ...
// 注意：inline 是个申请，编译器可以加以忽略(若 inline 函数过于复杂) ...
// 1    将大多数inlining限制在小型，被频繁调用的函数身上。这可使日后的调试过程
//      和二进制升级(binary upgradability)更容易，也可使潜在的代码膨胀问题最小化，
//      使程序的速度提升机会最大化 ...
// 2    不要只因为 function templateS 出现在头文件，就将它们声明 inline 。
// 3    编译器通常不对“通过函数指针而进行的调用”实施inlining ...有时包括构造函数
//      与析构函数 ... 有时候编译器会自动生成两者的outline 副本 ...往往(实际上)
//      构造和析构函数的inlining的糟糕候选，记住：编译器会自动为构造，析构扩充代码
namespace testItem30
{
    class Person
    {
    private:
        int     theAge ;
        //...
    public:
        int age() const { return theAge ; }
        // 一个隐喻的inline申请：age() 定义于class定义式内
        // ...
    } ;
    template <typename T>
    inline const T& Max(const T& a ,const T& b)//明确申请inline ...
    { return a < b ? b : a ; } //

    inline void inlineFunc()
    { cout << " inline void inlineFunc() ...\n" ; } // ...
    void exampleFunc()
    {
        void (*pFunc)() ;
        pFunc = inlineFunc ;
        inlineFunc() ; //这个调用将被inlined ，因为它是一个正常调用 ...
        pFunc() ;//这个调用或许(通常)不被inlined，因为它通过函数指针调用 ...
    }

}//namespace testItem30
// ====================================================================
// --- 条款31：将文件间的编译依存关系降至最低 ...
// 注意：
// 1    支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依于定义式。
//      基于此构想的两个手段是： Handle classes 和 Interface clases ...
// 2    程序库头文件应该以“完全且仅有声明式”( full and delaration-only forms)
//      的形式存在。这种做法不论是否涉及 templateS 都适用 ...
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


// ===  六、继承与面向对象设计 ========================================
// ====================================================================
// --- 条款32:确定你的public 继承塑模出is-a 关系
// 注意：
// 1    “public继承”意味着 is-。适用于base classes身上的每一件事一定也用于 derived classes
//      身上，因为每一个 derived class对象也都是一个base class 对象 ...
// 2    is-a并非是唯一存在于classes之间的关系，另外两种常见的关系是has-a和is-implementd-in-terms-of
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
    class Penguin : public Bird// 企鹅 ... no fly
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
        assert(r.getHeight()==oldHeight) ;//判断r的高度是否未曾改变 ...
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
        assert(s.getWidth()==s.getHeight()) ;//对于所有正方形必须为真
        makeBigger(s) ;// 增加面积 ...
        assert(s.getWidth()==s.getHeight()) ;//对于所有正方形必须为真
        // ...
    }


}//namespace testItem32
// ====================================================================
// --- 条款33：避免遮掩继承而来的名称
// 注意：
// 1    derived classes 内的名称会遮掩base classes 内的名称。在public继承下从来没有人希望如此
// 2    为了让被遮掩的名称再见天日，可以使用using声明式或转交函数（forwarding function）
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
        using Base::mf1 ; // 让 Base class 内名为 mf1和mf3的所有东西在
        using Base::mf3 ;//Derived 作用域内都可见 ，okokok
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
        virtual void mf1()// 转交函数暗自成为inline
        { Base::mf1() ; cout << " virtual void  Derived_2::mf1()\n\n" ;}
        // Warning W8022 : 'Derived_2::mf1()' hides virtual function 'Base::mf1(int)'|
    } ;
}//namespace testItem33
// --- 条款34：区分借口继承和实现继承
// 注意：
// 1    接口继承和实现继承不同。在public继承之下，derived classes 总是继承base class 的接口
// 2    pure virtual 函数只具体指定接口继承（但可以调用其实现--转交函数实现）
// 3    简朴的（非纯）impure virtual 还是那户具体指定借口继承及缺省实现继承
// 4    non-virtual 函数具体指定接口继承以及强制性实现继承
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
// --- 条款35：考虑virtual 函数之外的其他选择 ...
// 注意：
// 1    virtual函数的替代方案包括NVI(Non-Virtual Interface)手法及Strategy设计模式的多种形式。
//      NVI手法自身是一种特殊形式的 Template Method模式(与C++ templateS 并无关联)
// 2    将机能从成员函数移到class 外部函数，带来的一个缺点就是：非成员函数无法访问non-public成员
// 3    tr1::function对象的行为就像一般函数指针。这样的对象可接纳”与给定之目标签名式兼容“的
//      所有可调用物( callable entities ) ...
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
    // 1)   藉由Non-Virtual Interface 手法实现 Template Method 模式 ...
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
    // 2)   藉由Function Pointers 实现 Strategy 模式 ...
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
    //1     同一人物类型之不同实体可以有不同的健康计算函数  ...
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
    //2     并且谋已知人物的健康指数计算函数可以在运行期变更 ...
    // ....
    /**/
    // 3)   藉由 tr1::function 完成Stratagy 模式 ...


    class GameCharacter_3 ;
    int defaultHealthCalc(const GameCharacter_3& gc) { return int(1) ;} // ...
    class GameCharacter_3
    {
    public:
        typedef boost::function<int (const GameCharacter_3&) > HealthCalcFunc ;
        // HealthCalcFunc 可以是任何”可调用物“，课呗调用并接受
        // 任何兼容于 GameCharacter_3 之物，返回任何兼容于int 的东西 ....
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

    // 4)   藉由古典的 Stratagy 模式 ...
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
// --- 条款36：绝不重新定义继承而来的non-virtual函数 ...
// 注意：
// 1    绝对不要重新定义继承而来的non-virtual函数
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
        void nonvirFunc() const ;//遮掩(hides) 了Base::nonvirFunc ..见条款33
        // ...
    } ;
    void Derived::nonvirFunc() const
    { cout << " void Derived::nonvirFunc() const\n" ; }
    void exampleFunc()
    {
        Derived d ;
        Derived* pD = &d;
        Base*    pB = &d ;
        pB->nonvirFunc() ;// 调用Base::nonvirFunc
        pD->nonvirFunc() ;// 调用Derived::nonvirFunc
    }
}//namespace testItem36
// ====================================================================
// --- 条款37：绝不重新定义继承而来的缺省参数值 ...
// 注意：
// 1    绝对不要重新定义继承而来的缺省参数值，因为缺省参数值都是静态绑定(编译期)，
//      而 virtual 函数--你唯一应该覆盖的东西--却是动态绑定 ...
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
    //  注意：赋予不同的缺省参数值，这是很糟糕 ...
        void draw(ShapeColor color = Green) const //Warn--重新定义继承而来的缺省参数值,but ...
        { cout << " virtual void Rectangle::draw(ShapeColor color)const ,color: "<< color << "\n" ; }
        // ...
    } ;
    class Circle : public Shape
    {
    public:
        void draw(ShapeColor color) const //OK--继承缺省参数值 ...
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
    //  替代设计方法： NVI(non-virtual interface ) ...virtual to non-virtual ...
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
    // 由于non-virtual函数应该绝对不被derived classes 覆写(见条款36)，
    // 这个设计很清楚地使得draw函数的 color 缺省参数值总是 Red 。
    // ...

}//namespace testItem37
// ====================================================================
// --- 条款38：通过复合塑模出has-a或is-implemented-in-terms-of (“根据某物实现出”)
// 注意：
// 1    复合(composition)的意义和public继承完全不同 ...
// 2    在应用域(application domain) ，复合意味 has-a。在实现域(implementation domain),复合意味
//      is-implementd-in-terms-of (根据某物实现出) . ...
// 3
namespace testItem38
{
    // 1    has-a (是一种 )关系 ....
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
    // 2    is-implementd-in-terms-of (根据某物实现出)
    /*
    template<typename T>
    class Set : public std::list<T>//将list 应用于Set，错误用法 ...
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
    //这些函数如此简单，因此都适合inlining候选人 ...
}//namespace testItem38
// ====================================================================
// --- 条款39：明智而审慎地使用 private 继承 ...
// 注意：
// 1    private继承意味 is-implementd-in-terms-of(根据某物实现出)。它通常比复合成员(composition)
//      的级别低。但是当derived classes 需要访问 protected base class的成员，或需要重新定义继承
//      而来的 virtual 函数时，这么设计是合理的
// 2    和复合(composition)不同，private继承可以造成empty base class最优化。这对致力于“对象尺寸
//      最小化”的程序库开发者而言，可能很重要 ...
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
    class Widget_1 : private Timer //注意，no public ...
    {
    private:
        void OnTick() const ;//查看Widget的数据 ...等等
    public:
        // ...
    } ;
    void Widget_1::OnTick() const // ...
    { cout << " void Widget_1::OnTick() const ...\n" ; }
    // 2) ************better*************可以很好的替代private 继承 ...
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
    // 激进情况 --------------------------------
    class Empty{} ;// ...
    class HoldsAnInt_1
    {//编译器不能HoldsAnInt_1对象大小 ...
    private:
        Empty e ;
        int   x ;
    } ;
    class HoldsAnInt_2 : private Empty
    {//编译器优化HoldsAnInt_2对象大小 ...
    private:
        int x ;
    } ;

    void exampleFunc()
    {
        Person  p ;
        Student s ;
        testItem38::Student s_ ;
        eat(p) ;// 没有问题，p是Person  ...
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
// --- 条款40：明智而审慎地使用多重继承 ...
// 注意：
// 1    多重继承比起单一继承复杂。它可能导致新的歧义，以及对virtual继承的需要。
// 2    virtual继承会增加类型大小、速度、初始化(及赋值)复杂度等等成本。如果virtual base classes
//      不带任何数据，将是最具使用价值的情况 ...
// 3    多重继承的确有正当的用途。其中一个情节涉及“public继承某个Interface class”和“private继承
//      某个协助实现 class ”的两项组合 ....
namespace testItem40
{
    // 可能导致的歧义 ....
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
    //  warning ...歧义 ...runtime error in GUN GCC ...
        int getValue() const { return getValue() ; }// Warn ...
        void setValue(int newValue) { setValue(newValue) ; }// Warn ...
        // should 分开设计接口 或是 virtual 继承 ...
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
            // setValue(newValue) ;  //1 歧义 ...runtime error in GUN GCC ...
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
//歧义 ...，调用哪个checkOut：BorrowableItem::checkOut ,ElectronicGadget::checkOut
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


// 3    多重继承的确有正当的用途。其中一个情节涉及“public继承某个Interface class”和“private继承
//      某个协助实现 class ”的两项组合
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
        //保留缓冲区给返回值使用；由于缓冲区是static，因此会被自动初始化为“全部为0”
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
