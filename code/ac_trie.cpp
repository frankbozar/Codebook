struct actrie{
	struct node{
		node *flink, *nxt[26]; //failure link, trie structure
		int pcnt;
		node(){
			memset(this, 0, sizeof(node));
		}
	} *root, *que[MAXN*MAXP];//length*number
	actrie(){
		root=new node;
	}
	void addPattern(const char *P){
		node *now = root;
		for(int i=0; P[i]; i++){
			if( now->nxt[ P[i]-'a' ]==NULL )
				now->nxt[ P[i]-'a' ]=new node();
			now=now->nxt[ P[i]-'a' ];
		}
		++now->pcnt;
	}
	void build(){
		que[0]=root;
		for(int front=0, rear=1; front<rear; ){
			node *now=que[front], *fnode;
			for(int i=0; i<26; i++)
				if(now->nxt[i]){
					for(fnode=now->flink; fnode && !fnode->nxt[i]; fnode=fnode->flink);
					if(fnode) now->nxt[i]->flink=fnode->nxt[i];
					else now->nxt[i]->flink=root;
					que[rear++]=now->nxt[i];
				}
			++front;
		}
	}
	int match(const char* S){
		int ret=0;
		node *now=root;
		for(int i=0; S[i]; i++){
			while( now && !now->nxt[ S[i]-'a' ] )
				now=now->flink;
			if( now ){
				now=now->nxt[ S[i]-'a' ];
				node *temp=now;
				while( temp && temp->pcnt!=-1 ){
					ret+=temp->pcnt;
					temp->pcnt=-1;
					temp=temp->flink;
				}
			}
			else now = root;
		}
		return ret;
	}
};
