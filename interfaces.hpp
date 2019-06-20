#pragma once

// windows
#include <windows.h>

// local
#include "com_ptr.hpp"

// interfaces
#include "Accessible2.h"
#include "Accessible2_2.h"
#include "Accessible2_3.h"
#include "AccessibleAction.h"
#include "AccessibleApplication.h"
#include "AccessibleComponent.h"
#include "AccessibleDocument.h"
#include "AccessibleEditableText.h"
#include "AccessibleEventId.h"
#include "AccessibleHyperlink.h"
#include "AccessibleHypertext.h"
#include "AccessibleHypertext2.h"
#include "AccessibleImage.h"
#include "AccessibleRelation.h"
#include "AccessibleRole.h"
#include "AccessibleStates.h"
#include "AccessibleTable.h"
#include "AccessibleTable2.h"
#include "AccessibleTableCell.h"
#include "AccessibleText.h"
#include "AccessibleText2.h"
#include "AccessibleValue.h"
#include "IA2CommonTypes.h"


namespace rap
{
    #define MAKE_IID(INTERFACE) template<> struct iid<INTERFACE> { constexpr static auto& value = IID_##INTERFACE;}

    MAKE_IID(IUnknown);
    MAKE_IID(IDispatch);
    MAKE_IID(IServiceProvider);

    MAKE_IID(IAccessible);
    MAKE_IID(IAccessible2);
    MAKE_IID(IAccessible2_2);
    MAKE_IID(IAccessible2_3);
    MAKE_IID(IAccessibleAction);
    MAKE_IID(IAccessibleApplication);
    MAKE_IID(IAccessibleComponent);
    MAKE_IID(IAccessibleDocument);
    MAKE_IID(IAccessibleEditableText);
    MAKE_IID(IAccessibleHyperlink);
    MAKE_IID(IAccessibleHypertext);
    MAKE_IID(IAccessibleHypertext2);
    MAKE_IID(IAccessibleImage);
    MAKE_IID(IAccessibleRelation);
    MAKE_IID(IAccessibleTable);
    MAKE_IID(IAccessibleTable2);
    MAKE_IID(IAccessibleTableCell);
    MAKE_IID(IAccessibleText);
    MAKE_IID(IAccessibleText2);
    MAKE_IID(IAccessibleValue);
}