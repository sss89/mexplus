#include "mex.h" 
#include "OneDouble.h"
#include "class_handle.h"
#include "mexpp_class_model.h"
#include "AssertionError.h"

const size_t MAX_COMMAND_LEN = 256;
typedef OneDoubleMexPPSerialization SerializationType;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	try {
		VERIFY(nrhs > 0);

		VERIFY(mxIsChar(prhs[0]));

		char class_name[MAX_COMMAND_LEN + 1];
		if (nrhs < 1 || mxGetString(prhs[0], class_name, sizeof(class_name)))
		{
			// TODO: change the 256 to MAX_COMMAND_LEN using sprintf
			mexErrMsgTxt("First input should be a class name less than 256 characters long.");
		}


		char cmd[MAX_COMMAND_LEN + 1];
		if (nrhs < 2 || mxGetString(prhs[1], cmd, sizeof(cmd)))
		{
			// TODO: change the 256 to MAX_COMMAND_LEN using sprintf
			mexErrMsgTxt("First input should be a command less than 256 characters long.");
		}

		if (!strcmp("OneDouble", class_name)) {
			if (!strcmp("New", cmd)) {
				VERIFY(nrhs > 2);
				VERIFY(nlhs == 1);

				double* ptr = static_cast<double *>(mxGetData(prhs[2]));
				plhs[0] = convertPtr2Mat<OneDouble>(new OneDouble(ptr[0]));
			}

			parseRegularFunctions<OneDouble, SerializationType>(cmd, nlhs, plhs, nrhs, prhs);

			if (!strcmp("Mult", cmd)) {
				VERIFY(nrhs > 3);
				OneDouble* obj = convertMat2Ptr<OneDouble>(prhs[2]);

				double *ptr = static_cast<double *>(mxGetData(prhs[3]));
				obj->multiply(ptr[0]);
			}

			if (!strcmp("GetDouble", cmd)) {
				VERIFY(nrhs > 2);
				VERIFY(nlhs == 1);

				OneDouble* obj = convertMat2Ptr<OneDouble>(prhs[2]);
				plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
				double* ptr = static_cast<double*>(mxGetData(plhs[0]));
				ptr[0] = obj->getDouble();
			}
		}
	}
	catch (AssertionError& e) {
		mexErrMsgTxt((std::string("Assertion: ") + std::string(e.what())).c_str());
	}
}