//
// ********************************************************************
// *																  *
// * This file is part of the TOPAS-nBio extensions to the			  *
// *   TOPAS Simulation Toolkit.									  *
// * The TOPAS-nBio extensions are freely available under the license *
// *   agreement set forth at: https://topas-nbio.readthedocs.io/	  *
// *																  *
// ********************************************************************
//
// Authors: Alejandro Bertolet, Jan Schuemann


#ifndef TsScoreDNADamageSBS_hh
#define TsScoreDNADamageSBS_hh

#include "TsVNtupleScorer.hh"
#include "TsHitInDNA.hh"
//#include "TsDefineDamage.hh"

class TsScoreDNADamageSBS : public TsVNtupleScorer
{
public:
	TsScoreDNADamageSBS(TsParameterManager* pM, TsMaterialManager* mM, TsGeometryManager* gM, TsScoringManager* scM, TsExtensionManager* eM,
						G4String scorerName, G4String quantity, G4String outFileName, G4bool isSubScorer);
	~TsScoreDNADamageSBS();

	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	void AccumulateEvent();
	void AbsorbResultsFromWorkerScorer(TsVScorer*);
	void UserHookForEndOfRun();
	G4int Analyze(std::vector<TsHitInDNA*> hits, G4int eventID);

private:
	G4int fNumberOfHistoriesInRun;
	// For Material-based filter
	G4int fBasePairDepth;
	std::vector<G4Material*> fStrand1Materials;
	std::vector<G4Material*> fStrand2Materials;

	// For direct damage
	G4double fDirectDamageThreshold;
	G4bool fUseLinearProbabilityForDirectDamage;
	G4double fLowerLimitLinearProbability;
	G4double fUpperLimitLinearProbability;
	// For quasi-direct damage
	G4double fProbabilityOfChargeTransferFromHydrationShellToBackbone;
	// For indirect damage
	G4bool fAlwaysScavengeSpeciesInDNAComponents;
	G4double fProbabilityOfScavengingInBackbone;
	G4double fProbabilityOfScavengingInBase;
	G4double fProbabilityOfDamageInBackbone;
	G4double fProbabilityOfDamageInBase;
	G4bool fScavengeInHistones;

	// For defining types of damage to be accounted for
	G4bool fScoreDSB;
	G4int fNumberOfBasePairsForDSB;

	G4bool fScoreFoci;
	G4double fFociSize;

	G4bool fExcludeShortFragments;
	G4int fLowerThresholdForFragmentDetection;
	G4int fUpperThresholdForFragmentDetection;

	// Options for the output
	G4bool fWriteCSVWithExtensiveDamage;
	G4bool fScoreDirectDamage;
	G4bool fScoreIndirectDamage;
	G4bool fScoreQuasiDirectDamage;
	G4bool fScoreOnBases;
	G4bool fScoreOnBackbones;
	G4bool fBreakDownPerDamageOrigin;

	// For SDD specification
	G4double fDosePerExposure;
	G4bool fOnlyIncludeDSBinSDD;
	G4bool fWriteMinimalSDDOutput;
	G4String fPrimaryParticle;

	// Scoring of physical quantities
	G4double fEdep;
	G4double fTrackAveragedLET;
	G4double fDoseInThisExposure;
	G4int fExposureID;

	// Quantification of damage
	G4int fNumSB;
	G4int fNumSBDirect;
	G4int fNumSBQuasiDirect;
	G4int fNumSBIndirect;
	G4int fNumSSB;
	G4int fNumSSBDirect;
	G4int fNumSSBQuasiDirect;
	G4int fNumSSBIndirect;
	G4int fNumDSB;
	G4int fNumDSBDirect;
	G4int fNumDSBIndirect;
	G4int fNumDSBDirectIndirect;
	G4int fNumDSBDirectQuasiDirect;
	G4int fNumDSBQuasiDirectQuasiDirect;
	G4int fNumDSBIndirectQuasiDirect;
	G4int fNumBaseDamage;
	G4int fNumBaseDamageDirect;
	G4int fNumBaseDamageQuasiDirect;
	G4int fNumBaseDamageIndirect;

	// Quantification for foci
	G4int fNumFoci;

	// Yields
	G4double fYBaseDam;;
	G4double fYSB;
	G4double fYSSB;
	G4double fYDSB;

	// Accumulation of events
	std::vector<G4double> fEventsEdep;

	// Map to check if a track enters in a volume
	std::map<G4double, G4int> fTrackSteps;
	std::map<G4double, G4String> fTrackLastVolume;

	// Hits recorded
	std::vector<TsHitInDNA*> fHits;

	// Collections of hits for each event
	std::vector<std::vector<TsHitInDNA*>> fCollectionsOfHits;

	// Codes for components ID
	G4int base = 0;
	G4int backbone = 1;
	G4int hydrationshell = 2;
	G4int histone = 3;
};



#endif
