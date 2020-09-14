#include <iostream>

using namespace std;

class Parent{
    private:
        string name;
        int age;
    
    public:
        Parent(string aName, int aAge){
            name = aName;
            age = aAge;
            
            cout << "Parent Constructor" << endl;
        }

        int getAge(){
            return age;
        }
        void setAge(int aAge){
            age = aAge;
        }
        string getName(){
            return name;
        }
        void setName(string aName){
            name = aName;
        }
};

class Child: public Parent{
    private:
        bool married;

    public:
        Child(string pName, int pAge, bool aMarried): Parent(pName, pAge){
            married = aMarried;
            
            cout << "Child Constructor" << endl;
        }

        bool getMarried(){
            return married;
        }
        void setMarried(bool aMarried){
            married = aMarried;
        }
    
};


int main(){
    Child child1("John", 24, true);

    cout << "Get Parent Data: " << child1.getName() << endl;

    child1.setName("Jeff");

    cout << "Get changed Parent Data: " << child1.getName() << endl;

    cout << "Get Child Data: " << child1.getMarried() << endl;
    
    child1.setMarried(false);

    cout << "Get changed Child Data: " << child1.getMarried() << endl;
    return 0;
}