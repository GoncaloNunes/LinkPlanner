
#include "netxpto.h"
#include <stdio.h>

#include "binary_source.h"
#include "clock_20171219.h"
#include "alice_qkd.h"
#include "single_photon_source_20171218.h"
#include "polarizer.h"
#include "sink.h"
#include "bob_qkd.h"
#include "rotator_linear_polarizer.h"
#include "polarization_beam_splitter.h"
#include "single_photon_detector.h"
#include "optical_switch.h"
#include "eve_qkd.h"

int main()
{
	// #####################################################################################################
	// ################################# System Input Parameters #########################################
	// #####################################################################################################

	double RateOfPhotons{ 1e3 };
	vector<t_iqValues> iqAmplitudeValues = { {-45.0,0.0},{0.0,0.0},{45.0,0.0},{90.0,0.0} };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice Implementation
	Binary NUM_A{ "NUM_A.sgn" };
	Binary MI_A{ "MI_A.sgn" };
	TimeContinuousAmplitudeContinuous CLK_A{"CLK_A.sgn"};
	TimeContinuousAmplitudeContinuous CLK_A_1{ "CLKA_out.sgn" };
	PhotonStreamXY S2 {"S2.sgn"};
	TimeContinuousAmplitudeDiscreteReal S3{ "S3.sgn" };
	Messages C_C_1{ "C_C_1.sgn" };
	Messages C_C_6{ "C_C_1.sgn" };
	PhotonStreamXY Q_C_1{"Q_C_1.sgn"};

	// Bob Implementation
	Binary NUM_B{ "NUM_B.sgn" };
	Binary MI_B{ "MI_B.sgn" };
	TimeContinuousAmplitudeContinuous CLK_B{ };
	TimeContinuousAmplitudeContinuousReal SB_1{ "SB_1.sgn" };
	TimeContinuousAmplitudeContinuousReal SB_2{ "SB_2.sgn" };
	Binary SB_3{ "SB_3.sgn" };
	PhotonStream Q_C_4{};
	PhotonStream SB_4{};
	PhotonStream SB_5{};
	PhotonStream SB_6{};
	Messages C_C_4{ "C_C_4.sgn" };
	Messages C_C_3{ "C_C_3.sgn" };

	// Eve Implementation
	Binary NUM_E{ "NUM_E.sgn" };
	Binary MI_E{ "MI_E.sgn" };
	TimeContinuousAmplitudeContinuous CLK_E{ };
	Messages C_C_5{ "C_C_5.sgn" };
	Messages C_C_2{ "C_C_2.sgn" };
	Binary BS_2{ "BS_2.sgn" };
	Binary BS_3{ "BS_3.sgn" };
	TimeDiscreteAmplitudeDiscreteReal Sr_1{ "Sr_1.sgn" };
	TimeContinuousAmplitudeContinuousReal Sr_2{ "Sr_2.sgn" };
	TimeContinuousAmplitudeContinuousReal Sr_3{ "Sr_3.sgn" };
	PhotonStream SE_2{};
	PhotonStream SE_3{};
	PhotonStream SE_4{};
	PhotonStream SE_5{};
	PhotonStream Q_C_2{};
	TimeDiscreteAmplitudeDiscreteReal St_2{ "St_2.sgn" };
	TimeDiscreteAmplitudeDiscreteReal St_1{ "St_1.sgn" };
	PhotonStream SE_6{};
	PhotonStream SE_7{};
	PhotonStream SE_8{};
	PhotonStream Q_C_3{};
	
	
	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice implementation
	BinarySource B0{ vector <Signal*> {}, vector <Signal*> {&NUM_A} };
	B0.setBitPeriod(1/(2 * RateOfPhotons));
	B0.setMode( PseudoRandom );

	Clock B1{ vector<Signal*>{}, vector<Signal*>{&CLK_A} };
	B1.setClockPeriod(1 / RateOfPhotons);
	B1.setSamplingPeriod((1 / RateOfPhotons) / 16);
	B1.setClockPhase(3*PI/2);
	

	AliceQKD B2{ vector <Signal*> { &CLK_A, &NUM_A}, vector <Signal*> {&CLK_A_1, &S3} };
	B2.setIqAmplitudes(iqAmplitudeValues);
	B2.setNumberOfSamplesPerSymbol(16);
	B2.setPulseShaperFilter(Square);
	
	SinglePhotonSource B3{ vector <Signal*> {&CLK_A_1}, vector <Signal*> {&S2} };
	
	Polarizer B4{ vector<Signal*>{&S3,&S2}, vector <Signal*> {&Q_C_1} };

	Sink BB1{ vector <Signal*> {&S3}, vector <Signal*> {} };
	BB1.setNumberOfSamples(1000);

	/*Sink BB2{ vector <Signal*> {&S2}, vector <Signal*> {} };
	BB2.setNumberOfSamples(1000);
	BB2.setDisplayNumberOfSamples(true);*/

	Sink BB3{ vector <Signal*> {&Q_C_1}, vector <Signal*> {} };
	BB3.setNumberOfSamples(2000);

	// ################################################################################


	//Bob Implementation
	/*BinarySource B9{ vector <Signal*> {}, vector <Signal*> {&NUM_B} };
	B9.setMode(PseudoRandom);

	Clock B10{ vector <Signal*> {}, vector <Signal*> {&CLK_B} };

	RotatorLinearPolarizer B11{ vector <Signal*> {&Q_C_4, &SB_3}, vector <Signal*> {&SB_5} };

	PolarizationBeamSplitter B12{ vector <Signal*> {&SB_5}, vector <Signal*> {&SB_4, &SB_6} };

	SinglePhotonDetector B13{ vector <Signal*> {&SB_4}, vector <Signal*> {&SB_1} };

	SinglePhotonDetector B14{ vector <Signal*> {&SB_6}, vector <Signal*> {&SB_2} };

	BobQKD B15{ vector <Signal*> {&NUM_B, &CLK_B, &C_C_3, &SB_1, &SB_2}, vector <Signal*> {&MI_B, &SB_3, &C_C_4} };

	Sink B16{ vector <Signal*> {&C_C_4}, vector <Signal*> {} };

	Sink B17{ vector <Signal*> {&MI_B}, vector <Signal*> {} };*/

	

	// ####################################################################################################
	// ########################### System Declaration and Inicialization ##################################
	// #####################################################################################################

	System MainSystem{ vector <Block*> {&B0, &B1, &B2, &B3, &B4, &BB1, &BB3} };
	// ####################################################################################################
	// ########################### Run ##################################
	// #####################################################################################################

	MainSystem.run();


    return 0;
}

