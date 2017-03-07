# ifndef PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_

# include "netxpto.h"

# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "electrical_filter.h"
# include "sampler.h"
# include "bit_decider.h"


// Balanced Homodyne Receiver superblock
class I_HomodyneReceiver : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	TimeContinuousAmplitudeContinuousReal I_HMD01{ "I_HMD01.sgn" }; // Detected and Subtracted -> 4*S*LO

	TimeContinuousAmplitudeContinuousReal I_HMD02{ "I_HMD02.sgn" }; // Amplified, Noisy and Filtered


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	Photodiode B1;

	TI_Amplifier B2;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

	double localOscillatorOpticalPower{ 1e-3 };
	double localOscillatorPhase{ 0 };
	double localOscillatorWavelength{ 1550e-9 };

	int samplesToSkip{ 0 };

	double outputOpticalFrequency{ SPEED_OF_LIGHT / localOscillatorWavelength };

public:

	/* Methods */

	I_HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	/*void setLocalOscillatorSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };
	void setLocalOscillatorSymbolPeriod(double sPeriod) { B1.setSymbolPeriod(sPeriod); }
	void setLocalOscillatorOpticalPower(double opticalPower) { B1.setOpticalPower(opticalPower); };
	void setLocalOscillatorOpticalPower_dBm(double opticalPower_dBm) { B1.setOpticalPower_dBm(opticalPower_dBm); };
	void setLocalOscillatorPhase(double lOscillatorPhase) { B1.setPhase(lOscillatorPhase); };
	double const getLocalOscillatorPhase(void) { B1.getPhase(); }
	void setLocalOscillatorOpticalWavelength(double lOscillatorWavelength) { B1.setWavelength(lOscillatorWavelength); };

	void setSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { B2.matrix = TransferMatrix; };
	array<complex<double>, 4> const getBalancedBeamsplitter(void) { B2.getTransferMatrix(); }
*/
	void setResponsivity(double Responsivity) { B1.setResponsivity(Responsivity); };
	double const getResponsivity(void) { B1.getResponsivity(); }
	void useShotNoise(bool uShotNoise){ B1.useNoise(uShotNoise); };

	void setGain(double Gain) { B2.setGain(Gain); }

	void setElectricalNoiseSpectralDensity(double eNoiseSpectralDensity) { B2.setElectricalNoiseSpectralDensity(eNoiseSpectralDensity); }
	double const getElectricalNoiseSpectralDensity(void) { B2.getElectricalNoiseSpectralDensity(); }

};

#endif
