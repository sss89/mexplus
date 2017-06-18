
#include "OneDouble.h"

OneDoubleMexPPSerialization OneDouble::serialize() const
{
	OneDoubleMexPPSerialization res;
	res.setDouble(m_double);
	return res;
}

void OneDouble::unserialize(const OneDoubleMexPPSerialization& data)
{
	m_double = data.getDouble();
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