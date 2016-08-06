# QJet

## Installation
Be sure to modify the CMSSW release appropriately.
```
CMSSWREL=CMSSW_8_0_7
cmsrel $CMSSWREL
cd $CMSSWREL/src
cmsenv
git clone git@github.com:aminnj/QJet.git
cd QJet
scram b -j2
```
To do a quick test run over one file:
```
cd NtupleMaker/test
cmsRun pset.py # produces ntuple.root
```

