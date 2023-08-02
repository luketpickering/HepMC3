// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2023 The HepMC collaboration (see AUTHORS for details)
//
#ifndef HEPMC3_READERFACTORY_H
#define HEPMC3_READERFACTORY_H


#include "HepMC3/ReaderFactory_fwd.h"
#include "HepMC3/CompressedIO.h"

namespace HepMC3 {

/**
 * @brief This function deduces the type of input file based on the name/URL
 * and its content, and will return an appropriate Reader object
 *
 * @todo Need a DEBUG verbosity flag
 */

inline std::shared_ptr<Reader> deduce_reader(const std::string &filename)
{
    InputInfo input(filename);
    if (input.m_init && !input.m_error && input.m_reader) return input.m_reader;
    if ( input.m_root || input.m_remote) {
        HEPMC3_DEBUG(10, "deduce_reader: Attempt ReaderRootTree for " << filename);
        return   std::make_shared<ReaderPlugin>(filename,libHepMC3rootIO,std::string("newReaderRootTreefile"));
    }
    if (input.m_protobuf) {

        HEPMC3_DEBUG(10, "deduce_reader: Attempt ProtobufIO for " << filename);
        return std::make_shared<ReaderPlugin>(filename,libHepMC3protobufIO,std::string("newReaderprotobuffile"));
    }
#if HEPMC3_USE_COMPRESSION
    HEPMC3_DEBUG(10, "Attempt ReaderGZ for " << filename);
    char buf[6];
    snprintf(buf,6,"%s",input.m_head.at(0).c_str());
    Compression det = detect_compression_type(buf, buf + 6);
    if ( det != Compression::plaintext ) {
        HEPMC3_DEBUG(10, "Detected supported compression " << std::to_string(det));
        return deduce_reader(std::shared_ptr< std::istream >(new ifstream(filename.c_str())));
    }
#endif
    if (input.m_asciiv3) {
        HEPMC3_DEBUG(10, "Attempt ReaderAscii for " << filename);
        return std::shared_ptr<Reader>((Reader*) ( new ReaderAscii(filename)));
    }
    if ( input.m_iogenevent) {
        HEPMC3_DEBUG(10, "Attempt ReaderAsciiHepMC2 for " << filename);
        return std::shared_ptr<Reader>((Reader*) ( new ReaderAsciiHepMC2(filename)));
    }
    if ( input.m_lhef) {
        HEPMC3_DEBUG(10, "Attempt ReaderLHEF for " << filename);

        return std::shared_ptr<Reader>((Reader*) ( new ReaderLHEF(filename)));
    }
    if ( input.m_hepevt)  {
        HEPMC3_DEBUG(10, "Attempt ReaderHEPEVT for " << filename);

        return std::shared_ptr<Reader>((Reader*) ( new ReaderHEPEVT(filename)));
    }
    HEPMC3_DEBUG(10, "deduce_reader: all attempts failed for " << filename);
    return std::shared_ptr<Reader>(nullptr);
}
}
#endif
