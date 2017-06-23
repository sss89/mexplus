#pragma once

#include "IMexPPWrappableClass.h"
#include "AssertionError.h"

// if the cmd is one of "Serialize", "Restore" or "Delete", perfoms the appropriate operation and returns true.
// otherwise, returns false
template <class T, class SerializationType>
bool parseRegularFunctions(char* cmd, int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
	// TODO: add new here (need to parse args)
	VERIFY(nrhs > 2);

	if (!strcmp("Delete", cmd)) {
		destroyObject<T>(prhs[2]);
		return true;
	}

	if (!strcmp("Serialize", cmd)) {
		VERIFY(nlhs == 1);
		T* obj = convertMat2Ptr<T>(prhs[2]);

		SerializationType serializationObj = obj->serialize();
		plhs[0] = serializationObj.exportToMATLAB();
		return true;
	}

	if (!strcmp("Restore", cmd)) {
		VERIFY(nlhs == 1);

		SerializationType serializationObj;
		serializationObj.importFromMATLAB(prhs[2]);
		T* obj = new T;
		obj->unserialize(serializationObj);
		plhs[0] = convertPtr2Mat<T>(obj);
		return true;
	}

	return false;
}