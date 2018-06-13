//Rishabh Agarwal  ECE 223
// lab6

#include <unistd.h>
#include <stdlib.h>
#include "Dijkstras.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define unreachable 87654


int main(int argc, char *argv[])
 {
 clock_t start_clock,end_clock_clock;
 
int Verbose=FALSE; 
double time_taken =0.0;
int num_vertices=7;
int destinationvertex=0;
int Seed = 1234567; 
int approx_vertices=5; 
int graph_operation=1;
int sourcevertex=0;
int graph_type=1;
int d=0;
while((d=getopt(argc,argv,"g:v:n:a:h:s:d:r:"))!= -1)
    {
            switch(d)
                {
                     case 'n':
                      num_vertices= atoi(optarg);
                     break;
                     
                       case 'a':
                     approx_vertices = atoi(optarg);
                     break;

                    case 'g':
                    graph_type = atoi(optarg);
                     break;
                     
                     case 'v':
                     Verbose = TRUE;
                     break;
                     
                       case 'h':
                      graph_operation = atoi(optarg);
                     break;
                     
                       case 's':
                      sourcevertex= atoi(optarg);
                     break;
                     
                       case 'd':
                      destinationvertex= atoi(optarg);
                     break;
                     
                      case 'r':
                      Seed = atoi(optarg);
                       break;
                     
                     default : 
                     break;
                 }
}
srand48(Seed);
home importa_node;

construct(&importa_node,graph_type,num_vertices,0);

dijkstras_graph(&importa_node, approx_vertices,num_vertices,graph_type,0);

if(Verbose==TRUE)
{
graph_display(&importa_node,num_vertices,0);
}
	
if(graph_type ==1)
  {
	if(graph_operation !=2 && graph_operation ==1 )
	{
	  short_path(&importa_node,sourcevertex,0);
		if(importa_node.node_length[destinationvertex] == 0 && importa_node.node_length[destinationvertex] == unreachable)
		{
		printf("path does not exist between these vertices\n");	
		}
		else
		{
		printf("shortest node_length between (%d,%d)= %g\n",sourcevertex,destinationvertex,importa_node.node_length[destinationvertex]);
			graph_display_full(&importa_node,destinationvertex,0);
		
		}
	}
 
	
	else if(graph_operation !=1 && graph_operation == 2)
	{
	longest_path(&importa_node,num_vertices,0);
	int yy=0;
        while(yy<10)
        {
        yy++;
        }

	}
	
	else
	printf("\nenter again\n");
  }  


else if(graph_type ==3 )
  {	  
	if(graph_operation !=2 && graph_operation ==1)
	{
	start_clock = clock();
	short_path(&importa_node,sourcevertex,0);
	end_clock_clock=clock();
	time_taken=1000.0 * ((double) (end_clock_clock-start_clock))/CLOCKS_PER_SEC;
		if(importa_node.node_length[destinationvertex] ==0 && importa_node.node_length[destinationvertex] ==unreachable)
		{
		printf("path does not exist between these vertices\n");
		printf("\n time taken %f ",time_taken);
		}
		else
		{

		printf("shortest node_length between (%d,%d)= %g\n",sourcevertex,destinationvertex,importa_node.node_length[destinationvertex]);
			graph_display_full(&importa_node,destinationvertex,0);
			printf("\n time taken %f ",time_taken);
		}
	}

	
	else if(graph_operation !=1 && graph_operation ==2)
	{
	longest_path(&importa_node,num_vertices,0);
	int yy=0;
        while(yy<10)
        {
        yy++;
        }
	}
	

	else
	printf("\nenter again\n");
  }
else if(graph_type == 2)
  {	  
	if(graph_operation !=2 && graph_operation ==1)
	{
	start_clock = clock();
	short_path(&importa_node,sourcevertex,0);
 	end_clock_clock=clock();
 	
	time_taken=1000 *((double) (end_clock_clock-start_clock))/CLOCKS_PER_SEC;

		if(importa_node.node_length[destinationvertex] == 0 && importa_node.node_length[destinationvertex] == unreachable)
		{
		printf("path does not exist between these verticess\n");
		printf("\n time taken  : %f ",time_taken);
		}
		else
		{
		printf("shortest vertex_length between (%d,%d)= %g\n",sourcevertex,destinationvertex,importa_node.node_length[destinationvertex]);
			graph_display_full(&importa_node,destinationvertex,0);
			printf("\n time taken  : %f ",time_taken);
		}
	
	}

	else if(graph_operation !=1 && graph_operation ==2)
	{
	longest_path(&importa_node,num_vertices,0);
	int yy=0;
        while(yy<10)
        {
        yy++;
        }

	}
	
	else
	printf("\nenter again\n");
  }
destruct(&importa_node);
printf("\n");
printf("********End***********");
printf("\n");
exit(-1);

}
