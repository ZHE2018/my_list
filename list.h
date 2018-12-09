#ifndef LIST_H
#define LIST_H

template<typename T>
class List
{

private:
    struct node{
        T _data;
        node * _next;
        node(const T & data=T()):_data(data),_next(nullptr){}
        node * next(){return _next;}
        T &data(){return _data;}
    };
    node * n;
    unsigned int _size;
    node * _end;
    struct iterator{
        node * p;
        iterator(node * ptr=nullptr):p(ptr){}
        iterator operator++(){
            p=p->next();
            return iterator(this->p);
        }
        iterator operator++(int){
            node * ptr=this->p;
            p=p->next();
            return ptr;
        }
        T & operator*()const{
            return p->data();
        }
        T * operator->()const{
            return &(p->data());
        }
        bool operator==(const iterator &b)const{return b.p==this->p;}
        bool operator!=(const iterator &b)const{return b.p!=this->p;}
    };
    //iterator 必须是合理的，由构造函数构造的iterator的行为将是未定义的！
public:
    List(const T &data):n(new node(data)),_size(1),_end(nullptr){}
    List():n(nullptr),_size(0),_end(nullptr){}
    ~List(){
        node *ptr=n;
        while(ptr!=nullptr)
        {
            n=ptr->_next;
            delete ptr;
            ptr=n;
        }
    }
    iterator begin(){return iterator(n);}
    iterator end(){return iterator(_end->next());}
    bool empty()const{return this->_size==0;}
    void push_back(const T & data)
    {
        if(_end==nullptr)
        {
            _end= new node(data);
            n=_end;
        }
        else{
            _end->_next=new node(data);
            _end=_end->_next;
        }
        this->_size++;
    }
    void push_front(const T & data)
    {
        node * ptr=n->_next;
        n=new node(data);
        n->_next=ptr;
        this->_size++;
    }
    void push_frout(const T * dataPtr){
        node * ptr=n->_next;
        n=dataPtr;
        n->_next=ptr;
        this->_size++;
    }
    void pop_front(){
        if(n==nullptr)
            return;
        if(n==_end)
        {
            delete n;
            n=_end=nullptr;
            this->_size--;
            return;
        }
        node * ptr=n->_next;
        delete n;
        n=ptr;
        this->_size--;
    }

    void pop_back()
    {
        if(_end==nullptr)
            return ;
        if(n==_end)
        {
            delete _end;
            n=_end=nullptr;
            return ;
        }
        node * ptr=n;
        while(ptr->_next!=_end)
        {
            ptr=ptr->_next;
        }
        delete _end;
        _end=ptr;
        ptr->_next=nullptr;
        this->_size--;
    }
    unsigned int size()const{return this->_size;}

};


#endif // LIST_H
