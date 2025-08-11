#pragma once


    // Utility functions for characters and strings

    const char * trim_front(const char *str);
    void trim_back(char *str);
    char * trim(char *str);

    char to_upper(char c);
    _Bool is_digit(char c);
    _Bool is_letter(char c);
    _Bool is_space(char c);
    _Bool in_range(char c, char min, char max);
    _Bool starts_with(const char *string, const char *prefix);
    _Bool equals(const char *string1, const char *string2);

    int char_index(const char *string, char c);

    // Text message formatting: 
    //   - replaces lowercase letters with uppercase
    //   - merges consecutive spaces into single space
    void fmtmsg(char *msg_out, const char *msg_in);

    // Parse a 2 digit integer from string
    int dd_to_int(const char *str, int length);

    // Convert a 2 digit integer to string
    void int_to_dd(char *str, int value, int width, _Bool full_sign);

    char charn(int c, int table_idx);
    int nchar(char c, int table_idx);
