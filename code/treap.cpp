struct treap{
	struct node{
		int pri, siz, key, val;
		node *l, *r, *p;
	};
	static void set_parent(node* x, node* p=NULL){
		if( x!=NULL ) x->p=p;
	}
	static void push(node* p){}
	static void pull(node* p){}
	static node* merge(node* l, node* r, node* p=NULL){//if merge to root
		if( l==NULL ){
			set_parent(r, p); return r;
		}
		else if( r==NULL ){
			set_parent(l, p); return l;
		}
		else if( l->pri>r->pri ){
			push(l); l->r=merge(l->r, r, l);
			pull(l); set_parent(l, p);
			return l;
		}
		else{
			push(r); r->l=merge(l, r->l, r);
			pull(r); set_parent(r, p);
			return r;
		}
	}
	static void split(node* p, int key, node*& l, node*& r){
		if( p==NULL ) l=r=NULL;
		else if( p->key<=key ){
			l=p;
			push(l);
			split(l->r, key, l->r, r);
			set_parent(l->r, l);
			pull(l);
		}
		else{
			r=p;
			push(r);
			split(r->l, key, l, r->l);
			set_parent(r->l, r);
			pull(r);
		}
	}
};