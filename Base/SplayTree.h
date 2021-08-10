#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

#include <cassert>

struct STString
{
    char szString[_NAME_LEN];
    STString(){memset(szString, 0, sizeof(szString));}
    STString(const char _szStr[])
    {
        strncpy(szString, _szStr, sizeof(szString));
        szString[sizeof(szString) - 1] = '\0';
    }
    bool operator < (const STString& _Right) const 
    {
        return strcmp(szString, _Right.szString) < 0;
    }
    bool operator == (const STString& _Right) const
    {
        return strcmp(szString, _Right.szString) == 0;
    }
    bool operator <= (const STString& _Right) const
    {
        return strcmp(szString, _Right.szString) <= 0;
    }
};

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
            if (pValue)
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
        clear();
    }

    STValue* add(STKey Key)
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

    bool add(STKey Key, STValue Value)
    {
        bool bResult = false;
        STValue* pValue = add(Key);

        JY_PROCESS_ERROR(pValue);
        *pValue = Value;

        JY_STD_BOOL_END
    }

    bool remove(STKey Key)
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
            Link(pUpper, 0, pIter->ch[0]);
            SetRoot(pUpper);
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

    STValue* find(STKey Key)
    {
        Node* pResult = FindNode(Key);
        if (pResult)
            return pResult->pValue;
        return NULL;
    }

    template <typename STFunc>
    bool traversal(STFunc& Func)
    {
        return DFS_Traversal(m_pRoot, Func);
    }

    void clear()
    {
        DFS_Clear(m_pRoot);
        SetRoot(NULL);
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
        if (y == m_pRoot)
            SetRoot(x);
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

        pA->ch[nASon] = pB;
        if (pB)
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

            pIter = pIter->ch[pIter->Key < Key];
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
                if (!pResult || pResult->Key < pIter->Key)
                    pResult = pIter;
            }
            else if (pIter->Key == Key)
            {
                pResult = pIter;
                break;
            }

            pIter = pIter->ch[pIter->Key < Key];
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
            if (Key < pIter->Key)
            {
                if (!pResult || pIter->Key < pResult->Key)
                    pResult = pIter;
            }

            pIter = pIter->ch[pIter->Key <= Key];
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
            SetRoot(pNode);
            goto Exit1;
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

        JY_STD_BOOL_SUCCESS_END
    }

    void SetRoot(Node* pNode)
    {
        m_pRoot = pNode;
        if (m_pRoot)
            m_pRoot->par = NULL;
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
                SetRoot(pNode->ch[nNodeChild]);
            else
                SetRoot(NULL);
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

    template <typename STFunc>
    bool DFS_Traversal(Node* pNode, STFunc& Func)
    {
        bool bResult = false;
        bool bRetCode = false;

        if (pNode == NULL)
            return true;

        for (int i = 0; i < 2; i++)
        {
            bRetCode = DFS_Traversal(pNode->ch[i], Func);
            JY_PROCESS_ERROR(bRetCode);
        }

        bRetCode = Func(pNode->pValue);
        JY_PROCESS_ERROR(bRetCode);

        JY_STD_BOOL_END
    }

private:
    Node* m_pRoot;

};

#endif