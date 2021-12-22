#ifndef _BASE_ACCOUNT_DEF_H_
#define _BASE_ACCOUNT_DEF_H_

#define MAX_ACCOUNT_NAME_LEN 128
#define MAX_ACCOUNT_PASSWORD_LEN 128

// Tip: szLoginResult
enum LOGIN_RESULT_CODE
{
    elrc_begin = 0,
    elrc_invalid = elrc_begin,

    elrc_success,
    elrc_version_error,
    elrc_account_repeat,

    elrc_end
};

#endif