#pragma once

#include "IMexPPWrappableClass.h"
#include "AssertionError.h"

template <class T, class SerializationType>
void parseRegularFunctions(char* cmd, int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
	// TODO: add new here (need to parse args)
	VERIFY(nrhs > 2);

	if (!strcmp("Delete", cmd)) {
		destroyObject<T>(prhs[2]);
	}

	if (!strcmp("Serialize", cmd)) {
		VERIFY(nlhs == 1);
		T* obj = convertMat2Ptr<T>(prhs[2]);

		SerializationType serializationObj = obj->serialize();
		plhs[0] = serializationObj.exportToMATLAB();
	}

	if (!strcmp("Restore", cmd)) {
		VERIFY(nlhs == 1);

		SerializationType serializationObj;
		serializationObj.importFromMATLAB(prhs[2]);
		T* obj = new T;
		obj->unserialize(serializationObj);
		plhs[0] = convertPtr2Mat<T>(obj);
	}
}