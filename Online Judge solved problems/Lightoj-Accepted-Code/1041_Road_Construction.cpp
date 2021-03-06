/* Ashiq Uddin Pranto
   Department of Computer Science and Engineering
   BATCH 27
   University Of Rajshahi,Bangladesh
*/

#include <iostream>
#include<stdio.h>
#include<cmath>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<string.h>
#include<algorithm>
#include<vector>
#include<bitset>
#include<string.h>
#include <stack>
#include<queue>
#include<deque>

#define ll long long
#define ld long double
#define pb(x) push_back(x)
#define mp make_pair
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vii vector<int>
#define vll vector<ll>
#define PI (2*acos(0.0))
#define sqr(x) ((x)*(x))
#define FOR(start,end) for(ll i=start;i<=end;i++)
#define readfile freopen("input.txt","r",stdin);
#define writefile freopen("output.txt","w",stdout);
#define mx 100006
#define inf 1000000

using namespace std;

struct edgeStructure
{
    ll u,v,w;
};

bool operator<(edgeStructure lhs,edgeStructure rhs)
{
    return lhs.w<rhs.w;
}

vector<edgeStructure>edgeVector;
vector<edgeStructure>edgesOfMst;
ll parent[mx];
ll rankParent[mx];
ll parents[mx];

void makeSet(ll n)
{
    for(ll i=0;i<=n;i++)
    {
        parent[i]=i;
        rankParent[i]=0;
        parents[i]=-1;
    }
}

ll findParent(ll x)
{
    if(parent[x]==x) return x;
    else
    {
        return parent[x]=findParent(parent[x]);
    }
}


void unionSet(ll x,ll y)
{
    ll px=findParent(x);
    ll py=findParent(y);
    if(rankParent[px]<rankParent[py])
    {
        parent[px]=py;
    }
    else if(rankParent[px]>rankParent[py])
    {
        parent[py]=px;
    }
    else
    {
        parent[py]=px;
        rankParent[px]++;
    }
}

ll kruskal(ll n)
{
    makeSet(n);
    sort(edgeVector.begin(),edgeVector.end());

    ll sz=edgeVector.size();

    ll ans=0;
    ll edge=0;
    for(ll i=0;i<sz;i++)
    {
        ll pu=findParent(edgeVector[i].u);
        ll pv=findParent(edgeVector[i].v);
        if(pu!=pv)
        {
            edge++;
            //edgesOfMst.pb(edgeVector[i]);
            //parents[edgeVector[i].v]=edgeVector[i].u;
            unionSet(parent[pu],parent[pv]);
            ans+=edgeVector[i].w;
        }
    }
    if(edge!=n-1) return -1;
    else return ans;
}

ll second_best_mst(ll vertex)
{
    ll second_best_mst=inf;
    cout<<"\nAll other MST\n";
    for(ll i=0;i<edgesOfMst.size();i++)
    {
        makeSet(vertex);
        ll sum=0;
        ll edge1=0;
        for(ll j=0;j<edgeVector.size();j++)
        {
            if((edgesOfMst[i].u==edgeVector[j].u)&& (edgesOfMst[i].v==edgeVector[j].v) && (edgesOfMst[i].w==edgeVector[j].w))
            {
                //cout<<"loop"<<endl;
                 continue;
            }
            ll pu=findParent(edgeVector[j].u);
            ll pv=findParent(edgeVector[j].v);
            if(pu!=pv)
            {
                edge1++;
                unionSet(parent[pu],parent[pv]);
                sum+=edgeVector[j].w;
            }
        }
        if(edge1!=vertex-1) continue;
        cout<<sum<<endl;
        if(second_best_mst>sum) second_best_mst=sum;
    }
    return second_best_mst;
}

int main()
{
    //readfile
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    ll vertex,edge,test;
    string a,b;
    //cin>>vertex>>edge;
    //makeSet(vertex);
    cin>>test;
    for(ll t=1;t<=test;t++)
    {
        map<string,ll>mapping;
        cin>>edge;
        ll value=0;
        for(ll i=0;i<edge;i++)
        {
            edgeStructure e;
            cin>>a>>b>>e.w;
            if(mapping[a]==0) mapping[a]=++value;
            if(mapping[b]==0) mapping[b]=++value;
            e.u=mapping[a];
            e.v=mapping[b];
            edgeVector.pb(e);
        }
        printf("Case %lld: ",t);
        ll ans=kruskal(mapping.size());
        if(ans==-1) cout<<"Impossible\n";
        else cout<<ans<<endl;
        //cout<<"MST Cost "<<kruskal(vertex)<<endl;
        //cout<<"\nAll edges of the MST\n";
        //for(ll i=0;i<edgesOfMst.size();i++) cout<<edgesOfMst[i].u<<" "<<edgesOfMst[i].v<<" "<<edgesOfMst[i].w<<endl;

        //cout<<"\n2nd best mst = "<<second_best_mst(vertex)<<endl;
        //cout<<mapping.size()<<endl;
        edgeVector.clear();
    }
}
