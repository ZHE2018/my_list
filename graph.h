#ifndef GRAPH_H
#define GRAPH_H
#include "list.h"
#include <map>
#include <QDebug>
//十字链表法
//弧：头节点，尾节点，同头的下一个弧，同尾的下一个弧，附加信息
//节点：节点数据，入的第一个弧，出的第一个弧
template <typename INFO,typename DATA>
class Graph
{
private:
    struct Node;
    struct Arc{
        Node * head;
        Node * tail;
        Arc * headNextArc;
        Arc * tailNextArc;
        INFO info;
        Arc(Node * h,Node * t,const INFO & info=INFO(),Arc * hlink=nullptr,Arc * tlink=nullptr):
        head(h),tail(t),headNextArc(hlink),tailNextArc(tlink),info(info){}
    };
    struct Node{
        DATA data;//用于查找节点的Key,该项不能相同
        Arc * inArc;
        Arc * outArc;
        void addInArc(Arc* arc){
            Arc * ptr=inArc;
            while(ptr!=nullptr)ptr=ptr->tailNextArc;
            ptr=arc;
        }

        Node(const DATA & data,Arc * inArc=nullptr,Arc * outArc=nullptr):data(data),inArc(inArc),outArc(outArc){}
        ~Node(){
            Arc * ptr=inArc;
            while(ptr!=nullptr){
                ptr=inArc->tailNextArc;
                delete inArc;
                inArc=ptr;
            }//析构入度的弧
        }
    };
    //使用map管理所有定点，
    std::map<DATA,Node*> map;
public:
    Graph(){}
    ~Graph(){
        for(auto & i:map){
            delete i.second;
        }
    }
    bool insertNode(const DATA & data){
        if(map.find(data)!=map.end())
            return false;
        Node* n=new Node(data);
        map.insert(std::pair<DATA,Node*>(data,n));
        return true;
    }

    bool insertArc(const DATA & head,const DATA & tail,const INFO &info=INFO()){
        if(map.find(head)==map.end()||map.find(tail)==map.end())//弧头或尾不存在
            return false;
        //查找节点
        typename std::map<DATA,Node*>::iterator ptr=map.find(head);
        Node *h=ptr->second;
        ptr=map.find(tail);
        Node *t=ptr->second;
        //创建弧

        Arc * arc=new Arc(h,t,info);
        qDebug()<<info<<":"<<arc;
        //弧加入到头节点链表中
        Arc *temp=h->outArc;
        h->outArc=arc;
        h->outArc->headNextArc=temp;
        //弧加入到尾节点链表中
//        t->addInArc(arc);
        Arc * temp2=t->inArc;//弧为头节点入弧
        t->inArc=arc;
        t->inArc->tailNextArc=temp2;
        return true;
    }
};

#endif // GRAPH_H
