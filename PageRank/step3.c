
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Step Three: 
   parallization of step two
*/

int main(){
   
  /*************************** TIME, VARIABLES ***************************/

  // Keep track of the execution time
  clock_t begin, end;
  double time_spent;
  begin = clock();
  int numthreads = 4;//16;
  int granularity = 4;//8;

  /******************* OPEN FILE + NUM OF NODES/EDGES ********************/

  // Open the data set 
  //char filename[]="/root/hostCurUser/Green-Marl/data/soc-LiveJournal1.txt";
  //char filename[]="./microdataset.txt";
  char filename[]="../../PageRank/microdataset.txt";
  FILE *fp;
  if((fp=fopen(filename,"r"))==NULL) {
    fprintf(stderr,"[Error] cannot open file");
    exit(1);
  }
  
  // Read the data set and get the number of nodes (n) and edges (e)
  int n, e;
  char ch;
  char str[100];
  ch = getc(fp);
  while(ch == '#') {
    fgets(str, 100-1, fp);
    //Debug: print title of the data set
    //printf("%s",str);
    sscanf (str,"%*s %d %*s %d", &n, &e); //number of nodes
    ch = getc(fp);
  }
  ungetc(ch,fp);
  
  // DEBUG: Print the number of nodes and edges, skip everything else
  printf("\nGraph data:\n\n  Nodes: %d, Edges: %d \n\n", n, e);  
  
  /************************* CSR STRUCTURES *****************************/
    
  /* Compressed sparse row format: 
     - Val vector: contains 1.0 if an edge exists in a certain row
     - Col_ind vector: contains the column index of the corresponding value in 'val'
     - Row_ptr vector: points to the start of each row in 'col_ind'
  */

  float *val = calloc(e, sizeof(float));
  int *col_ind = calloc(e, sizeof(int));
  int *row_ptr = calloc(n+1, sizeof(int));
 
  // The first row always starts at position 0
  row_ptr[0] = 0;

  int fromnode, tonode;
  int cur_row = 0;
  int i = 0;
  int j = 0;
  // Elements for row
  int elrow = 0;
  // Cumulative numbers of elements
  int curel = 0;
  
  while(!feof(fp)){
    
    fscanf(fp,"%d%d",&fromnode,&tonode);
    
    // DEBUG: print fromnode and tonode
    //printf("From: %d To: %d\n",fromnode, tonode);
    
    if (fromnode > cur_row) { // change the row
      curel = curel + elrow;
      for (int k = cur_row + 1; k <= fromnode; k++) {
        row_ptr[k] = curel;
      }
      elrow = 0;
      cur_row = fromnode;
    }
    val[i] = 1.0;
    col_ind[i] = tonode;
    elrow++;
    i++;
  }
  row_ptr[cur_row+1] = curel + elrow - 1;

  /* DEBUG: Print vectors involved so far
  printf("\nVal vector:\n  [ ");
  for (i=0; i<e; i++){
        printf("%f ", val[i]);
      }
  printf(" ]\n");
  printf("\nCol_ind vector :\n  [ ");
  for (i=0; i<e; i++){
        printf("%d ", col_ind[i]);
      }
  printf(" ]\n");
  int size = sizeof(row_ptr) / sizeof(int);
  printf("\nrow_ptr vector (size = %d):\n  [ ", size);
  for (i=0; i< n; i++){
        printf("%d ", row_ptr[i]);
      }
  printf(" ]\n");*/


  // Fix the stochastization
  //int out_link[n];
  int* out_link = (int*) calloc(n, sizeof(int));
  //for(i=0; i<n; i++) {
  //  out_link[i] = 0;
  //}

  /* DEBUG: row pointer test
  printf("\nRow_ptr:\n");
  for (i=0; i<n; i++){
    printf("%d ", row_ptr[i]);
  }
  printf("\n");
  */

  int rowel = 0;
  for(i=0; i<n; i++){
        if (row_ptr[i+1] != 0) {
          rowel = row_ptr[i+1] - row_ptr[i];
          out_link[i] = rowel;
        }
   }

  /* DEBUG: Outlink print test
  printf("\nOutlink:\n");
  for (i=0; i<n; i++){
    printf("%d ", out_link[i]);
  }
  printf("\n");
  */
    
  int curcol = 0;
  for(i=0; i<n; i++) {
    rowel = row_ptr[i+1] - row_ptr[i];
    for (j=0; j<rowel; j++) {
      val[curcol] = val[curcol] / out_link[i];
      curcol++;
    }
  }

  free(out_link);
  
  /* DEBUG: val print test 
  for(i=0; i<e; i++){
      printf("%f ", val[i]);
  }*/

  printf("Initializing P\n");
 
  /******************* INITIALIZATION OF P, DAMPING FACTOR ************************/

  // Set the damping factor 'd'
  float d = 0.85;
  
  // Initialize p[] vector
  //float p[n];
  float* p = calloc(n, sizeof(float));
  for(i=0; i<n; i++){
    p[i] = 1.0/n;
  }
  
  // Set the looping condition and the number of iterations 'k'
  int looping = 1;
  int k = 0;
  int loopnum = 0;
  
  // Set 'parallel' depending on the number of threads
  int parallel = 0;
  if (numthreads >= 2) {
          parallel = 1;
  }

  // Initialize new p vector
  //float p_new[n];
  float* p_new = calloc(n, sizeof(float));
  
  printf("Begin pagerank loop\n");
  /*************************** PageRank LOOP  **************************/

  while (looping){

    printf("Loop %d\n", loopnum++);
    
    // Initialize p_new as a vector of n 0.0 cells
    for(i=0; i<n; i++){
      p_new[i] = 0.0;
    }
    
    int rowel = 0;
    int curcol = 0;
    int loopnum = 0;
    
    // Page rank modified algorithm + parallelization
    //#pragma omp parallel for schedule(static) if(parallel) num_threads(numthreads)
#pragma omp parallel num_threads(numthreads) private(i) private(j) private(rowel) private(curcol)
    {
      curcol = omp_get_thread_num();
      
    for(i=0; i<n; i = i + granularity){
      rowel = row_ptr[i+1] - row_ptr[i];
      for (j=0; j<rowel; j++) {
#pragma omp atomic
        p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p[i];
        //curcol++;
	curcol += granularity;
      }
    }
    printf("Hello from process: %d\n", omp_get_thread_num());
    }
    
    /*DEBUG: print pnew
    for (i=0; i<n; i++){
      printf("%f ", p_new[i]);
    }*/

    // Adjustment to manage dangling elements 
    for(i=0; i<n; i++){
      p_new[i] = d * p_new[i] + ((1.0 - d) / n);
    }

    /*DEBUG: print pnew after the damping factor multiplication
    for (i=0; i<n; i++){
      printf("%f ", p_new[i]);
    }*/
       
    // TERMINATION: check if we have to stop
    float error = 0.0;
    for(i=0; i<n; i++){
      error =  error + fabs(p_new[i] - p[i]);
    }
    //if two consecutive instances of pagerank vector are almost identical, stop
    if (error < 0.000001){
    //if (error <0.01) {
      looping = 0;
    }
    //printf("Error: %lf\n", error);
    
     // Update p[]
    for (i=0; i<n;i++){
	    	p[i] = p_new[i];
    }
    
    // Increase the number of iterations
    k = k + 1;
  }
  free(p_new);
  /*************************** CONCLUSIONS *******************************/

  // Stop the timer and compute the time spent
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  
  // Sleep a bit so stdout is not messed up
  //Sleep(500);
    
  // Print results
  printf ("\nNumber of iteration to converge: %d \n\n", k); 
  printf ("Final Pagerank values:\n\n[");
  for (i=0; i<n; i++){
    printf("%f ", p[i]);
    if(i!=(n-1)){ printf(", "); }
  }
  free(p);
  printf("]\n\nTime spent: %f seconds.\n", time_spent);
  return 0;
}
