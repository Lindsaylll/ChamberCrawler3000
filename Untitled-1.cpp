
#include <iostream>
#include <memory.h>
using namespace std;

class A {
    int i;
public:
    A(){
        i = 3;
    }
    A(int i){
        i = i;
    }
    int getA(){
        return i;
    }
    virtual int getB() = 0;
};



class B: public A{
    int ii;
public:
    B(){
        ii = 5;
    }
    int getB() override{
        return ii;
    }

};



class Total{
    // shared_ptr<A> a;
    A * a;
public:
    Total(){
        // auto b = make_shared<B>();
        B * b = new B();
        a = b;
    }
    int getA(){
        return a->getB();
    }
};



int main(){
    Total total = Total();
    cout << total.getA() << endl;  // will print 5
    return 0;
}


// A::A(){
//     i = 3;
// }
// A::A(int i){
//     i = i;
// }

// int A::getA(){
//     return i;
// }


// B::B(){
//     ii = 5;
// }
// int B::getB()   {
//     return ii;
// }


// Total::Total(){
//     B b = B();
//     a = b;
// }
// int Total::getA(){
//     return a.getB();
// }