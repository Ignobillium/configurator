#include <iostream>
using namespace std;

class a
{
protected:
  int A;
public:
  void show() { cout << A << endl; }
  a() { A = 9; }
  ~a() {}
};

class b: public a
{
protected:
  int B;
public:
  void showA() { cout << A+10 << endl; }
  void showB() { cout << B << endl;    }
  b() { B = 11; }
  ~b() {}
};

int main()
{
  a A;
  b B;

  B.show();
  B.showA();
  B.showB();
  return 0;
}
