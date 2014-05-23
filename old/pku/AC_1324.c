#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int kk[4][2]={1,0,0,1,0,-1,-1,0},N,M,L;
struct point{
    char x,y;
    int dis,body;
};
int bfs();
int main(){
    int Cas=0;
    while(scanf("%d%d%d",&N,&M,&L)==3){
        if(N==0&&M==0&&L==0)break;
        printf("Case %d: %d\n",++Cas,bfs());
    }
    return 0;
}
char viss[20][20][1<<14];
int vis(struct point* t){
    int ans=0,i=0;
    if(viss[t->x][t->y][t->body])return 1;
    viss[t->x][t->y][t->body]=1;
    return 0;
}
char map[20][20],mapt[20][20];
char valid(int x,int y){
    if(x<0||x>=N||y<0||y>=M||mapt[x][y])return 0;
    return 1;
}
struct point Q[20*20*(1<<14)];
int head,tail;
int bfs(){
    int x,y,lx,ly,i,k,nx,ny;
    struct point t,now;
    memset(viss,0,sizeof(viss));
    scanf("%d%d",&lx,&ly);
    t.x=lx-1;t.y=ly-1;t.dis=0;t.body=0;
    for(i=1;i<L;++i){
        scanf("%d%d",&x,&y);
        for(k=0;k<4;++k)if(lx+kk[k][0]==x&&ly+kk[k][1]==y)break;
        t.body|=k<<((i-1)<<1);
        lx=x;ly=y;
    }
    memset(map,0,sizeof(map));
    scanf("%d",&k);
    for(i=0;i<k;++i){
        scanf("%d%d",&x,&y);
        map[x-1][y-1]=1;
    }
    head=tail=0;
    Q[tail++]=t;
    vis(&t);
    while(head!=tail){
        now=Q[head++];
        if(now.x==0&&now.y==0)return now.dis;
        
        memcpy(mapt,map,sizeof(map));
        mapt[x=now.x][y=now.y]=1;
        int s=now.body;
        for(i=1;i<L;++i,s>>=2){
            k=s&3;
            mapt[x=x+kk[k][0]][y=y+kk[k][1]]=1;
        }
        
        for(k=0;k<4;++k){
            if(!valid(nx=now.x+kk[k][0],ny=now.y+kk[k][1]))continue;
            t.x=nx,t.y=ny;
            t.body=((now.body<<2)|(3-k))&((1<<((L-1)<<1))-1);
            t.dis=now.dis+1;
            if(!vis(&t)){
                Q[tail++]=t;
            }
        }
    }
    return -1;
}
