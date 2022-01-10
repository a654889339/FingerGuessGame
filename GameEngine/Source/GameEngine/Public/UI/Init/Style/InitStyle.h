// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

class GAMEENGINE_API InitStyle
{
public:
    static void Initialze();

    //��Ϸע�������
    static FName GetStyleSetName();

    //��Ϸ�رյ�ʱ��ȡ��ע��
    static void ShutDown();

    //���ⲿ���ã���ȡ����
    static const ISlateStyle& Get();

private:
    //FSlateStyleSet��ģ�壬����ע����ʽ
    static TSharedRef<class FSlateStyleSet> Create();

    //��Ϊ����ģʽ���������һ�����ܷŵ����캯����ȡʵ��
    static TSharedPtr<FSlateStyleSet> InitStyleInstance;
};
