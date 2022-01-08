// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

class GAMEENGINE_API InitStyle
{
public:
    static void Initialze();

    //游戏注册的名字
    static FName GetStyleSetName();

    //游戏关闭的时候取消注册
    static void ShutDown();

    //给外部调用，获取单例
    static const ISlateStyle& Get();

private:
    //FSlateStyleSet类模板，用来注册样式
    static TSharedRef<class FSlateStyleSet> Create();

    //作为单例模式，这个变量一定不能放到构造函数里取实现
    static TSharedPtr<FSlateStyleSet> InitStyleInstance;
};
