struct treap{
	struct node{
		node *l=NULL, *r=NULL, *p=NULL;
		int pri=rand(), siz=1, key, val;
	};
	static void pull(node* p){}
	static void push(node* p){
		if( p!=NULL ){
			set_parent(p->l, p);
			set_parent(p->r, p);
		}
	}
	static void set_parent(node* x, node* p=NULL){
		if( x!=NULL ) x->p=p;
	}
	static node* merge(node* l, node* r){
		if( l==NULL )
			return r;
		else if( r==NULL )
			return l;
		else if( l->pri>r->pri ){
			push(l); l->r=merge(l->r, r);
			pull(l); return l;
		}
		else{
			push(r); r->l=merge(l, r->l);
			pull(r); return r;
		}
	}
	static void split(node* p, int key, node*& l, node*& r){
		push(p);
		if( p==NULL ) l=r=NULL;
		else if( p->key<=key ){
			l=p;
			split(l->r, key, l->r, r);
			pull(l);
		}
		else{
			r=p;
			split(r->l, key, l, r->l);
			pull(r);
		}
	}
};
