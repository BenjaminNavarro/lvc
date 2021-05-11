add_llvm_component_library(LLVMDemangle
  Demangle.cpp
  ItaniumDemangle.cpp
  MicrosoftDemangle.cpp
  MicrosoftDemangleNodes.cpp

  ADDITIONAL_HEADER_DIRS
  "${LVC_MAIN_INCLUDE_DIR}/llvm/Demangle"

)
