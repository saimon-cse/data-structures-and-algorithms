#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
#define NULL_VALUE -999999
#define infinity 999999
#define white 1
#define gray 2
#define black 3

using namespace std;

class Queue
{
    int *Q;
    int inisize;
    int maxsize;
    int len;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int dequeue();
    bool empty();
};

Queue::Queue()
{
    inisize = 2 ;
    maxsize = inisize;
    Q = new int[maxsize];
    len = 0;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (len == maxsize)
    {
        int *temp;
        maxsize = 2*maxsize;
        temp = new int[maxsize];
        int i, j;
        j = 0;
        for(i=rear; i<len; i++)
        {
            temp[j] = Q[i];
            j++;
        }
        for(i=0; i<rear; i++)
        {
            temp[j] = Q[i];
            j++;
        }
        rear = 0;
        front = len;
        delete[] Q;
        Q = temp;
    }

    Q[front] = item;
    front = (front+1) % maxsize;
    len++;
}


bool Queue::empty()
{
    if(len == 0)
        return true;
    else
        return false;
}


int Queue::dequeue()
{
    if(len == 0)
        return NULL_VALUE;
    int item = Q[rear] ;
    rear = (rear+1) % maxsize;
    len--;
    return item;
}


Queue::~Queue()
{
    if(Q)
        delete[] Q;
    Q = 0;
}


class Stack
{
    int *s;
    int len, inisize, maxsize;
public:
    Stack();
    ~Stack();
    void push(int item);
    void pop();
    int top();
    bool empty();
};

Stack::Stack()
{
    len = 0;
    s = 0;
    inisize = 2;
    maxsize = inisize;
    s = new int[maxsize];
}

Stack::~Stack()
{
    if(s!=0)
        delete[] s;
    s = 0;
}

void Stack::push(int item)
{
    if(len == maxsize)
    {
        maxsize = 2*maxsize;
        int *temp = new int[maxsize];

        for(int i=0; i<len; i++)
        {
            temp[i] = s[i];
        }

        delete[] s;
        s = temp;
    }

    s[len] = item;
    len++;
}

void Stack::pop()
{
    s[len-1] = NULL_VALUE;
    len--;
}

int Stack::top()
{
    return s[len-1];
}

bool Stack::empty()
{
    if(len==0)
        return true;
    return false;
}


class ArrayList
{
    int *list;
    int len;
    int maxSize;
    int iniSize;
public:
    ArrayList();
    ~ArrayList();
    int searchItem(int item);
    void insertItem(int item);
    void removeItem(int item);
    void removeItemAt(int item);
    int getItem(int position);
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    iniSize = 2;
    maxSize = iniSize;
    list = new int[maxSize];
    len = 0;
}

int ArrayList::searchItem(int item)
{
    for (int i=0; i<len; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::insertItem(int newitem)
{
    int *tempList, i;
    if (len == maxSize)
    {
        maxSize = 2*maxSize;
        tempList = new int[maxSize];
        for(i=0; i<len ; i++)
        {
            tempList[i] = list[i];
        }
        delete[] list;
        list = tempList;
    };

    list[len] = newitem;
    len++;
}

void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item);
    if ( position == NULL_VALUE )
        return;
    removeItemAt(position);
}

void ArrayList::removeItemAt(int position)
{
    if (position < 0 || position >= len)
        return;
    list[position] = list[len-1];
    len--;
}

int ArrayList::getItem(int position)
{
    if(position < 0 || position >= len)
        return NULL_VALUE;
    return list[position];
}

int ArrayList::getLength()
{
    return len;
}

bool ArrayList::empty()
{
    if(len==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<len; i++)
        cout<<list[i]<<" ";

    cout<<endl;
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0;
}


class Graph
{
    ArrayList  *AdjList;
    int nVertices, nEdges;
    bool directed;
    int *col, *p, *dis;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v);
    void printGraph();
    void removeEdge(int u, int v);
    int NumofEdges();
    bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void bfs(int source);
    void dfs(int source);
    int getDist(int u, int v);
    bool isCycleUtil(int v, bool visited[], bool restack[]);
    bool isCycle();
};


Graph::Graph(bool dir)
{
    nVertices = 0;
    nEdges = 0;
    AdjList = 0;
    directed = dir;
    col = 0;
    p = 0;
    dis = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n;
    if(AdjList!=0)
        delete[] AdjList;
    AdjList = new ArrayList[nVertices];
    col = new int[nVertices];
    p = new int[nVertices];
    dis = new int[nVertices];
    this->nEdges = 0;
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    bool x = isEdge(u, v);

    if(x==true)
        return false;

    this->nEdges++;
    AdjList[u].insertItem(v);


    if(!directed)
        AdjList[v].insertItem(u);
}

void Graph::printGraph()
{
    for(int i=0; i<nVertices; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<AdjList[i].getLength(); j++)
        {
            cout<<AdjList[i].getItem(j)<<" ";
        }
        cout<<endl;
    }
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return;
    this->nEdges--;
    AdjList[u].removeItem(v);
    if(!directed)
        AdjList[v].removeItem(u);
}

int Graph::NumofEdges()
{
    return nEdges;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return  false;
    if(!directed)
    {
        int Echeck1, Echeck2;
        Echeck1 = AdjList[u].searchItem(v);
        Echeck2 = AdjList[v].searchItem(u);
        if(Echeck1 == NULL_VALUE && Echeck2 == NULL_VALUE)
            return false;
        else
            return true;
    }
    else
    {
        int isthere;
        isthere = AdjList[u].searchItem(v);
        if(isthere == NULL_VALUE)
            return false;
        else
            return true;
    }
}

int Graph::getOutDegree(int u)
{
    if(u<0 || u>=nVertices)
        return NULL_VALUE;

    return AdjList[u].getLength();
}

int Graph::getInDegree(int u)
{
    if(u<0 || u>=nVertices)
        return NULL_VALUE;

    int i;
    if(directed)
    {
        int deg=0,i;
        for(i=0; i<nVertices; i++)
        {
            if(AdjList[i].searchItem(u)!=NULL_VALUE)
                deg++;
        }
        return deg;
    }
    else
    {
        AdjList[u].getLength();
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    int lenU = AdjList[u].getLength();
    int lenV = AdjList[v].getLength();

    for(int i=0; i<lenU; i++)
    {
        for(int j=0; j<lenV; j++)
        {
            if(AdjList[u].getItem(i) == AdjList[v].getItem(j))
            {
                return true;
            }
        }
    }
    return false;
}

///BFS
void Graph::bfs(int source)
{
    if(source<0 || source >= nVertices)
        return;
    Queue q;

    col = new int[nVertices];
    p = new int[nVertices];
    dis = new int[nVertices];

    int s;
    for(int i=0; i<nVertices; i++)
    {
        if(i != source)
        {
            col[i] = white;
            p[i] = NULL_VALUE;
            dis[i] = infinity;
        }
    }
    col[source] = gray;
    p[source] = NULL_VALUE;
    dis[source] = 0;
    cout<<source<<" ";

    if(!q.empty())
        Queue q;
    q.enqueue(source);

    while(!q.empty())
    {
        s = q.dequeue();
        int len = AdjList[s].getLength();
        int v, i = 0;
        for(i = 0; i < len; i++)
        {
            v = AdjList[s].getItem(i);
            if(col[v] == white)
            {
                col[v] = gray;
                cout<<v<<" ";
                dis[v] = dis[s] + 1;
                p[v] = s;
                q.enqueue(v);
            }
        }
        col[s] = black;
    }
    cout<<endl;
}


///DFS
void Graph::dfs(int source)
{
    if(source<0 || source >= nVertices)
        return;

    col = new int[nVertices];
    p = new int[nVertices];
    dis = new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        col[i] = white;
        p[i] = NULL_VALUE;
    }

    Stack st;

    col[source] = gray;
    st.push(source);
    while(!st.empty())
    {
        int u = st.top();
        int sum=0;

        for(int i=0; i<AdjList[u].getLength(); i++)
        {
            int v = AdjList[u].getItem(i);
            if(col[v]==white)
            {
                p[v] = u;
                col[v] = gray;
                st.push(v);
                break;
            }
            else
                sum++;
        }
        if(sum == AdjList[u].getLength())
        {
            cout<<st.top()<<" ";
            col[u] = black;
            st.pop();
        }

    }
    cout<<endl;
}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return infinity;
    this->bfs(u);
    int dis = this->dis[v] - this->dis[u];
    return dis;
}

Graph::~Graph()
{
    if(AdjList)
        delete[] AdjList;
    AdjList = 0;
}

bool Graph::isCycleUtil(int v, bool visited[], bool restack[])
{
    if(visited[v]==false)
    {
        visited[v] = true;
        restack[v] = true;

        for(int i=0; i<AdjList[v].getLength(); i++)
        {
            int u = AdjList[v].getItem(i);

            if(visited[u]==false && isCycleUtil(u, visited, restack)==true)
                return true;
            else if(restack[u]==true)
                return true;
        }
    }

    restack[v] = false;
    return false;

}

bool Graph::isCycle()
{
    bool *visited = new bool[nVertices];
    bool *restack = new bool[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        visited[i] = false;
        restack[i] = false;
    }

    for(int i=0; i<nVertices; i++)
    {
        if(isCycleUtil(i, visited, restack)==true)
            return true;
    }

    return false;
}

int main()
{
    // Create a graph given in the above diagram
    Graph g;
    g.setnVertices(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    if(g.isCycle())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    return 0;
}
