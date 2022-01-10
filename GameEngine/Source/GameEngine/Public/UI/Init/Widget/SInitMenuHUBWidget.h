// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GAMEENGINE_API SInitMenuHUBWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInitMenuHUBWidget)
	{}
    SLATE_ARGUMENT(TWeakObjectPtr<class AInitMenuHUB>, InitMenuHUB)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

    // �����¼�
private:
    FReply Login();

private:
    TWeakObjectPtr<class AInitMenuHUB> InitMenuHUB;
    const struct FInitMenuStyle* MenuStyle;
};
