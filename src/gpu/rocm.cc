#include <dlfcn.h>

#include "../../include/gpu/rocm.h"

RocmHandler::RocmHandler() : IGpuHandler() {

}

RocmHandler::~RocmHandler() {

}

bool RocmHandler::init() {
   return true;
}

std::string RocmHandler::get_name() {
   return "";
}

int RocmHandler::get_temperature() {
   return 0;
}

int RocmHandler::get_load() {
   return 0;
}
