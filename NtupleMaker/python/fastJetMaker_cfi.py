import FWCore.ParameterSet.Config as cms

fixedGridRhoAllMaker = cms.EDProducer("EnergyDensityMaker",
                                      input = cms.InputTag("fixedGridRhoAll","", "RECO"),
                                      alias = cms.untracked.string("evt_fixgrid_all_rho"))

# fixedGridRhoFastJetAllMaker = cms.EDProducer("EnergyDensityMaker",
#                                              input = cms.InputTag("fixedGridRhoFastjetAll","", configProcessName.name2),
#                                              alias = cms.untracked.string("evt_fixgridfastjet_all_rho"))

# # fixedGridRhoFastJetAllMakerMETTools = cms.EDProducer("EnergyDensityMaker",
# #                                              input = cms.InputTag("fixedGridRhoFastjetAll","", "CMS3"),
# #                                              alias = cms.untracked.string("evt_fixgridfastjetMETTools_all_rho"))

# fixedGridRhoFastJetAllCaloMaker = cms.EDProducer("EnergyDensityMaker",
#                                              input = cms.InputTag("fixedGridRhoFastjetAllCalo","", configProcessName.name2),
#                                              alias = cms.untracked.string("evt_fixgridfastjet_allcalo_rho"))

# fixedGridRhoFastJetCentralCaloMaker = cms.EDProducer("EnergyDensityMaker",
#                                              input = cms.InputTag("fixedGridRhoFastjetCentralCalo","", configProcessName.name2),
#                                              alias = cms.untracked.string("evt_fixgridfastjet_centralcalo_rho"))
# fixedGridRhoFastJetCentralChargedPileUpMaker = cms.EDProducer("EnergyDensityMaker",
#                                              input = cms.InputTag("fixedGridRhoFastjetCentralChargedPileUp","", configProcessName.name2),
#                                              alias = cms.untracked.string("evt_fixgridfastjet_centralchargedpileup_rho"))
# fixedGridRhoFastJetCentralNeutralMaker = cms.EDProducer("EnergyDensityMaker",
#                                              input = cms.InputTag("fixedGridRhoFastjetCentralNeutral","", configProcessName.name2),
#                                              alias = cms.untracked.string("evt_fixgridfastjet_centralneutral_rho"))
