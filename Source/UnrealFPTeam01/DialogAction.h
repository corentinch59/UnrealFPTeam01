#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "DialogController.h"
#include "DialogAction.generated.h"


UENUM()
enum ActionType {
	DIALOG,
	SOUND,
	BOTH
};

UENUM()
enum DialogType {
	SPAWN,
	TICK
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALFPTEAM01_API UDialogAction : public UActorComponent {
	GENERATED_BODY()

public:	
	UDialogAction();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ActionType> actionType;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<DialogType> dialogType;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> sounds;

	UPROPERTY(EditAnywhere)
	TArray <FName> dialogs;

	UPROPERTY()
	ADialogController* dialogController;

	/*UFUNCTION(BlueprintImplementableEvent,Category="Dialog")
	void OnDialogSpawned(FName dialogName);
	*/
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
