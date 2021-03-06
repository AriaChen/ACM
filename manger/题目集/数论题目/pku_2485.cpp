#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct  {
    int from, to,weight;
}edge;

vector<edge> edges;

bool edgeCmp(const edge& a, const edge& b)
{
    return a.weight < b.weight;
}

void union_set(vector<int>& sets, int n, int from, int to)
{
    int j;
    if(sets[from] < 0 && sets[to] < 0) {
        int t = sets[to];
        for (j = 1; j <= n; ++j) {//合并集合
            if(sets[j] == t)
                sets[j] = sets[from];
        }
    }
    else if(sets[from] < 0 && sets[to] > 0) {
        sets[to] = sets[from];
    }
    else if(sets[from] > 0 && sets[to] < 0) {
        sets[from] = sets[to];
    }
    else if(sets[from] > 0 && sets[to] > 0) {
        sets[from] = sets[to] = -sets[from];
    }            
}

int MST_Kruskal_pku2421(int n)
{
    //所有的边按权值非降序排列
    sort(edges.begin(), edges.end(), edgeCmp);
    
    int  nMaxLen = -1000,
        nEdgeNum = edges.size(),//边的条数
        i, from, to;
    
    vector<bool> used(nEdgeNum+1, false); //标记每一条边是否已经用来构造生成树
    vector<int> sets(n+1);    //记录每一个定点加入的集合
    for(i = 1; i <= n; ++i) {
        sets[i] = i;//初始时, 每个定点单独属于一个集合
    } 
    
    //寻找权值最小的安全边加入,直到生成最小生成树
    for (i = 0; i < nEdgeNum; ++i) {
        from = edges[i].from;
        to = edges[i].to;
        
        //节点from 和 to 属于同一集合或连接他们的边已经用过了,则跳过不用考虑
        if (sets[from] == sets[to] || used[i] == true) {
            continue;
        }
        else {
            union_set(sets, n, from, to);
            nMaxLen = edges[i].weight;
        }        
    }
    return nMaxLen;
}

int main()
{
    int t, n, i, j, w;
    cin>>t;
    while (t--) {
        cin>>n;    
        edges = vector<edge>(n*(n-1)/2);
        int index = 0;
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                scanf("%d", &w);
                if (w > 0 && j >= i) {
                    edges[index].weight = w;
                    edges[index].from = i;
                    edges[index].to = j;
                    ++index;
                }                        
            }        
        }
        cout<<MST_Kruskal_pku2421(n)<<endl;
    }
    return 0;
}

