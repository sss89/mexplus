#pragma once

#include "IMexPPWrappableClass.h"
#include "mexpp\MexPPStandardserializer.h"

class OneDoubleMexPPSerialization : IMexPPSerialization
{
public:
	OneDoubleMexPPSerialization() {};
	OneDoubleMexPPSerialization(const mxArray* data)
	{
		importFromMATLAB(data);
	}

	void setDouble(double d) { m_double = d; }
	double getDouble() const { return m_double; }

	virtual mxArray* exportToMATLAB() const;
	virtual void importFromMATLAB(const mxArray* data);
private:
	double m_double;
};

class OneDouble : public IMexPPWrappableClassT<MexPPStandardSerializer>
{
public:
	OneDouble() {};
	OneDouble(double d) : m_double(d) { };

	virtual ~OneDouble() {};

	double getDouble() const { return m_double; };
	void setDouble(double d) { m_double = d; };

	void multiply(double a) { m_double *= a; }

	virtual MexPPStandardSerializer serialize() const;
	virtual void unserialize(const MexPPStandardSerializer& data);

protected:

private:
	double m_double;
};