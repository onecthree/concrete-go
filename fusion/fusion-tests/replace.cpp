#include <iostream>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

int main() {
    int error;
    PCRE2_SIZE erroffset;
    const PCRE2_SPTR subject = (PCRE2_SPTR)"%phpp echo 123; %~php <title>%php echo 889; %~php</title>";

    std::string list_pattern;
    list_pattern += "(?<openif>\\%php\\s+)|";
    list_pattern += "(?<closeif>\\%\\~php)";
    const PCRE2_SPTR pattern = reinterpret_cast<const unsigned char *>(list_pattern.c_str());
    
    std::string list_replacement;
    list_replacement += "${openif:+\\<\\?php}";
    list_replacement += "${closeif:+\\?\\>}";
    const PCRE2_SPTR replacement = reinterpret_cast<const unsigned char *>(list_replacement.c_str());

    pcre2_code *re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &error, &erroffset, 0);
    if (re == 0)
        return 1;

    pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);

    PCRE2_UCHAR output[1024] = "";
    PCRE2_SIZE outlen = sizeof(output) / sizeof(PCRE2_UCHAR);

    int rc = pcre2_substitute(re, subject, PCRE2_ZERO_TERMINATED, 0, PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED, 0, 0, replacement, PCRE2_ZERO_TERMINATED, output, &outlen);
    if (rc >= 0)
        printf("%s\n", output);

    pcre2_code_free(re);
    return 0;
}