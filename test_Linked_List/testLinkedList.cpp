#include "LinkedList.h"
#include <iostream>

using namespace std;

void main()
{
    LinkedList l;
    l.insert(1,0);
    l.insert(2,0);
    l.insert(3,1);
    l.insert(2,0);
	l.insert(5,0);
	l.display();
    
    l.erase(2);
    l.display();
	cout<<"l.find(1) "<<l.find(1)<<endl;
	cout<<"l.find(8) "<<l.find(8)<<endl;
	system("pause");
}
