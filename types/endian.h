//detect endianess at compile time
#if 'abcd' == 0x61626364
#warning "little endian"
#elif 'abcd' == 0x64636261
#warning "Big endian"
#elif  'abcd' == 0x62616463
#warning "Mixed endian(PDP)"
#elif  'abcd' == 0x63646162
#warning "Mixed endian(Honeywell)"
#endif
