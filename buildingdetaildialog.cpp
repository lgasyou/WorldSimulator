#include "buildingdetaildialog.h"
#include "basebuilding.h"
#include "baseindustry.h"
#include "company.h"
#include "factory.h"
#include "gameconstants.h"
#include "garage.h"
#include "goods.h"
#include "goodscontainer.h"
#include "machine.h"
#include "mine.h"

#include "buildingmanager.h"
#include "companymanager.h"
#include "industrychainmanager.h"
#include "machinemanager.h"

#include "defaultmachinebuilder.h"

#include "garagetablewidget.h"
#include "warehousetablewidget.h"
#include "ui_buildingdetaildialog.h"

BuildingDetailDialog::BuildingDetailDialog(QWidget *parent) :
	QDialog(parent),
    building_(nullptr),
	selectMachine_(nullptr),
    ui(new Ui::BuildingDetailDialog)
{
    ui->setupUi(this);

	signalSlotConfig();

	ui->expandStackedWidget->hide();
}

BuildingDetailDialog::~BuildingDetailDialog() {
    delete ui;
}

void BuildingDetailDialog::updateDisplay() {
	// Returns if this window isn't showing.
    if (this->isHidden() || !building_)	return;

	const QString &name = building_->name();
	const QString &value = toString(building_->value());
	const QString &type = building_->type();
	const QString &owner = building_->owner()->name();
	const QString &position = building_->position().toString();
	setWindowTitle(name);
	ui->nameLabel->setText(tr("Name:  ") + name);
	ui->valueLabel->setText(tr("Value: $") + value);
	ui->typeLabel->setText(tr("Type:  ") + type);
	ui->ownerLabel->setText(tr("Owner: ") + owner);
	ui->positionLabel->setText(tr("Position: ") + position);

	if (ui->machinePage->isVisible()) {
		updateMachineDetail(selectMachine_);
	}

	displayAccordingToBuildingType();
}

void BuildingDetailDialog::closeEvent(QCloseEvent *) {
	ui->expandStackedWidget->hide();
}

//void BuildingDetailDialog::deliverGoods(const Goods &goods, BaseIndustry *dest) {
//	BaseIndustry *industry = dynamic_cast<BaseIndustry *>(building_);
//	industry->deliverGoods(goods, dest);
//	emit dataChanged();
//}

void BuildingDetailDialog::addNewMachine() {
	auto industryType = BuildingManager::stringToEnum(building_->type());
	switch (industryType) {
	case GameConstants::Factory: {
		Factory *factory = dynamic_cast<Factory *>(building_);

		MachineBuilder *builder = new DefaultMachineBuilder;
		Machine *machine = MachineManager::instance().machine(builder);
		machine->setWarehouse(factory->warehouse());
		factory->addMachine(machine);
		delete builder;

		emit dataChanged();
		break;
	}

	case GameConstants::Mine: {
		Mine *mine = dynamic_cast<Mine *>(building_);

		MachineBuilder *builder = new DefaultMachineBuilder;
		Machine *machine = MachineManager::instance().machine(builder);
		machine->setWarehouse(mine->warehouse());
		mine->addMachine(machine);
		delete builder;

		emit dataChanged();
		break;
	}

	default:
		break;
	}

}

void BuildingDetailDialog::addNewVihicle() {
	Garage *garage = dynamic_cast<Garage *>(building_);
	garage->addNewVihicle("Truck");
	emit dataChanged();
}

void BuildingDetailDialog::setNextMachineProduct(const QString &product) {
	selectMachine_->setCurrentProduct(product);
	emit dataChanged();
}

void BuildingDetailDialog::showMachineDetail(Machine *machine) {
	ui->expandStackedWidget->show();
	selectMachine_ = machine;

	for (const auto &product : machine->products()) {
		ui->selectNextProductComboBox->addItem(product.name);
	}

	updateMachineDetail(machine);
}

void BuildingDetailDialog::updateMachineDetail(Machine *machine) {
	const QString &machineCurrentProductivity = toString(machine->currentProductivity());
	ui->machineCurrentProductivity->setText("Current Productivity: " + machineCurrentProductivity);

	const QString &machineMaximumProductivity = toString(machine->maximalProductivity());
	ui->machineMaximumProductivity->setText("Maximum Productivity: " + machineMaximumProductivity);
}

void BuildingDetailDialog::receiveCommand(int command) {
	emit sendCommand(command, building_);
	emit dataChanged();
}

void BuildingDetailDialog::displayAccordingToBuildingType() {
	bool isVisitorOwner = (building_->owner() == CompanyManager::instance().playerCompany());
	ui->basicOperationStackedWidget->setCurrentIndex(isVisitorOwner);

	const QString &type = building_->type();
	auto buildingType = BuildingManager::stringToEnum(type);
	ui->detailStackedWidget->setCurrentIndex(buildingType);
	switch (buildingType) {
	case GameConstants::Bank:
		break;

	case GameConstants::Factory:
		ui->factoryTableWidget->setIndustry(building_);
		ui->factoryTableWidget->updateDisplay();
		break;

	case GameConstants::Farm:
		break;

	case GameConstants::Garage: {
		Garage *garage = dynamic_cast<Garage *>(building_);
		const QString &freeVicleCount = QString::number(garage->freeVihicleCount());
		const QString &vihicleCount = QString::number(garage->vihicleCount());
		const QString &text = QString("%1 / %2 Truck Free").arg(freeVicleCount, vihicleCount);
		ui->garageStateLabel->setText(text);

		ui->garageTableWidget->setGarage(building_);
		ui->garageTableWidget->updateDisplay();
		break;
	}

	case GameConstants::Mine: {
		Mine *mine = dynamic_cast<Mine *>(building_);
		const QString &typeText = QString("Type:  %1 Mine").arg(mine->resource());
		ui->typeLabel->setText(typeText);

		ui->mineTableWidget->setIndustry(building_);
		ui->mineTableWidget->updateDisplay();
		break;
	}

	case GameConstants::Supermarket:
		break;

	case GameConstants::UnusedLand:
		break;

	case GameConstants::Villa:
		break;

	default:
		break;
	}
}

void BuildingDetailDialog::signalSlotConfig() {
	using namespace GameConstants;

	/* ---------------------------------- Basic Config ---------------------------------------------- */
	connect(ui->buyPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buyPushButton->setCommand(Commands::BuyBuilding);

	connect(ui->sellPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->sellPushButton->setCommand(Commands::SellBuilding);

	connect(ui->dismantlePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->dismantlePushButton->setCommand(Commands::DismantleBuilding);
	/* ---------------------------------------------------------------------------------------------- */

	/* ----------------------------------- Bank Config ---------------------------------------------- */
	connect(ui->closeAnAccountPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->closeAnAccountPushButton->setCommand(Commands::CloseAnAccount);

	connect(ui->depositPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->depositPushButton->setCommand(Commands::Deposit);

	connect(ui->loanPushButton,							SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->loanPushButton->setCommand(Commands::Loan);

	connect(ui->openAnAccountPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->openAnAccountPushButton->setCommand(Commands::OpenAnAccount);

	connect(ui->repayPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->repayPushButton->setCommand(Commands::Repay);

	connect(ui->withdrawPushButton,						SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->withdrawPushButton->setCommand(Commands::Withdraw);
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Garage Config --------------------------------------------- */
	connect(ui->purchaseNewVihiclePushButton,			SIGNAL(clicked()),
			this,										SLOT(addNewVihicle()));
	/* ---------------------------------------------------------------------------------------------- */

	/* --------------------------------- Industry Config -------------------------------------------- */
	connect(ui->purchaseNewMachineInFactoryPushButton,	SIGNAL(clicked()),
			this,										SLOT(addNewMachine()));
	connect(ui->purchaseNewMachineInMinePushButton,		SIGNAL(clicked()),
			this,										SLOT(addNewMachine()));

	connect(ui->factoryTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));
	connect(ui->mineTableWidget,						SIGNAL(sendSelectedMachine(Machine *)),
			this,										SLOT(showMachineDetail(Machine *)));

	connect(ui->selectNextProductComboBox,				SIGNAL(currentIndexChanged(const QString &)),
			this,										SLOT(setNextMachineProduct(const QString &)));
	/* ---------------------------------------------------------------------------------------------- */

	/* -------------------------------- UnusedLand Config ------------------------------------------- */
	connect(ui->buildBankPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildBankPushButton->setCommand(Commands::BuildBank);

	connect(ui->buildFactoryPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildFactoryPushButton->setCommand(Commands::BuildFactory);

	connect(ui->buildFarmPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildFarmPushButton->setCommand(Commands::BuildFarm);

	connect(ui->buildGaragePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildGaragePushButton->setCommand(Commands::BuildGarage);

	connect(ui->buildMinePushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildMinePushButton->setCommand(Commands::BuildMine);

	connect(ui->buildSupermarketPushButton,				SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildSupermarketPushButton->setCommand(Commands::BuildSupermarket);

	connect(ui->buildVillaPushButton,					SIGNAL(sendCommand(int)),
			this,										SLOT(receiveCommand(int)));
	ui->buildVillaPushButton->setCommand(Commands::BuildVilla);
	/* ---------------------------------------------------------------------------------------------- */

	/* ---------------------------------- Display Config -------------------------------------------- */
	connect(this,										SIGNAL(dataChanged()),
			this,										SLOT(updateDisplay()));
	/* ---------------------------------------------------------------------------------------------- */
}

QString BuildingDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}
