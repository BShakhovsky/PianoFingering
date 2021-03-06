# include "stdafx.h"
# include "MonoCosts.h"
# include "CostRules.h"
# include "DistanceTable.h"

using std::pair;

// not tested (too simple):
int MonoCosts::CostOfSingle(const char finger) const
{
	return CostRules::Rule5_WeakFinger(finger);
}

// fully tested:
double MonoCosts::CostOfPair(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2) const
{
	return static_cast<double>(CostRules::Rule1_StretchComf(note1, note2))
		+ CostRules::Rule2_SpanRel(note1, note2)
		+ CostRules::Rule7_ThreeFour(note1.second, note2.second)
		+ CostRules::Rule8_FourOnBlack(note1, note2)
		+ CostRules::Rule9_ThumbOnBlack(note1, note2)	// float
		+ CostRules::Rule10_PinkyOnBlack(note1, note2)
		+ CostRules::Rule11_ThumbPassing(note1, note2)
		+ CostRules::Rule12_ThumbCross_Black(note1, note2)
		+ CostRules::Rule14_MaxPractical(note1, note2)
		+ CostRules::Rule15_SameNote(note1, note2)
		+ CostRules::Rule16_SameFinger(note1, note2);	// my own rule
}
double MonoCosts::CostOfPair_modified(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2) const
{
	// if interval is longer than thumb-pinky max practical, then it does not matter which fingers to use
	return abs(note1.first - note2.first) > DistanceTable::MAX_PRACTICAL
		? static_cast<double>(CostRules::Rule7_ThreeFour(note1.second, note2.second))
			+ CostRules::Rule8_FourOnBlack(note1, note2)
			+ CostRules::Rule9_ThumbOnBlack(note1, note2)	// float
			+ CostRules::Rule10_PinkyOnBlack(note1, note2)
			+ CostRules::Rule11_ThumbPassing(note1, note2)
			+ CostRules::Rule12_ThumbCross_Black(note1, note2)
			+ CostRules::Rule16_SameFinger(note1, note2)	// my own rule
		: CostOfPair(note1, note2);
}

// not tested (do not know how - 3D-table?):
int MonoCosts::CostOfThree(const pair<int16_t, char>& note1, const pair<int16_t, char>& note2,
	const pair<int16_t, char>& note3) const
{
	// if interval is longer than thumb-pinky max practical, then it does not matter which fingers to use
	return (
		abs(note1.first - note3.first) > DistanceTable::MAX_PRACTICAL ? 0
			: CostRules::Rule3_PositionChange(note1, note2, note3)	// Rule3 is also not tested
//			+ CostRules::Rule4_PositionSize(note1, note3)
		)
		+ CostRules::Rule6_ThreeFourFive(note1.second, note2.second, note3.second)
		+ CostRules::Rule13_ThreeSameFinger(note1, note2, note3);
}