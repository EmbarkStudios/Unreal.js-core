// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "JavascriptGraphPinObject.h"
#include "JavascriptGraphEdNode.h"

#define LOCTEXT_NAMESPACE "JavascriptGraphPinObject"

/////////////////////////////////////////////////////
// UJavascriptGraphPinObject
UJavascriptGraphPinObject::UJavascriptGraphPinObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UJavascriptGraphPinObject::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Pin.Reset();
}

TSharedRef<SWidget> UJavascriptGraphPinObject::RebuildWidget()
{
	auto defaultWidget = SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("JavascriptGraphPinObject", "JavascriptGraphPinObject"))
		];

	if (IsDesignTime())
	{
		return RebuildDesignWidget(defaultWidget);
	}
	else
	{
		if (OnGetGraphPin.IsBound())
		{
			FJavascriptEdGraphPin GraphPin = OnGetGraphPin.Execute();
			if (GraphPin.IsValid())
			{
				if (OnGetDefaultValue.IsBound())
				{
					UObject* InDefaultObject = OnGetDefaultValue.Execute();
					GraphPin->DefaultObject = InDefaultObject;
				}
				Pin = SNew(SJavascriptGraphPinObject, GraphPin.Get(), this);

				// @todo:
				UJavascriptGraphEdNode* GraphEdNode = CastChecked<UJavascriptGraphEdNode>(GraphPin->GetOwningNode());
				Pin->SetOwner(StaticCastSharedRef< SGraphNode >(GraphEdNode->SlateGraphNode->AsShared()));

				return Pin.ToSharedRef();
			}
		}

		return defaultWidget;
	}
}

void UJavascriptGraphPinObject::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (Pin.IsValid())
	{

	}
}

#undef LOCTEXT_NAMESPACE