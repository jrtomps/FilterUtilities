INSTDIR=/usr/devopt/nscldaq/11.1-dev

include $(INSTDIR)/filterkit/FilterIncludes




#
#  Add your own compilation/link flags here:

USERCXXFLAGS=-std=c++11
USERCCFLAGS=$(USERCCFLAGS)
USERLDFLAGS= -Wl,-rpath=$(INSTDIR)/lib

#
#  Add the names of objects you need here if you modified the name of the driver file, 
#  this should also reflect thtat.
#
#OBJECTS = CSourceCounterFilter.o CMonotonicTstamp.o FragmentIndex.o CFragCounterFilter.o CCounterFilter.o CSourceIDSelector.o SkeletonMain.o
OBJECTS = CDuplicateFilter.o SkeletonMain.o

#
#  Modify the line below to provide the name of the library you are trying to build
#  it must be of the form libsomethingorother.so
#

USERFILTER = UserFilter

$(USERFILTER): $(OBJECTS)
	   $(CXX) $(OBJECTS) -o $@ $(USERLDFLAGS) $(LDFLAGS)






