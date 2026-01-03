/*
This CBPNN class is created by Vincent Gao(c_gao), 2009-10-31.
You can use it for any purposes as you want, but you must keep
this comment in these files. If you have any problems, please
contact me at:

e-mail:    dr.c.gao@gmail.com
homepage:  http://vgao.ddns.net

This class can create a three lays BackPropogation Neural
Network. Call InitBPNN() to create a network, and call Train()
to train the network.
*/

#pragma once

#include <vector>
#include <string>

#define DEFAULT_ETA			0.05		// default learning rate
#define DEFAULT_MOMENTUM	0			// default momentum


#define BPNN_SAVEFILE_FLAG			"BPNN"	// BPNN file ID
#define BPNN_SAVEFILE_SEPCHAR		'\n'	// File delimitor

#define ABS(x)	(x)>0?(x):(-(x))

typedef std::vector<std::pair<std::string,std::vector<double> > >	target_type;

class CBPNN
{
public:
	CBPNN(void);
	~CBPNN(void);
public:
	bool InitBPNN(int nInput,int nOutput,int nHidden);
	bool LoadInputUnit(const double* data,int count,double scale);
	bool LoadTarget(const double* data,int count,double scale=1.0);
	double Train(double eta,double momentum);
	void Test(const double* data,int nDimentions,double scale,std::vector<double>& vecOutput);
	const double* GetOutput();
	bool SaveBPNNFile(const char* sSavePath,const char* sTargetName,int nIterateTime,double fStopError,target_type* pvecTarget=NULL);
	bool LoadBPNNFile(const char* sSavePath,target_type* pvecTarget);
protected:
	void ReleaseBPNN();
	double Sigmoid(double x); // Activation function
	void LayerForward();
	double OutputError();
	double HiddenError();
	void AdjustWeights();
protected:
	int m_nInput;
	int m_nOutput;
	int m_nHidden;

	double* m_InputUnit;
	double* m_HiddenUnit;
	double* m_OutputUnit;

    // As shown below, first save the weights of the O1, then save the weights of O2; the same applies to the upper layer, i.e., node o.
    //       output layer      o
    //                        / \
    //       hidden layer   o1  o2
    //       	           /|\
    //       input layer  o o o
    // The bottom layer is the input layer, and the top layer is the output layer; that is, the network flows from bottom to top.

	double* m_I2HWeight;

	double* m_H2OWeight;

	double* m_preI2HWeight;
	double* m_preH2OWeight;

	double* m_OutputError;
	double* m_HiddenError;

	double* m_Target;

	double m_eta;//learning rate
	double m_momentum;//momentum for updating the weight
};
