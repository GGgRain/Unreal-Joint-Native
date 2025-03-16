//Copyright 2022~2024 DevGrain. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Node/JointFragment.h"

#include "DF_Text.generated.h"

/**
 * An interface class for the text nodes.
 * This has been added on Joint Native 1.12.0 update for the better support for the text related fragment variations.
 * @see UDF_Text, UJY_DF_GeneratedText for the usage.
 */

UINTERFACE(Blueprintable)
class JOINTNATIVE_API UJN_Text_Interface : public UInterface
{
	GENERATED_BODY()
};

class JOINTNATIVE_API IJN_Text_Interface
{
	GENERATED_BODY()

public:

	IJN_Text_Interface() {}

public:

	/**
	 * Get the text.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Text")
	const FText GetText() const;

	virtual const FText GetText_Implementation() const { return FText::GetEmpty(); }
	
	/**
	 * Set the text. 
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Text")
	void SetText(const FText& InText);

	virtual void SetText_Implementation(const FText& InText) {}

public:
	
	/**
	 * Get the text style table if it has any for the stylization. This is optional.
	 * @return The text style table for the text.
	 * @note we didn't keep it as a constant reference for the better compatibility, but it can be changed in the future.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Text")
	UDataTable* GetTextStyleTableIfPresent() const;

	virtual UDataTable* GetTextStyleTableIfPresent_Implementation() const { return nullptr; }
	
	
};


/**
 * A fragment that contains a text.
 * Can be used in multiple occasion.
 */
UCLASS(Category = "Joint Native|C++|Text")
class JOINTNATIVE_API UDF_Text: public UJointFragment, public IJN_Text_Interface
{
	GENERATED_BODY()

public:
	
	UDF_Text();

public:
	
	/**
	 * A text this text fragment contains.
	 * Can be used in various occasions where you need a text on the system, such as the dialogue widget text or select node.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText Text;

public:

	/**
	 * A text style fragment the text can use.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FJointNodePointer TextStyleInstance;

public:
	
	virtual const FText GetText_Implementation() const override;
	virtual void SetText_Implementation(const FText& InText) override;
	virtual UDataTable* GetTextStyleTableIfPresent_Implementation() const override;
	
};
