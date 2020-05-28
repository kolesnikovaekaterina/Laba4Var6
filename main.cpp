#include <iostream>
#include "LIST.h"

using namespace std;

int main()
{
List<int> k;
k.print();
cout<<endl;
k.insert(13456);
k.insert(122);
k.insert(11);
k.print();
cout<<endl<<k.size()<<endl;
//first.deleteCur();
k.delet(11);
k.print();
cout<<endl;
k.insert(12);
k.print();
cout<<endl<<k.size()<<endl;
k.insertAtPos(3,3);
k.insertAtPos(3,2);
k.delet(3);
k.print();
cout<<endl;
cout<<endl<<k.size()<<endl;
return 0;
}
