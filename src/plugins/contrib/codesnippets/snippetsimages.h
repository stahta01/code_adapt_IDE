/*
	This file is part of Code Snippets, a plugin for Code::Blocks
	Copyright (C) 2006 Arto Jonsson
	Copyright (C) 2007 Pecan Heber

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
// RCS-ID: $Id: snippetsimages.h 10362 2015-07-26 08:13:33Z jenslody $
#ifndef SNIPIMAGES_H
#define SNIPIMAGES_H

#include <wx/imaglist.h>

#if not defined(SNIPPETS_TREE_IMAGE_COUNT)
    #define SNIPPETS_TREE_IMAGE_COUNT 6
    #define TREE_IMAGE_ALL_SNIPPETS 0
    #define TREE_IMAGE_CATEGORY     1
    #define TREE_IMAGE_SNIPPET      2
    #define TREE_IMAGE_SNIPPET_TEXT 3
    #define TREE_IMAGE_SNIPPET_FILE 4
    #define TREE_IMAGE_SNIPPET_URL  5
#endif

class SnipImages
{
    public:
        SnipImages();
       ~SnipImages();
       void RegisterImage( char** xpm_data );
       wxImageList* GetSnipImageList(){ return m_pSnippetsTreeImageList;}
       wxIcon       GetSnipListIcon(int index);

    protected:

    private:
        wxImageList* m_pSnippetsTreeImageList;

};

#endif // SNIPIMAGES_H
