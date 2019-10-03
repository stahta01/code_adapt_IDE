/*
* This file is part of wxSmith plugin for Code::Blocks Studio
* Copyright (C) 2006-2007  Bartlomiej Swiecki
*
* wxSmith is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* wxSmith is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with wxSmith. If not, see <http://www.gnu.org/licenses/>.
*
* $Revision: 7835 $
* $Id: wxsbitmapcombobox.h 7835 2012-02-22 14:40:26Z mortenmacfly $
* $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/plugins/contrib/wxSmith/wxwidgets/defitems/wxsbitmapcombobox.h $
*/

#ifndef WXSBITMAPCOMBOBOX_H
#define WXSBITMAPCOMBOBOX_H

#include <wx/bmpcbox.h>

#include "../wxswidget.h"
#include "wxsimagelist.h"
#include "../properties/wxsimagelisteditordlg.h"


/** \brief Class for wxsBitmapComboBox widget */
class wxsBitmapComboBox: public wxsWidget
{
    public:

        wxsBitmapComboBox(wxsItemResData* Data);

    private:

        virtual void        OnBuildCreatingCode();
        virtual wxObject   *OnBuildPreview(wxWindow* Parent,long Flags);
        virtual void        OnEnumWidgetProperties(long Flags);

                void        FindAllImageLists(wxArrayString &aNames);
                void        UpdateComboItemList(void);
                void        ParseComboItem(wxString inSource, wxString &outItem, int &outIndex);



        wxString        mImageList;                 // list to use to select images
        wxArrayString   mItems;                     // text of drop-down items
};

#endif
