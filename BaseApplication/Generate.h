#include "Base.h"

class Generate : public Base
{
public:
    Generate(void);
    virtual ~Generate(void);
protected:
	virtual void createScene(void);
};