PHP_ARG_ENABLE(secure_int64, Whether to enable the secure_int64 extension, [ --enable-secure-int64 Enable secure_int64])

if test "$secure_int64" != "no"; then
    PHP_NEW_EXTENSION(secure_int64, secure_int64.c, $ext_shared)
fi
