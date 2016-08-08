import FWCore.ParameterSet.Config as cms

fixedGridRhoAllMaker = cms.EDProducer("EnergyDensityMaker",
                                      input = cms.InputTag("fixedGridRhoAll","", "RECO"),
                                      alias = cms.untracked.string("evt_fixgrid_all_rho"))
