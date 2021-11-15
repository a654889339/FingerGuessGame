#ifndef _BASE_JYVECTOR_H_
#define _BASE_JYVECTOR_H_

#define JYVECTOR_ERROR_INDEX -1

// �ʺϸ�Ƶ��������ɾ��Ϊ��������ݽṹ
template <typename T, typename ID_TYPE>
class JYVector
{
public:
    ID_TYPE add(T* pT)
    {
        ID_TYPE nResult = JYVECTOR_ERROR_INDEX;

        JYLOG_PROCESS_ERROR(pT);

        if (!m_UnuseID.empty())
        {
            nResult = m_UnuseID.top();
            m_UnuseID.pop();
        }
        else
        {
            m_Manager.push_back(*pT); // ������һ�ο������죬ҪС��
            m_EnableFlag.push_back(true);
            m_NextIndex.push_back(JYVECTOR_ERROR_INDEX);

            nResult = m_Manager.size() - 1;
        }

        m_bAddOrDelFlag = true;

    Exit0:
        return nResult;
    }

    bool del(ID_TYPE nID)
    {
        bool bResult = false;

        JY_PROCESS_ERROR(nID < m_Manager.size() && nID >= 0);
        JY_PROCESS_ERROR(m_EnableFlag[nID]);

        m_EnableFlag[nID] = false;
        m_UnuseID.push(nID);
        m_bAddOrDelFlag = true;

        JY_STD_BOOL_END
    }

    T* get(ID_TYPE nID)
    {
        T* pResult = NULL;

        JY_PROCESS_ERROR(nID < m_Manager.size() && nID >= 0);
        JY_PROCESS_ERROR(m_EnableFlag[nID]);

        pResult = &m_Manager[nID];
    Exit0:
        return pResult;
    }

    void clear()
    {
        m_Manager.clear();
        m_NextIndex.clear();
        m_EnableFlag.clear();
        m_bAddOrDelFlag = false;
    }

    template <typename JYVectorFunc>
    bool traversal(JYVectorFunc& Func)
    {
        bool bResult  = false;
        bool bRetCode = false;

        if (!m_bAddOrDelFlag)
        {
            ID_TYPE nID = m_nFirstID;
            while (nID != JYVECTOR_ERROR_INDEX)
            {
                bRetCode = Func(&m_Manager[nID]);
                JY_PROCESS_ERROR(bRetCode);

                nID = m_NextIndex[nID];
            }
        }
        else
        {
            ID_TYPE nPre = JYVECTOR_ERROR_INDEX;
            for (ID_TYPE i = 0; i < m_Manager.size(); i++)
            {
                if (!m_EnableFlag[i])
                    continue;

                bRetCode = Func(&m_Manager[i]);
                JY_PROCESS_ERROR(bRetCode);

                if (nPre == JYVECTOR_ERROR_INDEX)
                {
                    m_nFirstID = i;
                }
                else
                {
                    m_NextIndex[nPre] = i;
                }

                nPre = i;
            }

            m_bAddOrDelFlag = false;

            if (nPre != JYVECTOR_ERROR_INDEX)
                m_NextIndex[nPre] = JYVECTOR_ERROR_INDEX;
        }

        JY_STD_BOOL_END
    }

private:
    std::vector<T>                                                      m_Manager;
    std::vector<ID_TYPE>                                                m_NextIndex; // ��һ�����õ�����±ֻ꣬ά��m_EnableFlag[i]Ϊtrue�ĸ���
    std::vector<bool>                                                   m_EnableFlag;
    std::priority_queue<ID_TYPE, vector<ID_TYPE>, greater<ID_TYPE> >    m_UnuseID;
    bool                                                                m_bAddOrDelFlag; // ������ɾΪtrue��Ϊtrueʱ��m_NextIndex��m_nFirstID��������
    ID_TYPE                                                             m_nFirstID;
};


#endif