#pragma once

#include "IMexPPWrappableClass.h"

class OneDoubleMexPPSerialization
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
//
//template <IMexPPSerialization SerializationClass>
//class IMexPPWrappableClassT <SerializationClass>
//{
//public:
//	virtual SerializationClass serialize() const = 0;
//	virtual void unserialize(const SerializationClass& data) = 0;
//};

class OneDouble : public IMexPPWrappableClassT<OneDoubleMexPPSerialization>
{
public:
	OneDouble() {};
	OneDouble(double d) : m_double(d) { };

	virtual ~OneDouble() {};

	double getDouble() const { return m_double; };
	void setDouble(double d) { m_double = d; };

	void multiply(double a) { m_double *= a; }

	virtual OneDoubleMexPPSerialization serialize() const;
	virtual void unserialize(const OneDoubleMexPPSerialization& data);

protected:

private:
	double m_double;
};