/*
 *The purpose of this function is to test structs and
 *see how they work.  This is a working program that
 *displays arrays being used inside of structs.
 *by Adam Thiemann
 */

 #include <iostream>
 #include <string>
 using namespace std;

struct TestingStruct
{
    string name[2];
    int age[2];
};

int main()
{
    TestingStruct name;
    TestingStruct age;

    int count = 0;
    while (count < 2)
    {
        cout << "What is the age of person " << count + 1 << "?";
        cin >> age.age[count];
        cout << endl << "What is the name of person " << count + 1 << "?";
        cin >> name.name[count];
        cout << endl;
        count++;
    }
    //age.age = {17, 23};
    //name.name = {"Joe", "Kaitlyn"};
    for (int index = 0; index < 2; index++)
    {
        cout << "His/her name is " << name.name[index] << 
            " and his/her age is " << age.age[index] << endl;
    }
    

    return 0;
}