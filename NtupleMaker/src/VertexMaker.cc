// -*- C++ -*-
//
// Package:    VertexMaker
// Class:      VertexMaker
// 
/**\class VertexMaker VertexMaker.cc CMS2/VertexMaker/src/VertexMaker.cc

   Description: <one line class summary>

   Implementation:
   <Notes on implementation>
*/
//
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "QJet/NtupleMaker/interface/VertexMaker.h"

#include "DataFormats/Math/interface/LorentzVector.h"

typedef math::XYZTLorentzVectorF LorentzVector;

//
// class decleration
//

//
// constructors and destructor
//
VertexMaker::VertexMaker(const edm::ParameterSet& iConfig) {

  aliasprefix_ = iConfig.getUntrackedParameter<std::string>("aliasPrefix");
  std::string branchprefix = aliasprefix_;
  if(branchprefix.find("_") != std::string::npos) branchprefix.replace(branchprefix.find("_"),1,"");

  produces<unsigned int>                      ("evtn"+branchprefix              ).setBranchAlias("evt_n"+aliasprefix_              );  // number of vertices in event

  // vertex collection input tag
  primaryVertexToken = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVertexInputTag"));
}

void VertexMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // get the primary vertices
  edm::Handle<reco::VertexCollection> vertexHandle;

    iEvent.getByToken(primaryVertexToken, vertexHandle);
    if( !vertexHandle.isValid() ) {
      throw cms::Exception("VertexMaker::produce: error getting vertices from Event!");
    }
  const reco::VertexCollection *vertexCollection = vertexHandle.product();
//  std::cout << __LINE__ <<"number of vertex" <<vertexCollection->size()<<std::endl;

  std::auto_ptr<unsigned int>                      evt_nvtxs                     (new unsigned int                     );
     
  *evt_nvtxs = vertexCollection->size();

  // store into the event
  std::string branchprefix = aliasprefix_;
  if(branchprefix.find("_") != std::string::npos) branchprefix.replace(branchprefix.find("_"),1,"");

  iEvent.put(evt_nvtxs,                     "evtn"+branchprefix              );
}

// ------------ method called once each job just before starting event loop  ------------
void VertexMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void VertexMaker::endJob() 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(VertexMaker);

