// system
#include <windows.h>
#include <cxxabi.h>

// C++
#include <typeinfo>
#include <memory>

// local
#include "interfaces.hpp"
#include "com_ptr.hpp"
#include "logger.hpp"
#include "bstr.hpp"

namespace rap
{
    static void print_indent(char c, size_t indent)
    {
        for (size_t i = 0; i < indent; ++i) putc(' ', stdout);
    }

    template<typename... ARGS>
    static void println_indent(size_t indent, ARGS... args)
    {
        print_indent(' ', indent);
        printf(std::forward<ARGS>(args)...);
        putc('\n', stdout);
    }

    void dump_ia(com_ptr<IAccessible>& ia, size_t index, size_t indent);

    void dump_ia(com_ptr<IAccessible>& ia)
    {
        printf("----\n");
        dump_ia(ia, 1, 0);
    }

    template<typename T> const char* type_name()
    {
        static std::unique_ptr<char, decltype(&::free)> sname(abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr), &free);
        return sname.get();
    }

    template<typename INTERFACE>
    void dump_interface_methods(com_ptr<INTERFACE>& iface, size_t indent) {}

    template<typename INTERFACE>
    void dump_interface(com_ptr<IAccessible2>& ia2, size_t indent)
    {
        com_ptr<INTERFACE> iface;
        auto hr = ia2->QueryInterface(iid<INTERFACE>::value, (void**)&iface);
        if(hr == S_OK)
        {
            println_indent(indent, "%s : S_OK", type_name<INTERFACE>());
            dump_interface_methods<INTERFACE>(iface, indent+1);
        } else if (hr != E_NOINTERFACE) {
            println_indent(indent, "%s : 0x%08x", type_name<INTERFACE>(), (uint32_t)hr);
        }
    }

    template<>
    void dump_interface_methods<IAccessibleAction>(com_ptr<IAccessibleAction>& iface, size_t indent)
    {
        LONG nActions;
        LOG_IF_FAILED(iface->nActions(&nActions));
        println_indent(indent, "nActions : %li", nActions);
        for(LONG i = 0; i < nActions; ++i)
        {
            bstr description;
            LOG_IF_FAILED(iface->get_description(i, &description));
            println_indent(indent+1, "get_description(%li) : %S", i, description.get());

            BSTR* keyBindings = nullptr;
            LONG nBindings = 0;
            // FIXME?: ia2 spec says nMaxBindings should be ignored, but firefox explicitly checks for greater than 0
            LOG_IF_FAILED(iface->get_keyBinding(i, 1, &keyBindings, &nBindings));
            println_indent(indent+1, "nBindings : %li", nBindings);

            for(LONG j = 0; j < nBindings; ++j)
            {
                println_indent(indent+2, "keyBinding[%li] : %S", j, keyBindings[j]);
                ::SysFreeString(keyBindings[j]);
            }
            ::CoTaskMemFree(keyBindings);

            bstr name;
            if(LOG_IF_FAILED(iface->get_name(i, &name)))
            {
                println_indent(indent+1, "name : %S", name.get());
            }

            bstr localizedName;
            if(LOG_IF_FAILED_EX(iface->get_localizedName(i, &name), E_NOTIMPL))
            {
                println_indent(indent+1, "localizedName : %S", localizedName.get());
            }
        }
    }

    template<>
    void dump_interface_methods<IAccessibleApplication>(com_ptr<IAccessibleApplication>& iface, size_t indent)
    {
        // TODO: no example in example.com DOM
    }


    template<>
    void dump_interface_methods<IAccessibleComponent>(com_ptr<IAccessibleComponent>& iface, size_t indent)
    {
        long x;
        long y;
        if(LOG_IF_FAILED(iface->get_locationInParent(&x, &y)))
        {
            println_indent(indent, "locationInParent : { x : %li y : %li }", x, y);
        }

        IA2Color bg;
        if(LOG_IF_FAILED(iface->get_background(&bg)))
        {
            println_indent(indent, "background : rgb(%d,%d,%d)", (bg & 0xFF0000) >> 16, (bg & 0xFF00) >> 8, bg & 0xFF);
        }

        IA2Color fg;
        if(LOG_IF_FAILED(iface->get_foreground(&fg)))
        {
            println_indent(indent, "foreground : rgb(%d,%d,%d)", (fg & 0xFF0000) >> 16, (fg & 0xFF00) >> 8, fg & 0xFF);
        }
    }

    template<>
    void dump_interface_methods<IAccessibleDocument>(com_ptr<IAccessibleDocument>& iface, size_t indent)
    {
        // TODO: no example in example.com DOM
    }

    template<>
    void dump_interface_methods<IAccessibleEditableText>(com_ptr<IAccessibleEditableText>& iface, size_t indent)
    {
        // TODO: these are clipboard actions
    }

    template<>
    void dump_interface_methods<IAccessibleHyperlink>(com_ptr<IAccessibleHyperlink>& iface, size_t indent)
    {
        long startIndex;
        if(LOG_IF_FAILED(iface->get_startIndex(&startIndex)))
        {
            println_indent(indent, "startIndex : %li", startIndex);
        }

        long endIndex;
        if(LOG_IF_FAILED(iface->get_endIndex(&endIndex)))
        {
            println_indent(indent, "endIndex : %li", endIndex);
        }

        boolean valid;
        if(LOG_IF_FAILED(iface->get_valid(&valid)))
        {
            println_indent(indent, "valid : %s", valid ? "true" : "false");
        }

        // TODO: try fucking arouond with the get_anchor methods */
    }

    template<>
    void dump_interface_methods<IAccessibleHypertext>(com_ptr<IAccessibleHypertext>& iface, size_t indent)
    {
        long nHyperlinks = 0;
        if(LOG_IF_FAILED(iface->get_nHyperlinks(&nHyperlinks)))
        {
            println_indent(indent, "nHyperlinks : %li", nHyperlinks);
        }
        TRACE();
        for (long i = 0; i < nHyperlinks; ++i)
        {
            TRACE_MSG("hyperlink i : %li", i);
            com_ptr<IAccessibleHyperlink> currentHyperlink;
            if(LOG_IF_FAILED_EX(iface->get_hyperlink(i, &currentHyperlink), E_NOINTERFACE))
            {
                dump_interface_methods(currentHyperlink, indent+1);
            }
        }
    }

    template<>
    void dump_interface_methods<IAccessibleHypertext2>(com_ptr<IAccessibleHypertext2>& iface, size_t indent)
    {
        // TODO: not registered
    }

    template<>
    void dump_interface_methods<IAccessibleImage>(com_ptr<IAccessibleImage>& iface, size_t indent)
    {
        bstr description;
        if(LOG_IF_FAILED(iface->get_description(&description)))
        {
            println_indent(indent, "description : %S", description.get());
        }

        long x;
        long y;
        if(LOG_IF_FAILED(iface->get_imagePosition(IA2_COORDTYPE_PARENT_RELATIVE, &x, &y)))
        {

            println_indent(indent, "parent-relative position : { x : %li, y %li }", x, y);
        }
        if(LOG_IF_FAILED(iface->get_imagePosition(IA2_COORDTYPE_SCREEN_RELATIVE, &x, &y)))
        {
            println_indent(indent, "screen-relative position : { x : %li, y %li }", x, y);
        }

        long height;
        long width;
        if(LOG_IF_FAILED(iface->get_imageSize(&height, &width)))
        {
            println_indent(indent, "size : { width : %li, height : %li }", width, height);
        }
    }

    template<>
    void dump_interface_methods<IAccessibleRelation>(com_ptr<IAccessibleRelation>& iface, size_t indent)
    {
        // TODO: none in DOM
    }

    template<>
    void dump_interface_methods<IAccessibleTable>(com_ptr<IAccessibleTable>& iface, size_t indent)
    {
        // TODO: none in DOM
    }

    template<>
    void dump_interface_methods<IAccessibleTable2>(com_ptr<IAccessibleTable2>& iface, size_t indent)
    {
        // TODO: none in DOM
    }

    template<>
    void dump_interface_methods<IAccessibleTableCell>(com_ptr<IAccessibleTableCell>& iface, size_t indent)
    {
        // TODO: none in DOM
    }

    template<>
    void dump_interface_methods<IAccessibleText>(com_ptr<IAccessibleText>& iface, size_t indent)
    {
        // TODO: lots of methods here :(

        println_indent(indent, "HELLO!");

        long startOffset;
        long endOffset;
        bstr textAttributes;
        if(LOG_IF_FAILED(iface->get_attributes(0, &startOffset, &endOffset, &textAttributes)))
        {
            println_indent(indent, "startOffset : %li", startOffset);
            println_indent(indent, "endOffset : %li", endOffset);
            println_indent(indent, "textAttributes : %S", textAttributes.get());
        }

        long caretOffset;
        if(LOG_IF_FAILED(iface->get_caretOffset(&caretOffset)))
        {
            println_indent(indent, "caretOffset: %li", caretOffset);
        }

        struct {
            long x;
            long y;
            long width;
            long height;
        } characterExtents;
        if(LOG_IF_FAILED(iface->get_characterExtents(0, IA2_COORDTYPE_PARENT_RELATIVE, &characterExtents.x, &characterExtents.y, &characterExtents.width, &characterExtents.height)))
        {
            println_indent(indent, "characterExtents : { x : %li, y : %li, width : %li, height : %li }", characterExtents.x, characterExtents.y, characterExtents.width, characterExtents.height);
        }

        long nSelections;
        if(LOG_IF_FAILED(iface->get_nSelections(&nSelections)))
        {
            println_indent(indent, "nSelections : %li", nSelections);
        }

        for(long i = 0; i < nSelections; ++i)
        {
            long startOffset;
            long endOffset;
            if(LOG_IF_FAILED(iface->get_selection(i, &startOffset, &endOffset)))
            {
                println_indent(indent, "selection[%li] : { startOffset : %li, endOffset : %li }", i, startOffset, endOffset);
            }
        }

        long nCharacters;
        if (LOG_IF_FAILED(iface->get_nCharacters(&nCharacters)))
        {
            println_indent(indent, "nCharacters : %li", nCharacters);
        }

        bstr text;
        if(LOG_IF_FAILED(iface->get_text(0, nCharacters, &text)))
        {
            println_indent(indent, "text : %S", text.get());
        }
    }

    template<>
    void dump_interface_methods<IAccessibleValue>(com_ptr<IAccessibleValue>&iface, size_t indent)
    {

    }

    void dump_ia(com_ptr<IAccessible>& ia, size_t index, size_t indent)
    {
        println_indent(indent, "index : %u", index);

        if (!ia)
        {
            println_indent(indent, ("null"));
            return;
        }

        bstr name;
        VARIANT varName;
        ::VariantInit(&varName);
        varName.vt = VT_I4;
        varName.lVal = CHILDID_SELF;
        THROW_IF_FAILED(ia->get_accName(varName, &name));

        println_indent(indent, "name : %S", name.get());
        println_indent(indent, "interfaces :");

        com_ptr<IServiceProvider> pService = ia.QueryInterface<IServiceProvider>();
        if(pService)
        {
            com_ptr<IAccessible2> ia2;
            if(LOG_IF_FAILED(pService->QueryService(iid<IAccessible>::value, iid<IAccessible2>::value, (void**)&ia2)))
            {
                dump_interface<IAccessible>(ia2, indent+1);
                dump_interface<IAccessible2>(ia2, indent+1);
                // dump_interface<IAccessible2_2>(ia2, indent+1);
                // dump_interface<IAccessible2_3>(ia2, indent+1);
                dump_interface<IAccessibleAction>(ia2, indent+1);
                dump_interface<IAccessibleApplication>(ia2, indent+1);
                dump_interface<IAccessibleComponent>(ia2, indent+1);
                dump_interface<IAccessibleDocument>(ia2, indent+1);
                dump_interface<IAccessibleEditableText>(ia2, indent+1);
                dump_interface<IAccessibleHyperlink>(ia2, indent+1);
                dump_interface<IAccessibleHypertext>(ia2, indent+1);
                // dump_interface<IAccessibleHypertext2>(ia2, indent+1);
                dump_interface<IAccessibleImage>(ia2, indent+1);
                dump_interface<IAccessibleRelation>(ia2, indent+1);
                dump_interface<IAccessibleTable>(ia2, indent+1);
                dump_interface<IAccessibleTable2>(ia2, indent+1);
                dump_interface<IAccessibleTableCell>(ia2, indent+1);
                dump_interface<IAccessibleText>(ia2, indent+1);
                dump_interface<IAccessibleText2>(ia2, indent+1);
                dump_interface<IAccessibleValue>(ia2, indent+1);
            }
        }
        else
        {
            printf("pService is NULL\n");
        }

        long childCount = 0;
        THROW_IF_FAILED(ia->get_accChildCount(&childCount));

        println_indent(indent, "children: %li", childCount);

        for(long i = 1; i <= childCount; ++i )
        {
            VARIANT varChild;
            ::VariantInit(&varChild);
            varChild.vt = VT_I4;
            varChild.lVal = i;

            com_ptr<IDispatch> currentDispatch;
            THROW_IF_FAILED(ia->get_accChild(varChild, &currentDispatch));
            if (currentDispatch)
            {
                auto currentChild = currentDispatch.QueryInterface<IAccessible>();
                dump_ia(currentChild, i, indent+1);
            }
            ::VariantClear(&varChild);
        }
    }
}