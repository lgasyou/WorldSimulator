#include "WarehouseTableWidget.h"
#include "Warehouse.h"
#include <map>

WarehouseTableWidget::WarehouseTableWidget(QWidget *parent, Warehouse *warehouse) :
	QTableWidget(parent),
	warehouse_(warehouse)
{ 
	this->setColumnCount(3);
	QStringList header{ tr("Item"), tr("Weight"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

void WarehouseTableWidget::updateDisplay() {
	const QMap<QString, double> &warehouse = warehouse_->warehouse();
	this->setRowCount(warehouse.size());

	unsigned int i = 0;
	for (auto &iter = warehouse.constBegin(); iter != warehouse.constEnd(); ++iter, ++i) {
		this->setItem(i, 0, new QTableWidgetItem(iter.key()));
		this->setItem(i, 1, new QTableWidgetItem(toString(iter.value())));
	}
}

QString WarehouseTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}