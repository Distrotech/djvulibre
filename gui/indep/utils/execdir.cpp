//C-  -*- C++ -*-
//C- -------------------------------------------------------------------
//C- DjVuLibre-3.5
//C- Copyright (c) 2002  Leon Bottou and Yann Le Cun.
//C- Copyright (c) 2001  AT&T
//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, Version 2. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C- 
//C- DjVuLibre-3.5 is derived from the DjVu(r) Reference Library
//C- distributed by Lizardtech Software.  On July 19th 2002, Lizardtech 
//C- Software authorized us to replace the original DjVu(r) Reference 
//C- Library notice by the following text (see doc/lizard2002.djvu):
//C-
//C-  ------------------------------------------------------------------
//C- | DjVu (r) Reference Library (v. 3.5)
//C- | Copyright (c) 1999-2001 LizardTech, Inc. All Rights Reserved.
//C- | The DjVu Reference Library is protected by U.S. Pat. No.
//C- | 6,058,214 and patents pending.
//C- |
//C- | This software is subject to, and may be distributed under, the
//C- | GNU General Public License, Version 2. The license should have
//C- | accompanied the software or you may obtain a copy of the license
//C- | from the Free Software Foundation at http://www.fsf.org .
//C- |
//C- | The computer code originally released by LizardTech under this
//C- | license and unmodified by other parties is deemed "the LIZARDTECH
//C- | ORIGINAL CODE."  Subject to any third party intellectual property
//C- | claims, LizardTech grants recipient a worldwide, royalty-free, 
//C- | non-exclusive license to make, use, sell, or otherwise dispose of 
//C- | the LIZARDTECH ORIGINAL CODE or of programs derived from the 
//C- | LIZARDTECH ORIGINAL CODE in compliance with the terms of the GNU 
//C- | General Public License.   This grant only confers the right to 
//C- | infringe patent claims underlying the LIZARDTECH ORIGINAL CODE to 
//C- | the extent such infringement is reasonably necessary to enable 
//C- | recipient to make, have made, practice, sell, or otherwise dispose 
//C- | of the LIZARDTECH ORIGINAL CODE (or portions thereof) and not to 
//C- | any greater extent that may be necessary to utilize further 
//C- | modifications or combinations.
//C- |
//C- | The LIZARDTECH ORIGINAL CODE is provided "AS IS" WITHOUT WARRANTY
//C- | OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
//C- | TO ANY WARRANTY OF NON-INFRINGEMENT, OR ANY IMPLIED WARRANTY OF
//C- | MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//C- +------------------------------------------------------------------
// 
// $Id$
// $Name$

#ifdef __GNUG__
#pragma implementation
#endif
#include "DjVuConfig.h"

#include "DjVuMessageLite.h"
#include "DjVuMessage.h"

#include "execdir.h"


static GList<GURL>
parsePATH(void)
{
  GList<GURL> retval;
  const char *path=getenv("PATH");
  if(path)
  {
    GNativeString p(path);
    int from=0;
    for(int to;(to=p.search(':',from))>0;from=to+1)
    {
      if(to > from)
      {
        retval.append(GURL::Filename::Native(p.substr(from,to-from)));
      }
    }
    if((from+1)<(int)p.length())
    {
      retval.append(GURL::Filename::Native(p.substr(from,-1)));
    }
  }
  return retval;
}

GURL 
getExecDir(void)
{
  // This is the same as GetModulePath in DjVuMessage.cpp
 GURL retval;
 GUTF8String &xprogramname=DjVuMessage::programname();
 if(xprogramname.length())
 {
   if(xprogramname[1]=='/'
     ||!xprogramname.cmp("../",3)
     ||!xprogramname.cmp("./",2))
   {
     retval=GURL::Filename::UTF8(xprogramname);
   }
   if(retval.is_empty() || !retval.is_file())
   {
     GList<GURL> paths(parsePATH());
     GMap<GUTF8String,void *> pathMAP;
     for(GPosition pos=paths;pos;++pos)
     {
       retval=GURL::UTF8(xprogramname,paths[pos]);
       const GUTF8String path(retval.get_string());
       if(!pathMAP.contains(path))
       {
         if(retval.is_file())
           break;
         pathMAP[path]=0;
       }
     }
   }
   if (! retval.is_empty() )
     retval = retval.follow_symlinks();
   if (! retval.is_empty() )
     retval = retval.base();
 }
 return retval;
}

GURL 
getDjVuDataFile(const char *fname)
{
  GList<GURL> paths = DjVuMessage::GetProfilePaths();
  GUTF8String file = fname;
  for (GPosition pos=paths; pos; ++pos)
    {
      GURL url = GURL(file, paths[pos]);
      if(url.is_file())
        return url;
    }
  return GURL();
}


