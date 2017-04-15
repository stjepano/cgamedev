#ifndef ERR_H_
#define ERR_H_

typedef int error_t;

#ifndef NO_ERROR
#define NO_ERROR 0
#endif


/// Sets an error and returns error code.
/// 
///  Example:
///  error_t somefunc() {
///    if (error condition happens) return Error(233, "Description of error %d", some_number);
///    return NoError();  
///  }
error_t Error(error_t error_code, const char* msg, ...);

/// Get last error message
const char* GetError();

/// Clear error message
void ClearError();

#ifndef NoError
#define NoError() NO_ERROR
#endif



#endif // ERR_H_