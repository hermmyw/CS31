class A { public:
A()
{ cout << "DC" << endl; } A(const A& other)
{ cout << "CC" << endl; }
A& operator=(const A& other)
{ cout << ~A()
{ cout <<
int main() {
A arr[3];
"AO" << endl; return *this; } "Destructor!" << endl;}
};
arr[0] = arr[1];
A x = arr[0];
x = arr[1];
A y(arr[2]);
cout << "DONE" << endl;
}