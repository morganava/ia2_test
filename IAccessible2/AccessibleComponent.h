/*** Autogenerated by WIDL 3.20 from /home/pospeselr/Code/Tor/tor-browser/other-licenses/ia2/AccessibleComponent.idl - Do not edit ***/

#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __accessiblecomponent_h__
#define __accessiblecomponent_h__

/* Forward declarations */

#ifndef __IAccessibleComponent_FWD_DEFINED__
#define __IAccessibleComponent_FWD_DEFINED__
typedef interface IAccessibleComponent IAccessibleComponent;
#ifdef __cplusplus
interface IAccessibleComponent;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <objidl.h>
#include <oaidl.h>
#include <oleacc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef LONG IA2Color;
/*****************************************************************************
 * IAccessibleComponent interface
 */
#ifndef __IAccessibleComponent_INTERFACE_DEFINED__
#define __IAccessibleComponent_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAccessibleComponent, 0x1546d4b0, 0x4c98, 0x4bda, 0x89,0xae, 0x9a,0x64,0x74,0x8b,0xdd,0xe4);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("1546d4b0-4c98-4bda-89ae-9a64748bdde4")
IAccessibleComponent : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE get_locationInParent(
        LONG *x,
        LONG *y) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_foreground(
        IA2Color *foreground) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_background(
        IA2Color *background) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAccessibleComponent, 0x1546d4b0, 0x4c98, 0x4bda, 0x89,0xae, 0x9a,0x64,0x74,0x8b,0xdd,0xe4)
#endif
#else
typedef struct IAccessibleComponentVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAccessibleComponent *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAccessibleComponent *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAccessibleComponent *This);

    /*** IAccessibleComponent methods ***/
    HRESULT (STDMETHODCALLTYPE *get_locationInParent)(
        IAccessibleComponent *This,
        LONG *x,
        LONG *y);

    HRESULT (STDMETHODCALLTYPE *get_foreground)(
        IAccessibleComponent *This,
        IA2Color *foreground);

    HRESULT (STDMETHODCALLTYPE *get_background)(
        IAccessibleComponent *This,
        IA2Color *background);

    END_INTERFACE
} IAccessibleComponentVtbl;

interface IAccessibleComponent {
    CONST_VTBL IAccessibleComponentVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAccessibleComponent_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAccessibleComponent_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAccessibleComponent_Release(This) (This)->lpVtbl->Release(This)
/*** IAccessibleComponent methods ***/
#define IAccessibleComponent_get_locationInParent(This,x,y) (This)->lpVtbl->get_locationInParent(This,x,y)
#define IAccessibleComponent_get_foreground(This,foreground) (This)->lpVtbl->get_foreground(This,foreground)
#define IAccessibleComponent_get_background(This,background) (This)->lpVtbl->get_background(This,background)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT IAccessibleComponent_QueryInterface(IAccessibleComponent* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG IAccessibleComponent_AddRef(IAccessibleComponent* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG IAccessibleComponent_Release(IAccessibleComponent* This) {
    return This->lpVtbl->Release(This);
}
/*** IAccessibleComponent methods ***/
static FORCEINLINE HRESULT IAccessibleComponent_get_locationInParent(IAccessibleComponent* This,LONG *x,LONG *y) {
    return This->lpVtbl->get_locationInParent(This,x,y);
}
static FORCEINLINE HRESULT IAccessibleComponent_get_foreground(IAccessibleComponent* This,IA2Color *foreground) {
    return This->lpVtbl->get_foreground(This,foreground);
}
static FORCEINLINE HRESULT IAccessibleComponent_get_background(IAccessibleComponent* This,IA2Color *background) {
    return This->lpVtbl->get_background(This,background);
}
#endif
#endif

#endif


#endif  /* __IAccessibleComponent_INTERFACE_DEFINED__ */

/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __accessiblecomponent_h__ */