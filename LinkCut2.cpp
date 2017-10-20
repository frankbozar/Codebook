const int MAXN = 30000;
template <typename T>
struct LinkCutTree {
	enum Relation {
		L = 0, R = 1
	};
	struct Node {
		Node *child[2], *parent, *pathParent;
		T value, sum, max;
		bool reversed;
		Node(const T &value) : reversed(false), value(value), sum(value), max(value), parent(NULL), pathParent(NULL) {
			child[L] = child[R] = NULL;
		}
		Relation relation() {
			return this == parent->child[L] ? L : R;
		}
		void pushDown() {
			if (reversed) {
				std::swap(child[L], child[R]);
				if (child[L]) child[L]->reversed ^= 1;
				if (child[R]) child[R]->reversed ^= 1;
				reversed = false;
			}
		}
		void maintain() {
			sum = value;
			if (child[L]) sum += child[L]->sum;
			if (child[R]) sum += child[R]->sum;

			max = value;
			if (child[L]) max = std::max(max, child[L]->max);
			if (child[R]) max = std::max(max, child[R]->max);
		}
		void rotate() {
			if (parent->parent) parent->parent->pushDown();
			parent->pushDown(), pushDown();
			std::swap(pathParent, parent->pathParent);

			Relation x = relation();
			Node *oldParent = parent;

			if (oldParent->parent) oldParent->parent->child[oldParent->relation()] = this;
			parent = oldParent->parent;

			oldParent->child[x] = child[x ^ 1];
			if (child[x ^ 1]) child[x ^ 1]->parent = oldParent;

			child[x ^ 1] = oldParent;
			oldParent->parent = this;

			oldParent->maintain(), maintain();
		}
		void splay() {
			while (parent) {
				if (!parent->parent) rotate();
				else {
					parent->parent->pushDown(), parent->pushDown();
					if (relation() == parent->relation()) parent->rotate(), rotate();
					else rotate(), rotate();
				}
			}
		}
		void evert() {
			access();
			splay();
			reversed ^= 1;
		}
		void expose() {
			splay();
			pushDown();
			if (child[R]) {
				child[R]->parent = NULL;
				child[R]->pathParent = this;
				child[R] = NULL;
				maintain();
			}
		}
		bool splice() {
			splay();
			if (!pathParent) return false;

			pathParent->expose();
			pathParent->child[R] = this;
			parent = pathParent;
			pathParent = NULL;
			parent->maintain();
			return true;
		}
		void access() {
			expose();
			while (splice());
		}
		const T &querySum() {
			access();
			splay();
			return sum;
		}
		const T &queryMax() {
			access();
			splay();
			return max;
		}
	};
	Node *nodes[MAXN];
	void makeTree(int u, const T &value) {
		nodes[u - 1] = new Node(value);
	}
	void link(int u, int v) {
		nodes[v - 1]->evert();
		nodes[v - 1]->pathParent = nodes[u - 1];
	}
	void cut(int u, int v) {
		nodes[u - 1]->evert();
		nodes[v - 1]->access();
		nodes[v - 1]->splay();
		nodes[v - 1]->pushDown();
		nodes[v - 1]->child[L]->parent = NULL;
		nodes[v - 1]->child[L] = NULL;
		nodes[v - 1]->maintain();
	}
	const T &querySum(int u, int v) {
		nodes[u - 1]->evert();
		return nodes[v - 1]->querySum();
	}
	const T &queryMax(int u, int v) {
		nodes[u - 1]->evert();
		return nodes[v - 1]->queryMax();
	}
	void update(int u, const T &value) {
		nodes[u - 1]->splay();
		nodes[u - 1]->value = value;
		nodes[u - 1]->maintain();
	}
};
