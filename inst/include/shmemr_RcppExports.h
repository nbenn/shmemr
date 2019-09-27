// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#ifndef RCPP_shmemr_RCPPEXPORTS_H_GEN_
#define RCPP_shmemr_RCPPEXPORTS_H_GEN_

#include <Rcpp.h>

namespace shmemr {

    using namespace Rcpp;

    namespace {
        void validateSignature(const char* sig) {
            Rcpp::Function require = Rcpp::Environment::base_env()["require"];
            require("shmemr", Rcpp::Named("quietly") = true);
            typedef int(*Ptr_validate)(const char*);
            static Ptr_validate p_validate = (Ptr_validate)
                R_GetCCallable("shmemr", "_shmemr_RcppExport_validate");
            if (!p_validate(sig)) {
                throw Rcpp::function_not_exported(
                    "C++ function with signature '" + std::string(sig) + "' not found in shmemr");
            }
        }
    }

    inline Rcpp::List mem_init(std::string name, double length, std::string type) {
        typedef SEXP(*Ptr_mem_init)(SEXP,SEXP,SEXP);
        static Ptr_mem_init p_mem_init = NULL;
        if (p_mem_init == NULL) {
            validateSignature("Rcpp::List(*mem_init)(std::string,double,std::string)");
            p_mem_init = (Ptr_mem_init)R_GetCCallable("shmemr", "_shmemr_mem_init");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_mem_init(Shield<SEXP>(Rcpp::wrap(name)), Shield<SEXP>(Rcpp::wrap(length)), Shield<SEXP>(Rcpp::wrap(type)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<Rcpp::List >(rcpp_result_gen);
    }

    inline void mem_attach(SEXP x) {
        typedef SEXP(*Ptr_mem_attach)(SEXP);
        static Ptr_mem_attach p_mem_attach = NULL;
        if (p_mem_attach == NULL) {
            validateSignature("void(*mem_attach)(SEXP)");
            p_mem_attach = (Ptr_mem_attach)R_GetCCallable("shmemr", "_shmemr_mem_attach");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_mem_attach(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

    inline void mem_detach(SEXP x) {
        typedef SEXP(*Ptr_mem_detach)(SEXP);
        static Ptr_mem_detach p_mem_detach = NULL;
        if (p_mem_detach == NULL) {
            validateSignature("void(*mem_detach)(SEXP)");
            p_mem_detach = (Ptr_mem_detach)R_GetCCallable("shmemr", "_shmemr_mem_detach");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_mem_detach(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

    inline bool is_mem_attached(SEXP x) {
        typedef SEXP(*Ptr_is_mem_attached)(SEXP);
        static Ptr_is_mem_attached p_is_mem_attached = NULL;
        if (p_is_mem_attached == NULL) {
            validateSignature("bool(*is_mem_attached)(SEXP)");
            p_is_mem_attached = (Ptr_is_mem_attached)R_GetCCallable("shmemr", "_shmemr_is_mem_attached");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_is_mem_attached(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<bool >(rcpp_result_gen);
    }

    inline SEXP get_mem_ptr(SEXP x) {
        typedef SEXP(*Ptr_get_mem_ptr)(SEXP);
        static Ptr_get_mem_ptr p_get_mem_ptr = NULL;
        if (p_get_mem_ptr == NULL) {
            validateSignature("SEXP(*get_mem_ptr)(SEXP)");
            p_get_mem_ptr = (Ptr_get_mem_ptr)R_GetCCallable("shmemr", "_shmemr_get_mem_ptr");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_get_mem_ptr(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<SEXP >(rcpp_result_gen);
    }

    inline std::string get_mem_str(SEXP x) {
        typedef SEXP(*Ptr_get_mem_str)(SEXP);
        static Ptr_get_mem_str p_get_mem_str = NULL;
        if (p_get_mem_str == NULL) {
            validateSignature("std::string(*get_mem_str)(SEXP)");
            p_get_mem_str = (Ptr_get_mem_str)R_GetCCallable("shmemr", "_shmemr_get_mem_str");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_get_mem_str(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<std::string >(rcpp_result_gen);
    }

    inline double get_mem_length(SEXP x) {
        typedef SEXP(*Ptr_get_mem_length)(SEXP);
        static Ptr_get_mem_length p_get_mem_length = NULL;
        if (p_get_mem_length == NULL) {
            validateSignature("double(*get_mem_length)(SEXP)");
            p_get_mem_length = (Ptr_get_mem_length)R_GetCCallable("shmemr", "_shmemr_get_mem_length");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_get_mem_length(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<double >(rcpp_result_gen);
    }

    inline std::string get_mem_id(SEXP x) {
        typedef SEXP(*Ptr_get_mem_id)(SEXP);
        static Ptr_get_mem_id p_get_mem_id = NULL;
        if (p_get_mem_id == NULL) {
            validateSignature("std::string(*get_mem_id)(SEXP)");
            p_get_mem_id = (Ptr_get_mem_id)R_GetCCallable("shmemr", "_shmemr_get_mem_id");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_get_mem_id(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<std::string >(rcpp_result_gen);
    }

    inline void mem_remove(SEXP x) {
        typedef SEXP(*Ptr_mem_remove)(SEXP);
        static Ptr_mem_remove p_mem_remove = NULL;
        if (p_mem_remove == NULL) {
            validateSignature("void(*mem_remove)(SEXP)");
            p_mem_remove = (Ptr_mem_remove)R_GetCCallable("shmemr", "_shmemr_mem_remove");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_mem_remove(Shield<SEXP>(Rcpp::wrap(x)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

    inline void mem_resize(SEXP x, double new_length) {
        typedef SEXP(*Ptr_mem_resize)(SEXP,SEXP);
        static Ptr_mem_resize p_mem_resize = NULL;
        if (p_mem_resize == NULL) {
            validateSignature("void(*mem_resize)(SEXP,double)");
            p_mem_resize = (Ptr_mem_resize)R_GetCCallable("shmemr", "_shmemr_mem_resize");
        }
        RObject rcpp_result_gen;
        {
            RNGScope RCPP_rngScope_gen;
            rcpp_result_gen = p_mem_resize(Shield<SEXP>(Rcpp::wrap(x)), Shield<SEXP>(Rcpp::wrap(new_length)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

}

#endif // RCPP_shmemr_RCPPEXPORTS_H_GEN_
