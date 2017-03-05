#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class BaseBuilding;

class MyPushButton;
class BuildingDetailDialog;
class BuildingTableWidget;
class CompanyDetailDialog;
class HelpDialog;
class QString;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

	enum OrderTypes {
		Buy,
		Build,
		Dismantle,
		Details,
		Sell
	};

	static OrderTypes stringToEnum(const QString &type);

	void init();

signals:
    void dataChanged();

	void sendSelectedBuilding(BaseBuilding *);

private slots:
	// Calls function update() of every variable objects.
    void endTurns();

	void showBuildingTableWidget();

    void showCompanyDetail();

	void showHelp();

	void getBuildingByPos(int x, int y);

    void updateDisplay();

	void processOrders(const QString &order, BaseBuilding *);

private:
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	static QString toString(double value);

	void signalSlotConfig();

private:
    Company *playerCompany_;

	BuildingDetailDialog *buildingDetailDialog_;

	BuildingTableWidget *buildingInfoList_;

	CompanyDetailDialog *companyDetailDialog_;

	HelpDialog *helpDialog_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
