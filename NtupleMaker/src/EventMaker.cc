//-*- C++ -*-
//
// Package:    NtupleMaker
// Class:      EventMaker
// 
/**\class EventMaker EventMaker.cc QJet/NtupleMakerMaker/src/EventMaker.cc

   Description: <one line class summary>

   Implementation:
   <Notes on implementation>
*/
//
// Original Author:  Puneeth Kalavase
//         Created:  Fri Jun  6 11:07:38 CDT 2008
// $Id: EventMaker.cc,v 1.33 2012/03/15 22:02:28 dbarge Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Point3D.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "QJet/NtupleMaker/interface/EventMaker.h"

typedef math::XYZTLorentzVectorF LorentzVector;
typedef math::XYZPoint Point;
using namespace edm;
using namespace std;

//
// constructors and destructor
//

EventMaker::EventMaker(const edm::ParameterSet& iConfig) {

    aliasprefix_ = iConfig.getUntrackedParameter<std::string>("aliasPrefix");
    std::string branchprefix = aliasprefix_;
    if(branchprefix.find("_") != std::string::npos) branchprefix.replace(branchprefix.find("_"),1,"");

    produces<unsigned int>                 (branchprefix+"run"            ).setBranchAlias(aliasprefix_+"_run"           );
    produces<unsigned long long>           (branchprefix+"event"          ).setBranchAlias(aliasprefix_+"_event"         );
    produces<unsigned int>                 (branchprefix+"lumiBlock"      ).setBranchAlias(aliasprefix_+"_lumiBlock"     );
}


EventMaker::~EventMaker() {}

void EventMaker::beginRun (const edm::Run& iRun, const edm::EventSetup& iSetup)
{
}

void EventMaker::beginJob() {  
}

void EventMaker::endJob() {
}

// ------------ method called to produce the data  ------------
void EventMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
    auto_ptr<unsigned int>                evt_run             (new unsigned int              );
    auto_ptr<unsigned long long>          evt_event           (new unsigned long long        );
    auto_ptr<unsigned int>                evt_lumiBlock       (new unsigned int              );
     
    *evt_run                       = iEvent.id().run()        ;
    *evt_event                     = iEvent.id().event()      ;
    *evt_lumiBlock                 = iEvent.luminosityBlock() ;

    std::string branchprefix = aliasprefix_;
    if(branchprefix.find("_") != std::string::npos) branchprefix.replace(branchprefix.find("_"),1,"");

    iEvent.put(evt_run              ,branchprefix+"run"             );
    iEvent.put(evt_event            ,branchprefix+"event"           );
    iEvent.put(evt_lumiBlock        ,branchprefix+"lumiBlock"       );
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventMaker);
