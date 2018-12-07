#include "list.h"
#include <QDebug>
#include <iostream>
#include "graph.h"
#include "graph_l.h"
int main(int argc, char *argv[])
{

    using  std::cout;
    using std::endl;

//    Graph<int,int> g;
//    g.insertNode(1);
//    g.insertNode(2);
//    g.insertNode(3);

//    g.insertArc(1,2,7);
//    g.insertArc(1,3,8);
//    g.insertArc(2,3,9);
    Graph_l<int> g;
    g.insertVertex(1);
//    g.insertVertex(3);
//    g.insertVertex(5);
//    g.insertVertex(7);

    g.insertEdge(1,3);
    g.insertEdge(1,7);
    g.insertEdge(1,5,2);
    g.insertEdge(5,7);

    for(auto i:g.neighbor(1)){cout<<i<<" ";}
    cout<<endl;
    cout<<g.edgeValue(1,5)<<endl;

    qDebug()<<"ID:"<<argc<<"info:"<<*argv<<"\nfinish";
}
