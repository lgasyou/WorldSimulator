#ifndef BASEAGRICULTURE_H
#define BASEAGRICULTURE_H

#include "basebuilding.h"

class QString;

class BaseAgriculture : public BaseBuilding {
public:
	BaseAgriculture(const QString &name, const QString &type);

	virtual ~BaseAgriculture();

	void update() override;
};

#endif // !BASEAGRICULTURE_H
