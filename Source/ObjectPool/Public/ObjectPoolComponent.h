// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OBJECTPOOL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UObjectPoolComponent();

        /**
	* The class based on AActor which this pool holds.
	*/
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pooling")
	TSubclassOf<AActor> ObjectClass;

        /**
	* "How many objects the pool should spawn initially."
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pooling", meta=(ClampMin= "0"))
	int32 InitialSpawnAmount = 0;

        /**
	* "Decides wether the pool is allowed to spawn a new actor and expand the pool if something tries to pull an item and there's none available"
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Object Pooling", DisplayName="Should Pool Be Expanded")
	bool bCanExpandIfNeeded = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Object Pooling")
	TArray<AActor*> InactivePool;

	UPROPERTY(VisibleInstanceOnly, Category = "Object Pooling")
	TArray<AActor*> ActivePool;

        /**
	* "Moves an actor into the object pool and sends a OnPushed event to the object pool interface."
	*/
	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	void Push(AActor* Actor, UPARAM(DisplayName = "Sucess") bool& Success_Out);

        /**
	* "Fetches an actor reference from the pool and sends a OnPulled event to the object pool interface. If there's no available object it will spawn a new one if the settings allow it."
	*/
	UFUNCTION(BlueprintCallable, Category="Object Pooling")
	void Pull(AActor* & Actor_Out, UPARAM(DisplayName = "Sucess") bool& Success_Out);

	UFUNCTION(BlueprintInternalUseOnly)
	AActor* SpawnNewActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};


UINTERFACE()
class UObjectPool : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OBJECTPOOL_API IObjectPool
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Object Pooling")
	void OnPushed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ObjectPool")
	void OnPulled(UObjectPoolComponent* ObjectPool);
};
