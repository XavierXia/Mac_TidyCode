#ifndef __GDIEX__H__
#define __GDIEX__H__
#if defined(PLATFORM_WINDOWS)


#ifdef __cplusplus
extern "C"
{
#endif

// 计算中间色
COLORREF LITEGDI_IMP LightenScaleColor(long lScale,COLORREF crColor);
COLORREF LITEGDI_IMP DarkenScaleColor(long lScale,COLORREF crColor);
// 计算混合色,将crColorA和crColorB按照百分之nScale和100-nScale的比例混合
COLORREF LITEGDI_IMP MixedColor(COLORREF crColorA,UINT nScale,COLORREF crColorB);
// 计算灰度色
COLORREF LITEGDI_IMP GrayColor(COLORREF crColor);


typedef DWORD HLSCOLOR;
#define HLS(h,l,s) ((HLSCOLOR)(((BYTE)(h)|((WORD)((BYTE)(l))<<8))|(((DWORD)(BYTE)(s))<<16)))
#define HLS_H(hls) ((BYTE)(hls))
#define HLS_L(hls) ((BYTE)(((WORD)(hls)) >> 8))
#define HLS_S(hls) ((BYTE)((hls)>>16))
BYTE LITEGDI_IMP _ToRGB(float rm1,float rm2,float rh);
HLSCOLOR LITEGDI_IMP RGB2HLS(COLORREF rgb);
COLORREF LITEGDI_IMP HLS2RGB(HLSCOLOR hls);
COLORREF LITEGDI_IMP HLS_TRANSFORM(COLORREF rgb,int percent_L,int percent_S);

#ifdef __cplusplus
}
#endif


#endif // PLATFORM_WINDOWS
#endif // THIS_FILE
