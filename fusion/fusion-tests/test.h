#define PCRE2_CODE_UNIT_WIDTH 8

#include <iostream>
#include <functional>
#include <string.h>
#include <pcre2.h>

class regexp {
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
};