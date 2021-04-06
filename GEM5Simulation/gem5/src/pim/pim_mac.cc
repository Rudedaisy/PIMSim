#include "pim/pim_mac.hh"

PIMMAC::PIMMAC(const PIMMAC::Params *p):
PIMKernel(p)
{

}

PIMKernel::dataType
PIMMAC::doCompute(){
	computing_counts++;
	return (dataType)(data[0]*data[1] + data[2]);
}

PIMMAC *
PIMMACParams::create()
{
    return new PIMMAC(this);
}

