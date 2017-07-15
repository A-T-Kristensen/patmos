/*

	This program is part of the TACLeBench benchmark suite.
	Version V 1.x

	Name: adpcm_dec

	Author: Sung-Soo Lim

	Function:
	  CCITT G.722 ADPCM (Adaptive Differential Pulse Code Modulation)
	  algorithm.
	  16khz sample rate data is stored in the array test_data[TEST_SIZE].
	  Results are stored in the array compressed[TEST_SIZE] and result[TEST_SIZE].
	  Execution time is determined by the constant TEST_SIZE (default value
	  is 2000).

	Source: SNU-RT Benchmark Suite

	Changes: adpcm benchmark was split into decode and encode benchmark

	License: may be used, modified, and re-distributed freely, but
			the SNU-RT Benchmark Suite must be acknowledged

*/

/*
	This program is derived from the SNU-RT Benchmark Suite for Worst
	Case Timing Analysis by Sung-Soo Lim

	Original source: C Algorithms for Real-Time DSP by P. M. Embree
*/

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_test.h"

/*
  Forward declaration of functions
*/

void adpcm_dec_decode(int);
int adpcm_dec_filtez(int *bpl, int *dlt);
void adpcm_dec_upzero(int dlt, int *dlti, int *bli);
int adpcm_dec_filtep(int rlt1, int al1, int rlt2, int al2);

int adpcm_dec_logscl(int il, int nbl);
int adpcm_dec_scalel(int nbl, int shift_constant);
int adpcm_dec_uppol2(int al1, int al2, int plt, int plt1, int plt2);
int adpcm_dec_uppol1(int al1, int apl2, int plt, int plt1);

int adpcm_dec_logsch(int ih, int nbh);
void adpcm_dec_reset();
int adpcm_dec_fabs(int n);
int adpcm_dec_cos(int n);
int adpcm_dec_sin(int n);

void adpcm_dec_init();
int adpcm_dec_return();
void adpcm_dec_main() __attribute__((noinline));
int main(void);

/*
  Declaration of macros
*/
/* common sampling rate for sound cards on IBM/PC */
#define SAMPLE_RATE 11025
#define PI 3141
#define TEST_SIZE 3
#define IN_END 4

/*
  Declaration of global variables
*/

int adpcm_dec_test_data[TEST_SIZE * 2], adpcm_dec_result[TEST_SIZE * 2];

/* Input data for the decoder usually generated by the encoder. */
int adpcm_dec_compressed[TEST_SIZE] = { 0, 253, 32 };

/* G722 C code */

/* QMF filter coefficients:
  scaled by a factor of 4 compared to G722 CCITT recommendation */
int adpcm_dec_h[24] = {
	12,   -44,   -44,   212,    48,  -624,   128,  1448,
	-840, -3220,  3804, 15504, 15504,  3804, -3220,  -840,
	1448,   128,  -624,    48,   212,   -44,   -44,    12
};

//int xl,xh;

/* variables for receive quadrature mirror filter here */
int adpcm_dec_accumc[11], adpcm_dec_accumd[11];

/* outputs of decode() */
int adpcm_dec_xout1, adpcm_dec_xout2;

int adpcm_dec_xs, adpcm_dec_xd;

/* variables for encoder (hi and lo) here */

int adpcm_dec_il, adpcm_dec_szl, adpcm_dec_spl, adpcm_dec_sl, adpcm_dec_el;

int adpcm_dec_qq4_code4_table[16] = {
	0,  -20456,  -12896,   -8968,   -6288,   -4240,   -2584,   -1200,
	20456,   12896,    8968,    6288,    4240,    2584,    1200,       0
};


int adpcm_dec_qq6_code6_table[64] = {
	-136,    -136,    -136,    -136,  -24808,  -21904,  -19008,  -16704,
	-14984,  -13512,  -12280,  -11192,  -10232,   -9360,   -8576,   -7856,
	-7192,   -6576,   -6000,   -5456,   -4944,   -4464,   -4008,   -3576,
	-3168,   -2776,   -2400,   -2032,   -1688,   -1360,   -1040,    -728,
	24808,   21904,   19008,   16704,   14984,   13512,   12280,   11192,
	10232,    9360,    8576,    7856,    7192,    6576,    6000,    5456,
	4944,    4464,    4008,    3576,    3168,    2776,    2400,    2032,
	1688,    1360,    1040,     728,     432,     136,    -432,    -136
};


int adpcm_dec_wl_code_table[16] = {
	-60,  3042,  1198,   538,   334,   172,    58,   -30,
	3042,  1198,   538,   334,   172,    58,   -30,   -60
};


int adpcm_dec_ilb_table[32] = {
	2048,  2093,  2139,  2186,  2233,  2282,  2332,  2383,
	2435,  2489,  2543,  2599,  2656,  2714,  2774,  2834,
	2896,  2960,  3025,  3091,  3158,  3228,  3298,  3371,
	3444,  3520,  3597,  3676,  3756,  3838,  3922,  4008
};

int adpcm_dec_nbl;     /* delay line */
int adpcm_dec_al1, adpcm_dec_al2;
int adpcm_dec_plt, adpcm_dec_plt1, adpcm_dec_plt2;
int adpcm_dec_rs;
int adpcm_dec_dlt;
int adpcm_dec_rlt, adpcm_dec_rlt1, adpcm_dec_rlt2;


int adpcm_dec_detl;


int adpcm_dec_deth;
int adpcm_dec_sh;         /* this comes from adaptive predictor */
int adpcm_dec_eh;

int adpcm_dec_qq2_code2_table[4] = {
	-7408,   -1616,   7408,  1616
};

int adpcm_dec_wh_code_table[4] = {
	798,   -214,    798,   -214
};


int adpcm_dec_dh, adpcm_dec_ih;
int adpcm_dec_nbh, adpcm_dec_szh;
int adpcm_dec_sph, adpcm_dec_ph, adpcm_dec_yh, adpcm_dec_rh;

int adpcm_dec_delay_dhx[6];

int adpcm_dec_delay_bph[6];

int adpcm_dec_ah1, adpcm_dec_ah2;
int adpcm_dec_ph1, adpcm_dec_ph2;
int adpcm_dec_rh1, adpcm_dec_rh2;

/* variables for decoder here */
int adpcm_dec_ilr, adpcm_dec_yl, adpcm_dec_rl;
int adpcm_dec_dec_deth, adpcm_dec_dec_detl, adpcm_dec_dec_dlt;

int adpcm_dec_dec_del_bpl[6];

int adpcm_dec_dec_del_dltx[6];

int adpcm_dec_dec_plt, adpcm_dec_dec_plt1, adpcm_dec_dec_plt2;
int adpcm_dec_dec_szl, adpcm_dec_dec_spl, adpcm_dec_dec_sl;
int adpcm_dec_dec_rlt1, adpcm_dec_dec_rlt2, adpcm_dec_dec_rlt;
int adpcm_dec_dec_al1, adpcm_dec_dec_al2;
int adpcm_dec_dl;
int adpcm_dec_dec_nbl, adpcm_dec_dec_yh, adpcm_dec_dec_dh, adpcm_dec_dec_nbh;

/* variables used in filtez */
int adpcm_dec_dec_del_bph[6];

int adpcm_dec_dec_del_dhx[6];

int adpcm_dec_dec_szh;
/* variables used in filtep */
int adpcm_dec_dec_rh1, adpcm_dec_dec_rh2;
int adpcm_dec_dec_ah1, adpcm_dec_dec_ah2;
int adpcm_dec_dec_ph, adpcm_dec_dec_sph;

int adpcm_dec_dec_sh, adpcm_dec_dec_rh;

int adpcm_dec_dec_ph1, adpcm_dec_dec_ph2;


/*
  Arithmetic math functions
*/

/* MAX: 1 */
int adpcm_dec_fabs(int n)
{
	int f;


	if(n >= 0)
		f = n;
	else
		f = -n;

	return f;
}


int adpcm_dec_sin(int rad)
{
	int diff;
	int app = 0;
	int inc = 1;


	/* MAX dependent on rad's value, say 50 */
	_Pragma("loopbound min 0 max 0")
	while(rad > 2 * PI)
		rad -= 2 * PI;

	_Pragma("loopbound min 0 max 1999")
	while(rad < -2 * PI)
		rad += 2 * PI;

	diff = rad;
	app = diff;
	diff = (diff * (-(rad * rad))) / ((2 * inc) * (2 * inc + 1));
	app = app + diff;
	inc++;

	/* REALLY: while(my_fabs(diff) >= 0.00001) { */
	/* MAX: 1000 */
	_Pragma("loopbound min 849 max 2424")
	while(adpcm_dec_fabs(diff) >= 1) {
		diff = (diff * (-(rad * rad))) / ((2 * inc) * (2 * inc + 1));
		app = app + diff;
		inc++;
	}

	return app;
}


int adpcm_dec_cos(int rad)
{
	return (adpcm_dec_sin(PI / 2 - rad));
}


/*
  Algorithm core functions
*/

/* decode function, result in xout1 and xout2 */
void adpcm_dec_decode(int input)
{
	int i;
	long int xa1, xa2;    /* qmf accumulators */
	int *h_ptr, *ac_ptr, *ac_ptr1, *ad_ptr, *ad_ptr1;


	/* split transmitted word from input into ilr and ih */
	adpcm_dec_ilr = input & 0x3f;
	adpcm_dec_ih = input >> 6;

	/* LOWER SUB_BAND DECODER */

	/* filtez: compute predictor output for zero section */
	adpcm_dec_dec_szl = adpcm_dec_filtez(adpcm_dec_dec_del_bpl,
										 adpcm_dec_dec_del_dltx);

	/* filtep: compute predictor output signal for pole section */
	adpcm_dec_dec_spl = adpcm_dec_filtep(adpcm_dec_dec_rlt1, adpcm_dec_dec_al1,
										 adpcm_dec_dec_rlt2, adpcm_dec_dec_al2);

	adpcm_dec_dec_sl = adpcm_dec_dec_spl + adpcm_dec_dec_szl;

	/* invqxl: compute quantized difference signal for adaptive predic */
	adpcm_dec_dec_dlt = ((long)adpcm_dec_dec_detl *
						 adpcm_dec_qq4_code4_table[adpcm_dec_ilr
								 >> 2]) >> 15;

	/* invqxl: compute quantized difference signal for decoder output */
	adpcm_dec_dl = ((long)adpcm_dec_dec_detl *
					adpcm_dec_qq6_code6_table[adpcm_dec_il]) >>
				   15;

	adpcm_dec_rl = adpcm_dec_dl + adpcm_dec_dec_sl;

	/* logscl: quantizer scale factor adaptation in the lower sub-band */
	adpcm_dec_dec_nbl = adpcm_dec_logscl(adpcm_dec_ilr, adpcm_dec_dec_nbl);

	/* scalel: computes quantizer scale factor in the lower sub band */
	adpcm_dec_dec_detl = adpcm_dec_scalel(adpcm_dec_dec_nbl, 8);

	/* parrec - add pole predictor output to quantized diff. signal */
	/* for partially reconstructed signal */
	adpcm_dec_dec_plt = adpcm_dec_dec_dlt + adpcm_dec_dec_szl;

	/* upzero: update zero section predictor coefficients */
	adpcm_dec_upzero(adpcm_dec_dec_dlt, adpcm_dec_dec_del_dltx,
					 adpcm_dec_dec_del_bpl);

	/* uppol2: update second predictor coefficient apl2 and delay it as al2 */
	adpcm_dec_dec_al2 = adpcm_dec_uppol2(adpcm_dec_dec_al1, adpcm_dec_dec_al2,
										 adpcm_dec_dec_plt, adpcm_dec_dec_plt1,
										 adpcm_dec_dec_plt2);

	/* uppol1: update first predictor coef. (pole setion) */
	adpcm_dec_dec_al1 = adpcm_dec_uppol1(adpcm_dec_dec_al1, adpcm_dec_dec_al2,
										 adpcm_dec_dec_plt, adpcm_dec_dec_plt1);

	/* recons : compute recontructed signal for adaptive predictor */
	adpcm_dec_dec_rlt = adpcm_dec_dec_sl + adpcm_dec_dec_dlt;

	/* done with lower sub band decoder, implement delays for next time */
	adpcm_dec_dec_rlt2 = adpcm_dec_dec_rlt1;
	adpcm_dec_dec_rlt1 = adpcm_dec_dec_rlt;
	adpcm_dec_dec_plt2 = adpcm_dec_dec_plt1;
	adpcm_dec_dec_plt1 = adpcm_dec_dec_plt;

	/* HIGH SUB-BAND DECODER */

	/* filtez: compute predictor output for zero section */
	adpcm_dec_dec_szh = adpcm_dec_filtez(adpcm_dec_dec_del_bph,
										 adpcm_dec_dec_del_dhx);

	/* filtep: compute predictor output signal for pole section */
	adpcm_dec_dec_sph = adpcm_dec_filtep(adpcm_dec_dec_rh1, adpcm_dec_dec_ah1,
										 adpcm_dec_dec_rh2, adpcm_dec_dec_ah2);

	/* predic:compute the predictor output value in the higher sub_band decoder */
	adpcm_dec_dec_sh = adpcm_dec_dec_sph + adpcm_dec_dec_szh;

	/* invqah: in-place compute the quantized difference signal */
	adpcm_dec_dec_dh = ((long)adpcm_dec_dec_deth *
						adpcm_dec_qq2_code2_table[adpcm_dec_ih]) >> 15L ;

	/* logsch: update logarithmic quantizer scale factor in hi sub band */
	adpcm_dec_dec_nbh = adpcm_dec_logsch(adpcm_dec_ih, adpcm_dec_dec_nbh);

	/* scalel: compute the quantizer scale factor in the higher sub band */
	adpcm_dec_dec_deth = adpcm_dec_scalel(adpcm_dec_dec_nbh, 10);

	/* parrec: compute partially recontructed signal */
	adpcm_dec_dec_ph = adpcm_dec_dec_dh + adpcm_dec_dec_szh;

	/* upzero: update zero section predictor coefficients */
	adpcm_dec_upzero(adpcm_dec_dec_dh, adpcm_dec_dec_del_dhx,
					 adpcm_dec_dec_del_bph);

	/* uppol2: update second predictor coefficient aph2 and delay it as ah2 */
	adpcm_dec_dec_ah2 = adpcm_dec_uppol2(adpcm_dec_dec_ah1, adpcm_dec_dec_ah2,
										 adpcm_dec_dec_ph, adpcm_dec_dec_ph1, adpcm_dec_dec_ph2);

	/* uppol1: update first predictor coef. (pole setion) */
	adpcm_dec_dec_ah1 = adpcm_dec_uppol1(adpcm_dec_dec_ah1, adpcm_dec_dec_ah2,
										 adpcm_dec_dec_ph, adpcm_dec_dec_ph1);

	/* recons : compute recontructed signal for adaptive predictor */
	adpcm_dec_rh = adpcm_dec_dec_sh + adpcm_dec_dec_dh;

	/* done with high band decode, implementing delays for next time here */
	adpcm_dec_dec_rh2 = adpcm_dec_dec_rh1;
	adpcm_dec_dec_rh1 = adpcm_dec_rh;
	adpcm_dec_dec_ph2 = adpcm_dec_dec_ph1;
	adpcm_dec_dec_ph1 = adpcm_dec_dec_ph;

	/* end of higher sub_band decoder */

	/* end with receive quadrature mirror filters */
	adpcm_dec_xd = adpcm_dec_rl - adpcm_dec_rh;
	adpcm_dec_xs = adpcm_dec_rl + adpcm_dec_rh;

	/* receive quadrature mirror filters implemented here */
	h_ptr = adpcm_dec_h;
	ac_ptr = adpcm_dec_accumc;
	ad_ptr = adpcm_dec_accumd;
	xa1 = (long) adpcm_dec_xd * (*h_ptr++);
	xa2 = (long) adpcm_dec_xs * (*h_ptr++);

	/* main multiply accumulate loop for samples and coefficients */
	_Pragma("loopbound min 10 max 10")
	for(i = 0; i < 10; i++) {
		xa1 += (long)(*ac_ptr++) * (*h_ptr++);
		xa2 += (long)(*ad_ptr++) * (*h_ptr++);
	}

	/* final mult/accumulate */
	xa1 += (long)(*ac_ptr) * (*h_ptr++);
	xa2 += (long)(*ad_ptr) * (*h_ptr++);

	/* scale by 2^14 */
	adpcm_dec_xout1 = xa1 >> 14;
	adpcm_dec_xout2 = xa2 >> 14;

	/* update delay lines */
	ac_ptr1 = ac_ptr - 1;
	ad_ptr1 = ad_ptr - 1;

	_Pragma("loopbound min 10 max 10")
	for(i = 0; i < 10; i++) {
		*ac_ptr-- = *ac_ptr1--;
		*ad_ptr-- = *ad_ptr1--;
	}

	*ac_ptr = adpcm_dec_xd;
	*ad_ptr = adpcm_dec_xs;

	return;
}


/* filtez - compute predictor output signal (zero section) */
/* input: bpl1-6 and dlt1-6, output: szl */
int adpcm_dec_filtez(int *bpl, int *dlt)
{
	int i;
	long int zl;


	zl = (long)(*bpl++) * (*dlt++);

	/* MAX: 5 */
	_Pragma("loopbound min 5 max 5")
	for(i = 1; i < 6; i++)
		zl += (long)(*bpl++) * (*dlt++);

	return ((int)(zl >> 14));       /* x2 here */
}


/* filtep - compute predictor output signal (pole section) */
/* input rlt1-2 and al1-2, output spl */
int adpcm_dec_filtep(int rlt1, int al1, int rlt2, int al2)
{
	long int pl, pl2;


	pl = 2 * rlt1;
	pl = (long) al1 * pl;
	pl2 = 2 * rlt2;
	pl += (long) al2 * pl2;

	return ((int)(pl >> 15));
}


/* logscl - update log quantizer scale factor in lower sub-band */
/* note that nbl is passed and returned */
int adpcm_dec_logscl(int il, int nbl)
{
	long int wd;


	wd = ((long)nbl * 127L) >> 7L;     /* leak factor 127/128 */
	nbl = (int)wd + adpcm_dec_wl_code_table[il >> 2];

	if(nbl < 0)
		nbl = 0;
	if(nbl > 18432)
		nbl = 18432;

	return (nbl);
}


/* scalel: compute quantizer scale factor in lower or upper sub-band*/
int adpcm_dec_scalel(int nbl, int shift_constant)
{
	int wd1, wd2, wd3;


	wd1 = (nbl >> 6) & 31;
	wd2 = nbl >> 11;
	wd3 = adpcm_dec_ilb_table[wd1] >> (shift_constant + 1 - wd2);

	return (wd3 << 3);
}


/* upzero - inputs: dlt, dlti[0-5], bli[0-5], outputs: updated bli[0-5] */
/* also implements delay of bli and update of dlti from dlt */
void adpcm_dec_upzero(int dlt, int *dlti, int *bli)
{
	int i, wd2, wd3;


	/*if dlt is zero, then no sum into bli */
	if(dlt == 0) {
		_Pragma("loopbound min 6 max 6")
		for(i = 0; i < 6; i++) {
			bli[i] = (int)((255L * bli[i]) >> 8L);       /* leak factor of 255/256 */
		}

	} else {
		_Pragma("loopbound min 6 max 6")
		for(i = 0; i < 6; i++) {
			if((long)dlt * dlti[i] >= 0)
				wd2 = 128;
			else
				wd2 = -128;

			wd3 = (int)((255L * bli[i]) >> 8L);       /* leak factor of 255/256 */
			bli[i] = wd2 + wd3;
		}

	}

	/* implement delay line for dlt */
	dlti[5] = dlti[4];
	dlti[4] = dlti[3];
	dlti[3] = dlti[2];
	dlti[1] = dlti[0];
	dlti[0] = dlt;

	return;
}


/* uppol2 - update second predictor coefficient (pole section) */
/* inputs: al1, al2, plt, plt1, plt2. outputs: apl2 */
int adpcm_dec_uppol2(int al1, int al2, int plt, int plt1, int plt2)
{
	long int wd2, wd4;
	int apl2;


	wd2 = 4L * (long)al1;
	if((long)plt * plt1 >= 0L)
		wd2 = -wd2;    /* check same sign */
	wd2 = wd2 >> 7;      /* gain of 1/128 */

	if((long)plt * plt2 >= 0L) {
		wd4 = wd2 + 128;       /* same sign case */
	} else
		wd4 = wd2 - 128;
	apl2 = wd4 + (127L * (long)al2 >> 7L);     /* leak factor of 127/128 */

	/* apl2 is limited to +-.75 */
	if(apl2 > 12288)
		apl2 = 12288;
	if(apl2 < -12288)
		apl2 = -12288;

	return (apl2);
}


/* uppol1 - update first predictor coefficient (pole section) */
/* inputs: al1, apl2, plt, plt1. outputs: apl1 */
int adpcm_dec_uppol1(int al1, int apl2, int plt, int plt1)
{
	long int wd2;
	int wd3, apl1;


	wd2 = ((long)al1 * 255L) >> 8L;     /* leak factor of 255/256 */
	if((long)plt * plt1 >= 0L) {
		apl1 = (int)wd2 + 192;    /* same sign case */
	} else
		apl1 = (int)wd2 - 192;

	/* note: wd3= .9375-.75 is always positive */
	wd3 = 15360 - apl2;     /* limit value */
	if(apl1 > wd3)
		apl1 = wd3;
	if(apl1 < -wd3)
		apl1 = -wd3;

	return (apl1);
}


/* logsch - update log quantizer scale factor in higher sub-band */
/* note that nbh is passed and returned */
int adpcm_dec_logsch(int ih, int nbh)
{
	int wd;


	wd = ((long)nbh * 127L) >> 7L;       /* leak factor 127/128 */
	nbh = wd + adpcm_dec_wh_code_table[ih];

	if(nbh < 0)
		nbh = 0;
	if(nbh > 22528)
		nbh = 22528;

	return (nbh);
}

/*
  Initialization- and return-value-related functions
*/

/* clear all storage locations */

void adpcm_dec_reset()
{
	int i;


	adpcm_dec_detl = adpcm_dec_dec_detl = 32;   /* reset to min scale factor */
	adpcm_dec_deth = adpcm_dec_dec_deth = 8;
	adpcm_dec_nbl = adpcm_dec_al1 = adpcm_dec_al2 = adpcm_dec_plt1 = adpcm_dec_plt2
									= adpcm_dec_rlt1 = adpcm_dec_rlt2 = 0;
	adpcm_dec_nbh = adpcm_dec_ah1 = adpcm_dec_ah2 = adpcm_dec_ph1 = adpcm_dec_ph2 =
										adpcm_dec_rh1 = adpcm_dec_rh2 = 0;
	adpcm_dec_dec_nbl = adpcm_dec_dec_al1 = adpcm_dec_dec_al2 = adpcm_dec_dec_plt1 =
			adpcm_dec_dec_plt2 = adpcm_dec_dec_rlt1 = adpcm_dec_dec_rlt2 = 0;
	adpcm_dec_dec_nbh = adpcm_dec_dec_ah1 = adpcm_dec_dec_ah2 = adpcm_dec_dec_ph1 =
			adpcm_dec_dec_ph2 = adpcm_dec_dec_rh1 = adpcm_dec_dec_rh2 = 0;

	_Pragma("loopbound min 6 max 6")
	for(i = 0; i < 6; i++) {
		////delay_dltx[i] = 0;
		adpcm_dec_delay_dhx[i] = 0;
		adpcm_dec_dec_del_dltx[i] = 0;
		adpcm_dec_dec_del_dhx[i] = 0;
	}

	_Pragma("loopbound min 6 max 6")
	for(i = 0; i < 6; i++) {
		//delay_bpl[i] = 0;
		adpcm_dec_delay_bph[i] = 0;
		adpcm_dec_dec_del_bpl[i] = 0;
		adpcm_dec_dec_del_bph[i] = 0;
	}

	_Pragma("loopbound min 11 max 11")
	for(i = 0; i < 11; i++) {
		adpcm_dec_accumc[i] = 0;
		adpcm_dec_accumd[i] = 0;
	}

	return;
}

void adpcm_dec_init()
{
	int i, j, f;
	volatile int x = 0;
	/* read in amplitude and frequency for test data */
	j = 10;
	f = 2000;

	/* reset, initialize required memory */
	adpcm_dec_reset();

	/* 16 KHz sample rate */
	/* XXmain_0, MAX: 2 */
	/* Since the number of times we loop in adpcm_dec_sin depends on the
	   argument we add the fact: xxmain_0:[]: */
	_Pragma("loopbound min 3 max 3")
	for(i = 0 ; i < TEST_SIZE ; i++) {
		adpcm_dec_test_data[i] = (int) j * adpcm_dec_cos(f * PI * i);

		/* avoid constant-propagation optimizations */
		adpcm_dec_test_data[i] += x;
	}
}

int adpcm_dec_return()
{
	int i;
	int check_sum = 0;

	for(i = 0; i < IN_END; i += 2) {
		check_sum += (adpcm_dec_result[i] + adpcm_dec_result[i + 1]);
	}

	return check_sum != -2;
}

/*
  Main functions
*/

void _Pragma("entrypoint") adpcm_dec_main(void)
{
	int i;

	_Pragma("loopbound min 2 max 2")
	for(i = 0 ; i < IN_END ; i += 2) {
		adpcm_dec_decode(adpcm_dec_compressed[i / 2]);
		adpcm_dec_result[i] = adpcm_dec_xout1;
		adpcm_dec_result[i + 1] = adpcm_dec_xout2;
	}

}


int main(void)
{
	adpcm_dec_init();

#if(WCET)

	adpcm_dec_main();

#else

	static unsigned long long start_cycle, stop_cycle;
	static unsigned long long return_cycles = 0;

	printf("Benchmarking \n");

	start_cycle = get_cpu_cycles();

	adpcm_dec_main();

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;

	print_benchmark(return_cycles, 0);

#endif

	return adpcm_dec_return();
}