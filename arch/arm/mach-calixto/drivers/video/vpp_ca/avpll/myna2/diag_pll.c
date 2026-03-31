/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016~2023 Synaptics Incorporated. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or
 * later as published by the Free Software Foundation.
 *
 * INFORMATION CONTAINED IN THIS DOCUMENT IS PROVIDED "AS-IS," AND
 * SYNAPTICS EXPRESSLY DISCLAIMS ALL EXPRESS AND IMPLIED WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE, AND ANY WARRANTIES OF NON-INFRINGEMENT OF ANY
 * INTELLECTUAL PROPERTY RIGHTS. IN NO EVENT SHALL SYNAPTICS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OF THE INFORMATION CONTAINED IN THIS DOCUMENT, HOWEVER CAUSED AND
 * BASED ON ANY THEORY OF LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, AND EVEN IF SYNAPTICS WAS
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. IF A TRIBUNAL OF
 * COMPETENT JURISDICTION DOES NOT PERMIT THE DISCLAIMER OF DIRECT
 * DAMAGES OR ANY OTHER DAMAGES, SYNAPTICS' TOTAL CUMULATIVE LIABILITY
 * TO ANY PARTY SHALL NOT EXCEED ONE HUNDRED U.S. DOLLARS.
 */

#include "diag_pll.h"

#define PRINT printf

#define A_F_V(a, f, v)		(a)

ssc_div_t divs[SSC_DIV_MAX] = {
    {32, 	0xF},
    {42, 	0xE},
    {50, 	0xD},
    {64, 	0xC},
    {84, 	0xB},
    {102, 	0xA},
    {128, 	0x9},
    {170, 	0x8},
    {204, 	0x7},
    {256, 	0x6},
    {340, 	0x5},
    {408, 	0x4},
    {512, 	0x3},
    {682, 	0x2},
    {818, 	0x1},
};

static void delay_us_real(unsigned int us)
{
	const unsigned int step_us = 1000000;
	const unsigned int step_ns = 1000 * step_us;
	while (us > step_us) {
		ndelay(step_ns);
		us -= step_us;
	}
	if (us)
		ndelay(1000 * us);
}

// positive inputs
int gcd(int a, int b)
{
    while(a!=b)
    {
        if(a>b)
            a-=b;
        else
            b-=a;
    }
    return a;
}

int lcm(int a, int b)
{
    return a*b/gcd(a,b);
}

int calc_vco(int freq, int freq1)
{
    int vco = lcm(freq, freq1);
    return vco;
}

int rounding(double frac)
{
    int int_part = (int)frac;
    if((frac-0.5)<(double)int_part)
        return int_part;
    else
        return int_part+1;
}

// d1.div < target <d2.div
int closest(ssc_div_t d1, ssc_div_t d2, int target){
    if((target-d1.div)>(d2.div-target))
	return d2.val;
    else
	return d1.val;
}

// binary search to find the closest
// input ssc_div_t in ascending order (of ssc_div_t->div)
int bsearch(ssc_div_t a[], int target){
    int l=0, r=SSC_DIV_MAX;
    int mid;

    // corner case;
    if(target<=a[0].div)
	return a[0].val;
    if(target>=a[SSC_DIV_MAX-1].div)
	return a[SSC_DIV_MAX-1].val;

    while(l<r){
	mid=l+(r-l)/2;
	if(a[mid].div==target){
	    return a[mid].val;
	}else if(target<a[mid].div){
	    // search the left handside;
	    // check if target in range [mid-1, mid], if so, return the closest;
	    if(mid>0 && target>a[mid-1].div){
		return closest(a[mid-1], a[mid], target);
	    }
	    r=mid;
	}else{
	    // search the right handside
	    // check if target in range [mid, mid+1], if sp, return the closest
	    if(mid<SSC_DIV_MAX-1 && target<a[mid+1].div){
		return closest(a[mid], a[mid+1], target);
	    }
	    l=mid+1;
	}
    }
    return a[mid].val;
}

unsigned int get_pll_base(E_PLL_SRC pll)
{
    unsigned int pll_base;
    switch(pll)
    {
    case SYSPLL0:
        pll_base = MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_sysPll_0;
        break;
    case SYSPLL1:
        pll_base = MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_sysPll_1;
        break;
    case CPUPLL:
        pll_base = MEMMAP_CA7_REG_BASE + RA_CPU_WRP_PLL_REG;
        break;
    case MEMPLL:
        pll_base = MEMMAP_MCTRLSS_REG_BASE + RA_mc_wrap_memPll;
        break;
    case VPLL0:
        pll_base = VPLLWRAP0VPLL;
        break;
    case VPLL1:
        pll_base = VPLLWRAP1VPLL;
        break;
    case APLL0:
        pll_base = APLLWRAP0APLL;
        break;
    case APLL1:
        pll_base = APLLWRAP1APLL;
        break;
    default:
#if TARGET != BOOT
        printf("ILLEGAL PLL BASE!!\n");
#else
        PRINT("ILLEGAL PLL BASE!!\n");
#endif
        pll_base=0xDEADBEEF;
        break;
    }

    return pll_base;
}

int diag_bypass_pll(unsigned int pllbase, int bypass)
{
    int ret=0;
    Tabipll_ctrlA pllctrla;

    PLL_REG_PRINT(pllbase, 0);

    PLL_REG_READ(pllbase, 0, pllctrla.u32[0]);
    PLL_REG_SET(pllctrla, A_BYPASS, bypass);
    PLL_REG_WRITE(pllbase, 0, pllctrla.u32[0]);

    PLL_REG_PRINT(pllbase, 0);

    return ret;
}

int diag_reset_pll(unsigned int pllbase, int reset)
{
    int ret=0;
    Tabipll_ctrlA pllctrla;

    PLL_REG_PRINT(pllbase, 0);

    PLL_REG_READ(pllbase, 0, pllctrla.u32[0]);
    PLL_REG_SET(pllctrla, A_RESET, reset);
    PLL_REG_WRITE(pllbase, 0, pllctrla.u32[0]);

    PLL_REG_PRINT(pllbase, 0);

    return ret;
}

// TB: APLL/VPLL will be implemented later
int diag_apllwrapper_power(E_PLL_SRC pll, int down)
{
    int ret=0;
    unsigned int val;
    // centralized avpll power control
    // convert apll index
    pll -= VPLL0;

    // power PLL
    BFM_HOST_Bus_Read32(AVPLL_SWPD_ADDR, &val);
    val &= ~(1<<pll);
    val |= down<<pll;
    BFM_HOST_Bus_Write32(AVPLL_SWPD_ADDR, val);

    return ret;
}

int diag_bypass_pll_global(E_PLL_SRC pll, int bypass)
{
    int ret=0;
    unsigned int val;

    if(pll<=CPUPLL)
    {
        BFM_HOST_Bus_Read32(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_ClkSwitch, &val);
        val &= ~(1<<pll);
        val |= bypass<<pll;
        BFM_HOST_Bus_Write32(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_ClkSwitch, val);
    }
    else if(pll<=APLL0)
    {
        // APLL global wrapper clkEn
        // per Dheeray Gupta's email @ 10/23, use PD registers as
	// AVPLL global bypass.
	ret = diag_apllwrapper_power(pll, bypass);
    }
    else
    {
        // invalid pll
        ret=-1;
    }

    return ret;
}

int diag_config_pll_vco(unsigned int pllbase, int refdiv, int fddiv, unsigned int frac)
{
    int ret=0;
    Tabipll_ctrlC pllctrlc;
    Tabipll_ctrlD pllctrld;
    Tabipll_ctrlE pllctrle;

    PLL_REG_PRINT(pllbase, 2);
    PLL_REG_PRINT(pllbase, 3);
    PLL_REG_PRINT(pllbase, 4);

    PLL_REG_READ(pllbase, 2, pllctrlc.u32[0]);
    PLL_REG_READ(pllbase, 3, pllctrld.u32[0]);
    PLL_REG_READ(pllbase, 4, pllctrle.u32[0]);

    PLL_REG_SET(pllctrlc, C_DIVR, 	refdiv);
    PLL_REG_SET(pllctrld, D_DIVFI, 	fddiv);
    PLL_REG_SET(pllctrle, E_DIVFF, 	frac);

    PLL_REG_WRITE(pllbase, 2, pllctrlc.u32[0]);
    PLL_REG_WRITE(pllbase, 3, pllctrld.u32[0]);
    PLL_REG_WRITE(pllbase, 4, pllctrle.u32[0]);

    PLL_REG_PRINT(pllbase, 2);
    PLL_REG_PRINT(pllbase, 3);
    PLL_REG_PRINT(pllbase, 4);

    return ret;
}

int diag_config_pll_dp(unsigned int pllbase, int dp, int dp1)
{
    int ret=0;
    Tabipll_ctrlF pllctrlf;
    Tabipll_ctrlG pllctrlg;

    PLL_REG_READ(pllbase, 5, pllctrlf.u32[0]);
    PLL_REG_READ(pllbase, 6, pllctrlg.u32[0]);

    PLL_REG_SET(pllctrlf, F_DIVQ, 		dp);
    PLL_REG_SET(pllctrlg, G_DIVQF, 		dp1);

    PLL_REG_WRITE(pllbase, 5, pllctrlf.u32[0]);
    PLL_REG_WRITE(pllbase, 6, pllctrlg.u32[0]);

    PLL_REG_PRINT(pllbase, 5);
    PLL_REG_PRINT(pllbase, 6);

    return ret;
}

double diag_config_pll_getfpfd(unsigned int pllbase){
    Tabipll_ctrlC pllctrlc;
    int divr;

    PLL_REG_PRINT(pllbase, 2);
    // get DIVR
    PLL_REG_READ(pllbase, 2, pllctrlc.u32[0]);
    PLL_REG_GET(pllctrlc, C_DIVR, 	divr);

    double fpfd=(double)FREF/(divr+1);
    return fpfd;
}

int diag_config_pll_getpfdrange(unsigned int pllbase){
    int r=0;
    double fpfd=diag_config_pll_getfpfd(pllbase);

    // 8 possible ranges
    if(fpfd>=5 && fpfd<7.5){
	r=0;
    }else if(fpfd>=7.5 && fpfd<11){
	r=1;
    }else if(fpfd>=11 && fpfd<18){
	r=2;
    }else if(fpfd>=18 && fpfd<30){
	r=3;
    }else if(fpfd>=30 && fpfd<50){
	r=4;
    }else if(fpfd>=50 && fpfd<80){
	r=5;
    }else if(fpfd>=80 && fpfd<130){
	r=6;
    }else if(fpfd>=130 && fpfd<=200){
	r=7;
    }else{
#if TARGET != BOOT
        printf("ILLEGAL input FPFD!!\n");
#else
        PRINT("ILLEGAL PLL BASE!!\n");
#endif
	r=0;
    }
    return r;
}

int diag_config_pll_setpfdrange(unsigned int pllbase)
{
    int ret=0;
    Tabipll_ctrlA pllctrla;

    int range=diag_config_pll_getpfdrange(pllbase);

    PLL_REG_PRINT(pllbase, 0);

    PLL_REG_READ(pllbase, 0, pllctrla.u32[0]);
    PLL_REG_SET(pllctrla, A_RANGE, range);
    PLL_REG_WRITE(pllbase, 0, pllctrla.u32[0]);

    PLL_REG_PRINT(pllbase, 0);

    return ret;
}

// TB: ABI PLL support both downspread and centerspread
// so add a new parameter
// Hint: need to double the input ssc_amp if the ssc_mode is centerspread
// since the SSC depth is peak to peak frequency distance.
int diag_config_pll_ssc(unsigned int pllbase, int ssc_freq, int ssc_amp, int ssc_mode, int enable)
{
    int ret=0, ssfreq, ssdepth, ssmode;
    int ssc_div;
    Tabipll_ctrlB pllctrlb;
    double wssc_amp = 0, fpfd, ssc_freqd;

    if(enable)
    {
        // input parameter validate
	// SSC only in fraction mode.
	// use 6.25Mhz Fpfd, which is 25MHz/4
        if(ssc_freq<7||ssc_freq>234||ssc_amp<0||ssc_amp>40)
            return -1;

        // SSC calculation
        // SSC freq range [6.11, 234] KHz
        // SSC amp range [0.2%, 4%] both downspread and centerspread

	// select ssc depth, input ssc_amp = actual_ssc_amp * 10, which is to
	// avoid using floating point input
	// invalid input checked previously, so all ssc_amp should be valid
	if(ssc_amp<=2){
	    ssdepth=0;
	    wssc_amp=0.2;
	}else if(ssc_amp<=5){
	    ssdepth=1;
	    wssc_amp=0.5;
	}else if(ssc_amp<=8){
	    ssdepth=2;
	    wssc_amp=0.8;
	}else if(ssc_amp<=10){
	    ssdepth=3;
	    wssc_amp=1.0;
	}else if(ssc_amp<=16){
	    ssdepth=4;
	    wssc_amp=1.6;
	}else if(ssc_amp<=20){
	    ssdepth=5;
	    wssc_amp=2.0;
	}else if(ssc_amp<=31){
	    ssdepth=6;
	    wssc_amp=3.1;
	}else if(ssc_amp<=40){
	    ssdepth=7;
	    wssc_amp=4.0;
	}

#if TARGET != BOOT
        debug("written SSC depth is: %.1f,  input SSC depth is: %.1f\n", wssc_amp, (double)ssc_amp/10);
#else
        PRINT("written SSC depth is: %d,  input SSC depth is: %d\n", (int)(wssc_amp*10), ssc_amp);
#endif
	fpfd=diag_config_pll_getfpfd(pllbase);
	// per SPEC page 8, exmaple in Table5B, SSC_freq = Fpfd/SSMF[3:0]
	// ssc_freq input in KHz, so to transform to Mhz, we need to divide by
	// 1000
	ssc_freqd=(double)ssc_freq/1000;
	ssc_div=rounding(fpfd/ssc_freqd);
#if TARGET != BOOT
        debug("Calculated FPFD frequency is: %.3f\n", fpfd);
        debug("Calculated SSCD frequency is: %.3f\n", ssc_freqd);
        debug("Calculated divider is:%d, SSC frequency is: %.3f\n", ssc_div, fpfd/ssc_div);
#endif
	// select SSMF base on SSC_DIV
	// binary search, closest
	ssfreq=bsearch(divs, ssc_div);
#if TARGET != BOOT
        debug("Table Searched SSMF is: %d\n", ssfreq);
#endif
	ssmode=ssc_mode;
    }else{
        ssfreq = 0;
        ssdepth= 0;
	ssmode = 0;
    }

    // update corresponding SSRATE and SLOPE register
    PLL_REG_PRINT(pllbase, 1);
    PLL_REG_READ(pllbase, 1, pllctrlb.u32[0]);

    PLL_REG_SET(pllctrlb, B_SSMF, 	ssfreq);
    PLL_REG_SET(pllctrlb, B_SSMD, 	ssdepth);
    PLL_REG_SET(pllctrlb, B_SSE, 	enable);
    PLL_REG_SET(pllctrlb, B_SSDS, 	ssmode);

    PLL_REG_WRITE(pllbase, 1, pllctrlb.u32[0]);

    PLL_REG_PRINT(pllbase, 1);

    return ret + ((int)wssc_amp ^ (int)wssc_amp);
}

int diag_wait_pll_lock(unsigned int pllbase)
{
    // wait long enough for PLL LOCK
    // SPEC doesn't speficy timeout time
    int ret=0, tout = A_F_V(3000, 30, 30);
    // get statue
    volatile Tabipll_status pllstatus;
    PLL_REG_PRINT(pllbase, 7);
    PLL_REG_READ(pllbase, 7, pllstatus.u32[0]);
    while(!pllstatus.ustatus_LOCK&&tout)
    {
        delay_us_real(1);
        PLL_REG_READ(pllbase, 7, pllstatus.u32[0]);
        tout--;
    }

    if(!tout)
        ret=-1;
    return ret;
}

// CLKO and CLKO1 as inputs
// integer freq change
int diag_change_pll(E_PLL_SRC pll, int freq, int freq1, int ssc, int ssc_freq,
        int ssc_amp, int ssc_mode, int calc, APLLCFG_t apll_cfg)
{
    int ret=0;
    // reference divider is 1 by default
    int dm=M1;
    // get PLL base address with checker
    unsigned int pllbase = get_pll_base(pll);
    int dp, dp1, INT_N, frac, vco=0, target_vco=0;
    int divr, divfi, divff, divq, divqf;
    double N=0.0, FRAC_N=0.0;

    if(pllbase == 0xDEADBEEF)
    {
        ret = -1;
        return ret;
    }

    // if calculate PLL settings inside code
    if(calc)
    {
        // calculate VCO first
        vco = calc_vco(freq, freq1);
        // check if vco is valid
        // SPEC defined VCO should be in [1200,6000]
        if(vco>6000)
        {
#if TARGET != BOOT
            printf("INVALID VCO: %d\n", vco);
#else
            PRINT("INVALID VCO: %d\n", vco);
#endif
            ret = -1;
            return ret;
        }

        // multiply by 2 to get a valid VCO
	target_vco=vco;
	int i=2;
	// make sure:
	// 1. VCO is greater than 1200
	// 2. DIVQ value must be even number, starts from 2 [2,4,6,8,10...]
        while(target_vco<1200 || (target_vco/freq)%2==1)
        {
            target_vco=vco*i;
	    i++;
        }
	vco=target_vco;

        // VCO is finalized now, check DM
	// Fpfd=Fref/DIVR
	// for integer mode: Fpfd [10, 200]
	// for fractional mode: Fpfd [5, 7.5]
	// Per SPEC, the higher the Fpfd, the better jitter scenario
	// so integer mode, use DIVR=1 [2 is another candidate]
	// fraction mode, use DIVR=6 [5 is another candidate]
	// all SSC mode are in fraction, so, use fraction mode DIVR if SSC is
	// intend to enable
        if(vco%25==0 && !ssc)
            dm=M1;
        else if((vco*10)%125==0 && !ssc)
            dm=M2;
        else
	    // change the fraction mode ref divider to 4
            dm=M4;

        // calculate dp
        dp = vco/freq;
	// since dp is between [2, 64], vco must be twice the freq of Fout
	if(dp==1)
	    vco*=2;
        if(vco>6000)
        {
#if TARGET != BOOT
            printf("INVALID VCO: %d\n", vco);
#else
            PRINT("INVALID VCO: %d\n", vco);
#endif
            ret = -1;
            return ret;
	}
	dp=vco/freq;
        dp1 = vco/freq1;
	// dp1 between [1:7]
	if(dp1>7 || dp>64 || dp1<1 || dp<2)
	{
#if TARGET != BOOT
            printf("INVALID DIVQ and DIVQF: %d %d\n", dp, dp1);
#else
            PRINT("INVALID DIVQ and DIVQF: %d %d\n", dp, dp1);
#endif
            ret = -1;
            return ret;
	}
	// ABI PLL doesn't have separte sequnce for update DIVR/DIVFI/DIVFF or
	// DIVQ/DIVQR only.
        // previous vco
        //pvco = get_vco(pllbase);

	// calculate VCO(CLK) M and N
	// in case fraction mode needed
	// N here is N.X
	// need to multiply first
	// ABI PLL PLLOUT=REF/DIVR_VAL*4*DIVF_VAL/DIVQ_VAL
	// DIVR_VAL=DIVR_DIVR[5:0]+1
	// DIVF_VAL=DIVFI+1+(DIVFF/1<<24)
	// DIVQ_VAL=(DIVQ[4:0]+1)*2
	N = (double)vco*dm/FREF/4;
	// calculate integer part N
	INT_N = vco*dm/FREF/4;
	// calculate fraction part N
	FRAC_N = N-INT_N;
	// since calculated frac may cause output frequency slightly less than
	// target. < 2*10^-10
	// we choose over clock that amount, which also satisfy the timing
	frac = FRAC_N==0?0:(FRAC_N*(1<<24)+1);

    	// value need to by register program ready, so translate here
	divr=dm-1;
	divfi=INT_N-1;
	divff=frac;
	divq=dp/2-1;
	divqf=dp1-1;

#if TARGET != BOOT
	debug(" calculated DIVFI is: %d\n", INT_N);
	debug(" calculated fraction is: %f\n", FRAC_N);
	debug(" calculated DIVFF is: %d\n", frac);
	debug(" calculated DIVQ and DIVQF is: %d %d\n", divq, divqf);
#endif
    }
    else
    {
        divr=apll_cfg.dm;
	divfi=apll_cfg.dn;
	divff=apll_cfg.frac;
        divq=apll_cfg.dp;
        divqf=apll_cfg.dp1;

	// these parameters are needed to decide if we could do a glitch-free on
	// the fly feedback divider change.
	dm=divr+1;
	INT_N=divfi+1;
	frac=divff;
    }

    if (pll >= VPLL0 && pll <= APLL1)
    {
        diag_apllwrapper_power(pll, 0);
    }
    // PLL global bypass
    ret |= diag_bypass_pll_global(pll, ABYPASS);

    // PLL internal bypass, this will also power down the PLL per SPEC
    // p3
    ret |= diag_bypass_pll(pllbase, ABYPASS);


    // hold reset
    // PER SPEC, not necessary to hold both BYPASS and RESET, but we do it for
    // secure
    ret |= diag_reset_pll(pllbase, ARESET);


    // VS680 TB: no PLL mode selection in ABI PLL
    // change mode

    // update vco
    ret |= diag_config_pll_vco(pllbase, divr, divfi, divff);

    // update ssc settings
    // we need to use SSC configuration to decide if current Fpfd working in
    // fraction mode;
    int ssc_ret;
    ssc_ret = diag_config_pll_ssc(pllbase, ssc_freq, ssc_amp, ssc_mode, ssc);
    if(ssc_ret != 0)
#if TARGET != BOOT
	    printf("SSC change fail, SSC config not changed!\n");
#else
    PRINT("SSC change fail, SSC config not changed!\n");
#endif

    // update Fpfd range
    ret |= diag_config_pll_setpfdrange(pllbase);

    // update dp, dp1
    ret |= diag_config_pll_dp(pllbase, divq, divqf);
    // wait at least 2 ref_clock
    // assume FREF=25Mhz, we need to wait at least 80ns
    delay_us_real(1);

    // don't need to toggle power here, ABI PLL doesn't have output port
    // powerdown feature.

    // since de-assert BYPASS will make DVFI and DVFF being latched, we don't
    // need to utilize the glitch free fraction divider update here.
    // will have separate function to support it.

    // release RESET
    ret |= diag_reset_pll(pllbase, DEARESET);
    delay_us_real(1);

    // set BYPASS to 0
    // PLL internal bypass
    ret |= diag_bypass_pll(pllbase, DEABYPASS);

    // PLL global bypass
    ret |= diag_bypass_pll_global(pll, DEABYPASS);

    // wait lock here
    // per SPEC p2, frequency lock time is 125 Fpfd cycles for integer mode and
    // 250 Fpfd cycles for fraction mode. For safety, we always use the slowest
    //     Fpfd cycle to calculate: 5Mhz --> 200ns --> 50us.
    // TB: per ASIC PLL sequence, change the delay to >=120 us
    //delay_us_real(50);
    delay_us_real(120);
    ret |= diag_wait_pll_lock(pllbase);
    // should still keep the clock settings, assume the clock is there
    // unbypass anyways.
    // NEED TO BE UPDATED
    if(ret)
    {
	    //printf("PLL CHANGE FAIL!!!\nPLL in BYPASS mode!!!\n");
#if TARGET != BOOT
	    debug("PLL NOT LOCK!!!\nASSUME PLL IS READY!!\n");
	    ret=0;
#else
	    debug("PLL NOT LOCK!!!\nASSUME PLL IS READY!!\n");
	    ret=0;
#endif
	    //return ret;
    }

    //// update global ssc_status
    //curr_ssc[pll].ssc = ssc;
    //curr_ssc[pll].freq = ssc_freq;
    //curr_ssc[pll].amp = ssc_amp;
    return ret;
}

int diag_change_avpll(unsigned int apll_index, unsigned int freq,
		unsigned int ssc, unsigned int ssc_freq, unsigned int ssc_amp, unsigned
		int ssc_mode, unsigned int calc, APLLCFG_t pll_cfg)
{
	int ret=0;
	if(apll_index<0 || apll_index >(APLL1-VPLL0)){
#if TARGET != BOOT
		printf("INVALID input apll index!\n");
#else
	PRINT("INVALID input apll index!\n");
#endif
	return -1;
    }
    ret = diag_change_pll(VPLL0+apll_index, freq, freq, ssc, ssc_freq, ssc_amp, ssc_mode, calc, pll_cfg);

    return ret;
}
