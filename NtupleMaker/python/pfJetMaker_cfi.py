import FWCore.ParameterSet.Config as cms

pfJetMaker = cms.EDProducer("PFJetMaker",
  aliasPrefix = cms.untracked.string("pfjets"),
  pfJetsInputTag                   = cms.InputTag("slimmedJets","","RECO"),
  pfCandidatesTag                  = cms.InputTag("packedPFCandidates"),
  pfJetPtCut                       = cms.double(5.),
)
