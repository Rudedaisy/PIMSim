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

	int n = 0;
	//int e = 0;
	
	//struct glob *ptrs = (struct glob*)data[0];
	//float* p_new = (float*)data[2];
	//int* row_ptr = (int*)data[1];

	// data[0]: 2 if data[1] contains n, data[2] contains e
	// data[0]: 1 if contains end of vector (eov)
	if((int)data[0] == 2) {
	  n = (int)data[1];
	  //e = (int)data[2];
	  _op_latency = 1;
	}
	else if((int)data[0] == 1){
	  printf("data[2] = %f\n", (float)data[2]);
	  for(i=0; i<n; i++){
	    rowel = (int)(n/2);
	    for (j=0; j<rowel; j++) {
	      curcol++;
	      totMACs++;
	    }
	  }
	  
	  _op_latency =_latency;
          totalEnergy += static_cast<double>(_computeEnergy * totMACs * 1000000000000);
	}
        else{
          _op_latency =	1;
	}

	//int n = (int)data[0];
	
	//p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p[i];
	//for(i=0; i<n; i++){
	  //rowel = row_ptr[i+1] - row_ptr[i];
	  //rowel = 50;
	  //for (j=0; j<rowel; j++) {
	    //p_new[ptrs->col_ind[curcol]] = p_new[ptrs->col_ind[curcol]] + ptrs->val[curcol] * ptrs->p[i];
	    //curcol++;
	    //totMACs++;
	//}
	//}

	return (dataType)(data[2]) + (dataType)(data[1]);
	//return (dataType)(p_new);
}

PIMPR *
PIMPRParams::create()
{
    return new PIMPR(this);
}

