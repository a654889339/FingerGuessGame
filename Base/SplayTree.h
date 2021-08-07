#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

template <typename STKey, typename STValue>
class SplayTree
{
    STValue* NewNode(STKey Key)
    {
        Node* x = Ind[tot++];
        x->val = x->sum = x->max = x->mls = x->mrs = val;
        x->siz = 1;
        x->par = par;
        x->rev = x->sm = false;
        if (x->ch[0] != null) Ind[--tot] = x->ch[0];
        if (x->ch[1] != null) Ind[--tot] = x->ch[1];
        x->ch[0] = x->ch[1] = null;
        return x;
    }

    void Modify(Node* x, int d)
    {
        if (x == null) return;
        x->val = x->d = d;
        x->sm = true;
        x->sum = x->siz * d;
        x->mls = x->mrs = x->max = max(x->sum, d);
        x->rev = false;
    }

    void Reverse(Node* x)
    {
        if (x == null) return;
        x->rev ^= true;
        swap(x->mls, x->mrs);
        swap(x->ch[0], x->ch[1]);
    }

    void PushDown(Node* x)
    {
        if (x == null) return;
        if (x->sm) {
            Modify(x->ch[0], x->d);
            Modify(x->ch[1], x->d);
            x->sm = false;
        }
        if (x->rev) {
            Reverse(x->ch[0]);
            Reverse(x->ch[1]);
            x->rev = false;
        }
    }
    void PushUp(Node* x)
    {
        if (x == null) return;
        x->siz = x->ch[0]->siz + x->ch[1]->siz + 1;
        x->sum = x->ch[0]->sum + x->ch[1]->sum + x->val;
        x->mls = max(x->ch[0]->mls, x->ch[0]->sum + x->val + max(0, x->ch[1]->mls));
        x->mrs = max(x->ch[1]->mrs, x->ch[1]->sum + x->val + max(0, x->ch[0]->mrs));
        x->max = max(x->ch[0]->max, x->ch[1]->max);
        x->max = max(x->max, max(x->ch[0]->mrs, 0) + x->val + max(x->ch[1]->mls, 0));
        return;
    }
    void Rotate(Node* x, int c)
    {
        Node* y = x->par;
        PushDown(y);
        PushDown(x);
        y->ch[!c] = x->ch[c];
        if (x->ch[c] != null) x->ch[c]->par = y;
        x->par = y->par;
        if (y->par != null) {
            if (y->par->ch[0] == y) y->par->ch[0] = x;
            else y->par->ch[1] = x;
        }
        x->ch[c] = y;
        y->par = x;
        PushUp(y);
        if (y == root) root = x;
    }
    void Splay(Node* x, Node* f)
    {
        Node* y, * z;
        for (PushDown(x); x->par != f; ) {
            y = x->par, z = y->par;
            if (z == f) {
                if (y->ch[0] == x) Rotate(x, 1);
                else Rotate(x, 0);
            }
            else {
                if (z->ch[0] == y) {
                    if (y->ch[0] == x) Rotate(y, 1), Rotate(x, 1);
                    else Rotate(x, 0), Rotate(x, 1);
                }
                else {
                    if (y->ch[0] == x) Rotate(x, 1), Rotate(x, 0);
                    else Rotate(y, 0), Rotate(x, 0);
                }
            }
        }
        PushUp(x);
    }
    void Select(int k, Node* f)
    {
        Node* cur = root;
        int temp;
        while (1) {
            PushDown(cur);
            temp = cur->ch[0]->siz;
            if (k == temp) break;
            if (k < temp) cur = cur->ch[0];
            else {
                k -= (temp + 1);
                cur = cur->ch[1];
            }
        }
        Splay(cur, f);
    }
    Node* Build(int L, int R, Node* par)
    {

        if (L > R) return null;
        int mid = (L + R) / 2;
        Node* x = NewNode(number[mid], par);
        x->ch[0] = Build(L, mid - 1, x);
        x->ch[1] = Build(mid + 1, R, x);
        PushUp(x);
        return x;
    }
    void Insert(int pos, int L, int R)
    {
        Select(pos, null);
        Select(pos + 1, root);
        root->ch[1]->ch[0] = Build(L, R, root->ch[1]);
        PushUp(root->ch[1]);
        Splay(root->ch[1]->ch[0], null);
    }
    Node* Delete(int L, int R)
    {
        Node* ret;
        Select(L - 1, null);
        Select(R + 1, root);
        ret = root->ch[1]->ch[0];
        root->ch[1]->ch[0] = null;
        PushUp(root->ch[1]);
        Splay(root->ch[1], null);
        return ret;
    }
    void Init()
    {
        null = &nod[0];
        null->siz = null->sum = 0;
        null->val = null->mls = null->mrs = null->max = -inf;
        tot = 1;
        for (int i = 0; i != maxn; i++) {
            Ind[i] = &nod[i];
            nod[i].ch[0] = nod[i].ch[1] = null;
        }
    }
    void Modify(int L, int R, int d)
    {
        Select(L - 1, null);
        Select(R + 1, root);
        Modify(root->ch[1]->ch[0], d);
        Splay(root->ch[1]->ch[0], null);
    }
    void Reverse(int L, int R)
    {
        Select(L - 1, null);
        Select(R + 1, root);
        Reverse(root->ch[1]->ch[0]);
        Splay(root->ch[1]->ch[0], null);
    }
    int Sum(int L, int R)
    {
        Select(L - 1, null);
        Select(R + 1, root);
        return root->ch[1]->ch[0]->sum;
    }
    void Print()
    {
        Select(1, null);
        printf("%d", root->val);
        for (int i = 2; i <= root->siz - 2; i++) {
            Select(i, null);
            printf(" %d", root->val);
        }
        printf("\n");
    }
};

#endif