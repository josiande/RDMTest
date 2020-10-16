cmake_minimum_required (VERSION 3.8)

add_library (RDMTestClass OBJECT 
	    #source
		"RDMTestClass.cpp" 
		
		#includes
		"RDMTestClass.h")
target_link_libraries(RDMTestClass PUBLIC GadgetDLL::GadgetDLL)
target_link_libraries(RDMTestClass PUBLIC EtcPal)
target_link_libraries(RDMTestClass PUBLIC RDM)