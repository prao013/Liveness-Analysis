#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/PassManager.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"
#include <algorithm>
#include <iterator>
using namespace std;

using namespace llvm;

namespace {
void getunion(set<string> a, set<string> b)
	{
  	a.insert(b.begin(), b.end());
	}
// This method implements what the pass does
void visitor(Function &F){

    // Here goes what you want to do with a pass
    
		string func_name = "main";
	    
	    // Comment this line
        //if (F.getName() != func_name) return;
	int count=0;
	map<string, set<string> > PREDBBMAP;
	 
	for (auto& basic_block : F)
        {count++;
	}
	
	string bbs[count];
	for (auto& basic_block : F)
        {count--;
	bbs[count]=basic_block.getName().str();
	}
	
	for (auto& basic_block : F)
        {count++;
	}
	
	/*for(int i=0;i<count;i++){
	errs()<<bbs[i]<<" ";
	}*/
	
	for (auto& basic_block : F){
	
	for (auto it = pred_begin(&basic_block), et = pred_end(&basic_block); it != et; ++it){
		BasicBlock* predecessor = *it;
	PREDBBMAP[basic_block.getName().str()].insert(predecessor->getName().str());
		
	}}
	
	
	map<string, set<string> > UEVAR;
	map<string, set<string> > VARKILL;
        for (auto& basic_block : F)
        {	
	for (auto& inst : basic_block)
	    {	
		 if(inst.getOpcode() == Instruction::Store){
	            string operand2=inst.getOperand(1)->getName().str();
                    VARKILL[basic_block.getName().str()].insert(operand2);
                }
                if(inst.getOpcode() == Instruction::Load){
		    string operand1=inst.getOperand(0)->getName().str();
		    auto it=VARKILL[basic_block.getName().str()].find(operand1);
		    if ( it == VARKILL[basic_block.getName().str()].end() )  
		    {UEVAR[basic_block.getName().str()].insert(operand1);}
                }    
            } // end for inst  
	}

	
	
	
	
	
	
	map<string, set<string> > LIVEOUT;
	for(int i=0;i<count;i++){
	LIVEOUT[bbs[i]];
	}
	
	/*
	for(auto it = LIVEOUT.cbegin(); it != LIVEOUT.cend(); ++it)
	{
	errs()<<it->first<<" ";
	}*/
	
	set<string>::iterator itrr;
	set<string> HOLDER;
	
	int i=2;
	while(i>0){
	for(int i=0;i<count;i++){
	  for (itrr = PREDBBMAP[bbs[i]].begin();
       itrr != PREDBBMAP[bbs[i]].end(); itrr++)
	  {
//	LIVEOUT[*itrr] union ( ( LIVEOUT[bbs[i]] diff VARKILL[bbs[i]] ) union UEVAR[bbs[i]])
		set_difference(LIVEOUT[bbs[i]].begin(), LIVEOUT[bbs[i]].end(), VARKILL[bbs[i]].begin(), VARKILL[bbs[i]].end(),
    std::inserter(HOLDER, HOLDER.end()));
		
	//	errs()<<"Before"<<"\n";  
	//	set<string>::iterator iti;
	//	for (iti = HOLDER.begin(); iti != HOLDER.end(); ++iti) {
    	//			errs() << *iti<<" ";
	//	}
		  
		  
		  
		HOLDER.insert(UEVAR[bbs[i]].begin(),UEVAR[bbs[i]].end());
		
	//	errs()<<"After"<<"\n";
	//	set<string>::iterator itf;
	//	for (itf = HOLDER.begin(); itf != HOLDER.end(); ++itf) {
    	//			errs() << *itf<<" ";
	//	}
		  
		LIVEOUT[*itrr].insert(HOLDER.begin(),HOLDER.end());
		
		HOLDER.clear();
	}}
	i--;
	}
	
	/*
	for(int i=0;i<count;i++){
	  for (itrr = PREDBBMAP[bbs[i]].begin();
       itrr != PREDBBMAP[bbs[i]].end(); itrr++)
	  {
//	LIVEOUT[*itrr] union ( ( LIVEOUT[bbs[i]] diff VARKILL[bbs[i]] ) union UEVAR[bbs[i]])
		set_difference(LIVEOUT[bbs[i]].begin(), LIVEOUT[bbs[i]].end(), VARKILL[bbs[i]].begin(), VARKILL[bbs[i]].end(),
    std::inserter(HOLDER, HOLDER.end()));
		
		errs()<<"Before"<<"\n";  
		set<string>::iterator iti;
		for (iti = HOLDER.begin(); iti != HOLDER.end(); ++iti) {
    				errs() << *iti<<" ";
		}
		  
		  
		  
		HOLDER.insert(UEVAR[bbs[i]].begin(),UEVAR[bbs[i]].end());
		
		errs()<<"After"<<"\n";
		set<string>::iterator itf;
		for (itf = HOLDER.begin(); itf != HOLDER.end(); ++itf) {
    				errs() << *itf<<" ";
		}
		  
		LIVEOUT[*itrr].insert(HOLDER.begin(),HOLDER.end());
		
		HOLDER.clear();
	}}
	
	*/
	
	
	
	
	
	
	
	
	
	
	
for (auto& basic_block : F)
        {	
	errs() <<"\n"<< "-----"<<basic_block.getName()<<"-----"<<"\n"; 
//	errs() <<"\n"<<basic_block.getName().str()<<": ";
//		set<string>::iterator itr0;
  // Displaying set elements
//  for (itr0 = PREDBBMAP[basic_block.getName().str()].begin();
//       itr0 != PREDBBMAP[basic_block.getName().str()].end(); itr0++)
//  {
//    errs() << *itr0 << " ";
//  }
		
		
		
	    errs() <<"\n"<< "UEVAR:";
		set<string>::iterator itr;
   
  // Displaying set elements
  for (itr = UEVAR[basic_block.getName().str()].begin();
       itr != UEVAR[basic_block.getName().str()].end(); itr++)
  {
    errs() <<" "<< *itr ;
  }
 
	 //errs()<<UEVAR;
	//    for (int i = 0; i < UEVAR.size(); i++)
	//    {errs() << UEVAR[i] << " ";}
	
	errs() <<"\n"<< "VARKILL:";
	set<string>::iterator itr1;
   
  // Displaying set elements
  for (itr1 = VARKILL[basic_block.getName().str()].begin();
       itr1 != VARKILL[basic_block.getName().str()].end(); itr1++)
  {
    errs() <<" "<< *itr1;
  }
 errs() <<"\n"<< "LIVEOUT:";
	set<string>::iterator itr2;
   
  // Displaying set elements
  for (itr2 = LIVEOUT[basic_block.getName().str()].begin();
       itr2 != LIVEOUT[basic_block.getName().str()].end(); itr2++)
  {
    errs() << " "<< *itr2 ;
  } 
	
	//err()<<VARKILL;
	//    for (int i = 0; i < VARKILL.size(); i++)
	//    {errs() << VARKILL[i] << " ";}
	
        } // end for block
	errs()<<"\n";
        
}


// New PM implementation
struct ValueNumberingPass : public PassInfoMixin<ValueNumberingPass> {

  // The first argument of the run() function defines on what level
  // of granularity your pass will run (e.g. Module, Function).
  // The second argument is the corresponding AnalysisManager
  // (e.g ModuleAnalysisManager, FunctionAnalysisManager)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
  	visitor(F);
	return PreservedAnalyses::all();

	
  }
  
    static bool isRequired() { return true; }
};
}



//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "ValueNumberingPass", LLVM_VERSION_STRING,
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
        ArrayRef<PassBuilder::PipelineElement>) {
          if(Name == "value-numbering"){
            FPM.addPass(ValueNumberingPass());
            return true;
          }
          return false;
        });
    }};
}
