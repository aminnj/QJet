import FWCore.ParameterSet.Config as cms
from Configuration.EventContent.EventContent_cff        import *

process = cms.Process("QJet")

process.load('Configuration/EventContent/EventContent_cff')
process.load("Configuration.StandardSequences.Services_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.GlobalTag.globaltag = "80X_dataRun2_Prompt_v9"

process.out = cms.OutputModule("PoolOutputModule",
  fileName     = cms.untracked.string('ntuple.root'),
  dropMetaData = cms.untracked.string("NONE")
)
process.outpath = cms.EndPath(process.out)

process.out.outputCommands = cms.untracked.vstring( 'drop *' )
process.out.outputCommands.extend(cms.untracked.vstring('keep *_*_*_QJet*'))

process.load("QJet.NtupleMaker.qJetMaker_cfi")

#Options for Input
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
      '/store/data/Run2016B/JetHT/MINIAOD/PromptReco-v1/000/272/674/00000/3408A387-B514-E611-BBF8-02163E011E16.root',
      )
)
process.source.noEventSort = cms.untracked.bool( True )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.p = cms.Path( 
  process.qJetMaker
)

