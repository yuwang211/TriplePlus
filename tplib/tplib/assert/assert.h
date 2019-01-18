// assertion of fatal error
#ifdef TPL_DEBUG
#define Assert(exp, message) \
{ \
if (!(exp)) \
{ \
std::cerr << "Assertion failed: " << #exp << "\n" \
<< "Message: " << message << "\n" \
<< "line: " << __LINE__ << "\n" \
<< "file: " << __FILE__ << "\n"; \
exit(EXIT_FAILURE); \
} \
}
#else
#define Assert(exp, message)
#endif

// Warning
#ifdef TPL_DEBUG
#define Warning(exp, message) \
{ \
if (!(exp)) \
{ \
std::cerr << "Warning: " << #exp << "\n" \
<< "Message: " << message << "\n" \
<< "line: " << __LINE__ << "\n" \
<< "file: " << __FILE__ << "\n"; \
} \
}
#else
#define Warning(exp, message)
#endif

// Addition statement
#ifdef TPL_DEBUG
#define Debug(exp) exp
#else
#define Debug(exp)
#endif
