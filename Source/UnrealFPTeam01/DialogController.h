#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogController.generated.h"

UCLASS()
class UNREALFPTEAM01_API ADialogController : public AActor {
	GENERATED_BODY()
	
public:	
	ADialogController();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialog")
	void OnDialogSpawned(FName dialogName);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
