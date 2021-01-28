// Fill out your copyright notice in the Description page of Project Settings.


#include "CppLib.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Editor/ContentBrowser/Private/SContentBrowser.h"
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"

TArray<FString> UCppLib::GetSelectedAssets() {
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	// get selected assets
	TArray<FAssetData> SelectedAssets;
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);
	// convert assets to string
	TArray<FString> Result;
	for (FAssetData& AssetData : SelectedAssets) {
		Result.Add(AssetData.PackageName.ToString());
	}
	return Result;
}

void UCppLib::SetSelectedAssets(TArray<FString> Paths) {
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	// convert the string to FName
	TArray<FName> PathsName;
	for (FString Path : Paths) {
		PathsName.Add(*Path);
	}
	FARFilter AssetFilter;
	AssetFilter.PackageNames = PathsName;
	// Find the assets
	TArray<FAssetData> AssetDatas;
	AssetRegistryModule.Get().GetAssets(AssetFilter, AssetDatas);
	// Ask the ContentBrowser to select them Different to python, the folder levels is also selected.
	ContentBrowserModule.Get().SyncBrowserToAssets(AssetDatas);
}

TArray<FString> UCppLib::GetSelectedFolders() {
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FString> SelectedFolders;
	ContentBrowserModule.Get().GetSelectedFolders(SelectedFolders);
	return SelectedFolders;
}

void UCppLib::SetSelectedFolders(TArray<FString> Paths) {
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FString> SelectedFolders;
	ContentBrowserModule.Get().SyncBrowserToFolders(Paths);
}