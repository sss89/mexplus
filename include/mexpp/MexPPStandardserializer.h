#pragma once

#include "mexpp/arguments.h"
#include "mexpp/AssertionError.h"
#include "mexpp/IMexPPWrappableClass.h"
#include <unordered_map>

class MexPPStandardSerializer : IMexPPSerialization{
public:

	template <class T>
	void setField(const std::string& field_name, const T& data);

	template <class T>
	T getField(const std::string& field_name) const;

	template <class T>
	void getField(const std::string& field_name, T* data) const;

	virtual mxArray* exportToMATLAB() const {
		// init fieldnames
		const char** all_fieldnames;
		size_t num_fields = m_map.size();
		all_fieldnames = static_cast<const char**>(mxCalloc(num_fields, sizeof(*all_fieldnames)));
		const char** fieldname_ptr = all_fieldnames;
		for (auto it = m_map.begin(); it != m_map.end(); ++it, ++fieldname_ptr) {
			(*fieldname_ptr) = it->first.c_str();
		}

		// create struct with the given fieldnames
		mxArray* res = mxCreateStructMatrix(1, 1, m_map.size(), all_fieldnames);

		// release field names
		mxFree(static_cast<void *>(all_fieldnames));

		// set fields and return
		for (auto it = m_map.begin(); it != m_map.end(); ++it) {
			mxSetField(res, 0, it->first.c_str(), it->second);
		}
		return res;
	}

	virtual void importFromMATLAB(const mxArray* data) {
		VERIFY(mxIsStruct(data));
		VERIFY(!mxIsEmpty(data));
		VERIFY(mxGetNumberOfElements(data) == 1);

		for (size_t i = 0; i < mxGetNumberOfFields(data); ++i) {
			std::string fieldname(mxGetFieldNameByNumber(data, i));
			mxArray* val = mxGetFieldByNumber(data, 0, i);
			m_map[fieldname] = val;
		}
	}
private:
	std::unordered_map<std::string, mxArray*> m_map;
};

template <class T>
void MexPPStandardSerializer::setField(const std::string& field_name, const T& data) {
	m_map[field_name] = mexplus::MxArray::from(data);
}

template <class T>
T MexPPStandardSerializer::getField(const std::string& field_name) const {
	auto it = m_map.find(field_name);
	VERIFY(it != m_map.end());
	return mexplus::MxArray::to<T>(it->second);
}

template <class T>
void MexPPStandardSerializer::getField(const std::string& field_name, T* data) const {
	auto it = m_map.find(field_name);
	VERIFY(it != m_map.end());
	mexplus::MxArray::to<T>(it->second, data);
}