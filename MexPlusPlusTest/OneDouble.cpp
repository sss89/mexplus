
#include "OneDouble.h"

MexPPStandardSerializer OneDouble::serialize() const
{
	MexPPStandardSerializer res;
	res.setField("m_double", m_double);
	return res;
}

void OneDouble::unserialize(const MexPPStandardSerializer& data)
{
	m_double = data.getField<double>("m_double");
}


mxArray* OneDoubleMexPPSerialization::exportToMATLAB() const
{
	mxArray* res = mxCreateDoubleMatrix(1, 1, mxREAL);
	double* ptr = static_cast<double*>(mxGetData(res));
	ptr[0] = m_double;
	return res;
}

void OneDoubleMexPPSerialization::importFromMATLAB(const mxArray* data)
{
	double* ptr = static_cast<double*>(mxGetData(data));
	m_double = ptr[0];
}