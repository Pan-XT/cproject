/* Default value is 14, for 16KB, which nicely fits into Intel x86 L1 cache��
 * Increasing memory usage improves compression ratio
 * Reduced memory usage can improve speed, due to cache effect
 */

#define MEMORY_USAGE 14
#define LZ4_HASHLOG (MEMORY_USAGE - 2) /* ��ϣͰλ��12 */
#define HASHTABLESIZE (1 << MEMORY_USAGE) /* ��ϣ���С2^14 = 16K */
#define HASHNBCELLS4 (1 << LZ4_HASHLOG) /* ��ϣͰ����2^12 = 4K */
#define FORCE_INLINE inline



typedef enum { byPtr,
               byU32, byU16
             } tableType_t;

FORCE_INLINE int LZ4_hashSequence(U32 sequence, tableType_t tableType)
{
    if (tableType == byU16)
        /* ��ϣ��Ϊ16K�������ϣvalueΪ16λ => ��ϣkeyΪ13λ */
        return (((sequence) * 2654435761U) >> ((MINMATCH * 8) - (LZ4_HASHLOG + 1)));
    else
        /* ��ϣ��Ϊ16K�������ϣvalueΪ32λ => ��ϣkeyΪ12λ */
        return (((sequence) * 2654435761U) >> ((MINMATCH * 8) - LZ4_HASHLOG));
}


FORCE_INLINE int LZ4_hashPosition(const BYTE *p, tableType_t tableType)
{
    return LZ4_hashSequence(A32(p), tableType);
}

FORCE_INLINE void LZ4_putPositionOnHash(const BYTE *p, U32 h, void *tableBase, tableType_t tableType,
                                        const BYTE *srcBase)
{
    switch(tableType)
    {
    case byPtr:
    {
        const BYTE **hashTable = (const BYTE **) tableBase;
        hashTable[h] = p;
        break;
    }
    case byU32:
    {
        U32 *hashTable = (U32 *) tableBase;
        hashTable[h] = (U32) (p - srcBase);
        break;
    }
    case byU16:
    {
        U16 *hashTable = (U16 *) tableBase;
        hashTable[h] = (U16) (p - srcBase);
        break;
    }
    }
}


FORCE_INLINE void LZ4_putPosition(const BYTE *p, void *tableBase, tableType_t tableType, const BYTE *srcBase)
{
    U32 h = LZ4_hashPosition(p, tableType); /* �����ϣֵ */
    LZ4_putPositionOnHash(p, h, tableBase, tableType, srcBase); /* �ѵ�ַ�����ϣ�� */
}


FORCE_INLINE const BYTE *LZ4_getPositionOnHash(U32 h, void *tableBase, tableType_t tableType,
        const BYTE *srcBase)
{
    if (tableType == byPtr)
    {
        const BYTE **hashTable = (const BYTE **) tableBase;
        return hashTable[h];
    }
    if (tableType == byU32)
    {
        U32 *hashTable = (U32 *) tableBase;
        return hashTable[h] + srcBase;
    }
    {
        U16 *hashTable = (U16 *) tableBase;    /* default, to ensure a return */
        return hashTable[h] + srcBase;
    }
}


FORCE_INLINE const BYTE *LZ4_getPosition(const BYTE *p, void *tableBase, tableType, const BYTE *srcBase)
{
    U32 h = LZ4_hashPosition(p, tableType);
    return LZ4_getPositionOnHash(h, tableBase, tableType, srcBase);
}

/* LZ4_compress():
 * Compress inputSize bytes from source into dest.
 * Destination buffer must be already allocated, and must be sized to handle worst cases situations
 * (input data not compressible)
 * Worst case size evaluation is provided by function LZ4_compressBound()
 * inputSize: Max support value is LZ4_MAX_INPUT_VALUE
 * return: the number of bytes written in buffer dest or 0 if the compression fails.
 */

int LZ4_compress(const char *source, char *dest, int inputSize)
{
#if (HEAPMODE) /* �ڶ��и���ϣ������ڴ� */
    void *ctx = ALLOCATOR(HASHNBCELLS4, 4); /* Aligned on 4-bytes boundaries */
#else /* ��ջ�и���ϣ������ڴ棬�ȽϿ죬Ĭ�� */
    U32 ctx[1U << (MEMORY_USAGE - 2) ] = {0}; /* Ensure data is aligned on 4-bytes boundaries */
#endif
    int result;

    /* ����С��64K+11������16λ����ʾ�������ڣ�������32λ*/
    if (inputSize < (int) LZ4_64KLIMIT)
        result = LZ4_compress_generic((void *)ctx, source, dest, inputSize, 0, notLimited, byU16, noPrefix);
    else
        result = LZ4_compress_generic((void *)ctx, source, dest, inputSize, 0, notLimited,
                                      (sizeof(void *) == 8 ? byU32 : byPtr, noPrefix);

#if (HEAPMODE)
                                      FREE(ctx);
#endif
                                      return result;
}



#define MINMATCH 4 /* ��4�ֽ�Ϊ��λ���ҹ�ϣ�� */
#define COPYLENGTH 8
#define LASTLITERALS 5
#define MFLIMIT (COPYLENGTH + MINMATCH) /* ��������12���ֽڣ������в���ƥ�� */
         const int LZ4_minLength = (MFLIMIT + 1); /* һ����Ҫ>=13���ַ����Ż���в���ƥ�� */
#define LZ4_64KLIMIT ((1<<16) + (MFLIMIT - 1)) /* 64K + 11 */
/* Increasing this value will make the compression run slower on incompressible data��
 * ���ڿ��Ʋ���ƥ��ʱ��ǰ�����ȣ����һֱû�ҵ�ƥ�䣬��Ӵ�ǰ�����ȡ�
 */
#define SKIPSTRENGTH 6


FORCE_INLINE int LZ4_compress_generic(void *ctx, const char *source, char *dest, int inputSize,
                                      int maxOutputSize, limitedOutput_directive limitedOutput, tableType_t tableType,
                                      prefix64k_directive prefix)
{
    const BYTE *ip = (const BYTE *) source;
    /* ������ϣ���е�srcBase */
    const BYTE *const base = (prefix == withPrefix) ? ((LZ4_Data_Structure *)ctx)->base : (const BYTE *)source);
    /* ǰ�򴰿ڵ���ʼ��ַ */
    const BYTE *const lowLimit = ((prefix == withPrefix) ? ((LZ4_Data_Structure *)ctx)->bufferStart : (const BYTE *)source);
    const BYTE *anchor = (const BYTE *)source;
    const BYTE *const iend = ip + inputSize; /* ����Ľ�����ַ */
    const BYTE *const mflimit = iend - MFLIMIT; /* iend - 12�������˴�������������һ��ƥ�� */
    const BYTE *const matchlimit = iend - LASTLITERALS; /* iend - 5�����5���ַ�������ƥ�� */

    BYTE *op = (BYTE *) dest; /* ���ڲ���������� */
    BYTE *const oend = op + maxOutputSize; /* �������ı߽磬����еĻ� */

    int length;
    const int skipStrength = SKIPSTRENGTH; /* 6 */
    U32 forwardH;

    /* Init conditions */
    if ((U32) inputSize > (U32) LZ4_MAX_INPUT_SIZE) return 0; /* ���볤�ȹ��� */
        /* must continue from end of previous block */
        if ((prefix == withPrefix) && (ip != ((LZ4_Data_Structure *)ctx)->nextBlock)) return 0;
            /* do it now, due to potential early exit. ������һ�������ʼ��ַ */
            if (prefix == withPrefix) ((LZ4_Data_Structure *)ctx)->nextBlock = iend;
                if ((tableType == byU16) && (inputSize >= LZ4_64KLIMIT)) return 0; /* Size too large (not within 64K limit) */
                    if (inputSize < LZ4_minlength) goto _last_literals; /* ������볤��С��13���򲻲���ƥ�� */

                    /* First Byte */
                    LZ4_putPosition(ip, ctx, tableType, base); /* �����Ե�һ���ֽڿ�ͷ��U32�Ĺ�ϣֵ��������λ�� */
                    ip++;
                    forwardH = LZ4_hashPosition(ip, tableType); /* �����Եڶ����ֽڿ�ͷ��U32�Ĺ�ϣֵ */

                    /* Main loop��ÿ��ѭ������һ��ƥ�䣬����һ������ */
                    for ( ; ; )
{
    int findMatchAttempts = (1U << skipStrength) + 3;
        const BYTE *forwardIp = ip;
        const BYTE *ref;
        BYTE *token;

        /* Find a match������һ��ƥ�䣬���ߵ��˾�ͷmflimit */
        do
        {
            U32 h = forwardH; /* ��ǰip��Ӧ�Ĺ�ϣֵ */
            int step = findMatchAttempts++ >> skipStrength; /* forwardIp��ƫ�ƣ�һ����1 */
            ip = forwardIp;
            forwardIp = ip + step; /* ǰ�򻺴����¸������ĵ�ַ */

            if unlikely(forwardIp > mflimit)
            {
                goto _last_literals;    /* >=12�ֽڲŻ�ȥƥ�� */
            }
            forwardH = LZ4_hashPosition(forwardIp, tableType); /* forwardIp�Ĺ�ϣֵ */

            /* �����ǲ��ҵĹؼ������չ�ϣֵh����ȡ��ַref��
             * 1. û��ƥ�䣬refΪsrcBase��
             * 2. ��ƥ�䡣
             *     2.1 ���ڻ��������ڣ�������
             *     2.2 ��Ӧ��U32��һ�����ǳ�ͻ��������
             *     2.3 �ڻ��������ڣ��Ҷ�Ӧ��U32һ�����ҵ���match���˳���
             */
            ref = LZ4_getPositionOnHash(h, ctx, tableType, base);
            LZ4_putPositionOnHash(ip, h, ctx, tableType, base); /* ����ip��h�����Ӧ��ϵ */
        }
        while ((ref + MAX_DISTANCE < ip) || (A32(ref) != A32(ip)));

        /* �ҵ�ƥ��֮�󣬿��ܷ���ǰ����ƥ�� */
        while((ip > anchor) && (ref > lowLimit) && unlikely(ip[-1] == ref[-1]))
        {
            ip--;
            ref--;
        }

        /* Encode Literal length����ֵLiteral length */
        length = (int) (ip - anchor);
        token = op++;

        /* Check output limit */
        if ((limitedOutput) & unlikely(op + length + 2 + (1 + LASTLITERALS) + (length>>8) > oend)) return 0;

        if (length >= (int) RUN_MASK)
        {
            int len = length - RUN_MASK;
            *token = (RUN_MASK << ML_BITS);
            for(; len >= 255; len -= 255) *op++ = 255;
            *op++ = (BYTE) len;
        }
        else
            *token = (BYTE) (length << ML_BITS);

        /* Copy Literals�����Ʋ��ɱ����ַ� */
        {
            BYTE * end = (op) + (length);
            LZ4_WILDCOPY(op, anchor, end);
            op = end;
        }

_next_match: /* �����չƥ�� */
        /* Encode Offset����ֵoffset��op += 2 */
        LZ4_WRITE_LITTLEENDIAN_16(op, (U16) (ip - ref));

        /* Start Counting */
        ip += MINMATCH;
        ref += MINMATCH; /* MinMatch already verified */
        anchor = ip;

        while likely(ip < matchlimit - (STEPSIZE - 1))
        {
            size_t diff = AARCH(ref) ^ AARCH(ip); /* ���ֵΪ���ʾ��ͬ */
            if (! diff)
            {
                ip += STEPSIZE;
                ref += STEPSIZE;
                continue;
            }
            ip += LZ4_NbCommonBytes(diff); /* STEPSIZE��ͬ���������ж��ٸ��ֽ�����ͬ�� */
            goto _endCount;
        }

        if (LZ4_ARCH64)
            if ((ip < (matchlimit - 3)) && (A32(ref) == A32(ip)))
            {
                ip += 4;
                ref += 4;
            }
        if ((ip < matchlimit - 1)) && (A16(ref) == A16(ip)))
        {
            ip += 2;
            ref += 2;
        }
        if ((ip < matchlimit) && (*ref == *ip)) ip++;

_endCount:
            /* Ecode MatchLength����ֵmatch length */
            length = (int) (ip - anchor);
            /* Check output limit */
            if ((limitedOutput) && unlikely(op + (1 + LASTLITERALS) + (length >> 8) > oend)) return 0;

                if (length >= (int) ML_MASK)
                {
                    *token += ML_MASK;
                    length -= ML_MASK;
                    for (; length > 509; length -= 510)
                    {
                        *op++ = 255;
                        *op++ = 255;
                    }
                    if (length >= 255)
                    {
                        length -= 255;
                        *op++ = 255;
                    }
                    *op++ = (BYTE) (length);
                }
                else
                    *token += (BYTE) (length);

                    /* Test end of chunk */
                    if (ip > mflimit)
                {
                    anchor = ip;    /* ���ٽ���ƥ���� */
                    break;
                }
    /* Fill table��˳�㱣�� */
    LZ4_putPosition(ip - 2, ctx, tableType, base);

    /* Test next position����������ƥ�� */
    ref = LZ4_getPosition(ip, ctx, tableType, base);
    LZ4_putPosition(ip, ctx, tableType, base);
    /* ����ҵ�ƥ�䣬˵��û��literals������ֱ���������ҡ���ֵliteral length */
    if ((ref + MAX_DISTANCE >= ip) && (A32(ref) == A32(ip)))
        {
            token = op++;
            *token = 0;
            goto _next_match;
        }

        /* Prepare next loop��׼�������¸�ѭ�� */
        anchor = ip++;
        forwardH = LZ4_hashPosition(ip, tableType);
    }

_last_literals:
    /* Encode Last Literals */
    {
        int lastRun = (int) (iend - anchor); /* ���ԭ�ַ������� */

        if ((limitedOutput) && (((char *)op - dest) + lastRun + 1 + ((lastRun + 255 - RUN_MASK) / 255) >
                                (U32) maxOutputSize))
            return 0; /* check output limit */

        if (lastRun >= (int) RUN_MASK)
        {
            *op ++ = (RUN_MASK << ML_BITS);
            lastRun -= RUN_MASK;
            for (; lastRun >= 255; lastRun -=255) *op++ = 255;
            *op++ = (BYTE) lastRun;
        }
        else
            *op++ = (BYTE) (lastRun << ML_BITS);

        memcpy(op, anchor, iend - anchor); /* ����literals */
        op += iend - anchor;
    }

    /* End */
    return (int) (((char *)op) - dest); /* ����ѹ����ĳ��� */
}

#define LZ4_MAX_INPUT_SIZE 0x7E000000 /* 2 113 929 216 bytes */
#define ML_BITS 4 /* Token: 4-low-bits, match length */
#define ML_MASK ((1U << ML_BITS) - 1)
#define RUN_BITS (8 - ML_BITS) /* Token: 4-high-bits, literal length */
#define RUN_MASK ((1U << RUN_BITS) - 1)

#define MAXD_LOG 16 /* �������ڵ�λ�� */
#define MAX_DISTANCE ((1 << MAXD_LOG) - 1) /* �������ڵ����ֵ */
