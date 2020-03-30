#ifndef M_JET_H
#define M_JET_H
#include "TObject.h"

class MJet : public TObject {
	public:
        Int_t event;
        Int_t flavor;
        TLorentzVector lv;
	
	ClassDef(MJet,1);
};
#endif
