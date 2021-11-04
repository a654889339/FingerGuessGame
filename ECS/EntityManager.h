#ifndef _ECS_ENTITY_MANAGER_H_
#define _ECS_ENTITY_MANAGER_H_

class EntityManager
{
public:


    std::multimap<ComponentType, int_eid> m_EntityManager;
};

#endif