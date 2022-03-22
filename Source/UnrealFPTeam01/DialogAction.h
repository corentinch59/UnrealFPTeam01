#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "DialogAction.generated.h"


UENUM()
enum ActionType {
	DIALOG,
	SOUND,
	BOTH
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALFPTEAM01_API UDialogAction : public UActorComponent {
	GENERATED_BODY()

public:	
	UDialogAction();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ActionType> type;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> sounds;

	UPROPERTY(EditAnywhere)
	TArray <FName> dialogs;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
