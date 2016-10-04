# ifndef PROGRAM_INCLUDE_TESTBLOCK_H_
# define PROGRAM_INCLUDE_TESTBLOCK_H_

# include "netxpto.h"
# include <vector>

// this is a test block for the purpose of beta testing new code
// current code: TIAMP with electrical noise
class testblock : public Block {

	bool firstTime{ true };

public:

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };

	testblock(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

private:

};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
