#include "QJet/NtupleMaker/interface/HLTMaker.h"
//#include <fstream>
#include "TBits.h"

typedef math::XYZTLorentzVectorF LorentzVector;
using namespace edm;
using namespace reco;
using namespace std;

HLTMaker::HLTMaker(const edm::ParameterSet& iConfig) : 
hltConfig_(iConfig, consumesCollector(), *this) {

//HLTPrescaleProvider(iConfig, 
//edm::ConsumesCollector&& iC,
//T& module);

  processName_        = iConfig.getUntrackedParameter<string>         ("processName"       );
  aliasprefix_        = iConfig.getUntrackedParameter<string>         ("aliasPrefix"       );
  processNamePrefix_  = TString(aliasprefix_); //just easier this way....instead of replace processNamePrefix_ everywhere
  triggerPrescaleToken= consumes<pat::PackedTriggerPrescales>(iConfig.getUntrackedParameter<std::string>("triggerPrescaleInputTag"));
  triggerResultsToken = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults",       "", processName_));

  produces<TBits>                           (Form("%sbits"        ,processNamePrefix_.Data())).setBranchAlias(Form("%s_bits"       ,processNamePrefix_.Data()));
  produces<vector<TString> >                (Form("%strigNames"   ,processNamePrefix_.Data())).setBranchAlias(Form("%s_trigNames"  ,processNamePrefix_.Data()));
  produces<vector<unsigned int> >           (Form("%sprescales"   ,processNamePrefix_.Data())).setBranchAlias(Form("%s_prescales"  ,processNamePrefix_.Data()));
  produces<vector<unsigned int> >           (Form("%sl1prescales" ,processNamePrefix_.Data())).setBranchAlias(Form("%s_l1prescales",processNamePrefix_.Data()));
  
  // isData_ = iConfig.getParameter<bool>("isData");
  
}

void HLTMaker::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup){

  // In the case that we are choosing the process name
  // automatically, i.e. the processName_ parameter is
  // an empty string, we can't init  HLTConfigProvider
  // until after we've determined the process name. So
  // don't init here until after we've set processName_
  // in the produce method and init there once and only
  // once. Sounds scary, it is kinda!
  // HLT config _should no longer_ change within runs :)
  if (processName_ != "") {
	bool changed(true);
	// if (hltConfig_.init(iRun,iSetup,"*",changed)) {
	if (hltConfig_.init(iRun,iSetup,processName_,changed)) {
	} 
    else throw cms::Exception("HLTMaker::beginRun: config extraction failure with process name " + processName_);
  }
}

void HLTMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  // If the process name is not specified retrieve the  latest
  // TriggerEvent object and the corresponding TriggerResults.
  // We should only have to do this once though, the next time
  // produce is called processName_ should be set.

  //Now using a single processName_ (set to "HLT" in the configuration file). Is this OK? Do we need the flexibility we had before?
  iEvent.getByToken(triggerResultsToken, triggerResultsH_);
  if (! triggerResultsH_.isValid()) throw cms::Exception("HLTMaker::produce: error getting TriggerResults product from Event!");
  
  triggerNames_ = iEvent.triggerNames(*triggerResultsH_); // Does this have to be done for every event?


  edm::Handle<pat::PackedTriggerPrescales> triggerPrescalesH_; 
  iEvent.getByToken( triggerPrescaleToken, triggerPrescalesH_);
  if (!triggerPrescalesH_.isValid())
    throw cms::Exception("HLTMaker::produce: error getting PackedTriggerPrescales product from Event!");

  auto_ptr<vector<unsigned int> > prescales   (new vector<unsigned int>);
  auto_ptr<vector<unsigned int> > l1prescales (new vector<unsigned int>);

  unsigned int nTriggers = triggerResultsH_->size();
  //if (nTriggers > 768) throw cms::Exception( Form("HLTMaker::produce: number of HLT trigger variables must be increased! ( %d > 768 )", nTriggers) );

  auto_ptr<TBits>                           bits      (new TBits(nTriggers));
  auto_ptr<vector<TString> >                trigNames (new vector<TString>);
  trigNames ->reserve(nTriggers);

  for(unsigned int i = 0; i < nTriggers; ++i){


      // What is your name?
      const string& name = triggerNames_.triggerName(i);
      trigNames->push_back(name);

      //What is your prescale?
	  //Buggy way in miniAOD
      // prescales->push_back( triggerPrescalesH_.isValid() ? triggerPrescalesH_->getPrescaleForIndex(i) : -1 );
	  bool isdata = iEvent.isRealData();

	  if(isdata){

		//get prescale info from hltConfig_
		std::pair<std::vector<std::pair<std::string,int> >,int> detailedPrescaleInfo = hltConfig_.prescaleValuesInDetail(iEvent, iSetup, name);	 
		prescales->push_back( triggerPrescalesH_.isValid() ? detailedPrescaleInfo.second : -1 );
	  
		// save l1 prescale values in standalone vector
		std::vector <int> l1prescalevals;
		for( size_t varind = 0; varind < detailedPrescaleInfo.first.size(); varind++ ){
		  l1prescalevals.push_back(detailedPrescaleInfo.first.at(varind).second);
		}

		// find and save minimum l1 prescale of any ORed L1 that seeds the HLT
		std::vector<int>::iterator result = std::min_element(std::begin(l1prescalevals), std::end(l1prescalevals));
		size_t minind = std::distance(std::begin(l1prescalevals), result);
		// sometimes there are no L1s associated with a HLT. In that case, this branch stores -1 for the l1prescale
		l1prescales->push_back( minind < l1prescalevals.size() ? l1prescalevals.at(minind) : -1 );
	  }
      else {
	  	prescales   -> push_back( hltConfig_.prescaleValue(iEvent, iSetup, name) );
	  	l1prescales -> push_back( 1 );
	  }
	    

	  // Passed... F+
	  if (triggerResultsH_->accept(i)){
		bits->SetBitNumber(i);
	  }
    }


  // strip upper zeros
  bits->Compact();
  iEvent.put(bits,       Form("%sbits",       processNamePrefix_.Data() ) );
  iEvent.put(trigNames  , Form("%strigNames"   , processNamePrefix_.Data() ) );

  iEvent.put(prescales  , Form("%sprescales"   , processNamePrefix_.Data() ) );
  iEvent.put(l1prescales, Form("%sl1prescales" , processNamePrefix_.Data() ) );
}




//define this as a plug-in
DEFINE_FWK_MODULE(HLTMaker);
