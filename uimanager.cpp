#include "uimanager.h"

#include "bankdialog.h"
#include "buildingdetaildialog.h"
#include "companydetaildialog.h"
#include "setroutedialog.h"

UIManager::UIManager() { }

UIManager::~UIManager() { }

UIManager &UIManager::instance() {
	static UIManager uiManager;
	return uiManager;
}

BankDialog *UIManager::bankDialog() {
	if (!bankDialog_)
		bankDialog_ = new BankDialog;
	return bankDialog_;
}

BuildingDetailDialog *UIManager::buildingDetailDialog() {
	if (!buildingDetailDialog_)
		buildingDetailDialog_ = new BuildingDetailDialog;
	return buildingDetailDialog_;
}

CompanyDetailDialog *UIManager::companyDetailDialog() {
	if (!companyDetailDialog_)
		companyDetailDialog_ = new CompanyDetailDialog;
	return companyDetailDialog_;
}

SetRouteDialog *UIManager::setRouteDialog() {
	if (!setRouteDialog_)
		setRouteDialog_ = new SetRouteDialog;
	return setRouteDialog_;
}
