// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2023 The HepMC collaboration (see AUTHORS for details)
//
#ifndef HEPMC3_READERFACTORY_FWD_H
#define HEPMC3_READERFACTORY_FWD_H

#include <memory>
#include <string>
#include <sys/stat.h>
#include <string.h>

#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"
#include "HepMC3/ReaderHEPEVT.h"
#include "HepMC3/ReaderLHEF.h"
#include "HepMC3/ReaderPlugin.h"
#include "HepMC3/CompressedIO.h"

namespace HepMC3 {
#if ! (defined(__darwin__) || defined(__APPLE__)) &&  ! ((defined(WIN32) || defined(_WIN32) || defined(__WIN32)) && !defined(__CYGWIN__))
const std::string libHepMC3rootIO = "libHepMC3rootIO.so.3";
const std::string libHepMC3protobufIO = "libHepMC3protobufIO.so.3";
#endif
#if defined(__darwin__) || defined(__APPLE__)
const std::string libHepMC3rootIO = "libHepMC3rootIO.dylib";
const std::string libHepMC3protobufIO = "libHepMC3protobufIO.dylib";
#endif
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32)) && !defined(__CYGWIN__)
const std::string libHepMC3protobufIO = "HepMC3protobufIO.dll";
const std::string libHepMC3rootIO = "HepMC3rootIO.dll";
#endif

class InputInfo {
public:
    InputInfo() {};
    InputInfo(const std::string &filename);
    void classify();
    std::vector<std::string> m_head;
    bool m_remote;
    bool m_pipe;
    bool m_error;
    bool m_init;
    bool m_root;
    bool m_protobuf;
    bool m_asciiv3;
    bool m_iogenevent;
    bool m_lhef;
    bool m_hepevt;
    std::shared_ptr<Reader> m_reader;
};

std::shared_ptr<Reader> deduce_reader(std::istream &stream);

std::shared_ptr<Reader> deduce_reader(std::shared_ptr<std::istream> stream);


}
#endif
