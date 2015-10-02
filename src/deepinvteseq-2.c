/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf -m 100 --no-strlen deepinvteseq-2.gperf  */
/* Computed positions: -k'1-2' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 14 "deepinvteseq-2.gperf"
struct deepinvteseq_2_struct {
	char seq[3];
	DeepinvteTerminalSequenceHandler handler;
};
#include <string.h>
/* maximum key range = 77, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
/*ARGSUSED*/
static unsigned int
deepinvteseq_2_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 39, 77, 77, 32, 77,
      39, 77, 37, 33, 34, 36, 34, 77, 33, 77,
      77, 33, 33, 31, 32, 30, 77, 30, 40, 77,
      77, 77, 77, 77, 77, 77, 77, 50, 45,  1,
      27, 32, 41, 29,  7, 21,  5, 15, 49,  0,
      25, 77, 12, 13, 24, 11,  8,  2, 18, 37,
       9, 31, 77,  2, 11, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77
    };
  return asso_values[(unsigned char)str[1]+5] + asso_values[(unsigned char)str[0]];
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct deepinvteseq_2_struct *
deepinvteseq_2_lookup (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 74,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 2,
      MIN_HASH_VALUE = 0,
      MAX_HASH_VALUE = 76
    };

  static const struct deepinvteseq_2_struct wordlist[] =
    {
#line 247 "deepinvteseq-2.gperf"
      {"mh", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_mh)},
#line 166 "deepinvteseq-2.gperf"
      {"ch", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ch)},
#line 251 "deepinvteseq-2.gperf"
      {"mp", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_mp)},
#line 172 "deepinvteseq-2.gperf"
      {"cv", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cv)},
#line 285 "deepinvteseq-2.gperf"
      {"up", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_up)},
#line 246 "deepinvteseq-2.gperf"
      {"me", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_me)},
#line 165 "deepinvteseq-2.gperf"
      {"ce", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ce)},
#line 284 "deepinvteseq-2.gperf"
      {"ue", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ue)},
#line 163 "deepinvteseq-2.gperf"
      {"cc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 283 "deepinvteseq-2.gperf"
      {"uc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_uc)},
#line 170 "deepinvteseq-2.gperf"
      {"cs", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cs)},
#line 286 "deepinvteseq-2.gperf"
      {"us", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_us)},
#line 248 "deepinvteseq-2.gperf"
      {"mk", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_mk)},
#line 280 "deepinvteseq-2.gperf"
      {"te", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 167 "deepinvteseq-2.gperf"
      {"cl", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cl)},
#line 185 "deepinvteseq-2.gperf"
      {"ho", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ho)},
#line 274 "deepinvteseq-2.gperf"
      {"se", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_se)},
#line 282 "deepinvteseq-2.gperf"
      {"ts", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ts)},
#line 273 "deepinvteseq-2.gperf"
      {"sc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_sc)},
#line 276 "deepinvteseq-2.gperf"
      {"so", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_so)},
#line 224 "deepinvteseq-2.gperf"
      {"ke", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ke)},
#line 245 "deepinvteseq-2.gperf"
      {"md", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_md)},
#line 164 "deepinvteseq-2.gperf"
      {"cd", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cd)},
#line 288 "deepinvteseq-2.gperf"
      {"ve", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ve)},
#line 228 "deepinvteseq-2.gperf"
      {"ks", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ks)},
#line 168 "deepinvteseq-2.gperf"
      {"cm", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cm)},
#line 275 "deepinvteseq-2.gperf"
      {"sf", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_sf)},
#line 290 "deepinvteseq-2.gperf"
      {"vs", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_vs)},
#line 190 "deepinvteseq-2.gperf"
      {"ic", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ic)},
#line 244 "deepinvteseq-2.gperf"
      {"mb", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_mb)},
#line 162 "deepinvteseq-2.gperf"
      {"cb", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cb)},
#line 268 "deepinvteseq-2.gperf"
      {"rc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_rc)},
#line 171 "deepinvteseq-2.gperf"
      {"ct", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ct)},
#line 281 "deepinvteseq-2.gperf"
      {"ti", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 173 "deepinvteseq-2.gperf"
      {"dc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_dc)},
#line 176 "deepinvteseq-2.gperf"
      {"do", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_do)},
#line 254 "deepinvteseq-2.gperf"
      {"nw", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_nw)},
#line 252 "deepinvteseq-2.gperf"
      {"mr", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_mr)},
#line 169 "deepinvteseq-2.gperf"
      {"cr", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cr)},
#line 179 "deepinvteseq-2.gperf"
      {"ec", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ec)},
#line 174 "deepinvteseq-2.gperf"
      {"dl", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_dl)},
#line 161 "deepinvteseq-2.gperf"
      {"cS", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_cS)},
#line 278 "deepinvteseq-2.gperf"
      {"st", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_st)},
#line 289 "deepinvteseq-2.gperf"
      {"vi", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_vi)},
#line 222 "deepinvteseq-2.gperf"
      {"kb", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_kb)},
#line 192 "deepinvteseq-2.gperf"
      {"im", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_im)},
#line 253 "deepinvteseq-2.gperf"
      {"nd", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_nd)},
#line 287 "deepinvteseq-2.gperf"
      {"vb", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_vb)},
#line 277 "deepinvteseq-2.gperf"
      {"sr", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_sr)},
#line 279 "deepinvteseq-2.gperf"
      {"ta", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ta)},
#line 183 "deepinvteseq-2.gperf"
      {"fs", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_fs)},
#line 175 "deepinvteseq-2.gperf"
      {"dm", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 158 "deepinvteseq-2.gperf"
      {"bc", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_le)},
#line 180 "deepinvteseq-2.gperf"
      {"ed", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 242 "deepinvteseq-2.gperf"
      {"le", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_le)},
#line 155 "deepinvteseq-2.gperf"
      {"ae", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ae)},
#line 182 "deepinvteseq-2.gperf"
      {"ff", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_noop)},
#line 181 "deepinvteseq-2.gperf"
      {"ei", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ei)},
#line 159 "deepinvteseq-2.gperf"
      {"bl", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_bl)},
#line 157 "deepinvteseq-2.gperf"
      {"as", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_as)},
#line 153 "deepinvteseq-2.gperf"
      {"UP", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_UP)},
#line 151 "deepinvteseq-2.gperf"
      {"SR", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_SR)},
#line 243 "deepinvteseq-2.gperf"
      {"ll", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_ll)},
#line 156 "deepinvteseq-2.gperf"
      {"al", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_al)},
#line 79 "deepinvteseq-2.gperf"
      {"DO", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_DO)},
#line 78 "deepinvteseq-2.gperf"
      {"DL", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_DL)},
#line 147 "deepinvteseq-2.gperf"
      {"RI", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_RI)},
#line 150 "deepinvteseq-2.gperf"
      {"SF", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_SF)},
#line 139 "deepinvteseq-2.gperf"
      {"LE", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_LE)},
#line 77 "deepinvteseq-2.gperf"
      {"DC", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_DC)},
#line 133 "deepinvteseq-2.gperf"
      {"IC", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_IC)},
#line 178 "deepinvteseq-2.gperf"
      {"eA", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_eA)},
#line 76 "deepinvteseq-2.gperf"
      {"AL", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_AL)},
      {""}, {""}, {""},
#line 160 "deepinvteseq-2.gperf"
      {"bt", DEEPINVTE_SEQUENCE_HANDLER(deepinvte_sequence_handler_bt)}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = deepinvteseq_2_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].seq;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
