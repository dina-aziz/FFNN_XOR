#include<iostream>
#include<ctime>
using namespace std;

float randomizeAround(float n)  // returns a random number around the argument n (the number may be multiplied by -1)
{
	int sign=rand()%2;
	int addSub=rand()%2;
	int r=rand()%30;
	float range=float(r);
	range/=100;
	if(addSub==0) n+=range;
	else n-=range;
	if(sign==0) return n;
	else return -1*n;
}


class logisticNeuron    // this class represents a neuron
{
private:
	float * weights; 
	float output;
public:
	logisticNeuron()
	{
		//cout<<"\n creating neuron..";
	}
	logisticNeuron(int numOfLinks,float initialWeight)
	{
		weights=new float[numOfLinks+1];
		for(int j=0;j<numOfLinks+1;j++) weights[j]=randomizeAround(initialWeight); // initialize every weight with a number around: initialWeight
		//cout<<"\n creating neuron..";
	}
	void activate(float input[],int size,char da='a') // takes an array of inputs given to a neuron and returns the result of the activation function
	{
		if(da=='a')
		{
			float net=0;
			for(int j=0;j<size;j++) net+=input[j]*weights[j];
			  output=(2/(1+pow(2.718f,-1*net)))-1;                 // bipolar
			//output=1/(1+pow(2.718f,-1*net));                 //unipolar 
		}  
		else if(da=='d') output=-1;
	}
	float getOutput(){return output;}
	void setWeight(int n,float w){weights[n]=w;}
	float getWeight(int n){return weights[n];}
	void setNeuronData(int numOfLinks,float initialWeight)   // used to specify the number of links to a neuron, and set the weights of these links
	{
		weights=new float[numOfLinks+1];
		for(int j=0;j<numOfLinks+1;j++) weights[j]=randomizeAround(initialWeight);
		//cout<<"\n setting neuron data..";
	}
};


	
logisticNeuron a3(3,0.5);
logisticNeuron a4(3,0.5);   // layer 2
logisticNeuron a5(3,0.5);
logisticNeuron a6(3,0.5);

logisticNeuron a7(5,0.5);   // layer 3

float input1[3];
float input2[5];
float output;
void propagate(float x1,float x2)
{
	input1[0]=x1;  // first layer input : real input
	input1[1]=x2;
	input1[2]=-1;
	
	
	a3.activate(input1,3);      // hidden layer input
	input2[0]=a3.getOutput();
	
	a4.activate(input1,3);
	input2[1]=a4.getOutput();
				
	a5.activate(input1,3);
	input2[2]=a5.getOutput();

	a6.activate(input1,3);
	input2[3]=a6.getOutput();
	
	input2[4]=-1;

	a7.activate(input2,5);  // output
	output=a7.getOutput();
}
int main()
{
	
	float lr=0.001;    // 0.001 with 500000 iterations is good, 0.005 with 10000 iterations is good !!
	float target;
	float error=0.0;

	float delta2;
	float delta1[4];
	
	

		
	
	srand(time(NULL));
	for(int j=0;j<500000;j++)
	{
		
		float dwb3=0;
		float dwb4=0;
		float dwb5=0;
		float dwb6=0;
		float dwb7=0;
		float dwi13=0;
		float dwi14=0;
		float dwi15=0;
		float dwi16=0;
		float dwi23=0;
		float dwi24=0;
		float dwi25=0;
		float dwi26=0;
		float dw37=0;
		float dw47=0;
		float dw57=0;
		float dw67=0;

		for(int i=0;i<4;i++)
		{
			float x1,x2;
			if(i==0)
			{ x1=-1; x2=-1;}
			if(i==1)
			{ x1=1; x2=-1;}
			if(i==2)
			{ x1=-1; x2=1;}
			if(i==3)
			{ x1=1; x2=1;}
			
			//cout<<"\nx1:  "<<x1<<"    x2: "<<x2;
			propagate((float)x1,(float)x2);
				
			if(x1==x2) target=-1.0; else target=1.0;
	        //cout<<"  Output: "<<output;
			error+=0.5*(target-output)*(target-output);

			delta2=0.5*(target-output)*(1-output*output);            // computing dE/dNet
			delta1[0]=0.5*a7.getWeight(0)*delta2*(1-input2[0]*input2[0]);
			delta1[1]=0.5*a7.getWeight(1)*delta2*(1-input2[1]*input2[1]);
			delta1[2]=0.5*a7.getWeight(2)*delta2*(1-input2[2]*input2[2]);
			delta1[3]=0.5*a7.getWeight(3)*delta2*(1-input2[3]*input2[3]);
			

			
			dwb3-=lr*delta1[0];             // delta of bias weights
			dwb4-=lr*delta1[1];
			dwb5-=lr*delta1[2];
			dwb6=-lr*delta1[3];
			dwb7-=lr*delta2;
			                              
			                               // delta of 1st layer weights
			dwi13+=lr*delta1[0]*input1[0];      
			dwi14+=lr*delta1[1]*input1[0];
			dwi15+=lr*delta1[2]*input1[0];      
			dwi16+=lr*delta1[3]*input1[0];
			dwi23+=lr*delta1[0]*input1[1];      
			dwi24+=lr*delta1[1]*input1[1];
			dwi25+=lr*delta1[2]*input1[1];      
			dwi26+=lr*delta1[3]*input1[1];
			
			                                    // delta of 2nd layer weights	
			dw37+=lr*delta2*input2[0];       
			dw47+=lr*delta2*input2[1];          
			dw57+=lr*delta2*input2[2];
			dw67+=lr*delta2*input2[3];
		}

		                                      // update bias
		
		a3.setWeight(2,a3.getWeight(0)+dwb3);			
		a4.setWeight(2,a4.getWeight(0)+dwb4);
		a5.setWeight(2,a5.getWeight(0)+dwb5);
		a6.setWeight(2,a6.getWeight(0)+dwb6);
		a7.setWeight(4,a7.getWeight(0)+dwb7);

		
		a3.setWeight(0,a3.getWeight(0)+dwi13);
		a3.setWeight(1,a3.getWeight(1)+dwi23);
		a4.setWeight(0,a4.getWeight(0)+dwi14);
		a4.setWeight(1,a4.getWeight(1)+dwi24);
		a5.setWeight(0,a5.getWeight(0)+dwi15);
		a5.setWeight(1,a5.getWeight(1)+dwi25);
		a6.setWeight(0,a6.getWeight(0)+dwi16);
		a6.setWeight(1,a6.getWeight(1)+dwi26);
		a7.setWeight(0,a7.getWeight(0)+dw37);
		a7.setWeight(1,a7.getWeight(1)+dw47);
		a7.setWeight(2,a7.getWeight(2)+dw57);
		a7.setWeight(3,a7.getWeight(3)+dw67);
		

	}
	propagate(1.0,1.0);
	cout<<"\nx1: "<<1<<"     x2: "<<1<<"      output:"<<output;
	propagate(-1.0,-1.0);
	cout<<"\nx1: "<<-1<<"    x2: "<<-1<<"     output:"<<output;
	propagate(1.0,-1.0);
	cout<<"\nx1: "<<1<<"     x2: "<<-1<<"     output:"<<output;
	propagate(-1.0,1.0);
	cout<<"\nx1: "<<-1<<"    x2: "<<1<<"      output:"<<output<<endl<<endl;
	 
	return 0;
}
