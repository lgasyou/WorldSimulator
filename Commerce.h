#ifndef COMMERCE_H
#define COMMERCE_H

#include "buildingbase.h"

class Commerce : public BuildingBase {
public:
	Commerce(const QString & = "Commerce");

	Commerce(const BuildingBase &, const QString &);

	~Commerce();

	// manual manage building
	void manage(const QString &cmd) override;

	// update data after each turn
	void update() override;
};

#endif // COMMERCE_H