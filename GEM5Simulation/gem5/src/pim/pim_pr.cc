#include "pim/pim_pr.hh"

struct glob{
  float* p;
  float* val;
  int* row_ptr;
  int* col_ind;
  int n;
};

PIMPR::PIMPR(const PIMPR::Params *p):
PIMKernel(p)
{

}

PIMKernel::dataType
PIMPR::doCompute(){
	computing_counts++;

	int rowel = 0;
	int curcol = 0;
	int totMACs = 0;
	int i = 0;
	int j = 0;

	// Page rank modified algorithm
	// data[0]: ptrs (struct)
	//          ptrs.p
	//          ptrs.val
	//          ptrs.row_ptr
	//          ptrs.col_ind
	//          ptrs.n
	// data[1]: p_new
	// data[2]: p_new

	struct glob *ptrs = (struct glob*)&data[0];
	float* p_new = (float*)&data[2];
	
	//p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p[i];
	for(i=0; i<ptrs->n; i++){
	  rowel = ptrs->row_ptr[i+1] - ptrs->row_ptr[i];
	  for (j=0; j<rowel; j++) {
	    p_new[ptrs->col_ind[curcol]] = p_new[ptrs->col_ind[curcol]] + ptrs->val[curcol] * ptrs->p[i];
	    curcol++;
	    totMACs++;
	  }
	}

	_op_latency =_latency * totMACs;
	totalEnergy += static_cast<double>(_computeEnergy * totMACs * 1000000000000);
	
	//return (dataType)(data[2]);
	return (dataType)(p_new);
}

PIMPR *
PIMPRParams::create()
{
    return new PIMPR(this);
}

