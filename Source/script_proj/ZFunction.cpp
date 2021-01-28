// Fill out your copyright notice in the Description page of Project Settings.


#include "ZFunction.h"

void UZFunction::CalledFromPython(FString InputString) {
	UE_LOG(LogTemp, Error, TEXT("%s"), *InputString);
}