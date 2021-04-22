#ifndef __PIM_PR__
#define __PIM_PR__

#include "pim_kernel.hh"
#include "params/PIMPR.hh"

class PIMPR : public PIMKernel
{
public:
    
    typedef PIMPRParams Params;
    int n = 500;
    PIMPR(const Params *p);
    virtual dataType doCompute() override;

};


#endif
