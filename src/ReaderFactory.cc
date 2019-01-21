// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2019 The HepMC collaboration (see AUTHORS for details)
//
#include "HepMC/ReaderFactory.h"
namespace HepMC{
  
  std::shared_ptr<Reader> make_reader(const std::string &filename){
    
    std::ifstream file(filename);
    if(!file.is_open()){
      ERROR("make_reader: could not open file for testing HepMC version: "<<filename);
    }
    
    std::string word;
    while(word != "HepMC::Version" && !file.eof()){
      file >> word;
    }
    
    if(file.eof()){
      ERROR("make_reader: Could not determine version string from input HepMC file");
    }
    
    int ver;
    file >> ver;
    
    file.close();
    
    if(ver == 2){
      return std::make_shared<ReaderAsciiHepMC2>(filename);
    }else if(ver == 3){
      return std::make_shared<ReaderAscii>(filename);
    }
    
    std::shared_ptr<Reader> result = std::make_shared<ReaderAscii>(filename);
    if(!result->failed()) return result;
    
    result = std::make_shared<ReaderAsciiHepMC2>(filename);
    if(!result->failed()) return result;

    ERROR("make_reader: Could not determine HepMC version.  Expecting version 2 or 3, got "<<ver);
    
    return shared_ptr<Reader>(nullptr);
  }
  
}


