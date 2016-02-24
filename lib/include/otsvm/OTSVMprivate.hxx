
#ifndef OTSVM_PRIVATE_HXX
#define OTSVM_PRIVATE_HXX

/* From http://gcc.gnu.org/wiki/Visibility */
/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
#define OTSVM_HELPER_DLL_IMPORT __declspec(dllimport)
#define OTSVM_HELPER_DLL_EXPORT __declspec(dllexport)
#define OTSVM_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OTSVM_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OTSVM_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OTSVM_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OTSVM_HELPER_DLL_IMPORT
#define OTSVM_HELPER_DLL_EXPORT
#define OTSVM_HELPER_DLL_LOCAL
#endif
#endif

/* Now we use the generic helper definitions above to define OTSVM_API and OTSVM_LOCAL.
 * OTSVM_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * OTSVM_LOCAL is used for non-api symbols. */

#ifndef OTSVM_STATIC /* defined if OT is compiled as a DLL */
#ifdef OTSVM_DLL_EXPORTS /* defined if we are building the OT DLL (instead of using it) */
#define OTSVM_API OTSVM_HELPER_DLL_EXPORT
#else
#define OTSVM_API OTSVM_HELPER_DLL_IMPORT
#endif /* OTSVM_DLL_EXPORTS */
#define OTSVM_LOCAL OTSVM_HELPER_DLL_LOCAL
#else /* OTSVM_STATIC is defined: this means OT is a static lib. */
#define OTSVM_API
#define OTSVM_LOCAL
#endif /* !OTSVM_STATIC */


#endif // OTSVM_PRIVATE_HXX

