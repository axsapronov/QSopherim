#ifndef MODELSTATIC_H
#define MODELSTATIC_H

#include "src/model/abstractmodel.h"
#include "src/model/modelstatic/module/convertermodule.h"
#include "src/model/modelstatic/module/loadermodule.h"

class ModelStatic : public AbstractModel
{
public:
    ModelStatic();


private:
    ConverterModule* m_converterModule;
    LoaderModule* m_loaderModule;

};

#endif // MODELSTATIC_H
