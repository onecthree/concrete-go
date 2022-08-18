#pragma once

#define PCRE2_CODE_UNIT_WIDTH 8

#include <phpcpp.h>
#include <iostream>
#include <functional>
#include <string.h>
#include <pcre2.h>

class regexp: public Php::Base {
    public: void static match(const char *pattern_v, const char *subject_v, std::function<void(const char *)> cb) {
        int errorcode;
        size_t resultlen;
        PCRE2_SIZE erroroffset;
        PCRE2_UCHAR *result;
        PCRE2_SPTR pattern = reinterpret_cast<const unsigned char *>(pattern_v);
        PCRE2_SPTR subject = reinterpret_cast<const unsigned char *>(subject_v);   
        pcre2_code *regexp = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS | PCRE2_UTF, &errorcode, &erroroffset, NULL);

        if(regexp) {
            pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(regexp, NULL);

            if(pcre2_match(regexp, subject, strlen((char *)subject), 0, 0, match_data, NULL) >= 0) {
                pcre2_substring_get_bynumber(match_data, 0, &result, &resultlen);
            } else {
                result = NULL;
                resultlen = 0;
            }

            pcre2_match_data_free(match_data);
            pcre2_code_free(regexp);
        } else {
            PCRE2_UCHAR error[256];
            pcre2_get_error_message(errorcode, error, sizeof(error));
        }

        result ? cb((char *)result) : void();
    }

    public: void static replace(const char *pattern_v, const char *subject_v, const char *replacement_v, std::function<void(const char *)> cb) {
        int error;
        PCRE2_SIZE erroffset;

        const PCRE2_SPTR subject = reinterpret_cast<const unsigned char *>(subject_v);  
        const PCRE2_SPTR pattern = reinterpret_cast<const unsigned char *>(pattern_v);
        const PCRE2_SPTR replacement = reinterpret_cast<const unsigned char *>(replacement_v);

        pcre2_code *re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &error, &erroffset, 0);
        if (re == 0)
            return void();

        pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);

        PCRE2_UCHAR result[1024] = "";
        PCRE2_SIZE outlen = sizeof(result) / sizeof(PCRE2_UCHAR);

        int rc = pcre2_substitute(re, subject, PCRE2_ZERO_TERMINATED, 0, PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED, 0, 0, replacement, PCRE2_ZERO_TERMINATED, result, &outlen);

        // if (rc >= 0)
        //     printf("%s\n", result);

        pcre2_code_free(re);

        rc ? cb((char *)result) : void();

    }
};