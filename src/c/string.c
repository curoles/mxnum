/// Repeat string N times.
bool string_repeat(char* buf, size_t buf_len, const char* str,
    const char* delim, size_t times)
{
    size_t str_len = strlen(str), delim_len = strlen(delim);
    size_t required_len = (str_len + delim_len) * times;
    if (buf_len < required_len || times == 0) {
        return false;
    }

    strcpy(buf, str);
    buf_len -= str_len;

    for (size_t i = 1; i < times; i++) {
        strncat(buf, delim, buf_len);
        buf_len -= delim_len;
        strncat(buf, str, buf_len);
        buf_len -= str_len;
    }

    return true;
}

size_t strlen(const char* str)
{
    const char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

unsigned int atoui(const char* s)
{
    unsigned int res = 0;

    while (*s == ' ') { // Ignore leading whitespaces
        s++;
    }

    while (*s >= '0' && *s <= '9') {
        
        unsigned int digit = *s - '0';
    
        // Handling overflow
        if (res > UINT_MAX / 10 || (res == UINT_MAX / 10 && digit > 7)) {
            return UINT_MAX;
        }
      
        // Append current digit to the result
        res = 10 * res + digit;

        s++;
    }

    return res;
}