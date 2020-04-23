unsigned char *deserialize_char(unsigned char *buffer, char *value, int size)
{
    strncpy(value, (char *)buffer, size);
    return buffer + size;
}