#include "list.h"
#include <QDebug>
#include <iostream>
int main(int argc, char *argv[])
{

    using  std::cout;
    using std::endl;
    List<int>list;
    for(int i=0;i<10;i++)
    {
        list.push_back(i+1);
    }
    for(auto i=list.begin();i!=list.end();++i){cout<<*i;}
    cout<<endl;
    for(auto i: list){cout<<i<<" ";}cout<<endl;
    qDebug()<<"ID:"<<argc<<"info:"<<*argv<<"\nfinish";
}
