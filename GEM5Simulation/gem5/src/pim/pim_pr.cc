#include "pim/pim_mac.hh"

PIMPR::PIMPR(const PIMPR::Params *p):
PIMKernel(p)
{

}

PIMKernel::dataType
PIMPR::doCompute(){
	computing_counts++;

	int rowel = 0;
	int curcol = 0;

	// Page rank modified algorithm
	// data[0]: p
	// data[1]: val
	// data[2]: p_new
	// ?? : row_ptr
	// ?? : n
	for(i=0; i<n; i++){
	  rowel = row_ptr[i+1] - row_ptr[i];
	  for (j=0; j<rowel; j++) {
	    data[2][col_ind[curcol]] = data[2][col_ind[curcol]] + data[1][curcol] * data[0][i];
	    curcol++;
	  }
	}
	
	return (dataType)(data[2]);
}

PIMPR *
PIMPRParams::create()
{
    return new PIMPR(this);
}

