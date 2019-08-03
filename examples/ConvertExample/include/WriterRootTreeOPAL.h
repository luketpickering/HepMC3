#ifndef HEPMC3_WRITERROOTTREEOPAL_H
#define HEPMC3_WRITERROOTTREEOPAL_H
///
/// @file  WriterRootTreeOPAL.h
/// @brief Definition of class \b WriterRootTreeOPAL
///
/// @class HepMC3::WriterRootTreeOPAL
/// @brief GenEvent I/O output to files similar to these produced by OPAL software
///
/// @ingroup Examples
///
#include "HepMC3/WriterRootTree.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/Data/GenEventData.h"
namespace HepMC3
{
class WriterRootTreeOPAL : public WriterRootTree
{
public:
    WriterRootTreeOPAL(const std::string &filename,shared_ptr<GenRunInfo> run = shared_ptr<GenRunInfo>());
    void init_branches();
    void write_event(const GenEvent &evt);
    void set_run_number(const int nr);
private:
    float  m_Ebeam;
    int    m_Irun;
    int    m_Ievnt;
};
}
#endif
