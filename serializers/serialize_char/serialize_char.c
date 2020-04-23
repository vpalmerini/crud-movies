unsigned char *serialize_char(unsigned char *buffer, char *value, int size)
{
    strncpy(buffer, value, size);
    return buffer + size;
}