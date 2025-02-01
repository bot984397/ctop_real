#include "../../include/gpu/integrated.h"

IntegratedHandler::IntegratedHandler() : IGpuHandler() {

}

IntegratedHandler::~IntegratedHandler() {

}

bool IntegratedHandler::init() {
   return true;
}

std::string IntegratedHandler::get_name() {
   return "";
}

int IntegratedHandler::get_temperature() {
   return 0;
}

int IntegratedHandler::get_load() {
   return 0;
}
