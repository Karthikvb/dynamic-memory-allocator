#include <stdio.h>

class Base1
{
  public:

  virtual int virt1() { return 100; }

  int data1;
};

class Derived : public Base1
{
  public:

  virtual int virt1() { return 150; }

  int derivedData;
};

int Global1( Base1 * b1 )
{
  return b1->virt1();
}

/*
int main()
{
  Derived * d = new Derived;

  printf( "%d %d\n", d->virt1(), Global1( d ));
}*/


class Base2
{
  public:

  virtual int virt2() { return 200; }

  int data2;
};

class MultipleDerived : public Base1, public Base2
{
  public:

  virtual int virt1() { return 150; }
  virtual int virt2() { return this->data1; }

  int derivedData;
};

int Global2( Base2 * b2 )
{
  return b2->virt2();
}

int main()
{
  MultipleDerived * md = new MultipleDerived;
md->data1=333;
  printf( "%d %d %d %d\n",
    md->virt1(), Global1( md ), md->virt2(), Global2( md ));
}

