#ifndef __Z_MORE__H__
#define __Z_MORE__H__

// deflate压缩(支持压缩级别)
COMPRESS_IMP int compress_deflate OF((Bytef *dest,   uLongf *destLen,
									 const Bytef *source, uLong sourceLen,
									 int level));
// gzip压缩(支持压缩级别)
COMPRESS_IMP int compress_gzip OF((Bytef *dest,   uLongf *destLen,
                                  const Bytef *source, uLong sourceLen,
                                  int level));


// deflate格式解压(包含compress_deflate)
COMPRESS_IMP int uncompress_deflate OF((Bytef *dest,   uLongf *destLen,
									   const Bytef *source, uLong sourceLen));

// gzip格式解压(包含compress_gzip)
COMPRESS_IMP int uncompress_gzip OF((Bytef *dest,   uLongf *destLen,
									const Bytef *source, uLong sourceLen));



#endif
