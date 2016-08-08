from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'JetHT_Run2016B_v1'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/pset.py'

config.section_("Data")
config.Data.inputDataset = '/JetHT/Run2016B-PromptReco-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 3

config.section_("Site")
config.Site.storageSite = 'T2_US_UCSD'
