// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/InitHubBase.h"
#include "UI/Init/SInitHUBWidget.h"
#include "SlateBasics.h"

AInitHubBase::AInitHubBase()
{
    //���� MenuHUDWidget��������AddViewport
    if (GEngine && GEngine->GameViewport)
    {
        /*
        ����Widget����MenuHUDWidgetָ�봫��ȥ����һ����Ӧ��Widget��
        ����SlateWidget��������ʽ SNew() SAssignNew()
        SNew(��) ֱ����������ͺã����ص���һ������ָ��
        SAssignNew(����ָ�룬ָ���Ӧ����) �����ع���ָ�룬һ�����ڰѴ�����widget������һ��ָ�������ʱ�������
        ������ֻ�ܴ����̳���SlateWidget����
        */
        SAssignNew(MenuHUDWidget, SInitHUBWidget);

        GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));
    }
}