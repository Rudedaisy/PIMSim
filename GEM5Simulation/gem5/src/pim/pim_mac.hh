#ifndef __PIM_MAC__
#define __PIM_MAC__

#include "pim_kernel.hh"
#include "params/PIMMAC.hh"

class PIMMAC : public PIMKernel
{
public:
    
    typedef PIMMACParams Params;
    PIMMAC(const Params *p);
    virtual dataType doCompute() override;

};


#endif
