#pragma once
#include "mex.h"

//class IMexPPSerialization
//{
//public:
//	IMexPPSerialization();
//	IMexPPSerialization(const mxArray* data)
//	{
//		importFromMATLAB(data);
//	}
//
//	virtual mxArray* exportToMATLAB() const = 0;
//	virtual void importFromMATLAB(const mxArray* data) = 0;
//};

// TODO (uriel): can we make the template parameter to inherit from IMexPPSerialization
template <class SerializationClass>
class IMexPPWrappableClassT
{
public:
	IMexPPWrappableClassT() {};

	virtual SerializationClass serialize() const = 0;
	virtual void unserialize(const SerializationClass& data) = 0;

protected:
};
