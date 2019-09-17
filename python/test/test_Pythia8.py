import sys

v=sys.version_info
sys.path=["../"+str(v[0])+"."+str(v[1])+"."+str(v[2])+"/"]+sys.path

import pyHepMC3.pyHepMC3.HepMC3 as hm
import pythia8 as p8
from Pythia8ToHepMC3 import Pythia8ToHepMC3 
def test_Pythia8():
 pythia = p8.Pythia()
 pythia.readString("WeakSingleBoson:ffbar2gmZ = on")
 pythia.readString("Beams:idA =  11")
 pythia.readString("Beams:idB = -11")
 pythia.readString("Beams:eCM =  91.2")
 pythia.init()
 p8tohm=Pythia8ToHepMC3 ()
 out=hm.WriterAscii("test_Pythia.hepmc")
 for iEvent in range(0, 100):
    if not pythia.next(): continue
    nCharged = 0
    evt=hm.GenEvent()
    p8tohm.fill_next_event1(pythia,evt,iEvent)
    out.write_event(evt)
    evt.clear()
 pythia.stat()
 out.close()
 return 0
if __name__ == "__main__":
    result=1
    try:
     result=test_Pythia8()
    except:
     result=1
    sys.exit(result)