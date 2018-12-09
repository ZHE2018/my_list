#ifndef GRAPH_L_H
#define GRAPH_L_H

#include <QVector>
#include <QLinkedList>
#include <QMap>

//无向图，顶点可以指定KEY，key必须唯一
template<typename KEY>
class Graph_l
{
private:
    struct Arc{
        unsigned int arcNumber;
        int vaule;
        Arc(unsigned int arc,int vaule=1):arcNumber(arc),vaule(vaule){}
        bool operator==(const Arc & b)const{
            return b.arcNumber==arcNumber;
        }
        bool operator==(const unsigned int & b)const{return b==arcNumber;}
        operator unsigned int(){
            return arcNumber;
        }
    };
public:
    Graph_l():nodeSize(0){}
    void insertVertex(const KEY & k){

        if(key.find(k)!=key.end())//重复顶点
            return;
        key.insert(k,nodeSize);
        nodeSize++;
        graph.append(QLinkedList<Arc>());
        this->vaule.append(k);
    }
    void removeVertex(const KEY & k){
        if(key.find(k)==key.end())//节点不存在
            return;
        unsigned int a=*key.find(k);
        for(auto &i:graph)
        {
            i.removeOne(a);
        }//遍历所有边，删除相关边
        typename QMap<KEY,unsigned int>::iterator i;
        for(i=key.begin();i!=key.end();++i){
            if(i.value()>a){
                i.value()--;
            }
        }//更新map数值
        graph.remove(a);
        key.remove(k);
        vaule.removeOne(k);
        //删除节点
    }
    void insertEdge(const KEY & start,const KEY & end,int vual=1){
        if(start==end)//无效边
            return;
        //顶点不存在则添加顶点
        if(key.find(start)==key.end())
            insertVertex(start);
        if(key.find(end)==key.end())
            insertVertex(end);
//        if(key.find(start)==key.end()||key.find(end)==key.end())//不存在的顶点的边
//            return;
        if(edge(start,end))//已经存在相同边
            return;
        graph[*key.find(start)].append(Arc(*key.find(end),vual));
        graph[*key.find(end)].append(Arc(*key.find(start),vual));
    }
    //生成一个邻接顶点的列表，顶点不存在则返回空表
    QVector<KEY> neighbor(const KEY &k)const{
        QVector<KEY> neig;
        if(key.find(k)==key.end())
            return neig;
        unsigned int a = *key.find(k);

        for(auto i :graph[a]){
        neig.append(this->vaule.at(i));
        }
        return neig;
    }
    //迭代器避免了数据的复制，迭代器指向的是下标，而不是KEY,注意保证k的存在，否则将添加一个顶点;使用toKey()将下标翻译成KEY
    typename QLinkedList<Arc>::const_iterator neighborBegin(const KEY & k)const{
        if(key.find(k)==key.end()){
            this->insertVertex(k);
        }
        return graph[*key.find(k)].begin();
    }

    typename QLinkedList<Arc>::const_iterator neighborEnd(const KEY & k)const{
        if(key.find(k)==key.end()){
            this->insertVertex(k);
        }
        return graph[*key.find(k)].end();

    }
    KEY toKey(unsigned int & i)const{
        return vaule.at(i);
    }
    void removeEdge(const KEY & start,const KEY & end){
        if(!edge(start,end))
            return;
        graph[*key.find(start)].removeOne(*key.find(end));
        graph[*key.find(end)].removeOne(*key.find(start));
    }
    bool edge(const KEY & start,const KEY & end)const{
        if(start==end)
            return false;
        if(key.find(start)==key.end()||key.find(end)==key.end())
            return false;
        unsigned int a=* key.find(start);
        unsigned int b=* key.find(end);
        bool has=false;
        for(auto i:graph[a]){
            if(i==b){
                has=true;
                break;//return true;
            }
        }
        return has;//return false;
    }
    int edgeVaule(const KEY & start,const KEY & end)const{
        if(start==end)
            return 0;
        if(key.find(start)==key.end()||key.find(end)==key.end())
            return 0;
        unsigned int a=* key.find(start);
        unsigned int b=* key.find(end);
        for(auto i:graph[a]){
            if(i==b){
                return i.vaule;
                break;//return true;
            }
        }
        return 0;
    }

private:
    QVector<QLinkedList<Arc> > graph;//邻接链表
    unsigned int nodeSize;//顶点数量
    QMap<KEY,unsigned int> key;//由KEY查找对应顶点所在数组位置
    QVector<KEY> vaule;//不同顶点的KEY值

};

#endif // GRAPH_L_H
