struct AC{
	struct node{
		node *nx[26], *fl, *dl;
		int cnt, d;
		node(){
			memset(this, 0, sizeof(node));
		}
	} *root = new node;
	void add(const char *p){
		node *now=root;
		for(int i=0; p[i]; i++){
			node *&t=now->nx[ p[i]-'a' ];
			if( !t ) t=new node;
			now=t;
		}
		now->cnt++;
	}
	void build(){
		queue<node*> Q;
		for(Q.push(root); !Q.empty(); Q.pop()){
			node *now=Q.front();
			for(int i=0; i<26; i++){
				node *&t=now->nx[i], *fn=now->fl;
				if( t ){
					while( fn && !fn->nx[i] ) fn=fn->fl;
					t->fl= fn ? fn->nx[i] : root ;
					t->dl= t->fl->cnt ? t->fl : t->fl->dl ;
					t->d=now->d+1; Q.push(t);
				}
			}
		}
	}
	void match(const char *p){
		node *now=root;
		for(int i=0; p[i]; i++){
			while( now && !now->nx[ p[i]-'a' ] ) now=now->fl;
			if( !now ) now=root;
			else{
				now=now->nx[ p[i]-'a' ];
				for(node *tmp=now; tmp; tmp=tmp->dl);
			}
		}
	}
};
