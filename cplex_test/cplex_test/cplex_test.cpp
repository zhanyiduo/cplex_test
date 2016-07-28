//testing git 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include "ilcplex\cplex.h"
#include "ilcplex\ilocplex.h"
#include "math.h"
ILOSTLBEGIN

using namespace std;

void cplexeg();

void main()
{
	cplexeg();
	cin.get();
}

void cplexeg()
{
	int i,j;
	char temp[80];
	IloEnv env;
	try 
   {
	   IloModel model(env);  //create model
	   //==========create variables====================//
	   IloNumVarArray x(env,3,0,IloInfinity,ILOFLOAT);
	   IloNumVar y(env,0,1,ILOINT);
	   //============objective function================//
	   IloExpr sum(env);
	   for(i=0;i<3;i++)
	   {
		   sum+=x[i];
	   }
	   sum+=y;
	   model.add(IloMinimize(env,sum));
	   sum.end();

	   //=============add constraint====================//
	   sprintf(temp,"contraint 1");
		model.add(IloRange(env,20,5*x[0]+6*x[1],IloInfinity,temp));//5x1+6x2>=20
		sprintf(temp,"contraint 2");
		model.add(IloRange(env,4,x[1]+x[2],IloInfinity,temp));//x2+x3>=4
		sprintf(temp,"contraint 3");
		model.add(IloRange(env,9,x[0]+3*x[2],IloInfinity,temp));//x1+3x3>=9

	//==============solve============================//
		IloCplex cplex(model);
		cplex.exportModel("cplex_test.lp");
	//==============setting================//
        cplex.setParam(IloCplex::EpOpt, 1e-6);//set solver gap
		cplex.setParam(IloCplex::EpGap, 1e-6);//set MIP gap
		cplex.setParam(IloCplex::TiLim,5000);//set time limit
		cplex.extract(model);
		cplex.solve();
//===============================================  

	  if((cplex.getStatus() == IloAlgorithm::Infeasible ) || 
		(cplex.getStatus() == IloAlgorithm::InfeasibleOrUnbounded)) {
			cout << "Infeasible" <<endl;
			cplex.end();
			throw(-1);
		}
		else if(cplex.getStatus() == IloAlgorithm::Optimal){
		}
//===============get result===========================//
	double opt, x_opt[3],y_opt;
	opt=cplex.getObjValue();
	for(i=0;i<3;i++)
	{
		x_opt[i]=cplex.getValue(x[i]);
	}
	y_opt=cplex.getValue(y);

//============display================================//
	  cout<<"================Optimal============="<<endl;
      cout << "Solution status = " << cplex.getStatus() << endl;
	  cout<<"Number of Constraints = "<<cplex.getNrows()<<endl;
	  cout<< "Optimal value  = " << opt << endl;
	  cout<<"x="<<endl;
	  for(i=0;i<3;i++)
		{
			cout<<x_opt[i]<<",\t";
		}
	  cout<<endl;
	  cout<<"y=  "<<y_opt<<endl;

	 sprintf(temp,"result.txt");
	FILE * tempfile;
    tempfile = fopen(temp, "w");

	fclose(tempfile);
    fstream fout(temp, fstream::in | fstream::out);

	fout<<"Optimal value  = " << opt << endl;
	fout<<"Number of Constraints = "<<cplex.getNrows()<<endl;
	  fout<<"x="<<endl;
	  for(i=0;i<3;i++)
		{
			fout<<x_opt[i]<<",\t";
		}
	  fout<<endl;
	  fout<<"y=  "<<y_opt<<endl;
	}//END try

   catch (IloException& e) 
   {
      cerr << "Concert exception caught: " << e << endl;
   }

   catch (...) 
   {
      cerr << "Unknown exception caught" << endl;
   }
}