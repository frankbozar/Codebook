#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct SA
{
    int n, size, last;
    vector<int> length, link, first, next, label, to;
    
    SA(const char* s=NULL) : n(strlen(s)), length(n*2, 0), link(n*2, -1), first(n*2, -1), next(n*4), label(n*4), to(n*4)
    {
        size=1;
        last=0;
        int edgesize=0;
        
        for(int i=0; i<n; i++)
        {
            int c=s[i];
            int curr=size++;
            length[curr]=length[last]+1;
            
            for(int prev=last; ; prev=link[prev])
            {
                if( prev==-1 )
                {
                    link[curr]=0;
                    break;
                }
                
                int index=findedge(prev, c);
                
                if( index!=-1 )
                {
                    int curlink=to[index];
                    
                    if( length[prev]+1==length[curlink] )
                        link[curr]=curlink;
                    else
                    {
                        int clone=size++;
                        length[clone]=length[prev]+1;
                        link[clone]=link[curlink];
                        int linkedge=first[curlink];
                        
                        while( linkedge!=-1 )
                        {
                            next[edgesize]=first[clone];
                            first[clone]=edgesize;
                            label[edgesize]=label[linkedge];
                            to[edgesize++]=to[linkedge];
                            linkedge=next[linkedge];
                        }
                        
                        for(; prev!=-1; prev=link[prev])
                        {
                            int edge=findedge(prev, c);
                            
                            if( edge==-1 || to[edge]!=curlink )
                                break;
                            
                            to[edge]=clone;
                        }
                        
                        link[curr]=link[curlink]=clone;
                    }
                    
                    break;
                }
                
                next[edgesize]=first[prev];
                first[prev]=edgesize;
                label[edgesize]=c;
                to[edgesize++]=curr;
            }
            
            last=curr;
        }
        
        printf("%d %d %d\n", size, last, edgesize);
        
        for(int i=0; i<size+size; i++)
            printf("~ %d %d %d\n", length[i], link[i], first[i]);
        
        for(int i=0; i<=last+last; i++)
            printf("! %d %d %d\n", next[i], label[i], to[i]);
    }
    
    int findedge(int vertex, int lab)
    {
        for(int edge=first[vertex]; edge!=-1; edge=next[edge])
            if( label[edge]==lab )
                return edge;
        
        return -1;
    }
};

int main()
{
    char s[1000];
    scanf("%s", s);
    SA S(s);
}
