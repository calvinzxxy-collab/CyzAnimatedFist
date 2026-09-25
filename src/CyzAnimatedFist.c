/* Cyz Animated Fist SAFE - no code hooks, GTA SA 1.0 US / SA-MP */

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef signed int I32;
typedef unsigned long ULONG;
typedef int BOOL;
typedef unsigned short WCHAR;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* LPVOID;
typedef const WCHAR* LPCWSTR;
typedef const char* LPCSTR;
#define WINAPI __attribute__((stdcall))
#define CDECL __attribute__((cdecl))
#define TRUE 1
#define FALSE 0
#define DLL_PROCESS_ATTACH 1
#define FILE_ATTRIBUTE_DIRECTORY 0x10u
#define INVALID_HANDLE_VALUE ((HANDLE)(I32)-1)
#define MAX_GIF_BYTES 100000000u
#define MAX_PATH_W 512
#define MAX_SCAN_DEPTH 8
#define MAX_DECODE_BYTES (256u*1024u*1024u)
#define MAX_FRAMES 1024u
#define GDI_OK 0
#define PixelFormat32bppARGB 0x26200Au
#define ImageLockModeRead 1u
#define PropertyTagFrameDelay 0x5100u

static const WCHAR W_KERNEL32[] = {'k','e','r','n','e','l','3','2','.','d','l','l',0};
static const WCHAR W_GDIPLUS[] = {'g','d','i','p','l','u','s','.','d','l','l',0};
static const WCHAR W_MODLOADER[] = {'m','o','d','l','o','a','d','e','r',0};
static const WCHAR W_FISTGIF[] = {'f','i','s','t','.','g','i','f',0};
static const WCHAR W_STAR[] = {'*',0};
static volatile const char MARKER[] = "CYZ_FIST_SAFE_NO_HOOK_V1";

#pragma pack(push, 4)
typedef struct { U32 dwLowDateTime, dwHighDateTime; } FILETIME_CYZ;
typedef struct {
    U32 dwFileAttributes;
    FILETIME_CYZ ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    U32 nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;
    WCHAR cFileName[260];
    WCHAR cAlternateFileName[14];
} WIN32_FIND_DATAW_CYZ;
typedef struct { U32 Data1; U16 Data2, Data3; U8 Data4[8]; } GUID_CYZ;
typedef struct { I32 X, Y, Width, Height; } GpRect_CYZ;
typedef struct { U32 Width, Height; I32 Stride; I32 PixelFormat; void* Scan0; U32 Reserved; } BitmapData_CYZ;
typedef struct { U32 id, length; U16 type; U16 pad; void* value; } PropertyItem_CYZ;
#pragma pack(pop)

typedef void* GpImage;
typedef I32 GpStatus;
typedef void* RwRaster;
typedef void* RwTexture;

/* WinAPI */
typedef void* (WINAPI *PFN_GetProcAddress)(HMODULE,LPCSTR);
typedef HMODULE (WINAPI *PFN_LoadLibraryW)(LPCWSTR);
typedef BOOL (WINAPI *PFN_DisableThreadLibraryCalls)(HMODULE);
typedef HANDLE (WINAPI *PFN_CreateThread)(void*,U32,U32 (WINAPI*)(void*),void*,U32,U32*);
typedef void (WINAPI *PFN_Sleep)(U32);
typedef U32 (WINAPI *PFN_GetTickCount)(void);
typedef U32 (WINAPI *PFN_GetModuleFileNameW)(HMODULE,WCHAR*,U32);
typedef HANDLE (WINAPI *PFN_FindFirstFileW)(LPCWSTR,WIN32_FIND_DATAW_CYZ*);
typedef BOOL (WINAPI *PFN_FindNextFileW)(HANDLE,WIN32_FIND_DATAW_CYZ*);
typedef BOOL (WINAPI *PFN_FindClose)(HANDLE);
typedef HANDLE (WINAPI *PFN_GetProcessHeap)(void);
typedef void* (WINAPI *PFN_HeapAlloc)(HANDLE,U32,U32);
typedef BOOL (WINAPI *PFN_HeapFree)(HANDLE,U32,void*);

/* GDI+ flat API */
typedef GpStatus (WINAPI *PFN_GdiplusStartup)(ULONG*,const void*,void*);
typedef void (WINAPI *PFN_GdiplusShutdown)(ULONG);
typedef GpStatus (WINAPI *PFN_GdipLoadImageFromFile)(LPCWSTR,GpImage*);
typedef GpStatus (WINAPI *PFN_GdipDisposeImage)(GpImage);
typedef GpStatus (WINAPI *PFN_GdipGetImageWidth)(GpImage,U32*);
typedef GpStatus (WINAPI *PFN_GdipGetImageHeight)(GpImage,U32*);
typedef GpStatus (WINAPI *PFN_GdipImageGetFrameDimensionsCount)(GpImage,U32*);
typedef GpStatus (WINAPI *PFN_GdipImageGetFrameDimensionsList)(GpImage,GUID_CYZ*,U32);
typedef GpStatus (WINAPI *PFN_GdipImageGetFrameCount)(GpImage,const GUID_CYZ*,U32*);
typedef GpStatus (WINAPI *PFN_GdipImageSelectActiveFrame)(GpImage,const GUID_CYZ*,U32);
typedef GpStatus (WINAPI *PFN_GdipBitmapLockBits)(GpImage,const GpRect_CYZ*,U32,I32,BitmapData_CYZ*);
typedef GpStatus (WINAPI *PFN_GdipBitmapUnlockBits)(GpImage,BitmapData_CYZ*);
typedef GpStatus (WINAPI *PFN_GdipGetPropertyItemSize)(GpImage,U32,U32*);
typedef GpStatus (WINAPI *PFN_GdipGetPropertyItem)(GpImage,U32,U32,PropertyItem_CYZ*);

static PFN_GetProcAddress pGetProcAddress;
static PFN_LoadLibraryW pLoadLibraryW;
static PFN_DisableThreadLibraryCalls pDisableThreadLibraryCalls;
static PFN_CreateThread pCreateThread;
static PFN_Sleep pSleep;
static PFN_GetTickCount pGetTickCount;
static PFN_GetModuleFileNameW pGetModuleFileNameW;
static PFN_FindFirstFileW pFindFirstFileW;
static PFN_FindNextFileW pFindNextFileW;
static PFN_FindClose pFindClose;
static PFN_GetProcessHeap pGetProcessHeap;
static PFN_HeapAlloc pHeapAlloc;
static PFN_HeapFree pHeapFree;
static HANDLE gHeap;
static U8* gGameBase;

static void* mem_copy(void* d,const void* s,U32 n){U8*dd=(U8*)d;const U8*ss=(const U8*)s;while(n--)*dd++=*ss++;return d;}
static void mem_zero(void* d,U32 n){U8*p=(U8*)d;while(n--)*p++=0;}
static int ascii_eq(const char*a,const char*b){while(*a&&*b){if(*a!=*b)return 0;a++;b++;}return *a==*b;}
static WCHAR wlower(WCHAR c){if(c>='A'&&c<='Z')return (WCHAR)(c+32);return c;}
static int wide_eq_ci(const WCHAR*a,const WCHAR*b){while(*a&&*b){if(wlower(*a)!=wlower(*b))return 0;a++;b++;}return *a==*b;}
static U32 wlen(const WCHAR*s){U32 n=0;while(s[n])n++;return n;}
static int wcopy(WCHAR*d,U32 cap,const WCHAR*s){U32 i=0;if(!cap)return 0;while(s[i]){if(i+1>=cap){d[0]=0;return 0;}d[i]=s[i];i++;}d[i]=0;return 1;}
static int wappend(WCHAR*d,U32 cap,const WCHAR*s){U32 n=wlen(d),i=0;if(n>=cap)return 0;while(s[i]){if(n+i+1>=cap)return 0;d[n+i]=s[i];i++;}d[n+i]=0;return 1;}
static int append_slash(WCHAR*d,U32 cap){U32 n=wlen(d);if(n&&d[n-1]!='\\'&&d[n-1]!='/'){if(n+2>cap)return 0;d[n]='\\';d[n+1]=0;}return 1;}

static void* get_peb(void){void*p;__asm__ volatile("movl %%fs:0x30, %0":"=r"(p));return p;}
static HMODULE find_loaded_module_ci(const WCHAR* name){
    U8* peb=(U8*)get_peb(); if(!peb)return 0;
    U8* ldr=*(U8**)(peb+0x0C); if(!ldr)return 0;
    U8* head=ldr+0x0C; U8* e=*(U8**)head;
    while(e && e!=head){
        HMODULE base=*(HMODULE*)(e+0x18);
        WCHAR* bn=*(WCHAR**)(e+0x30);
        if(bn && wide_eq_ci(bn,name)) return base;
        e=*(U8**)e;
    }
    return 0;
}
static void* raw_export(HMODULE m,const char* name){
    U8*b=(U8*)m; if(!b||b[0]!='M'||b[1]!='Z')return 0;
    U32 nt=*(U32*)(b+0x3C); if(*(U32*)(b+nt)!=0x00004550u)return 0;
    U32 erva=*(U32*)(b+nt+0x78); if(!erva)return 0;
    U8* e=b+erva;
    U32 n=*(U32*)(e+24), frva=*(U32*)(e+28), nrva=*(U32*)(e+32), orva=*(U32*)(e+36);
    U32* names=(U32*)(b+nrva); U16* ords=(U16*)(b+orva); U32* funcs=(U32*)(b+frva);
    U32 i; for(i=0;i<n;i++){char*s=(char*)(b+names[i]);if(ascii_eq(s,name)){U32 r=funcs[ords[i]];return b+r;}}
    return 0;
}
static int resolve_kernel(void){
    HMODULE k=find_loaded_module_ci(W_KERNEL32); if(!k)return 0;
    pGetProcAddress=(PFN_GetProcAddress)raw_export(k,"GetProcAddress");
    pLoadLibraryW=(PFN_LoadLibraryW)raw_export(k,"LoadLibraryW");
    if(!pGetProcAddress||!pLoadLibraryW)return 0;
#define GP(type,var,nm) var=(type)pGetProcAddress(k,nm); if(!var)return 0
    GP(PFN_DisableThreadLibraryCalls,pDisableThreadLibraryCalls,"DisableThreadLibraryCalls");
    GP(PFN_CreateThread,pCreateThread,"CreateThread");
    GP(PFN_Sleep,pSleep,"Sleep");
    GP(PFN_GetTickCount,pGetTickCount,"GetTickCount");
    GP(PFN_GetModuleFileNameW,pGetModuleFileNameW,"GetModuleFileNameW");
    GP(PFN_FindFirstFileW,pFindFirstFileW,"FindFirstFileW");
    GP(PFN_FindNextFileW,pFindNextFileW,"FindNextFileW");
    GP(PFN_FindClose,pFindClose,"FindClose");
    GP(PFN_GetProcessHeap,pGetProcessHeap,"GetProcessHeap");
    GP(PFN_HeapAlloc,pHeapAlloc,"HeapAlloc");
    GP(PFN_HeapFree,pHeapFree,"HeapFree");
#undef GP
    gHeap=pGetProcessHeap(); return gHeap!=0;
}

static int find_fist_recursive(const WCHAR* dir,WCHAR*out,U32 cap,U32 depth){
    if(depth>MAX_SCAN_DEPTH)return 0;
    WCHAR pattern[MAX_PATH_W]; WIN32_FIND_DATAW_CYZ fd; HANDLE h;
    if(!wcopy(pattern,MAX_PATH_W,dir)||!append_slash(pattern,MAX_PATH_W)||!wappend(pattern,MAX_PATH_W,W_STAR))return 0;
    h=pFindFirstFileW(pattern,&fd); if(h==INVALID_HANDLE_VALUE)return 0;
    do{
        if(fd.cFileName[0]=='.' && (fd.cFileName[1]==0 || (fd.cFileName[1]=='.'&&fd.cFileName[2]==0)))continue;
        if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            WCHAR child[MAX_PATH_W];
            if(wcopy(child,MAX_PATH_W,dir)&&append_slash(child,MAX_PATH_W)&&wappend(child,MAX_PATH_W,fd.cFileName)){
                if(find_fist_recursive(child,out,cap,depth+1)){pFindClose(h);return 1;}
            }
        } else if(wide_eq_ci(fd.cFileName,W_FISTGIF)){
            if(fd.nFileSizeHigh==0 && fd.nFileSizeLow>=6 && fd.nFileSizeLow<=MAX_GIF_BYTES){
                if(wcopy(out,cap,dir)&&append_slash(out,cap)&&wappend(out,cap,fd.cFileName)){pFindClose(h);return 1;}
            }
        }
    }while(pFindNextFileW(h,&fd));
    pFindClose(h); return 0;
}

static int get_modloader_root(WCHAR*out,U32 cap){
    U32 n=pGetModuleFileNameW(0,out,cap); if(!n||n>=cap)return 0;
    while(n>0){if(out[n-1]=='\\'||out[n-1]=='/'){out[n]=0;break;}n--;}
    if(n==0)return 0;
    return wappend(out,cap,W_MODLOADER);
}

typedef RwRaster* (CDECL *PFN_RwRasterCreate)(I32,I32,I32,I32);
typedef void* (CDECL *PFN_RwRasterLock)(RwRaster*,U8,I32);
typedef RwRaster* (CDECL *PFN_RwRasterUnlock)(RwRaster*);
typedef RwTexture* (CDECL *PFN_RwTextureCreate)(RwRaster*);
typedef BOOL (CDECL *PFN_RwRasterDestroy)(RwRaster*);

typedef struct { RwTexture* tex; U32 delay; } Frame;

static RwTexture* make_texture(GpImage img,U32 w,U32 h,PFN_GdipBitmapLockBits lockbits,PFN_GdipBitmapUnlockBits unlockbits){
    PFN_RwRasterCreate rwCreate=(PFN_RwRasterCreate)(gGameBase+0x3FB230);
    PFN_RwRasterLock rwLock=(PFN_RwRasterLock)(gGameBase+0x3FB2D0);
    PFN_RwRasterUnlock rwUnlock=(PFN_RwRasterUnlock)(gGameBase+0x3FAEC0);
    PFN_RwTextureCreate rwTexCreate=(PFN_RwTextureCreate)(gGameBase+0x3F37C0);
    PFN_RwRasterDestroy rwDestroy=(PFN_RwRasterDestroy)(gGameBase+0x3FB020);
    RwTexture* result=0;
    {
        GpRect_CYZ rc; BitmapData_CYZ bd; U32 rowbytes=w*4, y; RwRaster*r; U8*dst;
        rc.X=rc.Y=0; rc.Width=(I32)w; rc.Height=(I32)h; mem_zero(&bd,sizeof(bd));
        if(lockbits(img,&rc,ImageLockModeRead,PixelFormat32bppARGB,&bd)!=GDI_OK || !bd.Scan0)return 0;
        r=rwCreate((I32)w,(I32)h,32,0x504); if(!r){unlockbits(img,&bd);return 0;}
        dst=(U8*)rwLock(r,0,5); if(!dst){rwDestroy(r);unlockbits(img,&bd);return 0;}
        {
            I32 rstride=*(I32*)((U8*)r+0x18);
            I32 sstride=bd.Stride;
            U8* src=(U8*)bd.Scan0;
            if(sstride<0){src += (h-1)*(U32)(-sstride); sstride=-sstride;}
            for(y=0;y<h;y++) mem_copy(dst+y*(U32)rstride, src+y*(U32)sstride, rowbytes);
        }
        rwUnlock(r); unlockbits(img,&bd);
        result=rwTexCreate(r); if(!result)rwDestroy(r);
    }
    return result;
}

static U32 WINAPI worker(void* unused){
    HMODULE gd; ULONG token=0; GpImage img=0; WCHAR root[MAX_PATH_W], gif[MAX_PATH_W]; U32 w=0,h=0,count=1,dimc=0,i,actual;
    GUID_CYZ guid; Frame* frames=0; U32 propSize=0; PropertyItem_CYZ* prop=0;
    PFN_GdiplusStartup startup; PFN_GdiplusShutdown shutdown; PFN_GdipLoadImageFromFile load; PFN_GdipDisposeImage dispose;
    PFN_GdipGetImageWidth getw; PFN_GdipGetImageHeight geth; PFN_GdipImageGetFrameDimensionsCount getdc;
    PFN_GdipImageGetFrameDimensionsList getdl; PFN_GdipImageGetFrameCount getfc; PFN_GdipImageSelectActiveFrame selectf;
    PFN_GdipBitmapLockBits lockbits; PFN_GdipBitmapUnlockBits unlockbits; PFN_GdipGetPropertyItemSize getps; PFN_GdipGetPropertyItem getp;
    U8* spritePtr; RwTexture* original; U32 start,idx=0,next;
    (void)unused;
    pSleep(2500); /* ensure DllMain/loader lock is long gone */
    {
        U8* peb=(U8*)get_peb(); if(!peb)return 0; gGameBase=*(U8**)(peb+8); if(!gGameBase)return 0;
        if(gGameBase[0]!='M'||gGameBase[1]!='Z')return 0;
        {
            U32 nt=*(U32*)(gGameBase+0x3C);
            U32 stamp=*(U32*)(gGameBase+nt+8);
            U32 size=*(U32*)(gGameBase+nt+0x50);
            if(stamp!=0x427101CAu || size<0x7AB300u)return 0;
        }
    }
    if(!get_modloader_root(root,MAX_PATH_W) || !find_fist_recursive(root,gif,MAX_PATH_W,0))return 0;
    /* wait until HUD sprite 0 has been initialised by the game */
    spritePtr=gGameBase+0x7AB1FC; original=0;
    start=pGetTickCount();
    while((U32)(pGetTickCount()-start)<120000u){
        original=*(RwTexture**)spritePtr;
        if(original)break; pSleep(100);
    }
    if(!original)return 0;
    gd=pLoadLibraryW(W_GDIPLUS); if(!gd)return 0;
#define GD(type,var,nm) var=(type)pGetProcAddress(gd,nm); if(!var)return 0
    GD(PFN_GdiplusStartup,startup,"GdiplusStartup"); GD(PFN_GdiplusShutdown,shutdown,"GdiplusShutdown");
    GD(PFN_GdipLoadImageFromFile,load,"GdipLoadImageFromFile"); GD(PFN_GdipDisposeImage,dispose,"GdipDisposeImage");
    GD(PFN_GdipGetImageWidth,getw,"GdipGetImageWidth"); GD(PFN_GdipGetImageHeight,geth,"GdipGetImageHeight");
    GD(PFN_GdipImageGetFrameDimensionsCount,getdc,"GdipImageGetFrameDimensionsCount"); GD(PFN_GdipImageGetFrameDimensionsList,getdl,"GdipImageGetFrameDimensionsList");
    GD(PFN_GdipImageGetFrameCount,getfc,"GdipImageGetFrameCount"); GD(PFN_GdipImageSelectActiveFrame,selectf,"GdipImageSelectActiveFrame");
    GD(PFN_GdipBitmapLockBits,lockbits,"GdipBitmapLockBits"); GD(PFN_GdipBitmapUnlockBits,unlockbits,"GdipBitmapUnlockBits");
    GD(PFN_GdipGetPropertyItemSize,getps,"GdipGetPropertyItemSize"); GD(PFN_GdipGetPropertyItem,getp,"GdipGetPropertyItem");
#undef GD
    {
        struct { U32 GdiplusVersion; void* DebugEventCallback; BOOL SuppressBackgroundThread; BOOL SuppressExternalCodecs; } in;
        in.GdiplusVersion=1;in.DebugEventCallback=0;in.SuppressBackgroundThread=FALSE;in.SuppressExternalCodecs=FALSE;
        if(startup(&token,&in,0)!=GDI_OK)return 0;
    }
    if(load(gif,&img)!=GDI_OK||!img){shutdown(token);return 0;}
    if(getw(img,&w)!=GDI_OK||geth(img,&h)!=GDI_OK||!w||!h||w>2048u||h>2048u){dispose(img);shutdown(token);return 0;}
    mem_zero(&guid,sizeof(guid));
    if(getdc(img,&dimc)==GDI_OK && dimc>0 && getdl(img,&guid,1)==GDI_OK){if(getfc(img,&guid,&count)!=GDI_OK||!count)count=1;} else count=1;
    {
        U32 per=w*h*4u; U32 bymem=per?MAX_DECODE_BYTES/per:1; if(bymem<1)bymem=1; actual=count; if(actual>bymem)actual=bymem; if(actual>MAX_FRAMES)actual=MAX_FRAMES;
    }
    frames=(Frame*)pHeapAlloc(gHeap,8,actual*sizeof(Frame)); if(!frames){dispose(img);shutdown(token);return 0;} mem_zero(frames,actual*sizeof(Frame));
    if(getps(img,PropertyTagFrameDelay,&propSize)==GDI_OK && propSize>=16 && propSize<65536u){prop=(PropertyItem_CYZ*)pHeapAlloc(gHeap,8,propSize); if(prop && getp(img,PropertyTagFrameDelay,propSize,prop)!=GDI_OK){pHeapFree(gHeap,0,prop);prop=0;}}
    for(i=0;i<actual;i++){
        U32 d=100;
        if(count>1 && selectf(img,&guid,i)!=GDI_OK)break;
        if(prop && prop->value && i*4u+4u<=prop->length){U32 v=((U32*)prop->value)[i]; if(v)d=v*10u;}
        if(d<20)d=20; if(d>10000)d=10000;
        frames[i].delay=d; frames[i].tex=make_texture(img,w,h,lockbits,unlockbits); if(!frames[i].tex)break;
    }
    actual=i; if(prop)pHeapFree(gHeap,0,prop); dispose(img); shutdown(token); if(!actual){pHeapFree(gHeap,0,frames);return 0;}
    idx=0; next=pGetTickCount()+frames[0].delay;
    for(;;){
        U32 now=pGetTickCount();
        *(RwTexture**)spritePtr=frames[idx].tex;
        if((I32)(now-next)>=0){idx++;if(idx>=actual)idx=0;next=now+frames[idx].delay;}
        pSleep(5);
    }
    return 0;
}

BOOL WINAPI DllMain(HMODULE self,U32 reason,void* reserved){
    (void)reserved; if(MARKER[0]==0)return TRUE;
    if(reason==DLL_PROCESS_ATTACH){
        if(!resolve_kernel())return TRUE;
        pDisableThreadLibraryCalls(self);
        {HANDLE t=pCreateThread(0,0,worker,0,0,0); (void)t;}
    }
    return TRUE;
}
