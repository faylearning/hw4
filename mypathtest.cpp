#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;

Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;
Node* g;

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
  setNode(a,5,b,c);
  setNode(b,1,d,e);
  setNode(c,8,f,NULL);
  setNode(d,0,NULL,NULL);
  setNode(e,4,NULL,NULL);
  setNode(f,7,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
  setNode(a,5,b,c);
  setNode(b,1,d, NULL);
  setNode(c,8,f,NULL);
  setNode(d,0,NULL,NULL);
  setNode(f,7,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
  setNode(a,5,b,c);
  setNode(b,1,d,e);
  setNode(c,8,NULL,NULL);
  setNode(d,0,NULL,NULL);
  setNode(e,4,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
  setNode(a,5,b,c);
  setNode(b,1,d,e);
  setNode(c,8,f,NULL);
  setNode(d,0,NULL,NULL);
  setNode(e,4,g,NULL);
  setNode(f,7,NULL,NULL);
  setNode(g,2,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}



int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4); 
  e = new Node(5);
  f = new Node(5);
  g = new Node(6);

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
//   test5("Test5");
 
  delete a;
  delete b;
  delete c;
  delete d;
  delete e;
  delete f;
  delete g;
}