unsigned char *deserialize_int(unsigned char *buffer, int *value)
{
    *value = buffer[0];
    *value = *value << 8;
    *value = buffer[1];
    *value = *value << 8;
    *value = buffer[2];
    *value = *value << 8;
    *value = buffer[3];

    return buffer + 4;
}