# ifndef PROGRAM_INCLUDE_RF_OSCILLATOR_H_
# define PROGRAM_INCLUDE_RF_OSCILLATOR_H_


# include "netxpto.h"
# include <complex>
# include <random>
# include <vector>

class RfOscillator : public Block {

	/* Input Parameters */

	double rfAmplitude{ 1.0 };				
	double rfInitialPhase{ 0.0 };
	double rfFrequency{ 100E6 };
	double samplingPeriod{ 1.0 };

	
	/* State Variables */
	double phase{ rfInitialPhase };

public:

	/* Methods */
	RfOscillator() {};
	RfOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) : Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }					// 
	double getSamplingPeriod() { return samplingPeriod; }

	void setrfAmplitude(double rfAmpl) { rfAmplitude = rfAmpl; }							// Set Amplitude of the RF Oscillator
	double getRfAmplitude() { return rfAmplitude; }

	void setrfFrequency(double rfFreq) { rfFrequency = rfFreq; }							// Set Frequency of the RF Oscillator
	double getrfFrequency() { return rfFrequency; }

	void setrfPhase(double rfPh) { rfInitialPhase = rfPh; }									// Set Phase     of the RF Oscillator
	double getRfPhase() { return rfInitialPhase; }
	
};

#endif 