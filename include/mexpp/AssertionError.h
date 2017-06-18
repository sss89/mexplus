#pragma once

#include <exception>

#include <string>
#include <sstream>

using std::exception;

class AssertionError : public exception
	{
	public:
		AssertionError(const char* cond, int line, const char* file) throw() : m_cond(cond), m_file(file) {
			m_line = std::to_string(line);
 			std::stringstream s("Assertion of (");
			s << m_cond << " failed on line " << m_line << " in file " << m_file;
			m_what = s.str();
		}

		virtual const char* what() const throw() {
			return m_what.c_str();
		}

		void append(const std::string& str_to_add) {
			std::stringstream s;
			s << m_what << std::endl << str_to_add;
			m_what = s.str();
		}
	private:
		std::string m_cond, m_line, m_file, m_what;
	};

#ifdef _DEBUG
#define ASSERT(cond)		if(!(cond)) throw AssertionError(#cond, __LINE__, __FILE__)
#else
#define    ASSERT(x)
#endif

#define _DEBUG_VERIFY

#ifdef _DEBUG_VERIFY
//#define    VERIFY(x)                assert(x)
#define VERIFY(cond)		if(!(cond)) throw AssertionError(#cond, __LINE__, __FILE__)
#else
#define    VERIFY(x)
#endif

#define VERIFY_ALWAYS(cond)   if(!(cond)) throw AssertionError(#cond, __LINE__, __FILE__)
