#include "mainwindow.h"
#include "buildingmanager.h"
#include "companymanager.h"
#include "timemanager.h"
#include "company.h"
#include "bankdialog.h"
#include "buildingdetaildialog.h"
#include "buildinginfotablewidget.h"
#include "companydetaildialog.h"

#include "mypushbutton.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    bankDialog_(nullptr),
    buildingDetailDialog_(nullptr),
    buildingInfoTableWidget_(new BuildingInfoTableWidget(this)),
    companyDetailDialog_(nullptr),
    ui(new Ui::MainWindow)
{
	init();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
	ui->setupUi(this);
	ui->BuildingInfoTableWidget->addWidget(buildingInfoTableWidget_);
	setWindowTitle(tr("Building Value Simulator"));

	playerCompany_ = CompanyManager::instance().playerCompany();

	buildingInfoTableWidget_->setCompany(playerCompany_);

	connect(ui->pushButton_EndTurn, SIGNAL(clicked(bool)),
		this, SLOT(endTurns()));
	connect(ui->pushButton_Bank, SIGNAL(clicked(bool)),
		this, SLOT(goBank()));
	connect(ui->pushButton_Company, SIGNAL(clicked(bool)),
		this, SLOT(showCompanyDetail()));

	connect(buildingInfoTableWidget_, SIGNAL(buySignal(BaseBuilding*)),
		this, SLOT(buy(BaseBuilding*)));
	connect(buildingInfoTableWidget_, SIGNAL(sellSignal(BaseBuilding*)),
		this, SLOT(sell(BaseBuilding*)));
	connect(buildingInfoTableWidget_, SIGNAL(showDetailSignal(BaseBuilding*)),
		this, SLOT(showBuildingDetail(BaseBuilding*)));

	connect(this, SIGNAL(dataChanged()),
		this, SLOT(updateDisplay()));

	updateDisplay();
}

void MainWindow::goBank() {
    if (!bankDialog_)
        bankDialog_ = new BankDialog(this, playerCompany_);
    bankDialog_->updateDisplay();
    if (bankDialog_->exec() == QDialog::Accepted) {
        updateStatusBar("Back.");
        emit dataChanged();
    }
}

void MainWindow::endTurns() {
	BuildingManager::instance().update();
	CompanyManager::instance().update();
	double deltaValue = BuildingManager::instance().deltaValueOfCompanyProperties(playerCompany_);
	playerCompany_->setTotalValue(playerCompany_->totalValue() + deltaValue);
    TimeManager::instance().increaseTime();
    emit dataChanged();
}

void MainWindow::showBuildingDetail(BaseBuilding *building) {
    if (!buildingDetailDialog_)
        buildingDetailDialog_ = new BuildingDetailDialog(this);
    buildingDetailDialog_->setBuilding(building);
    buildingDetailDialog_->setVisitor(playerCompany_);
	showDialog(buildingDetailDialog_);
    buildingDetailDialog_->updateDisplay();
}

void MainWindow::showCompanyDetail() {
    if (!companyDetailDialog_)
        companyDetailDialog_ = new CompanyDetailDialog(this);
    companyDetailDialog_->setCompany(playerCompany_);
	showDialog(companyDetailDialog_);
    companyDetailDialog_->updateDisplay();
}

void MainWindow::buy(BaseBuilding *building) {
    if (playerCompany_->buy(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " bought.");
    } else
        updateStatusBar("Cannot Afford it.");
}

void MainWindow::sell(BaseBuilding *building) {
    if (playerCompany_->sell(building)) {
        emit dataChanged();
        updateStatusBar(building->type()+ " " + building->name() + " sold.");
    }
}

void MainWindow::changeType(BaseBuilding *building, const QString &type) {
	BaseBuilding *newBuilding = BuildingManager::instance().resetItemType(building, type);
    buildingDetailDialog_->setBuilding(newBuilding);
    updateStatusBar(newBuilding->name() + " has been changed into " + type + ".");
    emit dataChanged();
}

void MainWindow::updateDisplay() {
    updateCompanyInfo();
    buildingInfoTableWidget_->updateDisplay();
}

void MainWindow::updateCompanyInfo() {
    ui->label_CompanyName->setText(playerCompany_->name());
    QString cash = toString(playerCompany_->cash());
    ui->label_CompanyCash->setText(tr("Cash: $") + cash);
    QString totalValue = toString(playerCompany_->totalValue());
    ui->label_CompanyTotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Turns->setText(tr("Turn ") + QString::number(TimeManager::instance().currentTime()));
}

inline void MainWindow::updateStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 5000);
}

QString MainWindow::toString(double value) {
	return QString::number(value, 10, 2);
}

void MainWindow::showDialog(QDialog *dialog) {
	dialog->show();
	dialog->raise();
	dialog->activateWindow();
}
