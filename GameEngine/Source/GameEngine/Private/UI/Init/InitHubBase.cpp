// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/InitHubBase.h"
#include "UI/Init/SInitHUBWidget.h"
#include "SlateBasics.h"

AInitHubBase::AInitHubBase()
{
    //创建 MenuHUDWidget，并把他AddViewport
    if (GEngine && GEngine->GameViewport)
    {
        /*
        创建Widget，吧MenuHUDWidget指针传进去，和一个对应的Widget类
        创建SlateWidget的两个方式 SNew() SAssignNew()
        SNew(类) 直接添加类名就好，返回的是一个共享指针
        SAssignNew(共享指针，指针对应的类) 不返回共享指针，一般用在把创建的widget保存在一个指针里面的时候用这个
        这两个只能创建继承于SlateWidget的类
        */
        SAssignNew(MenuHUDWidget, SInitHUBWidget);

        GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));
    }
}