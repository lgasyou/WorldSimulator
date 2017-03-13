#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include <QString>

class Warehouse;
struct Goods;

class Machine {
public:
	Machine();

	~Machine();

	void init();

	double currentProductivity() const { return this->currentProductivity_; }

	void produce();

	void setMaximalProductivity(double maximalProductivity);
	double maximalProductivity() const { return this->maximalProductivity_; }

	void setCurrentProduct(const QString &product);
	const QString &currentProduct() const { return this->currentProduct_; }

	void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

	void setProducts(const std::vector<Goods> &products);
	const std::vector<Goods> &products() const { return this->products_; }

	const std::vector<Goods> &materials() const { return this->materials_; }

private:
	double currentProductivity_;

	double maximalProductivity_;

	QString currentProduct_;

	Warehouse *warehouse_;

	std::vector<Goods> products_;

	std::vector<Goods> materials_;
};

#endif // !MACHINE_H
