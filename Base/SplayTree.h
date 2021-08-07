#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

#include <cassert>

template <typename STKey, typename STValue>
class SplayTree
{
    struct Node
    {
        STKey Key;
        STValue* pValue;
        Node* par, *ch[2];

        Node()
        {
            pValue = new STValue();
            par = NULL;
            ch[0] = NULL;
            ch[1] = NULL;
        }

        ~Node()
        {
            assert(pValue);
            delete pValue;
        }
    };

public:
    SplayTree()
    {
        m_pRoot = NULL;
    }

    ~SplayTree()
    {
        Clear();
    }

    STValue* Add(STKey Key)
    {
        STValue* pResult = NULL;
        Node* pNode = NULL;

        JY_PROCESS_ERROR(FindNode(Key) == NULL);

        pNode = new Node();
        JYLOG_PROCESS_ERROR(pNode);
        JYLOG_PROCESS_ERROR(pNode->pValue);

        pNode->Key = Key;

        JY_PROCESS_ERROR(Insert(pNode));

        pResult = pNode->pValue;
    Exit0:
        if (!pResult && pNode)
        {
            delete pNode;
        }
        return pResult;
    }

    STValue* Find(STKey Key)
    {
        Node* pResult = NULL;

        pResult = FindNode(Key);
        if (pResult)
            return pResult->pValue;
        return NULL;
    }

    bool Remove(STKey Key)
    {
        bool bResult = false;
        Node* pIter = NULL;
        Node* pUpper = NULL;

        pIter = FindNode(Key);
        JY_PROCESS_SUCCESS(pIter == NULL);

        pUpper = UpperBound(Key);
        if (pUpper)
        {
            Splay(pIter, NULL);
            Splay(pUpper, m_pRoot);
            m_pRoot = pUpper;
            pUpper->ch[0] = pIter->ch[0];
            if (pIter->ch[0])
                pIter->ch[0]->par = pUpper;
        }
        else
        {
            Erase(pIter);
        }

        delete pIter;

    Exit1:
        bResult = true;
    Exit0:
        return bResult;
    }

    void Clear()
    {
        DFS_Clear(m_pRoot);
        m_pRoot = NULL;
    }

private:
    void PushDown(Node* x){}
    void PushUp(Node* x){}

    void Rotate(Node* x, int c)
    {
        Node* y = x->par;
        PushDown(y);
        PushDown(x);
        y->ch[!c] = x->ch[c];
        if (x->ch[c] != NULL) x->ch[c]->par = y;
        x->par = y->par;
        if (y->par != NULL) {
            if (y->par->ch[0] == y) y->par->ch[0] = x;
            else y->par->ch[1] = x;
        }
        x->ch[c] = y;
        y->par = x;
        PushUp(y);
        if (y == m_pRoot) m_pRoot= x;
    }

    void Splay(Node* x, Node* f)
    {
        Node* y = NULL;
        Node* z = NULL;

        JY_PROCESS_ERROR(x);

        for (PushDown(x); x->par && x->par != f; ) {
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

        JY_STD_VOID_END
    }

    void Link(Node* pA, int nASon, Node* pB)
    {
        assert(pA);
        assert(pB);
        
        pA->ch[nASon] = pB;
        pB->par = pA;
    }

    Node* FindNode(STKey Key)
    {
        Node* pResult = NULL;
        Node* pIter = m_pRoot;

        while (pIter) {
            PushDown(pIter);
            if (pIter->Key == Key)
            {
                pResult = pIter;
                break;
            }

            pIter = pIter->ch[Key < pIter->Key];
        }

        if (pIter)
            Splay(pIter, NULL);

        return pResult;
    }

    Node* LowerBound(STKey Key)
    {
        Node* pResult = NULL;
        Node* pIter = m_pRoot;

        while (pIter) {
            PushDown(pIter);
            if (pIter->Key < Key)
            {
                if (!pResult || pResult->Key > pIter->Key)
                    pResult = pIter;
            }
            else if (pIter->Key == Key)
            {
                pResult = pIter;
                break;
            }

            pIter = pIter->ch[Key < pIter->Key];
        }

        if (pIter)
            Splay(pIter, m_pRoot);

        return pResult;
    }

    Node* UpperBound(STKey Key)
    {
        Node* pResult = NULL;
        Node* pIter = m_pRoot;

        while (pIter) {
            PushDown(pIter);
            if (pIter->Key > Key)
            {
                if (!pResult || pResult->Key < pIter->Key)
                    pResult = pIter;
            }

            pIter = pIter->ch[Key < pIter->Key];
        }

        if (pIter)
            Splay(pIter, m_pRoot);

        return pResult;
    }

    bool Insert(Node* pNode)
    {
        bool bResult = false;
        Node* pLower = NULL;
        Node* pUpper = NULL;

        if (m_pRoot == NULL)
        {
            m_pRoot = pNode;
            goto Exit0;
        }

        pLower = LowerBound(pNode->Key);
        pUpper = UpperBound(pNode->Key);

        if (pLower == NULL)
        {
            Splay(pUpper, NULL);
            Link(pUpper, 0, pNode);
        }
        else
        {
            Splay(pLower, NULL);
            if (pUpper == NULL)
            {
                Link(pLower, 1, pNode);
            }
            else
            {
                Splay(pUpper, pLower);
                Link(pUpper, 0, pNode);
            }
        }

        Splay(pNode, NULL);

        bResult = true;
    Exit0:
        return bResult;
    }

    void Erase(Node* pNode)
    {
        Node* pParent = NULL;
        int nParentSon = 0;
        int nNodeChild = -1;

        assert(pNode);

        if (pNode->ch[0])
            nNodeChild = 0;
        if (pNode->ch[1])
        {
            assert(nNodeChild == -1);
            nNodeChild = 1;
        }

        if (m_pRoot == pNode)
        {
            if (nNodeChild != -1)
            {
                m_pRoot = pNode->ch[nNodeChild];
                m_pRoot->par = NULL;
            }
            else
                m_pRoot = NULL;
            return;
        }

        pParent = pNode->par;
        assert(pParent);

        nParentSon = pParent->ch[1] == pNode;

        if (nNodeChild != -1)
        {
            pParent->ch[nParentSon] = pNode->ch[nNodeChild];
            pNode->ch[nNodeChild]->par = pParent;
        }
    }

    void DFS_Clear(Node* pNode)
    {
        if (pNode == NULL)
            return;

        for (int i = 0; i < 2; i++)
            DFS_Clear(pNode->ch[i]);

        delete pNode;
    }

private:
    Node* m_pRoot;

};

#endif