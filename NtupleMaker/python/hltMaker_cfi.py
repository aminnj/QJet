import FWCore.ParameterSet.Config as cms

hltMaker = cms.EDProducer("HLTMaker",
    processName = cms.untracked.string("HLT"),
    # HLT is the default process name, but it cannot be
    # guaranteed to be there. Use an empty string to
    # automatically choose the process name responsible
    # for the latest HLT products
    aliasPrefix = cms.untracked.string("hlt"),                       
    triggerPrescaleInputTag = cms.untracked.string("patTrigger"),
)
